#pragma once

#include "../iaudiocontext.h"
#include <vector>
#include <SDL2/SDL.h>

class SDLAudioContext : public IAudioContext
{
public:
  SDLAudioContext();
  virtual ~SDLAudioContext();

  virtual void PlayAudio(AudioObject& ao);
  virtual void PauseAudio(AudioObject& ao);
  virtual void StopAudio(AudioObject& ao);

  void GenerateSamples(Uint8* streamIn, int streamInLength);
private:
  SDL_AudioDeviceID m_device;
  std::vector<float> m_stream;
  std::vector<AudioObject*> m_playingAudio;

  bool RemoveAudio(AudioObject& ao);

  SDLAudioContext(SDLAudioContext& other){ (void)other; }
  void operator=(const SDLAudioContext& other){ (void)other; }
};