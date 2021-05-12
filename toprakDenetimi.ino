#include <DHT.h>
#include <DHT_U.h>
#define DHTTYPE DHT11  
#define DHTPIN 2
#include <SoftwareSerial.h>
SoftwareSerial ESPserial(2,3);


DHT dht(DHTPIN, DHTTYPE);
int mSensor = A1;
int msValue =0;
int led = 13;
const int LDR = A0;
boolean flag = false;


void setup() {
  Serial.begin(115200);
  pinMode(mSensor, INPUT);
  pinMode(led, OUTPUT);
  dht.begin();
}

void loop() {
  int lightValue = analogRead(LDR);
  msValue = analogRead(mSensor);
  int percentage = map(msValue, 0, 1023, 0, 100);
  percentage = 100- percentage;

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //float hif = dht.computeHeatIndex(t, h);
  float hic = dht.computeHeatIndex(t, h, false);

  float dewPoint = (t- (100 - h) / 5);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C || ");
  //Serial.print(f);
  //Serial.print(" *F\t");
  Serial.print("Heat index: "); // Hissedilen sıcaklık denilen olay
  Serial.print(hic);
  Serial.print(" *C || ");
  //Serial.print(hif);
  //Serial.print(" *C");
  Serial.print(" Dew Point: "); // Hissedilen sıcaklık denilen olay
  Serial.print(dewPoint);
  Serial.print(" *C || ");
  
  Serial.print(" Soil Humidity percentage : ");
  Serial.print(percentage);
  Serial.print(" % || ");
  Serial.print(" Light : ");
  Serial.println(lightValue);
  
  if(percentage >=50 && flag ==false){
    digitalWrite(led, LOW);
    flag = true;
    delay(1000);
  }

  if(percentage <=50 && flag ==true){
    digitalWrite(led, HIGH);
    flag = false;
    delay(1000);
  }

  
  delay(1000);
}
