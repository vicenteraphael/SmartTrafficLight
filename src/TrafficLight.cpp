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

void SmartTrafficLight::begin(bool mode) {
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
  
  	mode ? enable() : disable();
}


// ================================ TRAFFIC LIGHT CONTROL ================================

void SmartTrafficLight::turnOn(const uint8_t led_pin){
    assertBegun();

    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);
    
    if (led_pin == greenPin && onGreen) onGreen();
    else if (led_pin == redPin && onRed) onRed();

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
    if (millis() - lastTimeTransition >= yellowInterval) turnOn(redPin);
}

void SmartTrafficLight::handleRed() {
    if (millis() - lastTimeTransition >= redInterval) turnOn(greenPin);
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
    if (disabled) return;
    
    disabled = true;
    turnOn(yellowPin);
}

void SmartTrafficLight::enable() {
    assertBegun();
    if (!disabled && pinOn != NO_PIN) return;

    disabled = false;
  	turnOn(greenPin);
}


void SmartTrafficLight::onTurnGreen(void (*func)()) {
    onGreen = func;
}

void SmartTrafficLight::onTurnRed(void (*func)()) {
    onRed = func;
}