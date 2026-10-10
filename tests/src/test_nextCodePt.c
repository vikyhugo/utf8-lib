#define CP1_TOKENIZER_H_INTERNALS
#include "utf8-lib.h"

#include <inttypes.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *data = fopen(argv[1], "rb");
    FILE *expected = fopen(argv[2], "rb");
    if (data == NULL) {
        printf("Couldn't find test data\n");
        return 1;
    }
    if (expected == NULL) {
        printf("Couldn't find expected data\n");
        return 1;
    }
    fseek(expected, 0, SEEK_END);
    long int expected_len = ftell(expected) / sizeof(unicodeCodePt);
    printf("Expected code point count: %lu\n", expected_len);
    rewind(expected);

    for (long int i = 0; i < expected_len; i++) {
        unicodeCodePt expected_codePt;
        fread(&expected_codePt, sizeof(expected_codePt), 1, expected);
        unicodeCodePt got_codePt = nextCodePt(data);
        char specifier[7] = "%04";
        strcat(specifier, PRIX32);
        printf("Expected: U+");
        printf(specifier, expected_codePt);
        printf(", got: U+");
        printf(specifier, got_codePt);
        printf("\n");
        if (got_codePt != expected_codePt) {
            fclose(data);
            return 1;
        }
    }
    fclose(data);
    return 0;
}