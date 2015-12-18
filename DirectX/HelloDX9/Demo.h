#ifndef _DEMO_H
#define _DEMO_H

#include "d3dUtility.h"

extern IDirect3DDevice9* Device;

bool Setup();

void Cleanup();

bool Display(float timeDelta);

#endif