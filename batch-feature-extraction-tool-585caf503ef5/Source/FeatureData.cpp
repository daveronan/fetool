/*
  ==============================================================================

    FeatureData.cpp
    Created: 28 Aug 2014 6:41:48pm
    Author:  david.ronan

  ==============================================================================
*/

#include "FeatureData.h"

FeatureData::FeatureData(){}
FeatureData::~FeatureData(){}

void FeatureData::PoolData(float timefactor)
{
	//TODO: Remove hardcoded value
	int modval = static_cast<int>(timefactor / 0.05); //50 millisecs
	int index = 0;
	int remainderindex = 0;
	
	std::vector<float>  peak;
	std::vector<float>  rms;
	std::vector<float>  crestFactor;
	std::vector<float>  zcr;
	std::vector<float>  centroid;
	std::vector<float>  spread; 
	std::vector<float>  skewness;
	std::vector<float>  kurtosis;
	std::vector<float>  brightness;
	std::vector<float>  rolloff85;
	std::vector<float>  rolloff95;
	std::vector<float>  spectralentropy;
	std::vector<float>  flatness;
	std::vector<float>  spectralcf;
	std::vector<float>  spectralflux;

	std::vector<float>  mfcc1;
	std::vector<float>  mfcc2;
	std::vector<float>  mfcc3;
	std::vector<float>  mfcc4;
	std::vector<float>  mfcc5;
	std::vector<float>  mfcc6;
	std::vector<float>  mfcc7;
	std::vector<float>  mfcc8;
	std::vector<float>  mfcc9;
	std::vector<float>  mfcc10;
	std::vector<float>  mfcc11;
	std::vector<float>  mfcc12;

	std::vector<float>  spectralContrast1;
	std::vector<float>  spectralContrast2;
	std::vector<float>  spectralContrast3;
	std::vector<float>  spectralContrast4;
	std::vector<float>  spectralContrast5;
	std::vector<float>  spectralContrast6;

	std::vector<float>  spectralValley1;
	std::vector<float>  spectralValley2;
	std::vector<float>  spectralValley3;
	std::vector<float>  spectralValley4;
	std::vector<float>  spectralValley5;
	std::vector<float>  spectralValley6;

	for(size_t i = 1; i <= m_ObservationData.size(); i++)
	{
		peak.push_back(m_ObservationData[i -1].GetPeak());
		rms.push_back(m_ObservationData[i -1].GetRMS());
		crestFactor.push_back(m_ObservationData[i -1].GetCrestFactor());
		zcr.push_back(m_ObservationData[i -1].GetZCR());
		centroid.push_back(m_ObservationData[i -1].GetCentroid());
		spread.push_back(m_ObservationData[i -1].GetSpread());
		skewness.push_back(m_ObservationData[i -1].GetSkewness());
		kurtosis.push_back(m_ObservationData[i -1].GetKurtosis());
		brightness.push_back(m_ObservationData[i -1].GetBrightness());
		rolloff85.push_back(m_ObservationData[i -1].GetRollOff85());
		rolloff95.push_back(m_ObservationData[i -1].GetRollOff95());
		spectralentropy.push_back(m_ObservationData[i -1].GetSpectralEntropy());
		flatness.push_back(m_ObservationData[i -1].GetFlatness());
		spectralcf.push_back(m_ObservationData[i -1].GetSpectralCF());
		spectralflux.push_back(m_ObservationData[i -1].GetSpectralFlux());

		mfcc1.push_back(m_ObservationData[i -1].GetMFCCs()[0]);
		mfcc2.push_back(m_ObservationData[i -1].GetMFCCs()[1]);
		mfcc3.push_back(m_ObservationData[i -1].GetMFCCs()[2]);
		mfcc4.push_back(m_ObservationData[i -1].GetMFCCs()[3]);
		mfcc5.push_back(m_ObservationData[i -1].GetMFCCs()[4]);
		mfcc6.push_back(m_ObservationData[i -1].GetMFCCs()[5]);
		mfcc7.push_back(m_ObservationData[i -1].GetMFCCs()[6]);
		mfcc8.push_back(m_ObservationData[i -1].GetMFCCs()[7]);
		mfcc9.push_back(m_ObservationData[i -1].GetMFCCs()[8]);
		mfcc10.push_back(m_ObservationData[i -1].GetMFCCs()[9]);
		mfcc11.push_back(m_ObservationData[i -1].GetMFCCs()[10]);
		mfcc12.push_back(m_ObservationData[i -1].GetMFCCs()[11]);

		spectralContrast1.push_back(m_ObservationData[i - 1].GetSpectralContrast()[0]);
		spectralContrast2.push_back(m_ObservationData[i - 1].GetSpectralContrast()[1]);
		spectralContrast3.push_back(m_ObservationData[i - 1].GetSpectralContrast()[2]);
		spectralContrast4.push_back(m_ObservationData[i - 1].GetSpectralContrast()[3]);
		spectralContrast5.push_back(m_ObservationData[i - 1].GetSpectralContrast()[4]);
		spectralContrast6.push_back(m_ObservationData[i - 1].GetSpectralContrast()[5]);

		spectralValley1.push_back(m_ObservationData[i - 1].GetSpectralValley()[0]);
		spectralValley2.push_back(m_ObservationData[i - 1].GetSpectralValley()[1]);
		spectralValley3.push_back(m_ObservationData[i - 1].GetSpectralValley()[2]);
		spectralValley4.push_back(m_ObservationData[i - 1].GetSpectralValley()[3]);
		spectralValley5.push_back(m_ObservationData[i - 1].GetSpectralValley()[4]);
		spectralValley6.push_back(m_ObservationData[i - 1].GetSpectralValley()[5]);

		if(i % modval == 0)
		{
			std::vector<float> peaksubset(peak.begin() + index, peak.begin() + index + modval);
			std::vector<float> rmssubset(rms.begin() + index, rms.begin() + index + modval);
			std::vector<float> crestfactorsubset(crestFactor.begin() + index, crestFactor.begin() + index + modval);
			std::vector<float> zcrsubset(zcr.begin() + index, zcr.begin() + index + modval);
			std::vector<float> centroidsubset(centroid.begin() + index, centroid.begin() + index + modval);	
			std::vector<float> spreadsubset(spread.begin() + index, spread.begin() + index + modval);
			std::vector<float> skewnesssubset(skewness.begin() + index, skewness.begin() + index + modval);
			std::vector<float> kurtosissubset(kurtosis.begin() + index, kurtosis.begin() + index + modval);
			std::vector<float> brightnesssubset(brightness.begin() + index, brightness.begin() + index + modval);
			std::vector<float> rolloff85subset(rolloff85.begin() + index, rolloff85.begin() + index + modval);
			std::vector<float> rolloff95subset(rolloff95.begin() + index, rolloff95.begin() + index + modval);
			std::vector<float> spectralentropysubset(spectralentropy.begin() + index, spectralentropy.begin() + index + modval);
			std::vector<float> flatnesssubset(flatness.begin() + index, flatness.begin() + index + modval);
			std::vector<float> spectralcfsubset(spectralcf.begin() + index, spectralcf.begin() + index + modval);
			std::vector<float> spectralfluxsubset(spectralflux.begin() + index, spectralflux.begin() + index + modval);

			std::vector<float> mfcc1subset(mfcc1.begin() + index, mfcc1.begin() + index + modval);			
			std::vector<float> mfcc2subset(mfcc2.begin() + index, mfcc2.begin() + index + modval);			
			std::vector<float> mfcc3subset(mfcc3.begin() + index, mfcc3.begin() + index + modval);			
			std::vector<float> mfcc4subset(mfcc4.begin() + index, mfcc4.begin() + index + modval);			
			std::vector<float> mfcc5subset(mfcc5.begin() + index, mfcc5.begin() + index + modval);			
			std::vector<float> mfcc6subset(mfcc6.begin() + index, mfcc6.begin() + index + modval);			
			std::vector<float> mfcc7subset(mfcc7.begin() + index, mfcc7.begin() + index + modval);			
			std::vector<float> mfcc8subset(mfcc8.begin() + index, mfcc8.begin() + index + modval);			
			std::vector<float> mfcc9subset(mfcc9.begin() + index, mfcc9.begin() + index + modval);			
			std::vector<float> mfcc10subset(mfcc10.begin() + index, mfcc10.begin() + index + modval);			
			std::vector<float> mfcc11subset(mfcc11.begin() + index, mfcc11.begin() + index + modval);			
			std::vector<float> mfcc12subset(mfcc12.begin() + index, mfcc12.begin() + index + modval);
					
			std::vector<float> dmfcc1subset(m_deltamfccs[0].begin() + index, m_deltamfccs[0].begin() + index + modval);
			std::vector<float> dmfcc2subset(m_deltamfccs[1].begin() + index, m_deltamfccs[1].begin() + index + modval);
			std::vector<float> dmfcc3subset(m_deltamfccs[2].begin() + index, m_deltamfccs[2].begin() + index + modval);
			std::vector<float> dmfcc4subset(m_deltamfccs[3].begin() + index, m_deltamfccs[3].begin() + index + modval);
			std::vector<float> dmfcc5subset(m_deltamfccs[4].begin() + index, m_deltamfccs[4].begin() + index + modval);
			std::vector<float> dmfcc6subset(m_deltamfccs[5].begin() + index, m_deltamfccs[5].begin() + index + modval);
			std::vector<float> dmfcc7subset(m_deltamfccs[6].begin() + index, m_deltamfccs[6].begin() + index + modval);
			std::vector<float> dmfcc8subset(m_deltamfccs[7].begin() + index, m_deltamfccs[7].begin() + index + modval);
			std::vector<float> dmfcc9subset(m_deltamfccs[8].begin() + index, m_deltamfccs[8].begin() + index + modval);
			std::vector<float> dmfcc10subset(m_deltamfccs[9].begin() + index, m_deltamfccs[9].begin() + index + modval);
			std::vector<float> dmfcc11subset(m_deltamfccs[10].begin() + index, m_deltamfccs[10].begin() + index + modval);
			std::vector<float> dmfcc12subset(m_deltamfccs[11].begin() + index, m_deltamfccs[11].begin() + index + modval);

			std::vector<float> spectralContrast1subset(spectralContrast1.begin() + index, spectralContrast1.begin() + index + modval);
			std::vector<float> spectralContrast2subset(spectralContrast2.begin() + index, spectralContrast2.begin() + index + modval);
			std::vector<float> spectralContrast3subset(spectralContrast3.begin() + index, spectralContrast3.begin() + index + modval);
			std::vector<float> spectralContrast4subset(spectralContrast4.begin() + index, spectralContrast4.begin() + index + modval);
			std::vector<float> spectralContrast5subset(spectralContrast5.begin() + index, spectralContrast5.begin() + index + modval);
			std::vector<float> spectralContrast6subset(spectralContrast6.begin() + index, spectralContrast6.begin() + index + modval);

			std::vector<float> spectralValley1subset(spectralValley1.begin() + index, spectralValley1.begin() + index + modval);
			std::vector<float> spectralValley2subset(spectralValley2.begin() + index, spectralValley2.begin() + index + modval);
			std::vector<float> spectralValley3subset(spectralValley3.begin() + index, spectralValley3.begin() + index + modval);
			std::vector<float> spectralValley4subset(spectralValley4.begin() + index, spectralValley4.begin() + index + modval);
			std::vector<float> spectralValley5subset(spectralValley5.begin() + index, spectralValley5.begin() + index + modval);
			std::vector<float> spectralValley6subset(spectralValley6.begin() + index, spectralValley6.begin() + index + modval);

			float  avgpeak = Average(peaksubset);
			float  avgrms = Average(rmssubset);
			float  avgcrestFactor = Average(crestfactorsubset);
			float  avgzcr = Average(zcrsubset);
			float  avgcentroid = Average(centroidsubset);
			float  avgspread = Average(spreadsubset);
			float  avgskewness = Average(skewnesssubset);
			float  avgkurtosis = Average(kurtosissubset);
			float  avgbrightness = Average(brightness);
			float  avgrolloff85 = Average(rolloff85subset);
			float  avgrolloff95 = Average(rolloff95subset);
			float  avgspectralentropy = Average(spectralentropysubset); 
			float  avgflatness = Average(flatnesssubset) ;
			float  avgspectralcf = Average(spectralcfsubset); 
			float  avgspectralflux = Average(spectralfluxsubset); 
			std::vector<float>  avgmfcc;
			std::vector<float>  avgdmfcc;
			std::vector<float>  avgspectralContrast;
			std::vector<float>  avgspectralValley;

			avgmfcc.push_back(Average(mfcc1subset));
			avgmfcc.push_back(Average(mfcc2subset));
			avgmfcc.push_back(Average(mfcc3subset));
			avgmfcc.push_back(Average(mfcc4subset));
			avgmfcc.push_back(Average(mfcc5subset));
			avgmfcc.push_back(Average(mfcc6subset));
			avgmfcc.push_back(Average(mfcc7subset));
			avgmfcc.push_back(Average(mfcc8subset));
			avgmfcc.push_back(Average(mfcc9subset));
			avgmfcc.push_back(Average(mfcc10subset));
			avgmfcc.push_back(Average(mfcc11subset));
			avgmfcc.push_back(Average(mfcc12subset));

			avgdmfcc.push_back(Average(dmfcc1subset));
			avgdmfcc.push_back(Average(dmfcc2subset));
			avgdmfcc.push_back(Average(dmfcc3subset));
			avgdmfcc.push_back(Average(dmfcc4subset));
			avgdmfcc.push_back(Average(dmfcc5subset));
			avgdmfcc.push_back(Average(dmfcc6subset));
			avgdmfcc.push_back(Average(dmfcc7subset));
			avgdmfcc.push_back(Average(dmfcc8subset));
			avgdmfcc.push_back(Average(dmfcc9subset));
			avgdmfcc.push_back(Average(dmfcc10subset));
			avgdmfcc.push_back(Average(dmfcc11subset));
			avgdmfcc.push_back(Average(dmfcc12subset));

			avgspectralContrast.push_back(Average(spectralContrast1subset));
			avgspectralContrast.push_back(Average(spectralContrast2subset));
			avgspectralContrast.push_back(Average(spectralContrast3subset));
			avgspectralContrast.push_back(Average(spectralContrast4subset));
			avgspectralContrast.push_back(Average(spectralContrast5subset));
			avgspectralContrast.push_back(Average(spectralContrast6subset));

			avgspectralValley.push_back(Average(spectralValley1subset));
			avgspectralValley.push_back(Average(spectralValley2subset));
			avgspectralValley.push_back(Average(spectralValley3subset));
			avgspectralValley.push_back(Average(spectralValley4subset));
			avgspectralValley.push_back(Average(spectralValley5subset));
			avgspectralValley.push_back(Average(spectralValley6subset));


			ObservationData obs = ObservationData(avgrms, avgpeak, avgcrestFactor, avgzcr, avgcentroid, avgspread, avgskewness, avgkurtosis, avgbrightness, avgrolloff85, avgrolloff95, avgspectralentropy, avgflatness, avgspectralcf, avgspectralflux, avgmfcc, avgdmfcc, avgspectralContrast, avgspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
			obs.SetLowEnergy(m_ObservationData[i-1].GetLowEnergy());
			m_PooledObservationDataAverage.push_back(obs);

			std::vector<float>  stdmfcc;
			std::vector<float>  stddmfcc;
			std::vector<float>  stdspectralContrast;
			std::vector<float>  stdspectralValley;

			stdmfcc.push_back(Deviation(mfcc1subset,avgmfcc[0]));
			stdmfcc.push_back(Deviation(mfcc2subset, avgmfcc[1]));
			stdmfcc.push_back(Deviation(mfcc3subset, avgmfcc[2]));
			stdmfcc.push_back(Deviation(mfcc4subset, avgmfcc[3]));
			stdmfcc.push_back(Deviation(mfcc5subset, avgmfcc[4]));
			stdmfcc.push_back(Deviation(mfcc6subset, avgmfcc[5]));
			stdmfcc.push_back(Deviation(mfcc7subset, avgmfcc[6]));
			stdmfcc.push_back(Deviation(mfcc8subset, avgmfcc[7]));
			stdmfcc.push_back(Deviation(mfcc9subset, avgmfcc[8]));
			stdmfcc.push_back(Deviation(mfcc10subset, avgmfcc[9]));
			stdmfcc.push_back(Deviation(mfcc11subset, avgmfcc[10]));
			stdmfcc.push_back(Deviation(mfcc12subset, avgmfcc[11]));

			stddmfcc.push_back(Deviation(dmfcc1subset, avgdmfcc[0]));
			stddmfcc.push_back(Deviation(dmfcc2subset, avgdmfcc[1]));
			stddmfcc.push_back(Deviation(dmfcc3subset, avgdmfcc[2]));
			stddmfcc.push_back(Deviation(dmfcc4subset, avgdmfcc[3]));
			stddmfcc.push_back(Deviation(dmfcc5subset, avgdmfcc[4]));
			stddmfcc.push_back(Deviation(dmfcc6subset, avgdmfcc[5]));
			stddmfcc.push_back(Deviation(dmfcc7subset, avgdmfcc[6]));
			stddmfcc.push_back(Deviation(dmfcc8subset, avgdmfcc[7]));
			stddmfcc.push_back(Deviation(dmfcc9subset, avgdmfcc[8]));
			stddmfcc.push_back(Deviation(dmfcc10subset, avgdmfcc[9]));
			stddmfcc.push_back(Deviation(dmfcc11subset, avgdmfcc[10]));
			stddmfcc.push_back(Deviation(dmfcc12subset, avgdmfcc[11]));

			stdspectralContrast.push_back(Deviation(spectralContrast1subset, avgspectralContrast[0]));
			stdspectralContrast.push_back(Deviation(spectralContrast2subset, avgspectralContrast[1]));
			stdspectralContrast.push_back(Deviation(spectralContrast3subset, avgspectralContrast[2]));
			stdspectralContrast.push_back(Deviation(spectralContrast4subset, avgspectralContrast[3]));
			stdspectralContrast.push_back(Deviation(spectralContrast5subset, avgspectralContrast[4]));
			stdspectralContrast.push_back(Deviation(spectralContrast6subset, avgspectralContrast[5]));

			stdspectralValley.push_back(Deviation(spectralValley1subset, avgspectralValley[0]));
			stdspectralValley.push_back(Deviation(spectralValley2subset, avgspectralValley[1]));
			stdspectralValley.push_back(Deviation(spectralValley3subset, avgspectralValley[2]));
			stdspectralValley.push_back(Deviation(spectralValley4subset, avgspectralValley[3]));
			stdspectralValley.push_back(Deviation(spectralValley5subset, avgspectralValley[4]));
			stdspectralValley.push_back(Deviation(spectralValley6subset, avgspectralValley[5]));

			obs = ObservationData(Deviation(rmssubset, avgrms), Deviation(peaksubset, avgpeak),  Deviation(crestfactorsubset, avgcrestFactor), Deviation(zcrsubset, avgzcr), Deviation(centroidsubset, avgcentroid), Deviation(spreadsubset, avgspread), Deviation(skewnesssubset, avgskewness), Deviation(kurtosissubset, avgkurtosis), Deviation(brightnesssubset, avgbrightness), Deviation(rolloff85subset, avgrolloff85), Deviation(rolloff95subset, avgrolloff95), Deviation(spectralentropysubset, avgspectralentropy), Deviation(flatnesssubset, avgflatness), Deviation(spectralcfsubset, avgspectralcf), Deviation(spectralfluxsubset, avgspectralflux), stdmfcc, stddmfcc, stdspectralContrast, stdspectralValley, 0, 0);
			obs.SetLowEnergy(0); //
			m_PooledObservationDataStd.push_back(obs);

			std::vector<float>  maxmfcc;
			std::vector<float>  maxdmfcc;
			std::vector<float>  maxspectralContrast;
			std::vector<float>  maxspectralValley;

			maxmfcc.push_back(Max(mfcc1subset));
			maxmfcc.push_back(Max(mfcc2subset));
			maxmfcc.push_back(Max(mfcc3subset));
			maxmfcc.push_back(Max(mfcc4subset));
			maxmfcc.push_back(Max(mfcc5subset));
			maxmfcc.push_back(Max(mfcc6subset));
			maxmfcc.push_back(Max(mfcc7subset));
			maxmfcc.push_back(Max(mfcc8subset));
			maxmfcc.push_back(Max(mfcc9subset));
			maxmfcc.push_back(Max(mfcc10subset));
			maxmfcc.push_back(Max(mfcc11subset));
			maxmfcc.push_back(Max(mfcc12subset));

			maxdmfcc.push_back(Max(dmfcc1subset));
			maxdmfcc.push_back(Max(dmfcc2subset));
			maxdmfcc.push_back(Max(dmfcc3subset));
			maxdmfcc.push_back(Max(dmfcc4subset));
			maxdmfcc.push_back(Max(dmfcc5subset));
			maxdmfcc.push_back(Max(dmfcc6subset));
			maxdmfcc.push_back(Max(dmfcc7subset));
			maxdmfcc.push_back(Max(dmfcc8subset));
			maxdmfcc.push_back(Max(dmfcc9subset));
			maxdmfcc.push_back(Max(dmfcc10subset));
			maxdmfcc.push_back(Max(dmfcc11subset));
			maxdmfcc.push_back(Max(dmfcc12subset));

			maxspectralContrast.push_back(Max(spectralContrast1subset));
			maxspectralContrast.push_back(Max(spectralContrast2subset));
			maxspectralContrast.push_back(Max(spectralContrast3subset));
			maxspectralContrast.push_back(Max(spectralContrast4subset));
			maxspectralContrast.push_back(Max(spectralContrast5subset));
			maxspectralContrast.push_back(Max(spectralContrast6subset));

			maxspectralValley.push_back(Max(spectralValley1subset));
			maxspectralValley.push_back(Max(spectralValley2subset));
			maxspectralValley.push_back(Max(spectralValley3subset));
			maxspectralValley.push_back(Max(spectralValley4subset));
			maxspectralValley.push_back(Max(spectralValley5subset));
			maxspectralValley.push_back(Max(spectralValley6subset));

			obs = ObservationData(Max(rmssubset), Max(peaksubset), Max(crestfactorsubset),  Max(zcrsubset), Max(centroidsubset), Max(spreadsubset), Max(skewnesssubset), Max(kurtosissubset), Max(brightnesssubset), Max(rolloff85subset), Max(rolloff95subset), Max(spectralentropysubset), Max(flatnesssubset), Max(spectralcfsubset), Max(spectralfluxsubset), maxmfcc, maxdmfcc, maxspectralContrast, maxspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
			obs.SetLowEnergy(m_ObservationData[i-1].GetLowEnergy());
			m_PooledObservationDataMax.push_back(obs);

			std::vector<float>  minmfcc;
			std::vector<float>  mindmfcc;
			std::vector<float>  minspectralContrast;
			std::vector<float>  minspectralValley;

			minmfcc.push_back(Min(mfcc1subset));
			minmfcc.push_back(Min(mfcc2subset));
			minmfcc.push_back(Min(mfcc3subset));
			minmfcc.push_back(Min(mfcc4subset));
			minmfcc.push_back(Min(mfcc5subset));
			minmfcc.push_back(Min(mfcc6subset));
			minmfcc.push_back(Min(mfcc7subset));
			minmfcc.push_back(Min(mfcc8subset));
			minmfcc.push_back(Min(mfcc9subset));
			minmfcc.push_back(Min(mfcc10subset));
			minmfcc.push_back(Min(mfcc11subset));
			minmfcc.push_back(Min(mfcc12subset));

			mindmfcc.push_back(Min(dmfcc1subset));
			mindmfcc.push_back(Min(dmfcc2subset));
			mindmfcc.push_back(Min(dmfcc3subset));
			mindmfcc.push_back(Min(dmfcc4subset));
			mindmfcc.push_back(Min(dmfcc5subset));
			mindmfcc.push_back(Min(dmfcc6subset));
			mindmfcc.push_back(Min(dmfcc7subset));
			mindmfcc.push_back(Min(dmfcc8subset));
			mindmfcc.push_back(Min(dmfcc9subset));
			mindmfcc.push_back(Min(dmfcc10subset));
			mindmfcc.push_back(Min(dmfcc11subset));
			mindmfcc.push_back(Min(dmfcc12subset));

			minspectralContrast.push_back(Min(spectralContrast1subset));
			minspectralContrast.push_back(Min(spectralContrast2subset));
			minspectralContrast.push_back(Min(spectralContrast3subset));
			minspectralContrast.push_back(Min(spectralContrast4subset));
			minspectralContrast.push_back(Min(spectralContrast5subset));
			minspectralContrast.push_back(Min(spectralContrast6subset));

			minspectralValley.push_back(Min(spectralValley1subset));
			minspectralValley.push_back(Min(spectralValley2subset));
			minspectralValley.push_back(Min(spectralValley3subset));
			minspectralValley.push_back(Min(spectralValley4subset));
			minspectralValley.push_back(Min(spectralValley5subset));
			minspectralValley.push_back(Min(spectralValley6subset));

			obs = ObservationData(Min(rmssubset), Min(peaksubset),  Min(crestfactorsubset),  Min(zcrsubset), Min(centroidsubset), Min(spreadsubset), Min(skewnesssubset), Min(kurtosissubset), Min(brightnesssubset), Min(rolloff85subset), Min(rolloff95subset), Min(spectralentropysubset), Min(flatnesssubset), Min(spectralcfsubset),  Min(spectralfluxsubset), minmfcc, mindmfcc, minspectralContrast, minspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
			obs.SetLowEnergy(m_ObservationData[i-1].GetLowEnergy());
			m_PooledObservationDataMin.push_back(obs);

			//TODO: Think about this
			index += modval;
			remainderindex = i;
		}
	}

	//Get the end of the audio
	std::vector<float> peaksubset(peak.begin() + remainderindex, peak.end());
	std::vector<float> rmssubset(rms.begin() + + remainderindex, rms.end());
	std::vector<float> crestFactorsubset(crestFactor.begin() + remainderindex, crestFactor.end());
	std::vector<float> zcrsubset(zcr.begin() + remainderindex, zcr.end());
	std::vector<float> centroidsubset(centroid.begin() + remainderindex, centroid.end());	
	std::vector<float> spreadsubset(spread.begin() + remainderindex, spread.end());
	std::vector<float> skewnesssubset(skewness.begin() + remainderindex, skewness.end());
	std::vector<float> kurtosissubset(kurtosis.begin() + remainderindex, kurtosis.end());
	std::vector<float> brightnesssubset(brightness.begin() + remainderindex, brightness.end());
	std::vector<float> rolloff85subset(rolloff85.begin() + remainderindex, rolloff85.end());
	std::vector<float> rolloff95subset(rolloff95.begin() + remainderindex, rolloff95.end());
	std::vector<float> spectralentropysubset(spectralentropy.begin() + remainderindex, spectralentropy.end());
	std::vector<float> spectralcfsubset(spectralcf.begin() + remainderindex, spectralcf.end());
	std::vector<float> spectralfluxsubset(spectralflux.begin() + remainderindex, spectralflux.end());
	std::vector<float> flatnesssubset(flatness.begin() + remainderindex, flatness.end());

	std::vector<float> mfcc1subset(mfcc1.begin() + remainderindex, mfcc1.end());			
	std::vector<float> mfcc2subset(mfcc2.begin() + remainderindex, mfcc2.end());			
	std::vector<float> mfcc3subset(mfcc3.begin() + remainderindex, mfcc3.end());			
	std::vector<float> mfcc4subset(mfcc4.begin() + remainderindex, mfcc4.end());			
	std::vector<float> mfcc5subset(mfcc5.begin() + remainderindex, mfcc5.end());			
	std::vector<float> mfcc6subset(mfcc6.begin() + remainderindex, mfcc6.end());			
	std::vector<float> mfcc7subset(mfcc7.begin() + remainderindex, mfcc7.end());			
	std::vector<float> mfcc8subset(mfcc8.begin() + remainderindex, mfcc8.end());			
	std::vector<float> mfcc9subset(mfcc9.begin() + remainderindex, mfcc9.end());
	std::vector<float> mfcc10subset(mfcc10.begin() + remainderindex, mfcc10.end());			
	std::vector<float> mfcc11subset(mfcc11.begin() + remainderindex, mfcc11.end());			
	std::vector<float> mfcc12subset(mfcc12.begin() + remainderindex, mfcc12.end());

	std::vector<float> dmfcc1subset(m_deltamfccs[0].begin() + remainderindex, m_deltamfccs[0].end());			
	std::vector<float> dmfcc2subset(m_deltamfccs[1].begin() + remainderindex, m_deltamfccs[1].end());			
	std::vector<float> dmfcc3subset(m_deltamfccs[2].begin() + remainderindex, m_deltamfccs[2].end());			
	std::vector<float> dmfcc4subset(m_deltamfccs[3].begin() + remainderindex, m_deltamfccs[3].end());			
	std::vector<float> dmfcc5subset(m_deltamfccs[4].begin() + remainderindex, m_deltamfccs[4].end());			
	std::vector<float> dmfcc6subset(m_deltamfccs[5].begin() + remainderindex, m_deltamfccs[5].end());			
	std::vector<float> dmfcc7subset(m_deltamfccs[6].begin() + remainderindex, m_deltamfccs[6].end());			
	std::vector<float> dmfcc8subset(m_deltamfccs[7].begin() + remainderindex, m_deltamfccs[7].end());			
	std::vector<float> dmfcc9subset(m_deltamfccs[8].begin() + remainderindex, m_deltamfccs[8].end());			
	std::vector<float> dmfcc10subset(m_deltamfccs[9].begin() + remainderindex, m_deltamfccs[9].end());			
	std::vector<float> dmfcc11subset(m_deltamfccs[10].begin() + remainderindex, m_deltamfccs[10].end());			
	std::vector<float> dmfcc12subset(m_deltamfccs[11].begin() + remainderindex, m_deltamfccs[11].end());

	std::vector<float> spectralContrast1subset(spectralContrast1.begin() + remainderindex, spectralContrast1.end());
	std::vector<float> spectralContrast2subset(spectralContrast2.begin() + remainderindex, spectralContrast2.end());
	std::vector<float> spectralContrast3subset(spectralContrast3.begin() + remainderindex, spectralContrast3.end());
	std::vector<float> spectralContrast4subset(spectralContrast4.begin() + remainderindex, spectralContrast4.end());
	std::vector<float> spectralContrast5subset(spectralContrast5.begin() + remainderindex, spectralContrast5.end());
	std::vector<float> spectralContrast6subset(spectralContrast6.begin() + remainderindex, spectralContrast6.end());

	std::vector<float> spectralValley1subset(spectralValley1.begin() + remainderindex, spectralValley1.end());
	std::vector<float> spectralValley2subset(spectralValley2.begin() + remainderindex, spectralValley2.end());
	std::vector<float> spectralValley3subset(spectralValley3.begin() + remainderindex, spectralValley3.end());
	std::vector<float> spectralValley4subset(spectralValley4.begin() + remainderindex, spectralValley4.end());
	std::vector<float> spectralValley5subset(spectralValley5.begin() + remainderindex, spectralValley5.end());
	std::vector<float> spectralValley6subset(spectralValley6.begin() + remainderindex, spectralValley6.end());

	float  avgpeak = Average(peaksubset);
	float  avgrms = Average(rmssubset);
	float  avgcrestFactor = Average(crestFactorsubset);
	float  avgzcr = Average(zcrsubset);
	float  avgcentroid = Average(centroidsubset);
	float  avgspread = Average(spreadsubset);
	float  avgskewness = Average(skewnesssubset);
	float  avgkurtosis = Average(kurtosissubset);
	float  avgbrightness = Average(brightness);
	float  avgrolloff85 = Average(rolloff85subset);
	float  avgrolloff95 = Average(rolloff95subset);
	float  avgspectralentropy = Average(spectralentropysubset); 
	float  avgflatness = Average(flatnesssubset);
	float  avgspectralcf = Average(spectralcfsubset); 
	float  avgspectralflux = Average(spectralfluxsubset); 

	std::vector<float>  avgmfcc;
	std::vector<float>  avgdeltamfcc;
	std::vector<float>  avgspectralContrast;
	std::vector<float>  avgspectralValley;

	avgmfcc.push_back(Average(mfcc1subset));
	avgmfcc.push_back(Average(mfcc2subset));
	avgmfcc.push_back(Average(mfcc3subset));
	avgmfcc.push_back(Average(mfcc4subset));
	avgmfcc.push_back(Average(mfcc5subset));
	avgmfcc.push_back(Average(mfcc6subset));
	avgmfcc.push_back(Average(mfcc7subset));
	avgmfcc.push_back(Average(mfcc8subset));
	avgmfcc.push_back(Average(mfcc9subset));
	avgmfcc.push_back(Average(mfcc10subset));
	avgmfcc.push_back(Average(mfcc11subset));
	avgmfcc.push_back(Average(mfcc12subset));

	avgdeltamfcc.push_back(Average(dmfcc1subset));
	avgdeltamfcc.push_back(Average(dmfcc2subset));
	avgdeltamfcc.push_back(Average(dmfcc3subset));
	avgdeltamfcc.push_back(Average(dmfcc4subset));
	avgdeltamfcc.push_back(Average(dmfcc5subset));
	avgdeltamfcc.push_back(Average(dmfcc6subset));
	avgdeltamfcc.push_back(Average(dmfcc7subset));
	avgdeltamfcc.push_back(Average(dmfcc8subset));
	avgdeltamfcc.push_back(Average(dmfcc9subset));
	avgdeltamfcc.push_back(Average(dmfcc10subset));
	avgdeltamfcc.push_back(Average(dmfcc11subset));
	avgdeltamfcc.push_back(Average(dmfcc12subset));

	avgspectralContrast.push_back(Average(spectralContrast1subset));
	avgspectralContrast.push_back(Average(spectralContrast2subset));
	avgspectralContrast.push_back(Average(spectralContrast3subset));
	avgspectralContrast.push_back(Average(spectralContrast4subset));
	avgspectralContrast.push_back(Average(spectralContrast5subset));
	avgspectralContrast.push_back(Average(spectralContrast6subset));

	avgspectralValley.push_back(Average(spectralValley1subset));
	avgspectralValley.push_back(Average(spectralValley2subset));
	avgspectralValley.push_back(Average(spectralValley3subset));
	avgspectralValley.push_back(Average(spectralValley4subset));
	avgspectralValley.push_back(Average(spectralValley5subset));
	avgspectralValley.push_back(Average(spectralValley6subset));

	ObservationData obs = ObservationData(avgrms, avgpeak, avgcrestFactor, avgzcr, avgcentroid, avgspread, avgskewness, avgkurtosis, avgbrightness, avgrolloff85, avgrolloff95, avgspectralentropy, avgflatness, avgspectralcf, avgspectralflux, avgmfcc, avgdeltamfcc, avgspectralContrast, avgspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
	obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
	m_PooledObservationDataAverage.push_back(obs);

	std::vector<float>  stdmfcc;
	std::vector<float>  stddeltamfcc;
	std::vector<float>  stdspectralContrast;
	std::vector<float>  stdspectralValley;

	stdmfcc.push_back(Deviation(mfcc1subset,avgmfcc[0]));
	stdmfcc.push_back(Deviation(mfcc2subset,avgmfcc[1]));
	stdmfcc.push_back(Deviation(mfcc3subset,avgmfcc[2]));
	stdmfcc.push_back(Deviation(mfcc4subset,avgmfcc[3]));
	stdmfcc.push_back(Deviation(mfcc5subset,avgmfcc[4]));
	stdmfcc.push_back(Deviation(mfcc6subset,avgmfcc[5]));
	stdmfcc.push_back(Deviation(mfcc7subset,avgmfcc[6]));
	stdmfcc.push_back(Deviation(mfcc8subset,avgmfcc[7]));
	stdmfcc.push_back(Deviation(mfcc9subset,avgmfcc[8]));
	stdmfcc.push_back(Deviation(mfcc10subset,avgmfcc[9]));
	stdmfcc.push_back(Deviation(mfcc11subset,avgmfcc[10]));
	stdmfcc.push_back(Deviation(mfcc12subset,avgmfcc[11]));

	stddeltamfcc.push_back(Deviation(dmfcc1subset,avgdeltamfcc[0]));
	stddeltamfcc.push_back(Deviation(dmfcc2subset,avgdeltamfcc[1]));
	stddeltamfcc.push_back(Deviation(dmfcc3subset,avgdeltamfcc[2]));
	stddeltamfcc.push_back(Deviation(dmfcc4subset,avgdeltamfcc[3]));
	stddeltamfcc.push_back(Deviation(dmfcc5subset,avgdeltamfcc[4]));
	stddeltamfcc.push_back(Deviation(dmfcc6subset,avgdeltamfcc[5]));
	stddeltamfcc.push_back(Deviation(dmfcc7subset,avgdeltamfcc[6]));
	stddeltamfcc.push_back(Deviation(dmfcc8subset,avgdeltamfcc[7]));
	stddeltamfcc.push_back(Deviation(dmfcc9subset,avgdeltamfcc[8]));
	stddeltamfcc.push_back(Deviation(dmfcc10subset,avgdeltamfcc[9]));
	stddeltamfcc.push_back(Deviation(dmfcc11subset,avgdeltamfcc[10]));
	stddeltamfcc.push_back(Deviation(dmfcc12subset,avgdeltamfcc[11]));

	stdspectralContrast.push_back(Deviation(spectralContrast1subset, avgspectralContrast[0]));
	stdspectralContrast.push_back(Deviation(spectralContrast2subset, avgspectralContrast[1]));
	stdspectralContrast.push_back(Deviation(spectralContrast3subset, avgspectralContrast[2]));
	stdspectralContrast.push_back(Deviation(spectralContrast4subset, avgspectralContrast[3]));
	stdspectralContrast.push_back(Deviation(spectralContrast5subset, avgspectralContrast[4]));
	stdspectralContrast.push_back(Deviation(spectralContrast6subset, avgspectralContrast[5]));

	stdspectralValley.push_back(Deviation(spectralValley1subset, avgspectralValley[0]));
	stdspectralValley.push_back(Deviation(spectralValley2subset, avgspectralValley[1]));
	stdspectralValley.push_back(Deviation(spectralValley3subset, avgspectralValley[2]));
	stdspectralValley.push_back(Deviation(spectralValley4subset, avgspectralValley[3]));
	stdspectralValley.push_back(Deviation(spectralValley5subset, avgspectralValley[4]));
	stdspectralValley.push_back(Deviation(spectralValley6subset, avgspectralValley[5]));

	obs = ObservationData(Deviation(rmssubset, avgrms), Deviation(peaksubset, avgpeak), Deviation(crestFactorsubset, avgcrestFactor), Deviation(zcrsubset, avgzcr), Deviation(centroidsubset, avgcentroid), Deviation(spreadsubset, avgspread), Deviation(skewnesssubset, avgskewness), Deviation(kurtosissubset, avgkurtosis), Deviation(brightnesssubset, avgbrightness), Deviation(rolloff85subset, avgrolloff85), Deviation(rolloff95subset, avgrolloff95), Deviation(spectralentropysubset, avgspectralentropy), Deviation(flatnesssubset, avgflatness), Deviation(spectralcfsubset, avgspectralcf), Deviation(spectralfluxsubset, avgspectralflux), stdmfcc, stddeltamfcc, stdspectralContrast, stdspectralValley, 0, 0);
	obs.SetLowEnergy(0); //
	m_PooledObservationDataStd.push_back(obs);

	std::vector<float>  maxmfcc;
	std::vector<float>  maxdeltamfcc;
	std::vector<float>  maxspectralContrast;
	std::vector<float>  maxspectralValley;

	maxmfcc.push_back(Max(mfcc1subset));
	maxmfcc.push_back(Max(mfcc2subset));
	maxmfcc.push_back(Max(mfcc3subset));
	maxmfcc.push_back(Max(mfcc4subset));
	maxmfcc.push_back(Max(mfcc5subset));
	maxmfcc.push_back(Max(mfcc6subset));
	maxmfcc.push_back(Max(mfcc7subset));
	maxmfcc.push_back(Max(mfcc8subset));
	maxmfcc.push_back(Max(mfcc9subset));
	maxmfcc.push_back(Max(mfcc10subset));
	maxmfcc.push_back(Max(mfcc11subset));
	maxmfcc.push_back(Max(mfcc12subset));

	maxdeltamfcc.push_back(Max(dmfcc1subset));
	maxdeltamfcc.push_back(Max(dmfcc2subset));
	maxdeltamfcc.push_back(Max(dmfcc3subset));
	maxdeltamfcc.push_back(Max(dmfcc4subset));
	maxdeltamfcc.push_back(Max(dmfcc5subset));
	maxdeltamfcc.push_back(Max(dmfcc6subset));
	maxdeltamfcc.push_back(Max(dmfcc7subset));
	maxdeltamfcc.push_back(Max(dmfcc8subset));
	maxdeltamfcc.push_back(Max(dmfcc9subset));
	maxdeltamfcc.push_back(Max(dmfcc10subset));
	maxdeltamfcc.push_back(Max(dmfcc11subset));
	maxdeltamfcc.push_back(Max(dmfcc12subset));

	maxspectralContrast.push_back(Max(spectralContrast1subset));
	maxspectralContrast.push_back(Max(spectralContrast2subset));
	maxspectralContrast.push_back(Max(spectralContrast3subset));
	maxspectralContrast.push_back(Max(spectralContrast4subset));
	maxspectralContrast.push_back(Max(spectralContrast5subset));
	maxspectralContrast.push_back(Max(spectralContrast6subset));

	maxspectralValley.push_back(Max(spectralValley1subset));
	maxspectralValley.push_back(Max(spectralValley2subset));
	maxspectralValley.push_back(Max(spectralValley3subset));
	maxspectralValley.push_back(Max(spectralValley4subset));
	maxspectralValley.push_back(Max(spectralValley5subset));
	maxspectralValley.push_back(Max(spectralValley6subset));

	obs = ObservationData(Max(rmssubset), Max(peaksubset), Max(crestFactorsubset), Max(zcrsubset), Max(centroidsubset), Max(spreadsubset), Max(skewnesssubset), Max(kurtosissubset), Max(brightnesssubset), Max(rolloff85subset), Max(rolloff95subset), Max(spectralentropysubset), Max(flatnesssubset), Max(spectralcfsubset),  Max(spectralfluxsubset), maxmfcc, maxdeltamfcc, maxspectralContrast, maxspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
	obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
	m_PooledObservationDataMax.push_back(obs);

	std::vector<float>  minmfcc;
	std::vector<float> mindeltamfcc;
	std::vector<float>  minspectralContrast;
	std::vector<float>  minspectralValley;

	minmfcc.push_back(Min(mfcc1subset));
	minmfcc.push_back(Min(mfcc2subset));
	minmfcc.push_back(Min(mfcc3subset));
	minmfcc.push_back(Min(mfcc4subset));
	minmfcc.push_back(Min(mfcc5subset));
	minmfcc.push_back(Min(mfcc6subset));
	minmfcc.push_back(Min(mfcc7subset));
	minmfcc.push_back(Min(mfcc8subset));
	minmfcc.push_back(Min(mfcc9subset));
	minmfcc.push_back(Min(mfcc10subset));
	minmfcc.push_back(Min(mfcc11subset));
	minmfcc.push_back(Min(mfcc12subset));

	mindeltamfcc.push_back(Min(dmfcc1subset));
	mindeltamfcc.push_back(Min(dmfcc2subset));
	mindeltamfcc.push_back(Min(dmfcc3subset));
	mindeltamfcc.push_back(Min(dmfcc4subset));
	mindeltamfcc.push_back(Min(dmfcc5subset));
	mindeltamfcc.push_back(Min(dmfcc6subset));
	mindeltamfcc.push_back(Min(dmfcc7subset));
	mindeltamfcc.push_back(Min(dmfcc8subset));
	mindeltamfcc.push_back(Min(dmfcc9subset));
	mindeltamfcc.push_back(Min(dmfcc10subset));
	mindeltamfcc.push_back(Min(dmfcc11subset));
	mindeltamfcc.push_back(Min(dmfcc12subset));

	minspectralContrast.push_back(Min(spectralContrast1subset));
	minspectralContrast.push_back(Min(spectralContrast2subset));
	minspectralContrast.push_back(Min(spectralContrast3subset));
	minspectralContrast.push_back(Min(spectralContrast4subset));
	minspectralContrast.push_back(Min(spectralContrast5subset));
	minspectralContrast.push_back(Min(spectralContrast6subset));

	minspectralValley.push_back(Min(spectralValley1subset));
	minspectralValley.push_back(Min(spectralValley2subset));
	minspectralValley.push_back(Min(spectralValley3subset));
	minspectralValley.push_back(Min(spectralValley4subset));
	minspectralValley.push_back(Min(spectralValley5subset));
	minspectralValley.push_back(Min(spectralValley6subset));


	obs = ObservationData( Min(rmssubset), Min(peaksubset), Min(crestFactorsubset), Min(zcrsubset), Min(centroidsubset), Min(spreadsubset), Min(skewnesssubset), Min(kurtosissubset), Min(brightnesssubset), Min(rolloff85subset), Min(rolloff95subset), Min(spectralentropysubset), Min(flatnesssubset), Min(spectralcfsubset),  Min(spectralfluxsubset), minmfcc, mindeltamfcc, minspectralContrast, minspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
	obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
	m_PooledObservationDataMin.push_back(obs);

	///////Whole

	avgpeak = Average(peak);
	avgrms = Average(rms);
	avgcrestFactor = Average(crestFactor);
	avgzcr = Average(zcr);
	avgcentroid = Average(centroid);
	avgspread = Average(spread);
	avgskewness = Average(skewness);
	avgkurtosis = Average(kurtosis);
	avgbrightness = Average(brightness);
	avgrolloff85 = Average(rolloff85);
	avgrolloff95 = Average(rolloff95);
	avgspectralentropy = Average(spectralentropy); 
	avgflatness = Average(flatness);
	avgspectralcf = Average(spectralcf);
	avgspectralflux = Average(spectralflux);

	avgmfcc.clear();
	avgmfcc.push_back(Average(mfcc1));
	avgmfcc.push_back(Average(mfcc2));
	avgmfcc.push_back(Average(mfcc3));
	avgmfcc.push_back(Average(mfcc4));
	avgmfcc.push_back(Average(mfcc5));
	avgmfcc.push_back(Average(mfcc6));
	avgmfcc.push_back(Average(mfcc7));
	avgmfcc.push_back(Average(mfcc8));
	avgmfcc.push_back(Average(mfcc9));
	avgmfcc.push_back(Average(mfcc10));
	avgmfcc.push_back(Average(mfcc11));
	avgmfcc.push_back(Average(mfcc12));

	avgdeltamfcc.clear();
	avgdeltamfcc.push_back(Average(m_deltamfccs[0]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[1]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[2]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[3]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[4]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[5]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[6]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[7]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[8]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[9]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[10]));
	avgdeltamfcc.push_back(Average(m_deltamfccs[11]));

	avgspectralContrast.clear();
	avgspectralContrast.push_back(Average(spectralContrast1));
	avgspectralContrast.push_back(Average(spectralContrast2));
	avgspectralContrast.push_back(Average(spectralContrast3));
	avgspectralContrast.push_back(Average(spectralContrast4));
	avgspectralContrast.push_back(Average(spectralContrast5));
	avgspectralContrast.push_back(Average(spectralContrast6));

	avgspectralValley.clear();
	avgspectralValley.push_back(Average(spectralValley1));
	avgspectralValley.push_back(Average(spectralValley2));
	avgspectralValley.push_back(Average(spectralValley3));
	avgspectralValley.push_back(Average(spectralValley4));
	avgspectralValley.push_back(Average(spectralValley5));
	avgspectralValley.push_back(Average(spectralValley6));

	for(size_t i =0; i < m_PooledObservationDataAverage.size(); i++)
	{
		obs = ObservationData(avgrms, avgpeak, avgcrestFactor, avgzcr, avgcentroid, avgspread, avgskewness, avgkurtosis, avgbrightness, avgrolloff85, avgrolloff95, avgspectralentropy, avgflatness, avgspectralcf, avgspectralflux, avgmfcc, avgdeltamfcc, avgspectralContrast, avgspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
		obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
		m_WholeTrackObservationDataAverage.push_back(obs);

		stdmfcc.clear();
		stdmfcc.push_back(Deviation(mfcc1,avgmfcc[0]));
		stdmfcc.push_back(Deviation(mfcc2,avgmfcc[1]));
		stdmfcc.push_back(Deviation(mfcc3,avgmfcc[2]));
		stdmfcc.push_back(Deviation(mfcc4,avgmfcc[3]));
		stdmfcc.push_back(Deviation(mfcc5,avgmfcc[4]));
		stdmfcc.push_back(Deviation(mfcc6,avgmfcc[5]));
		stdmfcc.push_back(Deviation(mfcc7,avgmfcc[6]));
		stdmfcc.push_back(Deviation(mfcc8,avgmfcc[7]));
		stdmfcc.push_back(Deviation(mfcc9,avgmfcc[8]));
		stdmfcc.push_back(Deviation(mfcc10,avgmfcc[9]));
		stdmfcc.push_back(Deviation(mfcc11,avgmfcc[10]));
		stdmfcc.push_back(Deviation(mfcc12,avgmfcc[11]));

		stddeltamfcc.clear();
		stddeltamfcc.push_back(Deviation(m_deltamfccs[0], avgdeltamfcc[0]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[1], avgdeltamfcc[1]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[2], avgdeltamfcc[2]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[3], avgdeltamfcc[3]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[4], avgdeltamfcc[4]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[5], avgdeltamfcc[5]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[6], avgdeltamfcc[6]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[7], avgdeltamfcc[7]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[8], avgdeltamfcc[8]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[9], avgdeltamfcc[9]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[10], avgdeltamfcc[10]));
		stddeltamfcc.push_back(Deviation(m_deltamfccs[11], avgdeltamfcc[11]));

		stdspectralContrast.clear();
		stdspectralContrast.push_back(Deviation(spectralContrast1, avgspectralContrast[0]));
		stdspectralContrast.push_back(Deviation(spectralContrast2, avgspectralContrast[1]));
		stdspectralContrast.push_back(Deviation(spectralContrast3, avgspectralContrast[2]));
		stdspectralContrast.push_back(Deviation(spectralContrast4, avgspectralContrast[3]));
		stdspectralContrast.push_back(Deviation(spectralContrast5, avgspectralContrast[4]));
		stdspectralContrast.push_back(Deviation(spectralContrast6, avgspectralContrast[5]));

		stdspectralValley.clear();
		stdspectralValley.push_back(Deviation(spectralValley1, avgspectralValley[0]));
		stdspectralValley.push_back(Deviation(spectralValley2, avgspectralValley[1]));
		stdspectralValley.push_back(Deviation(spectralValley3, avgspectralValley[2]));
		stdspectralValley.push_back(Deviation(spectralValley4, avgspectralValley[3]));
		stdspectralValley.push_back(Deviation(spectralValley5, avgspectralValley[4]));
		stdspectralValley.push_back(Deviation(spectralValley6, avgspectralValley[5]));

		obs = ObservationData(Deviation(rms, avgrms), Deviation(peak, avgpeak), Deviation(crestFactor, avgcrestFactor), Deviation(zcr, avgzcr), Deviation(centroid, avgcentroid), Deviation(spread, avgspread), Deviation(skewness, avgskewness), Deviation(kurtosis, avgkurtosis), Deviation(brightness, avgbrightness), Deviation(rolloff85, avgrolloff85), Deviation(rolloff95, avgrolloff95), Deviation(spectralentropy, avgspectralentropy), Deviation(flatness, avgflatness), Deviation(spectralcf, avgspectralcf), Deviation(spectralflux, avgspectralflux), stdmfcc, stddeltamfcc, stdspectralContrast, stdspectralValley, 0, 0);
		obs.SetLowEnergy(0);
		m_WholeTrackObservationDataStd.push_back(obs);

		maxmfcc.clear();
		maxmfcc.push_back(Max(mfcc1));
		maxmfcc.push_back(Max(mfcc2));
		maxmfcc.push_back(Max(mfcc3));
		maxmfcc.push_back(Max(mfcc4));
		maxmfcc.push_back(Max(mfcc5));
		maxmfcc.push_back(Max(mfcc6));
		maxmfcc.push_back(Max(mfcc7));
		maxmfcc.push_back(Max(mfcc8));
		maxmfcc.push_back(Max(mfcc9));
		maxmfcc.push_back(Max(mfcc10));
		maxmfcc.push_back(Max(mfcc11));
		maxmfcc.push_back(Max(mfcc12));

		maxdeltamfcc.clear();
		maxdeltamfcc.push_back(Max(m_deltamfccs[0]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[1]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[2]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[3]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[4]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[5]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[6]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[7]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[8]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[9]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[10]));
		maxdeltamfcc.push_back(Max(m_deltamfccs[11]));

		maxspectralContrast.clear();
		maxspectralContrast.push_back(Max(spectralContrast1));
		maxspectralContrast.push_back(Max(spectralContrast2));
		maxspectralContrast.push_back(Max(spectralContrast3));
		maxspectralContrast.push_back(Max(spectralContrast4));
		maxspectralContrast.push_back(Max(spectralContrast5));
		maxspectralContrast.push_back(Max(spectralContrast6));

		maxspectralValley.clear();
		maxspectralValley.push_back(Max(spectralValley1));
		maxspectralValley.push_back(Max(spectralValley2));
		maxspectralValley.push_back(Max(spectralValley3));
		maxspectralValley.push_back(Max(spectralValley4));
		maxspectralValley.push_back(Max(spectralValley5));
		maxspectralValley.push_back(Max(spectralValley6));

		obs = ObservationData(Max(rms), Max(peak),  Max(crestFactor), Max(zcr), Max(centroid), Max(spread), Max(skewness), Max(kurtosis), Max(brightness), Max(rolloff85), Max(rolloff95), Max(spectralentropy), Max(flatness), Max(spectralcf),  Max(spectralflux), maxmfcc, maxdeltamfcc, maxspectralContrast, maxspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
		obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
		m_WholeTrackObservationDataMax.push_back(obs);

		minmfcc.clear();
		minmfcc.push_back(Min(mfcc1));
		minmfcc.push_back(Min(mfcc2));
		minmfcc.push_back(Min(mfcc3));
		minmfcc.push_back(Min(mfcc4));
		minmfcc.push_back(Min(mfcc5));
		minmfcc.push_back(Min(mfcc6));
		minmfcc.push_back(Min(mfcc7));
		minmfcc.push_back(Min(mfcc8));
		minmfcc.push_back(Min(mfcc9));
		minmfcc.push_back(Min(mfcc10));
		minmfcc.push_back(Min(mfcc11));
		minmfcc.push_back(Min(mfcc12));

		mindeltamfcc.clear();
		mindeltamfcc.push_back(Min(m_deltamfccs[0]));
		mindeltamfcc.push_back(Min(m_deltamfccs[1]));
		mindeltamfcc.push_back(Min(m_deltamfccs[2]));
		mindeltamfcc.push_back(Min(m_deltamfccs[3]));
		mindeltamfcc.push_back(Min(m_deltamfccs[4]));
		mindeltamfcc.push_back(Min(m_deltamfccs[5]));
		mindeltamfcc.push_back(Min(m_deltamfccs[6]));
		mindeltamfcc.push_back(Min(m_deltamfccs[7]));
		mindeltamfcc.push_back(Min(m_deltamfccs[8]));
		mindeltamfcc.push_back(Min(m_deltamfccs[9]));
		mindeltamfcc.push_back(Min(m_deltamfccs[10]));
		mindeltamfcc.push_back(Min(m_deltamfccs[11]));

		minspectralContrast.clear();
		minspectralContrast.push_back(Min(spectralContrast1));
		minspectralContrast.push_back(Min(spectralContrast2));
		minspectralContrast.push_back(Min(spectralContrast3));
		minspectralContrast.push_back(Min(spectralContrast4));
		minspectralContrast.push_back(Min(spectralContrast5));
		minspectralContrast.push_back(Min(spectralContrast6));

		minspectralValley.clear();
		minspectralValley.push_back(Min(spectralValley1));
		minspectralValley.push_back(Min(spectralValley2));
		minspectralValley.push_back(Min(spectralValley3));
		minspectralValley.push_back(Min(spectralValley4));
		minspectralValley.push_back(Min(spectralValley5));
		minspectralValley.push_back(Min(spectralValley6));

		obs = ObservationData(Min(rms), Min(peak),  Min(crestFactor), Min(zcr), Min(centroid), Min(spread), Min(skewness), Min(kurtosis), Min(brightness), Min(rolloff85), Min(rolloff95), Min(spectralentropy), Min(flatness), Min(spectralcf), Min(spectralflux), minmfcc, mindeltamfcc, minspectralContrast, minspectralValley, m_ObservationData[0].GetPeriodicity(), m_ObservationData[0].GetEntropyOfEnergy());
		obs.SetLowEnergy(m_ObservationData[0].GetLowEnergy());
		m_WholeTrackObservationDataMin.push_back(obs);
	}

}

void FeatureData::ComputeLowEnergyFeature()
{
	if(m_ObservationData.size() > 0)
	{
		float averageRMSForTrack = 0.0;
		float sumRMS = 0.0;
		int RMSbelowAvgCount = 0;
		float lowEnergyValue = 0.0;

		//First get average
		for(size_t i =0; i < m_ObservationData.size(); i++)
		{
			sumRMS += m_ObservationData[i].GetRMS();
		}

		averageRMSForTrack = sumRMS / m_ObservationData.size();

		//Count how many frames below average RMS.

		//Work out the Low Energy Value
		for(size_t i =0; i < m_ObservationData.size(); i++)
		{
			if(m_ObservationData[i].GetRMS() < averageRMSForTrack)
			{
				RMSbelowAvgCount++;
			}
		}

		lowEnergyValue = (((float)RMSbelowAvgCount / (float)m_ObservationData.size()) * 100);

		//Set the value for each observation
		for(size_t i =0; i < m_ObservationData.size(); i++)
		{
			m_ObservationData[i].SetLowEnergy(lowEnergyValue);
		}
	}

}

void FeatureData::ComputeDeltaMFCCs()
{
	if(m_ObservationData.size() > 0)
	{
		std::vector<float> dmfcc1;
		std::vector<float> dmfcc2;
		std::vector<float> dmfcc3;
		std::vector<float> dmfcc4;
		std::vector<float> dmfcc5;
		std::vector<float> dmfcc6;
		std::vector<float> dmfcc7;
		std::vector<float> dmfcc8;
		std::vector<float> dmfcc9;
		std::vector<float> dmfcc10;
		std::vector<float> dmfcc11;
		std::vector<float> dmfcc12;

		dmfcc1.push_back(0.0f);
		dmfcc1.push_back(0.0f);
		dmfcc2.push_back(0.0f);
		dmfcc2.push_back(0.0f);
		dmfcc3.push_back(0.0f);
		dmfcc3.push_back(0.0f);
		dmfcc4.push_back(0.0f);
		dmfcc4.push_back(0.0f);
		dmfcc5.push_back(0.0f);
		dmfcc5.push_back(0.0f);
		dmfcc6.push_back(0.0f);
		dmfcc6.push_back(0.0f);
		dmfcc7.push_back(0.0f);
		dmfcc7.push_back(0.0f);
		dmfcc8.push_back(0.0f);
		dmfcc8.push_back(0.0f);
		dmfcc9.push_back(0.0f);
		dmfcc9.push_back(0.0f);
		dmfcc10.push_back(0.0f);
		dmfcc10.push_back(0.0f);
		dmfcc11.push_back(0.0f);
		dmfcc11.push_back(0.0f);
		dmfcc12.push_back(0.0f);
		dmfcc12.push_back(0.0f);
		

		int indexminusone = -1;
		int indexplusone = 1;
		int indexminustwo = -2;
		int indexplustwo = 2;
	    //Need to start two samples ahead to gather the entire samples and not have spurious results from the MFCC 0 value

		for (size_t index = 2; index < (m_ObservationData.size() - 2); index++)
		{
			dmfcc1.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[0] - m_ObservationData[index + indexplusone].GetMFCCs()[0]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[0] - m_ObservationData[index + indexplustwo].GetMFCCs()[0]));
			dmfcc2.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[1] - m_ObservationData[index + indexplusone].GetMFCCs()[1]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[1] - m_ObservationData[index + indexplustwo].GetMFCCs()[1]));
			dmfcc3.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[2] - m_ObservationData[index + indexplusone].GetMFCCs()[2]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[2] - m_ObservationData[index + indexplustwo].GetMFCCs()[2]));
			dmfcc4.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[3] - m_ObservationData[index + indexplusone].GetMFCCs()[3]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[3] - m_ObservationData[index + indexplustwo].GetMFCCs()[3]));
			dmfcc5.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[4] - m_ObservationData[index + indexplusone].GetMFCCs()[4]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[4] - m_ObservationData[index + indexplustwo].GetMFCCs()[4]));
			dmfcc6.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[5] - m_ObservationData[index + indexplusone].GetMFCCs()[5]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[5] - m_ObservationData[index + indexplustwo].GetMFCCs()[5]));
			dmfcc7.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[6] - m_ObservationData[index + indexplusone].GetMFCCs()[6]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[6] - m_ObservationData[index + indexplustwo].GetMFCCs()[6]));
			dmfcc8.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[7] - m_ObservationData[index + indexplusone].GetMFCCs()[7]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[7] - m_ObservationData[index + indexplustwo].GetMFCCs()[7]));
			dmfcc9.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[8] - m_ObservationData[index + indexplusone].GetMFCCs()[8]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[8] - m_ObservationData[index + indexplustwo].GetMFCCs()[8]));
			dmfcc10.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[9] - m_ObservationData[index + indexplusone].GetMFCCs()[9]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[9] - m_ObservationData[index + indexplustwo].GetMFCCs()[9]));
			dmfcc11.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[10] - m_ObservationData[index + indexplusone].GetMFCCs()[10]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[10] - m_ObservationData[index + indexplustwo].GetMFCCs()[10]));
			dmfcc12.push_back(0.1f * (m_ObservationData[index + indexminusone].GetMFCCs()[11] - m_ObservationData[index + indexplusone].GetMFCCs()[11]) + 0.2f * (m_ObservationData[index + indexminustwo].GetMFCCs()[11] - m_ObservationData[index + indexplustwo].GetMFCCs()[11]));
		}

		dmfcc1.push_back(0.0f);
		dmfcc1.push_back(0.0f);
		dmfcc2.push_back(0.0f);
		dmfcc2.push_back(0.0f);
		dmfcc3.push_back(0.0f);
		dmfcc3.push_back(0.0f);
		dmfcc4.push_back(0.0f);
		dmfcc4.push_back(0.0f);
		dmfcc5.push_back(0.0f);
		dmfcc5.push_back(0.0f);
		dmfcc6.push_back(0.0f);
		dmfcc6.push_back(0.0f);
		dmfcc7.push_back(0.0f);
		dmfcc7.push_back(0.0f);
		dmfcc8.push_back(0.0f);
		dmfcc8.push_back(0.0f);
		dmfcc9.push_back(0.0f);
		dmfcc9.push_back(0.0f);
		dmfcc10.push_back(0.0f);
		dmfcc10.push_back(0.0f);
		dmfcc11.push_back(0.0f);
		dmfcc11.push_back(0.0f);
		dmfcc12.push_back(0.0f);
		dmfcc12.push_back(0.0f);

		m_deltamfccs.push_back(dmfcc1);
		m_deltamfccs.push_back(dmfcc2);
		m_deltamfccs.push_back(dmfcc3);
		m_deltamfccs.push_back(dmfcc4);
		m_deltamfccs.push_back(dmfcc5);
		m_deltamfccs.push_back(dmfcc6);
		m_deltamfccs.push_back(dmfcc7);
		m_deltamfccs.push_back(dmfcc8);
		m_deltamfccs.push_back(dmfcc9);
		m_deltamfccs.push_back(dmfcc10);
		m_deltamfccs.push_back(dmfcc11);
		m_deltamfccs.push_back(dmfcc12);
	}
}

float FeatureData::Average(std::vector<float> v)
{
	float sum = 0;

    for(size_t i = 0; i < v.size(); i++)
	{
		sum += v[i];
	}

    return sum / static_cast<float>(v.size());
}

float FeatureData::Deviation(std::vector<float> v, float ave)
{
	float E = 0;

	for(size_t i = 0; i < v.size(); i++)
	{
		E += (v[i] - ave) * (v[i] - ave);
	}
       
	return sqrt((1 / static_cast<float>(v.size())) * E);
}

float FeatureData::Max(std::vector<float> v)
{

	float max = std::numeric_limits<float>::lowest();

    for(size_t i = 0; i < v.size(); i++)
	{
		if (v[i] > max)
			max = v[i];
	}

    return max;
}

float FeatureData::Min(std::vector<float> v)
{
	float min = std::numeric_limits<float>::max();

    for(size_t i = 0; i < v.size(); i++)
	{
		if (v[i] < min)
			min = v[i];
	}

    return min;
}