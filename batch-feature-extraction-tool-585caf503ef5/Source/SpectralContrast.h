/*
  ==============================================================================

    SpectralContrast.h
    Created: 14 Aug 2015 12:21:29pm
    Author:  David

  ==============================================================================
*/

#ifndef SPECTRALCONTRAST_H_INCLUDED
#define SPECTRALCONTRAST_H_INCLUDED

#include <vector>

class SpectralContrast
{
public:
	void initSpectralContrastVariables(int frameSize, float sampleRate);
	void computeSpectralContrast(std::vector<float> spectrum, std::vector<float> &spectralContrast, std::vector<float> &valleys);
private:
	std::vector<int> m_numberOfBinsInBands;
	int m_startAtBin;
	float m_neighbourRatio;
};



#endif  // SPECTRALCONTRAST_H_INCLUDED
