#include <Arduino.h>
#include <Wire.h> // Include Wire.h - Arduino I2C library
#include <SparkFunMLX90614.h> // Include IR thermometer library

IRTherm temp; // Create an IRTherm object called temp

// put function declarations here:

//void setup();
//void loop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Initialize Serial to log output
  Wire.begin(); //Joing I2C bus

  while (temp.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Qwiic IR thermometer did not acknowledge! Freezing!");
  }
  Serial.println("Qwiic IR Thermometer did acknowledge.");
  
  temp.setUnit(TEMP_F); // Set the library's units to Fahrenheit
  // Alternatively, TEMP_F can be replaced with TEMP_C for Celsius or
  // TEMP_K for Kelvin.
  
  pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
    
  //call temp.read() to read object and ambient temperatures from the sensor.
  if (temp.read()) // On success, read() will return 1, on fail 0.
  {
	//floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(temp.object(), 2));
    Serial.println("F");
    Serial.print("Ambient: " + String(temp.ambient(), 2));
    Serial.println("F");
    Serial.println();
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

