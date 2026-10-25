// CharacterBuilding.h

#ifndef CHARACTER_BUILDING_H
#define CHARACTER_BUILDING_H

#include <stdint.h>
#include <stdbool.h>


void CB_initDisplay(const uint8_t numSymbols,
                    const uint8_t *symbolData);

void CB_displayOn(void);
void CB_clearDisplay(void);

void CB_setCursorAt(const uint8_t row,
                    const uint8_t col);
void CB_clearRow(const uint8_t row);

// starts at current position, leaves cursor on the next char at exit
void CB_writeChar(const char charAscii);

// starts at current position, leaves cursor on the next char at exit
void CB_writeString(const char charArray[],
                    const uint8_t numChars);

void CB_writeCharAt(const char charAscii,
                    const uint8_t row,
                    const uint8_t column);

void CB_writeStringAt(const char charArray[],
                      const uint8_t numChars,
                      const uint8_t row,
                      const uint8_t column);

#endif
