// CharacterBuilding.c

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "CharacterBuilding.h"
#include "CustomSymbols.h"
#include "DisplayDriver.h"


/*void cc_initSymbols(const uint8_t numSymbols,
                    const uint8_t *symbolData,
                    cc_createCustomCharFunction createCustomChar);
void DD_displayCreateCustomChar(const uint8_t cgramSlot,
                                const uint8_t charData[]);*/

void CB_initDisplay(const uint8_t numSymbols,
                    const uint8_t *symbolData) {
    DD_displayInit();
    cc_initSymbols(numSymbols, symbolData, DD_displayCreateCustomChar);
    DD_displayClear();
}


void CB_clearDisplay() {
    DD_displayClear();
}


void CB_displayOn() {
    DD_displayOn();
}


/* Write a single character to the current cursor position and leave the cursor
 *  at the next char at exit.
 * If the character is a symbol, it is replaced with its (ascii) code.
 */
void CB_writeChar(char charAscii) {
    if ((uint8_t)charAscii >= CC_FIRST_SYMBOL) {
        charAscii = cc_getSymbolCode(charAscii);
    }
    DD_displayChar(charAscii);
}

/* write a single character to ([row], [col]) and leave the cursor at
 * the next char at exit
 */
void CB_writeCharAt(const char charAscii,
                    const uint8_t row,
                    const uint8_t col) {
    CB_setCursorAt(row, col);
    CB_writeChar(charAscii);
}


void CB_setCursorAt(uint8_t row,
                    uint8_t col) {
    assert(row < DD_NUM_ROWS);
    assert(col < DD_NUM_COLUMNS);
    DD_displaySetCursorAt(row, col);
}


/* display [numChars] characters of the string [charArray] starting at
 * the current cursor position, if the string is shorter than [numChars] the
 * remaining positions are filled with spaces. At exit, the cursor is left at
 * the next character position.
 * Note that any \0 characters that CB_writeChar may put in the output do not
 *  affect its rendering, as the trailing \0 is caught before symbol
 *  replacement.
 */
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


/* display [numChars] characters of the string [charArray], if the
 * string is shorter than [numChars] the remaining positions are filled with
 * spaces.
 */
void CB_writeStringAt(const char charArray[],
                      const uint8_t numChars,
                      const uint8_t row,
                      const uint8_t column) {
    CB_setCursorAt(row, column);
    CB_writeString(charArray, numChars);
}
