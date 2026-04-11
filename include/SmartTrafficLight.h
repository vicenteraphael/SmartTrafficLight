#ifndef SMARTTRAFFICLIGHT_H
#define SMARTTRAFFICLIGHT_H

#include <Arduino.h>

#define NO_PIN (255)
#define NO_INTERVAL (0)

#define DEFAULT_GREEN_INTERVAL (10000)
#define DEFAULT_YELLOW_INTERVAL (2000)
#define DEFAULT_RED_INTERVAL (5000)
#define DEFAULT_MIN_GREEN_TIME (5000)

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

        bool disabled = false;

        bool begun = false;
        bool pressed = false;
        unsigned long lastTimeTransition = 0;
        uint8_t pinOn = NO_PIN;
        
        void assertBegun();
        void handleButton();
        void handleGreen();
        void handleYellow();
        void handleRed();

        void handleDisabled();

        void (*onGreen)() = nullptr;
        void (*onRed)() = nullptr;

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

        void turnOn(const uint8_t led_pin);
        void turnOff();
        
        void disable();
        void enable();

        void onTurnGreen(void (*func)());
        void onTurnRed(void (*func)());
};

#endif