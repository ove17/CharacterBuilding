// CharacterBuilding.c

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "CharacterBuilding.h"
#include "CustomSymbols.h"
#include "DisplayDriver.h"


void CB_initDisplay(const uint8_t numSymbols,
                    const uint8_t *symbolData) {
    DD_displayInit();
    if (numSymbols > 0) {
        cs_initSymbols(numSymbols, symbolData);
    }
    DD_displayClear();
    DD_displayOn();
}


void CB_clearDisplay() {
    DD_displayClear();
}


void CB_setCursorAt(uint8_t row,
                    uint8_t col) {
    assert(row < DD_NUM_ROWS);
    assert(col < DD_NUM_COLUMNS);
    DD_displaySetCursorAt(row, col);
}


void CB_writeChar(char charAscii) {
    if ((uint8_t)charAscii >= CS_FIRST_SYMBOL) {
        charAscii = cs_getSymbolCode(charAscii);
    }
    DD_displayChar(charAscii);
}


void CB_writeCharAt(const char charAscii,
                    const uint8_t row,
                    const uint8_t col) {
    CB_setCursorAt(row, col);
    CB_writeChar(charAscii);
}


void CB_writeString(const char charArray[],
                   const uint8_t numChars) {
    bool writeString = true;
    for (uint8_t i = 0; i < numChars; i++) {
        if (charArray[i] == '\0') {
            writeString = false;
        }
        if (writeString) {
            CB_writeChar(charArray[i]);
        } else {
            DD_displayChar(' '); // direct call: no symbol
        }
    }
}


void CB_writeStringAt(const char charArray[],
                      const uint8_t numChars,
                      const uint8_t row,
                      const uint8_t column) {
    CB_setCursorAt(row, column);
    CB_writeString(charArray, numChars);
}
