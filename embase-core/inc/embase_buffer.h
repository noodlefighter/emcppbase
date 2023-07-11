// originator: Ming180

#pragma once

#include "embase_types.h"

namespace embase {

template<std::size_t MAX_SIZE_>
class ByteBuffer {
public:
  static const std::size_t MAX_SIZE = MAX_SIZE_;

  void clear() {
	  _num_items = _head = 0;
  }
  uint32_t readAvailable() {
    return _num_items;
  }
  uint32_t writeAvailable() {
    return _size - _num_items;
  }
  uint32_t write(uint8_t *data, uint32_t size);

  uint32_t peekConsequent(uint8_t *data, uint32_t size); // 非回环peek
  uint32_t release(uint32_t size);

private:
	uint32_t _num_items;
	uint32_t _head;
	uint32_t _size;
	uint8_t  _buff[MAX_SIZE];
};


template<std::size_t MAX_SIZE_>
uint32_t ByteBuffer<MAX_SIZE_>::write(uint8_t *data, uint32_t size)
{
	uint32_t tail, temp;

	if (size <= _size - _num_items) {

		// determine position of new item
		tail = _head + _num_items;

		if (tail >= _size) {
			tail -= _size;
		}

		temp = _size - tail;
		if (size < temp) {
			memcpy(&_buff[tail], data, size);
		}
		else {
			memcpy(&_buff[tail], &data[0]   , temp);
			memcpy(&_buff[0]   , &data[temp], size - temp);
		}

		_num_items += size;
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
	if (size > _num_items) {
		size = _num_items;
	}

	// 缓冲边界检测
	tail = _head + _num_items;
	if (tail > _size) {
		temp = _size - _head;

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

	if (size > _num_items) {
		size = _num_items;
	}

	// increment to next point
	_head += size;
	if (_head >= _size) {
		_head -= _size;
	}

	_num_items -= size;

	return size;
}

};
