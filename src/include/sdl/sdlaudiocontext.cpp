#include "sdlaudiocontext.h"

static void SDLAudioContext_AudioCallback(void* userData, Uint8* streamIn, int length)
{
  SDLAudioContext* context = (SDLAudioContext*)userData;
  context->GenerateSamples(streamIn, length);
}

SDLAudioContext::SDLAudioContext()
{
  SDL_AudioSpec spec;
  
  //TO DO: make these values modifiable
  SDL_zero(spec);
  spec.freq = 44100;
  spec.format = AUDIO_S16SYS;
  spec.channels = 2;
  spec.samples = 2048;
  spec.callback = SDLAudioContext_AudioCallback;
  spec.userdata = this;

  //TO DO: handle different specs
  m_device = SDL_OpenAudioDevice(NULL, 0, &spec, 0, 0);
  if(m_device == 0)
  {
    //TO DO: proper error handling
    throw SDL_GetError();
  }

  SDL_PauseAudioDevice(m_device, 0);
}

SDLAudioContext::~SDLAudioContext()
{
  SDL_CloseAudioDevice(m_device);
}

void SDLAudioContext::PlayAudio(AudioObject& ao)
{
  SDL_LockAudioDevice(m_device);

  //This prevents duplicates
  RemoveAudio(ao);
  m_playingAudio.push_back(&ao);

  SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::PauseAudio(AudioObject& ao)
{
  SDL_LockAudioDevice(m_device);

  RemoveAudio(ao);

  SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::StopAudio(AudioObject& ao)
{
  SDL_LockAudioDevice(m_device);

  if(RemoveAudio(ao))
  {
    ao.SetPosition(0.0);
  }

  SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::GenerateSamples(Uint8* streamIn, int streamInLength)
{
  size_t streamLength = (size_t)(streamInLength/2);

  m_stream.reserve(streamLength);
  float* floatStream = *(float**)(&m_stream);

  for(size_t i = 0; i<streamLength; i++)
  {
    floatStream[i] = 0.0f;
  }

  std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
  std::vector<AudioObject*>::iterator end = m_playingAudio.end();
  for(; it != end; ++it)
  {
    if(!(*it)->GenerateSamples(floatStream, streamLength))
    {
      RemoveAudio(*(*it));
    }
  }

  Sint16* stream = (Sint16*)streamIn;
  for(size_t i = 0; i<streamLength; i++)
  {
    float value = floatStream[i];
    
    if(value > 1.0f)
    {
      value = 1.0f;
    }
    else if(value < -1.0f)
    {
      value = -1.0f;
    }
    
    stream[i] = (Sint16)(value * 32767);
  }
}

bool SDLAudioContext::RemoveAudio(AudioObject& ao)
{
  std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
  std::vector<AudioObject*>::iterator end = m_playingAudio.end();

  for(; it != end; ++it)
  {
    if(*it == &ao)
    {
      m_playingAudio.erase(it);
      return true;
    }
  }

  return false;
}