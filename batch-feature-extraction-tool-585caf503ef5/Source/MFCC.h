/*
  ==============================================================================

    MFCC.h
    Created: 2 Sep 2014 3:30:50pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef MFCC_H_INCLUDED
#define MFCC_H_INCLUDED

#include<vector>

class MFCC
{
public:
	void initMFFCvariables(int NCoeffs, int Nfft, float fSampleRate);
	void ComputeMFCC(std::vector<float> magnitude, std::vector<float> &mfccs);
private:
	// -------- MFFC computation
	int     m_iNumMFCCCoefs;
	int     m_iTotalMFCCFilters;
	std::vector<int>    m_pMFCCFilterStart;
	std::vector<int>    m_pMFCCFilterLength;
	std::vector<std::vector<float>> m_ppMFCCFilters;
	std::vector<float>  m_ppMFFC_DCT;
	std::vector<float>  m_fMelFilteredFFT;
	std::vector<float>  m_pMFCC;
	std::vector<float>  m_pfTempMelFilterResult;

	void  MultiplyVector(std::vector<float> v1, std::vector<float> v2, std::vector<float> &out, int iNumSamples);

	float SumVector(std::vector<float> v);

	void  MultiplySumVector(std::vector<float> v1, std::vector<float> v2, std::vector<float> &vout, int M, int P);

};



#endif  // MFCC_H_INCLUDED
