#include "embase_string.h"

#include <stdio.h>



int main()
{
  etl::string<20> str1 = "123";

  if (Embase::__string_startswith(str1, "12")) {
    printf("yes\n");
  }
  else {
    printf("no\n");
  }

  auto str2 = Embase::__string_format<20>("haha %d", 123);

  printf("str2=%s\n", str2.c_str());

  return 0;
}
