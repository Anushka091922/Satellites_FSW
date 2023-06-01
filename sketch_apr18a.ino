#include <Wire.h>  // Include the Wire library for I2C communication
#include <Adafruit_BMP280.h>  // Include the BMP280 library

Adafruit_BMP280 bmp;  // Create an instance of the BMP280 library

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  Wire.begin();  // Initialize the I2C bus
  bmp.begin(0x76);  // Initialize the BMP280 sensor with the I2C address 0x76
}

void loop() {
  float temperature = bmp.readTemperature();  // Read the temperature data from the sensor
  float pressure = bmp.readPressure() / 100.0;  // Read the pressure data from the sensor and convert it to hPa

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(1000);  // Wait for 1 second before taking the next reading
}
