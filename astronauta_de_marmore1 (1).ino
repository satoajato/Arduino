#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>

#define ASTRO_CHAR 0
#define METEOR_CHAR 1
#define LIFE_BONUS 2


LiquidCrystal lcd(12, 11, 6, 5, 4, 1);

static bool colide = false;
static bool colide_heart = false;
static bool life_increased = false;
static bool roundRecentlyStarted = false;
int delayLevel = 300;
int level = 0;
int life = 3;
int score = 0;
static bool playing = false;
int position_astro = 1;
const byte interruptPin_Start = 2;
const byte interruptPin_Jump = 3;

volatile byte button_Start_Pushed = LOW;
volatile byte button_Jump_Pushed = LOW;

byte astro[8] = {B00000, 
                 B01111, 
                 B11001, 
                 B11111, 
                 B11111, 
                 B01111, 
                 B01001, 
                 B10010,};
byte meteor[8] = {B00000, 
                  B01110, 
                  B11111, 
                  B11111, 
                  B11101, 
                  B11111, 
                  B01110, 
                  B00000,};
byte heart[8] =   {B00000, 
                  B00000, 
                  B01010, 
                  B11111, 
                  B11111, 
                  B01110, 
                  B00100, 
                  B00000,};



void setup(){
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(ASTRO_CHAR,astro);
  lcd.createChar(METEOR_CHAR,meteor);
  lcd.createChar(LIFE_BONUS,heart);
  lcd.setCursor(1,1);
  lcd.write((byte)ASTRO_CHAR);
  
  
  pinMode(interruptPin_Start, INPUT_PULLUP);
  pinMode(interruptPin_Jump, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin_Start), button_Start_Push, FALLING);  
  attachInterrupt(digitalPinToInterrupt(interruptPin_Jump), button_Jump_Push, CHANGE);  

}

void move(){
   
}

void loop(){
  
  static bool blink = false;
  if (!playing) {
  	
  	if (blink) {
    	lcd.setCursor(0,0);
      	lcd.print("Press Start");
      	lcd.setCursor(1,1);
  	  	lcd.write(' ');  
    }
    else{
    	lcd.setCursor(0,0);
      	lcd.print("           ");
      	drawAstro();
    }
  	delay(250);
    blink = !blink;
    if (button_Start_Pushed){
      startGame();
    }
  }
}

void startGame(){
	  lcd.clear();
      drawAstro();
      playing = true;
  	  position_astro = 1;
      life=3;
      score = 0;
      level = 0;
      button_Start_Pushed = LOW;
      lcd.setCursor(13,0);
  	  lcd.print(score);
  	  lcd.setCursor(13,1);
      lcd.print(life);
      lcd.setCursor(14,1);
      lcd.write((byte)LIFE_BONUS);
      game();
}

void game(){
  while(life>0){
    if(life<3) life_increased = false;
    else life_increased = true;
    drawAstro();
  	meteorAttacks_and_bonus(rand() % 9);
  }
  endgame();
}

void endgame(){
  playing = false;
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SCORE:");
  lcd.setCursor(10,0);
  lcd.print(score);
  lcd.setCursor(3,1);
  lcd.print("> Play Again");
  while(button_Start_Pushed==false){
  }
  roundRecentlyStarted=true;
  startGame();
}

void button_Start_Push() {
  button_Start_Pushed = !button_Start_Pushed;
}

void button_Jump_Push() {
  if(playing==true){
  if(roundRecentlyStarted==false )
  	button_Jump_Pushed = !button_Jump_Pushed;
    else if (roundRecentlyStarted==true){
      button_Jump_Pushed = 1;
      roundRecentlyStarted = false;
    }
  if(colide==true){
    lifeDecrease();
  	colide=false;
  }
  if(colide_heart==true){
    lifeIncrease();
  	colide_heart=false;
  }
  if(button_Jump_Pushed==1) {
        position_astro = 0;
       	lcd.setCursor(1,1);
  		lcd.write(' ');
        lcd.setCursor(1,0);
  		lcd.write((byte)ASTRO_CHAR);
  }
  if(button_Jump_Pushed==0) {
        position_astro = 1;
       	lcd.setCursor(1,0);
  		lcd.write(' ');
        lcd.setCursor(1,1);
  		lcd.write((byte)ASTRO_CHAR);
  }
  }
}

void drawAstro(){
  lcd.setCursor(1,position_astro);
  lcd.write((byte)ASTRO_CHAR);
  int apagar;
  if(position_astro == 0) apagar = 1;
  else apagar = 0;
  lcd.setCursor(1,apagar);
  lcd.write(" ");
}

void meteorAttacks_and_bonus(int numAttack){
  delay(delayLevel);
  if(numAttack==0){
    
    for(int i = 12; i>=-1; i--){
      showMeteor(i, 1);
      delay(delayLevel);
         
    }
  }
  if(numAttack==1){
  	for(int i = 12; i>=0; i--){
    	showMeteor(i, 0);
    	delay(delayLevel);
    }
  }
  if(numAttack==2){
    for(int i = 12; i>=-6; i--){
      showMeteor(i, 0);
      if(i<=11)
      showMeteor(i+1, 0);
      if(i<=10)
      showMeteor(i+2, 0);
      if(i<=7)
      showMeteor(i+5, 1);
      delay(delayLevel);
    }
  }
  if(numAttack==3){
    for(int i = 12; i>=-4; i--){
    	showMeteor(i, 0);
    	if(i<=9)   
    	showMeteor(i+3, 1);
    	delay(delayLevel);
    }
  }
  if(numAttack==4){
    for(int i = 12; i>=-6; i--){
    	showMeteor(i, 0);
    	if(i<=9)   
    	showMeteor(i+3, 1);
        if(i<=6)   
    	showMeteor(i+6, 0);
    	delay(delayLevel);
    }
  }
    if(numAttack==5){
      for(int i = 12; i>=-10; i--){
    		showMeteor(i, 0);
    	if(i<=9)   
    		showMeteor(i+3, 1);
        if(i<=6)   
    		showMeteor(i+6, 0);
        if(i<=3)
    		showMeteor(i+9, 1);
        
        
    	delay(delayLevel); 
      }
  }
  
     if(numAttack==6&&life<3){
     	for(int i = 12; i>=0; i--){
          if(life_increased==false)
          	showHeart(i,0);
          delay(delayLevel);
        }
     }
  	  if(numAttack==7){
    	for(int i = 12; i>=-4; i--){
    		showMeteor(i, 0);
            if(i<=11 && life_increased==false)
          		showHeart(i+1,0);
    		if(i<=9)   
    		showMeteor(i+3, 1);
    		delay(delayLevel);
       }
    }
      if(numAttack==8){
      	for(int i = 12; i>=-10; i--){
    		showMeteor(i, 0);
    		if(i<=9)   
    		showMeteor(i+3, 1);
        	if(i<=6)   
    		showMeteor(i+6, 0);
        	if(i<=5 && life_increased==false)
          	showHeart(i+7,0);
        	if(i<=3)
    		showMeteor(i+9, 1);
            delay(delayLevel); 
        }
      }
    	
      
        
       
  
  lcd.setCursor(0,0);
  lcd.print(" ");
}

void showMeteor(int col, int row){
	lcd.setCursor(col,row);
    lcd.write((byte)METEOR_CHAR);
    if((col+1)!=13){
    	lcd.setCursor(col+1,row);
    	lcd.print(" ");
  	}
    if(col==1)colide=true; 
  	if(col==1&&position_astro==row){
       colide=false;
       lifeDecrease();
  	}
    if(col==0&&colide==false);
  	else if(col==0&&colide==true){
    	colide=false;
    	scoreIncrease();
  }
}

void showHeart(int col, int row){
	lcd.setCursor(col,row);
    lcd.write((byte)LIFE_BONUS);
    if((col+1)!=13){
    	lcd.setCursor(col+1,row);
    	lcd.print(" ");
  	}
    if(col==1)colide_heart=true; 
  	if(col==1&&position_astro==row){
       colide_heart=false;
       lifeIncrease();
       drawAstro();
  	}
}

void lifeDecrease(){
	life--;
    lcd.setCursor(13,1);
    lcd.print(life);
  if(life==0){
    delay(50);
    endgame();
  }
}
void lifeIncrease(){
    life++;
    lcd.setCursor(13,1);
    lcd.print(life);
    life_increased = true;
}

void scoreIncrease(){
	score++;
    levelIncrease();
  	lcd.setCursor(13,0);
    lcd.print(score);
}

void levelIncrease(){
   level++;
   calcDelay();
}

void calcDelay(){
  if(delayLevel<=100)
    delayLevel = 100;  
  else delayLevel -= level;
  
}
