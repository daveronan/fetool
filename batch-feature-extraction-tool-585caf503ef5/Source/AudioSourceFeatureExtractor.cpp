/*
  ==============================================================================

    AudioSourceFeatureExtractor.cpp
    Created: 11 Aug 2014 10:41:02am
    Author:  david.ronan

  ==============================================================================
*/

#include "AudioSourceFeatureExtractor.h"
#include "ObservationData.h"
#include <math.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <memory>

//#include <windows.h>

//==============================================================================  AudioSourceFeatureExtractor
AudioSourceFeatureExtractor::AudioSourceFeatureExtractor() 
{
	m_fft = std::make_unique<FFTW>(FFTSIZE);
	m_fInputBuffer = std::vector<float>(FFTSIZE, 0);;
	m_fMagnitudeSpectrum = std::vector<float>(MAGNITUDESIZE, 0);
	m_fPreviousMagnitudeSpectrum = std::vector<float>(MAGNITUDESIZE, 0);
	m_OutReal = std::vector<float>(FFTSIZE, 0);
	m_OutImag = std::vector<float>(FFTSIZE, 0);
}

//============================================================================== ~AudioSourceFeatureExtractor
AudioSourceFeatureExtractor::~AudioSourceFeatureExtractor()
{

}

//==============================================================================  init
void AudioSourceFeatureExtractor::Initialise(float fSampleRate)
{
	m_fSampleRate = fSampleRate;
	m_iWriteIdx = 0;

	for (int i = 1; i <= MAGNITUDESIZE; i++)
	{
		float win = ((fSampleRate / (2 * MAGNITUDESIZE)) * i);
		m_fFreqBins.push_back(win);
	}

	m_MFCC.initMFFCvariables(12, MAGNITUDESIZE, m_fSampleRate);
	m_SpectralContrast.initSpectralContrastVariables(FFTSIZE, m_fSampleRate);
}

