#include <SoftwareSerial.h>
#define RxD 6
#define TxD 7

SoftwareSerial bt(RxD,TxD);

void setup()
{
  Serial.begin(9600);
  bt.begin(38400);
  bt.print("\r\n+STWMOD=0\r\n");  
  delay(2000);
  bt.print("\r\n+INQ=1\r\n");
  delay(2000); 
  bt.flush();
}

void loop()
{
}