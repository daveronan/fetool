/*
  ==============================================================================

    ParseCSV.h
    Created: 27 Aug 2014 3:18:54pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef PARSECSV_H_INCLUDED
#define PARSECSV_H_INCLUDED

#include <fstream>

#include "AudioFileData.h"

class ParseCSV
{
	public:
		ParseCSV();
		~ParseCSV();
		AudioFileData Parse(std::string fileName);

	private:
		std::vector<std::string> ReadLines(std::ifstream& is);
		AudioFileData m_AudioFileData;
};

#endif  // PARSECSV_H_INCLUDED
