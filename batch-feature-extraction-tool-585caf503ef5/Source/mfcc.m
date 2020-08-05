function [ceps] = mfcc(audioFile, FFTsize, hop, mfccFilterWeights, mfccDCTMatrix)

%Beat synched data
cepstralCoefficients = 13;
%BeatLength = 60/BPM*Fs;
%FrameSize = round(BeatLength*NoteDiv);
hop  = hop;
%Nfft = 2^nextpow2(FrameSize);
Nfft = FFTsize;
FrameSize = FFTsize;
%number_of_frame = length([1:FrameSize:length(audioFile)])-1;

seg_start = [1:FrameSize:length(audioFile)]';   
seg_stop  = min(seg_start+FrameSize,length(audioFile));

if(seg_stop(end)-seg_start(end)~=FrameSize)
    seg_stop(end) =[]; 
    seg_start(end)=[];
end

number_of_frame = length(seg_start);

hamWindow = 0.54 - 0.46*cos(2*pi*(0:FrameSize-1)/FrameSize);

% Filter the input with the preemphasis filter
preEmphasized = audioFile; %filter([1 -.97], 1, audioFile);

% Allocate all the space we need for the output arrays.
ceps = zeros(cepstralCoefficients, number_of_frame);

%Tuning related variables :
averagedPowerSpectrogram = zeros(Nfft/2,1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%             Mel - Frequencies Cepstrum Coefficients 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h=waitbar(0,'MFCC Calculus - Please wait..');
for start=1:number_of_frame

    %Frame position
    waitbar(start/number_of_frame);
      
    first = seg_start(start);
    last  = seg_stop(start);           
    

    %Hanning window mult
    fftData = zeros(1,Nfft);
    preEmphasizedSlice = preEmphasized(first:last-1);
    fftData(1:FrameSize) = preEmphasizedSlice.*hamWindow';

    %magnitude of the fft
    fftMag = abs(fft(fftData));
    fftMag = fftMag(1:Nfft/2);

    %Sum the spectrogram magnitude 
    averagedPowerSpectrogram = averagedPowerSpectrogram + fftMag'.^2;

    %fft data into filter bank outputs + Log Compression
    FilteredFFT = mfccFilterWeights * fftMag';
    
    factorLogCompr  = 10;
    addTermLogCompr = 1;    
    earMag =  log10(addTermLogCompr+FilteredFFT*factorLogCompr);

    %Cosine transform to reduce dimensionality
    ceps(:,start) = mfccDCTMatrix * earMag;                                    

end %Loop on frames

close(h);

end
