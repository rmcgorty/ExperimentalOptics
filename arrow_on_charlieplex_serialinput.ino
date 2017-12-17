#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

/************************************************************************
 * This works with the CharliePlex LED matrix from Adafruit. 
 * 
 * This program will display an arrow of a given orientation depending
 * on input from the user. For this to work, the Arduino must be plugged
 * into a computer. The Arduino program must be running along with the 
 * Serial Monitor (found under Tools). In the input textbox at the top 
 * of the Serial Monitor, enter a character and hit enter (or press the 
 * Send button). You may enter 'u', 'd', 'l', 'r' to display an arrow
 * that points up, down, left or right. You may enter 'c' to clear the 
 * screen.
 * 
 * RJM 12/17/2017
 ***********************************************************************/

// If you're using the full breakout...
Adafruit_IS31FL3731 matrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();

#define I2C_ADDR 0x74       // I2C address of Charlieplex matrix

uint8_t        brightness = 128; //Brightness can be from 0 to 255
char incomingByte = 0;           //This will be for user input

//Defined below are the patterns to display on the matrix
//They are either an arrow pointing up, down, left or right
static const uint8_t PROGMEM
  left_bmp[] =
  { B00011000,
    B00111100,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000 },
  right_bmp[] =
  { B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110,
    B00111100,
    B00011000 },
  down_bmp[] =
  { B00000000,
    B00100000,
    B01100000,
    B11111111,
    B11111111,
    B01100000,
    B00100000,
    B00000000 },
  up_bmp[] =
  { B00000000,
    B00000100,
    B00000110,
    B11111111,
    B11111111,
    B00000110,
    B00000100,
    B00000000 };



void setup() {
  /*
   * Setup function is needed to initialize Arduino board.
   * It establishes connection with the computer.
   */
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
  matrix.setRotation(0);
}

void loop() {
  /*
   * Loop function is iterated when Arduino board is plugged in.
   * Here, we check for user input and then, depending on what 
   * character is entered by the user, display either the up, down,
   * left or right arrow. Or, if the user enters 'c' or 'C', the 
   * LED matrix is cleared. 
   */

  //Check if any input from the user has been entered
  if (Serial.available()>0) {
    incomingByte = Serial.read(); //read the user input and store in variable 'incomingByte'

    if ((incomingByte=='u') || (incomingByte=='U')) {
      //clear the matrix and display up arrow if user entered 'u' or 'U'
      matrix.clear();
      matrix.drawBitmap(3,0,up_bmp,8,8,brightness);
      delay(1500); //pauses for 1.5 seconds
      }
    if ((incomingByte=='d') || (incomingByte=='D')) {
      //clear the matrix and display down arrow if user entered 'd' or 'D'
      matrix.clear(); 
      matrix.drawBitmap(3,0,down_bmp,8,8,brightness);
      delay(1500); }
    if ((incomingByte=='l') || (incomingByte=='L')) {
      matrix.clear();
      matrix.drawBitmap(3,0,left_bmp,8,8,brightness);
      delay(1500); }
    if ((incomingByte=='r') || (incomingByte=='R')) {
      matrix.clear();
      matrix.drawBitmap(3,0,right_bmp,8,8,brightness);
      delay(1500); }
    if ((incomingByte=='c') || (incomingByte=='C')) {
      //clears the matrix if user entered 'c' or 'C'
      matrix.clear();
      delay(1500); }
  }

}
