// Arduino Nano with DHT11 Sensor & OLED Display
// This project displays real-time temperature and humidity readings on a 128x64 OLED display.
// The DHT11 sensor reads the temperature and humidity, 
// while the OLED shows these values using large font and 
// relevant symbols (°C for temperature and % for humidity).
//
// Components Used:
// - Arduino Nano
// - DHT11 Humidity & Temperature Sensor
// - 128x64 OLED Display
//
// For more projects and to buy components, visit: http://kitkraft.in

#include "DHT.h"                      // Include the DHT sensor library
#include <Adafruit_SSD1306.h>          // Include the Adafruit SSD1306 library for OLED display

// DHT object for the DHT11 sensor
DHT dht;

// OLED display width and height
#define OLED_WIDTH 128  // OLED display width in pixels
#define OLED_HEIGHT 64  // OLED display height in pixels

// Create an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);               // Start serial communication for debugging

  dht.setup(7);                     // Set the pin (7) for DHT11 sensor data communication

  // Initialize the OLED display with address 0x3C for 128x64 resolution
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);                   // Halt the program if OLED fails to initialize
  }

  delay(2000);                      // Wait for the OLED to initialize
  oled.clearDisplay();              // Clear the OLED display

  // Display initialization message on OLED
  oled.setTextSize(1);              // Set text size to small
  oled.setTextColor(WHITE);         // Set text color to white
  oled.setCursor(0, 20);            // Set cursor position on the display
  oled.println("Temperature & ");    // Display initial message
  oled.println("Humidity Sensor");   // Display initial message
  oled.display();                   // Show the text on the OLED
  delay(2000);                      // Wait for 2 seconds to allow the user to read the message
  oled.clearDisplay();              // Clear the display for real-time data display
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());  // Delay for the sampling period required by DHT11

  // Get humidity and temperature values from DHT11 sensor
  float humidity = dht.getHumidity();      // Get humidity value
  float temperature = dht.getTemperature();  // Get temperature value in Celsius

  // Clear the OLED display to update with new data
  oled.clearDisplay();  

  // Set larger text size to display temperature and humidity
  oled.setTextSize(2);                   // Set text size to 2 for larger font

  // Display temperature with °C symbol
  oled.setCursor(0, 10);                 // Set cursor position for temperature
  oled.print("Temp: ");                  // Display label for temperature
  oled.print((int)temperature);          // Display temperature value as an integer
  oled.print((char)247);                 // Display the degree symbol (°)
  oled.print("C");                       // Display Celsius unit (C)

  // Display humidity with % symbol
  oled.setCursor(0, 40);                 // Set cursor position for humidity
  oled.print("Hum: ");                   // Display label for humidity
  oled.print((int)humidity);             // Display humidity value as an integer
  oled.print("%");                       // Display percentage symbol (%)

  oled.display();                        // Display the updated temperature and humidity on OLED

  delay(500);                            // Refresh every 500 milliseconds (0.5 seconds)
}
