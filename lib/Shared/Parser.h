#pragma once

#include <Context.h>

void processATCommand(Stream &stream)
{
    String command = stream.readStringUntil('\n');

    if (command.startsWith("AT+NUMPHASES="))
    {
        ctx.config.numPhases = command.substring(13).toInt();
        stream.println("OK");
    }
    else if (command == "AT+NUMPHASES?")
    {
        stream.println(String("+NUMPHASES: ") + ctx.config.numPhases);
    }
    else if (command.startsWith("AT+SIGNALFREQ="))
    {
        ctx.config.signalFrequency = command.substring(14).toInt();
        stream.println("OK");
    }
    else if (command == "AT+SIGNALFREQ?")
    {
        stream.println(String("+SIGNALFREQ: ") + ctx.config.signalFrequency);
    }
    else if (command.startsWith("AT+SAMPLINGFREQ="))
    {
        ctx.config.samplingFrequency = command.substring(16).toInt();
        stream.println("OK");
    }
    else if (command == "AT+SAMPLINGFREQ?")
    {
        stream.println(String("+SAMPLINGFREQ: ") + ctx.config.samplingFrequency);
    }
    else if (command.startsWith("AT+AMPLITUDE="))
    {
        ctx.config.amplitude = command.substring(13).toInt();
        stream.println("OK");
    }
    else if (command == "AT+AMPLITUDE?")
    {
        stream.println(String("+AMPLITUDE: ") + ctx.config.amplitude);
    }
    else if (command.startsWith("AT+OFFSET="))
    {
        ctx.config.offset = command.substring(10).toInt();
        stream.println("OK");
    }
    else if (command == "AT+OFFSET?")
    {
        stream.println(String("+OFFSET: ") + ctx.config.offset);
    }
    else if (command.startsWith("AT+ERRORPERCENT="))
    {
        ctx.config.errorPercentage = command.substring(16).toFloat();
        stream.println("OK");
    }
    else if (command == "AT+ERRORPERCENT?")
    {
        stream.println(String("+ERRORPERCENT: ") + ctx.config.errorPercentage);
    }
    else if (command == "AT+ALL?")
    {
        stream.println(String("+NUMPHASES: ") + ctx.config.numPhases);
        stream.println(String("+SIGNALFREQ: ") + ctx.config.signalFrequency);
        stream.println(String("+SAMPLINGFREQ: ") + ctx.config.samplingFrequency);
        stream.println(String("+AMPLITUDE: ") + ctx.config.amplitude);
        stream.println(String("+OFFSET: ") + ctx.config.offset);
        stream.println(String("+ERRORPERCENT: ") + ctx.config.errorPercentage);
        stream.println(String("+POINTSPERWAVE: ") + ctx.config.getPointsPerWave());
        stream.println(String("+SAMPLINGINTERVAL: ") + ctx.config.getSamplingInterval());
    }
    else
    {
        stream.println("ERROR");
    }
}
