#include <HardwareSerial.h>

#define GPS_SERIAL Serial2

void setup()
{
    Serial.begin(115200);
    GPS_SERIAL.begin(9600, SERIAL_8N1, 16, 17); // Use GPIO 16 (RX2) and GPIO 17 (TX2) for serial communication with GPS
}

void loop()
{
    if (GPS_SERIAL.available())
    {
        char c = GPS_SERIAL.read();
        // Process the received character from GPS module as needed
        Serial.print(c);
    }
}
