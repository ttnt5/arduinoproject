#include <SoftwareSerial.h>
#include <DHT.h>
#define Buse 2
#define fanpin 3
#define ledpin1 5
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
  //함수부분
  float tempa = myDHT.readTemperature();
  float Humia = myDHT.readHumidity();
  float gas = analogRead(Gasport);
  int light = analogRead(lightport);

  if (bt.available()){
    char c = bt.read();

    bt.print("Value" + String(tempa));
    bt.print(String(Humia));

    //가스 부저부분
    if (gas <50){
      bt.print("정상");
    }
    if (gas >50){
      bt.print("위험");
      digitalWrite(Buse, HIGH);
      delay(100);
      digitalWrite(Buse, LOW);
    }

    //팬관련 
    if (tempa < 26 ||Humia < 60 || gas < 50){
      bt.print("4");
    }
    else{
      bt.print("5");
    }

    //LED관련
    if (light < 10){
      bt.print("2");
    }
    else{
      bt.print("3");
    }
    //블루투스수신후 동작제어(팬, LED)
    if (c == '0'){
      digitalWrite(fanpin, LOW);
    }
    else if(c =='1'){
      digitalWrite(fanpin, HIGH);
    }
    if (c == '2'){
      digitalWrite(ledpin1, LOW);
    }
    else if(c =='3'){
      digitalWrite(ledpin1, HIGH);
    }
    delay(1000);
  }
    
  //Serial.println("온도" + String(tempa));
  //Serial.println("습도" + String(Humia));
  //Serial.println("가스" + String(gas));
 // Serial.println("조도값" + String(light));
}
