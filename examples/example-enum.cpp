#include "embase_log.h"
#include "enum.h"

BETTER_ENUM(EthernetProto_t, int, STATIC, DHCP);

int main()
{
  const char *str;
  better_enums::optional<EthernetProto_t> c;

  str = "static";
  c = EthernetProto_t::_from_string_nothrow(str);
  assert(!c);

  str = "static";
  c = EthernetProto_t::_from_string_nocase_nothrow(str);
  assert(c);

  EthernetProto_t val = c.value();
  g_default_logger.info(" %d-->%s", (int)val, val._to_string());
  return 0;
}
