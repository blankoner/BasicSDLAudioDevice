#include "include/audioobject.h"

AudioObject::AudioObject(const SampleInfo& info, IAudioData* data) : 
  m_audioPosition(0),
  m_audioLength(data->GetAudioLength()),
  m_sampleInfo(info),
  m_audioData(data) {}

bool AudioObject::GenerateSamples(float* stream, size_t streamLength)
{
  m_audioPosition = m_audioData->GenerateSamples(stream, streamLength, m_audioPosition, m_sampleInfo);

  if(m_audioPosition == (size_t)-1)
  {
    m_audioPosition = 0;
    return false;
  }

  return true;
}

void AudioObject::SetPosition(double position)
{
  if(position < 0.0)
  {
    position = 0.0;
  }
  else if(position > 1.0)
  {
    position = 1.0;
  }
  
  m_audioPosition = PositionToAbsolutePosition(position);
}

size_t AudioObject::PositionToAbsolutePosition(double position)
{
  return (size_t)(position * m_audioLength);
}