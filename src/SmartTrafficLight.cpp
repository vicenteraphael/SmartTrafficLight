#include "SmartTrafficLight.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN (2)
#endif

// ================================ CONSTRUCTORS ================================

void SmartTrafficLight::attach(const uint8_t gPin, const uint8_t yPin, const uint8_t rPin, const uint8_t bPin) {
    greenPin = gPin;
    yellowPin = yPin;
    redPin = rPin;
    buttonPin = bPin;
}

void SmartTrafficLight::setIntervals(const unsigned long gInterval, const unsigned long yInterval, const unsigned long rInterval, const unsigned long minGTime) {
    greenInterval = gInterval;
    yellowInterval = yInterval;
    redInterval = rInterval;
    minGreenTime = minGTime;
}

SmartTrafficLight::SmartTrafficLight() = default;

SmartTrafficLight::SmartTrafficLight(const uint8_t gPin, const uint8_t yPin, const uint8_t rPin, const uint8_t bPin) {
    attach(gPin, yPin, rPin, bPin);
}


// ================================ INITIALIZATION ================================

#ifndef UNITY_TEST
void SmartTrafficLight::printUninitializedError() const {
    Serial.println("Fatal: uninitialized...");
    Serial.println("Use attach() to configure the pins");
    Serial.println("Use setIntervals() to customize the traffic light intervals");
    Serial.println("Use begin() to start the traffic light");
}
#else // Ignore Serial during tests
    void SmartTrafficLight::printUninitializedError() const {}
#endif

bool SmartTrafficLight::assertInitialized() {
    if (!initialized) {
        printUninitializedError();
        printf("CUZAO");

        state = ERROR_STATE;
        initialized = true;

        pinMode(LED_BUILTIN, OUTPUT);
        lastTimeTransition = millis();

        return false;
    }
    return !(state == ERROR_STATE);
}

void SmartTrafficLight::begin() {
    // Safety verification
    if (greenPin == NO_PIN || yellowPin == NO_PIN || redPin == NO_PIN) {
        assertInitialized();
        return;
    }
    initialized = true;

    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
    if (buttonPin != NO_PIN) pinMode(buttonPin, INPUT_PULLUP);
}


// ================================ TRAFFIC LIGHT HANDLING ================================

void SmartTrafficLight::turnOn(const uint8_t ledPin){
    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);

    digitalWrite(ledPin, HIGH);

    pinOn = ledPin;
}

void SmartTrafficLight::turnOff() {
    lastTimeTransition = millis();

    if (pinOn != NO_PIN) digitalWrite(pinOn, LOW);
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

void SmartTrafficLight::handleError() {
    if (isLedBuiltinBlinking) {
        if (millis() - lastTimeTransition >= BLINKING_INTERVAL) {
            lastTimeTransition = millis();
            digitalWrite(LED_BUILTIN, LOW);
            isLedBuiltinBlinking = false;
        }
    } else {
        if (millis() - lastTimeTransition >= BLINKING_INTERVAL) {
            lastTimeTransition = millis();
            digitalWrite(LED_BUILTIN, HIGH);
            isLedBuiltinBlinking = true;
        }
    }
}


// ================================ STATE MACHINE ================================

void SmartTrafficLight::goTo(State newState) {
    if (!assertInitialized()) return;

    State oldState = state;
    state = newState;

    switch (newState) {
        case GREEN_STATE:
            turnOn(greenPin);
            if (oldState == DISABLED_STATE && onEn) onEn();
            else if (oldState == BLINKING_YELLOW_STATE && onStopBlink) onStopBlink();
            if (onGreen) onGreen();
            break;

        case YELLOW_STATE:
            turnOn(yellowPin);
            if (onYellow) onYellow();
            break;

        case RED_STATE:
            turnOn(redPin);
            if (onRed) onRed();
            break;

        case BLINKING_YELLOW_STATE:
            turnOn(yellowPin);
            if (onStartBlink) onStartBlink();
            break;

        case DISABLED_STATE:
            turnOff();
            if (onDis) onDis();
            break;

        default:
            break;

    }
    if (onAlter) onAlter();
}

void SmartTrafficLight::update() {
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

        case ERROR_STATE:
            handleError();
            break;

        default:
            break;
    }
}


// ================================ PUBLIC METHODS ================================

// State control functions

void SmartTrafficLight::enable() {
    if (!assertInitialized()) return;
    if (state != DISABLED_STATE) return;

    goTo(GREEN_STATE);
}

void SmartTrafficLight::disable() {
    if (!assertInitialized()) return;
    if (state == DISABLED_STATE) return;

    goTo(DISABLED_STATE);
}

void SmartTrafficLight::startBlinking() {
    if (!assertInitialized()) return;
    if (state == BLINKING_YELLOW_STATE) return;
    
    goTo(BLINKING_YELLOW_STATE);
}

void SmartTrafficLight::stopBlinking() {
    if (!assertInitialized()) return;
    if (state != BLINKING_YELLOW_STATE) return;
    
    goTo(GREEN_STATE);
}

void SmartTrafficLight::turnGreen() {
    if (!assertInitialized()) return;
    if (state == RED_STATE) goTo(GREEN_STATE);
}

void SmartTrafficLight::turnRed() {
    if (!assertInitialized()) return;
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

State SmartTrafficLight::getState() const {
    return state;
}

const char* SmartTrafficLight::getStateToString() const {
    switch (state) {
        case GREEN_STATE:
            return "GREEN_STATE";
        case YELLOW_STATE:
            return "YELLOW_STATE";
        case RED_STATE:
            return "RED_STATE";
        case BLINKING_YELLOW_STATE:
            return "BLINKING_YELLOW_STATE";
        case DISABLED_STATE:
            return "DISABLED_STATE";
        case ERROR_STATE:
            return "ERROR_STATE";
    }
    return "UNKNOWN_STATE"; // just to avoid warnings :/
}

uint8_t SmartTrafficLight::getPinOn() const {
    return pinOn;
}