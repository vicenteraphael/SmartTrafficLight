#include "unity.h"
#include <SmartTrafficLight.h>

using namespace fakeit;

void test_enable();
void test_disable();
void test_startBlinking();
void test_stopBlinking();
void test_turnGreen();
void test_turnRed();

void setUp(void) {
    ArduinoFakeReset();
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(LOW);
    When(Method(ArduinoFake(), millis)).AlwaysReturn();
}

void tearDown(void) {}

int runUnityTests() {
    UNITY_BEGIN();
    
    RUN_TEST(test_enable);
    RUN_TEST(test_disable);
    RUN_TEST(test_startBlinking);
    RUN_TEST(test_stopBlinking);
    RUN_TEST(test_turnGreen);
    RUN_TEST(test_turnRed);

    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}