/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
  
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
    }
    if (spd > 255)
      spd = 255;
    
    if (i == LEFT) { 
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_FORWARD, spd); analogWrite(RIGHT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_BACKWARD, spd); analogWrite(RIGHT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_FORWARD, spd); analogWrite(LEFT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_BACKWARD, spd); analogWrite(LEFT_MOTOR_FORWARD, 0); }
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298P_MOTOR_DRIVER
  void initMotorController() {
    pinMode(DIRA,OUTPUT);
    pinMode(PWMA,OUTPUT);
    pinMode(DIRB,OUTPUT);
    pinMode(PWMB,OUTPUT);
  }

void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;
  
  if (spd < 0)
  {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255){
    spd = 255;
  }
  
  if (i == LEFT) {
    if(reverse == 0) {
      digitalWrite(DIRA,HIGH);
      analogWrite(PWMA,spd);
    }else if (reverse == 1) {
      digitalWrite(DIRA,LOW);
      analogWrite(PWMA,spd);
    }
  }else{
    if(reverse == 0) {
      digitalWrite(DIRB,LOW);
      analogWrite(PWMB,spd);
    } else if (reverse == 1) {
      digitalWrite(DIRB,HIGH);
      analogWrite(PWMB,spd);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}


#elif defined TB6612_MOTOR_DRIVER
  void initMotorController() {
  //TB6612电机驱动模块控制信号初始化
  pinMode(AIN1, OUTPUT);//控制电机A的方向，(AIN1, AIN2)=(1, 0)为正转，(AIN1, AIN2)=(0, 1)为反转
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);//控制电机B的方向，(BIN1, BIN2)=(0, 1)为正转，(BIN1, BIN2)=(1, 0)为反转
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);//A电机PWM
  pinMode(PWMB, OUTPUT);//B电机PWM

  
  //初始化TB6612电机驱动模块
 /*
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 0);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 0);
  digitalWrite(STBY, 1);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
*/
  }

void setMotorSpeed(int i, int spd) {
  unsigned char reverse = 0;
  
  if (spd < 0)
  {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255){
    spd = 255;
  }
  
  if (i == LEFT) {
    if(reverse == 0) {
      digitalWrite(AIN1,HIGH);
      digitalWrite(AIN2,LOW);
      analogWrite(PWMA,spd);
    }else if (reverse == 1) {
      digitalWrite(AIN2,HIGH);
      digitalWrite(AIN1,LOW);
      analogWrite(PWMA,spd);
    }
  }else{
    if(reverse == 0) {
      digitalWrite(BIN1,HIGH);
      digitalWrite(BIN2,LOW);
      analogWrite(PWMB,spd);
    } else if (reverse == 1) {
      digitalWrite(BIN2,HIGH);
      digitalWrite(BIN1,LOW);
      analogWrite(PWMB,spd);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#else
  #error A motor driver must be selected!
#endif

#endif
