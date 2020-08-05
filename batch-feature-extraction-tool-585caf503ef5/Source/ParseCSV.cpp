/*
  ==============================================================================

    ParseCSV.cpp
    Created: 27 Aug 2014 3:18:54pm
    Author:  david.ronan

  ==============================================================================
*/

#include "ParseCSV.h"
#include "AudioFileData.h"

#include <fstream>
#include <string>
#include <vector>

ParseCSV::ParseCSV()
{

};

ParseCSV::~ParseCSV()
{

};

AudioFileData ParseCSV::Parse(std::string fileName)
{
	//open the file from which to read the data
	std::ifstream myFile;// = std::ifstream();

	myFile.open(fileName, std::ifstream::in);

	std::vector<std::string> data = ReadLines(myFile);

	std::vector<std::string> fileNames = std::vector<std::string>();
	std::vector<std::string> labels = std::vector<std::string>();

	for (size_t i = 0; i < data.size(); i++)
	{
		std::string s = data[i];
		std::string delimiter = ",";

		std::string newfile = "";
		std::string newlabel = "";

		size_t pos = 0;
		int idx = 1;
		std::string token = "";

		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);

			switch (idx)
			{
				case 1:
					newfile = token;
					idx++;
					break;
				default:
					break;
			}

			s.erase(0, pos + delimiter.length());
			newlabel = s;
		}

		fileNames.push_back(newfile);
		labels.push_back(newlabel);
	}

	m_AudioFileData = AudioFileData(fileNames, labels);

	myFile.close();

	return m_AudioFileData;
}

std::vector<std::string> ParseCSV::ReadLines(std::ifstream& is)
{
	std::vector<std::string> lines = std::vector<std::string>();
	std::string line = "";

	while (std::getline(is, line))
	{
		lines.push_back(line);
	}

	return lines;
}
