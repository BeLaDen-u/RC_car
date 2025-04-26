#include <Arduino.h>
#include "config.h"
#include "servo_control.h"
#include "esc_control.h"
#include "communication.h"

ServoControl servo;
ESCControl esc;
Communication comm;

void setup() {
    servo.setup();
    esc.setup();
    comm.setup(servo, esc);
}

void loop() {
    esc.update();

    if (comm.isConnectionTimedOut()) {
        servo.setFailsafe();
        esc.setFailsafe();
    }
}
