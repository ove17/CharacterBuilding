/* FakeDisplay.c
 *
 * Implements all functions from DisplayDriver.h + the inspection functions from
 *  FakeDisplay.h
 *
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "DisplayDriver.h"
#include "FakeDisplay.h"


typedef struct {
    uint8_t row;
    uint8_t col;
} cursor_t;


static char FakeDisplay[DD_NUM_ROWS * DD_NUM_COLUMNS];
static cursor_t Cursor;


void DD_displayInit(void) {
    Cursor = (cursor_t){.row = 0xFF, .col = 0xFF};
}


void DD_displayOn(void) {

}


void DD_displayClear(void) {
    DD_displaySetCursorAt(0,0);
    for (uint8_t i = 0; i < (DD_NUM_COLUMNS * DD_NUM_ROWS); i++) {
        DD_displayChar(' ');
    }
    DD_displaySetCursorAt(0,0);
}


void DD_displaySetCursorAt(const uint8_t row,
                           const uint8_t column) {
    Cursor = (cursor_t){.row = row, .col = column};
}


void DD_displayChar(const char charAscii) {
    FakeDisplay[Cursor.row * DD_NUM_COLUMNS + Cursor.col] = charAscii;
    Cursor.col++;
    if (Cursor.col >= DD_NUM_COLUMNS) {
        Cursor.col = 0;
        Cursor.row++;
    }
    if (Cursor.row >= DD_NUM_ROWS) {
        Cursor.row = 0;
    }
}



void DD_displayCreateCustomChar(const uint8_t cgramSlot,
                                const uint8_t charData[]) {
}


//////////


char getFakeDisplayChar(const uint8_t row,
                        const uint8_t col) {
    assert(row < DD_NUM_ROWS);
    assert(col < DD_NUM_COLUMNS);
    return FakeDisplay[row * DD_NUM_COLUMNS + col];
}


char * getFakeDisplayLine(const uint8_t row) {
    return & FakeDisplay[row * 20];
}


uint8_t getCursorRow() {
    return Cursor.row;
}


uint8_t getCursorColumn() {
    return Cursor.col;
}


void dumpDisplay() {
    printf("\n");
    for (uint8_t row = 0; row < DD_NUM_ROWS; row++) {
        printf("|");
        for (uint8_t col = 0; col < DD_NUM_COLUMNS; col++) {
            printf("%c", FakeDisplay[row * DD_NUM_COLUMNS + col]);
        }
        printf("|\n");
    }
    printf("\n");
}
