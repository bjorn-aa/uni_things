#ifndef xboxControl_h_
#define xboxControl_h_

extern "C" {
#include "mtJoystick.h"
#include "xboxControlRumble.h"
}


void xboxControlInit();
void xboxControlHandler();
bool isXboxControllerEnabled();
void xboxControlFree();

bool getIsXboxControllerConnected();

#endif
