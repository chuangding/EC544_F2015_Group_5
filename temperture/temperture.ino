#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
int sensorPin = A0;
long Rth;
double Temp;
int i;
double sum;
double sensorVal;

void setup() {
  // put your setup code here, to run once:
  // add
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  i = 0;
  sum = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(A0);
  Rth = ((10240000/sensorVal) - 10000);
  Temp = log(Rth);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  sum += Temp;
  i++;
  //Serial.print("sum:");
  //Serial.println(sum);
  if(i==10){
    Serial.print("D Temp:");
    Serial.println(sum/10);
    XBee.print("D Temp:");
    XBee.println(sum/10);
    i = 0;
    sum = 0;
    delay(10000);
  }
  
  
}

