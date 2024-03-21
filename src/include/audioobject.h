#pragma once

#include "iaudiodata.h"
#include "sampleinfo.h"

class AudioObject
{
public:
  AudioObject(const SampleInfo& info, IAudioData* data);
  
  bool GenerateSamples(float* stream, size_t streamLength);
  void SetPosition(double position);
private:
  size_t m_audioPosition;
  size_t m_audioLength;
  SampleInfo m_sampleInfo;
  IAudioData* m_audioData;

  size_t PositionToAbsolutePosition(double position);
};