//==============================================================================  process
std::vector<ObservationData> AudioSourceFeatureExtractor::Process(const std::vector<float> data)
{
	std::vector<ObservationData> observations = std::vector<ObservationData>();

	m_fInputBuffer = std::vector<float>(FFTSIZE, 0);;
	m_fMagnitudeSpectrum = std::vector<float>(MAGNITUDESIZE, 0);
	m_fPreviousMagnitudeSpectrum = std::vector<float>(MAGNITUDESIZE, 0);
	m_iWriteIdx = 0;

	float perdiodicity = EstimatePerdiodicity(data);

	float entropyofenergy = EntropyOfEnergy(data);

	for (size_t n = 0; n < data.size(); n++)
	{
		m_fInputBuffer[m_iWriteIdx] = data[n];
		m_iWriteIdx++;

		//Do normal FFT

		if (FFTSIZE == m_iWriteIdx)
		{
			//Get the peak amplitude rms and crest factor for the current frame
			float peakvalue = 0;
			float rms = 0;
			float crestfactor;

			for (int i = 0; i < FFTSIZE; i++)
			{
				if (m_fInputBuffer[i] > peakvalue)
					peakvalue = abs(m_fInputBuffer[i]);

				rms += (m_fInputBuffer[i] * m_fInputBuffer[i]);
			}

			rms /= FFTSIZE;
			rms = sqrt(rms);

			crestfactor = peakvalue / (rms + std::numeric_limits<float>::epsilon());

			float ZCR = 0;
			float inputBuffer2[FFTSIZE] = {0.0};

			for (int i = 1; i < FFTSIZE; i++)
			{
				inputBuffer2[i] = m_fInputBuffer[i - 1];
			}

			for (int i = 0; i < FFTSIZE; i++)
			{
				ZCR += (abs(Sign(m_fInputBuffer[i]) - Sign(inputBuffer2[i])));
			}

			ZCR /= (2 * FFTSIZE);

			//////////////////////////////////////////////////////////////////
			for (int i = 0; i < FFTSIZE; i++)
			{
				float multiplier = static_cast<float>(0.5 * (1 - cos(2 * PI * i / (FFTSIZE - 1))));
				m_fInputBuffer[i] = multiplier * m_fInputBuffer[i];
			}

			//Compute the FFT
			m_OutReal = std::vector<float>(FFTSIZE, 0);
			m_OutImag = std::vector<float>(FFTSIZE, 0);
			

			m_fft->process(m_fInputBuffer, m_OutReal, m_OutImag);

			//Compute the Magnitude
			VectorDistance(m_OutReal, 1, m_OutImag, 1, m_fMagnitudeSpectrum, 1, MAGNITUDESIZE);

			//Compute the spectral features
			float centroid = 0;
			float spread = 0;
			float skewness = 0;
			float kurtosis = 0;
			float brightness = 0;
			float rolloff85 = 0;
			float rolloff95 = 0;
			float spectralentropy = 0;
			float flatness = 0;
			float spectralcf = 0;
			float spectralflux = 0;
			std::vector<float> mfccs;
			std::vector<float> spectralContrast;
			std::vector<float> spectralValleys;

			SpectralFeatures(m_fMagnitudeSpectrum, m_fPreviousMagnitudeSpectrum, MAGNITUDESIZE, centroid, spread, skewness, kurtosis, brightness, rolloff85, rolloff95, spectralentropy, flatness, spectralcf, spectralflux);

			m_MFCC.ComputeMFCC(m_fMagnitudeSpectrum, mfccs);

			m_SpectralContrast.computeSpectralContrast(m_fMagnitudeSpectrum, spectralContrast, spectralValleys);

			//Update for Spectral Flux
			for (int i = 0; i < MAGNITUDESIZE; i++)
			{
				m_fPreviousMagnitudeSpectrum[i] = m_fMagnitudeSpectrum[i];
			}

			//50% Hop size
			for (int i = MAGNITUDESIZE; i < FFTSIZE; i++)
			{
				m_fInputBuffer[i - MAGNITUDESIZE] = m_fInputBuffer[i];
				m_iWriteIdx = MAGNITUDESIZE;
			}

			//create an observation for this window and push it to the list of observations for this 30 sec. audio clip
			ObservationData newObservation = ObservationData(rms, peakvalue, crestfactor, ZCR, centroid, spread, skewness, kurtosis, brightness, rolloff85, rolloff95, spectralentropy, flatness, spectralcf, spectralflux, mfccs, spectralContrast, spectralValleys, perdiodicity, entropyofenergy);
			observations.push_back(newObservation);
		}
	}

	return observations;
}

void AudioSourceFeatureExtractor::Finalize()
{
}

void AudioSourceFeatureExtractor::VectorDistance(std::vector<float> vIn1, int stride1, std::vector<float> vIn2, int stride2, std::vector<float> &vOut, int strideOut, size_t nElements)
{
	//Compute remaining samples
	for (size_t i = 0; i < nElements; i++)
	{
		vOut[i * strideOut] = sqrt(vIn1[i * stride1] * vIn1[i * stride1] + vIn2[i * stride2] * vIn2[i * stride2]);
	}
}

