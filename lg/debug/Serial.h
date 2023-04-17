#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/* ---------------------------- C Scope --------------------------- */
#include <stdint.h>
#include <stddef.h>
#ifdef __cplusplus
}
/* ---------------------------- C++ Scope --------------------------- */
#include "Stream.h"
#ifndef SERIAL_RX_BUFFER_SIZE
#define SERIAL_RX_BUFFER_SIZE 128
#endif

class Serial : public Stream {
private:
    typedef void (*callback)(void);

public:
    virtual void begin(uint32_t paraMeter) = 0;
    virtual size_t write(uint8_t n) = 0;
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual void flush(void);
    void attachInterrupt(callback function);
    void commonCallBack(void);
    uint8_t rev_char;
    inline size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t)n);
    }
    Serial(/* args */);
    ~Serial();

protected:
    volatile uint16_t m_rx_buffer_head;
    volatile uint16_t m_rx_buffer_tail;
    uint8_t m_rx_buffer[SERIAL_RX_BUFFER_SIZE];
    callback m_serial_cb;
};

#endif