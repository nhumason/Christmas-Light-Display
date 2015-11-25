#include <RGBLED.h>
#include <DMXSerial.h>

RGBLED L0 = RGBLED(2,3,4);
RGBLED L1 = RGBLED(5,6,7);
RGBLED L2 = RGBLED(8,9,10);
RGBLED L3 = RGBLED(11,12,13);
RGBLED L4 = RGBLED(44,45,46);
const int RlyPinCnt = 8;
const int RlyModuleCnt = 2;
const int RlyPins[][RlyPinCnt] = {{22,24,26,28,30,32,34,36},
                        {23,25,27,29,31,33,35,37}};
const int DMXStart = 1;
const int DMXLength = 31;
int DMXAddr[DMXLength];
const int RlyDMXStart = 16;

void setup() {
  DMXSerial.init(DMXReceiver); //initializes the DMX receiver
  for (int rly = 0; rly < RlyModuleCnt; rly++) { //initializes all the relay pins
    for (int pin = 0; pin < RlyPinCnt; pin++) {
      pinMode(RlyPins[rly][pin], OUTPUT);
      digitalWrite(RlyPins[rly][pin], HIGH); //set the relay off
    }
  }
  for (int Addr = 0; Addr < DMXLength; Addr++) { //initializes all DMX values
    DMXAddr[Addr] = Addr + DMXStart;
  }
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
  L2.setColors(
    DMXSerial.read(DMXAddr[7]),
    DMXSerial.read(DMXAddr[8]),
    DMXSerial.read(DMXAddr[9]));
  L3.setColors(
    DMXSerial.read(DMXAddr[10]),
    DMXSerial.read(DMXAddr[11]),
    DMXSerial.read(DMXAddr[12]));
  L4.setColors(
    DMXSerial.read(DMXAddr[13]),
    DMXSerial.read(DMXAddr[14]),
    DMXSerial.read(DMXAddr[15]));
  int DMX = RlyDMXStart; //keep track of the current DMX address within the loop
  for (int rly = 0; rly < RlyModuleCnt; rly++) {
    for (int pin = 0; pin < RlyPinCnt; pin++) {
      int DMXValue = DMXSerial.read(DMXAddr[DMX]);
      if (DMXValue == 255) { //on at max value
        digitalWrite(RlyPins[rly][pin], LOW);
      }
      else if (DMXValue < 255) { //off at anything below max
        digitalWrite(RlyPins[rly][pin], HIGH);
      }
      DMX++;
    }
  }
}
