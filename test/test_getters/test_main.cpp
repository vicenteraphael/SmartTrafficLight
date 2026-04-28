#include "unity.h"
#include <SmartTrafficLight.h>

void test_getPinOn();
void test_getState();
void test_getStateToString();

using namespace fakeit;

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

    RUN_TEST(test_getPinOn);
    RUN_TEST(test_getState);
    RUN_TEST(test_getStateToString);

    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}