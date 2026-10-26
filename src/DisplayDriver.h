/* DisplayDriver.h
 *
 * These functions must be linked from an external src file to provide a driver
 *  for a specific display type.
 *
 * NOTES:
 * - CharacterBuilder assumes a 4x20 character text display.
 * - CharacterBuilder assumes a display with 8 CGRAM slots
 */

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include <stdint.h>

#define DD_NUM_ROWS 4
#define DD_NUM_COLUMNS 20
#define DD_NUM_CGRAM_SLOTS 8


/* Initialises display hardware
 */
void DD_displayInit(void);

/* Switches the display on, ready to write to.
 */
void DD_displayOn(void);

/* Clears the display and moves the cursor to the top-left corner.
 */
void DD_displayClear(void);

/* Places the cursor at [row],[column].
 */
void DD_displaySetCursorAt(const uint8_t row,
                           const uint8_t column);

/* Writes [charAscii] to the current cursor position and moves to the next
 *  cursor position.
 */
void DD_displayChar(const char charAscii);

/* Fills one slot of the CGRAM with custom character. [charData] must be an
 *  array of 8 uint8_t's containing 5-bit values.
 */
void DD_displayCreateCustomChar(const uint8_t cgramSlot,
                                const uint8_t charData[]);

#endif
