#include <Arduino.h>
void setup()
{
  Serial.begin(115200);     // Set serial monitor speed to 115200 baud
  analogReadResolution(12); // Set ADC resolution to 12 bits (0-4095)
}

void loop()
{
  int sensorValue = analogRead(34); // Read from pin D34

  float voltage = sensorValue * (3.3 / 4095.0); // Convert ADC value to voltage
  float current = (voltage - 1.65) / 0.066;     // Calculate current based on ACS712 sensitivity

  Serial.print("Voltage: ");
  Serial.print(voltage, 2); // Print voltage with 2 decimal places
  Serial.print(" V\t");

  Serial.print("Current: ");
  Serial.print(current, 2); // Print current with 2 decimal places
  Serial.println(" A");

  Serial.print("ADC value: ");
  Serial.println(sensorValue);

  delay(1000); // Delay for 1 second
}
