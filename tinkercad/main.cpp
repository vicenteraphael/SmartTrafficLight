#include <Arduino.h> // Remove this when running on tinkercad

#define NO_PIN (255)
#define NO_INTERVAL (0)

#define DEFAULT_GREEN_INTERVAL (10000)
#define DEFAULT_YELLOW_INTERVAL (2000)
#define DEFAULT_RED_INTERVAL (5000)
#define DEFAULT_MIN_GREEN_TIME (5000)

#define BLINKING_INTERVAL (1000)

enum State {
    GREEN_STATE,
    YELLOW_STATE,
    RED_STATE,
    BLINKING_YELLOW_STATE,
    DISABLED_STATE
};

const char stringStates[][22] = {
    "GREEN_STATE",
    "YELLOW_STATE",
    "RED_STATE",
    "BLINKING_YELLOW_STATE",
    "DISABLED_STATE",
};

class SmartTrafficLight {
    private:
        uint8_t greenPin = NO_PIN;
        uint8_t yellowPin = NO_PIN;
        uint8_t redPin = NO_PIN;
        uint8_t buttonPin = NO_PIN;

        unsigned long greenInterval = DEFAULT_GREEN_INTERVAL;
        unsigned long yellowInterval = DEFAULT_YELLOW_INTERVAL;
        unsigned long redInterval = DEFAULT_RED_INTERVAL;
        unsigned long minGreenTime = DEFAULT_MIN_GREEN_TIME;

        bool begun = false;
        bool pressed = false;
        unsigned long lastTimeTransition = 0;

        State state = DISABLED_STATE;
        uint8_t pinOn = NO_PIN;
        
        void assertBegun();

        void turnOn(const uint8_t led_pin);
        void turnOff();

        void handleButton();
        void handleGreen();
        void handleYellow();
        void handleRed();
        void handleBlinking();

        void (*onGreen)() = nullptr;
        void (*onYellow)() = nullptr;
        void (*onRed)() = nullptr;
        void (*onEn)() = nullptr;
        void (*onDis)() = nullptr;
        void (*onStartBlink)() = nullptr;
        void (*onStopBlink)() = nullptr;
        void (*onAlter)() = nullptr;

        void goTo(State state);

    public:
        SmartTrafficLight();

        SmartTrafficLight(
            uint8_t g_pin,
            uint8_t y_pin,
            uint8_t r_pin,
            uint8_t b_pin = NO_PIN
        );

        void attach(
            uint8_t g_pin,
            uint8_t y_pin,
            uint8_t r_pin,
            uint8_t b_pin = NO_PIN
        );

        void setIntervals(
            unsigned long g_Interval,
            unsigned long y_Interval,
            unsigned long r_Interval,
            unsigned long min_g_time = DEFAULT_MIN_GREEN_TIME
        );

        void begin();

        void update();
        
        void startBlinking();
        void stopBlinking();
        void enable();
        void disable();
        void turnGreen();
        void turnRed();

        void onTurnGreen(void (*func)());
        void onTurnYellow(void (*func)());
        void onTurnRed(void (*func)());
        void onEnable(void (*func)());
        void onDisable(void (*func)());
        void onStartBlinking(void (*func)());
        void onStopBlinking(void (*func)());
        void onAlterState(void (*func)());

        const char* getCurrentState();
        const uint8_t getPinOn();
};


// ================================ CONSTRUCTORS ================================

void SmartTrafficLight::attach(const uint8_t g_pin, const uint8_t y_pin, const uint8_t r_pin, const uint8_t b_pin) {
    greenPin = g_pin;
    yellowPin = y_pin;
    redPin = r_pin;
    buttonPin = b_pin;
}

void SmartTrafficLight::setIntervals(const unsigned long g_interval, const unsigned long y_interval, const unsigned long r_interval, const unsigned long min_g_time) {
    greenInterval = g_interval;
    yellowInterval = y_interval;
    redInterval = r_interval;
    minGreenTime = min_g_time;
}

SmartTrafficLight::SmartTrafficLight() = default;

SmartTrafficLight::SmartTrafficLight(const uint8_t g_pin, const uint8_t y_pin, const uint8_t r_pin, const uint8_t b_pin) {
    attach(g_pin, y_pin, r_pin, b_pin);
}


// ================================ INITIALIZATION ================================

void SmartTrafficLight::assertBegun() {
    if (!begun) {
        Serial.begin(9600);
        Serial.println("Fatal: unitialized...");
        Serial.println("Use attach() to configure the pins");
        Serial.println("Use setIntervals() to customize the traffic light intervals");
        Serial.println("Use begin() to start the traffic light");
        while(true);
    }
}

void SmartTrafficLight::begin() {
    // Safety verification
    if (greenPin == NO_PIN || yellowPin == NO_PIN || redPin == NO_PIN) {
        assertBegun();
        return;
    }
    begun = true;

    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
    if (buttonPin != NO_PIN) pinMode(buttonPin, INPUT_PULLUP);
}


// ================================ TRAFFIC LIGHT HANDLING ================================


void SmartTrafficLight::turnOn(const uint8_t led_pin){
    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);

    digitalWrite(led_pin, HIGH);

    pinOn = led_pin;
}

void SmartTrafficLight::turnOff() {
    lastTimeTransition = millis();

    digitalWrite(pinOn, LOW);
    pinOn = NO_PIN;
}

void SmartTrafficLight::handleButton() {
    pressed = !digitalRead(buttonPin);

    if (pressed && (millis() - lastTimeTransition >= minGreenTime)) goTo(YELLOW_STATE);
}

