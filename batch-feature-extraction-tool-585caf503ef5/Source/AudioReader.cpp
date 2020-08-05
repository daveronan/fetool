/*
  ==============================================================================

    AudioReader.cpp
    Created: 27 Aug 2014 3:17:10pm
    Author:  david.ronan

  ==============================================================================
*/




#include "AudioReader.h"
#include "WriteCSV.h"
#include <iostream>
#include <vector>

#define ENERGYSEARCHTIME 3
#define SAMPLERATE 22050.0f
#include "XMLWrite.h"

AudioReader::AudioReader()
{

};

AudioReader::~AudioReader()
{

};

std::vector<FeatureData> AudioReader::Read(AudioFileData audioFileData, float poolTimeSecs, int analysisWindowSize)
{
	WriteCSV writeCSV = WriteCSV();
	XMLWrite xmlWrite = XMLWrite();
	std::vector<FeatureData> featureData = std::vector<FeatureData>();
	std::string CSVFileName = "..\\FeatureData" + writeCSV.currentDateTime();

	vector<string> audioFileNames = audioFileData.GetFileNames();
	vector<string> labels = audioFileData.GetLabels();

	AudioFormatManager m_formatManager;
    m_formatManager.registerBasicFormats();
	m_AudioSourceFeatureExtractor.Initialise(SAMPLERATE);

	for(size_t i=0; i<audioFileNames.size(); i++)
	{
		float percentcomplete = static_cast<float>(i) / static_cast<float>(audioFileNames.size()) * 100.0f;

		std::string outputStr = "Extracting features for " + audioFileNames[i] + "\n" +  std::to_string(percentcomplete) + "% complete...";
		cout << outputStr;
	
		//Create file from    our audio data
		File audioFile(audioFileNames[i].c_str());

		unique_ptr<AudioFormatReader> audioFileReader(m_formatManager.createReaderFor(audioFile));

		if(audioFileReader != nullptr)
		{
			float fSampleRate		= static_cast<float>(audioFileReader->sampleRate);
			int iLengthInSamples  = static_cast<int>(audioFileReader->lengthInSamples);
			int iNumOfChannels    = audioFileReader->numChannels;

			if (fSampleRate != 22050.0f)
			{
				cout << "\n\n\nERROR: File is not the required 22050 Hz sample rate.!!!\n\n\n";
			}

			//Get loudest 30 secs. of audio
			int numOfSamplesToCollect = static_cast<int>(analysisWindowSize * fSampleRate);

			if(iLengthInSamples <= numOfSamplesToCollect)
			{
				numOfSamplesToCollect = iLengthInSamples;
			}

			//Length of the full track in stereo;
			int* destSamples[2] = { nullptr };
			unique_ptr<int> L(new int[iLengthInSamples]);
			memset(L.get(), 0, iLengthInSamples);
			destSamples[0] = L.get();
			destSamples[1] = L.get();

			
			//30 sec clips to check energy levels
			std::vector<float> destSamplesFloat = std::vector<float>(static_cast<size_t>(numOfSamplesToCollect, 0));

			int timesToLoop = 0;

			if(iLengthInSamples == numOfSamplesToCollect)
			{
				timesToLoop = 1;
			}
			else
			{
				timesToLoop = static_cast<int>((iLengthInSamples - numOfSamplesToCollect) / (ENERGYSEARCHTIME * fSampleRate));
			}

			std::vector<float> thirtySecEnergy = std::vector<float>();

			//float loudestEnergy = 0.0;
			bool dave;
			dave = audioFileReader->readSamples(destSamples, iNumOfChannels, 0, 0, iLengthInSamples);

			for(int j=0; j < timesToLoop;j++)
			{
				float fSum=0.f;

				for(int n=0; n<numOfSamplesToCollect; n++)
				{
					//Sum to mono if needed and workout the energy for each 30 sec. frame
					if(iNumOfChannels > 1)
					{
						destSamplesFloat.push_back(static_cast<float>((destSamples[0][int(j * ENERGYSEARCHTIME * fSampleRate) + n] + destSamples[1][int( j * ENERGYSEARCHTIME * fSampleRate) + n]) / 2) / (0x7fffffff));
					}
					else
					{
						destSamplesFloat.push_back(static_cast<float>(destSamples[0][int(j * ENERGYSEARCHTIME * fSampleRate) + n]) / (0x7fffffff));
					}

					fSum+=(destSamplesFloat[n] * destSamplesFloat[n]);
				}

				//Normalise and push onto the list of 30 sec clips.
				fSum /= numOfSamplesToCollect;

				//if (fSum > loudestEnergy)
				//{
				//	loudestEnergy = fSum;
				//	destSamplesFloatLoudest = destSamplesFloat;
				//}

				thirtySecEnergy.push_back(fSum);
			}

			//Find the index of the section with the most energy
			int maxIdx = std::distance(thirtySecEnergy.begin(), max_element(thirtySecEnergy.begin(), thirtySecEnergy.end()));

			int* thirtySecSamples[2] = {0};
			unique_ptr<int> L30(new int[iLengthInSamples]{ 0 });
			memset(L30.get(), 0, iLengthInSamples);
			thirtySecSamples[0]=L30.get(); //Left channel
			thirtySecSamples[1]=L30.get(); //Left right

			//Read the 30 secs. in
			audioFileReader->readSamples(thirtySecSamples, iNumOfChannels, 0, int(maxIdx * ENERGYSEARCHTIME * fSampleRate), numOfSamplesToCollect);

			destSamplesFloat = std::vector<float>(static_cast<size_t>(numOfSamplesToCollect, 0));

			for(int n=0; n<numOfSamplesToCollect; n++)
			{
				//Sum to mono if needed
				if(iNumOfChannels > 1)
				{
					destSamplesFloat.push_back(static_cast<float>((thirtySecSamples[0][n] + thirtySecSamples[1][n]) / 2) / (0x7fffffff));
				}
				else
				{
					destSamplesFloat.push_back(static_cast<float>(thirtySecSamples[0][n]) / (0x7fffffff));
				}
			}

			std::vector<ObservationData> newObs =  m_AudioSourceFeatureExtractor.Process(destSamplesFloat);

			FeatureData newFeature = FeatureData(newObs, labels[i], audioFileNames[i], fSampleRate, FFTSIZE, static_cast<float>(numOfSamplesToCollect), poolTimeSecs);

			//XML from now on.
			writeCSV.Write(CSVFileName, newFeature);
			xmlWrite.Write(CSVFileName, newFeature);

			//Update the screen information;
			
			cout << string(outputStr.length(),'\b');	

		}
		else
		{
			cout << "\n\n\nERROR: Could not find file!!!\n\n\n";
		}		
	}

	m_AudioSourceFeatureExtractor.Finalize();

	return featureData;
};
