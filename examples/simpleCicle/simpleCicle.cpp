#include <Arduino.h>
#include "SmartTrafficLight.h"

// --------------- CONSTANTS ---------------

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)
#define BUTTON_PIN (2)

#define GREEN_INTERVAL (5000)
#define YELLOW_INTERVAL (1000)
#define RED_INTERVAL (2000)

#define MIN_GREEN_TIME (2000)


void print_turning_red() {
	Serial.println("Turning red...");
}
 
void print_turning_green() {
	Serial.println("Turning green...");
}


// --------------- PROGRAM ---------------

SmartTrafficLight trafficLight{};

void setup() {
  	Serial.begin(9600);
  
  	trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
      
  	trafficLight.onTurnRed(print_turning_red);
  	trafficLight.onTurnGreen(print_turning_green);
  	
  	trafficLight.begin(true);
}

void loop(){
    trafficLight.update();
}