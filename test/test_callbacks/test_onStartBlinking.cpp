#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_STARTBLINKING_TIME (0)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onStartBlinking() {
    tl.begin();

    tl.onStartBlinking(test_callback);

    // Test onStartBlinking()
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_STARTBLINKING_TIME);
    tl.startBlinking();

    TEST_ASSERT_EQUAL(called_state, BLINKING_YELLOW_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // startBlinking()
}