#include "HGpio.h"

extern "C" {

HGpio::HGpio(HPin pin, HMode mode)
{
    GPIO_InitTypeDef Temp_GPIO;             // Структура инициализации
    int8_t pinNum;                          // Номер контакта от 0 до 15


    if(pin < 20)                            // Если контакт A
    {
        if(!HGpioA_Enabled)                 // Если тактирование не подключено
            {
            __HAL_RCC_GPIOA_CLK_ENABLE();   // Подключить тактирование к контактам A
            HGpioA_Enabled = true;          // Записать в переменную
            }
        
        pinNum = pin;                       // Передать значение контакта в переменную pinNum
        m_Group = GPIOA;                    // Группа контактов A
    }

    else if(pin >= 20 && pin < 40)          // Если контакт B
    {
        /*Аналогично первому случаю*/
        if(!HGpioB_Enabled)                 
            {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            HGpioB_Enabled = true;
            }

        pinNum = pin % 20;                  // Передать значение контакта от 0 до 15
        m_Group = GPIOB;                    // Группа контактов B
    }

    else if(pin >= 40)                      // Если контакт C
    {
        /*Аналогично первому случаю*/
        if(!HGpioC_Enabled)
            {
            __HAL_RCC_GPIOC_CLK_ENABLE();
            HGpioC_Enabled = true;
            }
        
        pinNum = pin % 40;                  // Передать значение контакта от 0 до 15
        m_Group = GPIOC;                    // Группа контактов C
    }

    /*Запись данных*/
    m_Pin = pow(2, pinNum);                 // Возводится в степень для работы с HAL
    m_Mode = mode;

    if(mode == OUTPUT)
    {
        Temp_GPIO.Mode = GPIO_MODE_OUTPUT_PP;
        Temp_GPIO.Pull = GPIO_PULLUP;
    }
    else if(mode == INPUT)
    {
        Temp_GPIO.Mode = GPIO_MODE_INPUT;
        Temp_GPIO.Pull = GPIO_PULLDOWN;
    }
    Temp_GPIO.Pin = m_Pin;         // Номер контакта равняется двух в степени номера контакта
    
    Temp_GPIO.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(m_Group, &Temp_GPIO);
}

HGpio::~HGpio()
{
    HAL_GPIO_DeInit(m_Group, m_Pin);
}


/*Управление контактами*/

bool HGpio::setState(bool state)
{
    if(m_Mode == INPUT)             // Если контакт настроен на ввод
        return false;               // Вернуть false
    
    writePin_Shell(state);
    m_State = state;
    return true;
}

bool HGpio::setHIGH()
{
    return this->setState(true);
}

bool HGpio::setLOW()
{
    return this->setState(false);
}

bool HGpio::toggleState()
{
    return this->setState(!m_State);
}

/*Функция ввода*/
bool HGpio::readState()
{
    m_State = (HAL_GPIO_ReadPin(m_Group, m_Pin) == 1);
    return m_State;
}

/*Внутренние функции*/

void HGpio::writePin_Shell(bool state)
{
    if(state == false)                                          // Если false
        HAL_GPIO_WritePin(m_Group, m_Pin, GPIO_PIN_SET);      // Установить 0
    else                                                        // В другом случае
        HAL_GPIO_WritePin(m_Group, m_Pin, GPIO_PIN_RESET);        // Установить 1
}
}