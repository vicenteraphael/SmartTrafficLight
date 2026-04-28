#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

void test_startBlinking() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.startBlinking();

    TEST_ASSERT_EQUAL(tl.getState(), BLINKING_YELLOW_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // enable()
}