void AudioSourceFeatureExtractor::SpectralFeatures(std::vector<float> &magnitude, std::vector<float> &prevmagnitude, size_t windowSize, float& centroid, float& spread, float& skew, float& kurtosis, float& brightness, float& rolloff95, float& rolloff85, float& spectralentropy, float& flatness, float& spectralcf, float& spectralflux)
{
	float summagbin = 0;
	float summag = 0;
	float sumprevmag = 0;
	float summagspread = 0;
	float summagskewness = 0;
	float summagkurtosis = 0;
	float sumbrightness = 0;
	float maxmag = 0;

	float geo = 1;
	float totalenergy = 0;
	float currEnergy95 = 0;
	float currEnergy85 = 0;
	int countFFT85 = 0;
	int countFFT95 = 0;

	float normalisedMagSumEntropy = 0;

	//Centroid
	//////////////////////////////////////////////////////

	for (size_t i = 0; i < windowSize; i++)
	{
		//Moments
		summagbin += (m_fFreqBins[i] * magnitude[i]);
		summag += magnitude[i];
		sumprevmag += prevmagnitude[i];

		//Spectral Crest factor
		if (magnitude[i] > maxmag)
		{
			maxmag = magnitude[i];
		}

		float energy = magnitude[i] * magnitude[i];

		//Roll off + Flatness

		totalenergy += energy;
		float exponent = static_cast<float>(1.0 / static_cast<float>(windowSize));

		if (energy != 0)
		{
			geo *= pow(energy, exponent);
		}
	}

	summag += std::numeric_limits<float>::epsilon();

	centroid = summagbin / summag;

	/////////////////////////////////////////////////////////

	//Spread
	//////////////////////////////////////////////////////

	for (size_t i = 0; i < windowSize; i++)
	{
		float norm = magnitude[i] / (summag + std::numeric_limits<float>::epsilon());
		float normprev = prevmagnitude[i] / (sumprevmag + std::numeric_limits<float>::epsilon());

		//Spectral Flux
		spectralflux += ((norm - normprev) * (norm - normprev));

		//Entropy
		normalisedMagSumEntropy += (norm * log(norm + std::numeric_limits<float>::epsilon()));

		//Moments
		summagspread += pow((m_fFreqBins[i] - centroid), 2) * norm;
		summagskewness += pow((m_fFreqBins[i] - centroid), 3) * norm;
		summagkurtosis += pow((m_fFreqBins[i] - centroid), 4) * norm;

		//Brightness
		if (m_fFreqBins[i] >= 1500)
		{
			sumbrightness += magnitude[i];
		}
	}

	spread = sqrt(summagspread);

	/////////////////////////////////////////////////////////

	//Skewness
	//////////////////////////////////////////////////////

	float spreadtemp = spread;
	spreadtemp += std::numeric_limits<float>::epsilon();

	skew = summagskewness / pow(spreadtemp, 3);

	/////////////////////////////////////////////////////////

	//Kurtosis
	//////////////////////////////////////////////////////

	kurtosis = summagkurtosis / pow(spreadtemp, 4);

	/////////////////////////////////////////////////////////

	//Brightness
	//////////////////////////////////////////////////////

	brightness = sumbrightness / summag;

	/////////////////////////////////////////////////////////

	//Roll off 85% - 95%
	/////////////////////////////////////////////////////////

	while ((currEnergy95 <= 0.95 * totalenergy) && (countFFT95 < static_cast<int>(windowSize)))
	{
		currEnergy95 += (magnitude[countFFT95] * magnitude[countFFT95]);
		countFFT95 += 1;

		if (currEnergy85 <= 0.85 * totalenergy)
		{
			currEnergy85 += (magnitude[countFFT85] * magnitude[countFFT85]);
			countFFT85 += 1;
		}
	}

	countFFT85 -= 1;
	countFFT95 -= 1;

	//Normalization
	if (currEnergy85 <= 0)
	{
		//If we have silence then our value should be 0.
		rolloff85 = 0;
	}
	else
	{
		rolloff85 = (static_cast<float>(countFFT85) / static_cast<float>(windowSize));
	}

	//Normalization
	if (currEnergy95 <= 0)
	{
		//If we have silence then our value should be 0.
		rolloff95 = 0;
	}
	else
	{
		rolloff95 = (static_cast<float>(countFFT95) / static_cast<float>(windowSize));
	}

	/////////////////////////////////////////////////////

	//Spectral Entropy
	/////////////////////////////////////////////////////////

	spectralentropy = static_cast<float>((normalisedMagSumEntropy / log(static_cast<float>(windowSize))) * - 1);

	/////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////

	//Flatness
	/////////////////////////////////////////////////////////
	if (totalenergy != 0 && geo != 0)
	{
		flatness = geo / (totalenergy / static_cast<float>(windowSize));
	}
	else
	{
		flatness = 0;
	}

	/////////////////////////////////////////////////////////

	//Spectral Crest Factor
	/////////////////////////////////////////////////////////

	if (summag != 0)
	{
		spectralcf = maxmag / summag;
	}
	else
	{
		spectralcf = 0;
	}
}

