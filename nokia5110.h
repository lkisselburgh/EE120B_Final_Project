 /* Nokia 5110 LCD AVR Library
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 */

#ifndef __NOKIA_5110_H__
#define __NOKIA_5110_H__

#include <avr/pgmspace.h>
#include <stdint.h>

/*
 * LCD's port
 */
#define PORT_LCD PORTD
#define DDR_LCD DDRD

/*
 * LCD's pins
 */

#define LCD_SCE PD0
#define LCD_RST PD1
#define LCD_DC PD2
#define LCD_DIN PD5
#define LCD_CLK PD7

#define LCD_CONTRAST 0x40

/*
 * Must be called once before any other function, initializes display
 */
void nokia_lcd_init(void);

/*
 * Clear screen
 */
void nokia_lcd_clear(void);

/**
 * Power of display
 * @lcd: lcd nokia struct
 * @on: 1 - on; 0 - off;
 */
void nokia_lcd_power(uint8_t on);

/**
 * Set single pixel
 * @x: horizontal pozition
 * @y: vertical position
 * @value: show/hide pixel
 */
void nokia_lcd_set_pixel(uint8_t x, uint8_t y, uint8_t value);

/**
 * Draw single char with 1-6 scale
 * @code: char code
 * @scale: size of char
 */
void nokia_lcd_write_char(char code, uint8_t scale);

/**
 * Draw string. Example: writeString("abc",3);
 * @str: sending string
 * @scale: size of text
 */
void nokia_lcd_write_string(const char *str, uint8_t scale);

/**
 * Set cursor position
 * @x: horizontal position
 * @y: vertical position
 */
void nokia_lcd_set_cursor(uint8_t x, uint8_t y);

/*
 * Render screen to display
 */
void nokia_lcd_render(void);


// =========== Room Functions =============



void nokia_draw_room() {
	//nokia_lcd_clear();
	
	for (int x = 0; x < 84; x++) {
		nokia_lcd_set_pixel(x, 0, 1);
		nokia_lcd_set_pixel(x, 47, 1);
	}
	for (int y = 0; y < 48; y++) {
		nokia_lcd_set_pixel(0, y, 1);
		nokia_lcd_set_pixel(83, y, 1);
	}
	
	//Eastern Door
	for (int y = 19; y < 30; y++) { nokia_lcd_set_pixel(0, y, 0); }
	//Western Door
	for (int y = 19; y < 30; y++) {	nokia_lcd_set_pixel(83, y, 0); }
	//Northern Door
	for (int x = 35; x < 49; x++) { nokia_lcd_set_pixel(x, 0, 0); }
	//Southern Door
	for (int x = 35; x < 49; x++) { nokia_lcd_set_pixel(x, 47, 0); }
	//nokia_lcd_render();
}

