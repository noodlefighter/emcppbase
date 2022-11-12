#include "embase_thread.h"
#include "embase_log.h"
#include <unistd.h>

EmbaseThread::EmbaseThread()
{
  pthread_mutex_init(&_mutex, NULL);
  pthread_cond_init(&_cond, NULL);
  _thread = 0;
}

EmbaseThread::~EmbaseThread(){
  pthread_mutex_destroy(&_mutex);
  pthread_cond_destroy(&_cond);
}

void EmbaseThread::lock()
{
  pthread_mutex_lock(&_mutex);
}

void EmbaseThread::unlock()
{
  pthread_mutex_unlock(&_mutex);
}

void EmbaseThread::msleep(mseconds_t ms)
{
  ::usleep(ms * 1000);
}

void EmbaseThread::wait(){
  pthread_cond_wait(&_cond,&_mutex);
}

void EmbaseThread::signal(){
  pthread_cond_signal(&_cond);
}

void EmbaseThread::broadcast(){
  pthread_cond_broadcast(&_cond);
}

void EmbaseThread::run(){
  // C_LOG("%s","EmbaseThread::run");
}

BOOL EmbaseThread::start(){
  thread_t thread;
  pthread_create(&thread,NULL,_thread_t<EmbaseThread,&EmbaseThread::run>,this);
  _thread = thread;
  return TRUE;
}

int EmbaseThread::cancel(){
  return pthread_cancel(_thread);
}

void EmbaseThread::join(){
  pthread_join(_thread, NULL);
}
