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
String ac ="";
void setup()
{
  pinMode(Buse, OUTPUT);
  pinMode(Gasport, OUTPUT);
  pinMode(fanpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  Serial.begin(9600);
  myDHT.begin();
  bt.begin(38400);
  bt.print("\r\n+STWMOD=0\r\n");  
  bt.print("\r\n+STNA=SeeedBTSlave\r\n");
  bt.print("\r\n+STOAUT=1\r\n");
  bt.print("\r\n+STAUTO=0\r\n");    
  delay(2000);
  bt.print("\r\n+INQ=1\r\n");
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); 
  bt.flush();
  delay(2000);
  
}

void loop()
{
  //함수부분
  float tempa = myDHT.readTemperature();
  float Humia = myDHT.readHumidity();
  float gas = analogRead(Gasport);
  int light = analogRead(lightport);
  if (bt.available()){
    String c = bt.readStringUntil(0x0A);
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
    if (c == "fanoffledon"|| c=="fanoffledoff"){
      digitalWrite(fanpin, LOW);
      Serial.println("fanpinoff");
    }
    else if(c =="fanonledon"|| c=="fanonledoff"){
      digitalWrite(fanpin, HIGH);
      Serial.println("fanpinon");
    }
    if (c == "fanonledoff"|| c=="fanoffledoff"){
      digitalWrite(ledpin1, LOW);
      Serial.println("ledoff");
    }
    else if(c =="fanonledon" || c=="fanoffledon"){
      digitalWrite(ledpin1, HIGH);
      Serial.println("ledon");
    }
    delay(1000);
    Serial.println(light);
  }
}
