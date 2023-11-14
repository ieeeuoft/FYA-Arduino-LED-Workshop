#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#ifndef _BV
  #define _BV(bit) (1<<(bit))
#endif

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();

uint8_t counter = 0;
uint16_t delayTime = 1000;
uint64_t binaryAnd = 0b11111111;
bool buttonPressed = false;
int buttonState = 0;


const uint64_t checkmark[8] = {0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30}; //green
const uint64_t xmark[8] = {0x82, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x82}; //red
const uint64_t questionmark[8] = {0x00, 0x0c, 0x1e, 0xb2, 0xb2, 0x06, 0x04, 0x00}; //yellow
//const uint64_t checkmark = 0x3060c06030180c06;  //green
//const uint64_t xmark = 0x82c66c38386cc682;      //red
//const uint64_t questionMark = 0x000406b2b21e0c00;    //yellow

void clearMatrix(void) {
    for(int c=0; c < 8; c++){
        matrix.displaybuffer[c] = 0;
    } 
}

void setup() {
    Serial.begin(9600);  
    matrix.begin(0x70);  // pass in the address

    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(9, OUTPUT);

    clearMatrix();
    
    binaryAnd = 0b11111111;
    matrix.writeDisplay();
}

void loop() {

    if(!buttonPressed){
        if(digitalRead(2) == 1){    //red button
            buttonState = 1;
            buttonPressed = true;
            delay(1);
        }
        else if (digitalRead(3) == 1){  //yellow button
            buttonState = 2;
            buttonPressed = true;
            delay(1);
        }
        else if (digitalRead(4) == 1){  //green button
            buttonState = 3;
            buttonPressed = true;
            delay(1);
        }
        else {
            buttonState = 0;
        }

        //if button is pressed, execute this and switch case
        if(buttonPressed){
            
            switch(buttonState){
                case 1: //red button

                    for(int i=0; i < 8; i++){
                        matrix.displaybuffer[i] = xmark[i];   //red portion
                        //binaryAnd = binaryAnd << 8;
                    }

                    break;
                    
                case 2: //yellow button
                    
                    for(int i=0; i < 8; i++){ 
                        matrix.displaybuffer[i] = questionmark[i];   //red portion
                        matrix.displaybuffer[i] |= questionmark[i] << 8; //green portion
                        //binaryAnd = binaryAnd << 8;
                    }
                    
                    break;

                case 3: //green button
                    
                    for(int i=0; i < 8; i++){ 
                        matrix.displaybuffer[i] = checkmark[i] << 8; //green portion
                        //binaryAnd = binaryAnd << 8;
                    }

                    break;

                default: 
                break;
            }

            matrix.writeDisplay();
            binaryAnd = 0b11111111;
            counter++;
        }
    }

    if (buttonPressed){
        if (digitalRead(2) == 0 && digitalRead(3) == 0 && digitalRead(4) == 0){
            buttonPressed = false;
            delay(1);
        }
    }

}


