/*
  ==============================================================================

    SpectralContrast.cpp
    Created: 14 Aug 2015 12:21:29pm
    Author:  David

  ==============================================================================
*/

#include "SpectralContrast.h"
#include <algorithm>
#include <iostream>

void SpectralContrast::initSpectralContrastVariables(int frameSize, float sampleRate)
{

	int numberBands = 6; //the number of bands in the filter
	float lowFrequencyBound = 20; //the lower bound of the lowest band
	float highFrequencyBound = sampleRate / 2.0f;
	float staticDistribution = 0.15f; //the ratio of the bins to distribute equally [0, 1]
	m_neighbourRatio = 0.4f; //the ratio of the bins in the sub band used to calculate the peak and valley", "(0,1]"

	// get staticDistribution
	float partToScale = 1.0f - staticDistribution;

	float binWidth = sampleRate / frameSize;

	int lastBins = 0;
	m_startAtBin = 0;

	m_numberOfBinsInBands.clear();
	m_numberOfBinsInBands.resize(numberBands);
	lastBins = int(lowFrequencyBound / binWidth);
	m_startAtBin = lastBins;

	// Determine how many bins are in each band to start with.
	// The rest of the bands will be distributed logarithmically.
	int  totalNumberOfBins = int(highFrequencyBound / binWidth);
	highFrequencyBound = int(partToScale * totalNumberOfBins) * binWidth;
	int  staticBinsPerBand = int((1 - partToScale) * totalNumberOfBins) / numberBands;
	float ratio = highFrequencyBound / lowFrequencyBound;
	float ratioPerBand = pow(ratio, float(1.0 / numberBands));
	float currFreq = lowFrequencyBound;

	for (int i = 0; i < numberBands; ++i) 
	{
		currFreq = currFreq * ratioPerBand;
		m_numberOfBinsInBands[i] = int(currFreq / binWidth - lastBins + staticBinsPerBand);
		lastBins = int(currFreq / binWidth);
	}

}

void SpectralContrast::computeSpectralContrast(std::vector<float> spectrum, std::vector<float>& spectralContrast, std::vector<float>& valleys)
{
	std::vector<float> spectrumCopy = spectrum; // I want a copy because I'll be transforming it

	//substitute minReal for a static value that is the same in all architectures. i.e.: 1e-30
	float minFloat = std::numeric_limits<float>::min(); //numeric_limits<Real>::min();

	spectralContrast.clear();
	valleys.clear();

	int specIdx = m_startAtBin;

	for (int bandIdx = 0; bandIdx < int(m_numberOfBinsInBands.size()) && specIdx < int(spectrumCopy.size()); ++bandIdx)
	{
		// get the mean of the band
		float bandMean = 0;
		for (int i = 0; i < m_numberOfBinsInBands[bandIdx] && specIdx + i < int(spectrumCopy.size()); ++i)
		{
			bandMean += spectrumCopy[specIdx + i];
		}

		if (m_numberOfBinsInBands[bandIdx] != 0)
		{
			bandMean /= m_numberOfBinsInBands[bandIdx];
		}

		bandMean += minFloat;

		// sort the subband (ascending order)
		std::sort(spectrumCopy.begin() + specIdx, spectrumCopy.begin() + std::min(specIdx + m_numberOfBinsInBands[bandIdx], int(spectrum.size())));

		// number of bins to take the mean of
		int neighbourBins = int(m_neighbourRatio * m_numberOfBinsInBands[bandIdx]);
		if (neighbourBins < 1)
		{		
			neighbourBins = 1;
		}

		// valley (FLT_MIN prevents log(0))
		float sum = 0;
		for (int i = 0; i < neighbourBins && specIdx + i < int(spectrumCopy.size()); ++i) 
		{
			sum += spectrumCopy[specIdx + i];
		}

		float valley = (sum / neighbourBins) + minFloat;

		// peak
		sum = 0;
		for (int i = m_numberOfBinsInBands[bandIdx]; i > m_numberOfBinsInBands[bandIdx] - neighbourBins && specIdx + i - 1 < int(spectrumCopy.size()) && i > 0; --i)
		{
			sum += spectrumCopy[specIdx + i - 1];
		}
		

		float peak = (sum / neighbourBins) + minFloat;

		float ans = (log10(peak / valley)) / (log10(bandMean) + minFloat) ;

		spectralContrast.push_back(ans);
		valleys.push_back(log10(valley));

		specIdx += m_numberOfBinsInBands[bandIdx];
	}

}