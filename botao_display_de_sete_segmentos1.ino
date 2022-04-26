// C++ code
//
const int A = 7;
const int B = 6;
const int C = 4;
const int D = 3;
const int E = 2;
const int F = 9;
const int G = 10;

const int PT = 5;
int x =0;

boolean ligabotao = false;
const int l = 1, d = 0;

void setup()
{
  pinMode(13, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(PT, OUTPUT);
}

void loop()
{
  if(digitalRead(13)) {
    delay(200);
    if(x==0) {
      digitalWrite(A, l); //0
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, l);
      digitalWrite(F, l);
      digitalWrite(G, d);
    }
    if(x==1) {
      digitalWrite(A, d); //1
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, d);
      digitalWrite(E, d);
      digitalWrite(F, d);
      digitalWrite(G, d);
    }
    if(x==2) {
      digitalWrite(A, l); //2
      digitalWrite(B, l);
      digitalWrite(C, d);
      digitalWrite(D, l);
      digitalWrite(E, l);
      digitalWrite(F, d);
      digitalWrite(G, l);
    }
    if(x==3) {
      digitalWrite(A, l); //3
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, d);
      digitalWrite(F, d);
      digitalWrite(G, l);
    }
    if(x==4) {
      digitalWrite(A, d); //4
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, d);
      digitalWrite(E, d);
      digitalWrite(F, l);
      digitalWrite(G, l);
    }
    if(x==5) {
      digitalWrite(A, l); //5
      digitalWrite(B, d);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, d);
      digitalWrite(F, l);
      digitalWrite(G, l);
    }
    if(x==6) {
      digitalWrite(A, l); //6
      digitalWrite(B, d);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, l);
      digitalWrite(F, l);
      digitalWrite(G, l);
    }
    if(x==7) {
      digitalWrite(A, l); //7
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, d);
      digitalWrite(E, d);
      digitalWrite(F, d);
      digitalWrite(G, d);
    }
    if(x==8) {
      digitalWrite(A, l); //8
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, l);
      digitalWrite(F, l);
      digitalWrite(G, l);
    }
    if(x==9) {
      digitalWrite(A, l); //9
      digitalWrite(B, l);
      digitalWrite(C, l);
      digitalWrite(D, l);
      digitalWrite(E, d);
      digitalWrite(F, l);
      digitalWrite(G, l);
      x=-1;
    }
    x++;
  }
}

