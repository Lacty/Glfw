
#include <iostream>
#include <GLFW/glfw3.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <cmath>
#include <limits>
#include <thread>

#include "../include/appNative.hpp"

#include "../include/wav.hpp"


int main() {
  AppNative native(640, 480, "hoge");
  
  native.setup();
  native.setClearColor(Color::gray());

  // load wav
  Wav sound("assets/fanfare.wav");

  // create device, context
  ALCdevice*  device  = alcOpenDevice(nullptr);
  ALCcontext* context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);

  // make sin 440Hz
  //const size_t pcm_freq = 44100;
  //const float key_freq = 440.0;
  
  //ALshort pcm_data[pcm_freq];
  //for (size_t i = 0; i < pcm_freq; ++i) {
  //  pcm_data[i] = std::sin(key_freq * M_PI * 2.0 * i / pcm_freq)
  //                  * std::numeric_limits<ALshort>::max();
  //}

  // make buf
  ALuint buffer_id;
  alGenBuffers(1, &buffer_id);

  // cp buf to sin
  alBufferData(buffer_id,
               AL_FORMAT_STEREO16,
               sound.data(),
               sound.size(),
               sound.sampleRate());

  // make src
  ALuint source_id;
  alGenSources(1, &source_id);

  // source_id <- buf
  alSourcei(source_id, AL_BUFFER, buffer_id);

  // play src
  alSourcePlay(source_id);
  
  // wait 2 sec
  std::this_thread::sleep_for(std::chrono::seconds(2));

  // delete src
  alDeleteSources(1, &source_id);

  // delete buf
  alDeleteBuffers(1, &buffer_id);

  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();

    native.updateEvent();
  }

  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context);
  alcCloseDevice(device);
}