void AudioSourceFeatureExtractor::XCorr(std::vector<float>& output, std::vector<float> input1, std::vector<float> input2, size_t maxLag = 0)
{
	// TODO: adapt for different sizes

	// find next power of 2 for efficient FFT
	size_t fftSize = 1;
	while (fftSize < 2 * static_cast<size_t>(input1.size()) - 1)
	{
		fftSize *= 2;
	}

	FFTW fft1 = FFTW(fftSize);
	FFTW fft2 = FFTW(fftSize);

	// allocate space for FFTW processing
	std::vector<float> in1 = std::vector<float>(fftSize, 0);;
	std::vector<float> in2 = std::vector<float>(fftSize, 0);;

	// output from FFT is only up to Nyquist frequency
	std::vector<float> out1Real = std::vector<float>(fftSize, 0);
	std::vector<float> out1Imag = std::vector<float>(fftSize, 0);
	std::vector<float> out2Real = std::vector<float>(fftSize, 0);
	std::vector<float> out2Imag = std::vector<float>(fftSize, 0);

	// copy input to allocated arrays
	for (size_t i = 0; i < static_cast<size_t>(input1.size()); ++i)
	{
		in1[i] = input1[i];
		in2[i] = input2[i];
	}

	fft1.process(in1, out1Real, out1Imag);
	fft2.process(in2, out2Real, out2Imag);

	// multiply out1*conj(out2) in FFT domain
	fftwf_complex* product = static_cast<fftwf_complex*>(fftwf_malloc(sizeof(fftwf_complex) * fftSize));
	for (size_t i = 0; i < fftSize; ++i)
	{
		product[i][0] = (out1Real[i] * out2Real[i] + out1Imag[i] * out2Imag[i]);
		product[i][1] = (out1Imag[i] * out2Real[i] - out1Real[i] * out2Imag[i]);
	}

	// compute IFFT

	// do FFT, adapted from iTraktorLib "FFTW.h"
	fftw_iodim dim;
	dim.n = fftSize;
	dim.is = 1;
	dim.os = 1;

	fftwf_plan plan;

	float* result = static_cast<float*>(fftwf_malloc(sizeof(float) * fftSize));
	plan = fftwf_plan_guru_dft_c2r(1, &dim, 0, nullptr, product, result, FFTW_ESTIMATE);
	fftwf_execute_dft_c2r(plan, product, result);
	fftwf_destroy_plan(plan);

	// copy real part of result back to output array, normalize by FFT size
	if (maxLag == 0 || maxLag >= static_cast<size_t>(input1.size()))
	{
		maxLag = static_cast<size_t>(input1.size()) - 1;
	}

	output = std::vector<float>(2 * maxLag + 1, 0);

	for (size_t i = fftSize - maxLag; i < fftSize; ++i)
	{
		output[i - fftSize + maxLag] = result[i] / fftSize;
	}

	for (unsigned i = 0; i <= static_cast<unsigned>(maxLag); ++i)
	{
		output[i + maxLag] = result[i] / fftSize;
	}

	fftwf_free(result);
	fftwf_free(product);
}

float AudioSourceFeatureExtractor::EstimatePerdiodicity(std::vector<float> data)
{
	float periodicity;

	std::vector<float> downsampleddata = std::vector<float>(data.size(), 0);

	std::vector<float> xcorr;

	for (size_t k = 0; k < data.size(); k++)
	{
		downsampleddata[k] = data[k];
	}
	
	EnvelopeCurve(downsampleddata, downsampleddata, m_fSampleRate);

	int startLag = static_cast<int>(floor(static_cast<float>(60.0 / 480.0 * m_fSampleRate)));
	int endLag = static_cast<int>(floor(static_cast<float>(60.0 / 30.0 * m_fSampleRate)));
	int thresh = static_cast<int>(floor(static_cast<float>(0.2 * m_fSampleRate)));

	
	XCorr(xcorr, downsampleddata, downsampleddata, endLag);
	size_t xcorrlen = xcorr.size();

	int i = static_cast<int>(floor(xcorrlen / 2));

	std::vector<float> temp;
	for (size_t j = i; j < xcorrlen; j++)
	{
		temp.push_back(xcorr[j]);
	}

	std::vector<float> temp2;
	for (size_t j = static_cast<size_t>(std::max(1, startLag)); j < static_cast<size_t>(std::min(endLag, static_cast<int>(temp.size()))); j++)
	{
		temp2.push_back(temp[j]);
	}

	int maxIdx = 0;
	float maxVal = std::numeric_limits<float>::lowest();
	for (size_t j = 0; j < temp2.size(); j++)
	{
		if (temp2[j] > maxVal)
		{
			maxIdx = j;
			maxVal = temp2[j];
		}
	}

	int from = std::max(1, maxIdx - thresh);
	int to = std::min(static_cast<int>(temp2.size()), maxIdx + thresh);

	float minValInRange = std::numeric_limits<float>::max();

	for (size_t j = static_cast<size_t>(from); j < static_cast<size_t>(to); j++)
	{
		if (temp2[j] < minValInRange)
		{
			minValInRange = temp2[j];
		}
	}

	periodicity = (maxVal - minValInRange);

	//std::string dave = "Periodicity " + std::to_string(periodicity) + "\n";
	//OutputDebugString(dave.c_str());

	return periodicity;
}

