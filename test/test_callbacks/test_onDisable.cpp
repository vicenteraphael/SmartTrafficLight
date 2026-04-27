#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_ENABLE_TIME (0)
#define TRIGGER_DISABLE_TIME (100)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onDisable() {
    tl.begin();

    tl.onDisable(test_callback);
    

    When(Method(ArduinoFake(), millis)).Return(TRIGGER_ENABLE_TIME);
    tl.enable();


    // Test onDisable()
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_DISABLE_TIME);
    tl.disable();

    TEST_ASSERT_EQUAL(called_state, DISABLED_STATE);


    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // disable()
}