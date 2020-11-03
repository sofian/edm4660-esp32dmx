/**
 * Simple Wifi ArtNet control of 3 DMX channels (R, G, B).
 * 
 * Author: Sofian Audry
 * Licence: Gnu GPL 3.0 https://www.gnu.org/licenses/gpl-3.0.en.html
 */

#include <ArtnetWifi.h>
#include <Arduino.h>

//Wifi settings
#define WIFI_SSID "MyNetwork"
#define WIFI_PASSWORD "MyPassword"

#define WIFI_CONNECTION_TIMEOUT 5000

WiFiUDP UdpSend;
ArtnetWifi artnet;

#include <SparkFunDMX.h>

SparkFunDMX dmx;

//Channel Definitions
#define START_CHANNEL 1 // change as needed

#define RED_CHANNEL START_CHANNEL
#define GREEN_CHANNEL (START_CHANNEL+1)
#define BLUE_CHANNEL (START_CHANNEL+2)

#define TOTAL_CHANNELS 3

void blinkIndicatorLed(unsigned long period, float pulseProportion=0.5, int nBlinks=1);
void initWifi(boolean apMode=false);
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data);

#define CLOCK = 5;
#define DATA0 = 19;
#define DATA1 = 18;
#define DATA2 = 27;

#define AP_MODE false

void setup()
{
  // Start serial.
  Serial.begin(115200);
  while (!Serial) delay(1); // wait for serial to be ready
  Serial.println("Starting.");

  // Start wifi.
  initWifi(AP_MODE);

  // This will be called for each packet received.
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();

  // Initialize DMX for target number of channels.
  dmx.initWrite(TOTAL_CHANNELS);
  Serial.println("DMX initialized.");
  delay(200); // wait a while (not necessary)
}

void loop()
{
    // Check connection status: reconnect if connection lost.
  if (WiFi.status() != WL_CONNECTED)
    initWifi(AP_MODE);

  // we call the read function inside the loop
  artnet.read();
}

// Initialize wifi.
void initWifi(boolean apMode)
{
  // Start wifi.
  WiFi.mode(WIFI_AP_STA);

  // IP address of node.
  IPAddress myIP;

  // AP mode.
  if (apMode) {
  
    // You can remove the password parameter if you want the AP to be open.
    if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
      Serial.println("Unable to create access point. Rebooting.");
      blinkIndicatorLed(100, 0.7, 20);
      ESP.restart();
    }
  
    // Get IP address.
    myIP = WiFi.softAPIP();

  // Non-AP mode.
  } else {
  
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
    // Wait for connection to complete.
    unsigned long startMillis = millis();
    while (WiFi.status() != WL_CONNECTED && 
           millis() - startMillis < WIFI_CONNECTION_TIMEOUT) {
      Serial.print(".");
      blinkIndicatorLed(500);
    }
  
    // If still not connected, restart the board.
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Unable to connect. Rebooting.");
      blinkIndicatorLed(100, 0.7, 20);
      ESP.restart();
    }
  
    // Get IP address.
    myIP = WiFi.localIP();
  }

  // Send address.
  Serial.println("IP: ");
  Serial.println(myIP);
}

// This function is called upon receiving one DMX message from ArtNet.
void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  //Read universe and put into the right part of the display buffer
  //DMX data should be sent with the first LED in the string on channel 0 of Universe 0
  for (int channel = 0; channel < length; channel++)
  {
    dmx.write(channel+START_CHANNEL, data[channel]);
  }
  dmx.update();
}


// Simple method to blink the indicator LED with specific patterns.
void blinkIndicatorLed(unsigned long period, float pulseProportion, int nBlinks) {
  while (nBlinks--) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay((unsigned long) (period * pulseProportion));
    digitalWrite(LED_BUILTIN, LOW);
    delay((unsigned long) ((period * (1-pulseProportion))));
  }
}
