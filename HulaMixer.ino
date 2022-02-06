//This code controls the hula mixer functions. Currently it will rotate 5 times then shake 4x 45 degrees apart.
//Feel free to modify the code here. An FTDI programming board is required.
//The arduino is an arduino mini with the old bootloader. Be sure to select old bootloader when flashing.
//These top five lines are the primary lines to control functionality. If you don't want any shaking set times to shake to 0
const int stepsPerShake = 150; // how many pulses in one shake
const int numTimesToShake = 5; // how many flicks back and forth do we want
const int revsPerCycle = 5;  // revolutions before a shake occurs
const int motorSpeed = 1000;  // How fast are we going - lower values are faster
const int shakeSpeed = 300; // How fast are we going - lower values are faster - motor skips ~220


const int stepsPerRev = 3200; // change as needed
int count, rotateCount, shakeCount;
const int dirForward = 1;
const int dirReverse = 0;
const int stepperPulsePin = 4;
const int stepperDirectionPin = 3;
const int ms1 = 9;
const int ms2 = 8;
const int ms3 = 7;

void setup() {
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  pinMode(stepperPulsePin, OUTPUT);
  pinMode(stepperDirectionPin, OUTPUT);


  //set all pins low for half steps - adjust as needed
  digitalWrite(ms1, HIGH); //ms1
  digitalWrite(ms2, HIGH);  //ms2
  digitalWrite(ms3, HIGH);  //ms3

  //set pulse pin low, I don't know why but I'm doing it anyway
  digitalWrite(stepperPulsePin, LOW);
  //set spin direction to forward
  digitalWrite(stepperDirectionPin, dirForward);

  delay(1000); //Dont want to start this immediately

}

void loop() {
  int spinPulses = ((revsPerCycle * stepsPerRev) - (stepsPerRev / 8));
  for (count = 0; count <= spinPulses; count++) {

    digitalWrite(stepperPulsePin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepperPulsePin, LOW);
    delayMicroseconds(motorSpeed);

  }

  //shakey boi
  for (rotateCount = 0; rotateCount <= 3; rotateCount++) {

    //rotate quarter turns
    for (count = 0; count <= (stepsPerRev / 4); count++) {
      digitalWrite(stepperPulsePin, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepperPulsePin, LOW);
      delayMicroseconds(motorSpeed);
    }


    for (shakeCount = 0; shakeCount <= numTimesToShake; shakeCount++) { //shake some number of times then rotate again
      Shake();
    }
  }
  //add back the 1/8 turns worth of rotations we did to keep shake cycles consistent
  int spinPulsesCorrection = (stepsPerRev / 8);
  for (count = 0; count <= spinPulsesCorrection; count++) {

    digitalWrite(stepperPulsePin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepperPulsePin, LOW);
    delayMicroseconds(motorSpeed);

  }
}

void Shake() { //this amounts to one full "shake"
  for (count = 0; count <= stepsPerShake; count++) {
    digitalWrite(stepperPulsePin, HIGH);
    delayMicroseconds(shakeSpeed);
    digitalWrite(stepperPulsePin, LOW);
    delayMicroseconds(shakeSpeed);
  }
  digitalWrite(stepperDirectionPin, dirReverse);

  for (count = 0; count <= stepsPerShake; count++) {
    digitalWrite(stepperPulsePin, HIGH);
    delayMicroseconds(shakeSpeed);
    digitalWrite(stepperPulsePin, LOW);
    delayMicroseconds(shakeSpeed);
  }
  digitalWrite(stepperDirectionPin, dirForward);

}
