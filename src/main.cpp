#ifdef UNIT_TEST
#include "ArduinoFake.h"
#else
#include "Arduino.h"
#endif

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

SineWaveConfig config = {
    12,   // numPhases
    1,    // signalFrequency
    500,  // samplingFrequency
    1000, // amplitude
    0,    // offset
    0.0,  // errorPercentage
    false // addTime
};

void processATCommand(Stream &stream)
{
    String command = stream.readStringUntil('\n');

    if (command.startsWith("AT+NUMPHASES="))
    {
        config.numPhases = command.substring(13).toInt();
        stream.println("OK");
    }
    else if (command == "AT+NUMPHASES?")
    {
        stream.println(String("+NUMPHASES: ") + config.numPhases);
    }
    else if (command.startsWith("AT+SIGNALFREQ="))
    {
        config.signalFrequency = command.substring(14).toInt();
        stream.println("OK");
    }
    else if (command == "AT+SIGNALFREQ?")
    {
        stream.println(String("+SIGNALFREQ: ") + config.signalFrequency);
    }
    else if (command.startsWith("AT+SAMPLINGFREQ="))
    {
        config.samplingFrequency = command.substring(16).toInt();
        stream.println("OK");
    }
    else if (command == "AT+SAMPLINGFREQ?")
    {
        stream.println(String("+SAMPLINGFREQ: ") + config.samplingFrequency);
    }
    else if (command.startsWith("AT+AMPLITUDE="))
    {
        config.amplitude = command.substring(13).toInt();
        stream.println("OK");
    }
    else if (command == "AT+AMPLITUDE?")
    {
        stream.println(String("+AMPLITUDE: ") + config.amplitude);
    }
    else if (command.startsWith("AT+OFFSET="))
    {
        config.offset = command.substring(10).toInt();
        stream.println("OK");
    }
    else if (command == "AT+OFFSET?")
    {
        stream.println(String("+OFFSET: ") + config.offset);
    }
    else if (command.startsWith("AT+ERRORPERCENT="))
    {
        config.errorPercentage = command.substring(16).toFloat();
        stream.println("OK");
    }
    else if (command == "AT+ERRORPERCENT?")
    {
        stream.println(String("+ERRORPERCENT: ") + config.errorPercentage);
    }
    else if (command == "AT+ALL?")
    {
        stream.println(String("+NUMPHASES: ") + config.numPhases);
        stream.println(String("+SIGNALFREQ: ") + config.signalFrequency);
        stream.println(String("+SAMPLINGFREQ: ") + config.samplingFrequency);
        stream.println(String("+AMPLITUDE: ") + config.amplitude);
        stream.println(String("+OFFSET: ") + config.offset);
        stream.println(String("+ERRORPERCENT: ") + config.errorPercentage);
        stream.println(String("+POINTSPERWAVE: ") + config.getPointsPerWave());
        stream.println(String("+SAMPLINGINTERVAL: ") + config.getSamplingInterval());
    }
    else
    {
        stream.println("ERROR");
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(0, INPUT);
    randomSeed(analogRead(0));
    Serial.println("AT command interface ready.");
}

void loop()
{
    static uint32_t lastSampleTime = 0;
    static uint16_t pointIndex = 0;
    uint32_t currentMicros = micros();
    uint32_t elapsedSampleTime = currentMicros - lastSampleTime;

    // Process serial input
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();
        processATCommand(Serial);
    }

    // Check if it's time for the next sample
    if (elapsedSampleTime >= config.getSamplingInterval())
    {
        lastSampleTime = currentMicros;

        String output = "";

        if (config.addTime)
        {
            output += String(elapsedSampleTime) + "\t";
        }

        for (int phase = 0; phase < config.numPhases; ++phase)
        {
            float phaseShift = (2.0 * PI / config.numPhases) * phase;
            float radians = 2.0 * PI * pointIndex / config.getPointsPerWave() + phaseShift;
            int sineValue = config.offset + config.amplitude * sin(radians);

            float errorFactor = random(-1000, 1001) / 1000.0;
            int error = sineValue * (errorFactor * (config.errorPercentage / 100.0));
            sineValue += error;

            output += String(sineValue);
            if (phase < config.numPhases - 1)
            {
                output += "\t";
            }
        }

        Serial.println(output);
        pointIndex = (pointIndex + 1) % config.getPointsPerWave();
    }
}