void nokia_draw_enemies(uint8_t NW_enemy, uint8_t NE_enemy, uint8_t SW_enemy, uint8_t SE_enemy) {
	unsigned char end_x;
	if (NW_enemy) {
		for (int x = 4; x < 11; x++) {
			for (int y = 4; y < 11; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 10;
		nokia_lcd_set_pixel(end_x-5, 10, 0);
		nokia_lcd_set_pixel(end_x-3, 10, 0);
		nokia_lcd_set_pixel(end_x-1, 10, 0);
		nokia_lcd_set_pixel(end_x-6, 4, 0);
		nokia_lcd_set_pixel(end_x, 4, 0);
		nokia_lcd_set_pixel(end_x-5, 6, 0);
		nokia_lcd_set_pixel(end_x-1, 6, 0);
		nokia_lcd_set_pixel(end_x-3, 8, 0);
	}
	if (NE_enemy) {
	//if (room >= 2) {
		for (int x = 73; x < 80; x++) {
			for (int y = 4; y < 11; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 79;
		nokia_lcd_set_pixel(end_x-5, 10, 0);
		nokia_lcd_set_pixel(end_x-3, 10, 0);
		nokia_lcd_set_pixel(end_x-1, 10, 0);
		nokia_lcd_set_pixel(end_x-6, 4, 0);
		nokia_lcd_set_pixel(end_x, 4, 0);
		nokia_lcd_set_pixel(end_x-5, 6, 0);
		nokia_lcd_set_pixel(end_x-1, 6, 0);
		nokia_lcd_set_pixel(end_x-3, 8, 0);
	}
	if (SW_enemy) {
		for (int x = 20; x < 27; x++) {
			for (int y = 36; y < 43; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 26; // y < 11
		nokia_lcd_set_pixel(end_x-5, 42, 0);
		nokia_lcd_set_pixel(end_x-3, 42, 0);
		nokia_lcd_set_pixel(end_x-1, 42, 0);
		nokia_lcd_set_pixel(end_x-6, 36, 0);
		nokia_lcd_set_pixel(end_x, 36, 0);
		nokia_lcd_set_pixel(end_x-5, 38, 0);
		nokia_lcd_set_pixel(end_x-1, 38, 0);
		nokia_lcd_set_pixel(end_x-3, 40, 0);
	}
	if (SE_enemy) {
		for (int x = 61; x < 68; x++) {
			for (int y = 36; y < 43; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 67;
		nokia_lcd_set_pixel(end_x-5, 42, 0);
		nokia_lcd_set_pixel(end_x-3, 42, 0);
		nokia_lcd_set_pixel(end_x-1, 42, 0);
		nokia_lcd_set_pixel(end_x-6, 36, 0);
		nokia_lcd_set_pixel(end_x, 36, 0);
		nokia_lcd_set_pixel(end_x-5, 38, 0);
		nokia_lcd_set_pixel(end_x-1, 38, 0);
		nokia_lcd_set_pixel(end_x-3, 40, 0);
	}
	nokia_lcd_render();
}

void nokia_draw_character(uint8_t x0, uint8_t y0) {
	nokia_lcd_clear();
	nokia_draw_room();
	//nokia_draw_enemies(room);
	
	for (int x = x0; x < x0+6; x++) {
		for (int y = y0; y < y0+5; y++) {
			nokia_lcd_set_pixel(x, y, 1);
		}
	}
	nokia_lcd_set_pixel(x0-1, y0+4, 1);
	nokia_lcd_set_pixel(x0-1, y0+3, 1);
	nokia_lcd_set_pixel(x0+6, y0+4, 1);
	nokia_lcd_set_pixel(x0+6, y0+3, 1);
	
	nokia_lcd_set_pixel(x0, y0, 0);
	nokia_lcd_set_pixel(x0+5, y0, 0);
	
	//Draw eyes
	nokia_lcd_set_pixel(x0+1, y0+3, 0);
	nokia_lcd_set_pixel(x0+4, y0+3, 0);
	
	//Draw body
	for (int x = x0+1; x < x0+5; x++) {
		for (int y = y0+5; y < y0+11; y++) {
			nokia_lcd_set_pixel(x, y, 1);
		}
	}
	//x0 = 40, y0 = 20
	for (int x = x0-2; x < x0+8; x++) {
		nokia_lcd_set_pixel(x, y0+10, 1);
	}
	for (int x = x0-1; x < x0+7; x++) {
		nokia_lcd_set_pixel(x, y0+8, 1);
		nokia_lcd_set_pixel(x, y0+9, 1);
	}
	for (int x = x0; x < x0+6; x++) {
		nokia_lcd_set_pixel(x, y0+6, 1);
		nokia_lcd_set_pixel(x, y0+7, 1);
	}
	nokia_lcd_render();
}

void nokia_draw_exit() {
	nokia_lcd_set_pixel(1,24,1);
	nokia_lcd_set_pixel(2,23,1);
	nokia_lcd_set_pixel(2,24,1);
	nokia_lcd_set_pixel(2,25,1);
	for (int y = 22; y < 27; y++ ) { nokia_lcd_set_pixel(3, y, 1); }
	for (int y = 21; y < 28; y++ ) { nokia_lcd_set_pixel(4, y, 1); }
	for (int x = 5; x < 10; x++ ) {
		for (int y = 23; y < 26; y++) {
			nokia_lcd_set_pixel(x, y, 1);
		}
	}
	nokia_lcd_render();
}

void nokia_transition_screen() {
	for (int x = 0; x < 84; x++) {
		for (int y = 0; y < 48; y++) {
			nokia_lcd_set_pixel(x,y,1);
		}
	}
	nokia_lcd_render();
}

#endif