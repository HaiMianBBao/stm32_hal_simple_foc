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
#include "Serial.h"

void Serial::attachInterrupt(callback function)
{
    this->m_serial_cb = function;
}

void Serial::commonCallBack(void)
{
    uint16_t i = (uint16_t)(m_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
    if (i != m_rx_buffer_tail) {
        m_rx_buffer[m_rx_buffer_head] = rev_char;
        m_rx_buffer_head = i;
    }

    if (m_serial_cb) {
        m_serial_cb();
    }
}

int Serial::available(void)
{
    return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + m_rx_buffer_head - m_rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int Serial::peek(void)
{
    if (m_rx_buffer_head == m_rx_buffer_tail) {
        return -1;
    } else {
        return m_rx_buffer[m_rx_buffer_tail];
    }
}

int Serial::read(void)
{
    if (m_rx_buffer_head == m_rx_buffer_tail) {
        return -1;
    } else {
        unsigned char c = m_rx_buffer[m_rx_buffer_tail];
        m_rx_buffer_tail = (uint16_t)(m_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}

void Serial::flush(void)
{
    m_rx_buffer_head = m_rx_buffer_tail;
}

Serial::Serial()
{
}

Serial::~Serial()
{
}