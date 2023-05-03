#include <SoftwareSerial.h>
#include <DHT.h>
#define Buse 2
#define fanpin 3
#define ledpin1 4
#define ledpin2 5
#define RxD 6
#define TxD 7
#define DHTport A0
#define Gasport A2

DHT myDHT(DHTport,DHT11);
SoftwareSerial bt(RxD,TxD);

void setup()
{
  pinMode(Buse, OUTPUT);
  pinMode(Gasport, OUTPUT);
  pinMode(fanpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
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
  float gas = analogRead(Gasport);
  
  bt.print("Value" + String(tempa));
  bt.print(String(Humia));

  if (tempa > 25 ||Humia > 41 || gas > 50)
  {
    digitalWrite(fanpin, LOW);
  }
  else{
    digitalWrite(fanpin, HIGH);
  }

  if (gas <50){
    bt.print("정상");
  }
  if (gas >50){
    bt.print("위험");
    digitalWrite(Buse, HIGH);
    digitalWrite(ledpin1, LOW);
    delay(100);
    digitalWrite(Buse, LOW);
    digitalWrite(ledpin1, HIGH);
  }
  
  //Serial.println("온도" + String(tempa));
  //Serial.println("습도" + String(Humia));
  //Serial.println("가스" + String(gas));
  delay(1000);
}
