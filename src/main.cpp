#include <HardwareSerial.h>

#define GPS_SERIAL Serial2

void parseGPSData(String data)
{
    // Remove leading/trailing whitespace and the checksum
    data.trim();
    data = data.substring(0, data.indexOf('*'));

    // Split the sentence into individual fields using commas as delimiters
    int numFields = 0;
    String fields[20]; // Adjust the array size based on the maximum expected fields in your NMEA sentences
    char *dataPtr = const_cast<char *>(data.c_str());
    char *token = strtok(dataPtr, ",");
    while (token != NULL && numFields < 20)
    {
        fields[numFields] = String(token);
        numFields++;
        token = strtok(NULL, ",");
    }

    // Process the specific NMEA sentence types you're interested in
    if (fields[0] == "$GPGGA")
    {
        // Example: Extract latitude, longitude, and altitude
        String latitude = fields[2];
        String longitude = fields[4];
        String altitude = fields[9];
        Serial.print("Latitude: ");
        Serial.println(latitude);
        Serial.print("Longitude: ");
        Serial.println(longitude);
        Serial.print("Altitude: ");
        Serial.println(altitude);
        Serial.println();
    }
    else if (fields[0] == "$GPRMC")
    {
        // Example: Extract speed and course
        String speed = fields[7];
        String course = fields[8];
        Serial.print("Speed: ");
        Serial.println(speed);
        Serial.print("Course: ");
        Serial.println(course);
        Serial.println();
    }
    // Add more conditions to handle other NMEA sentence types as needed
}

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
        static String sentence = "";
        if (c == '\n')
        {
            if (sentence.startsWith("$"))
            {
                parseGPSData(sentence);
            }
            sentence = "";
        }
        else
        {
            sentence += c;
        }
    }
}
