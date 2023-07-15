#include "lest/lest.hpp"
#include <unistd.h>

#include "embase_buffer.h"
using namespace embase;

const lest::test specification[] =
{
  CASE( "ByteBuffer peekConsequent() test" ) {
    static const size_t BUFSIZE = 8;

    ByteBuffer<BUFSIZE> buffer;

    EXPECT(buffer.readAvailable() == 0);
    EXPECT(buffer.writeAvailable() == BUFSIZE);

    // 1. 写6字节
    const uint8_t testdata_0[] = { 1,2,3,4,5,6 };
    EXPECT(buffer.write(testdata_0, 6) == 6);
    EXPECT(buffer.readAvailable() == 6);
    EXPECT(buffer.writeAvailable() == BUFSIZE - 6);

    // 2. peekConsequent 读6字节
    uint8_t buf[256];
    EXPECT(buffer.peekConsequent(buf, sizeof(buf)) == 6);
    EXPECT(buffer.peekConsequent(buf, sizeof(buf)) == 6);
    EXPECT(buffer.peekConsequent(buf, sizeof(buf)) == 6); // peek几次都一样，不改变内部指针
    EXPECT(buffer.readAvailable() == 6);
    buffer.release(6);
    EXPECT(buffer.readAvailable() == 0);

    // 3. 写6字节，回环写
    EXPECT(buffer.write(testdata_0, 6) == 6);
    EXPECT(buffer.readAvailable() == 6);

    // 4. 调用peekConsequent，第一次读出2字节，不回环
    EXPECT(buffer.peekConsequent(buf, sizeof(buf)) == 2);
    buffer.release(2);
    EXPECT(buffer.readAvailable() == 4);

    // 5. 调用peekConsequent，第二次读出4字节
    EXPECT(buffer.peekConsequent(buf, sizeof(buf)) == 4);
    buffer.release(4);
    EXPECT(buffer.readAvailable() == 0);
    EXPECT(buffer.writeAvailable() == BUFSIZE);
  },

};
int main( int argc, char * argv[] )
{
  return lest::run( specification, argc, argv );
}
