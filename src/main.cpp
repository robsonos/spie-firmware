#include <Context.h>
#include <Parser.h>

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
        processATCommand(Serial);
    }

    // Check if it's time for the next sample
    if (elapsedSampleTime >= ctx.config.getSamplingInterval())
    {
        lastSampleTime = currentMicros;

        String output = "";

        if (ctx.config.addTime)
        {
            output += String(elapsedSampleTime) + "\t";
        }

        for (int phase = 0; phase < ctx.config.numPhases; ++phase)
        {
            float phaseShift = (2.0 * PI / ctx.config.numPhases) * phase;
            float radians = 2.0 * PI * pointIndex / ctx.config.getPointsPerWave() + phaseShift;
            int sineValue = ctx.config.offset + ctx.config.amplitude * sin(radians);

            float errorFactor = random(-1000, 1001) / 1000.0;
            int error = sineValue * (errorFactor * (ctx.config.errorPercentage / 100.0));
            sineValue += error;

            output += String(sineValue);
            if (phase < ctx.config.numPhases - 1)
            {
                output += "\t";
            }
        }

        Serial.println(output);
        pointIndex = (pointIndex + 1) % ctx.config.getPointsPerWave();
    }
}
