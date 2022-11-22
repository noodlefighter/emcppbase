#pragma once

#include "embase_config.h"
#include "embase_def.h"

namespace embase{

#if EMBASE_OS == EMBASE_OS_FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#else
#include <pthread.h>
#endif

template <typename TYPE, int (TYPE::*run)() >
void* _pthread_t(void* param)//线程启动函数，声明为模板函数
{
  TYPE* This = (TYPE*)param;
  This->run();
  return NULL;
}

class Thread{
public:
  Thread();
  ~Thread();
  virtual int run();
  BOOL cancel();
  int join();
  void lock();
  void unlock();
  void msleep(mseconds_t ms);
  void wait();
  void signal();
  void broadcast();
  BOOL start();

private:
#if EMBASE_OS == EMBASE_OS_FREERTOS
  StaticSemaphore_t _mutex;
  StaticSemaphore_t _workingSem;
  int _exitRc;
#else
  pthread_mutex_t _mutex;
  pthread_cond_t _cond;
  pthread_t _thread;
#endif

};
}
