#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* This is for LLP64 systems.
 * See http://wiki.osdev.org/X86-64#Data_Types
 */

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef unsigned long size_t;

#ifdef __cplusplus
}
#endif

#endif
