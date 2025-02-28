#include <Arduino.h>
#include <Wire.h> //include Wire.h - Arduino I2C library
#include <SparkFunMLX90614.h> //include IR thermometer library

//object called temp
IRTherm sensor;
//IRTherm sensor2;

const byte addr1 = 0x5A;
const byte addr2 = 0x5B;


// put function declarations here:
// void setup();
// void loop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //initialize Serial to log output
  //Serial.println("before");
  Wire.begin(); //join I2C bus

  //Serial.println("First ID: " + sensor.readID());
  

 // while(!Serial);
  if (!sensor.begin(addr1)) {
    Serial.println("Sensor-1 did not acknowledge.");
  }  
  Serial.println("Sensor-1 initialized.");

  if (!sensor.begin(addr2)) {
    Serial.println("Sensor-2 did not acknowledge.");
  }
  Serial.println("Sensor-2 initialized.");

  //setting units for both sensors
  sensor.setUnit(TEMP_F);
  //TEMP_C for celsius
  //TEMP_K for kelvin
  
  // sensor.setEmissivity(0.55);
  pinMode(LED_BUILTIN, OUTPUT); //LED pin as output
}

void readSensor(byte address) {
  
  if (!sensor.begin(address)) {
    Serial.print("Sensor at address 0x");
    Serial.print(address, HEX);
    Serial.println(" not responding.");
    return;
  }

  if (sensor.read()) {

    Serial.print("at address 0x");
    Serial.println(address, HEX);

    Serial.print("Emissivity: ");
    Serial.println(sensor.readEmissivity(), 3);

    Serial.print("Object Temp 0x");
    Serial.print(address, HEX);
    Serial.print(": ");
    Serial.print(sensor.object(), 2);
    Serial.println(" F");

    Serial.print("Ambient Temp 0x");
    Serial.print(address, HEX);
    Serial.print(": ");
    Serial.print(sensor.ambient(), 2);
    Serial.println(" F");
    
  } else {
    Serial.print("Failed to read - address 0x");
    Serial.println(address, HEX);
  }
  Serial.println();
}

void loop() {
  //Serial.println("Looping");

  //main code here to keep running:
  digitalWrite(LED_BUILTIN, HIGH);
  
  // Read sensors
  Serial.print("Sensor-1 ");
  readSensor(addr1);
  Serial.print("Sensor-2 ");
  readSensor(addr2); 
  Serial.println(" ");

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); //delaying by a second
}

//============================================================================================================================

// #include <Arduino.h>
// #include <Wire.h> // Include Wire.h - Arduino I2C library
// #include <SparkFunMLX90614.h> // Include IR thermometer library
// #include <SPI.h>
// #include <SD.h>

// // Object called temp
// IRTherm sensor;

// const byte addr1 = 0x5A;
// const byte addr2 = 0x5B;

// #define SD_CS 10  // Chip Select pin for SD card module

// File dataFile;

// void setup() {
//     Serial.begin(115200); // Initialize Serial for logging
//     Wire.begin(); // Join I2C bus

//     // Initialize SD card
//     if (!SD.begin(SD_CS)) {
//         Serial.println("SD Card initialization failed!");
//         return;
//     }
//     Serial.println("SD Card initialized.");

//     // Open file and write header if needed
//     dataFile = SD.open("sensor_data.txt", FILE_WRITE);
//     if (dataFile) {
//         dataFile.println("Timestamp, Address, Emissivity, Object Temp (F), Ambient Temp (F)");
//         dataFile.close();
//     } else {
//         Serial.println("Error opening file!");
//     }

//     // Initialize sensors
//     if (!sensor.begin(addr1)) {
//         Serial.println("Sensor-1 did not acknowledge.");
//     }  
//     Serial.println("Sensor-1 initialized.");

//     if (!sensor.begin(addr2)) {
//         Serial.println("Sensor-2 did not acknowledge.");
//     }
//     Serial.println("Sensor-2 initialized.");

