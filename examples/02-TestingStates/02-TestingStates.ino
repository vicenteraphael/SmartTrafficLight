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

void print_state() {
    Serial.print("Pin on: ");
    Serial.println(trafficLight.getPinOn());
    
    Serial.print("Current state: ");
    Serial.println(trafficLight.getStateToString());
}

void setup() {
  	Serial.begin(9600);
  
  	trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);

    trafficLight.onAlterState(print_state);
  	
  	trafficLight.begin();
    trafficLight.startBlinking();
}

void loop(){
    trafficLight.update();
  	if (millis() >= 10000) {
      trafficLight.enable();
    }
  	else if (millis() >= 5000) {
      trafficLight.disable();
    } 
}