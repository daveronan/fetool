/*
  ==============================================================================

    FFT.h
    Created: 11 Aug 2014 11:18:53am
    Author:  mickael.legoff

  ==============================================================================
*/

#ifndef FFT_H_INCLUDED
#define FFT_H_INCLUDED

#include "FFTW.h"


template < typename FFTImpl >
class FastFourierTransform
{

public:
  FastFourierTransform(){};
  FastFourierTransform( unsigned fftLength )
  : m_fft_impl( fftLength )
  {

	 std::vector<float> m_realPart = std::vector<float>(fftLength, 0);
	 std::vector<float> m_imagPart = std::vector<float>(fftLength, 0);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  ~FastFourierTransform()
  {

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void   process( const float* input )   { m_fft_impl.process( input , m_realPart , m_imagPart ); }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	std::vector<float>  realPart()      { return m_realPart; }
	std::vector<float>  imagPart()      { return m_imagPart; }

private:

	std::vector<float>  m_realPart;
	std::vector<float>  m_imagPart;

  FFTImpl   m_fft_impl;

};


typedef   FastFourierTransform<FFTW>  FFT;


#endif  // FFT_H_INCLUDED
