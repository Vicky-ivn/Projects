#define S0_LEFT_EDGE A7
#define S1_LEFT_MIDLE A6
#define S2_LEFT_CENTER A5
#define S3_RIGHT_CENTER A4
#define S4_RIGHT_MIDLE A3
#define S5_RIGHT_EDGE A2

#define TURN_S0_S3_ON 2
#define TURN_S1_S4_ON 3
#define TURN_S2_S5_ON 4

#define LEFT_DIRECTION 9
#define LEFT_MOTOR 10
#define RIGHT_DIRECTION 5
#define RIGHT_MOTOR 6

#define BUTTON_PIN 7
#define LED_RED 12
#define LED_WHITE 13

#define NOISE 20

//first time 43s

//3.0 0.32 90 19.49s
// 2.9 0.40 95 19.62s
//3.2 0.32 100 19.52s
//3.4 0.34 100 19.59s
//3.4 0.347 105 19.85s

// KD KP SPEED TIME
// 2.6 0.37 65 25.24s
// 2.8 0.37 70 23.77s
// 2.8 0.359 75 24s

// 2.8 0.34 85 22.38s
// 2.8 0.35 90 20.18s
// 2.9 0.40 95 19.62s


//new battery
//2.9 0.40 95 20.43s

//3.2 0.32 100 19.52s
//3.2 0.33 100 20.11s
//3.2 0.315 100 19.72s

//3.2 0.32 105 19.93s
//3.2 0.325 105 20.42s
//3.2 0.328 105 20.98s
//3.2 0.324 105 21.42s    

//3.2 0.38 110 20.82s
//3.2 0.32 100 20.58s
//3.4 0.33 100 19.62s
//3.4 0.34 100 19.59s
//3.5 0.345 100 19.95s
//3.41 0.343 100 19.73s

//3.4 0.33 105 19.91s
//3.5 0.35 105 20.22s
//3.4 0.345 105 20.63s
//3.5 0.35 105 21.14s
//3.4 0.347 105 19.85s
//3.465 0.348 105 20.49s
//3.00 0.3 90 19.41s
//3.00 0.32 90 19.52s
//3.00 0.3 100 19.81s
//3.05 0.31 100 21.63s
//3.0 0.29 100 19.82s
//3.0 0.32 100 19.49s
//3.1 0.321 100 19.54s
//3 0.3 100 20.00s
//3 0.33 100 19.77s
//3 0.33 100 19.55s

//brakes (-40)
//3 0.33 100 19.58s
//3 0.32 100 19.46s
//3.2 0.324 105 20.28s
//3 0.323 105 20.70s
//3.2 0.32 98 19.98s
//3.2 0.33 98 19.47s
//3.3 0.335 98 19.77s
//3.3 0.332 98 20.17s

//3.3 0.33 95 19.03s
//3.3 0.33 95 19.03s

//3.4 0.34 96 18.88s

//3.5 0.34 97 18.91s
//3.5 0.34 97 18.86s

//3.6 0.35 98 18.91s //ne

//3.6 0.35 97 19.15s
//3.7 0.35 98 18.98s
//3.6 0.353 98 18.85s

//3.6 0.353 98 18.85s
//3.6 0.355 99 19.15s
//3.6 0.36 99 20.56s

//best 3.6 0.353 98 18.85s

//3.6 0.36 99 20.56s
//3.6 0.3515 100 18.81s

//best 3.6 0.355 100 18.81s
//best 4.67 0.450 103 18.01s
//best 4.8 0.450 103 17.81s

//4.7 0.43 102 18.52s
//4.7 0.43 103 18.66s
//4.7 0.43 101 18.72s
//4.67 0.45 103 19.14
//5.3 0.50 100 18.62s
//5.2 0.47 100 18.52s
//5.2 0.46 100 19.01s
//5.3 0.455 100 19.00s
//5.5 0.453 100 18.44s
//5.5 0.452 100 19.01s
//5.6 0.453 100 18.27s
//5.7 0.453 100 18.46s

#define KD 5.7
#define KP 0.453
#define MAX_SPEED 100

#define TURN_SPEED 90

//#define DEBUG
//#define STATE

#define FORWARD 0
#define RECOVERY_LEFT 1
#define SEARCH_LEFT 2
#define BRAKES_RIGHT 3
#define BRAKES_LEFT 4
#define RECOVERY_RIGHT 5
#define SEARCH_RIGHT 6
#define DEBUG_2 7

