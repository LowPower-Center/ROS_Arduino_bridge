/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 5
  #define LEFT_MOTOR_BACKWARD  6
  #define RIGHT_MOTOR_FORWARD  9
  #define LEFT_MOTOR_FORWARD   10
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_ENABLE 13
#elif defined L298P_MOTOR_DRIVER
  #define DIRA 4
  #define PWMA 5
  #define DIRB 7
  #define PWMB 6

#elif defined TB6612_MOTOR_DRIVER
//定义引脚名称
#define PWMA A1  //3为模拟引脚，用于PWM控制
#define AIN1 4
#define AIN2 7
#define PWMB A2  //10为模拟引脚，用于PWM控制
#define BIN1 9
#define BIN2 8


#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
