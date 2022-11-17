
#include <map>
#include <string>
#include <stdio.h>

enum class EthernetProto_t{
  NONE,
  MIN = 1,
  STATIC = MIN,
  DHCP,
  MAX = DHCP,
};
typedef std::map<std::string,EthernetProto_t> EthProtoMap_t;
const EthProtoMap_t EthProtoMap = {
  {"static",EthernetProto_t::STATIC},
  {"dhcp",EthernetProto_t::DHCP},
};

template <typename enumType_>
std::string enum2str(enumType_ a, std::map<std::string, enumType_> map)
{
  if ((a > enumType_::MAX) || (a < enumType_::MIN)) {
    return std::string();
  }
  for (std::map<std::string,enumType_>::const_iterator itr = map.begin(); itr != map.end(); itr++) {
    if (itr->second == a) {
      return itr->first;
    }
  }
  return std::string();
}

template <typename enumType_>
enumType_ str2enum(const std::string &a, std::map<std::string, enumType_> map)
{
  for (std::map<std::string,enumType_>::const_iterator itr = map.begin(); itr != map.end(); itr++) {
    if (itr->first == a) {
      return itr->second;
    }
  }
  return enumType_::NONE;
}

int main()
{
  printf("[%d]-->%s", (int)EthernetProto_t::DHCP, enum2str<EthernetProto_t>(EthernetProto_t::DHCP, EthProtoMap).c_str());
  printf("[%s]-->%d", "dhcp", (int)str2enum<EthernetProto_t>("dhcp", EthProtoMap));
  return 0;
}
