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

SmartTrafficLight::SmartTrafficLight() {}

SmartTrafficLight::SmartTrafficLight(const uint8_t g_pin, const uint8_t y_pin, const uint8_t r_pin, const uint8_t b_pin) {
    attach(g_pin, y_pin, r_pin, b_pin);
}


// ================================ INITIALIZATION ================================

void SmartTrafficLight::assertBegun() {
    if (!begun) {
        Serial.begin(9600);
        Serial.println("Fatal: unitialized..\nUse attach() to configure the pins\nUse setIntervals() to customize the traffic light intervals");
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

    turnOn(greenPin);
}


// ================================ TRAFFIC LIGHT CONTROL ================================

void SmartTrafficLight::turnOn(const uint8_t led_pin){
    assertBegun();

    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);
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

    if (pressed && (millis() - lastTimeTransition >= minGreenTime)) turnOn(yellowPin);
}

void SmartTrafficLight::handleGreen() {
    if (buttonPin != NO_PIN) handleButton();

    if (millis() - lastTimeTransition >= greenInterval) turnOn(yellowPin);
}

void SmartTrafficLight::handleYellow() {
    if (millis() - lastTimeTransition >= yellowInterval) {
        turnOn(redPin);
        if (onRed) onRed();
    }
}

void SmartTrafficLight::handleRed() {
    if (millis() - lastTimeTransition >= redInterval) {
        turnOn(greenPin);
        if (onGreen) onGreen();
    } 
}

void SmartTrafficLight::handleDisabled() {
    if (pinOn == yellowPin) {
        if (millis() - lastTimeTransition >= yellowInterval) turnOff();
    }
    else {
        if (millis() - lastTimeTransition >= yellowInterval) turnOn(yellowPin);
    }
}

void SmartTrafficLight::update() {
    assertBegun();

    if (disabled)
        handleDisabled();

    else if (pinOn == greenPin)
        handleGreen();

    else if (pinOn == yellowPin)
        handleYellow();

    else if (pinOn == redPin)
        handleRed();
}

void SmartTrafficLight::disable() {
    assertBegun();
    disabled = true;
}

void SmartTrafficLight::enable() {
    assertBegun();
    disabled = false;
}

void SmartTrafficLight::onTurnGreen(void (*func)()) {
    assertBegun();
    onGreen = func;
}

void SmartTrafficLight::onTurnRed(void (*func)()) {
    assertBegun();
    onRed = func;
}