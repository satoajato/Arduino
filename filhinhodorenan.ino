#include <SoftwareSerial.h>

const int pinoRX = 10; //PINO DIGITAL 2(RX)
const int pinoTX = 11; //PINO DIGITAL 3 (TX)
const int pinoLedR = 2; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLedY = 3;
const int pinoLedG = 5;
const int buzzer = 13;

int dadoBluetooth = 1; //VARIAVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH
SoftwareSerial bluetooth(pinoRX, pinoTX); //PINOS QUE EMULAM A SERAL ONDE O PINO 2 É O RX E O PINO 3 É O TX
boolean loopLED = false; //VARIAVEL BOOLEANA QUE FAZ O CONTROLE E ATIVAÇÃO DO LOOP DO LED

int trig = 8;
int echo = 7;

float dist;  


void setup()  
{
  Serial.begin (9600);
  pinMode (trig, OUTPUT);
  pinMode (echo,INPUT);
  bluetooth.begin(9600);
  delay(100); //INTERVALO DE 100 MILESSEGUNDOS
  pinMode(pinoLedR,OUTPUT); //DEFINE O PINIO COMO SAÍDA
  pinMode(pinoLedY,OUTPUT);
  pinMode(pinoLedG,OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop()
{
  if(bluetooth.available()){
    dadoBluetooth = bluetooth.read();
  }
  digitalWrite(trig, LOW);
  delay(0250);
  digitalWrite(trig, HIGH);
  delay(0250);
  digitalWrite(trig, LOW);
  
  dist = pulseIn (echo, HIGH);
  dist = dist/58;
  Serial.println (dist);
  if(dist <10) {
    digitalWrite(pinoLedR,HIGH);
    digitalWrite(pinoLedY,LOW);
    digitalWrite(pinoLedG,LOW);
    if(dadoBluetooth == '1'){
      tone(buzzer, 392);
    }
    else if(dadoBluetooth == '0'){
      noTone(buzzer);
    }
  }
  else if (dist <20) {
    digitalWrite(pinoLedR,LOW);
    digitalWrite(pinoLedY,HIGH);
    digitalWrite(pinoLedG,LOW);
    if(dadoBluetooth == '1'){
      tone(buzzer, 261);
    }
    else if(dadoBluetooth == '0'){
      noTone(buzzer);
    }
  }
  else {
    digitalWrite(pinoLedR,LOW);
    digitalWrite(pinoLedY,LOW);
    digitalWrite(pinoLedG,HIGH);
    noTone(buzzer); 
  }
}
