#include <SPI.h>
#include <SD.h>

// Chip select pin for the SD card module
const int chipSelect = 6;

void setup()
{
  Serial.begin(115200);

  // Initialize SD card
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  Serial.println("Card Initialized");

  // Create and open a file on the SD card
  File dataFile = SD.open("/data.txt", FILE_WRITE);

  // If the file is available, write to it
  if (dataFile)
  {
    dataFile.println("Hello, this is data being written to the SD card!");
    dataFile.close();
    Serial.println("Data written to the file.");
  }
  else
  {
    Serial.println("Error opening file.");
  }
}

void loop()
{
  // Nothing to do here
}
