// Adafruit_DotStarMatrix example for single DotStar LED matrix.
// Scrolls 'Howdy' across the matrix.

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define DATAPIN  4
#define CLOCKPIN 5

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
  8, 8, DATAPIN, CLOCKPIN,
  DS_MATRIX_TOP     + DS_MATRIX_RIGHT +
  DS_MATRIX_COLUMNS + DS_MATRIX_ZIGZAG,
  DOTSTAR_BGR);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  matrix.fillScreen(0);
}

int x    = matrix.width();
int pass = 0;
char inByte = 0; 
int c = 0;

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
  
  if (Serial.available()>0){
    inByte = Serial.read();
    if (inByte=='u' || inByte=='U') {
      matrix.fillScreen(0);
      upArrow();}
    if (inByte=='d' || inByte=='D') {
      matrix.fillScreen(0);
      downArrow();}
    if (inByte=='l' || inByte=='L') {
      matrix.fillScreen(0);
      leftArrow();}
    if (inByte=='r' || inByte=='R') {
      matrix.fillScreen(0);
      rightArrow();}
    if (inByte=='c' || inByte=='C') {
      matrix.fillScreen(0);}
    if (inByte=='0') {
      c=0;}
    if (inByte=='1') {
      c=1;}
    if (inByte=='2') {
      c=2;}
  }

  matrix.show();
  delay(1000);
}
