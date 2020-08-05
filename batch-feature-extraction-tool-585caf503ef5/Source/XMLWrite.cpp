/*
  ==============================================================================

    XMLWrite.cpp
    Created: 1 Feb 2016 7:34:55pm
    Author:  David

  ==============================================================================
*/

#include "XMLWrite.h"
#include <ctime>
#include <fstream>

XMLWrite::XMLWrite(){};
XMLWrite::~XMLWrite(){};

static int count = 1;

void XMLWrite::Write(std::string filename, FeatureData data)
{
	std::string wholetrackfilename = filename + std::to_string(data.GetPoolingTimeFactor()) + "Sec.xml";
	std::ofstream foutWholeTrack(wholetrackfilename, std::ios::app | std::ios::out);

	juce::XmlElement featureData("FeatureData" + std::to_string(count));

	// create an inner element..
	juce::XmlElement* dataXML = new juce::XmlElement("Data");

	std::string label = data.GetLabel();
	//std::string rmsavgdata;
	//for (size_t j = 0; j < data.GetPooldedObservationDataAverage().size(); j++)
	//{
	//	rmsavgdata = rmsavgdata + ", " + std::to_string(data.GetPooldedObservationDataAverage()[j].GetRMS());
	//}

	//Whole Data

	juce::XmlElement* rms = new juce::XmlElement("rms");
	rms->setAttribute("FeatureType", "RMS");
	rms->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetRMS());
	rms->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetRMS());
	rms->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetRMS());
	rms->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetRMS());
	dataXML->addChildElement(rms);

	juce::XmlElement* peak = new juce::XmlElement("peak");
	peak->setAttribute("FeatureType", "Peak");
	peak->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetPeak());
	peak->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetPeak());
	peak->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetPeak());
	peak->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetPeak());
	dataXML->addChildElement(peak);

	juce::XmlElement* crestFactor = new juce::XmlElement("crestFactor");
	crestFactor->setAttribute("FeatureType", "CrestFactor");
	crestFactor->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetCrestFactor());
	crestFactor->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetCrestFactor());
	crestFactor->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetCrestFactor());
	crestFactor->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetCrestFactor());
	dataXML->addChildElement(crestFactor);

	juce::XmlElement* zcr = new juce::XmlElement("zcr");
	zcr->setAttribute("FeatureType", "ZCR");
	zcr->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetZCR());
	zcr->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetZCR());
	zcr->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetZCR());
	zcr->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetZCR());
	dataXML->addChildElement(zcr);

	juce::XmlElement* centroid = new juce::XmlElement("spectralCentroid");
	centroid->setAttribute("FeatureType", "SpectralCentroid");
	centroid->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetCentroid());
	centroid->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetCentroid());
	centroid->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetCentroid());
	centroid->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetCentroid());
	dataXML->addChildElement(centroid);

	juce::XmlElement* spread = new juce::XmlElement("spectralSpread");
	spread->setAttribute("FeatureType", "SpectralSpread");
	spread->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpread());
	spread->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpread());
	spread->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpread());
	spread->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpread());
	dataXML->addChildElement(spread);

	juce::XmlElement* skewness = new juce::XmlElement("spectralSkewness");
	skewness->setAttribute("FeatureType", "SpectralSkewness");
	skewness->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSkewness());
	skewness->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSkewness());
	skewness->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSkewness());
	skewness->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSkewness());
	dataXML->addChildElement(skewness);

	juce::XmlElement* kurtosis = new juce::XmlElement("spectralKurtosis");
	kurtosis->setAttribute("FeatureType", "SpectralKurtosis");
	kurtosis->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetKurtosis());
	kurtosis->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetKurtosis());
	kurtosis->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetKurtosis());
	kurtosis->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetKurtosis());
	dataXML->addChildElement(kurtosis);

	juce::XmlElement* brightness = new juce::XmlElement("spectralBrightness");
	brightness->setAttribute("FeatureType", "SpectralBrightness");
	brightness->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetBrightness());
	brightness->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetBrightness());
	brightness->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetBrightness());
	brightness->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetBrightness());
	dataXML->addChildElement(brightness);

	juce::XmlElement* flatness = new juce::XmlElement("Flatness");
	flatness->setAttribute("FeatureType", "Flatness");
	flatness->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetFlatness());
	flatness->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetFlatness());
	flatness->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetFlatness());
	flatness->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetFlatness());
	dataXML->addChildElement(flatness);

	juce::XmlElement* rolloff85 = new juce::XmlElement("rolloff85");
	rolloff85->setAttribute("FeatureType", "rolloff85");
	rolloff85->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetRollOff85());
	rolloff85->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetRollOff85());
	rolloff85->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetRollOff85());
	rolloff85->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetRollOff85());
	dataXML->addChildElement(rolloff85);

	juce::XmlElement* rolloff95 = new juce::XmlElement("rolloff95");
	rolloff95->setAttribute("FeatureType", "rolloff95");
	rolloff95->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetRollOff95());
	rolloff95->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetRollOff95());
	rolloff95->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetRollOff95());
	rolloff95->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetRollOff95());
	dataXML->addChildElement(rolloff95);

	juce::XmlElement* spectralEntropy = new juce::XmlElement("spectralEntropy");
	spectralEntropy->setAttribute("FeatureType", "spectralEntropy");
	spectralEntropy->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralEntropy());
	spectralEntropy->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralEntropy());
	spectralEntropy->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralEntropy());
	spectralEntropy->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralEntropy());
	dataXML->addChildElement(spectralEntropy);

	juce::XmlElement* spectralCrestFactor = new juce::XmlElement("spectralCrestFactor");
	spectralCrestFactor->setAttribute("FeatureType", "spectralCrestFactor");
	spectralCrestFactor->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralCF());
	spectralCrestFactor->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralCF());
	spectralCrestFactor->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralCF());
	spectralCrestFactor->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralCF());
	dataXML->addChildElement(spectralCrestFactor);

	juce::XmlElement* spectralFlux = new juce::XmlElement("spectralFlux");
	spectralFlux->setAttribute("FeatureType", "spectralFlux");
	spectralFlux->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralFlux());
	spectralFlux->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralFlux());
	spectralFlux->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralFlux());
	spectralFlux->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralFlux());
	dataXML->addChildElement(spectralFlux);

	juce::XmlElement* MFCCs = new juce::XmlElement("MFCCs");
	MFCCs->setAttribute("FeatureType", "MFCCs");

		juce::XmlElement* MFCC1 = new juce::XmlElement("MFCC1");
		MFCC1->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[0]);
		MFCC1->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[0]);
		MFCC1->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[0]);
		MFCC1->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[0]);
		juce::XmlElement* dMFCC1 = new juce::XmlElement("deltaMFCC1");
		dMFCC1->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[0]);
		dMFCC1->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[0]);
		dMFCC1->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[0]);
		dMFCC1->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[0]);

		juce::XmlElement* MFCC2 = new juce::XmlElement("MFCC2");
		MFCC2->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[1]);
		MFCC2->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[1]);
		MFCC2->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[1]);
		MFCC2->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[1]);
		juce::XmlElement* dMFCC2 = new juce::XmlElement("deltaMFCC2");
		dMFCC2->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[1]);
		dMFCC2->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[1]);
		dMFCC2->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[1]);
		dMFCC2->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[1]);

		juce::XmlElement* MFCC3 = new juce::XmlElement("MFCC3");
		MFCC3->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[2]);
		MFCC3->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[2]);
		MFCC3->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[2]);
		MFCC3->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[2]);
		juce::XmlElement* dMFCC3 = new juce::XmlElement("deltaMFCC3");
		dMFCC3->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[2]);
		dMFCC3->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[2]);
		dMFCC3->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[2]);
		dMFCC3->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[2]);

		juce::XmlElement* MFCC4 = new juce::XmlElement("MFCC4");
		MFCC4->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[3]);
		MFCC4->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[3]);
		MFCC4->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[3]);
		MFCC4->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[3]);
		juce::XmlElement* dMFCC4 = new juce::XmlElement("deltaMFCC4");
		dMFCC4->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[3]);
		dMFCC4->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[3]);
		dMFCC4->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[3]);
		dMFCC4->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[3]);

		juce::XmlElement* MFCC5 = new juce::XmlElement("MFCC5");
		MFCC5->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[4]);
		MFCC5->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[4]);
		MFCC5->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[4]);
		MFCC5->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[4]);
		juce::XmlElement* dMFCC5 = new juce::XmlElement("deltaMFCC5");
		dMFCC5->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[4]);
		dMFCC5->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[4]);
		dMFCC5->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[4]);
		dMFCC5->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[4]);

		juce::XmlElement* MFCC6 = new juce::XmlElement("MFCC6");
		MFCC6->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[5]);
		MFCC6->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[5]);
		MFCC6->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[5]);
		MFCC6->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[5]);
		juce::XmlElement* dMFCC6 = new juce::XmlElement("deltaMFCC6");
		dMFCC6->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[5]);
		dMFCC6->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[5]);
		dMFCC6->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[5]);
		dMFCC6->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[5]);

		juce::XmlElement* MFCC7 = new juce::XmlElement("MFCC7");
		MFCC7->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[6]);
		MFCC7->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[6]);
		MFCC7->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[6]);
		MFCC7->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[6]);
		juce::XmlElement* dMFCC7 = new juce::XmlElement("deltaMFCC7");
		dMFCC7->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[6]);
		dMFCC7->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[6]);
		dMFCC7->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[6]);
		dMFCC7->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[6]);

		juce::XmlElement* MFCC8 = new juce::XmlElement("MFCC8");
		MFCC8->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[7]);
		MFCC8->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[7]);
		MFCC8->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[7]);
		MFCC8->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[7]);
		juce::XmlElement* dMFCC8 = new juce::XmlElement("deltaMFCC8");
		dMFCC8->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[7]);
		dMFCC8->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[7]);
		dMFCC8->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[7]);
		dMFCC8->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[7]);

		juce::XmlElement* MFCC9 = new juce::XmlElement("MFCC9");
		MFCC9->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[8]);
		MFCC9->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[8]);
		MFCC9->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[8]);
		MFCC9->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[8]);
		juce::XmlElement* dMFCC9 = new juce::XmlElement("deltaMFCC9");
		dMFCC9->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[8]);
		dMFCC9->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[8]);
		dMFCC9->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[8]);
		dMFCC9->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[8]);

		juce::XmlElement* MFCC10 = new juce::XmlElement("MFCC10");
		MFCC10->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[9]);
		MFCC10->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[9]);
		MFCC10->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[9]);
		MFCC10->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[9]);
		juce::XmlElement* dMFCC10 = new juce::XmlElement("deltaMFCC10");
		dMFCC10->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[9]);
		dMFCC10->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[9]);
		dMFCC10->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[9]);
		dMFCC10->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[9]);

		juce::XmlElement* MFCC11 = new juce::XmlElement("MFCC11");
		MFCC11->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[10]);
		MFCC11->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[10]);
		MFCC11->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[10]);
		MFCC11->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[10]);
		juce::XmlElement* dMFCC11 = new juce::XmlElement("deltaMFCC11");
		dMFCC11->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[10]);
		dMFCC11->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[10]);
		dMFCC11->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[10]);
		dMFCC11->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[10]);

		juce::XmlElement* MFCC12 = new juce::XmlElement("MFCC12");
		MFCC12->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetMFCCs()[11]);
		MFCC12->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetMFCCs()[11]);
		MFCC12->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetMFCCs()[11]);
		MFCC12->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetMFCCs()[11]);
		juce::XmlElement* dMFCC12 = new juce::XmlElement("deltaMFCC12");
		dMFCC12->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetDeltaMFCCs()[11]);
		dMFCC12->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[11]);
		dMFCC12->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetDeltaMFCCs()[11]);
		dMFCC12->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetDeltaMFCCs()[11]);


	MFCCs->addChildElement(MFCC1);
	MFCCs->addChildElement(dMFCC1);
	MFCCs->addChildElement(MFCC2);
	MFCCs->addChildElement(dMFCC2);
	MFCCs->addChildElement(MFCC3);
	MFCCs->addChildElement(dMFCC3);
	MFCCs->addChildElement(MFCC4);
	MFCCs->addChildElement(dMFCC4);
	MFCCs->addChildElement(MFCC5);
	MFCCs->addChildElement(dMFCC5);
	MFCCs->addChildElement(MFCC6);
	MFCCs->addChildElement(dMFCC6);
	MFCCs->addChildElement(MFCC7);
	MFCCs->addChildElement(dMFCC7);
	MFCCs->addChildElement(MFCC8);
	MFCCs->addChildElement(dMFCC8);
	MFCCs->addChildElement(MFCC9);
	MFCCs->addChildElement(dMFCC9);
	MFCCs->addChildElement(MFCC10);
	MFCCs->addChildElement(dMFCC10);
	MFCCs->addChildElement(MFCC11);
	MFCCs->addChildElement(dMFCC11);
	MFCCs->addChildElement(MFCC12);
	MFCCs->addChildElement(dMFCC12);
	dataXML->addChildElement(MFCCs);

	juce::XmlElement* spectralContrast = new juce::XmlElement("spectralContrast");
	spectralContrast->setAttribute("FeatureType", "spectralContrast");

	juce::XmlElement* sc1 = new juce::XmlElement("SC1");
	sc1->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[0]);
	sc1->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[0]);
	sc1->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[0]);
	sc1->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[0]);

	juce::XmlElement* sc2 = new juce::XmlElement("SC2");
	sc2->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[1]);
	sc2->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[1]);
	sc2->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[1]);
	sc2->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[1]);

	juce::XmlElement* sc3 = new juce::XmlElement("SC3");
	sc3->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[2]);
	sc3->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[2]);
	sc3->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[2]);
	sc3->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[2]);

	juce::XmlElement* sc4 = new juce::XmlElement("SC4");
	sc4->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[3]);
	sc4->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[3]);
	sc4->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[3]);
	sc4->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[3]);

	juce::XmlElement* sc5 = new juce::XmlElement("SC5");
	sc5->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[4]);
	sc5->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[4]);
	sc5->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[4]);
	sc5->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[4]);

	juce::XmlElement* sc6 = new juce::XmlElement("SC6");
	sc6->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralContrast()[5]);
	sc6->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[5]);
	sc6->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralContrast()[5]);
	sc6->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralContrast()[5]);

	spectralContrast->addChildElement(sc1);
	spectralContrast->addChildElement(sc2);
	spectralContrast->addChildElement(sc3);
	spectralContrast->addChildElement(sc4);
	spectralContrast->addChildElement(sc5);
	spectralContrast->addChildElement(sc6);
	dataXML->addChildElement(spectralContrast);

	juce::XmlElement* spectralValley = new juce::XmlElement("spectralValley");
	spectralValley->setAttribute("FeatureType", "spectralValley");

	juce::XmlElement* sv1 = new juce::XmlElement("SV1");
	sv1->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[0]);
	sv1->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[0]);
	sv1->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[0]);
	sv1->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[0]);

	juce::XmlElement* sv2 = new juce::XmlElement("SV2");
	sv2->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[1]);
	sv2->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[1]);
	sv2->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[1]);
	sv2->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[1]);

	juce::XmlElement* sv3 = new juce::XmlElement("SV3");
	sv3->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[2]);
	sv3->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[2]);
	sv3->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[2]);
	sv3->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[2]);

	juce::XmlElement* sv4 = new juce::XmlElement("SV4");
	sv4->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[3]);
	sv4->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[3]);
	sv4->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[3]);
	sv4->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[3]);

	juce::XmlElement* sv5 = new juce::XmlElement("SV5");
	sv5->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[4]);
	sv5->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[4]);
	sv5->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[4]);
	sv5->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[4]);

	juce::XmlElement* sv6 = new juce::XmlElement("SV6");
	sv6->setAttribute("Average", data.GetPooldedObservationDataAverage()[0].GetSpectralValley()[5]);
	sv6->setAttribute("StandardDeviation", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[5]);
	sv6->setAttribute("Maximum", data.GetPooldedObservationDataMax()[0].GetSpectralValley()[5]);
	sv6->setAttribute("Minimum", data.GetPooldedObservationDataStd()[0].GetSpectralValley()[5]);

	spectralValley->addChildElement(sv1);
	spectralValley->addChildElement(sv2);
	spectralValley->addChildElement(sv3);
	spectralValley->addChildElement(sv4);
	spectralValley->addChildElement(sv5);
	spectralValley->addChildElement(sv6);
	dataXML->addChildElement(spectralValley);

	juce::XmlElement* lowEnergy = new juce::XmlElement("lowEnergy");
	lowEnergy->setAttribute("FeatureType", "lowEnergy");
	lowEnergy->setAttribute("Value", data.GetPooldedObservationDataAverage()[0].GetLowEnergy());
	dataXML->addChildElement(lowEnergy);

	juce::XmlElement* periodicity = new juce::XmlElement("periodicity");
	periodicity->setAttribute("FeatureType", "periodicity");
	periodicity->setAttribute("Value", data.GetPooldedObservationDataAverage()[0].GetPeriodicity());
	dataXML->addChildElement(periodicity);

	juce::XmlElement* entropyOfEnergy = new juce::XmlElement("entropyOfEnergy");
	entropyOfEnergy->setAttribute("FeatureType", "entropyOfEnergy");
	entropyOfEnergy->setAttribute("Value", data.GetPooldedObservationDataAverage()[0].GetEntropyOfEnergy());
	dataXML->addChildElement(entropyOfEnergy);


	dataXML->setAttribute("Label", label);
	featureData.addChildElement(dataXML);


	if (foutWholeTrack.is_open())
	{

		// now we can turn the whole thing into a text document..
		juce::String myXmlDoc = featureData.createDocument(juce::String::empty);
		foutWholeTrack << myXmlDoc.toStdString();

	}
	else
	{
		std::cout << "ERROR: Can't write to .csv.";
	}

	foutWholeTrack.close();

	std::string dave = "Files written: " + std::to_string(count) + "  Obs Data Size:" + std::to_string(data.GetPooldedObservationDataAverage().size()) + "\n";
	//	 OutputDebugString(dave.c_str());
	count++;

}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string XMLWrite::currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", &tstruct);

	return buf;
}