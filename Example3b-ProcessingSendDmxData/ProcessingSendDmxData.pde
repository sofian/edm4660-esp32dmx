import ch.bildspur.artnet.*;

// Edit to match receiving node IP address.
String DMX_NODE_IP = "192.168.1.100";

// ArtNetClient objects.
ArtNetClient artnet;
byte[] dmxData = new byte[512];

void setup()
{
  // Initialize.
  size(800, 800);
  
  colorMode(HSB, 360, 100, 100);
  textAlign(CENTER, CENTER);
  textSize(20);

  // Create artnet client without buffer (no receving needed).
  artnet = new ArtNetClient(null);
  artnet.start();
}

void draw()
{
  // Create color based on mouse position (x controls hue, y controls value).
  int c = color( map(mouseX, 0, width, 0, 360),
                 100,
                 map(mouseY, 0, height, 0, 100) );

  // Set background to color.
  background(c);

  // Fill DMX array.
  dmxData[0] = (byte) red(c);
  dmxData[1] = (byte) green(c);
  dmxData[2] = (byte) blue(c);

  // Send DMX message.
  // Function signature: unicastDmx(String address, int subnet, int universe, byte[] dmxData)
  artnet.unicastDmx(DMX_NODE_IP, 0, 0, dmxData);

  // Show RGB color value.
  String colorText = "R: " + (int)red(c) + " Green: " + (int)green(c) + " Blue: " + (int)blue(c);
  fill(0);
  rectMode(CENTER);
  rect(width/2, height/2, textWidth(colorText)+20, 40);
  fill(255);
  text(colorText, width / 2, height / 2);
}
