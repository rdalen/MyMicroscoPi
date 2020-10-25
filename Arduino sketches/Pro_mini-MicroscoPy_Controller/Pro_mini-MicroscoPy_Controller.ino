/* This code sends data via UART from one Arduino board (controller) to another (MainBoard) to control the stepper motors and the LED illumination
 * Arduino sends the data only if there is a change in the value of the joysticks or the LED potentiometer 
 * Therefore, there is no continuous data communication between the mainboard and the controller
 * Board: Arduino Pro mini 
 */

#include <Wire.h> // needed for the I2C communication of the OLED, already installed in Arduino IDE
#include <Adafruit_GFX.h> // needed for the OLED // Copyright (c) 2012 Adafruit Industries.  All rights reserved.
#include <Adafruit_SSD1306.h> // needed for the OLED // Copyright (c) 2012 Adafruit Industries.  All rights reserved.

// Arduino pins for the joysticks
#define joystickX A1
#define joystickY A0
#define joystickZ A2
#define joystickC A3
#define joystickR A7
#define joystickT A6
#define BUTTON1 2 //Button Joystick U1
#define BUTTON2 3 //Button Joystick U2 
#define BUTTON3 4 //Button Joystick U3 
#define RE_DT 8  // Rotary encoder signal DT (output A)
#define RE_CLK 9  // Rotary encoder signal CLK (output B)
#define RE_BUTTON 7 // Rotary encoder button | active LOW
#define BUTTON4 RE_BUTTON // ... also known as BUTTON4
#define RE_MAX 40 // Count value of one rotation of the   Rotary encoder

// potentiometer for the LED intensity
//#define potLED 8

// change these values to set the direction of the movement with respect to the joystick
// the direction can also be changed by simply rotating the motor 180-deg 

#define directionX -1
#define directionY 1
#define directionZ 1
#define directionC 1
#define directionR 1
#define directionT 1

// the joystick has a variable speed control at 3 predefined speeds
// change these values to change the speed of the motor

#define fast 500
#define medium 50
#define slow 10
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define TUNE_X 900
#define TUNE_Y 900
#define TUNE_C 900
#define TUNE_Z 900
#define TUNE_R 900
#define TUNE_T 900
#define TUNE_L 1023
#define LONGPRESSTIME 2000

int readX;
int readY;
int readC;
int readZ;
int readR;
int readT;
int readL;

bool button1Active = false;
long button1Timer;
bool longPress1Active = false;
bool button2Active = false;
long button2Timer;
bool longPress2Active = false;
bool button3Active = false;
long button3Timer;
bool longPress3Active = false;
bool button4Active = false;
long button4Timer;
bool longPress4Active = false;

int readXlast = 0;
int readYlast = 0;
int readClast = 0;
int readZlast = 0;
int readRlast = 0;
int readTlast = 0;
int readLlast = 0;
bool homingLast = 0;
int RE_counter = 0; // Rotary encoder counter
int RE_state; // Rotary encoder counter state
int RE_lastState; // Rotary encoder counter last state

String stepper;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize the display
  Serial.begin(57600); //start the serial communication, Serial: UART
//  Serial.println("starting up MicroscoPy Controller"); 
//  analogReference(EXTERNAL); // use AREF for reference voltage connected to +5V Power
  
  pinMode(joystickX, INPUT); // X stepper
  pinMode(joystickY, INPUT); // Y stepper
  pinMode(joystickZ, INPUT); // Z stepper
  pinMode(joystickC, INPUT); // Focus stepper
  pinMode(joystickR, INPUT); // Rotatie stepper
  pinMode(joystickT, INPUT); // Tilt stepper
  pinMode(BUTTON1, INPUT_PULLUP); //Joystick X/Y button | active LOW
  pinMode(BUTTON2, INPUT_PULLUP); //Joystick Z/C button | active LOW
  pinMode(BUTTON3, INPUT_PULLUP); //Joystick R/T button | active LOW 
  pinMode(BUTTON4, INPUT_PULLUP);  //Rotary encoder button | active LOW
  pinMode (RE_DT,INPUT_PULLUP); // Rotary encoder DT signal
  pinMode (RE_CLK,INPUT_PULLUP); // Rotary encoder CLK signal
//  pinMode(potLED, INPUT);

// show a start-up text on the OLED display
  display.clearDisplay();
  display.setRotation(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.println("Starting");
  display.display();

  delay(2000); //delay for the start-up message

// set the LED illumination to the Rotary encoder value at the start-up

//  readLlast = map((analogRead(potLED)), 0, 1023, 0, 20); // map to 20 steps (5% steps) 
  readLlast = map(read_RE(), 0, RE_MAX, 0, 20) ; // map to 20 steps (5% steps)
  Serial.print(readL); Serial.print("L"); Serial.print(","); // send the data to the MainBoard to update the LED intensity
  
// show the LED intensity on the OLED display

  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(2);
//  display.print("LED:"); display.print(100 - (readLlast * 5)); display.print("%"); // PWM of the LED driver used in the prototype works in the opposite direction
  display.print("LED: "); display.print(readLlast * 5); display.print("%");
  display.display();

   // Reads the initial state of the outputA
//   RE_lastState = digitalRead(RE_CLK);
}