void SmartTrafficLight::handleGreen() {
    if (buttonPin != NO_PIN) handleButton();

    if (millis() - lastTimeTransition >= greenInterval) goTo(YELLOW_STATE);
}

void SmartTrafficLight::handleYellow() {
    if (millis() - lastTimeTransition >= yellowInterval) goTo(RED_STATE);
}

void SmartTrafficLight::handleRed() {
    if (millis() - lastTimeTransition >= redInterval) goTo(GREEN_STATE);
}

void SmartTrafficLight::handleBlinking() {
    if (pinOn == yellowPin) {
        if (millis() - lastTimeTransition >= BLINKING_INTERVAL) turnOff();
    }
    else {
        if (millis() - lastTimeTransition >= BLINKING_INTERVAL) turnOn(yellowPin);
    }
}


// ================================ STATE MACHINE ================================

void SmartTrafficLight::goTo(State newState) {
    switch (newState) {
        case GREEN_STATE:
            if (state == DISABLED_STATE && onEn) onEn();
            else if (state == BLINKING_YELLOW_STATE && onStopBlink) onStopBlink();
            if (onGreen) onGreen();
            turnOn(greenPin);
            break;
        case YELLOW_STATE:
            if (onYellow) onYellow();
            turnOn(yellowPin);
            break;
        case RED_STATE:
            if (onRed) onRed();
            turnOn(redPin);
            break;
        case BLINKING_YELLOW_STATE:
            if (onStartBlink) onStartBlink();
            turnOn(yellowPin);
            break;
        case DISABLED_STATE:
            if (onDis) onDis();
            turnOff();
    }
    state = newState;
    if (onAlter) onAlter();
}

void SmartTrafficLight::update() {
    assertBegun();

    switch (state) {
        case GREEN_STATE:
            handleGreen();
            break;
        
        case YELLOW_STATE:
            handleYellow();
            break;

        case RED_STATE:
            handleRed();
            break;

        case BLINKING_YELLOW_STATE:
            handleBlinking();
    }
}


// ================================ PUBLIC METHODS ================================

// Alter state functions

void SmartTrafficLight::startBlinking() {
    assertBegun();
    if (state == BLINKING_YELLOW_STATE) return;
    
    goTo(BLINKING_YELLOW_STATE);
}

void SmartTrafficLight::stopBlinking() {
    assertBegun();
    if (state != BLINKING_YELLOW_STATE) return;
    
    goTo(GREEN_STATE);
}

void SmartTrafficLight::enable() {
    assertBegun();
    if (state != DISABLED_STATE) return;

    goTo(GREEN_STATE);
}

void SmartTrafficLight::disable() {
    assertBegun();
    if (state == DISABLED_STATE) return;

    goTo(DISABLED_STATE);
}

void SmartTrafficLight::turnGreen() {
    assertBegun();
    if (state == RED_STATE) goTo(YELLOW_STATE);
    else if (state == YELLOW_STATE) goTo(GREEN_STATE);
}

void SmartTrafficLight::turnRed() {
    assertBegun();
    if (state == GREEN_STATE) goTo(YELLOW_STATE);
    else if (state == YELLOW_STATE) goTo(RED_STATE);
}

// Event functions

void SmartTrafficLight::onTurnGreen(void (*func)()) {
    onGreen = func;
}

void SmartTrafficLight::onTurnYellow(void (*func)()) {
    onYellow = func;
}

void SmartTrafficLight::onTurnRed(void (*func)()) {
    onRed = func;
}

void SmartTrafficLight::onEnable(void (*func)()) {
    onEn = func;
}

void SmartTrafficLight::onDisable(void (*func)()) {
    onDis = func;
}

void SmartTrafficLight::onStartBlinking(void (*func)()) {
    onStartBlink = func;
}

void SmartTrafficLight::onStopBlinking(void (*func)()) {
    onStopBlink = func;
}

void SmartTrafficLight::onAlterState(void (*func)()) {
    onAlter = func;
}

// Getter functions

const char* SmartTrafficLight::getCurrentState() {
    return stringStates[state];
}

const uint8_t SmartTrafficLight::getPinOn() {
    return pinOn;
}


// --------------- CONSTANTS ---------------

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)
#define BUTTON_PIN (2)

#define GREEN_INTERVAL (5000)
#define YELLOW_INTERVAL (1000)
#define RED_INTERVAL (2000)

#define MIN_GREEN_TIME (2000)


// --------------- CALLBACK FUNCTIONS ---------------
 
void print_turning_green() {
	Serial.println("Turning green...");
}

void print_turning_yellow() {
	Serial.println("Turning yellow...");
}

void print_turning_red() {
	Serial.println("Turning red...");
}

void print_enable() {
	Serial.println("Enabling...");
}

void print_disable() {
	Serial.println("Desabling...");
}

void print_start_blinking() {
	Serial.println("Starting blinking...");
}

void print_stop_blinking() {
	Serial.println("Stopping blinking...");
}

void altering_state() {
	Serial.println("Altering state...");
}


// --------------- PROGRAM ---------------

SmartTrafficLight trafficLight{};

void setup() {
  	Serial.begin(9600);
  
  	trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
      
    trafficLight.onTurnGreen(print_turning_green);
    trafficLight.onTurnYellow(print_turning_yellow);
  	trafficLight.onTurnRed(print_turning_red);
  	trafficLight.onEnable(print_enable);
  	trafficLight.onDisable(print_disable);
  	trafficLight.onStartBlinking(print_start_blinking);
  	trafficLight.onStopBlinking(print_stop_blinking);
    trafficLight.onAlterState(altering_state);
  	
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