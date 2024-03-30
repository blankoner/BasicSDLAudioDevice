#include "sdlaudiodevice.h"
#include "sdlwavaudiodata.h"

IAudioData* SDLAudioDevice::CreateAudioFromFile(const std::string& filePath)
{
  return new SDLWAVAudioData(filePath, false);
}

void SDLAudioDevice::ReleaseAudio(IAudioData* audioData)
{
  if(audioData)
  {
    delete audioData;
  }
}