#include <Servo.h>
#define echoPin 7
#define trigPin 8

Servo servo;
long distance;
int angle = 90;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  servo.attach(9);
  servo.write(angle);
  Serial.begin(9600);
}

void loop() {
  generateTrigger();
  distance = calcDist();
  delay(1000);
  Serial.println(distance);
  if(distance < 20){
    open_close(); 
  }
}

void generateTrigger(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
}

long calcDist(){
  long duration = pulseIn(echoPin, HIGH);
  duration /= 2;
  long dist = duration * 0.034;
  return(dist);
}

void open_close(){
  
  for(angle = 90; angle < 180; ++angle){
    servo.write(angle);
    delay(10);
  }

  delay(2000);

   for(angle = 180; angle > 90; --angle){
    servo.write(angle);
    delay(10);
  }

  
}
