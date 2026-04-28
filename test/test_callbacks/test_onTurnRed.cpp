#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TL_INTERVAL (100)

#define TRIGGER_ENABLE_TIME (0)
#define TRIGGER_YELLOW_TIME (TL_INTERVAL)
#define TRIGGER_RED_TIME (TRIGGER_YELLOW_TIME + TL_INTERVAL)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onTurnRed() {
    tl.setIntervals(TL_INTERVAL, TL_INTERVAL, TL_INTERVAL);
    tl.begin();

    tl.onTurnRed(test_callback);
    

    // Goes to GREEN_STATE
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_ENABLE_TIME);
    tl.enable();


    // Goes to YELLOW_STATE
    When(Method(ArduinoFake(), millis)).AlwaysReturn(TRIGGER_YELLOW_TIME);
    tl.update();


    // Goes to RED_STATE
    When(Method(ArduinoFake(), millis)).AlwaysReturn(TRIGGER_RED_TIME);
    tl.update();

    TEST_ASSERT_EQUAL(called_state, RED_STATE);


    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // 1st update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // 1st update()
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // 1st update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(RED_PIN, HIGH)).Once(); // 2nd update()
}