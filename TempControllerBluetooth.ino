#include <SoftwareSerial.h>

#include <LiquidCrystal.h>

#include <math.h>
LiquidCrystal lcd(7,6,5,4,3,2); 
int rele = 8;
int releDefrost = 9;
 SoftwareSerial miBT(10, 11);
 char NOMBRE[21] = "DEIVID";
 char BPS = '4';
 char PASS[5] = "0000";                 // set contraseña
void setup() 
{     
 Serial.begin(9600);     
 Serial.println("listo");                               // inicializa
 miBT.begin(9600);
   pinMode(8, OUTPUT);
  digitalWrite(rele, LOW);
   pinMode(9, OUTPUT);
  digitalWrite(rele, LOW);
  lcd.begin(16, 2); 
  miBT.print("AT");
  delay(1000);
  miBT.print(NOMBRE);
  delay(1000);
  miBT.print("AT+BAUD");
  miBT.print(BPS);
  delay(1000);
  miBT.print("AT+PIN");
  miBT.print(PASS);
  delay(1000);
  
} 

void loop() 
{           
  if (miBT.available()) 
    Serial.write(miBT.read());
  if (Serial.available()) 
  miBT.write(Serial.read());
    lcd.setCursor(0,0);
  int val;
  double temp;
  val = analogRead(0);                              // asigna valores de lectura del termometro digital a una variable "temp"
  temp = log(((10240000/val) - 10000));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;
  Serial.print(temp);                               // imprime temperatura
  Serial.println("°C");
  lcd.print(temp);
  lcd.setCursor(6, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("TEMPERATURA");
  delay(1000);
  
if(temp < 27) {
  digitalWrite(rele, LOW);                        // apaga relay cuando temperatura sea menor que 27° 
  delay(1000);
}
else {
  digitalWrite(rele, HIGH);                         // enciende relay haste que la temperatura sea menor a 27°
  delay(1000);
}
  
}
