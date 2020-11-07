
/****************************************************************************************
 *  Code is based on Blynk USB-Serial Example
 *  Make sure you go to C:\Users\Your Username\Documents\Arduino\libraries\Blynk\scripts
 *  Press CTRL + LMouse Button and select Open Command Windows Here
 *  Then type in command windws >> blynk-ser.bat -c COM2 and click enter
 *  Enjoy the Virtual IoT !!!
 ****************************************************************************************/
#define BLYNK_PRINT SwSerial

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>
#include <DHT.h>

int pirPin = 5;

// Pin Assignments
int redPin=8,greenPin=9,bluePin=12; 

//Your app authentication token (can be fetched from your blynk app
char auth[] = "R0HnU_jFM_B_wlmPjaGot9hNoVGzOLwM";

#define DHTPIN 3          // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    SwSerial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}

void setup()
{
  //Set the three LED pins as output
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  
  // Debug console
  SwSerial.begin(9600);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
  dht.begin();
  pinMode(pirPin, INPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  // All the magic is here
  Blynk.run();
  timer.run();

  int pirValue = digitalRead(pirPin);
  if(pirValue==HIGH){
    Blynk.notify("Motion Detected");
    delay(1000);
  }
  if(pirValue==LOW){
    delay(1000);
  }
}
