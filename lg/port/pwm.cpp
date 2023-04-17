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
#include "port_foc.h"
#include "SerialUart.h"
#include "hardware_driver_api.h"

#define PWM_RANGE 2399

void _writeDutyCycle3PWM(float dc_a, float dc_b, float dc_c, void *params)
{
    static uint32_t ct = 0;
    ct ++;
    if (ct == 100000) {
        ct = 0;
			Serial.printf("write pwm duty dc_a:%f dc_b:%f dc_c:%f \r\n", dc_a, dc_b, dc_c);
    }
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, dc_a * PWM_RANGE);
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, dc_b * PWM_RANGE);
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, dc_c * PWM_RANGE);
    
}

void *_configure3PWM(long pwm_frequency, const int pinA, const int pinB, const int pinC)
{
    Serial.printf("_configure3PWM \r\n");
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
    return (void *)1;
}
