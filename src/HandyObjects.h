#ifndef HANDYOBJECTS_H
#define HANDYOBJECTS_H


#include "HDefine.h"
#include "HGpio.h"
#include "HGpio.cpp"
#include "HVector.h"
#include "_HProgramm.h"
#include "_HProgramm.cpp"

extern "C" {
void SysTick_Handler(void)
{
  HAL_IncTick();
}

}

#endif  //HANDYOBJECTS_H