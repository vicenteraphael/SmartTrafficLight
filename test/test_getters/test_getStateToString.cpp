#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

void test_getStateToString() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.enable();

    When(Method(ArduinoFake(), millis)).Return(100);
    tl.disable();

    TEST_ASSERT_EQUAL_STRING(tl.getStateToString(), "DISABLED_STATE");

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // disable()
}