#include "_HProgramm.h"

_HProgramm::_HProgramm()
{
    /*Инициализация таймера*/
    __HAL_RCC_TIM4_CLK_ENABLE();                                // Подклчюается тактирование 4 таймера
    htim.Instance = TIM4;                                       // 4 таймер
    htim.Init.Prescaler = 719;
    htim.Init.Period = 999;                                     // Задаётся период в 0.01 секунды
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim);
    TIM_ClockConfigTypeDef tmpClockConfig;
    tmpClockConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim, &tmpClockConfig);
    HAL_TIM_Base_Start_IT(&htim);
    NVIC_EnableIRQ (TIM4_IRQn);
}

_HProgramm::~_HProgramm()
{

}

void _HProgramm::programm()
{
    for(int i = 0; i < SignalAndSlots_Vector.size(); i++)                       // Осматривая все структуры
    {
        if(SignalAndSlots_Vector[i].signal() == true)                           // Если где-то отработал сигнал
        {   
            for(int j = 0; j < SignalAndSlots_Vector[i].slots.size(); j++)      // Проходя по всем слотам
            {
                SignalAndSlots_Vector[i].slots[j]();                            // Выполнять их
            }
        }
    }
}

bool _HProgramm::connect(bool(*signal)(), void(*slot)())
{
    for(int i = 0; i < SignalAndSlots_Vector.size(); i++)
    {
        if(SignalAndSlots_Vector[i].signal == signal)
        {
            for(int j = 0; j < SignalAndSlots_Vector[i].slots.size(); j++)
            {
                if(SignalAndSlots_Vector[i].slots[j] == slot)
                {
                    return false;
                }
            }
            SignalAndSlots_Vector[i].slots.push_back(slot);
            return true;
        }
    }

    SignalAndSlots tempSignalsAndSlots;
    tempSignalsAndSlots.signal = signal;
    tempSignalsAndSlots.slots.push_back(slot);

    SignalAndSlots_Vector.push_back(tempSignalsAndSlots);
    return true;
}