#include <SmartTrafficLight.h>

// --------------- CONSTANTS ---------------

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)
#define BUTTON_PIN (2)

#define GREEN_INTERVAL (5000)
#define YELLOW_INTERVAL (1000)
#define RED_INTERVAL (2000)

#define MIN_GREEN_TIME (2000)


// --------------- PROGRAM ---------------

SmartTrafficLight trafficLight{};

void setup() {
  // Try omitting the button pin to see how it works
  trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
  trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
  
  trafficLight.begin();
  trafficLight.enable();
}

void loop(){
  trafficLight.update();
}