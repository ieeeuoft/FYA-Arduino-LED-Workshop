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
int currentCode[4];

const uint64_t checkmark = 0x3060c06030180c06;  //green
const uint64_t xmark = 0x4163361c1c366341;      //red

void clearMatrix(void) {
    for(int c=0; c < 8; c++){
        matrix.displaybuffer[c] = 0;
    } 
}

void debugCodeSerial(void) {
    for(int i=0; i < 4; i++){
        Serial.print(currentCode[i]);
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
    matrix.writeDisplay();
    for(int i=0; i < 4; i++){
        currentCode[i] = 0;
        Serial.print(currentCode[i]);
    }
    
    digitalWrite(9, LOW);
}

void loop() {

    if (buttonPressed){
        if (digitalRead(2) == 0 && digitalRead(3) == 0 && digitalRead(4) == 0){
            buttonPressed = false;
            delay(1);
        }
    }

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
            currentCode[counter] = buttonState;     //change currentCode
            counter++;
            digitalWrite(9, LOW);
        
            switch(buttonState){
                case 1: //red button
                    clearMatrix();
                    for(int i=0; i < 8; i++){
                        matrix.displaybuffer[i] = 0b11111111;
                    }
                    break;
                    
                case 2: //yellow button
                    clearMatrix();
                    for(int i=0; i < 8; i++){
                        matrix.displaybuffer[i] = 0b1111111111111111;
                    }
                    break;
                    
                case 3: //green button
                    clearMatrix();
                    for(int i=0; i < 8; i++){
                        matrix.displaybuffer[i] = 0b1111111100000000;
                    }
                    break;

                default: 
                break;
            }

            matrix.writeDisplay();
        }
    }


    if (currentCode[0] == 1 && currentCode[1] == 2 && currentCode[2] == 3 && currentCode[3] == 1){
        digitalWrite(9, HIGH);
        counter = 0;
        for(int i=0; i < 4; i++){
            currentCode[i] = 0;
        }

        clearMatrix();
        for(int i=0; i < 8; i++){
            matrix.displaybuffer[i] = ((checkmark & binaryAnd) >> (i*8)) << 8;
            binaryAnd = binaryAnd << 8;
        }

        binaryAnd = 0b11111111;
        matrix.writeDisplay();
    }
    else if (counter == 4){
        counter = 0;
        for(int i=0; i < 4; i++){
            currentCode[i] = 0;
        }

        clearMatrix();
        for(int i=0; i < 8; i++){
            matrix.displaybuffer[i] = (xmark & binaryAnd) >> (i*8);
            binaryAnd = binaryAnd << 8;
        }

        binaryAnd = 0b11111111;
        matrix.writeDisplay();
    }
}


