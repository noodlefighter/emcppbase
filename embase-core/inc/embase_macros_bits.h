#pragma once

#include <stdint.h>

/** @brief mask of a bit */
#ifndef BIT
#	define BIT(bit)                    (1 << (bit))
#endif

/** @brief determine whether or not to set */
#ifndef BIT_ISSET
#define BIT_ISSET(data, bit)        ((data) & BIT(bit))
#endif

/** @brief get value of bit */
#ifndef BIT_GET
#define BIT_GET(data, bit)          (BIT_ISSET(data, bit) ? 1 : 0)
#endif

/** @brief set bit */
#ifndef BIT_SET
#define BIT_SET(data, bit)          ((data) |= BIT(bit))
#endif

/** @brief clear bit */
#ifndef BIT_CLR
#define BIT_CLR(data, bit)          ((data) &= ~BIT(bit))
#endif

/** @brief toggle bit */
#ifndef BIT_TOGGLE
#define BIT_TOGGLE(data, bit)       ((data) ^= BIT(bit))
#endif

/** @brief set bits with mask */
#ifndef BIT_SET_MASK
#define BIT_SET_MASK(data, mask)    ((data) |= (mask))
#endif

/** @brief clear bits with mask */
#ifndef BIT_CLR_MASK
#define BIT_CLR_MASK(data, mask)    ((data) &= ~(mask))
#endif

/** @brief clear bits with mask */
#ifndef BIT_TOGGLE_MASK
#define BIT_TOGGLE_MASK(data, mask) ((data) ^= ~(mask))
#endif

/** @brief value bitwise left shift */
#ifndef SBF
#define SBF(value, field)           ((value) << (field))
#endif

/** @brief mark of bits */
#ifndef BITS_MASK
#define BITS_MASK(n)                (~((~0u) << (n)))
#endif

/** @brief get value of bits*/
#ifndef BITS_GET
#define BITS_GET(data, start, len)  (((data) >> (start)) & BITS_MASK(len))
#endif

/** @brief set value of bits */
#ifndef BITS_SET
#define BITS_SET(data, start, len, value)                   \
    ((data) = (((data) & ~SBF(BITS_MASK(len), (start))) |   \
        SBF((value) & (BITS_MASK(len)), (start))))
#endif


#define BIT_REVERSE_U8(v8)			do {\
										(v8) = (((v8) >> 1) & 0x55) | (((v8) << 1) & 0xaa);\
										(v8) = (((v8) >> 2) & 0x33) | (((v8) << 2) & 0xcc);\
										(v8) = (((v8) >> 4) & 0x0f) | (((v8) << 4) & 0xf0);\
									} while (0)
#define BIT_REVERSE_U16(v16)		do {\
										(v16) = (((v16) >> 1) & 0x5555) | (((v16) << 1) & 0xaaaa);\
										(v16) = (((v16) >> 2) & 0x3333) | (((v16) << 2) & 0xcccc);\
										(v16) = (((v16) >> 4) & 0x0f0f) | (((v16) << 4) & 0xf0f0);\
										(v16) = (((v16) >> 8) & 0x00ff) | (((v16) << 8) & 0xff00);\
									} while (0)
#define BIT_REVERSE_U32(v32)		do {\
										(v32) = (((v32) >> 1) & 0x55555555ul) | (((v32) << 1) & 0xaaaaaaaaul);\
										(v32) = (((v32) >> 2) & 0x33333333ul) | (((v32) << 2) & 0xccccccccul);\
										(v32) = (((v32) >> 4) & 0x0f0f0f0ful) | (((v32) << 4) & 0xf0f0f0f0ul);\
										(v32) = (((v32) >> 8) & 0x00ff00fful) | (((v32) << 8) & 0xff00ff00ul);\
										(v32) = (((v32) >> 16)& 0x0000fffful) | (((v32) << 16)& 0xffff0000ul);\
									} while (0)
