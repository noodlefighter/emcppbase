#include "embase_types.h"
#include "etl/string.h"
#include <string>
#include <stddef.h>

namespace embase {

// BCD Code
std::string __bcd_bytes_to_string(const embase::BYTE *bytes, size_t len);
size_t __bcd_bytes_from_string(embase::BYTE *buf, size_t bufsize, const std::string &bcd_str);

void __bcd_bytes_to_num(UINT8 *dest, const UINT8 *src, int size); // example: UINT8[]{0x13,0x50,0x02} -> UINT8[]{13,50,2}

// MJD Code
int __mjd_to_day(int mjd);
int __mjd_to_month(int mjd);
int __mjd_to_year(int mjd);

// 数据转十六进制字符串
// space 每个数据间的空格个数
// col 几个数据换一次行，为0不换行
bool __bytes_to_hex_string(const embase::BYTE *bytes, size_t size, int space, int col, etl::istring &out);

}
