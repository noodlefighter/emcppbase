#pragma once

#include "etl/scheduler.h"

namespace embase {


class Task {
public:
  virtual void loop();
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

}
