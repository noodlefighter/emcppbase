/*
 * crc.h
 *
 *  Created on: 2014-3-9
 *      Author: Ming180
 */

#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t crc_16bits_compute(const uint8_t  *ptr, uint32_t size);
uint16_t crc_16bits_update(uint16_t init, uint8_t *ptr, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif // CRC_H_
