#pragma once

#include "sampleinfo.h"
#include <cstddef>

class IAudioData
{
public:
  virtual ~IAudioData(){}
  virtual size_t GenerateSamples(float* stream, size_t streamLength, size_t position, const SampleInfo& info) = 0;
  virtual size_t GetAudioLength() = 0;
private:

};