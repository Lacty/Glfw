
#pragma once

//
// wavデータを扱う
//

#include <string>
#include <vector>
#include <fstream>


class Wav {
public:
  struct Info {
    unsigned int id;
		unsigned int ch;
		unsigned int sample_rate;
		unsigned int bit;
		unsigned int size;
  };


  explicit Wav(const std::string& file);

  // チャンネル数を返す
	unsigned int channel() const;

  // データがステレオならtrueを返す
  bool isStereo() const;

  // サンプリングレートを返す
	unsigned int sampleRate() const;

  // データサイズ(バイト数)を返す
	unsigned int size() const;

  // 再生時間(秒)を返す
  float time() const;

  // 波形データを返す
	const char* data() const;

  
  // wavの情報を取得
  static bool analyzeWavFile(Info& info, std::ifstream& fstr);


private:
  Info info;
  float time_;
  std::vector<char> data_;

  
  // 指定バイト数のメモリの内容をint値にする
	static unsigned int getValue(const char* ptr, const unsigned int num);
  
  // wavの指定チャンクを探す
  static bool searchChunk(std::ifstream& fstr, const char* chunk);

  // チャンクのサイズを取得
	static unsigned int getChunkSize(std::ifstream& fstr);
  
};

