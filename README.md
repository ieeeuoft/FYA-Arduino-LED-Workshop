# 2023-FYA-Arduino-LED-Workshop
IEEE University of Toronto Student Branch FYA Workshop for Arduino and LED Matricies

final_version contains code used to demonstrate a LED matrix circuit. This circuit was used to teach IEEE Tech Team first year associates about the fundamentals of Arduino programming and circuit building. 

Below is a picture of the completed circuit:
![PXL_20231022_204059777](https://github.com/GeoFryer/2023-FYA-Arduino-LED-Workshop/assets/100430104/bea2d106-f8d1-4541-b5fd-2777d5f2a00a)

Note that the LED matrix is a 8x8 red-green LED matrix with 24 pins. It is oriented such that the model number is facing away in the picture. An Adafruit HT16K33 LED Driver is used to control the LED Matrix. 

Buttons in the background are designed with 10k pull-down resistors. These are connected to pins 2, 3, 4 of the Arduino.

Jumper cables running from the LED driver to LED matrix may be twisted. Be careful with the orientation of these wires.

The LED and resistor in the background on the breadboard is connected to pin 9 of the Arduino. 
