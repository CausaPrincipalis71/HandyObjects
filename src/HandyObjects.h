#ifndef HANDYOBJECTS_H
#define HANDYOBJECTS_H

extern "C" {
#include "HDefine.h"
#include "HGpio.h"
#include "HGpio.cpp"

void SysTick_Handler(void)
{
  HAL_IncTick();
}

}

#endif  //HANDYOBJECTS_H