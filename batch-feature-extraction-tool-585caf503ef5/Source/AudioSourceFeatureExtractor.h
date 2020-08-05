/*
  ==============================================================================

    AudioSourceFeatureExtractor.h
    Created: 11 Aug 2014 10:41:02am
    Author:  david.ronan

  ==============================================================================
*/

#ifndef AUDIOSOURCEFEATUREXTRACTOR_H_INCLUDED
#define AUDIOSOURCEFEATUREXTRACTOR_H_INCLUDED

#include <vector>

#include "FFT.h"
#include "MFCC.h"
#include "SpectralContrast.h"
#include "ObservationData.h"

#define MAGNITUDESIZE 512
#define FFTSIZE 1024
#define PI 3.14159265359
#include <memory>

class AudioSourceFeatureExtractor
{

public:

	AudioSourceFeatureExtractor();
	~AudioSourceFeatureExtractor();

	void Initialise ( float fSampleRate);
	std::vector<ObservationData> Process (const std::vector<float> data);
	void Finalize();

private:
	//Computes the magnitude of FFT
	void VectorDistance(std::vector<float> vIn1, int stride1, std::vector<float>, int stride2, std::vector<float> &vOut, int strideOut, size_t nElements);

	void SpectralFeatures(std::vector<float> &magnitude, std::vector<float> &previousmagnitude, size_t windowSize, float &centroid, float &spread, float &skew, float &kurtosis, float &brightness, float &rolloff95, float &rolloff85, float &spectralentropy, float &flatness, float &spectralcf, float &spectralflux);

	float EstimatePerdiodicity(std::vector<float> data);

	void EnvelopeCurve(std::vector<float> data, std::vector<float> &out, float sampleRate);

	void XCorr(std::vector<float> &output, std::vector<float> input1, std::vector<float> input2, size_t  maxLag);

	float EntropyOfEnergy(std::vector<float> data);

	float Log2(float n);

	int Sign(float x);

	std::vector<float> LinSpace(float min, float max, int n);

	std::vector<float> LogSpace(float min, float max, int n);

	//void Normalise(float* data, float* &out, size_t len);

	//void ConvolveFunction(float* &z, float *x, float *y, size_t &lenz, size_t lenx, size_t leny);

	//void DownSampler(float* data, float* &out,  size_t lenIn, size_t &lenOut, float currentSampleRate, float futureSampleRate);

	//void PDF_getResampleKrnl(std::vector<float> freqVec, float fsProc, int nfft, int nBin, std::vector<float> &outLogFreqVec, std::vector<std::vector<float>> &outKrnl);

	size_t m_iWriteIdx;
	size_t m_iFlucIdx;
	float  m_fSampleRate;
	std::unique_ptr<FFTW>  m_fft;
	std::vector<float> m_OutReal;
	std::vector<float> m_OutImag;
	MFCC   m_MFCC;
	SpectralContrast m_SpectralContrast;
	std::vector<float> m_fInputBuffer;
	std::vector<float> m_fMagnitudeSpectrum;
	std::vector<float> m_fPreviousMagnitudeSpectrum;
	std::vector<float> m_fFreqBins;
};

#endif  // AUDIOSOURCEFEATUREXTRACTOR_H_INCLUDED
