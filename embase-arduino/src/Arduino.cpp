#include "Arduino.h"
#include "embase_platform.h"


extern "C" {

uint32_t millis(void)
{
  return embase::__get_systick_ms();
}

uint32_t micros(void)
{
  return embase::__get_systick_us();
}

void delay(unsigned long ms)
{
  embase::__msleep(ms);
}

void delayMicroseconds(unsigned int us)
{
  embase::__usleep(us);
}

} // extern "C" {
