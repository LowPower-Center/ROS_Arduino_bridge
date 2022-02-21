/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined MY_ARDUINO_COUNTER
//#include <PinChangeInt.h>
//#include <MsTimer2.h>        //定时中断
volatile long left_count=0L;
volatile long right_count=0L ;   //左右轮编码器数据

//void control() {
//  sei();//全局中断开启
  //读取左轮编码器数据，并清零，这就是通过M法测速（单位时间内的脉冲数）得到速度。
  //读取右轮编码器数据，并清零
//}
  void initEncoders(){
  pinMode(ENCODER_L, INPUT);       //编码器引脚
  pinMode(DIRECTION_L, INPUT);       //编码器引脚
  pinMode(ENCODER_R, INPUT);        //编码器引脚
  pinMode(DIRECTION_R, INPUT);       //编码器引脚
    
  delay(200);                      //延时等待初始化完成
  attachInterrupt(0, READ_ENCODER_R, CHANGE);           //开启外部中断 编码器接口1
  attachInterrupt(1, READ_ENCODER_L, CHANGE);  //开启外部中断 编码器接口2
//  MsTimer2::set(10, control);       //使用Timer2设置5ms定时中断
//  MsTimer2::start();               //中断使能
  }
  
void READ_ENCODER_L() {
  if (digitalRead(ENCODER_L) == LOW) {     //如果是下降沿触发的中断
    if (digitalRead(DIRECTION_L) == LOW)      left_count--;  //根据另外一相电平判定方向
    else      left_count++;
  }
  else {     //如果是上升沿触发的中断
    if (digitalRead(DIRECTION_L) == LOW)      left_count++; //根据另外一相电平判定方向
    else     left_count--;
  }
}
/*****函数功能：外部中断读取编码器数据，具有二倍频功能 注意外部中断是跳变沿触发********/
void READ_ENCODER_R() {
  if (digitalRead(ENCODER_R) == LOW) { //如果是下降沿触发的中断
    if (digitalRead(DIRECTION_R) == LOW)      right_count++;//根据另外一相电平判定方向
    else      right_count--;
  }
  else {   //如果是上升沿触发的中断
    if (digitalRead(DIRECTION_R) == LOW)      right_count--; //根据另外一相电平判定方向
    else     right_count++;
  }
}
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_count;
    else return right_count; // It's just because my right encoder get reverse value so if yours is normal, don't add "-"
  }
  
  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_count=0L;
      return;
    } else {
      right_count=0L;
      return;
    }
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }

#elif defined TB6612_COUNTER
  volatile long left_count = 0L;//左轮计数器
  volatile long right_count = 0L;//右轮计数器
  void initEncoders(){
    pinMode(LEFT_ENC, INPUT);
    pinMode(RIGHT_ENC, INPUT);
    
    attachInterrupt(0, leftEncoderEvent, CHANGE);
    attachInterrupt(1, rightEncoderEvent, CHANGE);

  }
  void leftEncoderEvent(){
    if(digitalRead(LEFT_ENC) == HIGH){left_count++;}
       else { left_count--; }
    } 
  void rightEncoderEvent(){
    if(digitalRead(RIGHT_ENC) == HIGH){right_count++;}
       else { right_count--; }
    } 
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_count;
    else return right_count; // It's just because my right encoder get reverse value so if yours is normal, don't add "-"
  }
  
  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_count=0L;
      return;
    } else {
      right_count=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif
