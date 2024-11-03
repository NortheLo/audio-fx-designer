#include "../include/AudioSystem.hpp"

#include <iostream>
#include <string>

#define SIGQUIT -1

AudioSystem::AudioSystem() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        printErr(err);
    }

    inBuffer.resize(FRAMES_PER_BUFFER);
    outBuffer.resize(FRAMES_PER_BUFFER);

    selDev();
}

AudioSystem::~AudioSystem() {
    closeAudio(0);
}

void AudioSystem::printErr(PaError err) {
    std::cerr << "ERROR: " << Pa_GetErrorText(err) << "\n";
    closeAudio(SIGQUIT);
}

int AudioSystem::printDev() {
    int devices = Pa_GetDeviceCount();

    for (int i = 0; i != devices; ++i) 
    {
        auto * info = Pa_GetDeviceInfo(i);
        std::cout << "ID: " << i << " " << info->name << std::endl;
    } 
    return devices;
}

void AudioSystem::selDev() {
    int inID, outID;
    int devNum = printDev();
   
    do {
        std::cout << "Select input-device by ID number (0 will use system defaults): ";
        std::cin >> inID; 
        std::cout << "Select output-device by ID number (0 will use system defaults): ";
        std::cin >> outID;         
    } while (inID > devNum && outID > devNum);
    
    setDevices(inID, outID);
}

void AudioSystem::setDevices(int inID, int outID) {

    if (inID == 0 && outID == 0)
    {
        inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
        outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */

    }
    else {
        inputParameters.device = inID;
        outputParameters.device = outID;
    }

    inputInfo = Pa_GetDeviceInfo( inputParameters.device );
    inputParameters.channelCount = numChannels;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = inputInfo->defaultLowInputLatency ;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputInfo = Pa_GetDeviceInfo( outputParameters.device );
    outputParameters.channelCount = numChannels;
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = outputInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;    
    
    std::cout << "+++INFO+++\nDevice ID{i:o}: " << inputParameters.device << " " << outputParameters.device << "\n";
    std::cout << "Name{i:o}: " << inputInfo->name << " " <<  outputInfo->name << "\n";
    std::cout << "Latency:{i:o}: " << inputInfo->defaultLowInputLatency << " " << outputInfo->defaultLowOutputLatency << "\n";
    
}

int AudioSystem::openAudio() {
    PaError errOpen = Pa_OpenStream(&stream,
                                    &inputParameters,
                                    &outputParameters,
                                    SAMPLE_RATE,
                                    FRAMES_PER_BUFFER,
                                    paClipOff,              /* we won't output out of range samples so don't bother clipping them */
                                    &AudioSystem::streamCallback,                
                                    this);                /* Using 'this' for userData so we can cast to Sine* in paCallback method */
    if (errOpen != paNoError) {
        printErr(errOpen);
        return -1;
    }

    PaError errStart = Pa_StartStream(stream);

    if (errStart != paNoError) {
        printErr(errStart);
        return -1;
    }

    return 0;
}

void AudioSystem::closeAudio(int quit) {
    Pa_AbortStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    if (quit == SIGQUIT) {
        exit(EXIT_FAILURE);
    }
}

int AudioSystem::audioCallback(const void *inputBuffer,
                                void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags) {
    float* in = (float*) inputBuffer;       //Replace with C++ style cast
    float* out = static_cast<float*>(outputBuffer);
    std::unique_lock<std::mutex> ul(mu);

    [[maybe_unused]] const PaStreamCallbackTimeInfo* info = timeInfo;
    [[maybe_unused]] PaStreamCallbackFlags flags = statusFlags;
    
    /* For writing the data from the microphone */
    for (size_t i = 0; i < framesPerBuffer; i++) {
        inBuffer[i] = *in++; 
    }

    /* For writng the outputs data*/
    
    for (size_t i = 0; i < framesPerBuffer; i++) {
        *out++ = outBuffer[i];
    }
    
    rdy = true;    
    return paContinue;
}

std::vector<float> AudioSystem::getBuffer() {
    while (rdy == false);
    std::unique_lock<std::mutex> ul(mu);
    rdy = false;

    return inBuffer;
}

void AudioSystem::writeBuffer(std::vector<float> data) {
    if (data.size() > FRAMES_PER_BUFFER)
    {
        std::cout << "Data not in correct shape!\n";
        return;
    }
    
    for (size_t i = 0; i < data.size(); i++)
    {
        outBuffer[i] = data[i];
    }
}