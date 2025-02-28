# csv for multiple sensors

import serial
import csv
import time

# Set up the serial connection
SERIAL_PORT = 'COM6'  # Update as needed
BAUD_RATE = 115200
OUTPUT_CSV = 'temp_data_example.csv'

def extract_float(value):
    try:
        # Clean up value and convert to float
        return float(value.replace(" F", "").strip())
    except ValueError:
        print(f"WARNING: Could not convert '{value}' to float.")
        return None

def safe_extract(line, keyword):
    # trying to extract temperature data and handle invalid formats.
    if keyword in line:
        parts = line.split(":", 1)
        if len(parts) > 1:
            return extract_float(parts[1])
    print(f"WARNING: Unexpected format for {keyword}: {line}")
    return None

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
                        # Read Sensor-1 Data
                        line = ser.readline().decode('utf-8').strip()
                        print(f"DEBUG: Sensor-1 Header: {line}")
                        if "Sensor-1" in line:
                            # Process Sensor-1 lines
                            line = ser.readline().decode('utf-8').strip()
                            emissivity_5A = safe_extract(line, "Emissivity")

                            # Read object and ambient temperatures for Sensor-1
                            line = ser.readline().decode('utf-8').strip()
                            object_5A = safe_extract(line, "Object Temp 0x5A")

                            line = ser.readline().decode('utf-8').strip()
                            ambient_5A = safe_extract(line, "Ambient Temp 0x5A")

                            # Skip empty lines if any
                            ser.readline().decode('utf-8').strip()

                        # Read Sensor-2 Data
                        line = ser.readline().decode('utf-8').strip()
                        print(f"DEBUG: Sensor-2 Header: {line}")
                        if "Sensor-2" in line:
                            # Process Sensor-2 lines
                            line = ser.readline().decode('utf-8').strip()
                            emissivity_5B = safe_extract(line, "Emissivity")

                            # Read object and ambient temperatures for Sensor-2
                            line = ser.readline().decode('utf-8').strip()
                            object_5B = safe_extract(line, "Object Temp 0x5B")

                            line = ser.readline().decode('utf-8').strip()
                            ambient_5B = safe_extract(line, "Ambient Temp 0x5B")

                        # Ensure all values are valid before writing to CSV
                        if None in [emissivity_5A, object_5A, ambient_5A, emissivity_5B, object_5B, ambient_5B]:
                            print("WARNING: Skipping invalid data row.")
                            continue
                        
                        # Write to CSV
                        timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                        writer.writerow([timestamp, emissivity_5A, object_5A, ambient_5A, object_5B, ambient_5B])
                        file.flush()
                        
                        # Print data to console
                        print(f"{timestamp} | Sensor-1 | Emissivity: {emissivity_5A}, Object 0x5A: {object_5A}F, Ambient 0x5A: {ambient_5A}F")
                        print(f"{timestamp} | Sensor-2 | Emissivity: {emissivity_5B}, Object 0x5B: {object_5B}F, Ambient 0x5B: {ambient_5B}F")
                    
                    except ValueError as e:
                        print(f"ERROR: ValueError encountered - {e}")
                        continue  # Skip invalid data
                    except KeyboardInterrupt:
                        print("\nLogging stopped by user.")
                        break
    
    except serial.SerialException as e:
        print(f"Serial error: {e}")

if __name__ == "__main__":
    main()
