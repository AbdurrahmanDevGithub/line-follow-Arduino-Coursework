#include <AFMotor.h>

//assign pins for the motors
AF_DCMotor motor1(3); //1
AF_DCMotor motor2(4); //2
AF_DCMotor motor3(2); //3
AF_DCMotor motor4(1); //4

//ultraSonic Sensor
const int trig = A2;
const int echo = A3;
float duration, distance;

//IR Sensors
const int ir1 = A0;
const int ir2 = A1;
const int ir3 = A4;
const int ir4 = A5;

int right;
int left;
int midRight;
int midLeft;

int aright;
int aleft;
int amidRight;
int amidLeft;

int red = 22;
int yellow = 23;
int green = 24;

void setup() {
  // put your setup code here, to run once:

  //motor speed
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(130);
  motor4.setSpeed(130);

  //ultraSonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //IR Sensor
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);

  Serial.begin(9600);

  //led
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}//void setup end

void loop() {
  // put your main code here, to run repeatedly:

  right = IrValue(ir1);
  midRight = IrValue(ir2);
  midLeft = IrValue(ir3);
  left = IrValue(ir4);

  // aright = analogRead(ir1);
  // amidRight = analogRead(ir2);
  // amidLeft = analogRead(ir3);
  // aleft = analogRead(ir4);

  // Serial.print(aleft);
  // Serial.print("  ");
  // Serial.print(amidLeft);
  // Serial.print("  ");
  // Serial.print(amidRight);
  // Serial.print("  ");
  // Serial.print(aright);
  // Serial.println(".....");

  
  if(getObstacle() == LOW){

    if(left == LOW && midLeft == HIGH && midRight == HIGH && right == LOW){
      // 0 1 1 0
      moveForward();
      light();
    }else if(left == LOW  && midLeft == LOW && midRight == HIGH && right == HIGH){
      // 0 0 1 1
      turnRight();
    }else if(left == HIGH && midLeft == HIGH && midRight == LOW && right == LOW){
      // 1 1 0 0
      turnLeft();
    }else if(left == LOW  && midLeft == HIGH && midRight == HIGH && right == HIGH){
      // 0 1 1 1    *sharp right turn
      sharpRight();
    }else if(left == HIGH  && midLeft == HIGH && midRight == HIGH && right == LOW){
      // 1 1 1 0    *sharp lefAt turn
      sharpLeft();
    }else if(left == LOW  && midLeft == LOW && midRight == LOW && right == HIGH){
      // 0 0 0 1
      turnRight();
    }else if(left == HIGH  && midLeft == LOW && midRight == LOW && right == LOW){
      // 1 0 0 0 
      turnLeft();
    }else if(left == LOW  && midLeft == LOW && midRight == HIGH && right == LOW){
      // 0 0 1 0 
      turnRight();
    }else if(left == LOW  && midLeft == HIGH && midRight == LOW && right == LOW){
      // 0 1 0 0 
      turnLeft();
    }else if(left == HIGH  && midLeft == HIGH && midRight == HIGH && right == HIGH){
      // 1 1 1 1    *Loop
      // moveForward(); delay(200); //adjest the delay as needed
      // if(left == LOW  && midLeft == LOW && midRight == LOW && right == LOW){
        stop();
        delay(200);
        turnBack();
      // }
      // stop();
    }
    else{
      stop();
    }

  }else if(getObstacle() == HIGH){
    // if detect an obstacle
    stop();
    delay(2000);
    
    if(getObstacle() == HIGH){
      passObs();
    }
    
  }
  // delay(1000); 
}//void loop end.




//methods to move the robot

// forward method
void moveForward(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
// turn right method
void turnRight(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
// // turn left method
void turnLeft(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
//stop method
void stop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void sharpRight(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(600);
}
void sharpLeft(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(600);
}
// turn 180
void turnBack(){
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(1650);
}

//pass obstacle
void passObs(){
  turnLeft();
  delay(600);
  moveForward();
  delay(500);
  turnRight();
  delay(600);

  moveForward();
  delay(900);

  turnRight();
  delay(700);
  moveForward();
  delay(400);
  turnLeft();
  delay(700);
}




//Additional Method Section

int getObstacle(){  //start
  //this method will return the 1 if obstacle is detected

  //trigger the sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //get the distance
  duration = pulseIn(echo, HIGH);
  distance = (duration*0.0343)/2;

  int obs;
  if(distance <= 20){
    obs = 1;
  }else{
    obs = 0;
  }

  return obs;
} //end


int IrValue(int ir){  //start

  //method will return 0/1 from IR analog signals

  int red = analogRead(ir);
  int value;

  if(red <1000){
    value = 0;
  }else if(red > 1000){
    value = 1;
  }

  return value;
} //end

void light(){
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  delay(100);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  delay(50);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(100);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  delay(1000);
}
