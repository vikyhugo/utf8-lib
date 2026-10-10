#ifndef UTF8_LIB_H
#define UTF8_LIB_H

#include <stdio.h>
#include <stdint.h>

#define UNICODECODEPT_EOF 0xFFFFFFFF

typedef uint32_t unicodeCodePt;

unicodeCodePt nextCodePt(FILE *handle);

#endif

#ifndef UTF8_LIB_H_INTERNALS_INCLUDED
#ifdef UTF8_LIB_H_INTERNALS
#define UTF8_LIB_H_INTERNALS_INCLUDED

#include <stdbool.h>

bool validateContinuationByte(uint8_t b);

#endif
#endif
