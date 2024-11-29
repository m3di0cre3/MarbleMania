#include <Servo.h>

Servo servo1; Servo servo2; Servo servo3; Servo servo4;

int signalIn = 2;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long servoMillis1;
unsigned long servoMillis2;
unsigned long servoMillis3;
unsigned long servoMillis4;
unsigned long currServoMillis1;
unsigned long currServoMillis2;
unsigned long currServoMillis3;
unsigned long currServoMillis4;

// calibration
int minAngle = 0;
int maxAngle = 30;
int delayDiffs[] = {30, 0, 80, 0};
int moveTime = 210;
int marblesPer = 25;

int timer = 0;

bool isRunning1; bool isRunning2; bool isRunning3; bool isRunning4;
bool isGoingUp1; bool isGoingUp2; bool isGoingUp3; bool isGoingUp4;
int released1; int released2; int released3; int released4;

int pipeNum; int waitTime;

int waitTimes[120];
int pipeNums[120];
int dataCounter = 0;
int numInstructions;

void setup() {
  Serial.begin(115200);

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  pinMode(2, INPUT_PULLUP);
  pinMode(12, OUTPUT);

  servo1.write(maxAngle);
  servo2.write(maxAngle);
  servo3.write(minAngle);
  servo4.write(minAngle);
  while (Serial.available() == 0) {
    delay(10);
  }
  int counter = 0;
  int currWaitTime;
  int currPipeNum;
  while (true) {
    currWaitTime = Serial.parseInt();
    if (currWaitTime == -1){
      numInstructions = counter;
      break;
    }
    currPipeNum = Serial.parseInt();
    waitTimes[counter] = currWaitTime + delayDiffs[currPipeNum-1];
    pipeNums[counter] = currPipeNum;
    counter += 1;
  }
  waitTime = waitTimes[dataCounter];
  pipeNum = pipeNums[dataCounter];
  dataCounter += 1;
  delay(1000);
  startMillis = millis();
}

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= waitTime) {
    if (pipeNum == 1) {
      servo1.write(minAngle);
      servoMillis1 = millis();
      isRunning1 = true;
      isGoingUp1 = true;
    }
    else if (pipeNum == 2) {
      servo2.write(minAngle);
      servoMillis2 = millis();
      isRunning2 = true;
      isGoingUp2 = true;
    }
    else if (pipeNum == 3) {
      servo3.write(maxAngle);
      servoMillis3 = millis();
      isRunning3 = true;
      isGoingUp3 = true;
    }
    else if (pipeNum == 4) {
      servo4.write(maxAngle);
      servoMillis4 = millis();
      isRunning4 = true;
      isGoingUp4 = true;
    }

    if (dataCounter > numInstructions) {
      Serial.println(0);
      exit(0);
    }
    waitTime = waitTimes[dataCounter];
    pipeNum = pipeNums[dataCounter];
    dataCounter += 1;
    startMillis = currentMillis;
  }

  if (isRunning1) {
    currServoMillis1 = millis();
    if (currServoMillis1 - servoMillis1 >= moveTime/2 && isGoingUp1) {
      servo1.write(maxAngle);
      isGoingUp1 = false;
    }
    else if (currServoMillis1 - servoMillis1 >= moveTime) {
      isRunning1 = false;
    } 
  }
  if (isRunning2) {
    currServoMillis2 = millis();
    if (currServoMillis2 - servoMillis2 >= moveTime/2 && isGoingUp2) {
      servo2.write(maxAngle);
      isGoingUp2 = false;
    }
    else if (currServoMillis2 - servoMillis2 >= moveTime) {
      isRunning2 = false;
    }
  }
  if (isRunning3) {
    currServoMillis3 = millis();
    if (currServoMillis3 - servoMillis3 >= moveTime/2 && isGoingUp3) {
      servo3.write(minAngle);
      isGoingUp3 = false;
    }
    else if (currServoMillis3 - servoMillis3 >= moveTime) {
      isRunning3 = false;
    }
  }
  if (isRunning4) {
    currServoMillis4 = millis();
    if (currServoMillis4 - servoMillis4 >= moveTime/2 && isGoingUp4) {
      servo4.write(minAngle);
      isGoingUp4 = false;
    }
    else if (currServoMillis4 - servoMillis4 >= moveTime) {
      isRunning4 = false;
    }
  }
  if (digitalRead(2)) {
    digitalWrite(12, LOW);
  }
  else {
    digitalWrite(12, HIGH);
  }
}