void AudioSourceFeatureExtractor::EnvelopeCurve(std::vector<float> data, std::vector<float> & out, float sampleRate)
{
	float release = 0.02f;
	float envelope = 0.0f;

	float gr = exp(-1 / (sampleRate * release));

	for (size_t i = 0; i < data.size(); i++)
	{
		float EnvIn = abs(data[i]);

		if (envelope < EnvIn)
		{
			envelope = EnvIn;
		}
		else
		{
			envelope = envelope * gr;
			envelope = envelope + (1 - gr) * EnvIn;
		}

		out[i] = envelope;
	}
}

float AudioSourceFeatureExtractor::EntropyOfEnergy(std::vector<float> data)
{
	float totalEnergy = 0.0;
	float totalentropy = 0.0;
	const int numSubFrames = 30;

	//Calculate Total Energy and normalise it
	for (size_t i = 0; i < data.size(); i++)
	{
		totalEnergy += (data[i] * data[i]);
	}

	int subFrameSize = data.size() / numSubFrames;

	for (size_t i = 0; i < numSubFrames; i++)
	{
		float val = 0.0;

		for (size_t j = 0; j < static_cast<size_t>(subFrameSize); j++)
		{
			val += (data[j + (i * subFrameSize)] * data[j + (i * subFrameSize)]);
		}

		float frameval = val / (totalEnergy + std::numeric_limits<float>::epsilon());

		totalentropy += (frameval * Log2(frameval + std::numeric_limits<float>::epsilon()));
	}

	return (totalentropy * -1);
}

float AudioSourceFeatureExtractor::Log2(float n)
{
	// log(n)/log(2) is log2.
	return logf(n) / logf(2);
}

int AudioSourceFeatureExtractor::Sign(float x)
{
	int retValue = 0;
	if (x >= 0)
		retValue = 1;
	if (x < 0)
		retValue = -1;

	return retValue;
}

std::vector<float> AudioSourceFeatureExtractor::LinSpace(float min, float max, int n)
{
	std::vector<float> result;
	// vector iterator
	int iterator = 0;

	for (int i = 0; i <= n - 2; i++)
	{
		float temp = min + i * (max - min) / (floor(static_cast<float>(n)) - 1);
		result.insert(result.begin() + iterator, temp);
		iterator += 1;
	}

	result.insert(result.begin() + iterator, max);
	return result;
}

std::vector<float> AudioSourceFeatureExtractor::LogSpace(float min, float max, int n)
{
	float logMin = log(min);
	float logMax = log(max);
	double delta = (logMax - logMin) / n;
	double accDelta = 0;
	std::vector<float> v;

	for (int i = 0; i <= n; i++)
	{
		v.push_back(static_cast<float>(exp(logMin + accDelta)));
		accDelta += delta;// accDelta = delta * i
	}

	return v;
}

