#include <Arduino.h>
#include "SmartTrafficLight.h"

// --------------- CONSTANTS ---------------

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)
#define BUTTON_PIN (2)

#define GREEN_TIMEOUT (10000)
#define YELLOW_TIMEOUT (2000)
#define RED_TIMEOUT (4000)

#define MIN_GREEN_TIME (4000)

// --------------- PROGRAM ---------------

SmartTrafficLight trafficLight;

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_TIMEOUT, YELLOW_TIMEOUT, RED_TIMEOUT, MIN_GREEN_TIME);
    trafficLight.begin();
}

void loop(){
    trafficLight.update();
}