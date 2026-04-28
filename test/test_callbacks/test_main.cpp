#include "unity.h"
#include <SmartTrafficLight.h>

void test_onTurnGreen();
void test_onTurnYellow();
void test_onTurnRed();
void test_onEnable();
void test_onDisable();
void test_onStartBlinking();
void test_onStopBlinking();
void test_onAlterState();

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

    RUN_TEST(test_onTurnGreen);
    RUN_TEST(test_onTurnYellow);
    RUN_TEST(test_onTurnRed);
    RUN_TEST(test_onEnable);
    RUN_TEST(test_onDisable);
    RUN_TEST(test_onStartBlinking);
    RUN_TEST(test_onStopBlinking);
    RUN_TEST(test_onAlterState);

    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}