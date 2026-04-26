# API Reference - SmartTrafficLight methods


## Table of contents
1. [Quick start](#quick-start)
2. [Constructors](#constructors)
    - [`SmartTrafficLight()`](#smarttrafficlight)
    - [`attach()`](#attach)
    - [`setIntervals()`](#setintervals)
3. [Initialization and update](#initialization-and-update)
    - [`begin()`](#begin)
    - [`update()`](#update)
4. [State Control](#state-control)
    - [`enable()`](#enable)
    - [`disable()`](#disable)
    - [`startBlinking()`](#startblinking)
    - [`stopBlinking()`](#stopblinking)
    - [`turnGreen()`](#turngreen)
    - [`turnRed()`](#turnred)
5. [Getter methods](#getter-methods)
    - [`getPinOn()`](#getpinon)
    - [`getState()`](#getstate)
    - [`getStateToString()`](#getstatetostring)
6. [Event functions and callbacks](#event-functions-and-callbacks)
    - [`onTurnGreen()`](#onturngreen)
    - [`onTurnYellow()`](#onturnyellow)
    - [`onTurnRed()`](#onturnred)
    - [`onEnable()`](#onenable)
    - [`onDisable()`](#ondisable)
    - [`onStartBlinking()`](#onstartblinking)
    - [`onStopBlinking()`](#onstopblinking)
    - [`onAlterState()`](#onalterstate)
7. [Full example usage](#full-example-usage)

---

## Quick start

To install the library, follow these steps:

#### Using the Arduino IDE (recommended):

1. Access `Sketch` → `Include Library` `Manage Libraries... (Ctrl + Shift + I)`
2. Install `SmartTrafficLight` by Raphael Vicente de Oliveira
3. Include it in your code:
    ```
    #include <SmartTrafficLight.h>
    ```

#### Manual installation

1. Clone this repository (or download `.zip`):
    ```bash
    git clone https://github.com/vicenteraphael/SmartTrafficLight.git
    ```
2. Move it to your `Arduino/libraries/` folder
3. Restart the Arduino IDE
4. Include it in your code:

    ```cpp
    #include <SmartTrafficLight.h>
    ```
    ```

The example below shows the minimal setup required to run the traffic light

```cpp

#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void setup() {
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
}
```

Or with [`attach()`](#attach):

```cpp

#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
}
```

Typical usage flow:

1. Instantiate the object
2. **(Optional)** Configure pins with `attach()`
3. **(Optional)** Configure intervals with `setIntervals()`
4. Call `begin()`
5. Enable the system with `enable()` **(Required to start operation)**
6. Call `update()` continuously inside `loop()`

Common mistakes:

- Forgetting to call `begin()`
- Forgetting to call `enable()`
- Not calling `update()` inside `loop()`
- Calling `attach()` after `begin()`
- Forgetting to set the pins in the constructor or `attach()`

---


## Constructors


### `SmartTrafficLight()`


**Description:**

⚠️ Used to instantiate the class and, optionally, configure the LED pins

Creates an instance of `SmartTrafficLight` and, optionally, configures the pins to be used. Must be used before calling any other method. If the parameters are omitted, the pins can also be configured later by [`attach()`](#attach).


**Definition:**

```cpp
SmartTrafficLight() = default
SmartTrafficLight(const uint8_t gPin, const uint8_t yPin, const uint8_t rPin, const uint8_t bPin = NO_PIN)
```
> **Note:** `NO_PIN` is an internal macro with value `255`, which literally means "no pin"

**Parameters:**

- `void` or:
- `gPin`: Digital pin for the green LED
- `yPin`: Digital pin for the yellow LED
- `rPin`: Digital pin for the red LED
- `bPin`: Digital pin for the pedestrian button pin **(OPTIONAL)**


**Returns:**

- `SmartTrafficLight`

**Syntax:**
```cpp
SmartTrafficLight();
SmartTrafficLight(12, 8, 7);
SmartTrafficLight(12, 8, 7, 2);
```


In the first case, the constructor will only create an instance of SmartTrafficLight and return it. Therefore, the pins configuration will need to be done by using [`attach()`](#attach).

In the second case, the LED pins are being configured, except for the button pin, that is passed on in the third case.


**Example:**

```cpp
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);

void setup(){}

void loop(){}
```

If the parameters are omitted, creates the instance without reference to the pins, [`attach()`](#attach) is then required for setting up the pins.


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {}

void loop() {}
```


---


### `attach()`


**Description:**

⚠️ **CONDITIONALLY REQUIRED** - This method must be called and only if the pins were not set in the constructor, aka [`SmartTrafficLight()`](#smarttrafficlight)

Configures the pins to be used. Can be called to configure the pins instead of [`SmartTrafficLight()`](#smarttrafficlight)


**Definition:**

```cpp
void attach(const uint8_t gPin, const uint8_t yPin, const uint8_t rPin, const uint8_t bPin = NO_PIN)
```

> **Note:** `NO_PIN` is an internal macro with value `255`, which literally means "no pin"

**Parameters:**

- `gPin`: Digital pin for the green LED
- `yPin`: Digital pin for the yellow LED
- `rPin`: Digital pin for the red LED
- `bPin`: Digital pin for the pedestrian button pin **(OPTIONAL)**


**Returns:**

- `void`


**Syntax:**
```cpp
trafficLight.attach(12, 8, 7);
trafficLight.attach(12, 8, 7, 2);
```


**Example:**

```cpp
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

- Green interval        =   10000 milliseconds
- Yellow interval       =   2000 milliseconds
- Red interval          =   5000 milliseconds
- Minimum green time        =   5000 milliseconds


**Definition:**

```cpp
void setIntervals(const unsigned long gInterval, const unsigned long yInterval, const unsigned long rInterval, const unsigned long minGTime = DEFAULT_MIN_GREEN_TIME)
```


**Parameters:**

- `gInterval`: Amount of time, in milliseconds, in which the green pin shall be `HIGH`
- `yInterval`: Amount of time, in milliseconds, in which the yellow pin shall be `HIGH`
- `rInterval`: Amount of time, in milliseconds, in which the red pin shall be `HIGH`
- `minGTime`: **(OPTIONAL)** Minimum amount of time, in milliseconds, in which the green pin shall be `HIGH` before triggering the button. **DEFAULT VALUE:** 5000 milliseconds.

> **Note:** `DEFAULT_MIN_GREEN_TIME` is an internal macro for the default minimum green time (5000 milliseconds). The other literals are:

```cpp
#define DEFAULT_GREEN_INTERVAL (10000)
#define DEFAULT_YELLOW_INTERVAL (2000)
#define DEFAULT_RED_INTERVAL (5000)
#define DEFAULT_MIN_GREEN_TIME (5000)

#define BLINKING_INTERVAL (1000) // For ERROR_STATE and BLINKING_YELLOW_STATE
```


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.setIntervals(10000, 2000, 5000);
trafficLight.setIntervals(10000, 2000, 5000, 3000);

```


**Example:**

```cpp
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

⚠️ **REQUIRED** - This method must be called before using the traffic light

Initializes the system and checks if the pins were configured successfully. If not, the following message is displayed on the serial monitor (if `Serial.begin()` was previously called) and the program enters `ERROR_STATE`, which is a non-blocking state that triggers a constant blinking on the `LED_BUILTIN` pin (usually digital pin nº 13 or nº 2).

```
Fatal: uninitialized...
Use attach() to configure the pins
Use setIntervals() to customize the traffic light intervals
Use begin() to start the traffic light
```

> **Note:** the library is fail-safe: calling any public method before begin() will automatically trigger ERROR_STATE


**Definition:**

```cpp
void begin()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.begin();
```


**Example:**

```cpp
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

⚠️ **REQUIRED** - This method must be called as often as possible in order for the traffic light logic to work. The library is non-blocking and relies on `millis()`, so `update()` drives the internal state machine.

Updates the current state of the traffic light FSM using millis(). Needs to be continuously called inside `loop()`


**Definition:**

```cpp
void update()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.update();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);

void setup() {
    trafficLight.begin();
}

void loop() {
    trafficLight.update();
}
```


---


## State control

The methods in this section allow changing the current state of the traffic light FSM without interrupting its behaviour. The states are in the following format:

```cpp
enum State {
    GREEN_STATE, // Green light is active
    YELLOW_STATE, // Yellow light is active (transition before red)
    RED_STATE, // Red light is active
    BLINKING_YELLOW_STATE, // Blinking mode (night mode)
    DISABLED_STATE, // System is inactive (out of service)
    ERROR_STATE // For handling initialization error
};
```

In practice, the states can be represented by the following schema:

![SmartTrafficLight | Finite State Machine](/img/fsm.png)

> `Solid line`   = automatic transition (`timeout`) <br>
> `Dashed line`  = method call (`user-triggered`)


> `ANY STATE` → `BLINKING_YELLOW_STATE` = [`startBlinking()`](#startblinking) <br>
> `ANY STATE` → `DISABLED_STATE` = [`disable()`](#disable)

By default, the system starts on `DISABLED_STATE`


---


### `enable()`


**Description:**

⚠️ **REQUIRED** - This method must be called to start operation

Changes the current state from `DISABLED_STATE` to `GREEN_STATE`, enabling the traffic light for use. If the current state is different from `DISABLED_STATE`, the call is ignored.


**Definition:**

```cpp
void enable()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.enable();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(12, 11, 10, 9);
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

> **Note:** this is the default state in which the system starts


**Definition:**

```cpp
void disable()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.disable();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void setup() {
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

Changes the current state, whatever it may be, to `BLINKING_YELLOW_STATE`, also known as night or nocturnal mode.


**Definition:**

```cpp
void startBlinking()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.startBlinking();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(12, 11, 10, 9);
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

Changes the current state from `BLINKING_YELLOW_STATE` to `GREEN_STATE`, stopping the blinking mode. If the current state is different from `BLINKING_YELLOW_STATE`, the call is ignored.


**Definition:**

```cpp
void stopBlinking()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.stopBlinking();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void setup() {
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

Changes the current state from `RED_STATE` to `GREEN_STATE`. If the current state is different from `RED_STATE`, the call is ignored.


**Definition:**

```cpp
void turnGreen()
```


**Parameters:**

- `void`


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.turnGreen();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    trafficLight.attach(12, 11, 10, 9);
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

If the current state is `GREEN_STATE` or `YELLOW_STATE`, starts transition to `RED_STATE`. If on `GREEN_STATE`, the transition mandatorily passes by `YELLOW_STATE`. If the current state is different from those, the call is ignored.


**Definition:**

```cpp
void turnRed()
```

**Parameters:**

- `void`


**Returns:**

- `void`

**Syntax:**

```cpp
trafficLight.turnRed();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void setup() {
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

Returns the current `HIGH` LED pin. If no pin is currently `HIGH`, returns `NO_PIN` (255)


**Definition:**

```cpp
uint8_t getPinOn() const
```


**Parameters:**

- `void`


**Returns:**

- `uint8_t`: current `HIGH` LED pin. If no pin is `HIGH`, returns 255


**Syntax:**

```cpp
trafficLight.getPinOn();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
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
```cpp
State getState() const
```


**Parameters:**

- `void`

**Returns:**

- `enum State`: current state of the State Machine


**Syntax:**

```cpp
trafficLight.getState();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

#define GREEN_PIN 12
#define YELLOW_PIN 11
#define RED_PIN 10
#define BUTTON_PIN 9

SmartTrafficLight trafficLight(12, 11, 10, 9);

void setup() {
    Serial.begin(9600);
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


### `getStateToString()`


**Description:**

Returns the current state of the FSM as a string (`const char*`)


**Definition:**
```cpp
const char *getStateToString() const
```


**Parameters:**

- `void`

**Returns:**

- `const char*`: current state of the State Machine converted to string format


**Syntax:**

```cpp
trafficLight.getStateToString();
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();
    trafficLight.startBlinking();

    // Outputs: BLINKING_YELLOW_STATE
    Serial.println(trafficLight.getStateToString());
}

void loop() {
    trafficLight.update();
}
```


---

## Event functions and callbacks

The system has various built-in event functions that allow attaching custom callbacks are triggered after some specific changes of state happens. These functions should be called once and only accept pointers to functions or lambda functions (which requires C++11 support). If an event function is not set up, no callbacks are dispatched when the event occurs.


---


### `onTurnGreen()`

**Description:**

Dispatches its callback function when the state is changed to `GREEN_STATE`, that is, when the traffic light turns green.


**Definition:**

```cpp
void onTurnGreen(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onTurnGreen(my_func);
trafficLight.onTurnGreen([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void print_green_light() {
    Serial.println("Green light!");
}

void setup() {
    Serial.begin(9600);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnGreen(print_green_light);

    // trafficLight.onTurnGreen([]() {
    //     Serial.println("Green light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onTurnYellow()`


**Description:**

Dispatches its callback function when the state is changed to `YELLOW_STATE`, that is, when the traffic light turns yellow.


**Definition:**

```cpp
void onTurnYellow(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onTurnYellow(my_func);
trafficLight.onTurnYellow([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void print_yellow_light() {
    Serial.println("Yellow light!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnYellow(print_yellow_light);

    // trafficLight.onTurnYellow([]() {
    //     Serial.println("Yellow light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onTurnRed()`


**Description:**

Dispatches its callback function when the state is changed to `RED_STATE`, that is, when the traffic light turns red.


**Definition:**

```cpp
void onTurnRed(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onTurnRed(my_func);
trafficLight.onTurnRed([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void print_red_light() {
    Serial.println("Red light!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onTurnRed(print_red_light);
    
    // trafficLight.onTurnRed([]() {
    //     Serial.println("Red light!");
    // })
}

void loop() {
    trafficLight.update();
}
```


---


### `onEnable()`


**Description:**

Dispatches its callback function when the [`enable()`](#enable) method is called; that is, when the state is changed from `DISABLED_STATE` to `GREEN_STATE`.


**Definition:**


```cpp
void onEnable(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onEnable(my_func);
trafficLight.onEnable([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void print_enable() {
    Serial.println("Enabling...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();

    trafficLight.onEnable(print_enable);
    
    // trafficLight.onEnable([]() {
    //     Serial.println("Enabling...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis() >= 5000) {
        trafficLight.enable();
    }
}
```


---


### `onDisable()`


**Description:**

Dispatches its callback function when the state is changed to `DISABLED_STATE`, that is, when the [`disable()`](#disable) method is called.


**Definition:**


```cpp
void onDisable(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onDisable(my_func);
trafficLight.onDisable([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void print_disable() {
    Serial.println("Disabling...");
}

void setup() {
    Serial.begin(9600);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onDisable(print_disable);
    
    // trafficLight.onDisable([]() {
    //     Serial.println("Disabling...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis() >= 5000) {
        trafficLight.disable();
    }
}
```


---


### `onStartBlinking()`


**Description:**

Dispatches its callback function when the state is changed to `BLINKING_YELLOW_STATE`, that is, when the [`startBlinking()`](#startblinking) method is called.


**Definition:**

```cpp
void onStartBlinking(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Syntax:**

```cpp
trafficLight.onStartBlinking(my_func);
trafficLight.onStartBlinking([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void print_start_blinking() {
    Serial.println("Starting blinking...");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onStartBlinking(print_start_blinking);
    
    // trafficLight.onStartBlinking([]() {
    //     Serial.println("Starting blinking...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis() >= 5000) {
        trafficLight.startBlinking();
    }
}
```


---


### `onStopBlinking()`


**Description:**

Dispatches its callback function when the state is changed from `BLINKING_YELLOW_STATE` to `GREEN_STATE`; that is, when the [`stopBlinking()`](#stopblinking) method is called.


**Definition:**

```cpp
void onStopBlinking(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onStopBlinking(my_func);
trafficLight.onStopBlinking([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight(12, 11, 10, 9);

void print_stop_blinking() {
    Serial.println("Stopping blinking...");
}

void setup() {
    Serial.begin(9600);
    trafficLight.begin();
    trafficLight.startBlinking();

    trafficLight.onStopBlinking(print_stop_blinking);
    
    // trafficLight.onStopBlinking([]() {
    //     Serial.println("Stopping blinking...");
    // })
}

void loop() {
    trafficLight.update();
    if (millis() >= 5000) {
        trafficLight.stopBlinking();
    }
}
```


---


### `onAlterState()`


**Description:**

Dispatches its callback function when the current state is changed (to any other state).


**Definition:**

```cpp
void onAlterState(void (*func)())
```


**Parameters:**

- `void (*func)()`: Pointer to a function (callback)


**Returns:**

- `void`


**Syntax:**

```cpp
trafficLight.onAlterState(my_func);
trafficLight.onAlterState([]() {
    doSomething(); // Requires C++11 support
});
```


**Example:**

```cpp
#include <SmartTrafficLight.h>

SmartTrafficLight trafficLight{};

void print_alter_state() {
    Serial.println("State has been altered!");
}

void setup() {
    Serial.begin(9600);

    trafficLight.attach(12, 11, 10, 9);
    trafficLight.begin();
    trafficLight.enable();

    trafficLight.onAlterState(print_alter_state);
    
    // trafficLight.onAlterState([]() {
    //     Serial.println("State has been altered!");
    // })
}

void loop() {
    trafficLight.update();
    if (millis() >= 15000) {
        trafficLight.disable();
    }
    else if (millis() >= 10000) {
        trafficLight.startBlinking();
    }
}
```


---


## Full example usage

```cpp
#include <SmartTrafficLight.h>

#define GREEN_PIN (12)
#define YELLOW_PIN (8)
#define RED_PIN (7)
#define BUTTON_PIN (2)
#define GREEN_INTERVAL (5000)
#define YELLOW_INTERVAL (1000)
#define RED_INTERVAL (2000)
#define MIN_GREEN_TIME (2000)

SmartTrafficLight trafficLight{};
 
void print_green_yellow_red() {
    switch(trafficLight.getState()) {
        case GREEN_STATE:
            Serial.println("Turning Green...");
            break;
        case YELLOW_STATE:
            Serial.println("Turning Yellow...");
            break;
        case RED_STATE:
            Serial.println("Turning Red...");
            break;
    }
    Serial.print("Pin on: ");
    Serial.println(trafficLight.getPinOn());
}

void print_enable() {
	Serial.println("Enabling...");
}

void print_disable() {
	Serial.println("Disabling...");
}

void print_start_blinking() {
	Serial.println("Starting blinking...");
}

void print_stop_blinking() {
	Serial.println("Stopping blinking...");
}

void setup() {
  	Serial.begin(9600);
  
  	trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
      
  	trafficLight.onEnable(print_enable);
  	trafficLight.onDisable(print_disable);
  	trafficLight.onStartBlinking(print_start_blinking);
  	trafficLight.onStopBlinking(print_stop_blinking);
    trafficLight.onAlterState(print_green_yellow_red);
  	
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
```

See also:

01. [Hello World](/examples/01-HelloWorld/README.md)
02. [Testing States](/examples/02-TestingStates/README.md)
03. [Testing Callbacks](/examples/03-TestingCallbacks/README.md)
04. [All Together](/examples/04-AllTogether/README.md)

---


> "'I Dig a Pygmy', by Charles Hawtrey and the Deaf Aids... Phase One, in which Doris gets her oats!"