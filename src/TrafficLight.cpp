#include "SmartTrafficLight.h"

SmartTrafficLight::SmartTrafficLight() {}

SmartTrafficLight::SmartTrafficLight(uint8_t g_pin, uint8_t y_pin, uint8_t r_pin, uint8_t b_pin) {
    attach(g_pin, y_pin, r_pin, b_pin);
}

void SmartTrafficLight::attach(uint8_t g, uint8_t y, uint8_t r, uint8_t b) {
    greenPin = g;
    yellowPin = y;
    redPin = r;
    buttonPin = b;

    // Default intervals
    setIntervals(10000, 2000, 5000, 5000);
}

void SmartTrafficLight::setIntervals(unsigned long g_timeout, unsigned long y_timeout, unsigned long r_timeout, unsigned long b_timeout) {
    greenTimeout = g_timeout;
    yellowTimeout = y_timeout;
    redTimeout = r_timeout;
    buttonTimeout = b_timeout;
}

void SmartTrafficLight::begin(){
    // Safety verification
    if (greenPin == NO_PIN || yellowPin == NO_PIN || redPin == NO_PIN) return;

    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
    if (buttonPin != NO_PIN) pinMode(buttonPin, INPUT_PULLUP);

    turnOn(greenPin);
}

void SmartTrafficLight::turnOn(const uint8_t led_pin){
    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);
    digitalWrite(led_pin, HIGH);

    pinOn = led_pin;
}

void SmartTrafficLight::handleButton(){
    pressed = !digitalRead(buttonPin);

    if (pressed && (millis() - lastTimeTransition >= minGreenTime)) turnOn(yellowPin);
}

void SmartTrafficLight::handleGreen(){
    if (buttonPin != NO_PIN) handleButton();

    if (millis() - lastTimeTransition >= greenTimeout) turnOn(yellowPin);
}

void SmartTrafficLight::handleYellow(){
    if (millis() - lastTimeTransition >= yellowTimeout) turnOn(redPin);
}

void SmartTrafficLight::handleRed(){
    if (millis() - lastTimeTransition >= redTimeout) turnOn(greenPin);
}

void SmartTrafficLight::update(){
    // Safety verification
    if (pinOn == NO_PIN) return;

    if (pinOn == greenPin)
        handleGreen();

    else if (pinOn == yellowPin)
        handleYellow();

    else if (pinOn == redPin)
        handleRed();
}