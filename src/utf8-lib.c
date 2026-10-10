#define UTF8_LIB_H_INTERNALS
#include "utf8-lib.h"

bool validateContinuationByte(uint8_t b) {
    return ((b & 0b11000000) == 0b10000000);
}

unicodeCodePt nextCodePt(FILE *handle) {
    uint8_t b;
    uint8_t b0, b1, b2, b3;
    unicodeCodePt cp;
    while (true) {
        while (true) {
            if (feof(handle)) {
                return UNICODECODEPT_EOF;
            }
            b = fgetc(handle);
            b0 = b;

            if ((b0 & 0b10000000) == 0b00000000) {
                // 1 byte char
                cp = b0;
                break;
            } else if ((b0 & 0b11100000) == 0b11000000) {
                // 2 byte char
                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b1 = b;

                if (!validateContinuationByte(b1)) {
                    continue;
                }

                cp = (
                    ((b0 & 0b00011111) << 6) |
                    (b1 & 0b00111111)
                    );

                if (cp < (1 << 7)) {
                    // Could fit in 1 byte
                    continue;
                }

                break;
            } else if ((b0 & 0b11110000) == 0b11100000) {
                // 3 byte char
                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b1 = b;

                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b2 = b;

                if (!(validateContinuationByte(b1) && validateContinuationByte(b2))) {
                    continue;
                }

                cp = (
                    ((b0 & 0b00001111) << 12) |
                    ((b1 & 0b00111111) << 6) |
                    (b2 & 0b00111111)
                    );

                if (cp < (1 << 11)) {
                    // Could fit in 2 bytes
                    continue;
                }

                break;
            } else if ((b0 & 0b11111000) == 0b11110000) {
                // 4 byte char
                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b1 = b;

                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b2 = b;

                if (feof(handle)) {
                    return UNICODECODEPT_EOF;
                }
                b = fgetc(handle);
                b3 = b;

                if (!(validateContinuationByte(b1) && validateContinuationByte(b2) && validateContinuationByte(b3))) {
                    continue;
                }

                cp = (
                    ((b0 & 0b00000111) << 18) |
                    ((b1 & 0b00111111) << 12) |
                    ((b2 & 0b00111111) << 6) |
                    (b3 & 0b00111111)
                    );

                if (cp < (1 << 16)) {
                    // Could fit in 3 bytes
                    continue;
                }

                break;
            } else {
                // Not a valid start byte (maybe we're in the middle of a char?)
                continue;
            }
        }
        if ((0xD800 <= cp) && (cp <= 0xDFFF)) {
            // UTF-16 surrogate pair
            continue;
        }
        return cp;
    }
}
