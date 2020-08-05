/*
  ==============================================================================

    WriteCSV.cpp
    Created: 29 Aug 2014 3:57:27pm
    Author:  david.ronan

  ==============================================================================
*/

#include "WriteCSV.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
//#include <windows.h>

WriteCSV::WriteCSV(){};
WriteCSV::~WriteCSV(){};

static int count = 1;

void WriteCSV::Write(std::string filename, FeatureData data)
{
	//Pooled
	std::string pooledfilename = filename + "Pooled" + std::to_string(data.GetPoolingTimeFactor()) + "Sec.csv";
	std::ofstream foutPooled(pooledfilename, std::ios::app|std::ios::out);

	std::vector<ObservationData> observationDataAverage = data.GetPooldedObservationDataAverage();
	std::vector<ObservationData> observationDataStd = data.GetPooldedObservationDataStd();
	std::vector<ObservationData> observationDataMax = data.GetPooldedObservationDataMax();
	std::vector<ObservationData> observationDataMin = data.GetPooldedObservationDataMin();


	std::string label = data.GetLabel();

	if (foutPooled.is_open())
	{
		for(size_t j = 0; j < observationDataAverage.size(); j++)
		{
			foutPooled
				<< observationDataAverage[0].GetRMS() << ','
				<< observationDataStd[0].GetRMS() << ','
				<< observationDataMax[0].GetRMS() << ','
				<< observationDataMin[0].GetRMS() << ','
				<< observationDataAverage[0].GetPeak() << ','
				<< observationDataStd[0].GetPeak() << ','
				<< observationDataMax[0].GetPeak() << ','
				<< observationDataMin[0].GetPeak() << ','
				<< observationDataAverage[0].GetCrestFactor() << ','
				<< observationDataStd[0].GetCrestFactor() << ','
				<< observationDataMax[0].GetCrestFactor() << ','
				<< observationDataMin[0].GetCrestFactor() << ','
				<< observationDataAverage[0].GetZCR() << ','
				<< observationDataStd[0].GetZCR() << ','
				<< observationDataMax[0].GetZCR() << ','
				<< observationDataMin[0].GetZCR() << ','
				<< observationDataAverage[0].GetCentroid() << ','
				<< observationDataStd[0].GetCentroid() << ','
				<< observationDataMax[0].GetCentroid() << ','
				<< observationDataMin[0].GetCentroid() << ','
				<< observationDataAverage[0].GetSpread() << ','
				<< observationDataStd[0].GetSpread() << ','
				<< observationDataMax[0].GetSpread() << ','
				<< observationDataMin[0].GetSpread() << ','
				<< observationDataAverage[0].GetSkewness() << ','
				<< observationDataStd[0].GetSkewness() << ','
				<< observationDataMax[0].GetSkewness() << ','
				<< observationDataMin[0].GetSkewness() << ','
				<< observationDataAverage[0].GetKurtosis() << ','
				<< observationDataStd[0].GetKurtosis() << ','
				<< observationDataMax[0].GetKurtosis() << ','
				<< observationDataMin[0].GetKurtosis() << ','
				<< observationDataAverage[0].GetBrightness() << ','
				<< observationDataStd[0].GetBrightness() << ','
				<< observationDataMax[0].GetBrightness() << ','
				<< observationDataMin[0].GetBrightness() << ','
				<< observationDataAverage[0].GetFlatness() << ','
				<< observationDataStd[0].GetFlatness() << ','
				<< observationDataMax[0].GetFlatness() << ','
				<< observationDataMin[0].GetFlatness() << ','
				<< observationDataAverage[0].GetRollOff85() << ','
				<< observationDataStd[0].GetRollOff85() << ','
				<< observationDataMax[0].GetRollOff85() << ','
				<< observationDataMin[0].GetRollOff85() << ','
				<< observationDataAverage[0].GetRollOff95() << ','
				<< observationDataStd[0].GetRollOff95() << ','
				<< observationDataMax[0].GetRollOff95() << ','
				<< observationDataMin[0].GetRollOff95() << ','
				<< observationDataAverage[0].GetSpectralEntropy() << ','
				<< observationDataStd[0].GetSpectralEntropy() << ','
				<< observationDataMax[0].GetSpectralEntropy() << ','
				<< observationDataMin[0].GetSpectralEntropy() << ','
				<< observationDataAverage[0].GetSpectralCF() << ','
				<< observationDataStd[0].GetSpectralCF() << ','
				<< observationDataMax[0].GetSpectralCF() << ','
				<< observationDataMin[0].GetSpectralCF() << ','
				<< observationDataAverage[0].GetSpectralFlux() << ','
				<< observationDataStd[0].GetSpectralFlux() << ','
				<< observationDataMax[0].GetSpectralFlux() << ','
				<< observationDataMin[0].GetSpectralFlux() << ','
				<< observationDataAverage[0].GetMFCCs()[0] << ','
				<< observationDataStd[0].GetMFCCs()[0] << ','
				<< observationDataMax[0].GetMFCCs()[0] << ','
				<< observationDataMin[0].GetMFCCs()[0] << ','
				<< observationDataAverage[0].GetMFCCs()[1] << ','
				<< observationDataStd[0].GetMFCCs()[1] << ','
				<< observationDataMax[0].GetMFCCs()[1] << ','
				<< observationDataMin[0].GetMFCCs()[1] << ','
				<< observationDataAverage[0].GetMFCCs()[2] << ','
				<< observationDataStd[0].GetMFCCs()[2] << ','
				<< observationDataMax[0].GetMFCCs()[2] << ','
				<< observationDataMin[0].GetMFCCs()[2] << ','
				<< observationDataAverage[0].GetMFCCs()[3] << ','
				<< observationDataStd[0].GetMFCCs()[3] << ','
				<< observationDataMax[0].GetMFCCs()[3] << ','
				<< observationDataMin[0].GetMFCCs()[3] << ','
				<< observationDataAverage[0].GetMFCCs()[4] << ','
				<< observationDataStd[0].GetMFCCs()[4] << ','
				<< observationDataMax[0].GetMFCCs()[4] << ','
				<< observationDataMin[0].GetMFCCs()[4] << ','
				<< observationDataAverage[0].GetMFCCs()[5] << ','
				<< observationDataStd[0].GetMFCCs()[5] << ','
				<< observationDataMax[0].GetMFCCs()[5] << ','
				<< observationDataMin[0].GetMFCCs()[5] << ','
				<< observationDataAverage[0].GetMFCCs()[6] << ','
				<< observationDataStd[0].GetMFCCs()[6] << ','
				<< observationDataMax[0].GetMFCCs()[6] << ','
				<< observationDataMin[0].GetMFCCs()[6] << ','
				<< observationDataAverage[0].GetMFCCs()[7] << ','
				<< observationDataStd[0].GetMFCCs()[7] << ','
				<< observationDataMax[0].GetMFCCs()[7] << ','
				<< observationDataMin[0].GetMFCCs()[7] << ','
				<< observationDataAverage[0].GetMFCCs()[8] << ','
				<< observationDataStd[0].GetMFCCs()[8] << ','
				<< observationDataMax[0].GetMFCCs()[8] << ','
				<< observationDataMin[0].GetMFCCs()[8] << ','
				<< observationDataAverage[0].GetMFCCs()[9] << ','
				<< observationDataStd[0].GetMFCCs()[9] << ','
				<< observationDataMax[0].GetMFCCs()[9] << ','
				<< observationDataMin[0].GetMFCCs()[9] << ','
				<< observationDataAverage[0].GetMFCCs()[10] << ','
				<< observationDataStd[0].GetMFCCs()[10] << ','
				<< observationDataMax[0].GetMFCCs()[10] << ','
				<< observationDataMin[0].GetMFCCs()[10] << ','
				<< observationDataAverage[0].GetMFCCs()[11] << ','
				<< observationDataStd[0].GetMFCCs()[11] << ','
				<< observationDataMax[0].GetMFCCs()[11] << ','
				<< observationDataMin[0].GetMFCCs()[11] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[0] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[0] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[0] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[0] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[1] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[1] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[1] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[1] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[2] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[2] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[2] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[2] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[3] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[3] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[3] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[3] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[4] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[4] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[4] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[4] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[5] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[5] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[5] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[5] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[6] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[6] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[6] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[6] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[7] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[7] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[7] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[7] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[8] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[8] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[8] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[8] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[9] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[9] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[9] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[9] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[10] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[10] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[10] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[10] << ','
				<< observationDataAverage[0].GetDeltaMFCCs()[11] << ','
				<< observationDataStd[0].GetDeltaMFCCs()[11] << ','
				<< observationDataMax[0].GetDeltaMFCCs()[11] << ','
				<< observationDataMin[0].GetDeltaMFCCs()[11] << ','
				<< observationDataAverage[0].GetSpectralContrast()[0] << ','
				<< observationDataStd[0].GetSpectralContrast()[0] << ','
				<< observationDataMax[0].GetSpectralContrast()[0] << ','
				<< observationDataMin[0].GetSpectralContrast()[0] << ','
				<< observationDataAverage[0].GetSpectralContrast()[1] << ','
				<< observationDataStd[0].GetSpectralContrast()[1] << ','
				<< observationDataMax[0].GetSpectralContrast()[1] << ','
				<< observationDataMin[0].GetSpectralContrast()[1] << ','
				<< observationDataAverage[0].GetSpectralContrast()[2] << ','
				<< observationDataStd[0].GetSpectralContrast()[2] << ','
				<< observationDataMax[0].GetSpectralContrast()[2] << ','
				<< observationDataMin[0].GetSpectralContrast()[2] << ','
				<< observationDataAverage[0].GetSpectralContrast()[3] << ','
				<< observationDataStd[0].GetSpectralContrast()[3] << ','
				<< observationDataMax[0].GetSpectralContrast()[3] << ','
				<< observationDataMin[0].GetSpectralContrast()[3] << ','
				<< observationDataAverage[0].GetSpectralContrast()[4] << ','
				<< observationDataStd[0].GetSpectralContrast()[4] << ','
				<< observationDataMax[0].GetSpectralContrast()[4] << ','
				<< observationDataMin[0].GetSpectralContrast()[4] << ','
				<< observationDataAverage[0].GetSpectralContrast()[5] << ','
				<< observationDataStd[0].GetSpectralContrast()[5] << ','
				<< observationDataMax[0].GetSpectralContrast()[5] << ','
				<< observationDataMin[0].GetSpectralContrast()[5] << ','
				<< observationDataAverage[0].GetSpectralValley()[0] << ','
				<< observationDataStd[0].GetSpectralValley()[0] << ','
				<< observationDataMax[0].GetSpectralValley()[0] << ','
				<< observationDataMin[0].GetSpectralValley()[0] << ','
				<< observationDataAverage[0].GetSpectralValley()[1] << ','
				<< observationDataStd[0].GetSpectralValley()[1] << ','
				<< observationDataMax[0].GetSpectralValley()[1] << ','
				<< observationDataMin[0].GetSpectralValley()[1] << ','
				<< observationDataAverage[0].GetSpectralValley()[2] << ','
				<< observationDataStd[0].GetSpectralValley()[2] << ','
				<< observationDataMax[0].GetSpectralValley()[2] << ','
				<< observationDataMin[0].GetSpectralValley()[2] << ','
				<< observationDataAverage[0].GetSpectralValley()[3] << ','
				<< observationDataStd[0].GetSpectralValley()[3] << ','
				<< observationDataMax[0].GetSpectralValley()[3] << ','
				<< observationDataMin[0].GetSpectralValley()[3] << ','
				<< observationDataAverage[0].GetSpectralValley()[4] << ','
				<< observationDataStd[0].GetSpectralValley()[4] << ','
				<< observationDataMax[0].GetSpectralValley()[4] << ','
				<< observationDataMin[0].GetSpectralValley()[4] << ','
				<< observationDataAverage[0].GetSpectralValley()[5] << ','
				<< observationDataStd[0].GetSpectralValley()[5] << ','
				<< observationDataMax[0].GetSpectralValley()[5] << ','
				<< observationDataMin[0].GetSpectralValley()[5] << ','
				<< observationDataAverage[0].GetLowEnergy() << ','
				<< observationDataAverage[0].GetPeriodicity() << ','
				<< observationDataAverage[0].GetEntropyOfEnergy() << ','
				<< label << ',' ;
			foutPooled << "\n";
		}
	}
	else
	{
		std::cout << "ERROR: Can't write to .csv.";
	}

	 foutPooled.close();

	//WholeTrack

	std::string wholetrackfilename = filename + "Whole" + std::to_string(data.GetPoolingTimeFactor()) + "Sec.csv";
	std::ofstream foutWholeTrack(wholetrackfilename, std::ios::app|std::ios::out);

	std::vector<ObservationData> wholeTrackobservationDataAverage = data.GetWholeTrackObservationDataAverage();
	std::vector<ObservationData> wholeTrackobservationDataStd = data.GetWholeTrackObservationDataStd();
	std::vector<ObservationData> wholeTrackobservationDataMax = data.GetWholeTrackObservationDataMax();
	std::vector<ObservationData> wholeTrackobservationDataMin = data.GetWholeTrackObservationDataMin();

	if (foutWholeTrack.is_open())
	{
//		for(size_t j = 0; j < wholeTrackobservationDataAverage.size(); j++)
		{
			foutWholeTrack
				<< wholeTrackobservationDataAverage[0].GetRMS() << ','//1
				<< wholeTrackobservationDataStd[0].GetRMS() << ','//2
				<< wholeTrackobservationDataMax[0].GetRMS() << ','//3
				<< wholeTrackobservationDataMin[0].GetRMS() << ','//4
				<< wholeTrackobservationDataAverage[0].GetPeak() << ','//5
				<< wholeTrackobservationDataStd[0].GetPeak() << ','//6
				<< wholeTrackobservationDataMax[0].GetPeak() << ','//7
				<< wholeTrackobservationDataMin[0].GetPeak() << ','//8
				<< wholeTrackobservationDataAverage[0].GetCrestFactor() << ',' //9
				<< wholeTrackobservationDataStd[0].GetCrestFactor() << ',' //10
				<< wholeTrackobservationDataMax[0].GetCrestFactor() << ',' //11
				<< wholeTrackobservationDataMin[0].GetCrestFactor() << ',' //12
				<< wholeTrackobservationDataAverage[0].GetZCR() << ',' //13
				<< wholeTrackobservationDataStd[0].GetZCR() << ',' //14
				<< wholeTrackobservationDataMax[0].GetZCR()<< ',' //15
				<< wholeTrackobservationDataMin[0].GetZCR()<< ',' //16
				<< wholeTrackobservationDataAverage[0].GetCentroid() << ',' //17
				<< wholeTrackobservationDataStd[0].GetCentroid() << ','  //18
				<< wholeTrackobservationDataMax[0].GetCentroid() << ',' //19
				<< wholeTrackobservationDataMin[0].GetCentroid() << ',' //20
				<< wholeTrackobservationDataAverage[0].GetSpread() << ',' //21
				<< wholeTrackobservationDataStd[0].GetSpread() << ',' //22
				<< wholeTrackobservationDataMax[0].GetSpread() << ',' //23
				<< wholeTrackobservationDataMin[0].GetSpread() << ',' //24
				<< wholeTrackobservationDataAverage[0].GetSkewness() << ',' //25
				<< wholeTrackobservationDataStd[0].GetSkewness() << ',' //26
				<< wholeTrackobservationDataMax[0].GetSkewness() << ',' //27
				<< wholeTrackobservationDataMin[0].GetSkewness() << ',' //28
				<< wholeTrackobservationDataAverage[0].GetKurtosis() << ',' //29
				<< wholeTrackobservationDataStd[0].GetKurtosis() << ',' //30
				<< wholeTrackobservationDataMax[0].GetKurtosis() << ',' //31
				<< wholeTrackobservationDataMin[0].GetKurtosis() << ',' //32
				<< wholeTrackobservationDataAverage[0].GetBrightness() << ',' //33
				<< wholeTrackobservationDataStd[0].GetBrightness() << ',' //34
				<< wholeTrackobservationDataMax[0].GetBrightness() << ','  //35
				<< wholeTrackobservationDataMin[0].GetBrightness() << ',' //36
				<< wholeTrackobservationDataAverage[0].GetFlatness() << ',' //37
				<< wholeTrackobservationDataStd[0].GetFlatness() << ',' //38
				<< wholeTrackobservationDataMax[0].GetFlatness() << ','//39
				<< wholeTrackobservationDataMin[0].GetFlatness() << ','//40
				<< wholeTrackobservationDataAverage[0].GetRollOff85() << ',' //41
				<< wholeTrackobservationDataStd[0].GetRollOff85() << ','  //42
				<< wholeTrackobservationDataMax[0].GetRollOff85() << ','  //43
				<< wholeTrackobservationDataMin[0].GetRollOff85() << ','  //44
				<< wholeTrackobservationDataAverage[0].GetRollOff95() << ','  //45
				<< wholeTrackobservationDataStd[0].GetRollOff95() << ','  //46
				<< wholeTrackobservationDataMax[0].GetRollOff95() << ','  //47
				<< wholeTrackobservationDataMin[0].GetRollOff95() << ','  //48
				<< wholeTrackobservationDataAverage[0].GetSpectralEntropy() << ','//49
				<< wholeTrackobservationDataStd[0].GetSpectralEntropy() << ',' //50
				<< wholeTrackobservationDataMax[0].GetSpectralEntropy() << ','//51
				<< wholeTrackobservationDataMin[0].GetSpectralEntropy() << ','//52
				<< wholeTrackobservationDataAverage[0].GetSpectralCF() << ','//53
				<< wholeTrackobservationDataStd[0].GetSpectralCF() << ',' //54
				<< wholeTrackobservationDataMax[0].GetSpectralCF() << ','//55
				<< wholeTrackobservationDataMin[0].GetSpectralCF() << ','//56
				<< wholeTrackobservationDataAverage[0].GetSpectralFlux() << ','//57
				<< wholeTrackobservationDataStd[0].GetSpectralFlux() << ',' //58
				<< wholeTrackobservationDataMax[0].GetSpectralFlux() << ','//59
				<< wholeTrackobservationDataMin[0].GetSpectralFlux() << ','//60
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[0] << ','//61
				<< wholeTrackobservationDataStd[0].GetMFCCs()[0] << ',' //62
				<< wholeTrackobservationDataMax[0].GetMFCCs()[0] << ',' //47
				<< wholeTrackobservationDataMin[0].GetMFCCs()[0] << ',' //48
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[1] << ',' //49
				<< wholeTrackobservationDataStd[0].GetMFCCs()[1] << ',' //50
				<< wholeTrackobservationDataMax[0].GetMFCCs()[1] << ',' //51
				<< wholeTrackobservationDataMin[0].GetMFCCs()[1] << ',' //52
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[2] << ',' //53
				<< wholeTrackobservationDataStd[0].GetMFCCs()[2] << ',' //54
				<< wholeTrackobservationDataMax[0].GetMFCCs()[2] << ',' //55
				<< wholeTrackobservationDataMin[0].GetMFCCs()[2] << ',' //56
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[3] << ',' //57
				<< wholeTrackobservationDataStd[0].GetMFCCs()[3] << ',' //58
				<< wholeTrackobservationDataMax[0].GetMFCCs()[3] << ',' //59
				<< wholeTrackobservationDataMin[0].GetMFCCs()[3] << ',' //60
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[4] << ',' //61
				<< wholeTrackobservationDataStd[0].GetMFCCs()[4] << ',' //62
				<< wholeTrackobservationDataMax[0].GetMFCCs()[4] << ',' //63
				<< wholeTrackobservationDataMin[0].GetMFCCs()[4] << ',' //64
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[5] << ',' //65
				<< wholeTrackobservationDataStd[0].GetMFCCs()[5] << ',' //66
				<< wholeTrackobservationDataMax[0].GetMFCCs()[5] << ',' //67
				<< wholeTrackobservationDataMin[0].GetMFCCs()[5] << ',' //68
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[6] << ',' //69
				<< wholeTrackobservationDataStd[0].GetMFCCs()[6] << ',' //70
				<< wholeTrackobservationDataMax[0].GetMFCCs()[6] << ',' //71
				<< wholeTrackobservationDataMin[0].GetMFCCs()[6] << ',' //72
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[7] << ',' //73
				<< wholeTrackobservationDataStd[0].GetMFCCs()[7] << ',' //74
				<< wholeTrackobservationDataMax[0].GetMFCCs()[7] << ',' //75
				<< wholeTrackobservationDataMin[0].GetMFCCs()[7] << ',' //76
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[8] << ',' //77
				<< wholeTrackobservationDataStd[0].GetMFCCs()[8] << ',' //78
				<< wholeTrackobservationDataMax[0].GetMFCCs()[8] << ',' //79
				<< wholeTrackobservationDataMin[0].GetMFCCs()[8] << ',' //80
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[9] << ',' //81
				<< wholeTrackobservationDataStd[0].GetMFCCs()[9] << ',' //82
				<< wholeTrackobservationDataMax[0].GetMFCCs()[9] << ',' //83
				<< wholeTrackobservationDataMin[0].GetMFCCs()[9] << ',' //84
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[10] << ',' //85
				<< wholeTrackobservationDataStd[0].GetMFCCs()[10] << ',' //86
				<< wholeTrackobservationDataMax[0].GetMFCCs()[10] << ',' //87
				<< wholeTrackobservationDataMin[0].GetMFCCs()[10] << ',' //88
				<< wholeTrackobservationDataAverage[0].GetMFCCs()[11] << ',' //89
				<< wholeTrackobservationDataStd[0].GetMFCCs()[11] << ',' //90
				<< wholeTrackobservationDataMax[0].GetMFCCs()[11] << ',' //91
				<< wholeTrackobservationDataMin[0].GetMFCCs()[11] << ',' //92
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[0] << ','//45
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[0] << ',' //46
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[0] << ',' //47
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[0] << ',' //48
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[1] << ',' //49
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[1] << ',' //50
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[1] << ',' //51
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[1] << ',' //52
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[2] << ',' //53
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[2] << ',' //54
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[2] << ',' //55
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[2] << ',' //56
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[3] << ',' //57
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[3] << ',' //58
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[3] << ',' //59
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[3] << ',' //60
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[4] << ',' //61
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[4] << ',' //62
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[4] << ',' //63
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[4] << ',' //64
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[5] << ',' //65
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[5] << ',' //66
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[5] << ',' //67
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[5] << ',' //68
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[6] << ',' //69
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[6] << ',' //70
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[6] << ',' //71
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[6] << ',' //72
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[7] << ',' //73
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[7] << ',' //74
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[7] << ',' //75
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[7] << ',' //76
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[8] << ',' //77
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[8] << ',' //78
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[8] << ',' //79
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[8] << ',' //80
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[9] << ',' //81
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[9] << ',' //82
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[9] << ',' //83
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[9] << ',' //84
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[10] << ',' //85
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[10] << ',' //86
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[10] << ',' //87
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[10] << ',' //88
				<< wholeTrackobservationDataAverage[0].GetDeltaMFCCs()[11] << ',' //89
				<< wholeTrackobservationDataStd[0].GetDeltaMFCCs()[11] << ',' //90
				<< wholeTrackobservationDataMax[0].GetDeltaMFCCs()[11] << ',' //91
				<< wholeTrackobservationDataMin[0].GetDeltaMFCCs()[11] << ',' //92
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[0] << ','//61
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[0] << ',' //62
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[0] << ',' //47
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[0] << ',' //48
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[1] << ',' //49
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[1] << ',' //50
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[1] << ',' //51
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[1] << ',' //52
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[2] << ',' //53
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[2] << ',' //54
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[2] << ',' //55
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[2] << ',' //56
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[3] << ',' //57
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[3] << ',' //58
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[3] << ',' //59
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[3] << ',' //60
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[4] << ',' //61
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[4] << ',' //62
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[4] << ',' //63
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[4] << ',' //64
				<< wholeTrackobservationDataAverage[0].GetSpectralContrast()[5] << ',' //65
				<< wholeTrackobservationDataStd[0].GetSpectralContrast()[5] << ',' //66
				<< wholeTrackobservationDataMax[0].GetSpectralContrast()[5] << ',' //67
				<< wholeTrackobservationDataMin[0].GetSpectralContrast()[5] << ',' //68
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[0] << ','//61
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[0] << ',' //62
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[0] << ',' //47
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[0] << ',' //48
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[1] << ',' //49
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[1] << ',' //50
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[1] << ',' //51
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[1] << ',' //52
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[2] << ',' //53
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[2] << ',' //54
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[2] << ',' //55
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[2] << ',' //56
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[3] << ',' //57
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[3] << ',' //58
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[3] << ',' //59
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[3] << ',' //60
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[4] << ',' //61
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[4] << ',' //62
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[4] << ',' //63
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[4] << ',' //64
				<< wholeTrackobservationDataAverage[0].GetSpectralValley()[5] << ',' //65
				<< wholeTrackobservationDataStd[0].GetSpectralValley()[5] << ',' //66
				<< wholeTrackobservationDataMax[0].GetSpectralValley()[5] << ',' //67
				<< wholeTrackobservationDataMin[0].GetSpectralValley()[5] << ',' //68
				<< wholeTrackobservationDataAverage[0].GetLowEnergy() << ',' //93
				<< wholeTrackobservationDataAverage[0].GetPeriodicity() << ',' //94
				<< wholeTrackobservationDataAverage[0].GetEntropyOfEnergy() << ',' //95
				<< label << ',' ;
			foutWholeTrack << "\n";
		}
	}
	else
	{
		std::cout << "ERROR: Can't write to .csv.";
	}

	 foutWholeTrack.close();

	 std::string dave = "Files written: " + std::to_string(count) + "  Obs Data Size:" + std::to_string(wholeTrackobservationDataAverage.size())+  "\n";
//	 OutputDebugString(dave.c_str());
	 count++;
};

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string WriteCSV::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", &tstruct);

    return buf;
}
