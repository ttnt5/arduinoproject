#include <SoftwareSerial.h>
#include <DHT.h>
#define RxD 6
#define TxD 7
#define DHTport A0
#define Gasport A2
#define Buse 2

DHT myDHT(DHTport,DHT11);
SoftwareSerial bt(RxD,TxD);

void setup()
{
  pinMode(Buse, OUTPUT);
  Serial.begin(9600);
  pinMode(Gasport, OUTPUT);
  bt.begin(38400);
  myDHT.begin();
  bt.print("\r\n+STWMOD=0\r\n");  
  delay(2000);
  bt.print("\r\n+INQ=1\r\n");
  delay(2000); 
  bt.flush();
}

void loop()
{
  float tempa = myDHT.readTemperature();
  float Humia = myDHT.readHumidity();
  int gas = analogRead(Gasport);
  
  bt.print("Value" + String(tempa));
  bt.print(String(Humia));
  if (gas <50){
    bt.print("정상");
  }
  if (gas >50){
    bt.print("위험");
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
  }
  
  //Serial.println("온도" + String(tempa));
  //Serial.println("습도" + String(Humia));
  //Serial.println("가스" + String(gas));
  delay(1000);
}