#define BIT_REVERSE_U64(v64)		do {\
										(v64) = (((v64) >> 1) & 0x5555555555555555ull) | (((v64) << 1) & 0xaaaaaaaaaaaaaaaaull);\
										(v64) = (((v64) >> 2) & 0x3333333333333333ull) | (((v64) << 2) & 0xccccccccccccccccull);\
										(v64) = (((v64) >> 4) & 0x0f0f0f0f0f0f0f0full) | (((v64) << 4) & 0xf0f0f0f0f0f0f0f0ull);\
										(v64) = (((v64) >> 8) & 0x00ff00ff00ff00ffull) | (((v64) << 8) & 0xff00ff00ff00ff00ull);\
										(v64) = (((v64) >> 16)& 0x0000ffff0000ffffull) | (((v64) << 16)& 0xffff0000ffff0000ull);\
										(v64) = (((v64) >> 1) & 0x00000000ffffffffull) | (((v64) << 1) & 0xffffffff00000000ull);\
									} while (0)

#define GET_U16_MSBFIRST(p)			(	((uint16_t)(*((uint8_t *)(p) + 0)) << 8) | \
										((uint16_t)(*((uint8_t *)(p) + 1)) << 0))
#define GET_U24_MSBFIRST(p)			(	((uint32_t)(*((uint8_t *)(p) + 0)) << 16) | \
										((uint32_t)(*((uint8_t *)(p) + 1)) << 8) | \
										((uint32_t)(*((uint8_t *)(p) + 2)) << 0))
#define GET_U32_MSBFIRST(p)			(	((uint32_t)(*((uint8_t *)(p) + 0)) << 24) | \
										((uint32_t)(*((uint8_t *)(p) + 1)) << 16) | \
										((uint32_t)(*((uint8_t *)(p) + 2)) << 8) | \
										((uint32_t)(*((uint8_t *)(p) + 3)) << 0))
#define GET_U64_MSBFIRST(p)			(	((uint64_t)(*((uint8_t *)(p) + 0)) << 56) | \
										((uint64_t)(*((uint8_t *)(p) + 1)) << 48) | \
										((uint64_t)(*((uint8_t *)(p) + 2)) << 40) | \
										((uint64_t)(*((uint8_t *)(p) + 3)) << 32) |\
										((uint64_t)(*((uint8_t *)(p) + 4)) << 24) | \
										((uint64_t)(*((uint8_t *)(p) + 5)) << 16) | \
										((uint64_t)(*((uint8_t *)(p) + 6)) << 8) | \
										((uint64_t)(*((uint8_t *)(p) + 7)) << 0))
#define GET_U16_LSBFIRST(p)			(	((uint16_t)(*((uint8_t *)(p) + 0)) << 0) | \
										((uint16_t)(*((uint8_t *)(p) + 1)) << 8))
#define GET_U24_LSBFIRST(p)			(	((uint32_t)(*((uint8_t *)(p) + 0)) << 0) | \
										((uint32_t)(*((uint8_t *)(p) + 1)) << 8) | \
										((uint32_t)(*((uint8_t *)(p) + 2)) << 16))
#define GET_U32_LSBFIRST(p)			(	((uint32_t)(*((uint8_t *)(p) + 0)) << 0) | \
										((uint32_t)(*((uint8_t *)(p) + 1)) << 8) | \
										((uint32_t)(*((uint8_t *)(p) + 2)) << 16) | \
										((uint32_t)(*((uint8_t *)(p) + 3)) << 24))
#define GET_U64_LSBFIRST(p)			(	((uint64_t)(*((uint8_t *)(p) + 0)) << 0) | \
										((uint64_t)(*((uint8_t *)(p) + 1)) << 8) | \
										((uint64_t)(*((uint8_t *)(p) + 2)) << 16) | \
										((uint64_t)(*((uint8_t *)(p) + 3)) << 24) |\
										((uint64_t)(*((uint8_t *)(p) + 4)) << 32) | \
										((uint64_t)(*((uint8_t *)(p) + 5)) << 40) | \
										((uint64_t)(*((uint8_t *)(p) + 6)) << 48) | \
										((uint64_t)(*((uint8_t *)(p) + 7)) << 56))

#define SET_U16_MSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint16_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint16_t)(v)) >> 0) & 0xFF;\
	} while (0)
#define SET_U24_MSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint32_t)(v)) >> 16) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint32_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint32_t)(v)) >> 0) & 0xFF;\
	} while (0)
#define SET_U32_MSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint32_t)(v)) >> 24) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint32_t)(v)) >> 16) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint32_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 3) = (((uint32_t)(v)) >> 0) & 0xFF;\
	} while (0)
