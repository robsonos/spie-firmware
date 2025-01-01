#include <Arduino.h>
#include <unity.h>
#include "main.cpp"

using namespace fakeit;

class TestSupport
{
public:
    void putRxBuffer(const char *_str)
    {
        rxBuffer = String(_str);
    }

    String getTxBuffer(void)
    {
        return txBuffer;
    }

    void setupMocks(void)
    {
        // Stream.println methods
        When(OverloadedMethod(ArduinoFake(Stream), println, size_t(const char *)))
            .AlwaysDo([this](const char c[]) -> int
                      { txBuffer += String(c) + "\n";
                        return strlen(c); });
        When(OverloadedMethod(ArduinoFake(Stream), println, size_t(const String &)))
            .AlwaysDo([this](const String &s) -> int
                      { txBuffer += s + "\n";
                        return s.length(); });

        // Stream.readStringUntil method
        When(Method(ArduinoFake(Stream), readStringUntil))
            .AlwaysDo([this](char terminator) -> String
                      { return rxBuffer.substring(0, rxBuffer.indexOf(terminator)); });
    }

    void reset(void)
    {
        txBuffer = "";
        rxBuffer = "";
    }

private:
    String txBuffer;
    String rxBuffer;
};

TestSupport testSupport;

void test_pointsPerWave()
{
    SineWaveConfig config = {12, 1, 500, 1000, 0, 0.0, false};
    TEST_ASSERT_EQUAL_UINT16(500, config.getPointsPerWave());
    config.signalFrequency = 2;
    TEST_ASSERT_EQUAL_UINT16(250, config.getPointsPerWave());
}

void test_samplingInterval()
{
    SineWaveConfig config = {12, 1, 500, 1000, 0, 0.0, false};
    TEST_ASSERT_EQUAL_UINT32(2000, config.getSamplingInterval());
    config.samplingFrequency = 1000;
    TEST_ASSERT_EQUAL_UINT32(1000, config.getSamplingInterval());
}

void test_AT_NUMPHASES_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+NUMPHASES?\n";
    String expectedResponse = String("+NUMPHASES: ") + config.numPhases + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_NUMPHASES_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    uint8_t numPhases = 12;
    String input = String("AT+NUMPHASES=") + numPhases + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_UINT16(numPhases, config.numPhases);
}

void test_AT_SIGNALFREQ_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+SIGNALFREQ?\n";
    String expectedResponse = String("+SIGNALFREQ: ") + config.signalFrequency + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_SIGNALFREQ_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    uint16_t signalFrequency = 100;
    String input = String("AT+SIGNALFREQ=") + signalFrequency + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Run method
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_UINT16(signalFrequency, config.signalFrequency);
}

void test_AT_SAMPLINGFREQ_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+SAMPLINGFREQ?\n";
    String expectedResponse = String("+SAMPLINGFREQ: ") + config.samplingFrequency + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_SAMPLINGFREQ_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    uint16_t samplingFrequency = 1000;
    String input = String("AT+SAMPLINGFREQ=") + samplingFrequency + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_UINT16(samplingFrequency, config.samplingFrequency);
}

void test_AT_AMPLITUDE_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+AMPLITUDE?\n";
    String expectedResponse = String("+AMPLITUDE: ") + config.amplitude + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_AMPLITUDE_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    int16_t amplitude = 2000;
    String input = String("AT+AMPLITUDE=") + amplitude + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_INT16(amplitude, config.amplitude);
}

void test_AT_OFFSET_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+OFFSET?\n";
    String expectedResponse = String("+OFFSET: ") + config.offset + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_OFFSET_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    int16_t offset = 500;
    String input = String("AT+OFFSET=") + offset + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_INT16(offset, config.offset);
}

void test_AT_ERRORPERCENT_get()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+ERRORPERCENT?\n";
    String expectedResponse = String("+ERRORPERCENT: ") + config.errorPercentage + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_ERRORPERCENT_set()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    float errorPercentage = 5.5;
    String input = String("AT+ERRORPERCENT=") + errorPercentage + "\n";
    String expectedResponse = String("OK\n");

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
    TEST_ASSERT_EQUAL_FLOAT(errorPercentage, config.errorPercentage);
}

void test_AT_ALL()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Setup test conditions
    String input = "AT+ALL?\n";
    String expectedResponse = String("+NUMPHASES: ") + config.numPhases + "\n" +
                              "+SIGNALFREQ: " + config.signalFrequency + "\n" +
                              "+SAMPLINGFREQ: " + config.samplingFrequency + "\n" +
                              "+AMPLITUDE: " + config.amplitude + "\n" +
                              "+OFFSET: " + config.offset + "\n" +
                              "+ERRORPERCENT: " + config.errorPercentage + "\n" +
                              "+POINTSPERWAVE: " + config.getPointsPerWave() + "\n" +
                              "+SAMPLINGINTERVAL: " + config.getSamplingInterval() + "\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void test_AT_INVALID()
{
    // Setup stream
    Stream *stream = ArduinoFakeMock(Stream);

    // Test results
    String input = "INVALIDCOMMAND\n";
    String expectedResponse = "ERROR\n";

    // Run method
    testSupport.putRxBuffer(input.c_str());
    processATCommand(*stream);
    String actualResponse = testSupport.getTxBuffer();

    // Test results
    TEST_ASSERT_EQUAL_STRING(expectedResponse.c_str(), actualResponse.c_str());
}

void setUp(void)
{
    ArduinoFakeReset();
    testSupport.setupMocks();
}

void tearDown(void)
{
    testSupport.reset();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_pointsPerWave);
    RUN_TEST(test_samplingInterval);
    RUN_TEST(test_AT_NUMPHASES_get);
    RUN_TEST(test_AT_NUMPHASES_set);
    RUN_TEST(test_AT_SIGNALFREQ_get);
    RUN_TEST(test_AT_SIGNALFREQ_set);
    RUN_TEST(test_AT_SAMPLINGFREQ_get);
    RUN_TEST(test_AT_SAMPLINGFREQ_set);
    RUN_TEST(test_AT_AMPLITUDE_get);
    RUN_TEST(test_AT_AMPLITUDE_set);
    RUN_TEST(test_AT_OFFSET_get);
    RUN_TEST(test_AT_OFFSET_set);
    RUN_TEST(test_AT_ERRORPERCENT_get);
    RUN_TEST(test_AT_ERRORPERCENT_set);
    RUN_TEST(test_AT_ALL);
    RUN_TEST(test_AT_INVALID);
    return UNITY_END();
}
