/* Copyright 2023 Cheng Liren
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include "port_foc.h"

extern uint32_t SystemCoreClock;
extern volatile uint32_t uwTick;

#define CYCLES_PER_MICROSECOND (SystemCoreClock / 1000000U)
#define SysTick_LoadValue      (SystemCoreClock / 1000U)

void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

void delay_us(uint32_t us)
{
    uint32_t total = 0;
    uint32_t target = CYCLES_PER_MICROSECOND * us;
    int last = SysTick->VAL;
    int now = last;
    int diff = 0;
start:
    now = SysTick->VAL;
    diff = last - now;
    if (diff > 0) {
        total += diff;
    } else {
        total += diff + SysTick_LoadValue;
    }
    if (total > target) {
        return;
    }
    last = now;
    goto start;
}

uint32_t micros(void)
{
    return (uwTick * 1000 + ((SysTick_LoadValue - SysTick->VAL) / CYCLES_PER_MICROSECOND));
}