#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

void test_enable() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.enable();

    TEST_ASSERT_EQUAL(tl.getState(), GREEN_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
}