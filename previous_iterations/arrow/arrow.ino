#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

uint64_t counter = 0;
uint16_t delayTime = 100;
uint8_t colourCounter = 0;

const uint64_t arrow = 0x18181899db7e3c18;

void clearMatrix(void) {
    for(int c=0; c < 8; c++){
        matrix.displaybuffer[c] = 0;
    } 
    matrix.writeDisplay();
}

void setup() {
    Serial.begin(9600);  
    matrix.begin(0x70);  // pass in the address
    matrix.setBrightness(10);
    counter = 0b11111111;
    clearMatrix();
}

void loop() {

    //Going in
    for (int i = 0; i < 8; i++){
        for (int transfer = 7; transfer >= 0; transfer--){
            if (transfer == 0){
                matrix.displaybuffer[0] = 0;
            }
            else {
                matrix.displaybuffer[transfer] = matrix.displaybuffer[transfer - 1];
            }
        }

        if (colourCounter == 0){
            matrix.displaybuffer[0] = (arrow & counter) >> (i*8);
        }
        else if (colourCounter == 1){
            matrix.displaybuffer[0] = ((arrow & counter) >> (i*8)) << 8;
        }
        else if (colourCounter == 2){
            matrix.displaybuffer[0] = (arrow & counter) >> (i*8);
            matrix.displaybuffer[0] |= ((arrow & counter) >> (i*8)) << 8;
        }
            
        counter = counter << 8;
        matrix.writeDisplay();
        delay(delayTime);
    }

    //Going out
    for (int n = 0; n < 4; n++){
        for (int i=7; i >= 0; i--){
            if (i == 0){
                matrix.displaybuffer[0] = 0;
            }
            else {
                matrix.displaybuffer[i] = matrix.displaybuffer[i-1];
            }
        }
        matrix.writeDisplay();
        delay(delayTime);
    }

    counter = 0b11111111;
    colourCounter++;
    if (colourCounter == 3){
        colourCounter = 0;
    }
}


