#include "embase_thread.h"
#include <stdio.h>
#include <unistd.h>

using namespace Embase;

class MyThread : public Embase::Thread {
public:
  BOOL init() {
    _cnt = 0;
    start();
    return TRUE;
  }

  void run() override {
    while (1) {
      msleep(100);
      printf("run!\n");
      _cnt++;
      if (_cnt >= 20) {
        break;
      }
    }
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
