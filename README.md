# EDM4660: Atelier ESP32 et Shield Sparkfun DMX

## Composantes principales

* [SparkFun Thing Plus - ESP32 WROOM](https://www.sparkfun.com/products/15663)
* [SparkFun ESP32 Thing Plus DMX to LED Shield](https://www.sparkfun.com/products/15110)

IMPORTANT: Ne connectez pas de cartes audio DMX sur le shield car cela risque de bousiller les composantes.

## Préparation

Installez les dernières versions des logiciels [Arduino](https://www.arduino.cc/en/software) et [Processing](https://processing.org/download/).

Dans Arduino:
* Suivez les instructions pour installer le ["board add-on" du ESP32](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions) (le microcontrôlleur que nous allons utiliser)
* NOTE: Il n'est pas nécessaire de faire la procédure "Testing the Installation" avant le cours (à moins que vous ayez en votre possession un ESP32)
* Installer les librairies suivantes avec le ["Library manager"](https://www.arduino.cc/en/guide/libraries): ArtnetWifi, "Sparfun DMX Shield Library".
	
Dans Processing: Installer la librairie suivante: "Artnet for Java and Processing"

## ESP32

![Graphical datasheet ESP32](https://cdn.sparkfun.com/r/600-600/assets/learn_tutorials/8/5/2/ESP32ThingPlusV20_GraphicalDatasheet.jpg)

![ESP8266 vs ESP32](https://files.readme.io/854b6cc-esp8266-esp32.png)

![Benchmarks](https://forum.pjrc.com/coremark_barchart.png)
