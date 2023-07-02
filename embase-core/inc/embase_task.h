#pragma once

#include "embase_def.h"
#include "embase_platform.h"
#include "embase_thread.h"
#include "etl/task.h"
#include "etl/scheduler.h"
#include <type_traits>

namespace embase {

class IntervalTask : public etl::task {
public:
  const uint32_t DEFAULT_INTERVAL = 1000;

  IntervalTask(etl::task_priority_t priority)
    : task(priority), _interval(DEFAULT_INTERVAL)
  {
  }

  void setTaskInterval(uint32_t ms) {
    _interval = ms;
  }
  uint32_t task_request_work() const override {
    return embase::__get_sys_timestamp() - _lastStamp >= _interval;
  }

  virtual void intervalRun() = 0;

  void task_process_work() override {
    if (embase::__get_sys_timestamp() - _lastStamp >= _interval) {
      _lastStamp = embase::__get_sys_timestamp();
      intervalRun();
    }
  }

private:
  uint32_t _interval;
  embase::TimeStamp_t _lastStamp;
};

// note: fork from etl::scheduler
template <typename TSchedulerPolicy, size_t MAX_TASKS_>
class TaskScheduler : public etl::ischeduler, protected TSchedulerPolicy
{
public:
  enum
  {
    MAX_TASKS = MAX_TASKS_,
  };

  TaskScheduler()
    : ischeduler(task_list)
  {
  }

  //*******************************************
  /// Start the scheduler.
  //*******************************************
  void start()
  {
    ETL_ASSERT(task_list.size() > 0, ETL_ERROR(etl::scheduler_no_tasks_exception));

    scheduler_running = true;

    while (!scheduler_exit)
    {
      if (scheduler_running)
      {
        bool idle = TSchedulerPolicy::schedule_tasks(task_list);

        if (p_watchdog_callback)
        {
          (*p_watchdog_callback)();
        }

        if (idle && p_idle_callback)
        {
          (*p_idle_callback)();
        }
      }
    }
  }

  void start_noblock()
  {
    bool idle = TSchedulerPolicy::schedule_tasks(task_list);

    if (p_watchdog_callback)
    {
      (*p_watchdog_callback)();
    }

    if (idle && p_idle_callback)
    {
      (*p_idle_callback)();
    }
  }

private:

  typedef etl::vector<etl::task*, MAX_TASKS> task_list_t;
  task_list_t task_list;
};

template <typename Tscheduler>
class SchedulerWithThread : public Tscheduler, private embase::Thread
{
public:
  // static_assert(std::is_base_of_v<etl::scheduler, Tscheduler>, "must be child class of etl::scheduler");

  bool startScheduling() {
    return Thread::start();
  }
  void stopScheduling() {
    Tscheduler::exit_scheduler();
    Thread::join();
  }

private:
  int run() override {
    Tscheduler::start();
    return 0;
  }
};


}
