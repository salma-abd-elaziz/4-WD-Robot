#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int x;
int y;
double angle;
RF24 radio(8, 10);

const byte rxAddr[6] = "00003";

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void loop()
{
  x = analogRead(A0);
  y = analogRead(A1);
  x = map(x, 0, 1023, -512, 512);
  y = map(y, 0, 1023, -512, 512);
   if (y < 10 && y > -10) y = 0;
  if (x < 10 && x > -10) x = 0;
  if (x == 0) {
    if (y == 0) angle = 400;
    else if (y < 0) angle = 270;
    else angle = 90;
  }
  else angle = (atan2(y, x) * 180) / 3.14;
  if (angle < 0) angle += 360;
  radio.write(&angle, sizeof(angle));
  Serial.print("angle = ");
  Serial.println(angle);
  delay(1000);
}
