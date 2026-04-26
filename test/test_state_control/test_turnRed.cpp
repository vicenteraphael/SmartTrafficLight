#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_TIME (100)
#define RED_TRIGGER_TIME (DEFAULT_YELLOW_INTERVAL + TRIGGER_TIME)

void test_turnRed() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.enable(); // goes to green

    When(Method(ArduinoFake(), millis)).Return(TRIGGER_TIME); // still green
    tl.turnRed(); // goes to yellow!

    When(Method(ArduinoFake(), millis)).AlwaysReturn(RED_TRIGGER_TIME); // advances to red
    tl.update();

    TEST_ASSERT_EQUAL(RED_STATE, tl.getState());
    
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // enable()

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // turnRed() -> yellow
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // turnRed() -> red

    Verify(Method(ArduinoFake(), digitalWrite).Using(RED_PIN, HIGH)).Once(); // turnRed() -> red
}