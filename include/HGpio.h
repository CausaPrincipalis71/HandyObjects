#ifndef HGPIO_H
#define HGPIO_H

#include "HDefine.h"

class HGpio
{
public:
    /*Конструторы и деструктор*/
    HGpio(HPin pin, HMode mode);
    ~HGpio();

    /*Управление контактами в режиме OUTPUT*/
    bool setState(bool state);
    bool setHIGH();
    bool setLOW();
    bool toggleState();

    /*Управление контактами в режиме INPUT*/
    bool readState();

protected:
    bool m_State = false;
    uint16_t m_Pin;
    HMode m_Mode;
    GPIO_TypeDef * m_Group;

    /*Внутренние функции*/
    virtual void writePin_Shell(bool state);    //Оболочка для HAL_GPIO_Write_pin(), позволяющая работать с bool
};

#endif  //HGPIO_H