//     // Set temperature units
//     sensor.setUnit(TEMP_F); // TEMP_C for Celsius, TEMP_K for Kelvin
    
//     pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
// }

// void readAndLogSensor(byte address) {
//     if (!sensor.begin(address)) {
//         Serial.print("Sensor at address 0x");
//         Serial.print(address, HEX);
//         Serial.println(" not responding.");
//         return;
//     }

//     if (sensor.read()) {
//         // Read sensor data
//         float emissivity = sensor.readEmissivity();
//         float objTemp = sensor.object();
//         float ambTemp = sensor.ambient();

//         // Print to Serial Monitor
//         Serial.print("Sensor at address 0x");
//         Serial.println(address, HEX);
//         Serial.print("Emissivity: ");
//         Serial.println(emissivity, 3);
//         Serial.print("Object Temp 0x");
//         Serial.print(address, HEX);
//         Serial.print(": ");
//         Serial.print(objTemp, 2);
//         Serial.println(" F");
//         Serial.print("Ambient Temp 0x");
//         Serial.print(address, HEX);
//         Serial.print(": ");
//         Serial.print(ambTemp, 2);
//         Serial.println(" F");
//         Serial.println();

//         // Write to SD card
//         dataFile = SD.open("sensor_data.txt", FILE_WRITE);
//         if (dataFile) {
//             dataFile.print(millis());  // Timestamp
//             dataFile.print(", 0x");
//             dataFile.print(address, HEX);
//             dataFile.print(", ");
//             dataFile.print(emissivity, 3);
//             dataFile.print(", ");
//             dataFile.print(objTemp, 2);
//             dataFile.print(", ");
//             dataFile.println(ambTemp, 2);
//             dataFile.close();
//         } else {
//             Serial.println("Failed to open file.");
//         }

//     } else {
//         Serial.print("Failed to read - address 0x");
//         Serial.println(address, HEX);
//     }
// }

// void loop() {
//     digitalWrite(LED_BUILTIN, HIGH);
    
//     // Read and log sensor data
//     Serial.print("Reading Sensor-1...\n");
//     readAndLogSensor(addr1);
//     Serial.print("Reading Sensor-2...\n");
//     readAndLogSensor(addr2);
//     Serial.println(" ");

//     digitalWrite(LED_BUILTIN, LOW);
//     delay(1000); // Delay by a second
// }



// =================================================================


//===============================================================================

// #include <Arduino.h>
// #include <Wire.h> // Include Wire.h - Arduino I2C library
// #include <SparkFunMLX90614.h> 
// #include <Arduino.h>
// #include <Wire.h>  // Include Wire.h - Arduino I2C library
// #include <SparkFunMLX90614.h>
// #include <SPI.h>
// #include <SD.h>

// File myFile;
// const int chipSelect = 10;  // Change if needed

// void setup() {
//   Serial.begin(115200);
//    // while (!Serial);  // Wait for Serial (but don’t return)
  
//   Serial.println("Setup started...");  // Debug message 1
//   delay(1000);

//   Serial.println("Initializing SD card...");
//   if (!SD.begin(chipSelect)) {
//     Serial.println("SD Card initialization failed!");
//     return;
//   }
//   Serial.println("SD Card initialized successfully.");
// }

// void loop() {
//   Serial.println("Something should be printing...");
//     // Serial.println("Writing to SD card...");
//   myFile = SD.open("test.txt", FILE_WRITE);

//   if (myFile) {
//     myFile.println("Looping... " + String(millis()));
//     myFile.close();
//     Serial.println("Data written.");
//   } else {
//     Serial.println("Error opening test.txt for writing!");
//   }

//   Serial.println("Reading from SD card...");
//   myFile = SD.open("test.txt");

//   if (myFile) {
//     while (myFile.available()) {
//       Serial.write(myFile.read());  // Print file contents
//     }
//     myFile.close();
//     Serial.println("Read complete.");
//   } else {
//     Serial.println("Error opening test.txt for reading!");
//   }

//   delay(2000);  // Wait 2 seconds before repeating
// }

