#include "avr/eeprom.h"


enum Menu{menu_start, menu_on, start_game, controls, settings} menu_state;
void MenuTick() 
{
	unsigned char tmpB = 0x00;
	switch(menu_state)
	{ //Transitions
		case menu_start:
			menu_state = menu_on;
			break;
		case menu_on:
			//tmpB = ~PINA;
			if ((~PINA & 0x01) == 0x01)
			{
				if (pos == 20) { menu_state = start_game; str_out = 0;}
				else if (pos == 30) { menu_state = controls; str_out = 0; }
				else if (pos == 40) { menu_state = settings; str_out = 0; }
				break;
			}
			else { menu_state = menu_on; }
			break;
		case start_game:
			menu_state = start_game;
			break;
		case controls:
			break;
		case settings:
			tmpB = ~PINA & 0x08;
			if (tmpB == 0x08) {
				menu_state = menu_on;
				break;
			}
			else {
				menu_state = settings;
				break;
			}
	}
	switch (menu_state)
	{
		case menu_start:
			break;
		case menu_on:
			tmpB = ~PINA;
			if (!str_out) {
				nokia_lcd_clear();
				nokia_lcd_write_string("Trapped",2);
				nokia_lcd_set_cursor(0, 20);
				nokia_lcd_write_string("  Start Game",1);
				nokia_lcd_set_cursor(0, 30);
				nokia_lcd_write_string("  Introduction",1);
				nokia_lcd_set_cursor(0, 40);
				nokia_lcd_write_string("  Settings",1);
				pos = 20;
				nokia_lcd_set_cursor(1, pos);
				nokia_lcd_write_string(">",1);
				nokia_lcd_render();
				str_out = 1;
			}
			if ((~PINA & 0x08) == 0x08 )
			{
				nokia_lcd_set_cursor(1, pos);
				nokia_lcd_write_string(" ",1);
				//nokia_lcd_render();	
				if (pos == 40) { pos = 20; }
				else { pos += 10; }
				nokia_lcd_set_cursor(1, pos);
				nokia_lcd_write_string(">",1);
				nokia_lcd_render();
			}
			else if ((~PINA & 0x02) == 0x02)
			{
				nokia_lcd_set_cursor(1, pos);
				nokia_lcd_write_string(" ",1);	
				if (pos == 20) { pos = 40; }
				else { pos -= 10; }
				nokia_lcd_set_cursor(1, pos);
				nokia_lcd_write_string(">",1);
				nokia_lcd_render();	
			}
			break;
		case start_game:
			game_running = 1;
			//nokia_lcd_clear();
			break;
		case controls:
			if (!str_out)
			{
				nokia_lcd_clear();
				nokia_lcd_set_cursor(1,0);
				nokia_lcd_write_string("Use the buttons to move up, down, left, or right.", 1);
				nokia_lcd_render();
				str_out = 1;
			}
			break;
		case settings:
			//PORTC = 0x10;
			tmpB = ~PINA & 0x02;
			if (tmpB == 0x02) {
				//if (play_song == 0) { play_song = 1; }
				if (eeprom_read_byte(0) == 0) {eeprom_write_byte(0,1);}
				else { eeprom_write_byte(0,0); }
			}
			break;
			
	}
	//return menu_state;
};