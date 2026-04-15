#include "SmartTrafficLight.h"


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

    state = DISABLED;
}


// ================================ TRAFFIC LIGHT HANDLING ================================

void SmartTrafficLight::callEventFunctions() {
    if (state == GREEN && onGreen) onGreen();
    else if (state == YELLOW && onYellow) onYellow();
    else if (state == RED && onRed) onRed();
}

void SmartTrafficLight::turnOn(const uint8_t led_pin){
    assertBegun();

    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);
    
    callEventFunctions();

    digitalWrite(led_pin, HIGH);

    pinOn = led_pin;
}

void SmartTrafficLight::turnOff() {
    assertBegun();

    lastTimeTransition = millis();

    digitalWrite(pinOn, LOW);
    pinOn = NO_PIN;
}

void SmartTrafficLight::handleButton() {
    pressed = !digitalRead(buttonPin);

    if (pressed && (millis() - lastTimeTransition >= minGreenTime)) {
        state = YELLOW;
        turnOn(yellowPin);
    }
}

void SmartTrafficLight::handleGreen() {
    if (buttonPin != NO_PIN) handleButton();

    if (millis() - lastTimeTransition >= greenInterval) {
        state = YELLOW;
        turnOn(yellowPin);
    }
}

void SmartTrafficLight::handleYellow() {
    if (millis() - lastTimeTransition >= yellowInterval) {
        state = RED;
        turnOn(redPin);
    }
}

void SmartTrafficLight::handleRed() {
    if (millis() - lastTimeTransition >= redInterval) {
        state = GREEN;
        turnOn(greenPin);
    } 
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

void SmartTrafficLight::update() {
    assertBegun();

    switch (state) {
        case GREEN:
            handleGreen();
            break;
        
        case YELLOW:
            handleYellow();
            break;

        case RED:
            handleRed();
            break;

        case BLINKING_YELLOW:
            handleBlinking();
    }
}


// ================================ PUBLIC METHODS ================================

// Toggle mode functions

void SmartTrafficLight::startBlinking() {
    assertBegun();
    if (state == BLINKING_YELLOW) return;
    
    state = BLINKING_YELLOW;
    if (onStartBlink) onStartBlink();
    turnOn(yellowPin);
}

void SmartTrafficLight::stopBlinking() {
    assertBegun();
    if (state != BLINKING_YELLOW) return;
    
    state = GREEN;
    if (onStopBlink) onStopBlink();
    turnOn(greenPin);
}

void SmartTrafficLight::enable() {
    assertBegun();
    if (state != DISABLED) return;

    state = GREEN;
    if (onEn) onEn();
  	turnOn(greenPin);
}

void SmartTrafficLight::disable() {
    assertBegun();
    if (state == DISABLED) return;
    
    state = DISABLED;
    if (onDis) onDis();
    turnOff();
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