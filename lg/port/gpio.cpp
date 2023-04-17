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
#include <stdbool.h>
#include "port_foc.h"
#include "gpio.h"
#include "hardware_driver_api.h"
static uint16 pins[PIN_NUM] = {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15
};

static void *ports[PORT_NUM] = {
    (void *)GPIOA,
    (void *)GPIOB,
    (void *)GPIOC,
    (void *)GPIOD,
    (void *)GPIOE
};

void digitalWrite(int pin, bool state)
{
    HAL_GPIO_WritePin((GPIO_TypeDef *)(ports[(pin / PIN_NUM)]), pins[(pin % PIN_NUM)], (GPIO_PinState)state);
}
