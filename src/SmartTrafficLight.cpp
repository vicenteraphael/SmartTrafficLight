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
        Serial.println("Fatal: uninitialized...");
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
            break;

        case DISABLED_STATE:
            break;
    }
}


// ================================ PUBLIC METHODS ================================

// Alter state functions

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

void SmartTrafficLight::turnGreen() {
    assertBegun();
    if (state == RED_STATE) goTo(YELLOW_STATE);
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

State SmartTrafficLight::getState() {
    return state;
}

const char* SmartTrafficLight::getStringState() {
    return stringStates[state];
}

const uint8_t SmartTrafficLight::getPinOn() {
    return pinOn;
}