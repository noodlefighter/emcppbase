#include "lest/lest.hpp"
#include <unistd.h>

#include "embase_task.h"

class TestIntervalTask : public embase::IntervalTask {
public:
  TestIntervalTask() : IntervalTask(10)
  {
  }

  void intervalRun() override {
    _calledCount++;
  }

  int getCalledCount() {
    return _calledCount;
  }

private:
  int _calledCount = 0;
};


typedef etl::scheduler<etl::scheduler_policy_sequential_single, 2> SimpleScheduler;
using MyScheduler = embase::SchedulerWithThread<SimpleScheduler>;

const lest::test specification[] =
{
  CASE( "IntervalTask base test" ) {
    MyScheduler scheduler;

    TestIntervalTask task;
    task.setTaskInterval(1000);
    scheduler.add_task(task);

    EXPECT(task.getCalledCount() == 0);
    scheduler.startScheduling();
    sleep(2);
    EXPECT(task.getCalledCount() == 3);

    scheduler.stopScheduling();
  },

};
int main( int argc, char * argv[] )
{
  return lest::run( specification, argc, argv );
}