int sensor_value[6];
int minimum[6]={2000,2000,2000,2000,2000,2000};
int maximum[6]={0};
int znamenatel[6];
int value[6];
int noramal[6];

long long top, bottom;

int noline=0;

int last_error=0;
int error=0;

//int state=DEBUG_2;
int state=FORWARD;

int direction=0;

void sensor_value_read(){
 digitalWrite(TURN_S0_S3_ON, LOW);
  delayMicroseconds(50);
  sensor_value[0]= analogRead(S0_LEFT_EDGE);
  sensor_value[3]= analogRead(S3_RIGHT_CENTER);
 digitalWrite(TURN_S0_S3_ON, HIGH);

 digitalWrite(TURN_S1_S4_ON, LOW);
  delayMicroseconds(50);
  sensor_value[1]= analogRead(S1_LEFT_MIDLE);
  sensor_value[4]= analogRead(S4_RIGHT_MIDLE);
 digitalWrite(TURN_S1_S4_ON, HIGH);

 digitalWrite(TURN_S2_S5_ON, LOW);
  delayMicroseconds(50);
   sensor_value[2]= analogRead(S2_LEFT_CENTER);
   sensor_value[5]= analogRead(S5_RIGHT_EDGE);
 digitalWrite(TURN_S2_S5_ON, HIGH);
}

