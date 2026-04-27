#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TL_INTERVAL (100)

#define TRIGGER_ENABLE_TIME (0)
#define TRIGGER_YELLOW_TIME (TL_INTERVAL)
#define TRIGGER_RED_TIME (TRIGGER_YELLOW_TIME + TL_INTERVAL)
#define TRIGGER_DISABLE_TIME (TRIGGER_YELLOW_TIME + TL_INTERVAL)
#define TRIGGER_STARTBLINKING_TIME (TRIGGER_DISABLE_TIME + TL_INTERVAL)
#define TRIGGER_STOPBLINKING_TIME (TRIGGER_STARTBLINKING_TIME + TL_INTERVAL)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onAlterState() {
    tl.setIntervals(TL_INTERVAL, TL_INTERVAL, TL_INTERVAL);
    tl.begin();

    tl.onAlterState(test_callback);
    

    // Test GREEN_STATE
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_ENABLE_TIME);
    tl.enable();

    TEST_ASSERT_EQUAL(called_state, GREEN_STATE);


    // Test YELLOW_STATE
    When(Method(ArduinoFake(), millis)).AlwaysReturn(TRIGGER_YELLOW_TIME);
    tl.update();

    TEST_ASSERT_EQUAL(called_state, YELLOW_STATE);


    // Test RED_STATE
    When(Method(ArduinoFake(), millis)).AlwaysReturn(TRIGGER_RED_TIME);
    tl.update();

    TEST_ASSERT_EQUAL(called_state, RED_STATE);


    // Test DISABLED_STATE
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_DISABLE_TIME);
    tl.disable();

    TEST_ASSERT_EQUAL(called_state, DISABLED_STATE);


    // Test BLINKING_STATE
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_STARTBLINKING_TIME);
    tl.startBlinking();

    TEST_ASSERT_EQUAL(called_state, BLINKING_YELLOW_STATE);


    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // enable()
    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, LOW)).Once(); // 1st update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Twice(); // 1st update() and startBlinking()
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // 1st update()

    Verify(Method(ArduinoFake(), digitalWrite).Using(RED_PIN, HIGH)).Once(); // 2nd update()
    Verify(Method(ArduinoFake(), digitalWrite).Using(RED_PIN, LOW)).Once(); // disable()
}