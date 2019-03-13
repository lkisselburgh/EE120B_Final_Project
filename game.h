#include <time.h>
#include <stdlib.h>
//#include "nokia5110.c"

unsigned char r;
unsigned char r_limit;
unsigned char doors_opened = 0;
unsigned char move_rooms = 0;
int room = 0;
#define start_x 39
#define start_y 34
unsigned char curr_x = start_x;
unsigned char curr_y = start_y; 
void nokia_draw_enemies(unsigned char room);
void nokia_draw_exit();

enum Game{game_start, room0, room1, room2, room3, room4, room5, pause, win} game_state;
void GameTick()
{
	unsigned char tmpG = 0;
	switch(game_state)
	{ //Transitions
		case game_start:
			game_state = room0;
			move_rooms = 0;
			break;
			
		case room0:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (move_rooms) {
				str_out = 0;			
				if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
			
		case room1:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (move_rooms) {
				str_out = 0;
			
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
			
		case room2:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (move_rooms) {
				str_out = 0;
		
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
			
		case room3:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (move_rooms) {
				str_out = 0;
		
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
			
		case room4:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (move_rooms) {
				str_out = 0;
		
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
		case room5:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_state = pause; }
			else if (curr_x <= 4 && curr_y < 30 && curr_y > 18) { game_state = win; break; }
			else if (move_rooms) {
				str_out = 0;
		
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				move_rooms = 0;
			}
			else if ((tmpG & 0x10) == 0x10) {
				game_state = pause;
			}
			break;
		case pause:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) {
				game_state = room;
			}
			else { game_state = pause; }
			break;
		case win:
			tmpG = ~PINA;
			while (tmpG == 0 && !game_running) {
				game_state = win;
				break;
			}
			game_running = 0;
			break;
	}
	switch(game_state) 
	{ //State Actions
		case game_start:
			break;
		case room0:
			tmpG = ~PINA;
			move_rooms = 0;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
			
			if ((~PINA & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) { 
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((~PINA & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) { 
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((~PINA & 0x04) == 0x04) {
				if (curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 0) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(0); 
			nokia_lcd_render(); 
			break;
		case room1:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
			
			if ((tmpG & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x04) == 0x04) {
				if (curr_x < 78) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 1) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(1); 
			nokia_lcd_render();
			break;
		case room2:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
		
			if ((tmpG & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x04) == 0x04) {
				if (curr_x < 78) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 2) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(2); 
			nokia_lcd_render();
				break;
		case room3:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
			if ((tmpG & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x04) == 0x04) {
				if (curr_x < 78) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 3) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(3); 
			nokia_lcd_render(); 
			break;
		case room4:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
			if ((tmpG & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x04) == 0x04) {
				if (curr_x < 78) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 4) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(4); 
			nokia_lcd_render();
			break;
		case room5:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}
			if ((tmpG & 0x01) == 0x01) {
				if (curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x02) == 0x02) {
				if (curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x04) == 0x04) {
				if (curr_x < 78) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				// else if (curr_x <= 4 && curr_y < 30 && curr_y > 18) { game_state = win; break; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					if (doors_opened < 3) { r_limit = 5; }
					else { r_limit = 6; }
					r = rand() % r_limit;
					while (r == 5) { r = rand() % r_limit; }
					//Prevents player from being randomly sent into the room they left from
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(3);
			nokia_draw_exit(); 
			nokia_lcd_render();
			break;
		case win:
			if (!str_out) {
				nokia_lcd_clear();
				nokia_lcd_write_string(" You Escaped!", 1);
				nokia_lcd_set_cursor(0, 20);
				nokia_lcd_write_string("  For now...", 1);
				nokia_lcd_render();
				str_out = 1;
			}
			else {
				nokia_lcd_clear();
				str_out = 0;
			}
			break;
		case pause:
			tmpG = ~PINA;
			if (!str_out)
			{
				nokia_lcd_clear();
				nokia_lcd_set_cursor(0,0);
				nokia_lcd_write_string("Paused",2);
				nokia_lcd_set_cursor(0, 20);
				nokia_lcd_write_string(" Resume",1);
				nokia_lcd_set_cursor(0, 30);
				nokia_lcd_write_string(" Settings",1);
				nokia_lcd_set_cursor(0, 40);
				nokia_lcd_write_string(" Exit",1);
				nokia_lcd_render();
				str_out = 1;
			}			
			break;
	}
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
}

void nokia_draw_enemies(unsigned char room) {
	unsigned char end_x;
	if (room >= 1) {
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
	
	if (room >= 2) {
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
	if (room >= 3) {
		for (int x = 4; x < 11; x++) {
			for (int y = 35; y < 42; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 10; // y < 11
		nokia_lcd_set_pixel(end_x-5, 41, 0);
		nokia_lcd_set_pixel(end_x-3, 41, 0);
		nokia_lcd_set_pixel(end_x-1, 41, 0);
		nokia_lcd_set_pixel(end_x-6, 35, 0);
		nokia_lcd_set_pixel(end_x, 35, 0);
		nokia_lcd_set_pixel(end_x-5, 37, 0);
		nokia_lcd_set_pixel(end_x-1, 37, 0);
		nokia_lcd_set_pixel(end_x-3, 39, 0);
	}
	if (room >= 4) {
		for (int x = 73; x < 80; x++) {
			for (int y = 35; y < 42; y++) {
				nokia_lcd_set_pixel(x, y, 1);
			}
		}
		end_x = 79;
		nokia_lcd_set_pixel(end_x-5, 41, 0);
		nokia_lcd_set_pixel(end_x-3, 41, 0);
		nokia_lcd_set_pixel(end_x-1, 41, 0);
		nokia_lcd_set_pixel(end_x-6, 35, 0);
		nokia_lcd_set_pixel(end_x, 35, 0);
		nokia_lcd_set_pixel(end_x-5, 37, 0);
		nokia_lcd_set_pixel(end_x-1, 37, 0);
		nokia_lcd_set_pixel(end_x-3, 39, 0);
	}
}