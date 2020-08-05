/*
==============================================================================

MFCC.cpp
Created: 2 Sep 2014 3:30:50pm
Author:  david.ronan

==============================================================================
*/

#include "MFCC.h"
#include <math.h>

//-----------------------------------------------------------------------------  ComputeMFCC
void MFCC::ComputeMFCC(std::vector<float> magnitude, std::vector<float> &mfccs)
{
	//Apply the Mel Filters to the spectrum magnitude:
	for (int i = 0; i < m_iTotalMFCCFilters; i++)
	{
		//Multiply spectrum with spectral mask
		MultiplyVector(magnitude, m_ppMFCCFilters[i], m_pfTempMelFilterResult, m_pMFCCFilterLength[i]);

		//Sum the values of each bins
		m_fMelFilteredFFT[i] = SumVector(m_pfTempMelFilterResult);

		//Log compression
		float filterOut = log10(m_fMelFilteredFFT[i] * 10.f + 1.f);
		m_fMelFilteredFFT[i] = filterOut;
	}

	for (int j = 0; j < m_iNumMFCCCoefs; j++)
	{
		//Cosine Transform to reduce dimensionality:
		MultiplySumVector(m_ppMFFC_DCT, m_fMelFilteredFFT, m_pMFCC, m_iNumMFCCCoefs, m_iTotalMFCCFilters);
		mfccs.push_back(m_pMFCC[j]);
	}

}


//-----------------------------------------------------------------------------  initMFFCvariables
void MFCC::initMFFCvariables(int NCoeffs, int Nfft, float fSampleRate)
{
	m_iNumMFCCCoefs = NCoeffs;

	m_pMFCC = std::vector<float>(m_iNumMFCCCoefs, 0);


	//Add a value to take into account the 0 coefficient
	int iStartMfccCoeff = 1;

	//Mel FilterBank parameters
	float fLowestFreq = 133.3333f;
	int   iNumLinearFilter = 13;
	float fLinearSpacing = 66.66666666f;
	int   iNumLogFilters = 27;
	float fLogSpacing = 1.0711703f;
	float fFreqPerBin = fSampleRate / static_cast<float>(Nfft);
	m_iTotalMFCCFilters = iNumLinearFilter + iNumLogFilters;

	m_fMelFilteredFFT = std::vector<float>(m_iTotalMFCCFilters, 0);
	m_pMFCCFilterStart = std::vector<int>(m_iTotalMFCCFilters, 0);
	m_pMFCCFilterLength = std::vector<int>(m_iTotalMFCCFilters, 0);
	m_ppMFCCFilters = std::vector<std::vector<float>>(m_iTotalMFCCFilters);

	float FilterLimits[3];
	int iFilterWidthMax = 0;
	for (int i = 0; i < m_iTotalMFCCFilters; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i + j < iNumLinearFilter)
			{
				FilterLimits[j] = (i + j) * fLinearSpacing + fLowestFreq;
			}
			else
			{
				float fLowestLogFreq = (iNumLinearFilter - 1) * fLinearSpacing + fLowestFreq;
				FilterLimits[j] = fLowestLogFreq * powf(fLogSpacing, static_cast<float>((i + j) - iNumLinearFilter + 1));
			}
		}

		float fTriangleHeight = 2.f / (FilterLimits[2] - FilterLimits[0]);

		int iStartBin = static_cast<int>(ceil(FilterLimits[0] / fFreqPerBin));
		int iStopBin = static_cast<int>(floor(FilterLimits[2] / fFreqPerBin));

		int iFilterWidth = iStopBin - iStartBin + 1;
		m_pMFCCFilterStart[i] = iStartBin;
		m_pMFCCFilterLength[i] = iFilterWidth;
		m_ppMFCCFilters[i] = std::vector<float>(iFilterWidth, 0);

		if (iFilterWidth > iFilterWidthMax)
		{
			iFilterWidthMax = iFilterWidth;
		}

		for (int n = iStartBin; n<iStopBin + 1; n++)
		{
			float fFreq = n * fFreqPerBin;
			if (fFreq <= FilterLimits[1])
			{
				float factor = (fFreq - FilterLimits[0]) / (FilterLimits[1] - FilterLimits[0]);
				float filterVal = fTriangleHeight * factor;
				m_ppMFCCFilters[i][n - iStartBin] = filterVal;
			}
			else
			{
				float factor = (FilterLimits[2] - fFreq) / (FilterLimits[2] - FilterLimits[1]);
				float filterVal = fTriangleHeight * factor;
				m_ppMFCCFilters[i][n - iStartBin] = filterVal;
			}
		}
	}

	m_pfTempMelFilterResult = std::vector<float>(iFilterWidthMax, 0);

	//Compute the DCT reduction matrix
	m_ppMFFC_DCT = std::vector<float>(NCoeffs * m_iTotalMFCCFilters, 0);

	float fScaleDCTMatrix = 1.f / sqrtf(m_iTotalMFCCFilters / 2.f);

	for (int n = iStartMfccCoeff; n < NCoeffs + iStartMfccCoeff; n++)
	{
		for (int m = 0; m < m_iTotalMFCCFilters; m++)
		{
			m_ppMFFC_DCT[(n - iStartMfccCoeff) * m_iTotalMFCCFilters + m] = fScaleDCTMatrix * cosf(n * (m + 0.5f) * 3.141592653589793f / m_iTotalMFCCFilters);
		}
	}
}

//-----------------------------------------------------------------------------  MultiplyVector
void MFCC::MultiplyVector(std::vector<float> v1, std::vector<float> v2, std::vector<float> &out, int iNumSamples)
{

	for (int i = 0; i < iNumSamples; i++)
	{
		out[i] = v1[i] * v2[i];
	}
}

//-----------------------------------------------------------------------------  SumVector
float MFCC::SumVector(std::vector<float> v)
{
	float fSum = 0;

	for (size_t i = 0; i < v.size(); i++)
	{
		fSum += v[i];
	}

	return fSum;
}

//-----------------------------------------------------------------------------  MultiplySumVector
void MFCC::MultiplySumVector(std::vector<float> v1, std::vector<float> v2, std::vector<float> &vout, int M, int P)
{
	for (int m = 0; m < M; m++)
	{
		float fProdSum = 0.f;

		for (int p = 0; p < P; p++)
		{
			fProdSum += v1[m * P + p] * v2[p];
		}

		vout[m] = fProdSum;
	}
}
