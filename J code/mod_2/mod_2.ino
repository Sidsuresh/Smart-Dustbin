#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#define trigPin D5
#define echoPin D6

long distance;

const long int channelID = 1575850;
const char *writeAPI = "M1A3HASNWBP73OO6";
const char *readAPI = "M9BTCYXD4VSH6LPQ" ;
const char *ssid = "SureshKumar";
const char *pwd = "Elam1234";


WiFiClient client;

void setup(){
  Serial.begin(115200); 
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  ThingSpeak.begin(client);
  WiFi.mode(WIFI_STA);
}

void loop(){
  createConn();
  distance = calcDist();
  int x = ThingSpeak.writeField(channelID, 1, distance, writeAPI);
  if(x == 200){
    distance = calcDist();
    digitalWrite(2, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
  }
  int val = ThingSpeak.readIntField(channelID, 1, readAPI);
  Serial.println(val);
  delay(15000);
}

void createConn(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pwd); //Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected");
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
  generateTrigger();
  long duration = pulseIn(echoPin, HIGH);
  duration /= 2;
  long dist = duration * 0.034;
  return(dist);
}
