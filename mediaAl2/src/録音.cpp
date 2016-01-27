//
// OpenALによる録音
//

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <vector>
#include <thread>


int main() {
  // OpenALの初期化
  ALCdevice*  device  = alcOpenDevice(nullptr);
  ALCcontext* context = alcCreateContext(device, nullptr);
  alcMakeContextCurrent(context);

  // 録音デバイスを開く
  const int SAMPLING_RATE      = 44100;
  const int SAMPLE_BUFFER_SIZE = 1024;

  ALCdevice* capture_device = alcCaptureOpenDevice(nullptr,
                                                   SAMPLING_RATE,
                                                   AL_FORMAT_MONO16,
                                                   SAMPLE_BUFFER_SIZE);

  alcCaptureStart(capture_device);

  // 3秒ぶんの波形を格納する変数
  std::vector<ALshort> record_buffer;

#if 1
  // パターン1
  while (record_buffer.size() < (SAMPLING_RATE * 3)) {
    ALint sample;
    alcGetIntegerv(capture_device,
                   ALC_CAPTURE_SAMPLES,
                   sizeof(sample), &sample);

    if (sample > 0) {
      // 配列のサイズを拡張して録音した波形を追加
      size_t cur_sample = record_buffer.size();
      size_t new_sample = cur_sample + sample;
      record_buffer.resize(new_sample);

      alcCaptureSamples(capture_device,
                        (ALCvoid*)&record_buffer[cur_sample], sample);
    }
  }  
#else
  // パターン2
  while (record_buffer.size() < (SAMPLING_RATE * 3)) {
    ALint sample;
    alcGetIntegerv(capture_device,
                   ALC_CAPTURE_SAMPLES,
                   sizeof(sample), &sample);

    if (sample > 0) {
      // OpenALから録音した波形を受け取る
      std::vector<ALshort> buffer(sample);
      alcCaptureSamples(capture_device,
                        (ALCvoid*)&buffer[0], sample);

      // std::vectorの内容を他のstd::vectorに追加する
      std::copy(buffer.begin(), buffer.end(),
                std::back_inserter(record_buffer));
    }
  }
#endif

  alcCaptureStop(capture_device);

  
  // バッファの生成
  ALuint buffer_id;
  alGenBuffers(1, &buffer_id);

  // 録音したデータをバッファへコピー
  alBufferData(buffer_id,
               AL_FORMAT_MONO16,
               &record_buffer[0],                        // リニアPCM形式データ
               record_buffer.size() * sizeof(ALshort),   // サイズ(バイト数)
               SAMPLING_RATE);                           // サンプリングレート

  // ソースの生成
  ALuint source_id;
  alGenSources(1, &source_id);
  
  // ソースに再生したいバッファを割り当てる
  alSourcei(source_id, AL_BUFFER, buffer_id);

  // ソースの再生開始
  alSourcePlay(source_id);

  // ３秒待つ
  std::this_thread::sleep_for(std::chrono::seconds(3));
  
  // ソースの破棄
  alDeleteSources(1, &source_id);

  // バッファの破棄
  alDeleteBuffers(1, &buffer_id);
  
  // OpenALの後始末
  alcMakeContextCurrent(nullptr);
  alcDestroyContext(context);
  alcCloseDevice(device);
}
