function [mfccFilterWeights mfccDCTMatrix] = initMFCCVariables(sampleRate, FFTsize)

Fs   = sampleRate;
Nfft = FFTsize;
    
%Filter bank parameters
lowestFrequency = 133.3333;
linearFilters = 13;
linearSpacing = 66.66666666;
logFilters = 27;
logSpacing = 1.0711703;
cepstralCoefficients = 13;

% Keep this around for later....
totalFilters = linearFilters + logFilters;

% Now figure the band edges.  Interesting frequencies are spaced
% by linearSpacing for a while, then go logarithmic.  First figure0
% all the interesting frequencies.  Lower, center, and upper band
% edges are all consecutive interesting frequencies. 
freqs = lowestFrequency + (0:linearFilters-1)*linearSpacing;
freqs(linearFilters+1:totalFilters+2) = freqs(linearFilters) * logSpacing.^(1:logFilters+2);
lower  = freqs(1:totalFilters);
center = freqs(2:totalFilters+1);
upper  = freqs(3:totalFilters+2);

% each filter has unit weight, assuming a triangular weighting function
mfccFilterWeights = zeros(totalFilters,Nfft/2);
triangleHeight = 2./(upper-lower);
fftFreqs = (0:Nfft/2-1)/(Nfft)*Fs;
for chan=1:totalFilters
	mfccFilterWeights(chan,:) = (fftFreqs > lower(chan) & fftFreqs <= center(chan)).* triangleHeight(chan).*(fftFreqs-lower(chan))/(center(chan)-lower(chan)) + ...
                                (fftFreqs > center(chan) & fftFreqs < upper(chan)) .* triangleHeight(chan).*(upper(chan)-fftFreqs)/(upper(chan)-center(chan));
end

% Figure out Discrete Cosine Transform.  We want a matrix
% dct(i,j) which is totalFilters x cepstralCoefficients in size.
% The i,j component is given by cos( i * (j+0.5)/totalFilters pi )
% where we have assumed that i and j start at 0.
mfccDCTMatrix      = 1/sqrt(totalFilters/2)*cos((0:(cepstralCoefficients-1))' * (2*(0:(totalFilters-1))+1) * pi/2/totalFilters);
mfccDCTMatrix(1,:) = mfccDCTMatrix(1,:) * sqrt(2)/2;

