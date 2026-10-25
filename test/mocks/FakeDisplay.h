// FakeDisplay.h

#ifndef FAKE_DISPLAY_H
#define FAKE_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

//#define INVALID_CHAR 0xFF

char getFakeDisplayChar(const uint8_t row,
                        const uint8_t col);

char * getFakeDisplayLine(const uint8_t row);

uint8_t getCursorRow();

uint8_t getCursorColumn();

void dumpDisplay();

#endif
