#include "unity.h"
#include <SmartTrafficLight.h>
#include "test_pins.h"

using namespace fakeit;

#define TRIGGER_STARTBLINKING_TIME (0)
#define TRIGGER_STOPBLINKING_TIME (100)

static SmartTrafficLight tl(GREEN_PIN, YELLOW_PIN, RED_PIN);

static State called_state = DISABLED_STATE;

static void test_callback() {
    called_state = tl.getState();
}

void test_onStopBlinking() {
    tl.begin();

    tl.onStopBlinking(test_callback);


    When(Method(ArduinoFake(), millis)).Return(TRIGGER_STARTBLINKING_TIME);
    tl.startBlinking();


    // Test onStopBlinking()
    When(Method(ArduinoFake(), millis)).Return(TRIGGER_STOPBLINKING_TIME);
    tl.stopBlinking();

    TEST_ASSERT_EQUAL(called_state, GREEN_STATE);


    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, HIGH)).Once(); // startBlinking()
    Verify(Method(ArduinoFake(), digitalWrite).Using(YELLOW_PIN, LOW)).Once(); // stopBlinking()

    Verify(Method(ArduinoFake(), digitalWrite).Using(GREEN_PIN, HIGH)).Once(); // stopBlinking()
}