// originator: Ming180

#pragma once

#include "embase_types.h"
#include <string.h>

namespace embase {

template<std::size_t MAX_SIZE_>
class ByteBuffer {
public:
  static const std::size_t MAX_SIZE = MAX_SIZE_;

	ByteBuffer() : _bytes(0), _head(0), _capacity(MAX_SIZE_)
	{
	}

  void clear() {
	  _bytes = _head = 0;
  }
  uint32_t readAvailable() {
    return _bytes;
  }
  uint32_t writeAvailable() {
    return _capacity - _bytes;
  }
  uint32_t write(const uint8_t *data, uint32_t size);

  uint32_t peekConsequent(uint8_t *data, uint32_t size); // 非回环peek
  uint32_t release(uint32_t size);

private:
	uint32_t _bytes;
	uint32_t _head;
	uint32_t _capacity;
	uint8_t  _buff[MAX_SIZE];
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

template<std::size_t MAX_SIZE_>
uint32_t ByteBuffer<MAX_SIZE_>::peekConsequent(uint8_t *data, uint32_t size)
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
