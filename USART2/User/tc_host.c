#include "stm32f4xx_conf.h"
#include "tc_host.h"
#include "pi-09.h"
#include "rc_code.h"

#define   TIME_WAIT_FIRST_SM     (2000-1000)
#define   TIME_WAIT_NEXT_SM      (2000-1-300)

void InitTCHost(void) {
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef htim4;

    // Настраиваем таймер и разрешаем прерывания от него
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_TimeBaseStructInit(&htim4);
    htim4.TIM_Prescaler         = 84000000/1000000-1;	// 1 мкс (1 МГц)
    htim4.TIM_Period            = 2000-1 ;				// 500 мс  (2 кГц)
    htim4.TIM_ClockDivision     = 0;
    htim4.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &htim4);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    // Настраиваем последовательный порт
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 |GPIO_Pin_11;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    USART_StructInit(&USART_InitStructure);

    USART_InitStructure.USART_BaudRate   		  = 115200;
    USART_InitStructure.USART_WordLength 		  = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits   		  = USART_StopBits_1;
    USART_InitStructure.USART_Parity     		  = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       		  = USART_Mode_Rx | USART_Mode_Tx;
    USART_OverSampling8Cmd(USART3, ENABLE);
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
}

static uint16_t  buf_ind;

static uint8_t  *buf_tx;
static uint8_t  *buf_rx;

static uint16_t  len_tx;
static uint16_t *len_rx;
static uint16_t *flag;

// Прерывания от USART
void USART3_IRQHandler(void) {
    // Окончание передачи
    if(USART_GetITStatus(USART3, USART_IT_TC) == SET) {
        USART_ClearITPendingBit(USART3, USART_IT_TC);    // Сбрасываем флаг
        USART_ITConfig(USART3, USART_IT_TC, DISABLE);    // Запрещаем прерывание передатчика
        SYSRS485_RX;                                     // Переключаемся на прием
        USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);   // Разрешаем прерывание приемника
        TIM_SetCounter(TIM4, TIME_WAIT_FIRST_SM);        // Настраиваем таймер
        TIM_Cmd(TIM4, ENABLE);                           // Запускаем таймер
        buf_ind = 0;
    }

    // Выдача очередного байта
    if(USART_GetITStatus(USART3, USART_IT_TXE) == SET) {
        USART_ClearITPendingBit(USART3, USART_IT_TXE);		// Сбрасываем флаг

        // Пока есть байты для выдачи - передаем
        if(buf_ind < len_tx) USART_SendData(USART3, buf_tx[buf_ind++]);

        // Когда байты закончились - переключаем прерывания
        else {
            USART_ITConfig(USART3, USART_IT_TC,  ENABLE);   // Разрешаем по окончанию передачи
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);  // Запрещаем по выдаче байта
        }
    }

    // Прием байта
    if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET) {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);       // Сбрасываем флаг
        TIM_SetCounter(TIM4, TIME_WAIT_NEXT_SM);              // Перезапускаем таймер
        buf_rx[buf_ind++] = (uint8_t)USART_ReceiveData(USART3); // Сохраняем принятый байт
        if(buf_ind > *len_rx) buf_ind = 0;
    }
}

// Прерывания от таймера (таймер завершения приема)
void TIM4_IRQHandler(void) {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);       // Сбрасываем флаг
    TIM_Cmd(TIM4, DISABLE);                           // Останавливаем таймер
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);   // Запрещаем прерывния от приемника
    *len_rx = buf_ind;                                // количество принятых символов
    *flag = (buf_ind < 6) ? RCC_ER_IO : RCC_NO_ERROR;
}

//
// Входные параметры:
// uint8_t  *tx_ptr - указатель на передаваемые данные
// uint16_t  cnt_tx - длинна в байтах передаваемых данных
// uint8_t  *rx_ptr - указатель на буфер для принимаемых данных
// uint16_t *cnt_rx - через переменную передается размер буфера, возврадается количество принятых байтов
// uint16_t *fl     - возвращается статус принятого предложения.
//
uint16_t tr_port(uint8_t *tx_ptr, uint16_t cnt_tx, uint8_t *rx_ptr, uint16_t *cnt_rx, uint16_t *fl) {

	// Переводим драйвер на передачу
    SYSRS485_TX;

    // Сохраняем параметры
    buf_tx	= tx_ptr;
    len_tx	= cnt_tx;
    buf_rx	= rx_ptr;
    len_rx	= cnt_rx;
    flag	= fl;
    buf_ind	= 0;

    // Начинаем передачу
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

    return *flag;
}
