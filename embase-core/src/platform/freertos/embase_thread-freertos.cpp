#include "embase_thread.h"
#include "embase_log.h"
#include <unistd.h>

using namespace embase;

Thread::Thread()
{
  xSemaphoreCreateBinaryStatic();
  _thread = 0;
}

Thread::~Thread()
{
}

void Thread::lock()
{
  xSemaphoreTake();
}

void Thread::unlock()
{
  xSemaphoreGive();
}

void Thread::msleep(mseconds_t ms)
{
  vTaskDelay(ms / portTICK_RATE_MS);
}

void Thread::wait()
{
}

int Thread::doRun()
{
  xSemaphoreTake(_workingSem);
  _exitRc = run();
  xSemaphoreGive(_workingSem);
  return _exitRc;
}

BOOL Thread::start()
{
  _thread = xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL); // start doRun()
  return TRUE;
}

BOOL Thread::cancel()
{
#if INCLUDE_vTaskDelete
  vTaskDelete();
  xSemaphoreGive(_workingSem);
  return TRUE;
#else
  return FALSE;
#endif

}

int Thread::join()
{
  xSemaphoreTake(_workingSem);
  xSemaphoreGive(_workingSem);
  return _exitRc;
}
