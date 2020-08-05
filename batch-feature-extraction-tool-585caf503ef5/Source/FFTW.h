/*
==============================================================================

FFTW.cpp
Created: 29 Oct 2014 6:30:26pm
Author:  david.ronan

==============================================================================
*/
#pragma once

#include "fftw3.h"
#include <vector>


class FFTW
{

public:
   fftwf_plan  m_plan;
  unsigned m_iFFTSize;

  FFTW();
  FFTW( unsigned fftLength )
  {
	m_iFFTSize = fftLength;

	std::vector<float> tempInput = std::vector<float>(fftLength, 0);
	std::vector<float> tempReal = std::vector<float>(fftLength, 0);
	std::vector<float> tempImag = std::vector<float>(fftLength, 0);


    fftwf_iodim  dim;
    dim.n =  fftLength;
    dim.is = 1;
    dim.os = 1;
    m_plan = fftwf_plan_guru_split_dft_r2c( 1, &dim, 0, nullptr, tempInput.data(), tempReal.data(), tempImag.data(), FFTW_ESTIMATE );
  }


 ~FFTW()
  {
	  if(m_plan != nullptr)
	  {
			fftwf_destroy_plan( m_plan );
	  }
  }


 void process(std::vector<float> input, std::vector<float> &realPart, std::vector<float> &imagPart)
  {
	
	fftwf_execute_split_dft_r2c( m_plan, input.data(), realPart.data(), imagPart.data());

	//Multiply results by 2 to match the iOS output
	for(size_t i = 0; i < m_iFFTSize; i++)
	{
		realPart[i] *= 2.f;
		imagPart[i] *= 2.f;
	}
  }

};

