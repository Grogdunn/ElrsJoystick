#include <Joystick.h>
#include "CrsfSerial.h"

// Create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_MULTI_AXIS, 8, 0,
                   true, true, false, false, false, false,  //x, y, !z, !rx, !ry, !rz
                   true, true, false, false, false);        //rudder, throttle, !accelerator, !brake, !steering
long baud_rate = 115200;
CrsfSerial crsf(Serial1, baud_rate);
int values[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void copy() {
  for (int i = 0; i < 16; i++) {
    values[i] = crsf.getChannel(i + 1);
  }
}
void print() {
  for (int i = 0; i < 16; i++) {
    Serial.print("CH");
    Serial.print(i + 1);
    Serial.print(" ");
    // Serial.print(map(values[i], 989, 2011, 0, 1023));
    Serial.print(values[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void packetChannels() {
  Joystick.setXAxis(crsf.getChannel(1));
  Joystick.setYAxis(crsf.getChannel(2));
  Joystick.setRudder(crsf.getChannel(3));
  Joystick.setThrottle(crsf.getChannel(4));
  // Uncomment for debug
  // for (int i = 0; i < 16; i++) {
  //   if (i != 14 && values[i] != crsf.getChannel(i + 1)) {
  //     copy();
  //     print();
  //     break;
  //   }
  // }
}

void onLinkUp() {
  // Serial.print("link up");
}

void setup() {
  // Initialize Joystick Library
  crsf.onPacketChannels = &packetChannels;
  crsf.onLinkUp = &onLinkUp;
  Joystick.setXAxisRange(989, 2011);
  Joystick.setYAxisRange(989, 2011);
  Joystick.setRudderRange(989, 2011);
  Joystick.setThrottleRange(989, 2011);
  Joystick.begin();
  // Serial.begin(baud_rate);
}


void loop() {
  crsf.loop();
}
