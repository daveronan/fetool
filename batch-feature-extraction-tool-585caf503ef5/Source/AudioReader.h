/*
  ==============================================================================

    AudioReader.h
    Created: 27 Aug 2014 3:17:10pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef AUDIOREADER_H_INCLUDED
#define AUDIOREADER_H_INCLUDED

#include <string>
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileData.h"
#include "AudioSourceFeatureExtractor.h"
#include "FeatureData.h"

using namespace std;

class AudioReader
{
public:
	AudioReader();
	~AudioReader();
	std::vector<FeatureData> Read(AudioFileData audioFileData, float poolTimeSecs, int analysisWindowSize);

private:

	AudioSourceFeatureExtractor m_AudioSourceFeatureExtractor;
};

#endif  // AUDIOREADER_H_INCLUDED
