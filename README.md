# avr-moth
A breitenberg vehicle for attiny45 written in C
This breitenberg vehicle is designed to mimic a moth, following light. However, unlike a moth, it does not bump into the light source.

Electricals
ATTINY45 connected as follows:

- Pin 1 - PB5 - RESET - Connected to VCC
- Pin 2 - PB3 - Connected to left side voltage divider
- Pin 3 - PB4 - Connected to left side motor
- Pin 4 - GND - Connected to ground
- Pin 5 - PB0 - No connection, too many pins on this chip anyway (should really be attached to ground)
- Pin 6 - PB1 - Connected to right side motor
- Pin 7 - PB2 - Connected to right side voltage divider
- Pin 8 - VCC - Connected to VCC

Voltage divider is made up of a resistor connected to VCC and LDR connected to GND. Voltage rises when the LDR is deprived of light.
Output to motor goes through a zener diode to the gate of a mosfet. Motor connects to 6V and drain of mosfet. Source connected to ground.
Attiny must be powered using a separate power source to the motors. However, the ground connections must be common.

Code
After setting up the ADC and 'motor' pins as outputs, an empty while loop starts. Logic is fired purely by interrupts. 
When an analogue reading is taken, the interrupt fires and determines whether the left side or right side was read.
After reading and logging the voltage, the channel is switched so that the other side can be read on the next interrupt.
The difference between the left and right side voltages is tested. Whichever voltage is higher is darker and so the motor should be engaged to turn to towards the light.
Two deadzones have been built in - turn tolerance and advance tolerance.
- Turn tolerance determines whether the two voltages are roughly the same (roughly the same light values). This prevents rapid oscillation of the outputs.
- Advance tolerance determines how close the vehicle should get to the light source. Without this, the vehicle will constantly try to get as close as possible to the light source (basically impossible unless you are on the Sun).

Notes for possible improvements:
To improve the smoothness of the movement, PWM could be used but this does not seem to need it. This would possibly also reduce responsiveness.
A resistor-capacitor used as a filter on the voltage dividers could also have a similar effect.
The ADC readings could be averaged for the same result again - e.g take two or three readings before executing logic. Again, this does not seem to need it.

This took so many iterations to sort out. The electrics were the worst part - the code was a lot easier.
