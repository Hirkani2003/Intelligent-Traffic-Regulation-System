#include <ESP8266WiFi.h>
WiFiServer server(80);
#define red D2
#include <Servo.h>
Servo myservo; 
int pos = 0;
int timer1;
int timer2;
float Time;
int flag1 = 0;
int flag2 = 0;
float distance = 5.5;
float speed = 0;
int ir_s1 = 16;
int ir_s2 = 5;
int flag = 0;

void setup(){
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
//  WiFi.begin("OnePlus_ONEPLUS_A6000_co_aptmfl","isha2003");
// WiFi.begin("Contractor","Bramha@206");
  
  while(WiFi.status() != WL_CONNECTED)
  { delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("NodeMCU is Connected");
  Serial.println(WiFi.localIP());
  server.begin();
  myservo.attach(14);
  myservo.write(0);
}

void loop() {
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<center>");
  client.println("<h1 style=background-color:DodgerBlue;>Speed Status</h1>");
  
  if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}
  if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}
  
  if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
     else if(timer2 > timer1){Time = timer2 - timer1;}
     Time=Time/1000;
     speed=(distance/Time);
     speed=speed*3600;
     speed=speed/1000;-
     Serial.print("Speed: ");
     Serial.print(speed);
     Serial.println(" Km/Hr");
     flag1 = 0;
     flag2 = 0; 
     flag = 1;
  }
   client.println("<p><strong>"+String(speed)+"</strong></p>");
   if(flag == 1 and speed > 15){
    digitalWrite(red, HIGH);
    for (pos = 0; pos <= 90; pos += 1) {
      myservo.write(pos);
      delay(3);             
    }
    delay(5000);
    for (pos = 90; pos >= 0; pos -= 1) { 
      myservo.write(pos);
      delay(3);              
      }
    digitalWrite(red, LOW);
    flag = 0;
   }
   client.println("</center>"); 
   client.println("</html>");
}
