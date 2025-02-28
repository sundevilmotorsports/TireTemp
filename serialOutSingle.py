# csv data for single sensor

import serial
import csv
import time

# Set up the serial connection
SERIAL_PORT = 'COM6'  # Update as needed
BAUD_RATE = 115200
OUTPUT_CSV = 'datatemp.csv'

def main():
    print("Starting dual-sensor data logging...")
    try:
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            with open(OUTPUT_CSV, mode='w', newline='') as file:
                writer = csv.writer(file)
                # Write CSV headers
                writer.writerow(["Timestamp", "Emissivity", "Object 0x5A Temp (F)", "Ambient 0x5A Temp (F)", "Object 0x5B Temp (F)", "Ambient 0x5B Temp (F)"])
                file.flush()
                
                while True:
                    try:
                        # Read and validate Sensor-1
                        line = ser.readline().decode('utf-8').strip()
                        if not line.startswith("Sensor-1"):
                            continue
                        ser.readline()  # Skip address line
                        
                        # Read Emissivity
                        emissivity_line = ser.readline().decode('utf-8').strip()
                        if ":" not in emissivity_line:
                            continue
                        emissivity = float(emissivity_line.split(":")[1].strip())
                        
                        # Read Object and Ambient Temps for Sensor-1
                        object_5A = float(ser.readline().decode('utf-8').split(":")[1].replace("F", "").strip())
                        ambient_5A = float(ser.readline().decode('utf-8').split(":")[1].replace("F", "").strip())
                        
                        ser.readline()  # Skip empty line
                        
                        # Read and validate Sensor-2
                        line = ser.readline().decode('utf-8').strip()
                        if not line.startswith("Sensor-2"):
                            continue
                        ser.readline()  # Skip address line
                        ser.readline()  # Skip emissivity line
                        
                        # Read Object and Ambient Temps for Sensor-2
                        object_5B = float(ser.readline().decode('utf-8').split(":")[1].replace("F", "").strip())
                        ambient_5B = float(ser.readline().decode('utf-8').split(":")[1].replace("F", "").strip())
                        
                        # Write to CSV
                        timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                        writer.writerow([timestamp, emissivity, object_5A, ambient_5A, object_5B, ambient_5B])
                        file.flush()
                        
                        # Print data to console
                        print(f"{timestamp} | Emissivity: {emissivity}, Object 0x5A: {object_5A}F, Ambient 0x5A: {ambient_5A}F, Object 0x5B: {object_5B}F, Ambient 0x5B: {ambient_5B}F")
                    
                    except ValueError:
                        continue  # Skip invalid data
                    except KeyboardInterrupt:
                        print("\nLogging stopped by user.")
                        break
    
    except serial.SerialException as e:
        print(f"Serial error: {e}")

if __name__ == "__main__":
    main()
