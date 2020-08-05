/*
  ==============================================================================

    FeatureData.h
    Created: 28 Aug 2014 6:41:48pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef FEATUREDATA_H_INCLUDED
#define FEATUREDATA_H_INCLUDED

#include "ObservationData.h"
#include <string>
#include <vector>

class FeatureData
{
public:
	FeatureData();
	~FeatureData();
	FeatureData(std::vector<ObservationData> observationData, std::string label, std::string fileName, float sampleRate, int windowSize, float lengthOfAudioClip , float poolingTimeFactor)
	{
		m_ObservationData = observationData;
		m_Label = label;
		m_FileName = fileName;
		m_SampleRate = sampleRate;
		m_LengthOfAudioClip = lengthOfAudioClip;
		m_WindowSize = windowSize;
		m_poolingTimeFactor = poolingTimeFactor;
		
		ComputeLowEnergyFeature();
		ComputeDeltaMFCCs();

		//Pool the Data
		PoolData(m_poolingTimeFactor);
	};

	std::vector<ObservationData> GetObservationData(){return m_ObservationData;}

	std::vector<ObservationData> GetPooldedObservationDataAverage(){return m_PooledObservationDataAverage;}
	std::vector<ObservationData> GetWholeTrackObservationDataAverage(){return m_WholeTrackObservationDataAverage;}

	std::vector<ObservationData> GetPooldedObservationDataStd(){return m_PooledObservationDataStd;}
	std::vector<ObservationData> GetWholeTrackObservationDataStd(){return m_WholeTrackObservationDataStd;}

	std::vector<ObservationData> GetPooldedObservationDataMax(){return m_PooledObservationDataMax;}
	std::vector<ObservationData> GetWholeTrackObservationDataMax(){return m_WholeTrackObservationDataMax;}

	std::vector<ObservationData> GetPooldedObservationDataMin(){return m_PooledObservationDataMin;}
	std::vector<ObservationData> GetWholeTrackObservationDataMin(){return m_WholeTrackObservationDataMin;}

	std::string GetLabel(){return m_Label;}
	float GetPoolingTimeFactor(){return m_poolingTimeFactor;}


private:
	void ComputeLowEnergyFeature();
	void ComputeDeltaMFCCs();
	void PoolData(float timefactor);

	float Average(std::vector<float> v);
	float Deviation(std::vector<float> v, float ave);
	float Max(std::vector<float> v);
	float Min(std::vector<float> v);

	std::vector<ObservationData> m_ObservationData;

	std::vector<ObservationData> m_PooledObservationDataAverage;
	std::vector<ObservationData> m_WholeTrackObservationDataAverage;

	std::vector<ObservationData> m_PooledObservationDataStd;
	std::vector<ObservationData> m_WholeTrackObservationDataStd;

	std::vector<ObservationData> m_PooledObservationDataMax;
	std::vector<ObservationData> m_WholeTrackObservationDataMax;

	std::vector<ObservationData> m_PooledObservationDataMin;
	std::vector<ObservationData> m_WholeTrackObservationDataMin;

	std::string m_Label;
	std::string m_FileName;

	float m_SampleRate;
	float m_LengthOfAudioClip;

	int m_WindowSize;
	float m_poolingTimeFactor;

	std::vector<std::vector<float>> m_deltamfccs;
};



#endif  // FEATUREDATA_H_INCLUDED
