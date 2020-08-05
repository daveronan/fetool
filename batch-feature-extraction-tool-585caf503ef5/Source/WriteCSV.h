/*
  ==============================================================================

    WriteCSV.h
    Created: 29 Aug 2014 3:57:27pm
    Author:  david.ronan

  ==============================================================================
*/

#ifndef WRITECSV_H_INCLUDED
#define WRITECSV_H_INCLUDED
#include "FeatureData.h"
#include "ObservationData.h"

class WriteCSV
{
public:
	WriteCSV();
	~WriteCSV();
	void Write(std::string filename, FeatureData data);
	const std::string currentDateTime();
};


#endif  // WRITECSV_H_INCLUDED
