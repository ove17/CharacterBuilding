/* DisplayDriver.h
 *
 * These functions must be linked from an external src file to provide a
 *  driver for a specific display type.
 *
 * Note that CharacterBuilder assumes a 4x20 character text display!
 */

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include <stdint.h>

#define DD_NUM_ROWS 4
#define DD_NUM_COLUMNS 20


void DD_displayInit(void);
void DD_displayOn(void);
void DD_displayClear(void);

void DD_displaySetCursorAt(const uint8_t row,
                           const uint8_t column);
void DD_displayChar(const char charAscii);

void DD_displayCreateCustomChar(const uint8_t cgramSlot,
                                const uint8_t charData[]);

#endif
