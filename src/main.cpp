#include <Wire.h>
#include <Arduino.h>

#define AHT21B_ADDRESS 0x38 // I2C address of AHT21B sensor

void setup()
{
  Serial.begin(115200);
  Wire.begin();
}

void loop()
{
  // Start a measurement
  Wire.beginTransmission(AHT21B_ADDRESS);
  Wire.write(0xAC); // Send measurement command
  Wire.write(0x33); // Trigger a humidity and temperature measurement
  Wire.endTransmission();

  delay(100); // Wait for measurement to complete (adjust if necessary)

  // Request data from the sensor
  Wire.beginTransmission(AHT21B_ADDRESS);
  Wire.write(0x00); // Send data request command
  Wire.endTransmission();

  // Read the data from the sensor
  Wire.requestFrom(AHT21B_ADDRESS, 6);
  if (Wire.available() == 6)
  {
    uint8_t data[6];
    for (int i = 0; i < 6; i++)
    {
      data[i] = Wire.read();
    }

    // Convert the data to temperature and humidity values
    int32_t rawHumidity = ((int32_t)data[1] << 12) | ((int32_t)data[2] << 4) | ((int32_t)data[3] >> 4);
    int32_t rawTemperature = ((int32_t)data[3] & 0x0F) | ((int32_t)data[4] << 4) | ((int32_t)data[5] << 12);

    float humidity = (float)rawHumidity * 100 / 0x100000;
    float temperature = (float)rawTemperature * 200 / 0x100000 - 50;

    // Display the temperature and humidity values in the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  else
  {
    Serial.println("Error: Failed to read data from AHT21B sensor!");
  }

  delay(5000); // Wait for 5 seconds before taking the next measurement
}
