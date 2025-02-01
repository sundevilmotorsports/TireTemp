//works single sensor
#include <Arduino.h>
#include <Wire.h> //include Wire.h - Arduino I2C library
#include <SparkFunMLX90614.h> //include IR thermometer library

IRTherm temp; //create IRTherm object called temp

// put function declarations here:

//void setup();
//void loop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //initialize Serial to log output
  Wire.begin(); //join I2C bus

  while (temp.begin() == false){ //initialize thermal IR sensor
    Serial.println("IR thermometer did not acknowledge! Freezing!");
  }
  Serial.println("IR Thermometer did acknowledge.");
  
  temp.setUnit(TEMP_F); //set to farenheit
  //TEMP_C for celsius
  //TEMP_K for kelvin
  //temp.setEmissivity(0.55);
  pinMode(LED_BUILTIN, OUTPUT); //LED pin as output
}

void loop() {
  //main code here to keep running:
  digitalWrite(LED_BUILTIN, HIGH);
    
  //read object and ambient temperatures from sensor
  if (temp.read()) //on success return 1, on fail return 0
  {
	//floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(temp.object(), 2));
    Serial.println("F");
    Serial.print("Ambient: " + String(temp.ambient(), 2));
    Serial.println("F");
    Serial.println();
    Serial.println("Emissivity: " + String(temp.readEmissivity(),3));
  }
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}