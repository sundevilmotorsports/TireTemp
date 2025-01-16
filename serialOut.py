#this one works
import serial
import csv
import time

# Set up the serial connection
SERIAL_PORT = 'COM6'  # Might need to change port
BAUD_RATE = 115200
OUTPUT_CSV = 'datatemp.csv'

def main():
    try:
        # Open the serial port
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            
            # Open the CSV file for writing
            with open(OUTPUT_CSV, mode='w', newline='') as file:
                writer = csv.writer(file)
                # Write CSV headers
                writer.writerow(["Timestamp", "Object Temperature (F)", "Ambient Temperature (F)", "Emissivity"])
                
                while True:
                    try:
                        # Read a line from the serial output
                        line = ser.readline().decode('utf-8').strip()
                        
                        if line.startswith("Object:"):
                            # Extract Object temperature
                            object_temp = int(float(line.split(":")[1].replace("F", "").strip()))
                            
                            # Read the next line for Ambient temperature
                            line = ser.readline().decode('utf-8').strip()
                            if line.startswith("Ambient:"):
                                ambient_temp = int(float(line.split(":")[1].replace("F", "").strip()))
                            else:
                                continue  # Skip if the format is not as expected
                            
                            # Read the next line for Emissivity
                            ser.readline()  # Skip empty line
                            line = ser.readline().decode('utf-8').strip()
                            if line.startswith("Emissivity:"):
                                emissivity = float(line.split(":")[1].strip())
                            else:
                                continue  # Skip if the format is not as expected
                            
                            # Write to CSV
                            timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                            writer.writerow([timestamp, object_temp, ambient_temp, emissivity])
                            print(f"{timestamp} | Object Temp: {object_temp}F, Ambient Temp: {ambient_temp}F, Emissivity: {emissivity}")
                    
                    except ValueError:
                        # Skip problematic data
                        continue
                    except KeyboardInterrupt:
                        # Graceful exit on user interrupt
                        print("\nLogging stopped by user.")
                        break
                    
    except serial.SerialException as e:
        print(f"Serial error: {e}")


if __name__ == "__main__":
    main()


'''
import serial
import csv
import time

# Set up the serial connection
SERIAL_PORT = 'COM6'  #Might need to change port
BAUD_RATE = 115200
OUTPUT_CSV = 'data3.csv'


def main():
    try:
        # Open the serial port
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
            
            # Open the CSV file for writing
            with open(OUTPUT_CSV, mode='w', newline='') as file:
                writer = csv.writer(file)
                # Write CSV headers
                writer.writerow(["Timestamp", "Object Temperature (F)", "Ambient Temperature (F)", "Emissivity"])
                
                while True:
                    try:
                        # Read a line from the serial output
                        line = ser.readline().decode('utf-8').strip()
                        
                        if line.startswith("Object:"):
                            # Extract Object temperature
                            object_temp = (line.split(":")[1].replace("F", "").strip())
                            
                            # Read the next line for Ambient temperature
                            line = ser.readline().decode('utf-8').strip()
                            ambient_temp = (line.split)
                            # Read the next line for Emissivity
                            ser.readline()  # Skip empty line?  
                            line = ser.readline().decode('utf-8').strip()
                            emissivity = (line.split(":")[1].strip())
                            
                            # Write to CSV
                            timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
                            writer.writerow([timestamp, object_temp, ambient_temp, emissivity])
                    
                    except ValueError:
                        # Skips problematic data
                        continue
                    except KeyboardInterrupt:
                        # exita on user interrupt
                        break
                    
    except serial.SerialException as e:
        print(f"Serial error: {e}")

if __name__ == "__main__":
    main()
'''