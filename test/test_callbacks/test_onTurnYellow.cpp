#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TL_INTERVAL (100)

#define TRIGGER_ENABLE_TIME (0)
#define TRIGGER_YELLOW_TIME (100)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onTurnYellow() {
    tl.setIntervals(TL_INTERVAL, TL_INTERVAL, TL_INTERVAL);
    tl.begin();

    tl.onTurnYellow(test_callback);
    

    When(Method(ArduinoFake(), millis)).Return(TRIGGER_ENABLE_TIME);
    tl.enable();


    // Test YELLOW_STATE
    When(Method(ArduinoFake(), millis)).AlwaysReturn(TRIGGER_YELLOW_TIME);
    tl.update();

    TEST_ASSERT_EQUAL(called_state, YELLOW_STATE);

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // update()
}