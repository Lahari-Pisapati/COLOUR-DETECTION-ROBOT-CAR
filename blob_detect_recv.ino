#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";

int pwm = 120;

int mr1 = 10;
int mr2 = 9;
int ml1 = 6;
int ml2 = 5;

void forward();
void right();
void left();
void wait();

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("started");
  pinMode(mr1,OUTPUT);
  pinMode(mr2,OUTPUT);
  pinMode(ml1,OUTPUT);
  pinMode(ml2,OUTPUT);
  wait();
}

void loop() {
  char text;
  if(radio.available())
  {
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
    if (text == 'f')
    {
      Serial.println("forward");
      forward();
    }
    else if(text == 'r')
    {
      Serial.println("right");
      right();
    }
    else if(text == 'l')
    {
      Serial.println("left");
      left();
    }
    else if(text == 's')
    {
      Serial.println("stop");
      wait();
    }
    else
    {
      Serial.println("no data");
      wait();
    }
  }
}

void forward()
{
  analogWrite(mr1,pwm);
  digitalWrite(mr2,LOW);
  analogWrite(ml1,pwm);
  digitalWrite(ml2,LOW); 
}
void right()
{
  analogWrite(mr1,LOW);
  analogWrite(mr2,pwm);
  analogWrite(ml1,pwm);
  digitalWrite(ml2,LOW); 
}
void left()
{
  analogWrite(mr1,pwm);
  analogWrite(mr2,LOW);
  analogWrite(ml1,LOW);
  analogWrite(ml2,pwm); 
}
void wait()
{
  analogWrite(mr1,LOW);
  analogWrite(mr2,LOW);
  analogWrite(ml1,LOW);
  digitalWrite(ml2,LOW); 
}
