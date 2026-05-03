#include <Arduino.h>
#include <IRremote.h>

int duration;
int distance;
int trigPin = 10;
int echoPin = 11;
int led1Pin = 9;
int led2pin = 3; // bocina
int Recv = 5;
bool desactivado = false;
bool activado = false;

void manejarDistancia()
{
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if (distance <= 10) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2pin, LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  IrReceiver.begin(Recv);
}

void loop()
{
  // LECTURA DEL CONTROL INFRARROJO
  if (IrReceiver.decode()) {
    unsigned long value = IrReceiver.decodedIRData.command;
    Serial.print("IR code: ");
    Serial.println(value);

    if (value == 12) {
      desactivado = true;
      activado = false;
    } else if (value == 16) {
      activado = true;
      desactivado = false;
    }

    IrReceiver.resume();
  }

  if (activado && !desactivado) {
    manejarDistancia();
digitalWrite(led1Pin, LOW);
    digitalWrite(led2pin, LOW);    
  }
  
  delay(100);
}

  

