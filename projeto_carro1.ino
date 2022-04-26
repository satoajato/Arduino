// C++ code
//
#include <IRremote.h>
#include <Servo.h>

Servo meuServo;
int RECV_PIN = 0;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop()
{
  meuServo.attach(4);
  if(irrecv.decode(&results)) {
  Serial.println(results.value, HEX);
    switch(results.value) {
      
      case 0xFD807F: //vol+ -> acelera
      analogWrite(5,150);
      digitalWrite(10, LOW);
      break;
      
      case 0xFD906F: //vol- -> desacelera
      analogWrite(5,300);
      digitalWrite(10, LOW);
      break;
      
      case 0xFDA05F: //>||  -> freia
      analogWrite(5,0);
      digitalWrite(10, HIGH);
      break;
      
      case 0xFD20DF: //|<<  -> esquerda
      meuServo.write(150);
      break;
      
      case 0xFD609F: //>>|  -> direita
      meuServo.write(30);
      break;
      
      case 0xFD08F7: //1    -> seta esquerda
      digitalWrite(13,HIGH);
      delay(7000);
      digitalWrite(13,LOW);
      break;
      
      case 0xFD8877: //2	-> pisca alerta
      digitalWrite(11,HIGH);
      delay(1000);
      digitalWrite(11,LOW);
      delay(1000);
      digitalWrite(11,HIGH);
      delay(1000);
      digitalWrite(11,LOW);
      delay(1000);
      digitalWrite(11,HIGH);
      delay(1000);
      digitalWrite(11,LOW);
      break;
      
      case 0xFD48B7: //3	-> seta direita
      digitalWrite(12,HIGH);
      delay(7000);
      digitalWrite(12,LOW);
      break;
      
      case 0xFD50AF: //^	-> luz alta
      digitalWrite(7,HIGH);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      break;
      
      case 0xFD10EF: //v	-> luz baixa
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      break;
      
      case 0xFD00FF: //power  -> desliga o farol
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      break;
      
  }
    irrecv.resume();
  }
  delay(100);
}