void sensor_value_print(){
  for(int i=0;i<6;i++){
    Serial.print(sensor_value[i]);
    Serial.print(" ");
  }
  Serial.println();
}

  void sensor_calibrate(){
    digitalWrite(LED_RED, HIGH);
    
    for(int i=0;i<6;i++){
      if(minimum[i]>sensor_value[i]){
        minimum[i]=sensor_value[i];
      }
      if(maximum[i]<sensor_value[i]){
        maximum[i]=sensor_value[i];
      }
    }
    for(int i=0;i<6;i++){
      znamenatel[i]=(maximum[i]-minimum[i])/10;
    }

  }

  void sensor_calibrate_print(){
    for(int i=0;i<6;i++){
      Serial.print(maximum[i]);
      Serial.print(" ");
    }
    Serial.println();

    for(int i=0;i<6;i++){
      Serial.print(minimum[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

void normal_read(){
  for(int i=0;i<6;i++){
    if(sensor_value[i]>maximum[i]){
      sensor_value[i]=maximum[i];
    }
    if(sensor_value[i]<minimum[i]){
      sensor_value[i]=minimum[i];
    }
    value[i]=(sensor_value[i]-minimum[i])*10;
    noramal[i]=value[i]/znamenatel[i];
    if(noramal[i]<NOISE){
      noramal[i]=0;
    }
  }
  
}
void normal_print(){
  for(int i=0;i<6;i++){
    Serial.print(noramal[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(20); 
}

void error_value(){
  top = (long long)noramal[0]*100 + (long long)noramal[1]*200 + (long long)noramal[2]*300 + (long long)noramal[3]*400 + (long long)noramal[4]*500 + (long long)noramal[5]*600;
  bottom = (long long)noramal[0] + (long long)noramal[1] + (long long)noramal[2] + (long long)noramal[3] + (long long)noramal[4] + (long long)noramal[5];

  if(bottom<20){
    noline++;
    if(last_error<0){
      //ot lqvo
      direction=BRAKES_LEFT;
      error=-250;
    }
    else{
      //ot dqsno
      direction=BRAKES_RIGHT;
      error=250;
    }
  }
  else{
    noline=0;
    error=(int)(top/bottom) -350;
  }
}

void error_print(){
  Serial.print(error);
  Serial.println();
}

void right_motor(int speed){
  if(speed<0){
    digitalWrite(RIGHT_DIRECTION, LOW);
  }
  else{
    digitalWrite(RIGHT_DIRECTION, HIGH);
  }
  speed=abs(speed);

  analogWrite(RIGHT_MOTOR, speed);
}

void left_motor(int speed){
  if(speed<0){
    digitalWrite(LEFT_DIRECTION, LOW);
  }
  else{
    digitalWrite(LEFT_DIRECTION, HIGH);
  }
  speed=abs(speed);

  analogWrite(LEFT_MOTOR, speed);
}

void auto_calibrate(){

  digitalWrite(LED_RED, HIGH);

  right_motor(25);
  left_motor(-25);

  for(int i=0;i<600;i++){
    sensor_value_read();

    for(int y=0;y<6;y++){
      if(sensor_value[y]>maximum[y]){
        maximum[y]=sensor_value[y];
      }
      if(sensor_value[y]<minimum[y]){
        minimum[y]=sensor_value[y];
      }
    }

    if(i==200){
      right_motor(-25);
      left_motor(25);
    }
    delay(2);
  }

  for(int i=0;i<6;i++){
    znamenatel[i]=(maximum[i]-minimum[i])/10;
  }

  sensor_value_read();  
  normal_read();

  right_motor(25);
  left_motor(-25);

  int pos=noramal[3];

  while(pos<=80){
    sensor_value_read();
    normal_read();
    pos=noramal[3];

#ifdef DEBUG
    Serial.println(pos);
#endif

    delay(5);
  }

  right_motor(0);
  left_motor(0);
}

// void no_line(){
// if(noramal[0]+noramal[1]+noramal[2]+noramal[3]+noramal[4]+noramal[5] == 0)
// noline++;
// else 
// noline = 0;
  
// if(noline>40){
// digitalWrite(LED_RED, LOW);
// digitalWrite(LED_WHITE, LOW);

// right_motor(0);
// left_motor(0);

// while(1);
// }

// }

void brakes(){
  left_motor(-40);
  right_motor(-40);
  delay(10);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(TURN_S0_S3_ON, OUTPUT);
  pinMode(TURN_S1_S4_ON, OUTPUT);
  pinMode(TURN_S2_S5_ON, OUTPUT);

  pinMode(S0_LEFT_EDGE, INPUT);
  pinMode(S1_LEFT_MIDLE, INPUT);
  pinMode(S2_LEFT_CENTER, INPUT);
  pinMode(S3_RIGHT_CENTER, INPUT);
  pinMode(S4_RIGHT_MIDLE, INPUT);
  pinMode(S5_RIGHT_EDGE, INPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(LED_WHITE, OUTPUT);
    digitalWrite(LED_WHITE, HIGH);
    delay(10);
    digitalWrite(LED_WHITE, LOW);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(LEFT_DIRECTION, OUTPUT);
  pinMode(RIGHT_DIRECTION, OUTPUT);
  
  pinMode(BUTTON_PIN, INPUT);

  Serial.begin(9600);

  while(digitalRead(BUTTON_PIN)!=0){}
  delay(1000);
  auto_calibrate();  
  digitalWrite(LED_WHITE, HIGH);

  while(digitalRead(BUTTON_PIN)!=0){
   // sensor_value_read();
   // sensor_calibrate(); 
  }

  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_value_read();
  normal_read();
  error_value();

  if(state==FORWARD)
  {
    int rotation_speed = (int)(KP*(float)error +KD*(float)(error-last_error) );

    left_motor(MAX_SPEED+rotation_speed);
    right_motor(MAX_SPEED-rotation_speed);

    if(noline>10){
      state=direction;
    }
  } else if (state == DEBUG_2) {
    Serial.println(error);
    delay(200);
  }
  else if(state==BRAKES_RIGHT){
    brakes();
    state=SEARCH_RIGHT;
  }

  else if(state==BRAKES_LEFT){
    brakes();
    state=SEARCH_LEFT;
  }

  else if(state==SEARCH_RIGHT)
  {
    left_motor(80);
    right_motor(-10);
    if(error<200){
    state=RECOVERY_RIGHT;
    }
  }
  else if(state==RECOVERY_RIGHT){
    left_motor(MAX_SPEED-(MAX_SPEED/4));
    right_motor(MAX_SPEED);
    delay(10);
    state=FORWARD;
    last_error=0;
  }

  else if(state==SEARCH_LEFT)
  {
    left_motor(-10);
    right_motor(80);
    if(error>-200){
      state=RECOVERY_LEFT;
    }
  }
  else if(state==RECOVERY_LEFT){
    left_motor(MAX_SPEED);
    right_motor(MAX_SPEED-(MAX_SPEED/4));
    delay(10);
    state=FORWARD;
    last_error=0;
  }

  last_error=error;

}
