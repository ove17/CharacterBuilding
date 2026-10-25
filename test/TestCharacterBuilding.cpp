// TestCharacterBuilding.cpp

#include "CppUTest/TestHarness.h"
#include <stdint.h>
#include <stdio.h>

extern "C" {
    #include "CharacterBuilding.h"
    #include "mocks/FakeDisplay.h"
    #include "CustomSymbolsForTesting.h"
}

#define BUF_SIZE 20

static char textBuffer[BUF_SIZE];


TEST_GROUP(DisplayInit) {
    void setup() {}

    void teardown() {
        cc_clearSymbols();
    }
};


TEST(DisplayInit,
     displayIsClear_atInit) {
    CB_initDisplay(NUM_SYMBOLS, customSymbolData);
    STRNCMP_EQUAL("                    ", getFakeDisplayLine(0), 20);
    STRNCMP_EQUAL("                    ", getFakeDisplayLine(1), 20);
    STRNCMP_EQUAL("                    ", getFakeDisplayLine(2), 20);
    STRNCMP_EQUAL("                    ", getFakeDisplayLine(3), 20);
}


TEST(DisplayInit,
     cursorIsAtTopLeftCorner_atInit) {
    CB_initDisplay(NUM_SYMBOLS, customSymbolData);
    CB_writeChar('*');
    CHECK_EQUAL('*', getFakeDisplayChar(0, 0));
}


///////


TEST_GROUP(Display) {
    void setup() {
        CB_initDisplay(NUM_SYMBOLS, customSymbolData);
    }

    void teardown() {
        cc_clearSymbols();
    }
};


TEST(Display,
     setCursor_placesCursorAtRowColumn) {
    CB_setCursorAt(1, 5);
    CB_writeChar('E');
    CHECK_EQUAL('E', getFakeDisplayChar(1, 5));
}


TEST(Display,
     writeCharTo0_0_worksAsExpected) {
    CB_writeCharAt('A', 0, 0);
    CHECK_EQUAL('A', getFakeDisplayChar(0, 0));
}


TEST(Display,
     writeChar_advancesCursorToNextColumn) {
    CB_writeCharAt('A', 2, 3);
    CB_writeChar('Z');
    CHECK_EQUAL('Z', getFakeDisplayChar(2, 4));
}


TEST(Display,
     CursorAutomaticallyWrapsAtEndOfFirstLine_toStartOf2ndLine) {
    CB_writeCharAt('A', 0, 19);
    CB_writeChar('Z');
    CHECK_EQUAL('Z', getFakeDisplayChar(1, 0));
}


TEST(Display,
     CursorAutomaticallyWrapsAtEndOfLastLine_toStartOf1stLine) {
    CB_writeCharAt('Z', 3, 19);
    CB_writeChar('0');
    CHECK_EQUAL('0', getFakeDisplayChar(0, 0));
}


TEST(Display,
     WriteStringAt0_0_worksAsExpected) {
    CB_writeStringAt("1234", 4, 0, 1);
    STRNCMP_EQUAL(" 1234 ", getFakeDisplayLine(0), 6);
}


TEST(Display,
     WriteEmptyString_ClearsUnderlyingContent) {
    CB_writeStringAt("ABCD", 4, 2, 2);
    CB_writeStringAt("", 2, 2, 3);
    STRNCMP_EQUAL("  A  D", getFakeDisplayLine(2), 6);
}


TEST(Display,
     WriteStringWithFewerCharsThanLength_truncatesString) {
    CB_writeStringAt("ABC", 2, 0, 1);
    STRNCMP_EQUAL(" AB ", getFakeDisplayLine(0), 4);
}


TEST(Display,
     WriteStringWithMoreCharsThanLength_padsWithTrailingSpaces) {
    CB_writeString("XXXXXXXXXX", 10);
    CB_writeStringAt("123", 5, 0, 3);
    STRNCMP_EQUAL("XXX123  XX ", getFakeDisplayLine(0), 11);
}


TEST(Display,
     WriteStringWithSymbol_replacesSymbolWithSymbolCode) {
    snprintf(textBuffer, BUF_SIZE, "ABC%cX", TEST_SYMBOL_4);
    CB_writeString(textBuffer, 5);
    STRNCMP_EQUAL("ABC\x4X", getFakeDisplayLine(0), 5);
}


TEST(Display,
     WriteStringWithMultipleSymbols_replacesEachSymbolWithDifferentSymbolCode) {
    snprintf(textBuffer, BUF_SIZE, "A%cX%cY%cZ", TEST_SYMBOL_1, TEST_SYMBOL_7, TEST_SYMBOL_11);
    CB_writeString(textBuffer, 7);
    MEMCMP_EQUAL("A\x1X\x7Y\x0Z", getFakeDisplayLine(0), 7); // memcmp for dealing with \0
}
