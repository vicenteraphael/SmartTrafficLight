#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_ENABLE_TIME (0)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onTurnGreen() {
    tl.begin();

    tl.onTurnGreen(test_callback);
    
    // Test onTurnGreen()
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_ENABLE_TIME);
    tl.enable();


    TEST_ASSERT_EQUAL(called_state, GREEN_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
}