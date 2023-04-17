#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/* ---------------------------- C Scope --------------------------- */
#include "port_foc.h"
#ifdef __cplusplus
}
/* ---------------------------- C++ Scope --------------------------- */
#include "Serial.h"
class SerialUart : public Serial {
private:
    typedef void (*USART_CallbackFunction_t)(void);
    UART_HandleTypeDef *huart;
    bool is_start = false;
public:
    SerialUart();
    ~SerialUart();
    SerialUart(UART_HandleTypeDef *huart);
    void begin(uint32_t baudRate);
    void end(void);
    size_t write(uint8_t n);
};

extern SerialUart Serial;

#endif