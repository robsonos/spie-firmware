#pragma once

#include <Context.h>

void processATCommand(Stream &stream)
{
    String command = stream.readStringUntil('\n');
    String response;

    if (command.startsWith("AT+"))
    {
        // Extract the command and optional argument
        int separatorIndex = command.indexOf('=');
        String cmdKey = separatorIndex > 0 ? command.substring(0, separatorIndex) : command;
        String cmdValue = separatorIndex > 0 ? command.substring(separatorIndex + 1) : "";

        // Process commands using a switch-case equivalent
        if (cmdKey == "AT+NUMPHASES")
        {
            int numPhases = cmdValue.toInt();
            if (numPhases <= 0)
            {
                response = "ERROR: NUMPHASES must be positive.";
            }
            else
            {
                ctx.config.numPhases = numPhases;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+SIGNALFREQ")
        {
            int signalFreq = cmdValue.toInt();
            if (signalFreq <= 0)
            {
                response = "ERROR: SIGNALFREQ must be positive.";
            }
            else
            {
                ctx.config.signalFrequency = signalFreq;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+SAMPLINGFREQ")
        {
            int samplingFreq = cmdValue.toInt();
            if (samplingFreq <= 0)
            {
                response = "ERROR: SAMPLINGFREQ must be positive.";
            }
            else
            {
                ctx.config.samplingFrequency = samplingFreq;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+AMPLITUDE")
        {
            int amplitude = cmdValue.toInt();
            if (amplitude < 0)
            {
                response = "ERROR: AMPLITUDE must be zero or positive.";
            }
            else
            {
                ctx.config.amplitude = amplitude;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+OFFSET")
        {
            int offset = cmdValue.toInt();
            if (offset < -10000 || offset > 10000)
            {
                response = "ERROR: OFFSET must be between -10000 and 10000.";
            }
            else
            {
                ctx.config.offset = offset;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+ERRORPERCENT")
        {
            float errorPercent = cmdValue.toFloat();
            if (errorPercent < 0.0 || errorPercent > 100.0)
            {
                response = "ERROR: ERRORPERCENT must be between 0 and 100.";
            }
            else
            {
                ctx.config.errorPercentage = errorPercent;
                response = "OK";
            }
        }
        else if (cmdKey == "AT+NUMPHASES?")
        {
            response = String("+NUMPHASES: ") + ctx.config.numPhases;
        }
        else if (cmdKey == "AT+SIGNALFREQ?")
        {
            response = String("+SIGNALFREQ: ") + ctx.config.signalFrequency;
        }
        else if (cmdKey == "AT+SAMPLINGFREQ?")
        {
            response = String("+SAMPLINGFREQ: ") + ctx.config.samplingFrequency;
        }
        else if (cmdKey == "AT+AMPLITUDE?")
        {
            response = String("+AMPLITUDE: ") + ctx.config.amplitude;
        }
        else if (cmdKey == "AT+OFFSET?")
        {
            response = String("+OFFSET: ") + ctx.config.offset;
        }
        else if (cmdKey == "AT+ERRORPERCENT?")
        {
            response = String("+ERRORPERCENT: ") + ctx.config.errorPercentage;
        }
        else if (cmdKey == "AT+ALL?")
        {
            response = String("+NUMPHASES: ") + ctx.config.numPhases + "\n" +
                       String("+SIGNALFREQ: ") + ctx.config.signalFrequency + "\n" +
                       String("+SAMPLINGFREQ: ") + ctx.config.samplingFrequency + "\n" +
                       String("+AMPLITUDE: ") + ctx.config.amplitude + "\n" +
                       String("+OFFSET: ") + ctx.config.offset + "\n" +
                       String("+ERRORPERCENT: ") + ctx.config.errorPercentage + "\n" +
                       String("+POINTSPERWAVE: ") + ctx.config.getPointsPerWave() + "\n" +
                       String("+SAMPLINGINTERVAL: ") + ctx.config.getSamplingInterval();
        }
        else
        {
            response = "ERROR: Unknown command.";
        }
    }
    else
    {
        response = "ERROR: Invalid AT command format.";
    }

    // Send the response back to the stream
    stream.println(response);
}
