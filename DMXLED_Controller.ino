#include <RGBLED.h>
#include <DMXSerial.h>

RGBLED L0 = RGBLED(3,5,6);
RGBLED L1 = RGBLED(9,10,11);
const int DMXAddr[6] = {1,2,3,4,5,6};

void setup() {
  DMXSerial.init(DMXReceiver);
}

void loop() {
  L0.setColors(
    DMXSerial.read(DMXAddr[1]),
    DMXSerial.read(DMXAddr[2]),
    DMXSerial.read(DMXAddr[3]));
  L1.setColors(
    DMXSerial.read(DMXAddr[4]),
    DMXSerial.read(DMXAddr[5]),
    DMXSerial.read(DMXAddr[6]));
 
}
