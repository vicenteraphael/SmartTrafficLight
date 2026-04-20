# API Reference - SmartTrafficLight methods


## Table of contents

1. [Constructors](#constructors)
    - [`SmartTrafficLight()`](#smarttrafficlight)
    - [`attach()`](#attach)
    - [`setIntervals()`](#setintervals)
2. [Initialization and update](#initialization-and-update)
    - [`begin()`](#begin)
    - [`udpate()`](#update)
3. [Alter State](#alter-state)
    - [`enable()`](#enable)
    - [`disable()`](#disable)
    - [`startBlinking()`](#startblinking)
    - [`stopBlinking()`](#stopblinking)
    - [`turnGreen()`](#turngreen)
    - [`turnRed()`](#turnred)
4. [Getter methods](#getter-methods)
    - [`getPinOn()`](#getpinon)
    - [`getState()`](#getstate)
    - [`getStringState()`](#getstringstate)
5. [Event functions and callbacks](#event-functions-and-callbacks)
    - [`onTurnGreen()`](#onturngreen)
    - [`onTurnYellow()`](#onturnyellow)
    - [`onTurnRed()`](#onturnred)
    - [`onEnable()`](#onenable)
    - [`onDisable()`](#ondisable)
    - [`onStartBlinking()`](#onstartblinking)
    - [`onStopBlinking()`](#onstopblinking)
    - [`onAlterState()`](#onalterstate)


---


## Constructors


### `SmartTrafficLight()`


**Description:**

⚠️ This method must be called to instantiate the library and, optionally, configure the LED pins

Creates and instance of `SmartTrafficLight` and, optionally, configures the pins to be used. Must be called before using the system. If the parameters are ommited, the pins can also be configured later by [`attach()`](#attach).


**Definition:**

```cpp copy
SmartTrafficLight() = default
SmartTrafficLight(const uint8_t g_pin, const uint8_t y_pin, const uint8_t r_pin, const uint8_t b_pin = NO_PIN)
```


**Parameters:**

- `void` or:
- `g_pin`: Digital pin for the green LED
- `y_pin`: Digital pin for the yellow LED
- `r_pin`: Digital pin for the red LED
- `b_pin`: Digital pin for the button LED (OPTIONAL)


**Returns:**

- `SmartTrafficLight`

**Syntax:**
```cpp copy
SmartTrafficLight();
SmartTrafficLight(12, 8, 7);
SmartTrafficLight(12, 8, 7, 2);
```


In the first case, the constructor will only create an instance of SmartTrafficLight and return it. Therefore, the pins configuration will need to be done by using [`attach()`](#attach).

In the second case, the pins are being configured, except for the button, that is passed on in the third case.


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);

void setup(){}

void loop(){}
```

If the parameters are ommited, creates the instance without reference to the pins, [`attach()`](#attach) is then required for setting up the pins.


**Example:**

```cpp copy
#include <SmartTrafficLight>

SmartTrafficLight trafficLight{};

void setup() {}

void loop() {}
```


---


### `attach()`


**Description:**

⚠️ This method must be called if, and only if, the pins weren't configured in the constructor, aka [`SmartTrafficLight()`]((#smarttrafficlight))

Configures the pins to be used. Can be called to configure the pins instead of [`SmartTrafficLight()`](#smarttrafficlight)


**Definition:**

```cpp copy
void attach(const uint8_t g_pin, const uint8_t y_pin, const uint8_t r_pin, const uint8_t b_pin = NO_PIN)
```


**Parameters:**

- `g_pin`: Digital pin for the green LED
- `y_pin`: Digital pin for the yellow LED
- `r_pin`: Digital pin for the red LED
- `b_pin`: Digital pin for the button LED (OPTIONAL)


**Returns:**

- `void`


**Syntax:**
```cpp copy
trafficLight.attach(12, 8, 7);
trafficLight.attach(12, 8, 7, 2);
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
}

void loop() {}
```


---


### `setIntervals()`


**Description:**

Configures each individual LED display timing, along with the minimum green time for the button timeout. If not called, the values are defined by default:

- Green interval        =   10000 ms
- Yellow interval       =   2000 ms
- Red interval          =   50000 ms
- Min green time        =   5000 ms


**Definition:**

```cpp copy
void setIntervals(const unsigned long g_interval, const unsigned long y_interval, const unsigned long r_interval, const unsignedlong min_g_time = DEFAULT_MIN_GREEN_TIME)
```


**Parameters:**

- `g_interval`: Amount of time, in milliseconds, in which the green pin shall be HIGH
- `y_interval`: Amount of time, in milliseconds, in which the green pin shall be HIGH
- `r_interval`: Amount of time, in milliseconds, in which the green pin shall be HIGH
- `min_green_time`: Minimum amount of time, in milliseconds, in which the green pin shall be HIGH before triggering the button (OPTIONAL: default value = 5000 ms)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.setIntervals(10000, 2000, 5000);
trafficLight.setIntervals(10000, 2000, 5000, 3000);

```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_TIME 60000
#define YELLOW_TIME 5000
#define RED_TIME 30000
#define MIN_GREEN_TIME 30000

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.setIntervals(GREEN_TIME, YELLOW_TIME, RED_TIME, MIN_GREEN_TIME);
}

void loop() {}
```


---


## Initialization and update


### `begin()`


**Description:**

⚠️ This method must be called before using the traffic light

Initializes the system and checks if the pins were configured succesfully. If not, the following message is displayed on the serial monitor and the program is freezed:

```
Fatal: unitialized...
Use attach() to configure the pins
Use setIntervals() to customize the traffic light intervals
Use begin() to start the traffic light
```

If, by chance, `begin()` is not called before for initializatoin, the same message and behaviour will occurr when a public method is called.


**Definition:**

```cpp copy
void begin()
```


**Parameters:**

- `void`;


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.begin();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
}

void loop() {}
```


---


### `update()`


**Description:**

⚠️ This method must be called as often as possible in order for the traffic light logic to work

Updates the current state of the traffic light FSM using millis(). Needs to be continously called inside `loop()`


**Definition:**

```cpp copy
void update()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.update();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
}

void loop() {
    trafficLight.update();
}
```


---


## Alter state

The methods in this section allow changing the current state of the traffic light FSM without interrupting its behaviour. The states are:

- `GREEN_STATE`
- `YELLOW_STATE`
- `RED_STATE`
- `BLINKING_YELLOW_STATE`
- `DISABLED_STATE`

By default, the system starts on `DISABLED_STATE`


---


### `enable()`


**Description:**

Changes the current state from `DISABLED_STATE` to `GREEN_STATE`, enabling the traffic light for use


**Definition:**

```cpp copy
void enable()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.enable();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
}
```


---


### `disable()`


**Description:**

Changes the current state, whatever it may be, to `DISABLED_STATE`, taking the entire traffic light out of service.

> Note: this is the default state in which the system starts


**Definition:**

```cpp copy
void disable()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.disable();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
    if (millis() >= 10000) {
        trafficLight.disable(); // Disables the traffic light after 10 seconds of service
    }
}
```


---


### `startBlinking()`


**Description:**

Changes the current state to `BLINKING_YELLOW_STATE`, also known as night or nocturnal mode. 


**Definition:**

```cpp copy
void startBlinking()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.startBlinking();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.startBlinking();
}

void loop() {
    trafficLight.update();
}
```


---


### `stopBlinking()`


**Description:**

Changes the current state from `BLINKING_YELLOW_STATE` to `GREEN_STATE`, stopping the blinking mode.


**Definition:**

```cpp copy
void stopBlinking()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.stopBlinking();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.startBlinking();
}

void loop() {
    trafficLight.update();
    if (millis() >= 10000) { // stops blinking after 10 seconds
        trafficLight.stopBlinking();
    }
}
```


---


### `turnGreen()`


**Description:**

If the traffic light is enabled and on `RED_STATE`, the state is then changed to `GREEN_STATE`.


**Definition:**

```cpp copy
void turnGreen()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.turnGreen();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
    // The first cycle will have only 2 seconds of red interval
    if (millis() >= 14000) {
        trafficLight.turnGreen();
    }
}
```


---


### `turnRed()`


**Description:**

If the current state is `GREEN_STATE` or `YELLOW_STATE`, starts transition to `RED_STATE`. If on `GREEN_STATE`, the transition mandatorily passes by `YELLOW_STATE`.


**Definition:**

```cpp copy
void turnRed()
```

**Parameters:**

- `void`


**Returns:**

- `void`

**Syntax:**

```cpp copy
trafficLight.turnRed();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
    // The first cycle will have only 2 seconds of green interval
    if (millis() >= 20000) {
        trafficLight.turnRed();
    }
}
```


---


## Getter methods

The system has built-in getter functions that allow accessing state-related attributes


---


### `getPinOn()`

**Description:**

Returns the current HIGH LED pin. If no pin is HIGH, returns 255


**Definition:**

```cpp copy
const uint8_t getPinOn()
```


**Parameters:**

- `void`


**Returns:**

- `const uint8_t`: current HIGH LED pin. If no pin is HIGH, returns 255


**Syntax:**

```cpp copy
trafficLight.getPinOn();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.startBlinking();

    // Outputs 11
    Serial.println(trafficLight.getPinOn());
}

void loop() {
    trafficLight.update();
}
```


---


### `getState()`


**Description:**

Returns the current state of the FSM, an enum State variable


**Definition:**
```cpp copy
void getState()
```


**Parameters:**

- `void`

**Returns:**

- `enum State`: current state of the State Machine


**Syntax:**

```cpp copy
trafficLight.getState();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();

    // Outputs: Disabled... Call enable()
    if (trafficLight.getState() == DISABLED_STATE) {
        Serial.println("Disabled... Call enable()");
    }
    else {
        Serial.println("Enabled");
    }

    trafficLight.enable();
}

void loop() {
    trafficLight.update();
}
```


---


### `getStringState()`


**Description:**

Returns the current state of the FSM as an string (const char*)


**Definition:**
```cpp copy
const char *getStringState()
```


**Parameters:**

- `void`

**Returns:**

- `const char*`: current state of the State Machine in string format


**Syntax:**

```cpp copy
trafficLight.getStringState();
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.startBlinking();

    // Outputs: BLINKING_YELLOW_STATE
    Serial.println(trafficLight.getStringState());
}

void loop() {
    trafficLight.update();
}
```


---

## Event functions and callbacks


### `onTurnGreen()`


**Definition:**

```cpp copy
void onTurnGreen(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onTurnGreen(my_func);
trafficLight.onTurnGreen([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_green_light() {
    Serial.println("Green light!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnGreen(print_green_light);

    // trafficLight.onTurnGreen(()[] {
    //     Serial.println("Green light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onTurnYellow()`


**Definition:**

```cpp copy
void onTurnYellow(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onTurnYellow(my_func);
trafficLight.onTurnYellow([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_yellow_light() {
    Serial.println("Yellow light!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnYellow(print_yellow_light);

    // trafficLight.onTurnYellow(()[] {
    //     Serial.println("Yellow light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onTurnRed()`


**Definition:**

```cpp copy
void onTurnRed(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onTurnRed(my_func);
trafficLight.onTurnRed([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_red_light() {
    Serial.println("Red light!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnRed(print_red_light);
    
    // trafficLight.onTurnRed(()[] {
    //     Serial.println("Red light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onEnable()`


**Definition:**


```cpp copy
void onEnable(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onEnable(my_func);
trafficLight.onEnable([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_enable() {
    Serial.println("Enabling...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();

    trafficLight.onEnable(print_enable);
    
    // trafficLight.onEnable(()[] {
    //     Serial.println("Enabling...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis >= 5000) {
        trafficLight.enable();
    }
}
```


---


### `onDisable()`


**Definition:**


```cpp copy
void onDisable(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onDisable(my_func);
trafficLight.onDisable([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_disable() {
    Serial.println("Disabling...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onDisable(print_disable);
    
    // trafficLight.onDisable(()[] {
    //     Serial.println("Disabling...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis >= 5000) {
        trafficLight.disable();
    }
}
```


---


### `onStartBlinking()`


**Definition:**

```cpp copy
void onStartBlinking(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Syntax:**

```cpp copy
trafficLight.onStartBlinking(my_func);
trafficLight.onStartBlinking([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_start_blinking() {
    Serial.println("Starting blinking...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onStartBlinking(print_start_blinking);
    
    // trafficLight.onStartBlinking(()[] {
    //     Serial.println("Starting blinking...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis >= 5000) {
        trafficLight.startBlinking();
    }
}
```


---


### `onStopBlinking()`


**Definition:**

```cpp copy
void onStopBlinking(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onStopBlinking(my_func);
trafficLight.onStopBlinking([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_stop_blinking() {
    Serial.println("Stopping blinking...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.startBlinking();

    trafficLight.onStopBlinking(print_stop_blinking);
    
    // trafficLight.onStopBlinking(()[] {
    //     Serial.println("Stopping blinking...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis >= 5000) {
        trafficLight.StopBlinking();
    }
}
```


---


### `onAlterState()`


**Definition:**

```cpp copy
void onAlterState(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp copy
trafficLight.onAlterState(my_func);
trafficLight.onAlterState([]() {
    doSomething;
});
```


**Example:**

```cpp copy
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight{};

void print_alter_state() {
    Serial.println("State has been altered!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onAlterState(print_alter_state);
    
    // trafficLight.onAlterState(()[] {
    //     Serial.println("State has been altered!");
    // })
}

void loop() {
    trafficLight.update();
    if (millis >= 15000) {
        trafficLight.disable();
    }
    else if (millis >= 10000) {
        trafficLight.startBlinking();
    }
}
```


---


> "'I Dig a Pygmy', by Charles Hawtrey and the Deaf Aids... Phase One, in which Doris gets her oats!"