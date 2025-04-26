#include <Arduino.h>
#include "config.h"
#include "joystick.h"
#include "communication.h"

Joystick joystick;
Communication comm;
rc_data_t rcData;

void setup() {
    joystick.setup();
    joystick.calibrate();
    comm.setup();
}

void loop() {
    joystick.updateValues(rcData);
    comm.sendData(rcData);
}