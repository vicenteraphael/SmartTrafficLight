#ifndef SMARTTRAFFICLIGHT_H
#define SMARTTRAFFICLIGHT_H

#include <Arduino.h>

#define NO_PIN (255)

class SmartTrafficLight {
    private:
        uint8_t greenPin;
        uint8_t yellowPin;
        uint8_t redPin;
        uint8_t buttonPin;

        
        unsigned long greenTimeout = NO_PIN;
        unsigned long yellowTimeout = NO_PIN;
        unsigned long redTimeout = NO_PIN;
        unsigned long buttonTimeout = NO_PIN;

        unsigned long minGreenTime;

        bool pressed = false;
        uint8_t pinOn = NO_PIN;
        unsigned long lastTimeTransition = 0;
        

        void turnOn(const uint8_t led_pin);
        void handleButton();
        void handleGreen();
        void handleYellow();
        void handleRed();

    public:
        SmartTrafficLight();

        SmartTrafficLight(
            uint8_t g_pin,
            uint8_t y_pin,
            uint8_t r_pin,
            uint8_t b_pin = NO_PIN // No button by default
        );

        void attach(
            uint8_t g_pin,
            uint8_t y_pin,
            uint8_t r_pin,
            uint8_t b_pin = NO_PIN // No button by default
        );

        void setIntervals(
            unsigned long g_timeout,
            unsigned long y_timeout,
            unsigned long r_timeout,
            unsigned long min_g_time = 5000 // Default minGreenTimeout
        );

        void begin();

        void update();
};

#endif