#define SET_U64_MSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint64_t)(v)) >> 56) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint64_t)(v)) >> 48) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint64_t)(v)) >> 40) & 0xFF;\
		*((uint8_t *)(p) + 3) = (((uint64_t)(v)) >> 32) & 0xFF;\
		*((uint8_t *)(p) + 4) = (((uint64_t)(v)) >> 24) & 0xFF;\
		*((uint8_t *)(p) + 5) = (((uint64_t)(v)) >> 16) & 0xFF;\
		*((uint8_t *)(p) + 6) = (((uint64_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 7) = (((uint64_t)(v)) >> 0) & 0xFF;\
	} while (0)
#define SET_U16_LSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint16_t)(v)) >> 0) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint16_t)(v)) >> 8) & 0xFF;\
	} while (0)
#define SET_U24_LSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint32_t)(v)) >> 0) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint32_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint32_t)(v)) >> 16) & 0xFF;\
	} while (0)
#define SET_U32_LSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint32_t)(v)) >> 0) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint32_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint32_t)(v)) >> 16) & 0xFF;\
		*((uint8_t *)(p) + 3) = (((uint32_t)(v)) >> 24) & 0xFF;\
	} while (0)
#define SET_U64_LSBFIRST(p, v)		\
	do{\
		*((uint8_t *)(p) + 0) = (((uint64_t)(v)) >> 0) & 0xFF;\
		*((uint8_t *)(p) + 1) = (((uint64_t)(v)) >> 8) & 0xFF;\
		*((uint8_t *)(p) + 2) = (((uint64_t)(v)) >> 16) & 0xFF;\
		*((uint8_t *)(p) + 3) = (((uint64_t)(v)) >> 24) & 0xFF;\
		*((uint8_t *)(p) + 4) = (((uint64_t)(v)) >> 32) & 0xFF;\
		*((uint8_t *)(p) + 5) = (((uint64_t)(v)) >> 40) & 0xFF;\
		*((uint8_t *)(p) + 6) = (((uint64_t)(v)) >> 48) & 0xFF;\
		*((uint8_t *)(p) + 7) = (((uint64_t)(v)) >> 56) & 0xFF;\
	} while (0)

#define GET_LE_U16(p)				GET_U16_LSBFIRST(p)
#define GET_LE_U24(p)				GET_U24_LSBFIRST(p)
#define GET_LE_U32(p)				GET_U32_LSBFIRST(p)
#define GET_LE_U64(p)				GET_U64_LSBFIRST(p)
#define GET_BE_U16(p)				GET_U16_MSBFIRST(p)
#define GET_BE_U24(p)				GET_U24_MSBFIRST(p)
#define GET_BE_U32(p)				GET_U32_MSBFIRST(p)
#define GET_BE_U64(p)				GET_U64_MSBFIRST(p)
#define SET_LE_U16(p, v)			SET_U16_LSBFIRST(p, v)
#define SET_LE_U24(p, v)			SET_U24_LSBFIRST(p, v)
#define SET_LE_U32(p, v)			SET_U32_LSBFIRST(p, v)
#define SET_LE_U64(p, v)			SET_U64_LSBFIRST(p, v)
#define SET_BE_U16(p, v)			SET_U16_MSBFIRST(p, v)
#define SET_BE_U24(p, v)			SET_U24_MSBFIRST(p, v)
#define SET_BE_U32(p, v)			SET_U32_MSBFIRST(p, v)
#define SET_BE_U64(p, v)			SET_U64_MSBFIRST(p, v)

#define SWAP_U16(v)					(	(((uint16_t)(v) & 0xFF00) >> 8) | \
										(((uint16_t)(v) & 0x00FF) << 8))
#define SWAP_U24(v)					(	(((uint32_t)(v) & 0x00FF0000ul) >> 16) | \
										(((uint32_t)(v) & 0x0000FF00ul) << 0) | \
										(((uint32_t)(v) & 0x000000FFul) << 16))
#define SWAP_U32(v)					(	(((uint32_t)(v) & 0xFF000000ul) >> 24) | \
										(((uint32_t)(v) & 0x00FF0000ul) >> 8) | \
										(((uint32_t)(v) & 0x0000FF00ul) << 8) | \
										(((uint32_t)(v) & 0x000000FFul) << 24))
