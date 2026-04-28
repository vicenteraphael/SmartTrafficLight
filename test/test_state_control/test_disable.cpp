#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TIMEOUT (100)

void test_disable() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0); 
    tl.enable();

    When(Method(ArduinoFake(), millis)).Return(TIMEOUT, TIMEOUT); // still green
    tl.update();

    When(Method(ArduinoFake(), millis)).Return(TIMEOUT);
    tl.disable();

    TEST_ASSERT_EQUAL(tl.getState(), DISABLED_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // disable()
}