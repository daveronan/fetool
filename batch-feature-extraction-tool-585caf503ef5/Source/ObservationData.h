/*
  ==============================================================================

    ObservationData.h
    Created: 28 Aug 2014 5:28:49pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef OBSERVATIONDATA_H_INCLUDED
#define OBSERVATIONDATA_H_INCLUDED

#include <vector>

class ObservationData
{
public:
	ObservationData();
	~ObservationData();

	ObservationData(float rms, float peak, float crestfactor, float zcr, float centroid, float spread, float skewness, float kurtosis, float brightness, float rolloff85, float rolloff95, float spectralentropy, float flatness, float spectralcf, float spectralflux, std::vector<float> mfccs, std::vector<float> spectralContrast, std::vector<float> spectralValley, float periodicity, float entropyofenergy)
	{
		m_peak = peak;
		m_rms = rms;
		m_crestFactor = crestfactor;
		m_zcr = zcr;
		m_centroid = centroid;
		m_spread = spread;
		m_skewness = skewness;
		m_kurtosis = kurtosis;
		m_brightness = brightness;
		m_rolloff85 = rolloff85;
		m_rolloff95 = rolloff95;
		m_spectralentropy = spectralentropy;
		m_flatness = flatness;
		m_spectralcf = spectralcf;
		m_spectralflux = spectralflux;
		m_mfccs = mfccs;
		m_spectralContrast = spectralContrast;
		m_spectralValley = spectralValley;
		m_periodicity = periodicity;
		m_entropyofenergy = entropyofenergy;
	};

	ObservationData(float rms, float peak, float crestfactor, float zcr, float centroid, float spread, float skewness, float kurtosis, float brightness, float rolloff85, float rolloff95, float spectralentropy, float flatness, float spectralcf, float spectralflux, std::vector<float> mfccs, std::vector<float> dmfccs, std::vector<float> spectralContrast, std::vector<float> spectralValley, float periodicity, float entropyofenergy)
	{
		m_peak = peak;
		m_rms = rms;
		m_crestFactor = crestfactor;
		m_zcr = zcr;
		m_centroid = centroid;
		m_spread = spread;
		m_skewness = skewness;
		m_kurtosis = kurtosis;
		m_brightness = brightness;
		m_rolloff85 = rolloff85;
		m_rolloff95 = rolloff95;
		m_spectralentropy = spectralentropy;
		m_flatness = flatness;
		m_spectralcf = spectralcf;
		m_spectralflux = spectralflux;		
		m_mfccs = mfccs;
		m_dmfccs = dmfccs;
		m_spectralContrast = spectralContrast;
		m_spectralValley = spectralValley;
		m_periodicity = periodicity;
		m_entropyofenergy = entropyofenergy;
	};
		
	float GetPeak(){return m_peak;}
	float GetRMS(){return m_rms;}
	float GetCrestFactor(){return m_crestFactor;}
	float GetZCR(){return m_zcr;}
	float GetCentroid(){return m_centroid;}
	float GetSpread(){return m_spread;}
	float GetSkewness(){return m_skewness;}
	float GetKurtosis(){return m_kurtosis;}
	float GetBrightness(){return m_brightness;}
	float GetRollOff85(){return m_rolloff85;}
	float GetRollOff95(){return m_rolloff95;}
	float GetSpectralEntropy(){return m_spectralentropy;}
	float GetFlatness(){return m_flatness;}
	float GetSpectralCF(){return m_spectralcf;}
	float GetSpectralFlux(){return m_spectralflux;}
	float GetPeriodicity(){return m_periodicity;}
	float GetEntropyOfEnergy(){return m_entropyofenergy;}
	float GetLowEnergy(){return m_lowEnergy;}
	std::vector<float> GetMFCCs(){return m_mfccs;}
	std::vector<float> GetDeltaMFCCs(){return m_dmfccs;}
	std::vector<float> GetSpectralContrast(){ return m_spectralContrast; }
	std::vector<float> GetSpectralValley(){ return m_spectralValley; }
	
	//WholeTrack Feature
	void SetLowEnergy(float lowEnergy){m_lowEnergy = lowEnergy;}

private:
	float m_peak;
	float m_rms;
	float m_crestFactor;
	float m_zcr;
	float m_centroid;
	float m_spread;
	float m_skewness;
	float m_kurtosis;
	float m_brightness;
	float m_rolloff85;
	float m_rolloff95;
	float m_spectralentropy;
	float m_flatness;
	float m_spectralcf;
	float m_spectralflux;
	std::vector<float> m_mfccs;
	std::vector<float> m_dmfccs;
	std::vector<float> m_spectralContrast;
	std::vector<float> m_spectralValley;
	float m_periodicity;
	float m_lowEnergy;
	float m_entropyofenergy;
};



#endif  // OBSERVATIONDATA_H_INCLUDED
