#include <SoftwareSerial.h>
#include <DHT.h>
#define Buse 2
#define fanpin 3
#define ledpin1 4
#define ledpin2 5
#define RxD 6
#define TxD 7
#define DHTport A0
#define lightport A1
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
  int light = analogRead(lightport);

  if (bt.available()){
    char c = bt.read();
    //Serial.println(c);

    bt.print("Value" + String(tempa));
    bt.print(String(Humia));

    //빨간벽램프 (ledpin1)
    if (gas <50){
      bt.print("정상");
      digitalWrite(ledpin1, LOW);
    }
    if (gas >50){
      bt.print("위험");
      digitalWrite(Buse, HIGH);
      digitalWrite(ledpin1, LOW);
      delay(100);
      digitalWrite(Buse, LOW);
      digitalWrite(ledpin1, HIGH);
    }

    //팬관련
    if (tempa > 25 ||Humia > 41 || gas > 50 || c == '0')
    {
      digitalWrite(fanpin, LOW);
      bt.print("0");
    }
    else if (tempa < 25 ||Humia < 41 || gas < 50 || c == '0'){
      digitalWrite(fanpin, HIGH);
      bt.print("1");
    }
    else if (c == '7'){
      digitalWrite(fanpin, HIGH);
      bt.print("1");
    }
    else if (c == '6'){
      digitalWrite(fanpin, LOW);
      bt.print("0");
    }

    //ledpin2 (천장램프)
    if (light > 10 && c=='2'){
      digitalWrite(ledpin2, HIGH);
      bt.print("1");
    }
    else if (light < 10 && c=='2'){
      digitalWrite(ledpin2, LOW);
      bt.print("0");
    }
    else if (c=='5'){
      digitalWrite(ledpin2, HIGH);
      bt.print("1");
    }
    else if (c=='4'){
      digitalWrite(ledpin2, LOW);
      bt.print("0");
    }
  }
  
  
  
  //Serial.println("온도" + String(tempa));
  //Serial.println("습도" + String(Humia));
  //Serial.println("가스" + String(gas));
  //Serial.println("조도값" + String(light));
  delay(1000);
}
