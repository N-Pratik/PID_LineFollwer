#define m1 4  //Right Motor MA1
#define m2 5  //Right Motor MA2
#define m3 3  //Left Motor MB1
#define m4 2  //Left Motor MB2
#define e1 9  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB

//*********5 Channel IR Sensor Connection*********//
#define ir1 A0
#define ir2 A1
#define ir3 A2
#define ir4 A3
#define ir5 A5
//*************************************************//

int error = 0;
int prevError;
int cumError = 0;
int errorRate = 0;
int input;

int pace = 60;
int C = 3;
double R;

double Kp = 1.3;
double Kd = 0.03;
double Ki = 0.001;

void setup() { 
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

   getInput();
   
digitalWrite(m1,HIGH);
digitalWrite(m2,LOW);
digitalWrite(m3,HIGH);
digitalWrite(m4,LOW);
}

void loop(){
  getInput();
  errorfunc();

  
  cumError = cumError + error;
  errorRate = error - prevError; 
  R= Kp*error + Ki*cumError + Kd*errorRate;
  //Serial.println(R);
  foo();
  prevError = error;
}

void getInput(){
  int read0 = digitalRead(ir1);
  int read1 = digitalRead(ir2);
  int read2 = digitalRead(ir3);
  int read3 = digitalRead(ir4);
  int read4 = digitalRead(ir4);

  input = read0 + 2*read1 + 4*read2 +8*read3 +16*read4;
  Serial.println(input);
}

void foo(){
  if( input == 0 || input == 31){
    delay(200);
  analogWrite(e1,0);
  analogWrite(e2,0);
  cumError=0;
  errorRate=0;
  R=0;
  }

  else{
  analogWrite(e1,pace+ R*C);
  analogWrite(e2,pace- R*C); 
  }
}

void errorfunc(){
  if(input == 27){
    error = 0;
  }
  if(input == 25){
    error = 1;
  }
   if(input == 19){
    error = -1;
  }
   if(input == 29){
    error = 2;
  }
   if(input == 23){
    error = -2;
  }
   if(input == 28){
    error = 3;
  }
   if(input == 7){
    error = -3;
  }  
  if(input == 30){
    error = 3.5;
  }
   if(input == 15){
    error = -3.5;
  }  
}
