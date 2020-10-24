/* This code controls the stepper motors and the LED intensity
   according to the data received from the UART (RX, TX) (Controller) or the USB (e.g. Raspberry Pi)
   All 6 motors share the same stepper motor pins, but only one
   is activated depending on the status of the Enable pin of the driver
   Data format: "50X," where 50 is the speed and X is the axis
   X: X axis, Y: Y axis, Z: Z axis (magnification), C: camera stage (Focus), R: rotation, T: tilt
   d: Button1 ShortPressed, D Button1 LongPressed,
   e: Button2 ShortPressed, E Button2 LongPressed,
   f: Button3 ShortPressed, F Button3 LongPressed,
   g: Button4 ShortPressed, G Button4 LongPressed,
   The data is executed after a "," (comma) is received
   Hence; disconnect the TxD RxD pins (jumpers on PCB) when uploading a new sketch
*/

// board: Arduino Pro mini
// Stepper driver; Adafruit Breakoutboard DRV8825 from Aliexpress

#include <AccelStepper.h> // Library to control stepper motors // Copyright (C) 2010-2018 Mike McCauley
#include <Adafruit_NeoPixel.h> // Library to control the optional status LED
#include <EEPROM.h>

////////////////// Arduino pins connected to the EN of each stepper motor driver

#define TESTMODE false // In Testmode the endstops are disabled

// stepper motor pins
#define IN1 8  //B1 - pin3 stepper driver Breakoutboard
#define IN2 9  //B2 - pin4 stepper driver Breakoutboard
#define IN3 10 //A2 - pin5 stepper driver Breakoutboard
#define IN4 11 //A1 - pin6 stepper driver Breakoutboard
#define ENDSTOP 2 //Pin connected to Endstop switch boards

#define NEO_COUNT 1
#define NEOBLUE 50
#define NEOGREEN 50
#define NEORED 50

// motor enable pins
#define EnableX A1
#define EnableY A2
#define EnableR A3
#define EnableC 3
#define EnableZ 4
#define EnableT 5

// value 0 means no endstop
#if TESTMODE
#define homeDirX 0  // disable endstops
#define homeDirY 0
#define homeDirC 0
#define homeDirZ 0
#define homeDirR 0
#define homeDirT 0
#else
#define homeDirX 1 // Homing direction of X
#define homeDirY -1  // Homing direction of Y
#define homeDirC 1  // Homing direction of C
#define homeDirZ 1  // Homing direction of Z
#define homeDirR 0  // R has no endstop
#define homeDirT 1  // T has no endstop
#endif

#define CHECK 1
#define NO_CHECK 0

#define MAX_X 4500  // max X steps
#define MAX_Y 4000  // max Y steps
#define MAX_C 5500  // max C steps
#define MAX_Z 5050  // max Z steps
#define MAX_R 0  // max R steps
#define MAX_T 3400  // max T steps

#define LEDPWM 6 // High-power illumination LED PWM control pin
#define NEO_PIN 7 // GPIO-nr NeoPixel status LED | PWM output


#define PRESET1_Y 2110
#define PRESET1_X 2290
#define PRESET1_C 3820
#define PRESET1_Z 1200
#define PRESET1_R -1
#define PRESET1_T 3400
#define PRESET1_L 191


const int stepsPerRevolution = 2048; //set according to the specs of the stepper motor
String receivedString; //incoming data from the serial ports (USB or UART)
int stepperSpeed;
//position variables
long stepX = 0;
long stepY = 0;
long stepC = 0;
long stepZ = 0;
long stepR = 0;
long stepT = 0;
int laststepperMotor = "";
int lastspeedStepper = 0;
int stepDir;
int checkEndstops;
char stepperState; //variable to define the active stepper motor, X, Y, Z, C, R, T
int LEDintensity;

// instantiate steppers
// AccelStepper myStepper(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperX(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperY(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperC(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperZ(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperR(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins
AccelStepper StepperT(AccelStepper::FULL4WIRE, IN1, IN3, IN2, IN4); // stepper motor pins

