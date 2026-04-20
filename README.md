# SmartTrafficLight


![Arduino](https://img.shields.io/badge/platform-Arduino-blue)
![License](https://img.shields.io/badge/license-MIT-green)

An easy-to-use, non-blocking Arduino library for building smart traffic light systems with support for pedestrian buttons and event-driven behavior.


---


## Features

- Traffic light cycle handling
- Support for pedestrian button
- Blinking (nocturnal) mode
- Enabled/Disabled mode
- Event-driven architecture


---


## Installation

1. Download the repository by running the following command:
    ```bash copy
    git clone https://github.com/vicenteraphael/SmartTrafficLight.git
    ```
2. Move it to your `Arduino/libraries/` folder
3. Restart the Arduino IDE


---


## Example usage

```cpp copy
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

void setup() {
    trafficLight.attach(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
    trafficLight.setIntervals(GREEN_INTERVAL, YELLOW_INTERVAL, RED_INTERVAL, MIN_GREEN_TIME);
    
    trafficLight.onTurnGreen([]() {
        Serial.println("Turning green...");
    });
  
    trafficLight.begin();
    trafficLight.enable();
}

void loop() {
    trafficLight.update();
}
```


---


### How it works

1. Connect your LEDs and (optionally) a button, then call `attach()`
2. Configure timing using `setIntervals()`
3. Initialize the system with `begin()`
4. Start the traffic light with `enable()`
5. Call `update()` continuously inside `loop()` <br><br>

Note: You can also pass the pins directly through the constructor instead of calling `attach()`

Like this:

```cpp copy
SmartTrafficLight trafficLight(GREEN_PIN, YELLOW_PIN, RED_PIN, BUTTON_PIN);
```


---


## Architecture

This library implements a Finite State Machine (FSM) to ensure non-blocking operation. The states are the following:

- `GREEN_STATE`
- `YELLOW_STATE`
- `RED_STATE`
- `BLINKING_YELLOW_STATE`
- `DISABLED_STATE`


### Alter state functions

You can, at any moment, change the state of the system without interrupting its behaviour

- `startBlinking()` → enters `BLINKING_YELLOW_STATE`
- `stopBlinking()` → leaves `BLINKING_YELLOW_STATE` and goes to `GREEN_STATE`
- `enable()` → starts up the system and goes to `GREEN_STATE`
- `disable()` → turns the system off and goes to `DISABLED_STATE`
- `turnGreen()` → starts transition from `RED_STATE` to `GREEN_STATE`
- `turnRed()` → starts transition from `GREEN_STATE` to `RED_STATE` (passing by `YELLOW_STATE`) or from `YELLOW_STATE` to `RED_STATE`


### Event Functions

You can attach custom callbacks that will be triggered when the state changes:

- `onTurnGreen()` → called when the light turns green
- `onTurnYellow()` → called when the light turns yellow
- `onTurnRed()` → called when the light turns red
- `onEnable()` → called when the system is enabled
- `onDisable()` → called when the system is disabled
- `onStartBlinking()` → called when the system enters blinking mode
- `onStopBlinking()` → called when the system stops blinking
- `onAlterState()` → called whenever the state is changed


### Getter functions

You can use these functions to access state-related attributes:

- `getState()` → returns current state in enum State format
- `getStringState()` → returns current state in string format
- `getPinOn()` → returns current HIGH LED pin number (255 meaning no pin is HIGH)


---


## Documentation

Full API reference available in [docs/API.md](docs/API.md)


---


## License

[MIT License](LICENSE)

Copyright (c) 2026 Raphael Vicente de Oliveira

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.