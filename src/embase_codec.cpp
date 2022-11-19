#include "embase_codec.h"

using namespace embase;

std::string __bcd_bytes_to_string(const embase::BYTE *bytes, size_t len)
{
  std::string tmp(len*2, '0');
  for (size_t i = 0; i < len; i++)
  {
    BYTE c = bytes[i];
    tmp[i * 2] = (c >> 4) + '0';
    tmp[i * 2 + 1] = (c & 0x0F) + '0';
  }
  return tmp;
}

size_t __bcd_bytes_from_string(embase::BYTE *buf, size_t bufsize, const std::string &bcd_str)
{
  size_t i;
  size_t strlen = bcd_str.size();
  for (i = 0; i < bufsize; i++)
  {
    int idx1 = i * 2;
    int idx2 = i * 2 + 1;
    char c1 = strlen > (size_t)idx1 ? ((bcd_str[idx1] - '0') & 0xF) : 0;
    char c2 = strlen > (size_t)idx2 ? ((bcd_str[idx2] - '0') & 0xF) : 0;
    buf[i] = (c1 << 4) | c2;
  }
  return i;
}

void __bcd_bytes_to_num(UINT8 *dest, const UINT8 *src, int size)
{
  for (int i = 0; i < size; i++)
  {
    dest[i] = (src[i] & 0xF) + ((src[i] & 0xF0) >> 4)*10;
  }
}

int __mjd_to_day(int mjd)
{
  int y1, m1;
  y1 = (int)(((float)mjd - 15078.2) / 365.25);
  m1 = (int)(((float)mjd - 14956.1 - (int)((float)y1 * 365.25)) / 30.6001);
  return (mjd - 14956 - (int)((float)y1 * 365.25) - (int)((float)m1 * 30.6001));
}
int __mjd_to_month(int mjd)
{
  int y1, m1, k;
  y1 = (int)(((float)mjd - 15078.2) / 365.25);
  m1 = (int)(((float)mjd - 14956.1 - (int)((float)y1 * 365.25)) / 30.6001);
  k = 0;
  if ((y1 == 14) || (y1 == 15))
    k = 1;
  return (m1 - 1 - k * 12);
}
int __mjd_to_year(int mjd)
{
  int y1, m1, k;
  y1 = (int)(((float)mjd - 15078.2) / 365.25);
  m1 = (int)(((float)mjd - 14956.1 - (int)((float)y1 * 365.25)) / 30.6001);
  k = 0;
  if ((y1 == 14) || (y1 == 15))
    k = 1;
  return (y1 + k);
}
