// originator: Ming180

#pragma once

#include "embase_types.h"
#include "embase_macros.h"
#include <string.h>

namespace embase {

template<std::size_t MAX_SIZE_>
class ByteBuffer {
public:
	static const std::size_t MAX_SIZE = MAX_SIZE_;

	ByteBuffer()
	{
	}

	void clear() {
		_bytes = _head = 0;
	}
	uint32_t readAvailable() const {
		return _bytes;
	}
	uint32_t writeAvailable() const {
		return _capacity - _bytes;
	}

	// 写入数据
	uint32_t write(const uint8_t *data, uint32_t size);
	// 读出数据
	uint32_t read(uint8_t *data, uint32_t size);

	// 另一种读出数据的方法，但不支持回环读，即不一定能一次读出readAvailable()个字节，读之后需要release()释放
	uint32_t peekConsequent(uint8_t *data, uint32_t size) const;
	uint32_t release(uint32_t size);

private:
	uint32_t _bytes = 0;
	uint32_t _head = 0;
	uint32_t _capacity = MAX_SIZE_;
	uint8_t _buff[MAX_SIZE];
};


template<std::size_t MAX_SIZE_>
uint32_t ByteBuffer<MAX_SIZE_>::write(const uint8_t *data, uint32_t size)
{
	uint32_t tail, temp;

	if (size <= _capacity - _bytes) {

		// determine position of new item
		tail = _head + _bytes;

		if (tail >= _capacity) {
			tail -= _capacity;
		}

		temp = _capacity - tail;
		if (size < temp) {
			memcpy(&_buff[tail], data, size);
		}
		else {
			memcpy(&_buff[tail], &data[0]   , temp);
			memcpy(&_buff[0]   , &data[temp], size - temp);
		}

		_bytes += size;
	}
	else {
		size = 0;
	}

	return size;
}

template <std::size_t MAX_SIZE_>
inline uint32_t ByteBuffer<MAX_SIZE_>::read(uint8_t *data, uint32_t size)
{
	uint32_t n = 0;

	// 此次peek能读出的最大字节数
	size = (readAvailable() < size) ? readAvailable() : size;
	// 先读出一次，如果完整则直接返回，不完整则再读一次
	n = peekConsequent(data, size);
	release(n);
	if (n != size) {
		int n2 = peekConsequent(data + n, size - n);
		release(n2);
		n += n2;
	}
	EM_ASSERT(n == size, "");
	return n;
}

template <std::size_t MAX_SIZE_>
uint32_t ByteBuffer<MAX_SIZE_>::peekConsequent(uint8_t *data, uint32_t size) const
{
	uint32_t tail, temp;

	// 从队列中获取连续的数据，不回环
	if (size > _bytes) {
		size = _bytes;
	}

	// 缓冲边界检测
	tail = _head + _bytes;
	if (tail > _capacity) {
		temp = _capacity - _head;

		if (size > temp) {
			size = temp;
		}
	}

	memcpy(data, &_buff[_head], size);
	return size;
}

template<std::size_t MAX_SIZE_>
uint32_t ByteBuffer<MAX_SIZE_>::release(uint32_t size)
{
	// 从队列中获取连续的数据，不回环

	if (size > _bytes) {
		size = _bytes;
	}

	// increment to next point
	_head += size;
	if (_head >= _capacity) {
		_head -= _capacity;
	}

	_bytes -= size;

	return size;
}

};
