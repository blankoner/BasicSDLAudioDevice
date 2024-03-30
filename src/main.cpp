#include <iostream>
#include <SDL2/SDL.h>

#include "include/iaudiodevice.h"
#include "include/iaudiocontext.h"
#include "include/audioobject.h"

#include "include/sdl/sdlaudiodevice.h"
#include "include/sdl/sdlaudiocontext.h"

#define FILE_PATH "../sounds/sample.wav"

int main()
{
  SDL_Init(SDL_INIT_AUDIO);

  IAudioDevice* device = new SDLAudioDevice;
  IAudioContext* context = new SDLAudioContext;

  IAudioData* data = device->CreateAudioFromFile(FILE_PATH);

  SampleInfo info;
  info.volume = 1.0;

  AudioObject sound(info, data);

  char in = 0;
  while(in != 'q')
  {
    std::cin >> in;
    switch(in)
    {
    case 'a':
      context->PlayAudio(sound);
      break;
    case 's':
      context->PauseAudio(sound);
      break;
    case 'd':
      context->StopAudio(sound);
      break;
    }
  }

  device->ReleaseAudio(data);

  delete device;
  delete context;

  SDL_Quit();
  return 0;
}