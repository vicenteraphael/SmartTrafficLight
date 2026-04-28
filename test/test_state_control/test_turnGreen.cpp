#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define YELLOW_TRIGGER_TIME (DEFAULT_GREEN_INTERVAL + 100)
#define RED_TRIGGER_TIME ((YELLOW_TRIGGER_TIME) + (DEFAULT_YELLOW_INTERVAL))

void test_turnGreen() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.enable(); // goes to green

    When(Method(ArduinoFake(), millis)).AlwaysReturn(YELLOW_TRIGGER_TIME); // Advances to yellow
    tl.update();

    When(Method(ArduinoFake(), millis)).AlwaysReturn(RED_TRIGGER_TIME); // Advances to red
    tl.update();
    tl.turnGreen(); // goes to green

    TEST_ASSERT_EQUAL(tl.getState(), GREEN_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Twice(); // enable() and turnGreen()

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // 1st update()
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // 1st update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // 2nd update()
    Verify(Method(ArduinoFake(), digitalWrite).Using(RED_PIN, HIGH)).Once(); // 2nd update()
}