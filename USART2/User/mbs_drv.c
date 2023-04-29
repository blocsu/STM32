#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#include "stm32f4xx_conf.h"

#include "pi-09.h"

#include "mbs.h"
#include "mbs_drv.h"

#define MBS_DRV_PIRIOD_TIMER     10000                                           // Периуд работы таймера.

static uint32_t  mbs_baud[] = {9600, 14400, 19200, 28800, 38400, 57600, 115200}; // скорость объмена Бод
static uint32_t  mbs_p35[]  = {4010, 2673,  2005,  1750,  1750,  1750,  1750};   // интервал тишины мкс
static uint32_t  mbs_p15[]  = {1718, 1146,  859,   750,   750,   750,   750};    // Максимальная пауза между символами
static uint16_t  mbs_dpv_p35 = MBS_DRV_PIRIOD_TIMER/2;       // Величина таймаута 3.5 символа
static uint16_t  mbs_drv_p15 = MBS_DRV_PIRIOD_TIMER/2;       // Величина таймаута 1.5 символа
static mbs_pool * mbsp = NULL;           // Указатель на родительский пул устройств
static uint16_t index;                   // Вспомогательная переменная, номер текущего байта
static uint16_t ln_tx;                   // Количество байт для передачи
static uint8_t * buf_tx;                 // Буфер передачи

/**-----------------------------------------------------------------------------------------------/
/ Инициализация драйвера
/------------------------------------------------------------------------------------------------*/
void mbs_drv_port_init(uint8_t n_baud, mbs_pool * pool)
  {
    if (n_baud > MDS_BAUD_115200) n_baud = MDS_BAUD_115200;                 //
    mbs_dpv_p35 = MBS_DRV_PIRIOD_TIMER - mbs_p35[n_baud];                   //
    mbs_drv_p15 = MBS_DRV_PIRIOD_TIMER - mbs_p15[n_baud];                   //
    mbsp = pool;

    USART_InitTypeDef       USART_InitStructure;                            //
    GPIO_InitTypeDef        GPIO_InitStructure;                             //
    NVIC_InitTypeDef        NVIC_InitStructure;                             //
    TIM_TimeBaseInitTypeDef htim3;                                          //

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                   // тактирование торта С
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,  ENABLE);                   //

#ifdef MBS_232
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);                   // Настройка тактирвания

    NVIC_InitStructure.NVIC_IRQChannel                   = USART6_IRQn;      //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               //
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;               //
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          //
    NVIC_Init(&NVIC_InitStructure);                                         //

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;       //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               //
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;               //
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          //
    NVIC_Init(&NVIC_InitStructure);                                         //

// Инициализация портов ввода/вывода
    GPIO_StructInit(&GPIO_InitStructure);                                   //
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                           //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                       //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                          //
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                           //
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 |GPIO_Pin_7;                 //
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);               //
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);               //
// Инициализация порта USART6
    USART_StructInit(&USART_InitStructure);                                 //
    USART_InitStructure.USART_BaudRate   = mbs_baud[n_baud];                //
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                //
    USART_InitStructure.USART_Parity     = USART_Parity_No;                 //
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;   //
    USART_OverSampling8Cmd(USART6, ENABLE);                                  //
    USART_Init(USART6, &USART_InitStructure);                                //
    USART_Cmd(USART6, ENABLE);                                               //
#else
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);                   // Настройка тактирвания
    
    NVIC_InitStructure.NVIC_IRQChannel                   = UART4_IRQn;      //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               //
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;               //
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          //
    NVIC_Init(&NVIC_InitStructure);                                         //
    
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;       //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;               //
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;               //
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;          //
    NVIC_Init(&NVIC_InitStructure);                                         //

// Инициализация портов ввода/вывода
    GPIO_StructInit(&GPIO_InitStructure);                                   //
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                           //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                       //
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                          //
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                           //
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 |GPIO_Pin_1;                 //
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                  //
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);                //
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);                //
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;                          //
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;                             //
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                  //
// Инициализация порта UART4
    USART_StructInit(&USART_InitStructure);                                 //
    USART_InitStructure.USART_BaudRate   = mbs_baud[n_baud];                //
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                //
    USART_InitStructure.USART_Parity     = USART_Parity_No;                 //
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;   //
    USART_OverSampling8Cmd(UART4, ENABLE);                                  //
    USART_Init(UART4, &USART_InitStructure);                                //
    USART_Cmd(UART4, ENABLE);                                               //
#endif

