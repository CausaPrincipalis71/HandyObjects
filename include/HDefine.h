#ifndef HDEFINE_H
#define HDEFINE_H

#include "stm32f1xx_hal.h"

#include "math.h"

/*СПИСОК КОНТАКТОВ*/

enum HPin  {A0 = 0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
           B0 = 20, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15,
           C0 = 40, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15};


/*СПИСОК РЕЖИМОВ*/
enum HMode {OUTPUT = 0, INPUT = 1};

/*ПЕРЕМЕННЫЕ ХРАНЯЩИЕ ДАННЫЕ*/

bool HGpioA_Enabled = false;
bool HGpioB_Enabled = false;
bool HGpioC_Enabled = false;

#endif