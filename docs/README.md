# Smart Traffic Light library

This library allows using an Arduino Board to easily and efficiently manage traffic lights, with support for pedestrian button and flexibility for communication between different traffic lights. It enhances experimentation, customization and user-control. For instance, each individual LED duration can be configured to the user liking.

The SmartTrafficLight uses a Finite State Machine (FSM), which not only permits non-blocking operation, but
control of different states and the implementation of event-driven behaviour such as dispatching of customized alerts and messages triggered by specific events.

## Installation

### Using the Arduino IDE:

#### By Sketch

1. Access `Sketch` → `Include Library` → `Manage Libraries... (Ctrl + Shift + I)`
2. Install `SmartTrafficLight` by Raphael Vicente de Oliveira
3. [Include it in your code](#Include-it-in-your-code)

#### By Manual installation

1. Clone this repository (or download `.zip`):
    ```bash
    git clone https://github.com/vicenteraphael/SmartTrafficLight.git
    ```
2. Move it to your `Arduino/libraries/` folder
3. Restart the Arduino IDE
4. [Include it in your code](#Include-it-in-your-code)


### Using PlatformIO:

### By dependency

1. Open [`platformio.ini`](https://docs.platformio.org/en/latest/projectconf/index.html), a project configuration file located in the root of PlatformIO project.
2. Add the following line to the lib_deps option of `[env:]` section:
    ```
    vicenteraphael/SmartTrafficLight@^2.0.1
    ```
4. Build a project, PlatformIO will automatically install dependencies.
5. [Include it in your code](#Include-it-in-your-code)


### By Command Line Interface (CLI)

1. Open PlatformIO Core CLI
2. Change directory (`cd`) to the PlatformIO project where [`platformio.ini`](https://docs.platformio.org/en/latest/projectconf/index.html) is located.
3. Copy the following [`pio pkg install`](https://docs.platformio.org/en/latest/core/userguide/pkg/cmd_install.html) command and paste into the CLI shell, press Enter:
    ``` bash
    pio pkg install --library "vicenteraphael/SmartTrafficLight@^2.0.1"
    ```
4. [Include it in your code](#Include-it-in-your-code)


### Include it in your code

`SmartTrafficLight` library provides the following header files that can be included in your project:

```cpp
#include <SmartTrafficLight.h>
```


---


## Circuit

### Hardware required

* Arduino Board
* 3 LEDs
* 3 Resistors (220Ω-1000Ω should work)
* Button (optional)
* Hook-up wires

### Specifications

1. Reserve 3 digital pins from the Arduino board to three LEDs for the traffic light, which are usually green, yellow and red. 

2. Use appropriate resistors for the LEDs. Generally, any one between 220Ω-1000Ω should work.

3. If wished, one more digital pin can be reserved for the pedestrian button.

4. Make sure to have a common GND wiring.

> [!NOTE]
> A resistor for the button is not needed once this library uses pin mode `INPUT_PULLUP`, which already uses the Arduino internal resistor for this matter.

### Schematic

![SmartTrafficLight Circuit](/img/traffic-light-schematic.jpeg)

## Examples

1. [Hello World](/examples/01-HelloWorld/README.md): an introduction to the library
2. [Testing States](/examples/02-TestingStates/README.md): an example of how to control the library states
3. [Testing Callbacks](/examples/03-TestingCallbacks/README.md): an example of how to use the library event functions
4. [All Together](/examples/04-AllTogether/README.md): an example demonstrating all functionalities together
5. [Intersection](/examples/05-Intersection/README.md): an example demonstrating a road intersection controlled by two traffic lights