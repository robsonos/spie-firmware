#pragma once

#define FIRMWARE_VERSION "1.0.0" // INFO: line used by builder. Do not change it

#include <Arduino.h>

struct SineWaveConfig
{
    uint8_t numPhases;
    uint16_t signalFrequency;
    uint16_t samplingFrequency;
    int16_t amplitude;
    int16_t offset;
    float errorPercentage;
    bool addTime;

    uint16_t getPointsPerWave() const
    {
        return samplingFrequency / signalFrequency;
    }

    uint32_t getSamplingInterval() const
    {
        return 1000000 / samplingFrequency;
    }
};

struct Context
{
    SineWaveConfig config;

    Context() : config()
    {
        config = {
            3,    // numPhases
            1,    // signalFrequency
            50,   // samplingFrequency
            1000, // amplitude
            0,    // offset
            0.0,  // errorPercentage
            false // addTime
        };
    }
};

extern Context ctx;