void loop() {

  readX = map((analogRead(joystickX)), 0, TUNE_X, -3, 3); // map the measured value to 3 positive and 3 negative speed values
//  readX=0; // disabled
//  readX = analogRead(joystickX); // map the measured value to 3 positive and 3 negative speed values
//  Serial.println(readX);
  if ((readX != readXlast) ) { //check if it has changed
    if (readX == -3) {
      Serial.print(fast * -1 * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }
    if (readX == -2)  {
      Serial.print(medium * -1 * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }
    if (readX == -1)  {
      Serial.print(slow * -1 * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }
    if (readX == 0) {
      Serial.print(0); Serial.print("O"); Serial.print(","); //stop the stepper motor by sending "0O,"
      readXlast = readX;
    }
    if (readX == 1)  {
      Serial.print(slow * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }

    if (readX == 2)  {
      Serial.print(medium * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }

    if (readX == 3)  {
      Serial.print(fast * directionX); Serial.print("X"); Serial.print(",");
      readXlast = readX;
    }
  }

// REPEAT THE SAME FOR ALL OTHER JOYSTICK POTENTIOMETERS 

  readY = map((analogRead(joystickY)), 0, TUNE_Y, -3, 3);
//  readY=0; // disabled
  if (readY != readYlast) {
    if (readY == -3)  {
      Serial.print(fast * -1 * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }
    if (readY == -2)  {
      Serial.print(medium * -1 * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }
    if (readY == -1)  {
      Serial.print(slow * -1 * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }
    if (readY == 0) {
      Serial.print(0); Serial.print("O"); Serial.print(",");
      readYlast = readY;
    }
    if (readY == 1)  {
      Serial.print(slow * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }

    if (readY == 2)  {
      Serial.print(medium * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }

    if (readY == 3)  {
      Serial.print(fast * directionY); Serial.print("Y"); Serial.print(",");
      readYlast = readY;
    }
  }

  readC = map((analogRead(joystickC)), 0, TUNE_C, -3, 3);
//  readC=0; // disabled
  if (readC != readClast) {
    if (readC == -3)  {
      Serial.print(fast * -1 * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }
    if (readC == -2)  {
      Serial.print(medium * -1 * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }
    if (readC == -1) {
      Serial.print(slow * -1 * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }
    if (readC == 0)  {
      Serial.print(0); Serial.print("O"); Serial.print(",");
      readClast = readC;
    }
    if (readC == 1)  {
      Serial.print(slow * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }

    if (readC == 2)  {
      Serial.print(medium * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }

    if (readC == 3) {
      Serial.print(fast * directionC); Serial.print("C"); Serial.print(",");
      readClast = readC;
    }
  }

  readZ = map((analogRead(joystickZ)), 0, TUNE_Z, -3, 3);
//  readZ=0; // disabled
  if (readZ != readZlast) {
    if (readZ == -3)  {
      Serial.print(fast * -1 * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }
    if (readZ == -2)  {
      Serial.print(medium * -1 * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }
    if (readZ == -1)  {
      Serial.print(slow * -1 * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }
    if (readZ == 0) {
      Serial.print(0); Serial.print("O"); Serial.print(",");
      readZlast = readZ;
    }
    if (readZ == 1) {
      Serial.print(slow * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }

    if (readZ == 2)  {
      Serial.print(medium * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }

    if (readZ == 3)  {
      Serial.print(fast * directionZ); Serial.print("Z"); Serial.print(",");
      readZlast = readZ;
    }
  }

  readR = map((analogRead(joystickR)), 0, TUNE_R, -3, 3); 
//  readR=0; // disabled
  if (readR != readRlast)  {
    if (readR == -3) {
      Serial.print(fast * -1 * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }
    if (readR == -2) {
      Serial.print(medium * -1 * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }
    if (readR == -1)  {
      Serial.print(slow * -1 * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }
    if (readR == 0) {
      Serial.print(0); Serial.print("O"); Serial.print(",");
      readRlast = readR;
    }
    if (readR == 1)  {
      Serial.print(slow * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }

    if (readR == 2)  {
      Serial.print(medium * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }

    if (readR == 3) {
      Serial.print(fast * directionR); Serial.print("R"); Serial.print(",");
      readRlast = readR;
    }
  }

  readT = map((analogRead(joystickT)), 0, TUNE_T, -3, 3);
//  readT=0; // disabled
  if (readT != readTlast)  {
    if (readT == -3) {
      Serial.print(fast * -1 * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }
    if (readT == -2) {
      Serial.print(medium * -1 * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }
    if (readT == -1) {
      Serial.print(slow * -1 * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }
    if (readT == 0)  {
      Serial.print(0); Serial.print("O"); Serial.print(",");
      readTlast = readT;
    }
    if (readT == 1)  {
      Serial.print(slow * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }

    if (readT == 2)  {
      Serial.print(medium * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }

    if (readT == 3)  {
      Serial.print(fast * directionT); Serial.print("T"); Serial.print(",");
      readTlast = readT;
    }
  }

// LED INTENSITY


  readL = map(read_RE(), 0, RE_MAX, 0, 20) ; // map Rotary Encoder value to 20 steps (5% steps)
//  readL=0; // disabled
  if (readL != readLlast) {
    Serial.print(readL); Serial.print("L"); Serial.print(",");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(2);
//    display.print("LED:"); display.print(100 - (readL * 5)); display.print("%");
    display.print("LED: "); display.print(readL * 5); display.print("%");
    display.display();
    readLlast = readL;
  }

// Buttons
  if (digitalRead(BUTTON1) == LOW) {  // Button1 pressed
    if (button1Active == false) {
      button1Active = true;
      button1Timer = millis();
    }
    if ((millis() - button1Timer > LONGPRESSTIME) && (longPress1Active == false)) {
      longPress1Active = true;
//      Serial.println("Button1 LongPressed"); 
      Serial.print(0); Serial.print("D"); Serial.print(",");
    }
  } 
  else {                            // Button1 released
    if (button1Active == true) {
      if (longPress1Active == true) {
        longPress1Active = false;
      } else {
//        Serial.println("Button1 ShortPressed"); 
        Serial.print(0); Serial.print("d"); Serial.print(",");
      }
      button1Active = false;
    }
  }
  if (digitalRead(BUTTON2) == LOW) {  // Button2 pressed
    if (button2Active == false) {
      button2Active = true;
      button2Timer = millis();
    }
    if ((millis() - button2Timer > LONGPRESSTIME) && (longPress2Active == false)) {
      longPress2Active = true;
//      Serial.println("Button2 LongPressed"); 
      Serial.print(0); Serial.print("E"); Serial.print(",");
    }
  } 
  else {                            // Button2 released
    if (button2Active == true) {
      if (longPress2Active == true) {
        longPress2Active = false;
      } else {
//        Serial.println("Button2 ShortPressed"); 
        Serial.print(0); Serial.print("e"); Serial.print(",");
      }
      button2Active = false;
    }
  }
  if (digitalRead(BUTTON3) == LOW) {  // Button3 pressed
    if (button3Active == false) {
      button3Active = true;
      button3Timer = millis();
    }
    if ((millis() - button3Timer > LONGPRESSTIME) && (longPress3Active == false)) {
      longPress3Active = true;
//      Serial.println("Button3 LongPressed"); 
      Serial.print(0); Serial.print("F"); Serial.print(",");
    }
  } 
  else {                            // Button3 released
    if (button3Active == true) {
      if (longPress3Active == true) {
        longPress3Active = false;
      } else {
//        Serial.println("Button3 ShortPressed"); 
        Serial.print(0); Serial.print("f"); Serial.print(",");
      }
      button3Active = false;
    }
  }
  if (digitalRead(BUTTON4) == LOW) {  // Button4 pressed
    if (button4Active == false) {
      button4Active = true;
      button4Timer = millis();
    }
    if ((millis() - button4Timer > LONGPRESSTIME) && (longPress4Active == false)) {
      longPress4Active = true;
//      Serial.println("Button4 LongPressed"); 
      Serial.print(0); Serial.print("G"); Serial.print(",");
    }
  } 
  else {                            // Button4 released
    if (button4Active == true) {
      if (longPress4Active == true) {
        longPress4Active = false;
      } else {
//        Serial.println("Button4 ShortPressed"); 
        Serial.print(0); Serial.print("g"); Serial.print(",");
      }
      button4Active = false;
    }
  }
}

//Read Rotary encoder
 int read_RE() { 
   RE_state = digitalRead(RE_DT); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (RE_state != RE_lastState){     
     // If the outputB state is equal to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(RE_CLK) == RE_state) { 
       RE_counter ++;
       if (RE_counter > RE_MAX) RE_counter=RE_MAX;
     } else {
       RE_counter --;
       if (RE_counter < 0) RE_counter=0;       
     }
//     Serial.print("Position Rotary Encoder: ");
//     Serial.println(RE_counter);
   }
   RE_lastState = RE_state; // Updates the previous state of the outputA with the current state
   return(RE_counter);
 }

