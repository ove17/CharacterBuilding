// CustomSymbolsForTesting.h

#include "CustomSymbols.h"

enum {
        TEST_SYMBOL_0 = CS_FIRST_SYMBOL,
        TEST_SYMBOL_1,
        TEST_SYMBOL_2,
        TEST_SYMBOL_3,
        TEST_SYMBOL_4,
        TEST_SYMBOL_5,
        TEST_SYMBOL_6,
        TEST_SYMBOL_7,
        TEST_SYMBOL_8,
        TEST_SYMBOL_9,
        TEST_SYMBOL_10,
        TEST_SYMBOL_11,
        AFTER_LAST_SYMBOL,
        NUM_SYMBOLS = AFTER_LAST_SYMBOL - CS_FIRST_SYMBOL
};


static const uint8_t customSymbolData[8 * NUM_SYMBOLS] = {
        // TEST_SYMBOL_0 :
        0, 0, 0, 0, 0, 0, 0, 0,
        // TEST_SYMBOL_1 :
        1, 1, 1, 1, 1, 1, 1, 1,
        // TEST_SYMBOL_2 :
        2, 2, 2, 2, 2, 2, 2, 2,
        // TEST_SYMBOL_3 :
        3, 3, 3, 3, 3, 3, 3, 3,
        // TEST_SYMBOL_4 :
        4, 4, 4, 4, 4, 4, 4, 4,
        // TEST_SYMBOL_5 :
        5, 5, 5, 5, 5, 5, 5, 5,
        // TEST_SYMBOL_6 :
        6, 6, 6, 6, 6, 6, 6, 6,
        // TEST_SYMBOL_7 :
        7, 7, 7, 7, 7, 7, 7, 7,
        // TEST_SYMBOL_8 :
        8, 8, 8, 8, 8, 8, 8, 8,
        // TEST_SYMBOL_9 :
        9, 9, 9, 9, 9, 9, 9, 9,
        // TEST_SYMBOL_10 :
        10, 10, 10, 10, 10, 10, 10, 10,
        // TEST_SYMBOL_11 :
        11, 11, 11, 11, 11, 11, 11, 11,
};