Adafruit_NeoPixel pixel(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

// set NeoPixel colors
uint32_t blue = pixel.Color(0, 0, 50); // Status: Homing
uint32_t green = pixel.Color(0, 50, 0); // Status: OK
uint32_t red = pixel.Color(50, 0, 0); // Status: Endstop
uint32_t yellow = pixel.Color(50, 50, 0);
uint32_t dark = pixel.Color(0, 0, 0);

void setup() {

  Serial.begin(57600); // UART with the jostick controller
  Serial.println("starting up MicroscoPy Mainboard");
  pinMode(EnableX, OUTPUT);
  pinMode(EnableY, OUTPUT);
  pinMode(EnableC, OUTPUT);
  pinMode(EnableZ, OUTPUT);
  pinMode(EnableR, OUTPUT);
  pinMode(EnableT, OUTPUT);
  pinMode(LEDPWM, OUTPUT);
  pinMode(ENDSTOP, INPUT); //endstop switch | active HIGH | Hence; endstop board has been modified!!


  analogWrite(LEDPWM, 0); // initialize the LED intensity to 0%
  /* PWM of the LED driver (RCD-24-0.70/PL/B, Recom) used in this project
    works in the opposite direction, i.e. 255 is for 0% and 0 for 100% intensity
  */
  pixel.begin();
  pixel.setPixelColor(0, dark);
  pixel.show();
  delay(2000);

  //  myStepper.setMaxSpeed(1000);
  StepperX.setMaxSpeed(1000);
  StepperY.setMaxSpeed(1000);
  StepperC.setMaxSpeed(1000);
  StepperZ.setMaxSpeed(1000);
  StepperR.setMaxSpeed(1000);
  StepperT.setMaxSpeed(1000);


  // Start Homing procedure of Stepper Motors at startup
  pixel.setPixelColor(0, blue);  //Status; Homing
  pixel.show();
  HomeSteppers();
  pixel.setPixelColor(0, green);  //Status; OK
  pixel.show();

}

void loop() {


  ////// data from UART: joystick controller

  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == ',') {
      if (receivedString.length() > 1) {
        stepperSpeed = receivedString.toInt();

        if (receivedString.indexOf('X') > 0) {
          stepperState = 'X';
          checkEndstops = abs(homeDirX);
        }

        if (receivedString.indexOf('Y') > 0) {
          stepperState = 'Y';
          checkEndstops = abs(homeDirY);
        }

        if (receivedString.indexOf('C') > 0) {
          stepperState = 'C';
          checkEndstops = abs(homeDirC);
        }

        if (receivedString.indexOf('Z') > 0) {
          stepperState = 'Z';
          checkEndstops = abs(homeDirZ);
        }

        if (receivedString.indexOf('R') > 0) {
          stepperState = 'R';
          checkEndstops = abs(homeDirR);
        }

        if (receivedString.indexOf('T') > 0) {
          stepperState = 'T';
          checkEndstops = abs(homeDirT);
        }

        if (receivedString.indexOf('L') > 0) {
          stepperState = '@';
          //          Serial.print("stepperspeed for L: ");
          //          Serial.println(stepperSpeed);
          LEDintensity = map(stepperSpeed, 0, 20, 0, 255);
          analogWrite(LEDPWM, LEDintensity);
          Serial.print("LED intensity: ");
          Serial.println(LEDintensity);
        }

        if (receivedString.indexOf('O') > 0) {
          stepperState = 'O';
          stepperSpeed = 0;
        }
        //Buttons
        if (receivedString.indexOf('d') > 0) {
          Serial.println("Button1 ShortPressed");
          stepperState = '@';
          ReadPreset(1); // Read & Set Preset1
        }
        if (receivedString.indexOf('e') > 0) {
          Serial.println("Button2 ShortPressed");
          ReadPreset(2); // Read & Set Preset2
          stepperState = '@';
        }
        if (receivedString.indexOf('f') > 0) {
          Serial.println("Button3 ShortPressed");
          ReadPreset(3); // Read & Set Preset3
          stepperState = '@';
        }
        if (receivedString.indexOf('g') > 0) {
          Serial.println("Button4 ShortPressed");
          stepperState = '@';
        }
        if (receivedString.indexOf('D') > 0) {
          Serial.println("Button1 LongPressed");
          stepperState = '@';
          WritePreset(1); // Write Preset1
        }
        if (receivedString.indexOf('E') > 0) {
          Serial.println("Button2 LongPressed");
          WritePreset(2); // Write Preset2
          stepperState = '@';
        }
        if (receivedString.indexOf('F') > 0) {
          Serial.println("Button3 LongPressed");
          WritePreset(3); // Write Preset3
          stepperState = '@';
        }
        if (receivedString.indexOf('G') > 0) {
          Serial.println("Button4 LongPressed");
          stepperState = '@';
        }
        receivedString = "";
      }

    }
    else {
      receivedString += data;
    }

  }
  if (stepperState != '@') {
    MoveStepper(stepperState, stepperSpeed, checkEndstops);
  }
}
// Move stepper one step
void MoveStepper(char stepperMotor, int speedStepper, bool checksteps)
///// RUN STEPPER MOTORS, only one runs at a given time
{
  //  myStepper.setSpeed(speedStepper);
  if (stepperMotor == 'X') {
    StepperX.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepX && stepX <= MAX_X) || (stepX < 0 && stepDir == -homeDirX) || (stepX > MAX_X && stepDir == homeDirX) || !checksteps )  {
      digitalWrite(EnableX, HIGH);
      digitalWrite(EnableY, LOW);
      digitalWrite(EnableZ, LOW);
      digitalWrite(EnableC, LOW);
      digitalWrite(EnableR, LOW);
      digitalWrite(EnableT, LOW);
      StepperX.runSpeed();
      stepX = StepperX.currentPosition() * (-homeDirX);
      Serial.print("StepX; ");
      Serial.println(stepX);
    }
    else {
      stepperMotor = 'O';
      Serial.println("EndstepX reached");
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
    }
  }

  if (stepperMotor == 'Y') {
    StepperY.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepY && stepY <= MAX_Y) || (stepY < 0 && stepDir == -homeDirY) || (stepY > MAX_Y && stepDir == homeDirY) || !checksteps )  {
      digitalWrite(EnableY, HIGH);
      digitalWrite(EnableX, LOW);
      digitalWrite(EnableZ, LOW);
      digitalWrite(EnableC, LOW);
      digitalWrite(EnableR, LOW);
      digitalWrite(EnableT, LOW);
      StepperY.runSpeed();
      stepY = StepperY.currentPosition() * (-homeDirY);
      Serial.print("StepY; ");
      Serial.println(stepY);
    }
    else {
      stepperMotor = 'O';
      Serial.println("EndstepY reached");
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
    }
  }

  if (stepperMotor == 'C') {
    StepperC.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepC && stepC <= MAX_C) || (stepC < 0 && stepDir == -homeDirC) || (stepC > MAX_C && stepDir == homeDirC) || !checksteps )  {
      digitalWrite(EnableC, HIGH);
      digitalWrite(EnableX, LOW);
      digitalWrite(EnableY, LOW);
      digitalWrite(EnableZ, LOW);
      digitalWrite(EnableR, LOW);
      digitalWrite(EnableT, LOW);
      StepperC.runSpeed();
      stepC = StepperC.currentPosition() * (-homeDirC);
      Serial.print("StepC; ");
      Serial.println(stepC);
    }
    else {
      stepperMotor = 'O';
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
      Serial.println("EndstepC reached");
    }
  }

  if (stepperMotor == 'Z') {
    StepperZ.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepZ && stepZ <= MAX_Z) || (stepZ < 0 && stepDir == -homeDirZ) || (stepZ > MAX_Z && stepDir == homeDirZ) || !checksteps )  {
      digitalWrite(EnableZ, HIGH);
      digitalWrite(EnableX, LOW);
      digitalWrite(EnableY, LOW);
      digitalWrite(EnableC, LOW);
      digitalWrite(EnableR, LOW);
      digitalWrite(EnableT, LOW);
      StepperZ.runSpeed();
      stepZ = StepperZ.currentPosition() * (-homeDirZ);
      Serial.print("StepZ; ");
      Serial.println(stepZ);
    }
    else {
      stepperMotor = 'O';
      Serial.println("EndstepZ reached");
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
    }
  }

  if (stepperMotor == 'R') {
    StepperR.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepR && stepR <= MAX_R) || (stepR < 0 && stepDir == -homeDirR) || (stepR > MAX_R && stepDir == homeDirR) || !checksteps )  {
      digitalWrite(EnableR, HIGH);
      digitalWrite(EnableX, LOW);
      digitalWrite(EnableY, LOW);
      digitalWrite(EnableZ, LOW);
      digitalWrite(EnableC, LOW);
      digitalWrite(EnableT, LOW);
      StepperR.runSpeed();
      stepR = StepperR.currentPosition() * (-homeDirR);
      Serial.print("StepR; ");
      Serial.println(stepR);
    }
    else {
      stepperMotor = 'O';
      Serial.println("EndstepR reached");
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
    }
  }

  if (stepperMotor == 'T') {
    StepperT.setSpeed(speedStepper);
    stepDir = sgn(speedStepper);  // get step direction
    if ((0 <= stepT && stepT <= MAX_T) || (stepT < 0 && stepDir == -homeDirT) || (stepT > MAX_T && stepDir == homeDirT) || !checksteps )  {
      digitalWrite(EnableT, HIGH);
      digitalWrite(EnableX, LOW);
      digitalWrite(EnableY, LOW);
      digitalWrite(EnableZ, LOW);
      digitalWrite(EnableC, LOW);
      digitalWrite(EnableR, LOW);
      StepperT.runSpeed();
      stepT = StepperT.currentPosition() * (-homeDirT);
      Serial.print("StepT; ");
      Serial.println(stepT);
    }
    else {
      stepperMotor = 'O';
      pixel.setPixelColor(0, red); //Status; Endstop
      pixel.show();
      Serial.println("EndstepT reached");
    }
  }

  // TURN OFF all stepper motors
  if (stepperMotor == 'O') {
    //  if ((state == 'O') || (speedStepper==0)) {
    digitalWrite(EnableX, LOW);
    digitalWrite(EnableY, LOW);
    digitalWrite(EnableZ, LOW);
    digitalWrite(EnableC, LOW);
    digitalWrite(EnableR, LOW);
    digitalWrite(EnableT, LOW);
  }

  if ((stepperMotor != laststepperMotor) || (speedStepper != lastspeedStepper))  {
    Serial.print("Steppermotor; ");
    Serial.println(stepperMotor);
    Serial.print("Speed; ");
    Serial.println (speedStepper);
    laststepperMotor = stepperMotor;
    lastspeedStepper = speedStepper;
  }

  if (speedStepper == 0 && checksteps) {
    pixel.setPixelColor(0, green); //Status; OK
    pixel.show();
  }

}

