#pragma once
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "main.h"
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
uint32_t micros(void);

#define delay(ms)             delay_ms(ms)
#define delayMicroseconds(us) delay_us(us)
