#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

uint8_t counter = 0;
uint16_t delayTime = 500;

void clearMatrix(void) {
    for(int c=0; c < 8; c++){
        matrix.displaybuffer[c] = 0;
    } 
    matrix.writeDisplay();
}

void drawLine(char *colour) {
    if (strcmp(colour, "GREEN") == 0) {
        matrix.displaybuffer[0] = 0b1111111100000000;
    }
    else if(strcmp(colour, "YELLOW") == 0){
        matrix.displaybuffer[0] = 0b1111111111111111;
    }
    else {
        matrix.displaybuffer[0] = 0b11111111;
    }
    //matrix.writeDisplay();
}

void setup() {
    Serial.begin(9600);  
    matrix.begin(0x70);  // pass in the address
    counter = 1;
}

void loop() {

    for (int i=7; i >= 0; i--){
        if (i == 0){
            matrix.displaybuffer[i] = 0;
        }
        else {
            matrix.displaybuffer[i] = matrix.displaybuffer[i-1];
        }
    }
    
    if (counter == 1) {
        drawLine("RED");
    }
    else if (counter == 3) {
        drawLine("YELLOW");
    }
    else if (counter == 5) {
        drawLine("GREEN");
    }

    counter++;

    if (counter == 7){
        counter = 1;
    }

    delay(delayTime);
    matrix.writeDisplay();
}


