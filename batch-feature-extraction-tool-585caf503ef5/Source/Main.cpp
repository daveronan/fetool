/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include<string>

//#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFileData.h"
#include "AudioReader.h"
#include "ParseCSV.h"
#include <iostream>



//==============================================================================
int main (int argc, char* argv[])
{
	if(argc == 4)
	{
		cout << "*** Batch Feature Extraction Tool ***\n";
		cout << "*** Written by David Ronan  ***\n\n\n";

		std::string fileName;
		fileName = argv[1];
		int poolTimeSecs = atoi(argv[2]);
		int analysisWindowSize = atoi(argv[3]);

		ParseCSV parser = ParseCSV();
		AudioReader audioReader = AudioReader();
		audioReader.Read(parser.Parse(fileName), (float)poolTimeSecs, analysisWindowSize);
	}
	else
	{
		cout << "ERROR: Not enough parameters\n";
	}
    return 0;
}
