// TestCustomSymbols.cpp

#include "CppUTest/TestHarness.h"
#include <stdint.h>

extern "C" {
    #include "CustomSymbols.h"
    #include "CustomSymbolsForTesting.h"
    #include "DisplayDriver.h"
    #include "FakeDisplay.h"
}


static uint8_t initialSymbolCode[DD_NUM_CGRAM_SLOTS];


TEST_GROUP(CustomChars) {

    void setup() {
        DD_displayInit();
        cs_initSymbols(NUM_SYMBOLS,
                       customSymbolData);
        for (uint8_t i = 0; i < DD_NUM_CGRAM_SLOTS; i++) {
            initialSymbolCode[i] = cs_getSymbolCode(TEST_SYMBOL_0 + i);
        }
        BYTES_EQUAL(DD_NUM_CGRAM_SLOTS, getCreateCustomCharCallCount());
    }

    void teardown() {
        cs_clearSymbols();
    }
};


// LRU = Least Recently Used

TEST(CustomChars,
     initialCS_NUM_CGRAM_SLOTSsymbolsFillBuffer_andHaveDifferentAsciiValues) {
    for (uint8_t i = 0; i < DD_NUM_CGRAM_SLOTS; i++) {
        for (uint8_t j = i + 1; j < DD_NUM_CGRAM_SLOTS; j++) {
            CHECK_TEXT(initialSymbolCode[i] != initialSymbolCode[j],
                       StringFromFormat("i = %d, j = %d, val = %d", i, j, initialSymbolCode[i]).asCharString());
        }
    }
}


TEST(CustomChars,
     GetSymbolCode_onFirstUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[0], cs_getSymbolCode(TEST_SYMBOL_0));
    BYTES_EQUAL(8, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_on2ndUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[1], cs_getSymbolCode(TEST_SYMBOL_1));
    BYTES_EQUAL(8, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_on8thUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[7], cs_getSymbolCode(TEST_SYMBOL_7));
    BYTES_EQUAL(8, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_returnsCodeOfLRUsymbol_andCalledCreateOnce) {
    BYTES_EQUAL(initialSymbolCode[0], cs_getSymbolCode(TEST_SYMBOL_10));
    BYTES_EQUAL(8 + 1, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     AfterGetSymbolCode_onNewSymbol_theOriginalSymbolReturnsCodeOfNewLRUsymbol) {
     cs_getSymbolCode(TEST_SYMBOL_10);
     BYTES_EQUAL(initialSymbolCode[1], cs_getSymbolCode(TEST_SYMBOL_0));
     BYTES_EQUAL(initialSymbolCode[2], cs_getSymbolCode(TEST_SYMBOL_1));
}


TEST(CustomChars,
     GetSymbolCode_onUsedSymbol_doesNotAssignNewSymbolCode) {
    cs_getSymbolCode(TEST_SYMBOL_0);
    BYTES_EQUAL(initialSymbolCode[7], getLastCreatedSymbolCode());
    BYTES_EQUAL(8, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_assignsNewSymbolCode) {
    cs_getSymbolCode(TEST_SYMBOL_10);
    BYTES_EQUAL(initialSymbolCode[0], getLastCreatedSymbolCode());
    BYTES_EQUAL(8 + 1, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_onUsedSymbol_doesNotCreateNewCharInDisplay) {
    cs_getSymbolCode(TEST_SYMBOL_0);
    const uint8_t symbolId = TEST_SYMBOL_7 - CS_FIRST_SYMBOL;
    const uint8_t bitPattern = customSymbolData[symbolId * 8];
    BYTES_EQUAL(bitPattern, getLastCreatedSymbolData()[0]);
    BYTES_EQUAL(bitPattern, getLastCreatedSymbolData()[7]);
    BYTES_EQUAL(8, getCreateCustomCharCallCount());
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_createsNewCharInDisplay) {
    cs_getSymbolCode(TEST_SYMBOL_10);
    const uint8_t symbolId = TEST_SYMBOL_10 - CS_FIRST_SYMBOL;
    const uint8_t bitPattern = customSymbolData[symbolId * 8];
    BYTES_EQUAL(bitPattern, getLastCreatedSymbolData()[0]);
    BYTES_EQUAL(bitPattern, getLastCreatedSymbolData()[7]);
    BYTES_EQUAL(8 + 1, getCreateCustomCharCallCount());
}
