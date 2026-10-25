/* CustomSymbols.h
 *
 * The LCD hardware allows storage of a limited number (generally 8) of custom
 *  characters. These can be used by displaying ASCII values 0x00-0x07, called
 *  symbolCode in this module.
 * This library allows defining up to 32 custom characters, with ASCII values
 *  starting at 0x80, the symbols.
 * The function cc_getSymbolCode replaces symbol with its symbolCode.
 *
 * NOTE that this does NOT allow showing more that 8 custom characters AT THE
 *      SAME TIME. That is a hardware limit. This library merely automates
 *      replacing the definition of symbols as required.
 *
 * Naming conventions in this module:
 *  symbolCode = the ASCII code of the symbol, i.e. the CGRAM slot number in
 *              the display
 *  symbol = the unique ASCII code that is used to define a specific symbol,
 *              these start at CC_FIRST_SYMBOL
 *  symbolId = the offset of the symbol, i.e. the index of the symbol in the
 *              array of symbols
 *
 * NOTE: this module is not thread safe nor re-entrant.
 */

#ifndef CUSTOM_SYMBOLS_H
#define CUSTOM_SYMBOLS_H

#include <stdint.h>

#define CC_NUM_CGRAM_SLOTS 8        // == number of CGRAM slots
#define CC_FIRST_SYMBOL 0x80    // beyond the standard character set
#define CC_MAX_NUM_SYMBOLS 32


/* Callback function to create a new custom character in the CGRAM of the
 *  display.
 */
typedef void (*cc_createCustomCharFunction)(const uint8_t symbolCode,
                                            const uint8_t *customCharData);

/* Initialisation must once, before using cc_getSymbolCode.
 *  Failure to provide valid input will result in an assertion error.
 * symbolData must point to data that remains valid for the duration of the
 *  module, e.g. a static table in flash or RAM.
 */
void cc_initSymbols(const uint8_t numSymbols,
                    const uint8_t *symbolData,
                    cc_createCustomCharFunction createCustomChar);

/* Returns the ascii value between 0x00 and 0x07 that corresponds to the CGRAM
 *  position in the display where symbol is stored.
 */
uint8_t cc_getSymbolCode(const uint8_t symbol);

/* Used to avoid errors in test code. Not intended to use in production code.
 */
void cc_clearSymbols(void);

#endif
