// Library Files
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <dht.h>

// LCD Display
//#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
//LiquidCrystal lcd(6, 5, 4, 3, 2, 1); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Temperature
#define datapin 10     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(datapin, DHTTYPE);
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

////Motion Sensor
//int Buzzerpin = 8;// Digital pin n D6 buzzer
int pir1;
//int LedPin3 = 9; 
int sensor1 = 13 ;//motion senson1 on D7

//Gas Sensor
const int smoke = A0;
int Buzzerpin = 8;// Digital pin n D6 buzzer
const int exFan = 9; //exFan
const int threshold = 1000;//gas sensor

//Vibration sensor

int vibration = A8; //vibration sensor D0
int LedPin3 = 9; //vibration in led D1 LED

//dust sensor
int measurePin = A15;
int ledPower = 52;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup() {

  //Motion
//  pinMode(sensor1, INPUT);   // declare sensor as input
//  pinMode(Buzzerpin, OUTPUT);  // declare LED as output

  //gas sensor
  pinMode(smoke, INPUT);
  pinMode(exFan, OUTPUT); //Buzzpin for fire alarm

  //temperature
  dht.begin();

  //Vibration
  pinMode (vibration, INPUT);
  pinMode(LedPin3, OUTPUT);

  //Display
  lcd.begin(16, 2);
  lcd.print("Smart Industry");
  Serial.begin(9600);
}

void loop() {
  gasSensor();
  temperature();
  vibration_sensor();
  motionDetected1();
  lcd.clear();
  lcd.println(temp);
}

                                                                              //Vibration
void vibration_sensor() {
  int vibrationvalue = analogRead(vibration);
  Serial.println("\n Vibration value is");
  Serial.println(vibrationvalue);

  if (vibrationvalue > 1000 ) {
    digitalWrite(LedPin3, HIGH);
    Serial.println("\n Vibration");
    delay(1000);
  }

  else {
    digitalWrite(LedPin3, LOW);
    Serial.println("\n No Vibration");
    delay(1000);
  }
  //  delay(500);
}


                                                         //temperature
void temperature() {

  /* Find Temperature & Humidity */
  float air_temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  /* Print Output on LCD Screen */
  lcd.setCursor(0,0);
  lcd.print(String("Temp. ") + String(air_temp));
  lcd.setCursor(0,1);
  lcd.print(String("Humidity ") + String(humidity));
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temp: ");
  Serial.print(air_temp);
  Serial.println(" Celsius");

  delay(2000);

}
//void temperature() {
//  delay(1000);
//  //Read data and store it to variables hum and temp
//  hum = dht.readHumidity();
//  temp = dht.readTemperature();
//  Serial.print("Humidity: ");
//  Serial.print(hum);
//  Serial.print(" %, Temp: ");
//  Serial.print(temp);
//  Serial.println(" Celsius");
//  delay(1000);
//}
//#define dataPin 11 // Defines pin number to which the sensor is connected

//
//void temperature() {
//  //Uncomment whatever type you're using!
//  int readData = dht.read22(dataPin); // DHT22/AM2302
//  int readData = dht.read11(dataPin); // DHT11
//
// float hum = dht.readHumidity();
// float temp = dht.readTemperature();
//
//  // Printing the results on the serial monitor
//  Serial.print("Temperature = ");
//  Serial.print(temp);
//  Serial.print(" ");
//  Serial.print((char)176);//shows degrees character
//  Serial.print("C | ");
//  Serial.print((temp * 9.0) / 5.0 + 32.0);//print the temperature in Fahrenheit
//  Serial.print(" ");
//  Serial.print((char)176);//shows degrees character
//  Serial.println("F ");
//  Serial.print("Humidity = ");
//  Serial.print(hum);
//  Serial.println(" % ");
//  Serial.println("");
//
//  delay(2000); // Delays 2 secods
//}
                                                                                          //Motion Sensor Detection
void motionDetected1() {
  pir1 = digitalRead (sensor1);
    Serial.println(pir1);

  if (pir1 == HIGH) {
    digitalWrite(LedPin3, HIGH);
    Serial.println("\n Motion Detected");
     Serial.println(pir1);
    delay(50);
    digitalWrite(LedPin3, LOW);

  }
  else {
    digitalWrite(LedPin3, LOW);
    Serial.println(" Motion Not Detected");
    Serial.println(pir1);
    delay(50);
  }
}

                                                                //gas sensor
void gasSensor() {
  int analogValue = analogRead(smoke);

  Serial.println("\n Gas value = ");
  Serial.println(analogValue);

  if (analogValue > threshold) {
    digitalWrite(exFan, HIGH);
    digitalWrite(Buzzerpin, HIGH);
    delay(1000);
    digitalWrite(Buzzerpin, LOW);
    delay(5000);

  }
  else if (analogValue == threshold) {
    digitalWrite(exFan, LOW);
    delay(400);
    //digitalWrite(Buzzerpin, LOW);
  }
  else {
    digitalWrite(exFan, LOW);
  }

  //  Serial.println(analogRead(A0));
  delay(500);
}
