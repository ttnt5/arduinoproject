#include <SoftwareSerial.h>
#include <DHT.h>
#define RxD 6
#define TxD 7
#define DHTport A0

DHT myDHT(DHTport,DHT11);
SoftwareSerial bt(RxD,TxD);

void setup()
{
  Serial.begin(9600);
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
  bt.print("Value" + String(tempa));
  bt.print(String(Humia));
  //Serial.println("온도" + String(tempa));
  //Serial.println("습도" + String(Humia));
  delay(1000);
}