//void AudioSourceFeatureExtractor::ConvolveFunction(float* & z, float* x, float* y, size_t& lenz, size_t lenx, size_t leny)
//{
//	// computes cross-correlation of two vectors, takes 2 vectors of the same length and computes 2*length-1 lags
//
//	//float *zptr, s, *xp, *yp;
//	//size_t n_lo, n_hi;
//
//	//lenz = lenx + leny - 1;
//
//	//z = new float[lenz];
//
//	//zptr = z;
//
//	//for (size_t i = 0; i < lenz; i++)
//	//{
//	//	s = 0.0;
//	//	n_lo = 0 > (i - leny + 1) ? 0 : (i - leny + 1);
//	//	n_hi = (lenx - 1) < i ? (lenx - 1) : i;
//	//	xp = &x[0] + n_lo;
//	//	yp = &y[0] + i - n_lo;
//
//	//	for (size_t n = n_lo; n <= n_hi; n++)
//	//	{
//	//		s += *xp * *yp;
//	//		xp++;
//	//		yp--;
//	//	}
//
//	//	*zptr = s;
//	//	zptr++;
//	//}
//}

//void AudioSourceFeatureExtractor::DownSampler(float* data, float* & out, size_t lenIn, size_t& lenOut, float currentSampleRate, float futureSampleRate)
//{
//	////Low pass our data before we decimate
//	//const int filterlength = 101;
//	//float* tempdata = new float[lenIn];
//	//memset(tempdata, 0, sizeof(float)*lenIn);
//
//	////Coefficients were taken from Matlab
//	//float coeffs[filterlength] ={2.0839274e-05f, 6.6880953e-06f,-4.7252855e-05f,	-3.4874138e-05f,	7.8508412e-05f,9.7089069e-05f,-9.9197161e-05f,	-0.00020412984f,	8.2261082e-05f,	0.00035689832f,	9.4890293e-06f,	-0.00053820928f,	-0.00021722882f,	0.00070567406f,	0.00057491515f,	-0.00078844035f, -0.0010939316f,	0.00069057313f,	0.0017460365f,	-0.00030308162f,	-0.0024484061f,	-0.00047496572f,	0.0030552838f,	0.0017078921f, 	-0.0033604759f, 	-0.0033912712f, 	0.0031135236f, 	0.0054217125f, 	-0.0020499325f, 	-0.0075746416f, 	-6.7239242e-05f, 0.0094950572f, 0.0034002098f,	-0.010703080f, 	-0.0079918290f, 	0.010610434f, 0.013732497f, 	-0.0085344436f, 	-0.020346783f, 0.0036776769f,	0.027405130f,	0.0050050775f,	-0.034361813f,	-0.019287759f,	0.040615436f,	0.043452863f,-0.045583628f,	-0.093336113f,	0.048780452f,	0.31394306f,	0.45011634f,	0.31394306f,	0.048780452f,-0.093336113f,-0.045583628f,	0.043452863f,0.040615436f,-0.019287759f,	-0.034361813f,	0.0050050775f,	0.027405130f,0.0036776769f,-0.020346783f,	-0.0085344436f,	0.013732497f,	0.010610434f,	-0.0079918290f,	-0.010703080f,	0.0034002098f,	0.0094950572f,	-6.7239242e-05f,	-0.0075746416f,	-0.0020499325f,	0.0054217125f,	0.0031135236f,	-0.0033912712f,	-0.0033604759f,	0.0017078921f,	0.0030552838f,	-0.00047496572f,	-0.0024484061f,	-0.00030308162f,	0.0017460365f,0.00069057313f,	-0.0010939316f,	-0.00078844035f,	0.00057491515f,	0.00070567406f,	-0.00021722882f,	-0.00053820928f,	9.4890293e-06f,	0.00035689832f,	8.2261082e-05f,	-0.00020412984f,	-9.9197161e-05f,	9.7089069e-05f,	7.8508412e-05f,	-3.4874138e-05f,	-4.7252855e-05f,	6.6880953e-06f,	2.0839274e-05f};
//	//
//	//float acc;     // accumulator for MACs
//	//   float* coeffp; // pointer to coefficients
//	//   float* inputp; // pointer to input samples
//	//float* endp = &data[lenIn -1]; // pointer to last sample
//	//
//	//
//	//   // apply the filter to each input sample
//	//   for (size_t n = 0; n < lenIn; n++ )
//	//{
//	//       // calculate output n
//	//       coeffp = &coeffs[0];
//	//       inputp = &data[filterlength - 1 + n];
//
//	//	acc = 0.0f;
//	//	for (int k = 0; k < filterlength; k++ )
//	//	{
//	//		if(inputp <= endp)
//	//			acc += (*coeffp++) * (*inputp--);
//	//		else
//	//		{
//	//			//When we reach the end of the buffer
//	//			acc += (*coeffp++) * 0.0f;
//	//			*inputp--;
//	//		}
//	//	}
//
//	//	tempdata[n] = acc;
//	//   }
//	//int ratio = (int) (currentSampleRate / futureSampleRate);
//	//
//	//lenOut = lenIn / ratio;
//
//	//out = new float[lenOut];
//	//memset(out, 0, sizeof(float)*lenOut);
//
//
//	//int idx = 0;
//	//for(size_t i = 0; i < lenIn; i = i + ratio)
//	//{
//	//	out[idx] = tempdata[i];
//	//	idx++;
//	//}
//
//	//if(tempdata != NULL)
//	//{
//	//	delete[] tempdata;
//	//	tempdata = nullptr;
//	//}
//}

