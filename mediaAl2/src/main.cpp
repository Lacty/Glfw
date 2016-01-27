
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

  // open device
  ALCdevice* device = alcOpenDevice(nullptr);

  // set sampleRate
  const int SAMPLING_RATE      = 44100;
  const int SAMPLE_BUFFER_SIZE = 1024;
  
  ALCdevice* capture_device = alcCaptureOpenDevice(nullptr,
                                                   SAMPLING_RATE,
                                                   AL_FORMAT_MONO16,
                                                   SAMPLE_BUFFER_SIZE);

  ALCcontext* context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);

  std::vector<ALshort> record_buffer;
  
  // make buff
  ALuint buffer_id;
  alGenBuffers(1, &buffer_id);

  // make source
  ALuint source_id;
  alGenSources(1, &source_id);

  while (native.isOpen() && !native.isPushKey(GLFW_KEY_ESCAPE)) {
    native.clearWindowBuff();

    if (native.isPushButton(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // start
      alcCaptureStart(capture_device);
      std::cout << "record start" << std::endl;
    }
    
    if (native.isPressButton(GLFW_MOUSE_BUTTON_RIGHT))
    {
      if (record_buffer.size() < (SAMPLING_RATE * 3)) {
        ALint sample;
        alcGetIntegerv(capture_device,
                       ALC_CAPTURE_SAMPLES,
                       sizeof(sample), &sample);

        if (sample > 0) {
          size_t cur_sample = record_buffer.size();
          size_t new_sample = cur_sample + sample;
          record_buffer.resize(new_sample);

          alcCaptureSamples(capture_device,
                            (ALCvoid*)&record_buffer[cur_sample], sample);
        }
      }
    }
    
    if (native.isPullButton(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // stop capture
      alcCaptureStop(capture_device);
      
      alBufferData(buffer_id,
                   AL_FORMAT_MONO16,
                   &record_buffer[0],
                   record_buffer.size() * sizeof(ALshort),
                   SAMPLING_RATE);
      
      alSourcei(source_id, AL_BUFFER, buffer_id);
      alSourcePlay(source_id);
      std::cout << "record play" << std::endl;
    }

    native.updateEvent();
  }

  // delete source buff
  alDeleteSources(1, &source_id);
  alDeleteBuffers(1, &buffer_id);

  // close
  alcCaptureCloseDevice(capture_device);
  alcDestroyContext(context);
  alcCloseDevice(device);
}
