#include "sdlwavaudiodata.h"

SDLWAVAudioData::SDLWAVAudioData(const std::string& fileName, bool streamFromFile)
{
  //TO DO: handle streamFromFile
  SDL_AudioSpec wavSpec;
  Uint8* wavStart;
  Uint32 wavLength;

  if(SDL_LoadWAV(fileName.c_str(), &wavSpec, &wavStart, &wavLength) == NULL)
  {
    throw fileName;
  }

  m_position = wavStart;
  m_start = wavStart;
  m_length = wavLength;
}

SDLWAVAudioData::~SDLWAVAudioData()
{
  SDL_FreeWAV(m_start);
}

size_t SDLWAVAudioData::GenerateSamples(float* stream, size_t streamLength, size_t position, const SampleInfo& info)
{
  //TO DO: handle position
  if(m_length == 0)
  {
    return (size_t)-1;
  }

  Uint32 length = (Uint32)streamLength;
  length = (length > m_length ? m_length : length);

  //TO DO: make this more suitable for the different wav files
  Sint16* samples = (Sint16*)m_position;

  float factor = (float)info.volume * 1.0f/32768.0f;
  for(Uint32 i = 0; i < length; i++)
  {
    stream[i] = (*samples) * factor;
    samples++;
  }

  m_position = (Uint8*)samples;
  m_length -= (length*2);
}

size_t SDLWAVAudioData::GetAudioLength()
{
  return m_length;
}