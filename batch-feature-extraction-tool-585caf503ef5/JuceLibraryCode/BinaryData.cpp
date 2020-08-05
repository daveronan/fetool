/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== initMFCCVariables.m ==================
static const unsigned char temp_binary_data_0[] =
"function [mfccFilterWeights mfccDCTMatrix] = initMFCCVariables(sampleRate, FFTsize)\r\n"
"\r\n"
"Fs   = sampleRate;\r\n"
"Nfft = FFTsize;\r\n"
"    \r\n"
"%Filter bank parameters\r\n"
"lowestFrequency = 133.3333;\r\n"
"linearFilters = 13;\r\n"
"linearSpacing = 66.66666666;\r\n"
"logFilters = 27;\r\n"
"logSpacing = 1.0711703;\r\n"
"cepstralCoefficients = 13;\r\n"
"\r\n"
"% Keep this around for later....\r\n"
"totalFilters = linearFilters + logFilters;\r\n"
"\r\n"
"% Now figure the band edges.  Interesting frequencies are spaced\r\n"
"% by linearSpacing for a while, then go logarithmic.  First figure0\r\n"
"% all the interesting frequencies.  Lower, center, and upper band\r\n"
"% edges are all consecutive interesting frequencies. \r\n"
"freqs = lowestFrequency + (0:linearFilters-1)*linearSpacing;\r\n"
"freqs(linearFilters+1:totalFilters+2) = freqs(linearFilters) * logSpacing.^(1:logFilters+2);\r\n"
"lower  = freqs(1:totalFilters);\r\n"
"center = freqs(2:totalFilters+1);\r\n"
"upper  = freqs(3:totalFilters+2);\r\n"
"\r\n"
"% each filter has unit weight, assuming a triangular weighting function\r\n"
"mfccFilterWeights = zeros(totalFilters,Nfft/2);\r\n"
"triangleHeight = 2./(upper-lower);\r\n"
"fftFreqs = (0:Nfft/2-1)/(Nfft)*Fs;\r\n"
"for chan=1:totalFilters\r\n"
"\tmfccFilterWeights(chan,:) = (fftFreqs > lower(chan) & fftFreqs <= center(chan)).* triangleHeight(chan).*(fftFreqs-lower(chan))/(center(chan)-lower(chan)) + ...\r\n"
"                                (fftFreqs > center(chan) & fftFreqs < upper(chan)) .* triangleHeight(chan).*(upper(chan)-fftFreqs)/(upper(chan)-center(chan));\r\n"
"end\r\n"
"\r\n"
"% Figure out Discrete Cosine Transform.  We want a matrix\r\n"
"% dct(i,j) which is totalFilters x cepstralCoefficients in size.\r\n"
"% The i,j component is given by cos( i * (j+0.5)/totalFilters pi )\r\n"
"% where we have assumed that i and j start at 0.\r\n"
"mfccDCTMatrix      = 1/sqrt(totalFilters/2)*cos((0:(cepstralCoefficients-1))' * (2*(0:(totalFilters-1))+1) * pi/2/totalFilters);\r\n"
"mfccDCTMatrix(1,:) = mfccDCTMatrix(1,:) * sqrt(2)/2;\r\n"
"\r\n";

const char* initMFCCVariables_m = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x45d89b1c:  numBytes = 1883; return initMFCCVariables_m;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "initMFCCVariables_m"
};

}
