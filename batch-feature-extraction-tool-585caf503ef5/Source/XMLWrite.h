/*
  ==============================================================================

    XMLWrite.h
    Created: 1 Feb 2016 7:34:54pm
    Author:  David

  ==============================================================================
*/

#ifndef XMLWRITE_H_INCLUDED
#define XMLWRITE_H_INCLUDED

#include "ObservationData.h"
#include "FeatureData.h"
#include "../JuceLibraryCode/JuceHeader.h"

class XMLWrite
{
public:
	XMLWrite();
	~XMLWrite();
	void Write(std::string filename, FeatureData data);
	const std::string currentDateTime();
};




#endif  // XMLWRITE_H_INCLUDED
