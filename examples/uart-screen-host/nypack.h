#pragma once

#include "crc.h"

#include <string.h>
#include <stdint.h>
#include <stddef.h>

struct nypack_parser {
	// private
	uint8_t *m_buffer;
	size_t   m_bufsize;
	int      m_step;
	int      m_offset;
	uint16_t m_packet_len;
	uint16_t m_crc;

	// parser results
	int      type;
	uint8_t *payload;
	size_t   payload_len;
};

typedef enum {
	NYPACK_PARSER_EVT_NO,
	NYPACK_PARSER_EVT_DONE,
	NYPACK_PARSER_EVT_ERR_BUFFSIZE,
	NYPACK_PARSER_EVT_ERR_CRC_FAIL,
} nypack_parser_evt_t;

#define NYPACK_PARSER_INIT(buffer, bufsize)  { \
	.m_buffer  = buffer, \
	.m_bufsize = bufsize, \
}

#define NYPACK_HEAD_BYTE1		0x23u
#define NYPACK_HEAD_BYTE2		0x3Eu

// head(2) | length(2) | type(1) | payload(n) | crc(2)
enum {
	NYPACK_HEAD_OFFSET = 0,
	NYPACK_LENGTH_OFFSET = 2,
	NYPACK_TYPE_OFFSET = 4,
	NYPACK_DATA_OFFSET = 5,
};
#define NYPACK_PACKET_SIZE(payload_len)	  (NYPACK_DATA_OFFSET + payload_len + 2)
#define NYPACK_CRC_OFFSET(packet_len)     (packet_len - 3)
#define NYPACK_PAYLOAD_SIZE(packet_len)	  (packet_len - NYPACK_DATA_OFFSET - 2)

static inline
int nypack_generate(const uint8_t *payload, size_t payload_len, uint8_t *buffer, size_t buffer_size, uint8_t type, size_t *out_len)
{
	int crc_offset;
	size_t pack_len = NYPACK_PACKET_SIZE(payload_len);
    if (buffer_size < pack_len) { // note: crc16 2 bytes
        return -1;
    }

#define SET_U16_LSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint16_t)(v)) >> 0) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint16_t)(v)) >> 8) & 0xFF;\
	} while (0)

	memmove(buffer + NYPACK_DATA_OFFSET, payload, payload_len);
	buffer[NYPACK_HEAD_OFFSET] = NYPACK_HEAD_BYTE1;
	buffer[NYPACK_HEAD_OFFSET+1] = NYPACK_HEAD_BYTE2;
	SET_U16_LSBFIRST(buffer + NYPACK_LENGTH_OFFSET, pack_len);
	buffer[NYPACK_TYPE_OFFSET] = type;
	crc_offset = NYPACK_CRC_OFFSET(pack_len);
	SET_U16_LSBFIRST(&buffer[crc_offset], crc_16bits_compute(buffer, crc_offset));
	*out_len = pack_len;
	return 0;
#undef SET_U16_LSBFIRST
}

static inline
nypack_parser_evt_t nypack_parser_byte(struct nypack_parser *obj, uint8_t c)
{
	nypack_parser_evt_t evt = NYPACK_PARSER_EVT_NO;

	switch (obj->m_step) {
	case 0:
		(c == NYPACK_HEAD_BYTE1) ? (obj->m_step++) : (obj->m_step = 0);
		break;
	case 1:
		(c == NYPACK_HEAD_BYTE2) ? (obj->m_step++) : (obj->m_step = 0);
		break;
	case 2:
		obj->m_packet_len = c;
		obj->m_step++;
		break;
	case 3:
		obj->m_packet_len |= (c << 8);
		if ((size_t)obj->m_packet_len > obj->m_bufsize) {
			obj->m_step = 0;
			evt = NYPACK_PARSER_EVT_ERR_BUFFSIZE;
			break;
		}

		obj->m_offset = NYPACK_DATA_OFFSET;
		obj->m_step++;
		break;
	case 4:
		obj->type = c;
		obj->m_step++;
		break;
	case 5:
		obj->m_buffer[obj->m_offset++] = c;
		if (obj->m_offset >= NYPACK_CRC_OFFSET(obj->m_packet_len)) {
			obj->m_step++;
		}
		break;
	case 6:
		obj->m_crc = c;
		obj->m_step++;
		break;
	case 7: {
		uint16_t calc_crc;

		obj->m_crc |= c << 8;
		obj->m_buffer[NYPACK_HEAD_OFFSET]     = NYPACK_HEAD_BYTE1;
		obj->m_buffer[NYPACK_HEAD_OFFSET+1]   = NYPACK_HEAD_BYTE2;
		obj->m_buffer[NYPACK_LENGTH_OFFSET]   = obj->m_packet_len & 0x0F;
		obj->m_buffer[NYPACK_LENGTH_OFFSET+1] = (obj->m_packet_len >> 8) & 0x0F;
		obj->m_buffer[NYPACK_TYPE_OFFSET]     = obj->type;

		calc_crc = crc_16bits_compute(obj->m_buffer, obj->m_offset);
		// printf("m_packet_len=%d, calc_crc=0x%04X, m_crc=0x%04X\n", obj->m_packet_len, calc_crc, obj->m_crc);
		if (obj->m_crc == calc_crc) {
			obj->payload = &obj->m_buffer[NYPACK_DATA_OFFSET];
			obj->payload_len = NYPACK_PAYLOAD_SIZE(obj->m_packet_len);
			evt = NYPACK_PARSER_EVT_DONE;
		}
		else {
			evt = NYPACK_PARSER_EVT_ERR_CRC_FAIL;
		}
		obj->m_step = 0;
		break;
	}
	default:
		obj->m_step = 0;
		break;
	}
	// printf("input=%02X, now step=%d\n", c, obj->m_step);
	return evt;
}