void HomeSteppers()
{
  if (homeDirY != 0) {
    Serial.println("NO_CHECK stepperY");
    stepperState = 'Y'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'Y';
      stepperSpeed = 500 * homeDirY; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopY detected");
      stepperState = 'Y';
      stepperSpeed = 50 * -homeDirY; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepY = 0; // Set position variable to zero
    StepperY.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperY");
  }
  else Serial.println("Y has no endstop");

  if (homeDirX != 0) {
    Serial.println("Homing stepperX");
    stepperState = 'X'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'X';
      stepperSpeed = 500 * homeDirX; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopX detected");
      stepperState = 'X';
      stepperSpeed = 50 * -homeDirX; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepX = 0; // Set position variable to zero
    StepperX.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperX");
  }
  else Serial.println("X has no endstop");

  if (homeDirC != 0) {
    Serial.println("Homing stepperC");
    stepperState = 'C'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'C';
      stepperSpeed = 500 * homeDirC; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopC detected");
      stepperState = 'C';
      stepperSpeed = 50 * -homeDirC; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepC = 0; // Set position variable to zero
    StepperC.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperC");
  }
  else Serial.println("C has no endstop");

  if (homeDirZ != 0) {
    Serial.println("Homing stepperZ");
    stepperState = 'Z'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'Z';
      stepperSpeed = 500 * homeDirZ; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopZ detected");
      stepperState = 'Z';
      stepperSpeed = 50 * -homeDirZ; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepZ = 0; // Set position variable to zero
    StepperZ.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperZ");
  }
  else Serial.println("Z has no endstop");

  if (homeDirR != 0) {
    Serial.println("Homing stepperR");
    stepperState = 'R'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'R';
      stepperSpeed = 500 * homeDirR; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopR detected");
      stepperState = 'R';
      stepperSpeed = 50 * -homeDirR; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepR = 0; // Set position variable to zero
    StepperR.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperR");
  }
  else Serial.println("R has no endstop");

  if (homeDirT != 0) {
    Serial.println("Homing stepperT");
    stepperState = 'T'; // activate enable pin
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    while (!digitalRead(ENDSTOP)) {  // Do this until the switch is activated
      stepperState = 'T';
      stepperSpeed = 500 * homeDirT; // move in direction of Endstop
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    while (digitalRead(ENDSTOP)) { // Do this until the switch is not activated
      Serial.println("EndstopT detected");
      stepperState = 'T';
      stepperSpeed = 50 * -homeDirT; // move until endstop released
      MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    stepT = 0; // Set position variable to zero
    StepperT.setCurrentPosition(0);  // Home position
    Serial.println("@Home stepperT");
  }
  else Serial.println("T has no endstop");

}

void Go2Pos(char stepperMotor, long Position)
{
  if ((stepperMotor=='X') && (Position>0)) {
    Serial.println("Go2Pos stepperX");
    if (stepX < Position) {
      while (stepX < Position) {  // Do this until the position is reached
        stepperState = 'X';
        stepperSpeed = 500 * (-homeDirX); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirX));
      }
    }
    if (stepX > Position) {
      while (stepX > Position) {  // Do this until the position is reached
        stepperState = 'X';
        stepperSpeed = 500 * homeDirX; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirX));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepX reached position :");
    Serial.println(stepX);
  }
  if ((stepperMotor=='Y') && (Position>0)) {
    Serial.println("Go2Pos stepperY");
    if (stepY < Position) {
      while (stepY < Position) {  // Do this until the position is reached
        stepperState = 'Y';
        stepperSpeed = 500 * (-homeDirY); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirY));
      }
    }
    if (stepY > Position) {
      while (stepY > Position) {  // Do this until the position is reached
        stepperState = 'Y';
        stepperSpeed = 500 * homeDirY; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirY));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepY reached position :");
    Serial.println(stepY);
  }
  if ((stepperMotor=='C') && (Position>0)) {
    Serial.println("Go2Pos stepperC");
    if (stepC < Position) {
      while (stepC < Position) {  // Do this until the position is reached
        stepperState = 'C';
        stepperSpeed = 500 * (-homeDirC); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirC));
      }
    }
    if (stepC > Position) {
      while (stepC > Position) {  // Do this until the position is reached
        stepperState = 'C';
        stepperSpeed = 500 * homeDirC; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirC));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepC reached position :");
    Serial.println(stepC);
  }

  if ((stepperMotor=='Z') && (Position>0)) {
    Serial.println("Go2Pos stepperZ");
    if (stepZ < Position) {
      while (stepZ < Position) {  // Do this until the position is reached
        stepperState = 'Z';
        stepperSpeed = 500 * (-homeDirZ); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirZ));
      }
    }
    if (stepZ > Position) {
      while (stepZ > Position) {  // Do this until the position is reached
        stepperState = 'Z';
        stepperSpeed = 500 * homeDirZ; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirZ));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepZ reached position :");
    Serial.println(stepZ);
  }

  if ((stepperMotor=='R') && (Position>0)) {
    Serial.println("Go2Pos stepperR");
    if (stepR < Position) {
      while (stepR < Position) {  // Do this until the position is reached
        stepperState = 'R';
        stepperSpeed = 500 * (-homeDirR); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirR));
      }
    }
    if (stepR > Position) {
      while (stepR > Position) {  // Do this until the position is reached
        stepperState = 'R';
        stepperSpeed = 500 * homeDirR; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirR));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepR reached position :");
    Serial.println(stepR);
  }

  if ((stepperMotor=='T') && (Position>0)) {
    Serial.println("Go2Pos stepperT");
    if (stepT < Position) {
      while (stepT < Position) {  // Do this until the position is reached
        stepperState = 'T';
        stepperSpeed = 500 * (-homeDirT); // move in opposite direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirT));
      }
    }
    if (stepT > Position) {
      while (stepT > Position) {  // Do this until the position is reached
        stepperState = 'T';
        stepperSpeed = 500 * homeDirT; // move in direction of Endstop
        MoveStepper(stepperState, stepperSpeed, abs(homeDirT));
      }
    }
    stepperState = 'O';
    stepperSpeed = 0;
    MoveStepper(stepperState, stepperSpeed, NO_CHECK);
    Serial.print("StepT reached position :");
    Serial.println(stepT);
  }

}

