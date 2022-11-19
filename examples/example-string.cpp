#include "embase_string.h"

#include <stdio.h>

int main()
{
  etl::string<20> str1 = "123";

  if (embase::__string_startswith(str1, "12")) {
    printf("yes\n");
  }
  else {
    printf("no\n");
  }

  auto str2 = embase::__string_format<20>("haha %d", 123);
  printf("str2=%s\n", str2.c_str());

  const char *split_testdata = "123,456,789,10";
  auto split_res = embase::__string_split<4>(split_testdata, ",");
  printf("split \"%s\"\n", split_testdata);
  for (auto item : split_res) {
    char buf[20];
    memset(buf, 0, sizeof(buf));
    item.copy(buf, item.size());
    printf("\"%s\"\n", buf);
  }
  return 0;
}
