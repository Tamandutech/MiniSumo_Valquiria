#include <analogWrite.h>
#define lineC 2
#define lineD 15
#define lineE 4

void setup() {
  pinMode(lineE, INPUT);
  pinMode(lineD, INPUT);
  Serial.begin(9600);
}
int media10(int i){
    int media=0;
    for(int a=0;a<1000;a++){
        media+=analogRead(i);
    }
    return media/1000;
}
 
void loop() {
  Serial.print(media10(lineD));
  Serial.print(" ");
  Serial.print(media10(lineC));
  Serial.print(" ");
  Serial.println(media10(lineE));
  delay(500);
}
