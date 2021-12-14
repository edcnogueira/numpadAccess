#include <Keypad.h>
#include <LiquidCrystal.h> 
#include <Wire.h>

LiquidCrystal lcd(A5, A4, A0, A1, A2, A3);
bool aut = false;
int aux = 0;
char comp[4];
char senha[4] = {'A','2','B','1'};
int i = 0;
const byte LINHAS = 4;
const byte COLUNAS = 4;
char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinoLinha[LINHAS] = {9,8,10,11};
byte pinoColuna[COLUNAS] = {5,6,3,4};
Keypad keypad = Keypad(makeKeymap(teclas), pinoLinha, pinoColuna, LINHAS, COLUNAS);
int leds = 7;

void setup(){

  pinMode(leds, OUTPUT);
  locked(true);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.print("? - Cartao");
  lcd.setCursor(0,1);
  lcd.print("C - Senha");
  
}
void loop(){
  
  char key2 = keypad.getKey();
  char key = keypad.getKey();
  if(key2 == '*' && aux<1){
    aux++;
    lcd.clear();
    lcd.print("Digite a senha");
    lcd.setCursor(0,1);
    aut = true;
  }
  if(aut == true){
  if(key){
  	lcd.print(key);
    comp[i] = key;
    i++;
    if(i == 4){
      delay(420);
        if(comp[0] == senha[0]&&
          comp[1] == senha[1] &&
          comp[2] == senha[2] &&
          comp[3] == senha[3]){
          locked(false);   
        }
        else
        {
          lcd.clear();
          lcd.print("SENHA INCORRETA");
          delay(3000);
          reset();
        }
  	}
	}
    }
}
void locked(int block){
  if (block){
    digitalWrite(leds, HIGH);
  }
  else{
    digitalWrite(leds, LOW);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("BEM-VINDO!");
    delay(3000);
    digitalWrite(leds, HIGH);
    reset();
  }
}
void reset(){
  	lcd.clear();
    lcd.print("? - Cartao");
  	lcd.setCursor(0,1);
    lcd.print("C - Senha");
    memset(comp,0,4);
    i=0;
  	aut = false;
  	aux = 0;
}