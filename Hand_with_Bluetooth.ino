// SERVO_ARRAY
// 
// Made by Julius Garcia

#include <Servo.h>
int incomingByte = 0;
String content = "";

#define number_of_servos 4
Servo servos[number_of_servos];
int servoPins[] = {8,9,10,11,12};
int servoPosMax[] = {180, 180, 180, 180, 180};
int servoPosMin[] = {0, 0, 0, 0, 0};
int servoPosSafeStart[] = {0, 0, 0, 0, 0};

void initServos() {
  for (int i=0; i<number_of_servos; i++) 
  {
    servos[i].attach(servoPins[i]);
    servos[i].write(servoPosMax[i]);
  }
  
  Serial.println("Ready..." );
}

void setServo(int num, int deg) {
  deg = constrain(deg, servoPosMin[num], servoPosMax[num]);
  servos[num].write(deg);
}

void close() {
  for (int i=0; i<number_of_servos; i++) 
  {
    servos[i].attach(servoPins[i]); // servo setup
    servos[i].write(servoPosMax[i]);
    delay(10); //10 milisecond
  }
}

void open() {
  for (int i=0; i<number_of_servos; i++) 
  {
    servos[i].attach(servoPins[i]); // servo setup
    servos[i].write(servoPosSafeStart[i]);
  }
}

void countByFinger(int noItem) {
  close();
  int temp = 0;
  if(noItem > number_of_servos)
  {
  	temp = noItem - number_of_servos;
    noItem = 4;
  }
  for (int ctrItem=0; ctrItem<noItem; ctrItem++) 
  {  
    int i;
    for (i=ctrItem; i<=ctrItem; i++) 
    {
      servos[i].attach(servoPins[i]); // servo setup
      servos[i].write(servoPosSafeStart[i]);
    }
    delay(1000); 
    
  }
  if(temp > 0){
  close();
  delay(1000); 
  countByFinger(temp);
  }
}

void setup() {
  Serial.begin(9600);
  initServos();
}

void loop() {
  
  while(Serial.available()) {
      content = Serial.readString();
  }
  
  int counter = 0;
  if(content.indexOf(" ") > 0)
  {
    String temp = content.substring(content.indexOf(" ") +1);
  	content = content.substring(0,content.indexOf(" "));

    counter = temp.toInt();
  }
  
  
  if (content != "") {
    Serial.println(content);
  }
  
  if(content == "close")
  {
    close();  
  }
  else if(content == "open")
  {
    open();  
  } 
  else if(content == "count"){
  	countByFinger(counter);
  }
  content = "";
}