//void AudioSourceFeatureExtractor::Normalise(float* data, float* & out, size_t len)
//{
//	//float maxvalue = std::numeric_limits<float>::lowest();
//
//	//for (size_t i = 0; i < len; i++)
//	//{
//	//	if (data[i] > maxvalue)
//	//		maxvalue = data[i];
//	//}
//
//	//for (size_t i = 0; i < len; i++)
//	//{
//	//	out[i] = data[i] / maxvalue;
//	//}
//}

//void AudioSourceFeatureExtractor::PDF_getResampleKrnl(std::vector<float> freqVec, float fsProc, int nfft, int nBin, std::vector<float>& outLogFreqVec, std::vector<std::vector<float>>& outKrnl)
//{
//	//float f1 = freqVec[0];
//	//float f2 = freqVec[freqVec.size() - 1];
//
//	//outLogFreqVec = LinSpace(log(f1), log(f2), nBin);
//	//std::vector<float> f(nfft / 2, 0.0f);
//
//	//for (size_t i = 0; i < static_cast<size_t>(nBin); i++)
//	//{
//	//	outKrnl.push_back(f);
//	//}
//
//	//for (size_t i = 0; i < outLogFreqVec.size(); i++)
//	//{
//	//	outLogFreqVec[i] = exp(outLogFreqVec[i]);
//	//}
//
//	//for (size_t i = 1; i < static_cast<size_t>(nBin) - 2; i++)
//	//{
//	//	float freqBinLin = outLogFreqVec[i] / (fsProc / nfft);
//
//	//	float nextBinUp = outLogFreqVec[i + 1] / (fsProc / nfft);
//
//	//	float nextBinDown = outLogFreqVec[i - 1] / (fsProc / nfft);
//
//	//	float filtWid = nextBinUp - nextBinDown;
//
//	//	if (filtWid <= 2)
//	//	{
//	//		// log resolution is finer than linear resolution
//	//		// linear interpolation  of neighboring bins
//
//	//		float binDown = floor(freqBinLin);
//	//		float frac = freqBinLin - binDown;
//	//		std::vector<float> filt(nfft / 2, 0.0f);
//	//		filt[((int)binDown) - 1] = 1 - frac;
//	//		filt[((int)binDown + 1) - 1] = frac;
//	//		outKrnl[i][((int)binDown) - 1] = filt[((int)binDown) - 1];
//	//		outKrnl[i][((int)binDown + 1) - 1] = filt[((int)binDown + 1) - 1];
//	//	}
//	//	else
//	//	{
//	//		float ceilNextBinDown = ceil(nextBinDown);
//	//		float floorFreqBinLin = floor(freqBinLin);
//	//		float ceilFreqBinLin = ceil(freqBinLin);
//	//		float floorNextBinUp = floor(nextBinUp);
//
//	//		std::vector<int> idxLow;
//	//		std::vector<int> idxHigh;
//	//		std::vector<int> filtIdx;
//
//	//		for (size_t j = (size_t)ceilNextBinDown; j <= (size_t)floorFreqBinLin; j++)
//	//		{
//	//			idxLow.push_back(j);
//	//		}
//
//	//		for (size_t j = (size_t)ceilFreqBinLin; j <= (size_t)floorNextBinUp; j++)
//	//		{
//	//			idxHigh.push_back(j);
//	//		}
//
//	//		std::vector<int>::iterator it;
//	//		it = std::unique(idxLow.begin(), idxLow.end());
//	//		idxLow.resize(std::distance(idxLow.begin(), it));
//
//	//		it = std::unique(idxHigh.begin(), idxHigh.end());
//	//		idxHigh.resize(std::distance(idxHigh.begin(), it));
//
//	//		filtIdx.reserve(idxLow.size() + idxHigh.size()); // preallocate memory
//	//		filtIdx.insert(filtIdx.end(), idxLow.begin(), idxLow.end());
//	//		filtIdx.insert(filtIdx.end(), idxHigh.begin(), idxHigh.end());
//
//	//		std::vector<float> rampUp;
//	//		std::vector<float> rampDown;
//	//		for (size_t j = 0; j < filtIdx.size(); j++)
//	//		{
//	//			rampUp.push_back(1 - (freqBinLin - filtIdx[j]) / (freqBinLin - nextBinDown));
//	//			rampDown.push_back(1 - (filtIdx[j] - freqBinLin) / (nextBinUp - freqBinLin));
//	//		}
//
//	//		std::vector<float> filt;
//
//	//		for (size_t j = 0; j < rampUp.size(); j++)
//	//		{
//	//			filt.push_back(std::min(rampUp[j], rampDown[j]));
//	//		}
//
//	//		float sumfilt = 0.0f;
//	//		for (size_t j = 0; j < filt.size(); j++)
//	//		{
//	//			sumfilt += filt[j];
//	//		}
//
//	//		for (size_t j = 0; j < filt.size(); j++)
//	//		{
//	//			filt[j] /= sumfilt;
//	//		}
//
//	//		for (size_t j = 0; j < filtIdx.size(); j++)
//	//		{
//	//			outKrnl[i][filtIdx[j] - 1] = filt[j];
//	//		}
//	//	}
//	//}
//
//	// special routine for first bin
//	// get frequency in linear bins
//
//	//float freqBinLin = outLogFreqVec[0] / (fsProc / (float)nfft);
//	//float binDown = floor(freqBinLin);
//	//float frac = freqBinLin - binDown;
//
//	//std::vector<float> filt(nfft / 2, 0.0f);
//	//filt[((int)binDown) - 1] = 1 - frac;
//	//filt[((int)binDown + 1) - 1] = frac;
//
//	//outKrnl[0][((int)binDown) - 1] = filt[((int)binDown) - 1];
//	//outKrnl[0][((int)binDown + 1) - 1] = filt[((int)binDown + 1) - 1];
//
//	//// special routine for last bin
//	//// get frequency in linear bins
//	//freqBinLin = outLogFreqVec[outLogFreqVec.size() - 1] / (fsProc / nfft);
//
//	//// get next lower bin
//	//float nextBinDown = outLogFreqVec[outLogFreqVec.size() - 2] / (fsProc / nfft);
//
//	//float ceilNextBinDown = ceil(nextBinDown); //Subtract by -1 because of array
//	//float floorFreqBinLin = floor(freqBinLin);
//
//	//std::vector<int> filtIdx;
//
//	//for (size_t i = (size_t)ceilNextBinDown; i <= (size_t)floorFreqBinLin; i++)
//	//{
//	//	filtIdx.push_back(i);
//	//}
//
//	//std::vector<float> filt2;
//	//for (size_t i = 0; i < filtIdx.size(); i++)
//	//{
//	//	filt2.push_back(1 - (freqBinLin - filtIdx[i]) / (freqBinLin - nextBinDown));
//	//}
//
//	//float sumfilt = 0.0f;
//	//for (size_t i = 0; i < filt2.size(); i++)
//	//{
//	//	sumfilt += filt2[i];
//	//}
//
//	//for (size_t i = 0; i < filt2.size(); i++)
//	//{
//	//	filt2[i] /= sumfilt;
//	//}
//
//	//for (size_t j = 0; j < filtIdx.size(); j++)
//	//{
//	//	outKrnl[outKrnl.size() - 1][filtIdx[j] - 1] = filt2[j];
//	//}
//}


