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
#include "example_main.h"

__attribute__((weak)) void loop(void)
{
    Serial.printf("This is loop function template\r\n");
    _delay(1000);
}

__attribute__((weak)) void setup(void)
{
    Serial.begin(0);
    Serial.printf("This is setup function template\r\n");
}

int example_main(void)
{
    setup();
    while (1) {
        loop();
    }
}