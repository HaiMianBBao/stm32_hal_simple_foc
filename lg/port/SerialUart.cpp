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

void SerialUart::begin(uint32_t baudRate)
{
    is_start = true;
    HAL_UART_Receive_IT(huart, &rev_char, 1);
}

void SerialUart::end(void)
{
    if (is_start == true) {
        is_start = false;
    }
}

size_t SerialUart::write(uint8_t n)
{
    if (is_start == true) {
        HAL_UART_Transmit(huart, &n, 1, 0xff);
    }
    return 1;
}

SerialUart::SerialUart(UART_HandleTypeDef *huart)
{
    this->huart = huart;
    this->m_serial_cb = nullptr;
    this->m_rx_buffer_head = this->m_rx_buffer_tail = 0;
}

SerialUart::SerialUart(/* args */)
{
}

SerialUart::~SerialUart()
{
}

SerialUart Serial(&huart1);

#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) {
        Serial.commonCallBack();
        HAL_UART_Receive_IT(huart, &Serial.rev_char, 1);
    }
}

#ifdef __cplusplus
}
/* ---------------------------- C++ Scope --------------------------- */
#endif