#define SWAP_U64(v)					(	(((uint64_t)(v) & 0xFF00000000000000ull) >> 56) | \
										(((uint64_t)(v) & 0x00FF000000000000ull) >> 40) | \
										(((uint64_t)(v) & 0x0000FF0000000000ull) >> 24) | \
										(((uint64_t)(v) & 0x000000FF00000000ull) >> 8) | \
										(((uint64_t)(v) & 0x00000000FF000000ull) << 8) | \
										(((uint64_t)(v) & 0x0000000000FF0000ull) << 24) | \
										(((uint64_t)(v) & 0x000000000000FF00ull) << 40) | \
										(((uint64_t)(v) & 0x00000000000000FFull) << 56))

#if defined(__BIG_ENDIAN__) && (__BIG_ENDIAN__ == 1)
#	define LE_TO_SYS_U16(v)			SWAP_U16(v)
#	define LE_TO_SYS_U24(v)			SWAP_U24(v)
#	define LE_TO_SYS_U32(v)			SWAP_U32(v)
#	define LE_TO_SYS_U64(v)			SWAP_U64(v)
#	define BE_TO_SYS_U16(v)			((uint16_t)(v))
#	define BE_TO_SYS_U24(v)			((uint32_t)(v))
#	define BE_TO_SYS_U32(v)			((uint32_t)(v))
#	define BE_TO_SYS_U64(v)			((uint64_t)(v))

#	define SYS_TO_LE_U16(v)			SWAP_U16(v)
#	define SYS_TO_LE_U24(v)			SWAP_U24(v)
#	define SYS_TO_LE_U32(v)			SWAP_U32(v)
#	define SYS_TO_LE_U64(v)			SWAP_U64(v)
#	define SYS_TO_BE_U16(v)			((uint16_t)(v))
#	define SYS_TO_BE_U24(v)			((uint32_t)(v))
#	define SYS_TO_BE_U32(v)			((uint32_t)(v))
#	define SYS_TO_BE_U64(v)			((uint64_t)(v))

#	define SET_SYS_U16(p, v)		SET_BE_U16(p, v)
#	define SET_SYS_U24(p, v)		SET_BE_U24(p, v)
#	define SET_SYS_U32(p, v)		SET_BE_U32(p, v)
#	define SET_SYS_U64(p, v)		SET_BE_U64(p, v)
#	define GET_SYS_U16(p)			GET_BE_U16(p)
#	define GET_SYS_U24(p)			GET_BE_U24(p)
#	define GET_SYS_U32(p)			GET_BE_U32(p)
#	define GET_SYS_U64(p)			GET_BE_U64(p)
#else
#	define LE_TO_SYS_U16(v)			((uint16_t)(v))
#	define LE_TO_SYS_U24(v)			((uint32_t)(v))
#	define LE_TO_SYS_U32(v)			((uint32_t)(v))
#	define LE_TO_SYS_U64(v)			((uint64_t)(v))
#	define BE_TO_SYS_U16(v)			SWAP_U16(v)
#	define BE_TO_SYS_U24(v)			SWAP_U24(v)
#	define BE_TO_SYS_U32(v)			SWAP_U32(v)
#	define BE_TO_SYS_U64(v)			SWAP_U64(v)

#	define SYS_TO_LE_U16(v)			((uint16_t)(v))
#	define SYS_TO_LE_U24(v)			((uint32_t)(v))
#	define SYS_TO_LE_U32(v)			((uint32_t)(v))
#	define SYS_TO_LE_U64(v)			((uint64_t)(v))
#	define SYS_TO_BE_U16(v)			SWAP_U16(v)
#	define SYS_TO_BE_U24(v)			SWAP_U24(v)
#	define SYS_TO_BE_U32(v)			SWAP_U32(v)
#	define SYS_TO_BE_U64(v)			SWAP_U64(v)

#	define SET_SYS_U16(p, v)		SET_LE_U16(p, v)
#	define SET_SYS_U24(p, v)		SET_LE_U24(p, v)
#	define SET_SYS_U32(p, v)		SET_LE_U32(p, v)
#	define SET_SYS_U64(p, v)		SET_LE_U64(p, v)
#	define GET_SYS_U16(p)			GET_LE_U16(p)
#	define GET_SYS_U24(p)			GET_LE_U24(p)
#	define GET_SYS_U32(p)			GET_LE_U32(p)
#	define GET_SYS_U64(p)			GET_LE_U64(p)
#endif

