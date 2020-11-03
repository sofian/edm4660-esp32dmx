/**
 * Simple analog read to DMX output demo to control 3 channels (R, G, B).
 * 
 * Author: Sofian Audry
 * Licence: Gnu GPL 3.0 https://www.gnu.org/licenses/gpl-3.0.en.html
 */
#include <SparkFunDMX.h>

SparkFunDMX dmx;

//Channel Definitions
#define START_CHANNEL 1 // change as needed

#define RED_CHANNEL START_CHANNEL
#define GREEN_CHANNEL (START_CHANNEL+1)
#define BLUE_CHANNEL (START_CHANNEL+2)

#define TOTAL_CHANNELS 3

// Analog input pin.
#define ANALOG_IN 26

//Pin Definitions for ESP32 WROOM DMX to LED Shield
#define CLOCK = 5;
#define DATA0 = 19;
#define DATA1 = 18;
#define DATA2 = 27;

void writeRgb(int r, int g, int b, unsigned long duration=0);

void setup() {
  // Start serial.
  Serial.begin(115200);
  while (!Serial) delay(1); // wait for serial to be ready
  Serial.println("Starting.");

  // Initialize DMX for target number of channels.
  dmx.initWrite(TOTAL_CHANNELS);
  Serial.println("DMX initialized.");
  delay(200); // wait a while (not necessary)
}

void loop() {
  // Read analog value (0..4095).
  int analogValue = analogRead(ANALOG_IN);
  Serial.println(analogValue);

  // Transfer range [0..4095] to [0..255].
  int intensity = map(analogValue, 0, 4095, 0, 255);
  
  // Adjust lights accordingly.
  writeRgb(intensity, intensity, intensity);
  
}

// Write RGB value for specific duration (in ms).
void writeRgb(int r, int g, int b, unsigned long duration) {
  // Write once.
  dmx.write(RED_CHANNEL,   r);
  dmx.write(GREEN_CHANNEL,  g);
  dmx.write(BLUE_CHANNEL, b);
  // Keep updating.
  duration += millis(); // duration becomes max. millis
  do {
    dmx.update();
    delay(1);
  } while (millis() < duration);
}
