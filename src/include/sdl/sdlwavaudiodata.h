#pragma once

#include "../iaudiodata.h"
#include <SDL2/SDL.h>
#include <string>

class SDLWAVAudioData : public IAudioData
{
public:
  SDLWAVAudioData(const std::string& fileName, bool streamFromFile);
  virtual ~SDLWAVAudioData();

  virtual size_t GenerateSamples(float* stream, size_t streamLength, size_t position, const SampleInfo& info);
  virtual size_t GetAudioLength();
private:
  Uint8* m_position;
  Uint8* m_start;
  Uint32 m_length;

  SDLWAVAudioData(SDLWAVAudioData& other){ (void)other; }
  void operator=(const SDLWAVAudioData& other){ (void)other; }
};