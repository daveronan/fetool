/*
  ==============================================================================

    AudioFileData.h
    Created: 27 Aug 2014 3:41:03pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef AUDIOFILEDATA_H_INCLUDED
#define AUDIOFILEDATA_H_INCLUDED

#include<string>
#include<vector>


class AudioFileData
{
	public:
		AudioFileData();
		~AudioFileData();

		AudioFileData(std::vector<std::string> fileNames, std::vector<std::string> labels){m_FileNames = fileNames; m_Labels = labels;};

		std::vector<std::string> GetFileNames(){return m_FileNames;};
		std::vector<std::string> GetLabels(){return m_Labels;};

	private:
		std::vector<std::string> m_FileNames;
		std::vector<std::string> m_Labels;
};

#endif  // AUDIOFILEDATA_H_INCLUDED
