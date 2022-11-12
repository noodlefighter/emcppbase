#include "embase_thread.h"
#include "embase_log.h"
#include <unistd.h>

using namespace Embase;

Thread::Thread()
{
  pthread_mutex_init(&_mutex, NULL);
  pthread_cond_init(&_cond, NULL);
  _thread = 0;
}

Thread::~Thread(){
  pthread_mutex_destroy(&_mutex);
  pthread_cond_destroy(&_cond);
}

void Thread::lock()
{
  pthread_mutex_lock(&_mutex);
}

void Thread::unlock()
{
  pthread_mutex_unlock(&_mutex);
}

void Thread::msleep(mseconds_t ms)
{
  ::usleep(ms * 1000);
}

void Thread::wait(){
  pthread_cond_wait(&_cond,&_mutex);
}

void Thread::signal(){
  pthread_cond_signal(&_cond);
}

void Thread::broadcast(){
  pthread_cond_broadcast(&_cond);
}

void Thread::run(){
  // C_LOG("%s","Thread::run");
}

BOOL Thread::start(){
  thread_t thread;
  pthread_create(&thread,NULL,_thread_t<Thread,&Thread::run>,this);
  _thread = thread;
  return TRUE;
}

int Thread::cancel(){
  return pthread_cancel(_thread);
}

void Thread::join(){
  pthread_join(_thread, NULL);
}
