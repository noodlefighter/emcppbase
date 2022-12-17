#include "embase_platform.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace embase {

void __msleep(UINT32 v) {
  vTaskDelay(v / portTICK_RATE_MS);
}

}
