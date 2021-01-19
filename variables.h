#ifndef VARIABLES_H
#define VARIABLES_H

// BASES

#define INTERVAL 1000

const int BUTTON_RED = 2;
const int BUTTON_GREEN = 3;
const short int LONG_PRESS_TIME = 2000;

bool currentStateRed;
bool currentStateGreen;
bool RED_BUTTON_5S = false;
bool GREEN_BUTTON_5S = false;

unsigned long pressedTime = 0;
unsigned long currentTime = 0;

#endif