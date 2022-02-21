/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC5   //pin A5
#elif defined MY_ARDUINO_COUNTER
#define ENCODER_L 8  //编码器采集引脚 每路2个 共4个
#define DIRECTION_L 3
#define ENCODER_R 7
#define DIRECTION_R 2
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
