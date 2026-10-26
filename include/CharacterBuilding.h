/* CharacterBuilding.h
 *
 * Library for writing characters and strings to a text based display. It
 *  includes automatic management of custom characters (symbols). Generally
 *  display hardware has a limit of 8 custom characters, but this library
 *  allows defining more than 8 custom symbols, as long as no more than
 *  8 are on the display at the same time. See CustomSymbols.h for details.
 *
 * A Display Driver for the display hardware is required, only its header is
 *  provided, make sure this library is linked against a source for those
 *  functions. See DisplayDriver.h for details.
 *
 * NOTES:
 * - After writing anything to the screen, the cursor will move to the next
 *      cursor position. When writing to the last column, the cursor will move
 *      to the first position of the next row. When writing to the last column
 *      of the last row, the cursor will move to the first column of the first
 *      row.
 * - If a custom symbol is written as a character, or inside a string, its
 *      symbolCode will be sent to the display. See CustomSymbols.h for details.
 * - If a custom symbol happens to be replaced with symbolCode '\0', this does
 *      not affect string writing, i.e. it will NOT be seen as the trailing \0.
 * - Attempting to write to a position outside the display will trigger an
 *      assert.
 */

#ifndef CHARACTER_BUILDING_H
#define CHARACTER_BUILDING_H

#include <stdint.h>
#include <stdbool.h>


/* Initialises the display hardware, sets up the custom symbols (if any) and
 *  clears the display.
 * If no custom symbols are used, set numSymbols to 0 and symbolData to NULL.
 * Attempting to write a custom symbol (ascii >= 0x80) after setting numSymbols
 *  to 0 will trigger an assert.
 */
void CB_initDisplay(const uint8_t numSymbols,
                    const uint8_t *symbolData);

/* Clears the entire display and moves the cursor to the top-left corner.
 */
void CB_clearDisplay(void);

/* Moves the cursor to position (row, column). Attempting to set a position
 *  outside the display will trigger an assert.
 */
void CB_setCursorAt(const uint8_t row,
                    const uint8_t col);

/* Writes a single character to the current cursor position. If the character
 *  is a symbol, it is replaced with its (ascii) symbolCode.
 * After writing, the cursor moves to the next cursor position.
 */
void CB_writeChar(const char charAscii);

/* Writes [numChars] characters of a string, starting at the current cursor
 *  position. If a '\0' is found before [numChars] the remaining positions are
 *  filled with spaces.
 * After writing the last character, the cursor moves to the next cursor
 *  position.
 */
void CB_writeString(const char charArray[],
                    const uint8_t numChars);

/* Writes a single character to [row],[column]. If the character is a symbol,
 *  it is replaced with its (ascii) symbolCode.
 * After writing, the cursor moves to the next cursor position.
 */
void CB_writeCharAt(const char charAscii,
                    const uint8_t row,
                    const uint8_t column);

/* Writes [numChars] characters of a string, starting at [row],[column]. If a
 *  '\0' is found before [numChars], the remaining positions are filled with
 *  spaces.
 * After writing the last character, the cursor moves to the next cursor
 *  position.
 */
void CB_writeStringAt(const char charArray[],
                      const uint8_t numChars,
                      const uint8_t row,
                      const uint8_t column);

#endif
