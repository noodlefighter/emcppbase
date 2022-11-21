#include "embase_log.h"

int main(int argc, char const *argv[])
{
  embase::Logger logger("test");

  logger.info("info!!");
  logger.debug("debug!! !!!!!should not print this!!!!!");

  logger.setLv(EMBASE_LOG_LV_DEBUG);
  logger.debug("debug!!");

  return 0;
}
