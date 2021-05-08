#ifndef _HPROGRAMM_H
#define _HPROGRAMM_H
#include <HDefine.h>
#include <HVector.h>

class _HProgramm                // Реализация статичного класса
{

public:
    _HProgramm();
    ~_HProgramm();

    void programm();            // Сама программа
    bool connect(bool(*signal)(), void(*slot)());

private:
    TIM_HandleTypeDef htim;     // Таймер

    /*Структура, содержащая в себе сигнал, и прикреплённые к нему слоты*/
    struct SignalAndSlots       
    {
        bool(*signal)();
        HVector<void(*)()> slots;
    };
    
    HVector<SignalAndSlots> SignalAndSlots_Vector;
};

#endif//HProgramm