#include <BluetoothSerial.h>
//#include <LinkedList.h>
//#include <Gaussian.h>
//#include <GaussianAverage.h>
#include <analogWrite.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char BT = 'f';
int tempo = 4900;
char estrategia = 'b';
char lupi = '2';

  #define sharpFE 36
  #define sharpFD 39
  //#define sharpFD 34

  #define pwmB 25
  #define b1 33
  #define b2 26
  #define stby 27
  #define a1 14
  #define a2 12
  #define pwmA 13
  //sensor de linha
  #define linhaD 15
  #define linhaE 4
  
  bool direc = true;
  
void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(linhaE, INPUT);
  pinMode(linhaD, INPUT);
  //pinMode(sharpE, INPUT);
  pinMode(sharpFE, INPUT);
  pinMode(sharpFD, INPUT);
  digitalWrite(stby,1);
  
  SerialBT.begin("Valquiria"); //Bluetooth device name
  
  SerialBT.println("LIGOUUUU");
  
  //enquanto serial não receber 0, troca de estretégia é possível
  
  while(BT != '0'){
    
      if(SerialBT.available()) {
          BT = SerialBT.read();
          Serial.print(BT);
      }
      
      if(BT == '+'){
          tempo += 100;
      }else if(BT == '-'){
          tempo -= 100; 
      }else if(BT == '<'){//escolha de direção
          direc = false;        
      }else if(BT == '>'){//escolha de direção
          direc = true;        
      }else if(BT == 'C'){
          SerialBT.println("Check");
          SerialBT.print("Estrategia: ");
          SerialBT.println(estrategia);
          SerialBT.print("Loop: ");
          SerialBT.println(lupi);
          SerialBT.print("Direc: ");
          if(direc) SerialBT.println("direita");
          else SerialBT.println("esquerda"); 
          SerialBT.print("Delay: ");
          SerialBT.println(tempo);  
      }else if(BT == '0') {
        break;
      }else {
          if(!(BT == 13 || BT == 10 || (BT>48 && BT<58))){
              estrategia = BT;
          }
          if(BT>48 && BT<58){
            lupi = BT;
          }
      }
      
  }
  delay(tempo);
  //SerialBT.println("Start");
  //SerialBT.println(lupi);
  //SerialBT.println(estrategia);

  switch (estrategia){
    case 'a': //frentao
      frente(200, 200);
      SerialBT.print("FRENTAAO");
      delay(500);
    break;

    case 'b':  //curvao
      if(direc){
        esquerda(250,250);
        delay(150);
        frente(250, 110);
        delay(1100);
      }
      else{
        direita(250,250);
        delay(120);
        frente(120, 250);
        delay(1000);
      }
      break;
    
  }
}
 
void loop() {

  if(analogRead(sharpFD) > 1200 || analogRead(sharpFE) > 1200){
        frente(250, 250);
    }else{
      direita(100, 100);
      }
   if(analogRead(linhaD) < 70 || analogRead(linhaE) < 70){
      tras(200, 200);
      delay(200);
      esquerda(200, 200);
      delay(200);
    }
      
  }
  /*if(SerialBT.available()){
      BT = SerialBT.read();
      if(BT == 'S') digitalWrite(stby,0);
  }*/




void tras(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void frente(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void esquerda(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
 }
void direita(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }
