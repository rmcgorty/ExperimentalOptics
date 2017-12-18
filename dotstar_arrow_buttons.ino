// Adafruit_DotStarMatrix 

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define DATAPIN  4
#define CLOCKPIN 5

#define BUTTON1 7
#define BUTTON2 2

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
  8, 8, DATAPIN, CLOCKPIN,
  DS_MATRIX_TOP     + DS_MATRIX_RIGHT +
  DS_MATRIX_COLUMNS + DS_MATRIX_ZIGZAG,
  DOTSTAR_BGR);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };


int x    = matrix.width();
int pass = 0;
char inByte = 0; 
int c = 0;
int lastButtonState1 = LOW;
int buttonState1;
int lastButtonState2 = LOW;
int buttonState2;
int pattern = -1;

//For debouncing buttons
unsigned long lastDebounceTime1=0;
unsigned long lastDebounceTime2=0;
unsigned long debounceDelay = 100;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  matrix.fillScreen(0);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}



void upArrow() {
  for (int i=0; i<8; i++){
    matrix.drawPixel(3,i,colors[c]);
    matrix.drawPixel(4,i,colors[c]);}
  matrix.drawPixel(2,6,colors[c]);
  matrix.drawPixel(2,5,colors[c]);
  matrix.drawPixel(1,5,colors[c]);
  matrix.drawPixel(5,6,colors[c]);
  matrix.drawPixel(5,5,colors[c]);
  matrix.drawPixel(6,5,colors[c]);
}

void downArrow() {
  for (int i=0; i<8; i++){
    matrix.drawPixel(3,i,colors[c]);
    matrix.drawPixel(4,i,colors[c]);}
  matrix.drawPixel(2,1,colors[c]);
  matrix.drawPixel(2,2,colors[c]);
  matrix.drawPixel(1,2,colors[c]);
  matrix.drawPixel(5,1,colors[c]);
  matrix.drawPixel(5,2,colors[c]);
  matrix.drawPixel(6,2,colors[c]);
}

void rightArrow() {
  for (int i=0; i<8; i++){
    matrix.drawPixel(i,3,colors[c]);
    matrix.drawPixel(i,4,colors[c]);}
  matrix.drawPixel(2,1,colors[c]);
  matrix.drawPixel(2,2,colors[c]);
  matrix.drawPixel(1,2,colors[c]);
  matrix.drawPixel(1,5,colors[c]);
  matrix.drawPixel(2,5,colors[c]);
  matrix.drawPixel(2,6,colors[c]);
}

void leftArrow() {
  for (int i=0; i<8; i++){
    matrix.drawPixel(i,3,colors[c]);
    matrix.drawPixel(i,4,colors[c]);}
  matrix.drawPixel(5,1,colors[c]);
  matrix.drawPixel(5,2,colors[c]);
  matrix.drawPixel(6,2,colors[c]);
  matrix.drawPixel(6,5,colors[c]);
  matrix.drawPixel(5,5,colors[c]);
  matrix.drawPixel(5,6,colors[c]);
}

void loop() {
  //read state of the button pin
  int reading1 = digitalRead(BUTTON1);
  int reading2 = digitalRead(BUTTON2);

  //Serial.print(reading1);

  //check to see if change in button is real (or noise)
  if (reading1 != lastButtonState1){
    lastDebounceTime1 = millis();
  }
  if ((millis()-lastDebounceTime1)>debounceDelay){
    if (reading1!=buttonState1){
      buttonState1=reading1;
      if (buttonState1==HIGH) {
        pattern = pattern+1;
        if (pattern>3){
          pattern=0;
        }
      }
    }
  }

  if (reading2 != lastButtonState2){
    lastDebounceTime2 = millis();
  }
  if ((millis()-lastDebounceTime2)>debounceDelay){
    if (reading2!=buttonState2){
      buttonState2=reading2;
      if (buttonState2==HIGH) {
        c = c+1;
        if (c>2){
          c=0;
        }
      }
    }
  }
  
  lastButtonState1=reading1;
  lastButtonState2=reading2;
  
  if (pattern==0) {
    matrix.fillScreen(0);
    upArrow();
  }
  if (pattern==1) {
    matrix.fillScreen(0);
    rightArrow();
  }
  if (pattern==2) {
    matrix.fillScreen(0);
    downArrow();
  }
  if (pattern==3) {
    matrix.fillScreen(0);
    leftArrow();
  }

  matrix.show();
  
}
