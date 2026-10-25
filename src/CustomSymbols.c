// CustomSymbols.c

#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#include "CustomSymbols.h"

#define SYMBOL_NOT_IN_USE 0xFF


/* This is the callback function to create a new custom character in the CGRAM
 *  of the display.
 */
static cc_createCustomCharFunction CreateCustomCharFunction = NULL;
static const uint8_t *SymbolData = NULL;

/* recentSymbolQueue[0..QueueSize-1] contains every active symbolId exactly
 *  once, in the order most to least recently used.
 */
static uint8_t recentSymbolQueue[CC_NUM_CGRAM_SLOTS];
static uint8_t QueueSize = CC_NUM_CGRAM_SLOTS;

/* A symbolId identifies a logical custom symbol.
 * A symbolCode is the LCD character code currently assigned to that symbol.
 * Only QueueSize symbols can have an assigned symbolCode at a time.
 * All symbolCodes that are not in use are set to SYMBOL_NOT_IN_USE.
 */
static uint8_t symbolCodes[CC_MAX_NUM_SYMBOLS];
static uint8_t NumSymbols = 0;


static inline uint8_t getLeastRecentlyUsedSymbol(void) {
    return recentSymbolQueue[QueueSize - 1];
}


// recentSymbolQueue[0] is most recently used
static void shiftSymbolIntoQueue(const uint8_t symbolId) {
    for (uint8_t i = QueueSize - 1; i > 0; i--) {
        recentSymbolQueue[i] = recentSymbolQueue[i - 1];
    }
    recentSymbolQueue[0] = symbolId;
}


/* Moves symbol to position [0], shifting the items between 0 and its original
 *  position.
 */
static void setSymbolToMostRecent(const uint8_t symbolId) {
    uint8_t previousSymbol = symbolId;
    for (uint8_t i = 0; i < QueueSize; i++) {
        uint8_t tmp = recentSymbolQueue[i];
        recentSymbolQueue[i] = previousSymbol;
        if (tmp == symbolId) {
            return;
        }
        previousSymbol = tmp;
    }
}


static void createSymbolInDisplay(const uint8_t symbolId,
                                  const uint8_t symbolCode) {
    CreateCustomCharFunction(symbolCode, SymbolData + 8 * symbolId);
}


static uint8_t reclaimSymbolCode(void) {
    const uint8_t lruSymbolId = getLeastRecentlyUsedSymbol();
    const uint8_t symbolCode = symbolCodes[lruSymbolId];
    symbolCodes[lruSymbolId] = SYMBOL_NOT_IN_USE;
    return symbolCode;
}


static void assignSymbolCode(const uint8_t symbolId,
                             const uint8_t symbolCode) {
    symbolCodes[symbolId] = symbolCode;
    createSymbolInDisplay(symbolId, symbolCode);
    shiftSymbolIntoQueue(symbolId);
}


static inline bool isSymbolInUse(const uint8_t symbolId) {
    return symbolCodes[symbolId] != SYMBOL_NOT_IN_USE;
}


// symbol is the 0x80+ ascii character and symbolId is its index in symbolCodes[]
uint8_t cc_getSymbolCode(const uint8_t symbol) {
    assert (symbol >= CC_FIRST_SYMBOL);
    assert (symbol < CC_FIRST_SYMBOL + NumSymbols);
    const uint8_t symbolId = symbol - CC_FIRST_SYMBOL;
    if (isSymbolInUse(symbolId)) {
        setSymbolToMostRecent(symbolId);
    } else {
        const uint8_t newSymbolCode = reclaimSymbolCode();
        assignSymbolCode(symbolId, newSymbolCode);
    }
    return symbolCodes[symbolId];
}


/* Fills the recentSymbolQueue with the first symbols.
 */
static void primesymbolCodes(void) {
    for (uint8_t i = 0; i < NumSymbols; i++) {
        if (i < QueueSize) {
            assignSymbolCode(i, i);
        } else {
            symbolCodes[i] = SYMBOL_NOT_IN_USE;
        }
    }
}


void cc_initSymbols(const uint8_t numSymbols,
                    const uint8_t *symbolData,
                    cc_createCustomCharFunction createCustomChar) {
    assert(NumSymbols == 0); // init must only be called once
    assert(numSymbols > 0);
    assert(numSymbols <= CC_MAX_NUM_SYMBOLS);
    assert(symbolData != NULL);
    assert(createCustomChar != NULL);
    CreateCustomCharFunction = createCustomChar;
    SymbolData = symbolData;
    NumSymbols = numSymbols;
    if (NumSymbols < CC_NUM_CGRAM_SLOTS) {
        QueueSize = NumSymbols;
    }
    primesymbolCodes();
}


void cc_clearSymbols(void) {
    NumSymbols = 0;
}
