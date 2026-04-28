#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_TIME (100)

void test_stopBlinking() {
    SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    tl.begin();

    When(Method(ArduinoFake(), millis)).Return(0);
    tl.startBlinking();

    When(Method(ArduinoFake(), millis)).Return(TRIGGER_TIME); // still enabled
    tl.stopBlinking();
    
    TEST_ASSERT_EQUAL(tl.getState(), GREEN_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // startBlinking()
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // stopBlinking()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // stopBlinking() -> green
}