// get step direction
int sgn(int val) {
  if (val < 0) return -1;
  // if (val==0) return 0;
  return 1;
}

//Save Preset
void WritePreset(int Presetnr)
{
  int addressCount = 0;
  for (int i = 1; i <= Presetnr; i++) {  // blink NEOLED
    pixel.setPixelColor(0, dark);
    pixel.show();
    delay(500);
    pixel.setPixelColor(0, green);
    pixel.show();
    delay(500);
  }
  Serial.print("write actual stepvalues to Preset");
  Serial.println(Presetnr);  
  addressCount = 4*7*(Presetnr-1);
  Serial.print("to address = ");
  Serial.println(addressCount);
  writeLongToEEPROM(addressCount, LEDintensity);
  addressCount+=4;
  writeLongToEEPROM(addressCount, stepT);
  addressCount+=4;
//  writeLongToEEPROM(addressCount, stepR);
  writeLongToEEPROM(addressCount, -1);
  addressCount+=4;
  writeLongToEEPROM(addressCount, stepZ);
  addressCount+=4;
  writeLongToEEPROM(addressCount, stepX);
  addressCount+=4;
  writeLongToEEPROM(addressCount, stepY);
  addressCount+=4;
  writeLongToEEPROM(addressCount, stepC);
}

//Read & Set Preset value
void ReadPreset(int Presetnr)
{
  int addressCount = 0;
  int Position;
  Serial.print("Set stepvalues from Preset");
  Serial.println(Presetnr);  
  addressCount = 4*7*(Presetnr-1);
  Serial.print("from address = ");
  Serial.println(addressCount);
  Position=readLongFromEEPROM(addressCount);
  analogWrite(LEDPWM, Position);
  Serial.print("LEDPWM: ");
  Serial.println(Position);
  addressCount+=4;  
  Position=readLongFromEEPROM(addressCount);
  Serial.print("Go2To stepT position ");
  Serial.println(Position);    
  Go2Pos('T', Position);
  addressCount+=4;
  Position=readLongFromEEPROM(addressCount);
  Serial.print("Go2To stepR position ");
  Serial.println(Position);    
  Go2Pos('R', Position);
  addressCount+=4;
  Position=readLongFromEEPROM(addressCount);
  Serial.print("Go2To stepZ position ");
  Serial.println(Position);
  Go2Pos('Z', Position);
  addressCount+=4;
  Position=readLongFromEEPROM(addressCount);
  Go2Pos('X', Position);
  Serial.print("Go2To stepX position ");
  Serial.println(Position);
  addressCount+=4;
  Position=readLongFromEEPROM(addressCount);
  Serial.print("Go2To stepY position ");
  Serial.println(Position);
  Go2Pos('Y', Position);
  addressCount+=4;
  Position=readLongFromEEPROM(addressCount);
  Serial.print("Go2To stepC position ");
  Serial.println(Position);
  Go2Pos('C', Position);
}

  
//  Write Long to EEPROM
void writeLongToEEPROM(int address, long number)
{ 
  EEPROM.write(address, (number >> 24) & 0xFF);
  EEPROM.write(address + 1, (number >> 16) & 0xFF);
  EEPROM.write(address + 2, (number >> 8) & 0xFF);
  EEPROM.write(address + 3, number & 0xFF);
}

//  Read Long from EEPROM
long readLongFromEEPROM(int address)
{
  return ((long)EEPROM.read(address) << 24) +
         ((long)EEPROM.read(address + 1) << 16) +
         ((long)EEPROM.read(address + 2) << 8) +
         (long)EEPROM.read(address + 3);
}


