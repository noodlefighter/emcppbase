#pragma once

#include "embase_def.h"

namespace Embase{

#if EMBASE_TARGET_PLATFORM == EMBASE_PLATFORM_WIN32


#elif EMBASE_TARGET_PLATFORM == EMBASE_PLATFORM_BAREMETAL

#else
#include <pthread.h>

typedef pthread_t thread_t;
typedef pthread_cond_t cond_t;
typedef pthread_mutex_t mutex_t;

#endif

template <typename TYPE, void (TYPE::*run)() >
void* _thread_t(void* param)//线程启动函数，声明为模板函数
{
  TYPE* This = (TYPE*)param;
  This->run();
  return NULL;
}

class Thread{
protected:
  mutex_t _mutex;
  cond_t _cond;
  thread_t _thread;
public:
  Thread();
  ~Thread();
  virtual void run();
  int cancel();
  void join();
  void lock();
  void unlock();
  void msleep(mseconds_t ms);
  void wait();
  void signal();
  void broadcast();
  BOOL start();
};
}
