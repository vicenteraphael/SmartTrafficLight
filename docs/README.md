# Smart Traffic Light library

This library allows using an Arduino Board to easily and efficiently manage traffic lights, with support for pedestrian button and flexibility for communication between different traffic lights. It enhances experimentation, customization and user-control. For instance, each individual LED duration can be configured to the user liking.

The SmartTrafficLight uses a Finite State Machine (FSM), which not only permits non-blocking operation, but
control of different states and the implementation of event-driven behaviour such as dispatching of customized alerts and messages triggered by specific events.

# Installation

1. Download the repository by running the following command:
    ```bash copy
    git clone https://github.com/vicenteraphael/SmartTrafficLight.git
    ```
2. Move it to your `Arduino/libraries/` folder
3. Restart the Arduino IDE
4. Include it in your code:

    ```cpp copy
    #include <SmartTrafficLight.h>
    ```

# Circuit

## Hardware required

* Arduino Board
* 3 LEDs
* 3 Resistors (220Ω-1000Ω should work)
* Button (optional)
* Hook-up wires

## Specifications

1. Reserve 3 digital pins from the Arduino board to three LEDs for the traffic light, which are usually green, yellow and red. 

2. Use appropriate resistors for the LEDs. Generally, any one between 220Ω-1000Ω should work.

3. If wished, one more digital pin can be reserved for the pedestrian button.

4. Make sure to have a common GND wiring.

> **Please note** that a resistor for the button is not needed once this library uses pin mode `INPUT_PULLUP`, which already uses the Arduino internal resistor for this matter.

## Schematic

![SmartTrafficLight Circuit](/examples/img/traffic-light-schematic.jpeg)

# Examples

1. [Hello World](/examples/01-HelloWorld/README.md): an introduction to the livrary
2. [Testing States](/examples/02-TestingStates/README.md): an example of how to control the library states
3. [Testing Callbacks](/examples/03-TestingCallbacks/README.md): an example of how to use the library event functions
4. [All Together](/examples/04-AllTogether/README.md): an example demonstrating all functionalities together