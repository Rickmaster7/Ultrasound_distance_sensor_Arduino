/*velocità suono a 20C: 343,4 m/s
  V = 331,4 + 0.62 T (T = tmp in C)
  S=V*t
  S=0.0343cm * t
  S=0.0343 * t/2 il suono percorre due volte il percorso
  S=0.01715 * t
  S=t/58.31
*/
#include <LiquidCrystal.h>
const int rs = 11, e = 10, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(rs, e, D4, D5, D6, D7);

const int trigPin = 12;
const int echoPin = 13;
const int tmpPin = A0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //colonne, righe
  //lcd.print("distanza:");
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long durata, distanza;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durata = pulseIn(echoPin, HIGH);

  int sensorVal = analogRead(tmpPin);
  float voltage = (sensorVal/1024.0) * 5;
  float temperatura = (voltage - .5) * 100;

  distanza = durata / 29.1 / 2; //si divide per 2 perché il suono colpisce oggetto e torna

  if (distanza<=0){
    Serial.println("Out of range");
    lcd.setCursor(0, 0);
    lcd.print("Out of range");
  }
  else{
    Serial.print(distanza);
    Serial.println("cm");
    Serial.println();
    lcd.setCursor(0, 0);
    lcd.print("distanza: ");
    lcd.print(distanza);
    lcd.print("cm    ");
    lcd.setCursor(0, 1);
    lcd.print("temp: ");
    lcd.print(temperatura);
    lcd.print("C   ");
   }
  delay(1000);
  }
