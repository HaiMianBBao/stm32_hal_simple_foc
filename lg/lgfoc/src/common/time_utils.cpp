#include "time_utils.h"
#include "port_foc.h"
// function buffering delay()
// arduino uno function doesn't work well with interrupts
void _delay(unsigned long ms)
{
  delay(ms);
}

// function buffering _micros()
// arduino function doesn't work well with interrupts
unsigned long _micros()
{
  // regular micros
  return micros();
}
