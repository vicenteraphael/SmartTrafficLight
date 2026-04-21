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

SmartTrafficLight trafficLight{};
 

// --------------- CALLBACKS ---------------

void print_green_yellow_red() {
    switch(trafficLight.getState()) {
        case GREEN_STATE:
            Serial.println("Turning Green...");
            break;
        case YELLOW_STATE:
            Serial.println("Turning Yellow...");
            break;
        case RED_STATE:
            Serial.println("Turning Red...");
            break;
    }
    Serial.print("Pin on: ");
    Serial.println(trafficLight.getPinOn());
}

void print_enable() {
	Serial.println("Enabling...");
}

void print_disable() {
	Serial.println("Disabling...");
}

void print_start_blinking() {
	Serial.println("Starting blinking...");
}

void print_stop_blinking() {
	Serial.println("Stopping blinking...");
}


// --------------- PROGRAM ---------------

void setup() {
  	Serial.begin(9600);
  
  	trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
      
  	trafficLight.onEnable(print_enable);
  	trafficLight.onDisable(print_disable);
  	trafficLight.onStartBlinking(print_start_blinking);
  	trafficLight.onStopBlinking(print_stop_blinking);
    trafficLight.onAlterState(print_green_yellow_red);
  	
  	trafficLight.begin();
    trafficLight.enable();
}

void loop(){
    trafficLight.update();
    if (millis() >= 15000) {
        trafficLight.stopBlinking();
    }
    else if (millis() >= 10000) {
        trafficLight.startBlinking();
    }
  	else if (millis() >= 5000) {
        trafficLight.disable();
    }
}