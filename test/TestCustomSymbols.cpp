// TestCustomSymbols.cpp

#include "CppUTest/TestHarness.h"
#include <stdint.h>

extern "C" {
    #include "CustomSymbols.h"
    #include "CustomSymbolsForTesting.h"
}


static uint8_t initialSymbolCode[CC_NUM_CGRAM_SLOTS];

static uint8_t LastCreatedSymbolCode = 7;
static const uint8_t *LastCreatedSymbolData = NULL;
static uint8_t CreateCustomCharCallCount = 0;


static void createCustomChar(const uint8_t symbolCode,
                             const uint8_t *customCharData) {
    LastCreatedSymbolCode = symbolCode;
    LastCreatedSymbolData = customCharData;
    CreateCustomCharCallCount++;
}


TEST_GROUP(CustomChars) {

    void setup() {
        CreateCustomCharCallCount = 0;
        cc_initSymbols(NUM_SYMBOLS,
                       customSymbolData,
                       createCustomChar);
        for (uint8_t i = 0; i < CC_NUM_CGRAM_SLOTS; i++) {
            initialSymbolCode[i] = cc_getSymbolCode(TEST_SYMBOL_0 + i);
        }
        BYTES_EQUAL(CC_NUM_CGRAM_SLOTS, CreateCustomCharCallCount);
        CreateCustomCharCallCount = 0;
    }

    void teardown() {
        cc_clearSymbols();
    }
};


// LRU = Least Recently Used

TEST(CustomChars,
     initialCC_NUM_CGRAM_SLOTSsymbolsFillBuffer_andHaveDifferentAsciiValues) {
    for (uint8_t i = 0; i < CC_NUM_CGRAM_SLOTS; i++) {
        for (uint8_t j = i + 1; j < CC_NUM_CGRAM_SLOTS; j++) {
            CHECK_TEXT(initialSymbolCode[i] != initialSymbolCode[j],
                       StringFromFormat("i = %d, j = %d, val = %d", i, j, initialSymbolCode[i]).asCharString());
        }
    }
}


TEST(CustomChars,
     GetSymbolCode_onFirstUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[0], cc_getSymbolCode(TEST_SYMBOL_0));
    BYTES_EQUAL(0, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_on2ndUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[1], cc_getSymbolCode(TEST_SYMBOL_1));
    BYTES_EQUAL(0, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_on8thUsedSymbol_returnsSameCode_andDidNotCallCreate) {
    BYTES_EQUAL(initialSymbolCode[7], cc_getSymbolCode(TEST_SYMBOL_7));
    BYTES_EQUAL(0, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_returnsCodeOfLRUsymbol_andCalledCreateOnce) {
    BYTES_EQUAL(initialSymbolCode[0], cc_getSymbolCode(TEST_SYMBOL_10));
    BYTES_EQUAL(1, CreateCustomCharCallCount);
}


TEST(CustomChars,
     AfterGetSymbolCode_onNewSymbol_theOriginalSymbolReturnsCodeOfNewLRUsymbol) {
     cc_getSymbolCode(TEST_SYMBOL_10);
     BYTES_EQUAL(initialSymbolCode[1], cc_getSymbolCode(TEST_SYMBOL_0));
     BYTES_EQUAL(initialSymbolCode[2], cc_getSymbolCode(TEST_SYMBOL_1));
}


TEST(CustomChars,
     GetSymbolCode_onUsedSymbol_doesNotAssignNewSymbolCode) {
    cc_getSymbolCode(TEST_SYMBOL_0);
    BYTES_EQUAL(initialSymbolCode[7], LastCreatedSymbolCode);
    BYTES_EQUAL(0, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_assignsNewSymbolCode) {
    cc_getSymbolCode(TEST_SYMBOL_10);
    BYTES_EQUAL(initialSymbolCode[0], LastCreatedSymbolCode);
    BYTES_EQUAL(1, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_onUsedSymbol_doesNotCreateNewCharInDisplay) {
    cc_getSymbolCode(TEST_SYMBOL_0);
    const uint8_t symbolId = TEST_SYMBOL_7 - CC_FIRST_SYMBOL;
    const uint8_t bitPattern = customSymbolData[symbolId * 8];
    BYTES_EQUAL(bitPattern, LastCreatedSymbolData[0]);
    BYTES_EQUAL(bitPattern, LastCreatedSymbolData[7]);
    BYTES_EQUAL(0, CreateCustomCharCallCount);
}


TEST(CustomChars,
     GetSymbolCode_onNewSymbol_createsNewCharInDisplay) {
    cc_getSymbolCode(TEST_SYMBOL_10);
    const uint8_t symbolId = TEST_SYMBOL_10 - CC_FIRST_SYMBOL;
    const uint8_t bitPattern = customSymbolData[symbolId * 8];
    BYTES_EQUAL(bitPattern, LastCreatedSymbolData[0]);
    BYTES_EQUAL(bitPattern, LastCreatedSymbolData[7]);
    BYTES_EQUAL(1, CreateCustomCharCallCount);
}