// Инициализация таймера
    TIM_TimeBaseStructInit(&htim3);                                         //
    htim3.TIM_Prescaler         = 84000000/1000000-1;                       // 1 мкс (1 МГц)
    htim3.TIM_Period            = 10000-1 ;                                  // 500 мс  (2 кГц)
    htim3.TIM_ClockDivision     = 0;
    htim3.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &htim3);                                         // Разрешить прерывания от таймера
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);       // сбрасываем бит
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                              //

    return;
  }

/**-----------------------------------------------------------------------------------------------/
/ Обработчик прерываний последовательного порта
/------------------------------------------------------------------------------------------------*/
#ifdef MBS_232

void USART6_IRQHandler(void)
  {
    if (USART_GetITStatus(USART6, USART_IT_TC) == SET)   // прерывание генерируется по окончанию передачи последнего символа
      {
        USART_ClearITPendingBit(USART6, USART_IT_TC);    // ожидаем окончание передачи
        USART_ITConfig(USART6, USART_IT_TC, DISABLE);    // запрещаем прерывание
        USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);   // разрешаем приемник
        mbs_msg_to_port(mbsp, mbs_msg_ts, index);       //
        index = 0;
      }
    if (USART_GetITStatus(USART6, USART_IT_TXE) == SET)  // прерывание генерируется по освобождению приемного регистра
      {
        USART_ClearITPendingBit(USART6, USART_IT_TXE);
        if(index < ln_tx) USART_SendData(USART6, buf_tx[index++]); // передаем очередной байт
        else
          {
            USART_ITConfig(USART6, USART_IT_TC,  ENABLE);          // разрешаем прерывание
            USART_ITConfig(USART6, USART_IT_TXE, DISABLE);         // запрещаем прерывание
          }
      }
    if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET)           //
      {
        USART_ClearITPendingBit(USART6, USART_IT_RXNE);            // Сбрасываем бит
        TIM_SetCounter(TIM3, mbs_dpv_p35);                        // перезапускаем таймер
        TIM_Cmd(TIM3, ENABLE);                                    // Запускаем таймер
        mbsp->io_buf.p.ab[index++] = (uint8_t)USART_ReceiveData(USART6);// Сохраняем принятый байт
        if (index > sizeof(mbs_adu_rtu))
          {
            mbs_msg_to_port(mbsp, mbs_msg_erp, index);              //
            index = 0;
          }
      }
    if (USART_GetITStatus(USART6, USART_IT_ORE_RX) == SET)           //
      {
        USART_ReceiveData(USART6);
        USART_ClearITPendingBit(USART6, USART_IT_ORE_RX);            // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(USART6, USART_IT_ORE_ER) == SET)           //
      {
        USART_ClearITPendingBit(USART6, USART_IT_ORE_ER);            // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(USART6, USART_IT_NE) == SET)               //
      {
        USART_ClearITPendingBit(USART6, USART_IT_NE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(USART6, USART_IT_FE) == SET)               //
      {
        USART_ClearITPendingBit(USART6, USART_IT_FE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(USART6, USART_IT_PE) == SET)               //
      {
        USART_ClearITPendingBit(USART6, USART_IT_PE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
  }

#else
void UART4_IRQHandler(void)
  {
    if (USART_GetITStatus(UART4, USART_IT_TC) == SET)   // прерывание генерируется по окончанию передачи последнего символа
      {
        USART_ClearITPendingBit(UART4, USART_IT_TC);    // ожидаем окончание передачи
        USART_ITConfig(UART4, USART_IT_TC, DISABLE);    // запрещаем прерывание
        USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);   // разрешаем приемник
        mbs_msg_to_port(mbsp, mbs_msg_ts, index);       //
        index = 0;
      }
    if (USART_GetITStatus(UART4, USART_IT_TXE) == SET)  // прерывание генерируется по освобождению приемного регистра
      {
        USART_ClearITPendingBit(UART4, USART_IT_TXE);
        if(index < ln_tx) USART_SendData(UART4, buf_tx[index++]); // передаем очередной байт
        else
          {
            USART_ITConfig(UART4, USART_IT_TC,  ENABLE);          // разрешаем прерывание
            USART_ITConfig(UART4, USART_IT_TXE, DISABLE);         // запрещаем прерывание
          }
      }
    if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET)           //
      {
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);            // Сбрасываем бит
        TIM_SetCounter(TIM3, mbs_dpv_p35);                        // перезапускаем таймер
        TIM_Cmd(TIM3, ENABLE);                                    // Запускаем таймер
        mbsp->io_buf.p.ab[index++] = (uint8_t)USART_ReceiveData(UART4);// Сохраняем принятый байт
        if (index > sizeof(mbs_adu_rtu))
          {
            mbs_msg_to_port(mbsp, mbs_msg_erp, index);              //
            index = 0;
          }
      }
    if (USART_GetITStatus(UART4, USART_IT_ORE_RX) == SET)           //
      {
        USART_ReceiveData(UART4);
        USART_ClearITPendingBit(UART4, USART_IT_ORE_RX);            // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(UART4, USART_IT_ORE_ER) == SET)           //
      {
        USART_ClearITPendingBit(UART4, USART_IT_ORE_ER);            // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(UART4, USART_IT_NE) == SET)               //
      {
        USART_ClearITPendingBit(UART4, USART_IT_NE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(UART4, USART_IT_FE) == SET)               //
      {
        USART_ClearITPendingBit(UART4, USART_IT_FE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
    if (USART_GetITStatus(UART4, USART_IT_PE) == SET)               //
      {
        USART_ClearITPendingBit(UART4, USART_IT_PE);                // Сбрасываем бит
        mbs_msg_to_port(mbsp, mbs_msg_erb, 0);                      //
      }
  }
#endif

void TIM3_IRQHandler()
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);       // сбрасываем бит
    TIM_Cmd(TIM3, DISABLE);                           // Запрещаем таймер
#ifdef MBS_232
    USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);    // запрещаем приемник
#else
    USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);    // запрещаем приемник
#endif
    mbsp->io_buf.size = index;
    mbs_msg_to_port(mbsp, mbs_msg_t35, index);        //
    index = 0;
  }

/**-----------------------------------------------------------------------------------------------/
/ Инициация передачи предложения
/------------------------------------------------------------------------------------------------*/
uint16_t mbs_start_tx(uint8_t * tx, uint16_t n_tx)
  {
    MB485_TX;                      // Переводим драйвер на передачу
    buf_tx             = tx;       // устанавливаем буффер передачи
    ln_tx              = n_tx;     // длинна передаваемого предложения
    index              = 0;        //
#ifdef MBS_232
    USART_ITConfig(USART6, USART_IT_TXE, ENABLE);  // запускаем передачу
#else
    USART_ITConfig(UART4, USART_IT_TXE, ENABLE);  // запускаем передачу
#endif
    return 0;
  }

/**-----------------------------------------------------------------------------------------------/
/ Функция управления портом
/------------------------------------------------------------------------------------------------*/
#ifdef MBS_232
void mbs_drv_control(mbs_drv_st_ctrl st_ctrl)
  {
    switch (st_ctrl)
      {
        case  mbs_drv_off_port:
            MB485_RX;
            USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);   // запрещаем приемник
            USART_ITConfig(USART6, USART_IT_TXE, DISABLE);    // запрещаем передатчик
          break;
        case  mbs_drv_on_rx:
            MB485_RX;
            USART_ClearITPendingBit(USART6, USART_IT_RXNE);
            USART_ITConfig(USART6, USART_IT_TXE, DISABLE);    // запрещаем передатчик
            USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);    // Разрешаем прерывания приемника
          break;
        case  mbs_drv_on_tx:
            MB485_TX;
            USART_ClearITPendingBit(USART6, USART_IT_TXE);
            USART_ITConfig(USART6, USART_IT_RXNE, DISABLE);   // запрещаем приемник
            USART_ITConfig(USART6, USART_IT_TXE, ENABLE);     // Разрешаем прерывания передатчика
          break;
        case  mbs_drv_restart:
          break;
      }
  }
#else
void mbs_drv_control(mbs_drv_st_ctrl st_ctrl)
  {
    switch (st_ctrl)
      {
        case  mbs_drv_off_port:
            MB485_RX;
            USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);   // запрещаем приемник
            USART_ITConfig(UART4, USART_IT_TXE, DISABLE);    // запрещаем передатчик
          break;
        case  mbs_drv_on_rx:
            MB485_RX;
            USART_ClearITPendingBit(UART4, USART_IT_RXNE);
            USART_ITConfig(UART4, USART_IT_TXE, DISABLE);    // запрещаем передатчик
            USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);    // Разрешаем прерывания приемника
          break;
        case  mbs_drv_on_tx:
            MB485_TX;
            USART_ClearITPendingBit(UART4, USART_IT_TXE);
            USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);   // запрещаем приемник
            USART_ITConfig(UART4, USART_IT_TXE, ENABLE);     // Разрешаем прерывания передатчика
          break;
        case  mbs_drv_restart:
          break;
      }
  }
#endif
