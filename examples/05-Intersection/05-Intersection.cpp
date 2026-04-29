#include <SmartTrafficLight.h>

// --------------- CONSTANTS ---------------

#define GREEN_PIN_1 (12)
#define YELLOW_PIN_1 (11)
#define RED_PIN_1 (10)
#define BUTTON_PIN_1 (8)

#define GREEN_PIN_2 (7)
#define YELLOW_PIN_2 (5)
#define RED_PIN_2 (3)
#define BUTTON_PIN_2 (2)

#define GREEN_INTERVAL (5000)
#define YELLOW_INTERVAL (1000)
#define RED_INTERVAL (2000)

#define MIN_GREEN_TIME (2000)

#define TRANSITION_TIME (1000)

// --------------- VARIABLES ---------------

SmartTrafficLight tl1{};
SmartTrafficLight tl2{};

enum Status {
	FIRST_WORKING,
	SECOND_WORKING,
	TRANSITION_TO_FIRST,
	TRANSITION_TO_SECOND
};

Status status = FIRST_WORKING;

unsigned long startTransition = 0;

void turn_second_green();
void turn_first_green();
void transition_to_first();
void transition_to_second();


// --------------- PROGRAM ---------------

void setup() {
  Serial.begin(9600);
    tl1.attach(GREEN_PIN_1, YELLOW_PIN_1, RED_PIN_1, BUTTON_PIN_1);
    tl2.attach(GREEN_PIN_2, YELLOW_PIN_2, RED_PIN_2, BUTTON_PIN_2);

	// Notice that the RED_INTERVAL won't be 2s but rather 5s
  	tl1.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
  	tl2.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
  
  	tl1.onTurnRed(turn_second_green);
  	tl2.onTurnRed(turn_first_green);
  
  	tl1.begin();
    tl2.begin();

  	tl1.enable(GREEN_STATE);
  	tl2.enable(RED_STATE);
}

void loop(){
	switch (status) {
		case FIRST_WORKING:
			tl1.update();
			break;
		
		case SECOND_WORKING:
			tl2.update();
			break;

		case TRANSITION_TO_FIRST:
			transition_to_first();
			break;

		case TRANSITION_TO_SECOND:
			transition_to_second();
			break;
	}
}


// --------------- HELPER FUNCTIONS ---------------

void turn_second_green() {
	status = TRANSITION_TO_SECOND;
  	startTransition = millis();
}

void turn_first_green() {
	status = TRANSITION_TO_FIRST;
  	startTransition = millis();
}

void transition_to_second() {
  if (millis() - startTransition >= TRANSITION_TIME) {
  	status = SECOND_WORKING;
    tl2.turnGreen();
  }
}

void transition_to_first() {
  if (millis() - startTransition >= TRANSITION_TIME) {
	status = FIRST_WORKING;
    tl1.turnGreen();
  }
}