#include "embase_thread.h"
#include <stdio.h>
#include <unistd.h>

using namespace embase;

class MyThread : public embase::Thread {
public:
  BOOL init() {
    _cnt = 0;
    start();
    return TRUE;
  }

  int run() override {
    while (1) {
      msleep(100);
      printf("run!\n");
      _cnt++;
      if (_cnt >= 20) {
        break;
      }
    }
    return 0;
  }
private:
  int _cnt;
};

int main()
{
  MyThread thread;

  thread.init();
  thread.join();

  return 0;
}
