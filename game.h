#include <time.h>
#include <stdlib.h>

unsigned char r;
unsigned char r_limit;
unsigned char doors_opened = 0;
unsigned char move_rooms = 0;
unsigned char room = 0;

#define start_x 39
#define start_y 34
#define hi_y_bound 11
#define low_y_bound 25
unsigned char curr_x = start_x;
unsigned char curr_y = start_y; 

//Room 1 enemies
unsigned char NW1_enemy = 1; unsigned char NE1_enemy = 0;
unsigned char SW1_enemy = 0; unsigned char SE1_enemy = 0;
//Room 2 enemies
unsigned char NW2_enemy = 1; unsigned char NE2_enemy = 0;
unsigned char SW2_enemy = 0; unsigned char SE2_enemy = 1;
//Room 3 enemies
unsigned char NW3_enemy = 1; unsigned char NE3_enemy = 1;
unsigned char SW3_enemy = 1; unsigned char SE3_enemy = 0;
// Room 4 enemies
unsigned char NW4_enemy = 1; unsigned char NE4_enemy = 1;
unsigned char SW4_enemy = 1; unsigned char SE4_enemy = 1;
// Room 5 enemies
unsigned char NW5_enemy = 1; unsigned char NE5_enemy = 0;
unsigned char SW5_enemy = 1; unsigned char SE5_enemy = 1;

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
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (move_rooms) {
				str_out = 0;

				if (doors_opened < 3) { r_limit = 5; }
				else { r_limit = 6; }
				r = rand() % r_limit;
				//Prevents player from being randomly sent into the room they left from	
				while (r == 0) { r = rand() % r_limit; }
						
				if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			break;
			
		case room1:
			tmpG = ~PINA;
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (move_rooms) {
				str_out = 0;
				if (doors_opened < 3) { r_limit = 5; }
				else { r_limit = 6; }
				r = rand() % r_limit;
				while (r == 1) { r = rand() % r_limit; }
				//Prevents player from being randomly sent into the room they left from
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			
			break;
			
		case room2:
			tmpG = ~PINA;
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (move_rooms) {
				str_out = 0;
				if (doors_opened < 3) { r_limit = 5; }
				else { r_limit = 6; }
				r = rand() % r_limit;
				while (r == 2) { r = rand() % r_limit; }
				//Prevents player from being randomly sent into the room they left from
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			
			break;
			
		case room3:
			tmpG = ~PINA;
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (move_rooms) {
				str_out = 0;
			if (doors_opened < 3) { r_limit = 5; }
			else { r_limit = 6; }
			r = rand() % r_limit;
			while (r == 3) { r = rand() % r_limit; }
			//Prevents player from being randomly sent into the room they left from
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			break;
			
		case room4:
			tmpG = ~PINA;
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (move_rooms) {
				str_out = 0;
				if (doors_opened < 3) { r_limit = 5; }
				else { r_limit = 6; }
				r = rand() % r_limit;
				while (r == 4) { r = rand() % r_limit; }
				//Prevents player from being randomly sent into the room they left from
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 5) { game_state = room5; doors_opened++; }
				move_rooms = 0;
			}
			break;
			
		case room5:
			tmpG = ~PINA;
			if ((tmpG & 0x20) == 0x20) { game_state = pause; str_out = 0; }
			else if (curr_x <= 4 && curr_y < 30 && curr_y > 18) { game_state = win; score += 35; break; }
			else if (move_rooms) {
				str_out = 0;
				if (doors_opened < 3) { r_limit = 5; }
				else { r_limit = 6; }
				r = rand() % r_limit;
				while (r == 5) { r = rand() % r_limit; }
				if (r == 0) { game_state = room0; doors_opened++; }
				else if (r == 1) { game_state = room1; doors_opened++; }
				else if (r == 2) { game_state = room2; doors_opened++; }
				else if (r == 3) { game_state = room3; doors_opened++; }
				else if (r == 4) { game_state = room4; doors_opened++; }
				move_rooms = 0;
			}
			break;
			
		case pause:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) {
				if (pos == 20) {
					if (room == 0) {game_state = room0; str_out = 0; }
					if (room == 1) {game_state = room1; str_out = 0; }
					if (room == 2) {game_state = room2; str_out = 0; }
					if (room == 3) {game_state = room3; str_out = 0; }
					if (room == 4) {game_state = room4; str_out = 0; }
					if (room == 5) {game_state = room5; str_out = 0; }
				}
				else if (pos == 40) { game_running = 0; return; }
			}
			else { game_state = pause; break; }
			
		case win:
			tmpG = ~PINA;
			if ((tmpG & 0x10) == 0x10) { game_running = 0; str_out = 0; return; }
			else { game_state = win; break; }
	}
	
	
	
	//=================================
	//			STATE ACTIONS
	//=================================
	
	
	
	switch(game_state) 
	{ //State Actions
		
		case game_start:
			break;
		case room0:;
			tmpG = ~PINA;
			room = 0;
			move_rooms = 0;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				str_out = 1;
			}			
			
			if ((~PINA & 0x01) == 0x01) {
				
				if (curr_x > 4 ) { curr_x -= 5; }
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
			
			// MOVE RIGHT
			else if ((~PINA & 0x04) == 0x04) {
				if (curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			// MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if (curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			//nokia_lcd_render(); 
			break;
			
			
		case room1:
			tmpG = ~PINA;
			room = 1;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				nokia_draw_enemies(NW1_enemy, NE1_enemy, SW1_enemy, SE1_enemy);
				str_out = 1;
			}			
			if ((tmpG & 0x10) == 0x10) {
				if	(NW1_enemy &&
					((curr_x <= 15 && curr_y <= 6) || (curr_x < 6 && (curr_y > 10 && curr_y < 15) )))
					{ NW1_enemy = 0; score += 5; }
				if	(SW1_enemy &&
					((curr_y >= 25 && ((curr_x <= 34 && curr_x > 28) || (curr_x < 10 && curr_x > 4)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x > 15 && curr_x < 30)) ))
					{ SW1_enemy = 0; score += 5; }
				if	(NE1_enemy &&
					(((curr_x < 70 && curr_x > 60) && curr_y <= 6) || ((curr_x < 83 && curr_x > 72) && (curr_y > 10 && curr_y < 15) )))
					{ NE1_enemy = 0; score += 5; }
				if	(SE1_enemy &&
					((curr_y >= 25 && ((curr_x < 55 && curr_x > 45) || (curr_x < 75 && curr_x > 68)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x < 73 && curr_x > 58))))
					{ SE1_enemy = 0; score += 5; }
				
			}
			//MOVE LEFT
			else if ((tmpG & 0x01) == 0x01) {
				if	(NW1_enemy && SW1_enemy && ((curr_y > 11 && curr_y < 25 && curr_x > 4) ||
					((curr_y <= 11 && curr_x > 15) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68))))))
					{ curr_x -= 5; }
				else if (NW1_enemy && !SW1_enemy && ((curr_y > 11 && curr_x > 4)
					|| (curr_y <= 11 && curr_x > 15) ))
					{ curr_x -= 5; }
				else if (!NW1_enemy && SW1_enemy && ((curr_y < 25 && curr_x > 4) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68)))))
					{ curr_x -= 5; }
				else if (!NW1_enemy && !SW1_enemy && curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE UP
			else if ((tmpG & 0x02) == 0x02) {
				if	(NW1_enemy && NE1_enemy && ((curr_y > 15) || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68 && curr_x > 11))))
					{ curr_y -= 5; }
				else if (NW1_enemy && !NE1_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x > 11))))
					{ curr_y -= 5; }
				else if (!NW1_enemy && NE1_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68))))
					{ curr_y -= 5; }
				else if (!NW4_enemy && !NE4_enemy && curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE RIGHT
			else if ((tmpG & 0x04) == 0x04) {
				if	(NE1_enemy && SE1_enemy && ((curr_y > 11 && curr_y < 25 && curr_x < 73) ||
					(curr_y <= 11 && curr_x < 63) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6 )))))
					{ curr_x += 5; }
				else if (NE1_enemy && !SE1_enemy && ((curr_y > 11 && curr_x < 73)
					|| (curr_y <= 11 && curr_x < 63) ))
					{ curr_x += 5; }
				else if (!NE1_enemy && SE1_enemy && ((curr_y < 25 && curr_x < 73) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6)))))
					{ curr_x += 5; }

				else if (!NE1_enemy && !SE1_enemy && curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if	(SW1_enemy && SE1_enemy && ((curr_y < 20) || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50 && curr_x > 27) || (curr_x < 15 && curr_x > 4) || (curr_x < 80 && curr_x > 68)))))
					{ curr_y += 5; }
				else if (SW1_enemy && !SE1_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x > 27) || (curr_x < 10 && curr_x > 4)))))
					{ curr_y += 5; }
				else if (!SW1_enemy && SE1_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50) || (curr_x > 68 && curr_x < 73)))))
					{ curr_y += 5; }
				else if (!SE1_enemy && !SW1_enemy && curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(NW1_enemy, NE1_enemy, SW1_enemy, SE1_enemy);
			nokia_lcd_render();
			break;
			
			
			
		case room2:
			tmpG = ~PINA;
			room = 2;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				nokia_draw_enemies(NW2_enemy, NE2_enemy, SW2_enemy, SE2_enemy);
				str_out = 1;
			}
		
			if ((tmpG & 0x10) == 0x10) {
				if	(NW2_enemy &&
					((curr_x <= 15 && curr_y <= 6) || (curr_x < 6 && (curr_y > 10 && curr_y < 15) )))
					{ NW2_enemy = 0; score += 5; }
				if	(SW2_enemy &&
					((curr_y >= 25 && ((curr_x <= 34 && curr_x > 28) || (curr_x < 10 && curr_x > 4)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x > 15 && curr_x < 30)) ))
					{ SW2_enemy = 0; score += 5; }
				if	(NE2_enemy &&
					(((curr_x < 70 && curr_x > 60) && curr_y <= 6) || ((curr_x < 83 && curr_x > 72) && (curr_y > 10 && curr_y < 15) )))
					{ NE2_enemy = 0; score += 5; }
				if	(SE2_enemy &&
					((curr_y >= 25 && ((curr_x < 55 && curr_x > 45) || (curr_x < 75 && curr_x > 68)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x < 73 && curr_x > 58))))
					{ SE2_enemy = 0; score += 5; }
				
			}
			
			//MOVE LEFT
			else if ((tmpG & 0x01) == 0x01) {
				if	(NW2_enemy && SW2_enemy && ((curr_y > 11 && curr_y < 25 && curr_x > 4) ||
					((curr_y <= 11 && curr_x > 15) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68))))))
					{ curr_x -= 5; }
				else if (NW2_enemy && !SW2_enemy && ((curr_y > 11 && curr_x > 4)
					|| (curr_y <= 11 && curr_x > 15) ))
					{ curr_x -= 5; }
				else if (!NW2_enemy && SW2_enemy && ((curr_y < 25 && curr_x > 4) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68)))))
					{ curr_x -= 5; }
				else if (!NW2_enemy && !SW2_enemy && curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE UP
			else if ((tmpG & 0x02) == 0x02) {
				if	(NW2_enemy && NE2_enemy && ((curr_y > 15) || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68 && curr_x > 11))))
					{ curr_y -= 5; }
				else if (NW2_enemy && !NE2_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x > 11))))
					{ curr_y -= 5; }
				else if (!NW2_enemy && NE2_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68))))
					{ curr_y -= 5; }
				else if (!NW2_enemy && !NE2_enemy && curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE RIGHT
			else if ((tmpG & 0x04) == 0x04) {
				if	(NE2_enemy && SE2_enemy && ((curr_y > 11 && curr_y < 25 && curr_x < 73) ||
					(curr_y <= 11 && curr_x < 63) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6 )))))
					{ curr_x += 5; }
				else if (NE2_enemy && !SE2_enemy && ((curr_y > 11 && curr_x < 73)
					|| (curr_y <= 11 && curr_x < 63) ))
					{ curr_x += 5; }
				else if (!NE2_enemy && SE2_enemy && ((curr_y < 25 && curr_x < 73) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6)))))
					{ curr_x += 5; }

				else if (!NE2_enemy && !SE2_enemy && curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if	(SW2_enemy && SE2_enemy && ((curr_y < 20) || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50 && curr_x > 27) || (curr_x < 15 && curr_x > 4) || (curr_x < 80 && curr_x > 68)))))
					{ curr_y += 5; }
				else if (SW2_enemy && !SE2_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x > 27) || (curr_x < 10 && curr_x > 4)))))
					{ curr_y += 5; }
				else if (!SW2_enemy && SE2_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50) || (curr_x > 68 && curr_x < 73)))))
					{ curr_y += 5; }
				else if (!SE2_enemy && !SW2_enemy && curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(NW2_enemy, NE2_enemy, SW2_enemy, SE2_enemy);
			break;
			
			
			
		case room3:
			tmpG = ~PINA;
			room = 3;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				nokia_draw_enemies(NW3_enemy, NE3_enemy, SW3_enemy, SE3_enemy);
				str_out = 1;
			}
			if ((tmpG & 0x10) == 0x10) {
				if	(NW3_enemy &&
					((curr_x <= 15 && curr_y <= 6) || (curr_x < 6 && (curr_y > 10 && curr_y < 15) )))
					{ NW3_enemy = 0; score += 5; }
				if	(SW3_enemy &&
					((curr_y >= 25 && ((curr_x <= 34 && curr_x > 28) || (curr_x < 10 && curr_x > 4)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x > 15 && curr_x < 30)) ))
					{ SW3_enemy = 0; score += 5; }
				if	(NE3_enemy &&
					(((curr_x < 70 && curr_x > 60) && curr_y <= 6) || ((curr_x < 83 && curr_x > 72) && (curr_y > 10 && curr_y < 15) )))
					{ NE3_enemy = 0; score += 5; }
				if	(SE3_enemy &&
					((curr_y >= 25 && ((curr_x < 55 && curr_x > 45) || (curr_x < 75 && curr_x > 68)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x < 73 && curr_x > 58))))
					{ SE3_enemy = 0; score += 5; }
				
			}
			//MOVE LEFT
			else if ((tmpG & 0x01) == 0x01) {
				if	(NW3_enemy && SW3_enemy && ((curr_y > 11 && curr_y < 25 && curr_x > 4) ||
					((curr_y <= 11 && curr_x > 15) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68))))))
					{ curr_x -= 5; }
				else if (NW3_enemy && !SW3_enemy && ((curr_y > 11 && curr_x > 4)
					|| (curr_y <= 11 && curr_x > 15) ))
					{ curr_x -= 5; }
				else if (!NW3_enemy && SW3_enemy && ((curr_y < 25 && curr_x > 4) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68)))))
					{ curr_x -= 5; }
				else if (!NW3_enemy && !SW3_enemy && curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE UP
			else if ((tmpG & 0x02) == 0x02) {
				if	(NW3_enemy && NE3_enemy && ((curr_y > 15) || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68 && curr_x > 11))))
					{ curr_y -= 5; }
				else if (NW3_enemy && !NE3_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x > 11))))
					{ curr_y -= 5; }
				else if (!NW3_enemy && NE3_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68))))
					{ curr_y -= 5; }
				else if (!NW3_enemy && !NE3_enemy && curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE RIGHT
			else if ((tmpG & 0x04) == 0x04) {
				if	(NE3_enemy && SE3_enemy && ((curr_y > 11 && curr_y < 25 && curr_x < 73) ||
					(curr_y <= 11 && curr_x < 63) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6 )))))
					{ curr_x += 5; }
				else if (NE3_enemy && !SE3_enemy && ((curr_y > 11 && curr_x < 73)
					|| (curr_y <= 11 && curr_x < 63) ))
					{ curr_x += 5; }
				else if (!NE3_enemy && SE3_enemy && ((curr_y < 25 && curr_x < 73) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6)))))
					{ curr_x += 5; }

				else if (!NE3_enemy && !SE3_enemy && curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if	(SW3_enemy && SE3_enemy && ((curr_y < 20) || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50 && curr_x > 27) || (curr_x < 15 && curr_x > 4) || (curr_x < 80 && curr_x > 68)))))
					{ curr_y += 5; }
				else if (SW3_enemy && !SE3_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x > 27) || (curr_x < 10 && curr_x > 4)))))
					{ curr_y += 5; }
				else if (!SW3_enemy && SE3_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50) || (curr_x > 68 && curr_x < 73)))))
					{ curr_y += 5; }
				else if (!SE3_enemy && !SW3_enemy && curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(NW3_enemy, NE3_enemy, SW3_enemy, SE3_enemy); 
			break;
			
			
		case room4:
			tmpG = ~PINA;
			room = 4;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				nokia_draw_enemies(NW4_enemy, NE4_enemy, SW4_enemy, SE4_enemy);
				str_out = 1;
			}
			
			if ((tmpG & 0x10) == 0x10) {
				if	(NW4_enemy && 
					((curr_x <= 15 && curr_y <= 6) || (curr_x < 6 && (curr_y > 10 && curr_y < 15) )))
					{ NW4_enemy = 0; score += 5; }
				if	(SW4_enemy && 
					((curr_y >= 25 && ((curr_x <= 34 && curr_x > 28) || (curr_x < 10 && curr_x > 4)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x > 15 && curr_x < 30)) ))
					{ SW4_enemy = 0; score += 5; }
				if	(NE4_enemy &&
					(((curr_x < 70 && curr_x > 60) && curr_y <= 6) || ((curr_x < 83 && curr_x > 72) && (curr_y > 10 && curr_y < 15) )))
					{ NE4_enemy = 0; score += 5; }
				if	(SE4_enemy &&
					((curr_y >= 25 && ((curr_x < 55 && curr_x > 45) || (curr_x < 75 && curr_x > 68))) 
					|| ((curr_y < 25 && curr_y > 20) && (curr_x < 73 && curr_x > 58))))
					{ SE4_enemy = 0; score += 5; }
						
			}
			//MOVE LEFT
			else if ((tmpG & 0x01) == 0x01) {
				if	(NW4_enemy && SW4_enemy && ((curr_y > 11 && curr_y < 25 && curr_x > 4) ||
					((curr_y <= 11 && curr_x > 15) || 
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68))))))	
					{ curr_x -= 5; }
				else if (NW4_enemy && !SW4_enemy && ((curr_y > 11 && curr_x > 4) 
						|| (curr_y <= 11 && curr_x > 15) ))
						{ curr_x -= 5; }
				else if (!NW4_enemy && SW4_enemy && ((curr_y < 25 && curr_x > 4) ||
						(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68)))))
						{ curr_x -= 5; }
				else if (!NW4_enemy && !SW4_enemy && curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE UP
			else if ((tmpG & 0x02) == 0x02) {
				if	(NW4_enemy && NE4_enemy && ((curr_y > 15) || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68 && curr_x > 11))))
					{ curr_y -= 5; }
				else if (NW4_enemy && !NE4_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					 && (curr_x > 11))))
					{ curr_y -= 5; }
				else if (!NW4_enemy && NE4_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5) 
					 && (curr_x < 68))))
					 { curr_y -= 5; }
				else if (!NW4_enemy && !NE4_enemy && curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE RIGHT
			else if ((tmpG & 0x04) == 0x04) {
				if	(NE4_enemy && SE4_enemy && ((curr_y > 11 && curr_y < 25 && curr_x < 73) ||
					(curr_y <= 11 && curr_x < 63) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6 )))))
					{ curr_x += 5; }
				else if (NE4_enemy && !SE4_enemy && ((curr_y > 11 && curr_x < 73)
					|| (curr_y <= 11 && curr_x < 63) ))
					{ curr_x += 5; }
				else if (!NE4_enemy && SE4_enemy && ((curr_y < 25 && curr_x < 73) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6)))))
					{ curr_x += 5; }

				else if (!NE4_enemy && !SE4_enemy && curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if	(SW4_enemy && SE4_enemy && ((curr_y < 20) || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50 && curr_x > 27) || (curr_x < 15 && curr_x > 4) || (curr_x < 80 && curr_x > 68)))))
					{ curr_y += 5; }
				else if (SW4_enemy && !SE4_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x > 27) || (curr_x < 10 && curr_x > 4)))))
					{ curr_y += 5; }
				else if (!SW4_enemy && SE4_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50) || (curr_x > 68 && curr_x < 73)))))
					{ curr_y += 5; }
				else if (!SE4_enemy && !SW4_enemy && curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y); 
			nokia_draw_enemies(NW4_enemy, NE4_enemy, SW4_enemy, SE4_enemy);
			break;
			
			
		case room5:
			tmpG = ~PINA;
			room = 5;
			if (!str_out)
			{
				nokia_transition_screen();
				_delay_ms(2500);
				nokia_draw_character(start_x, start_y);
				nokia_draw_enemies(NW5_enemy, NE5_enemy, SW5_enemy, SE5_enemy);
				str_out = 1;
			}
			if ((tmpG & 0x10) == 0x10) {
				if	(NW5_enemy &&
					((curr_x <= 15 && curr_y <= 6) || (curr_x < 6 && (curr_y > 10 && curr_y < 15) )))
					{ NW4_enemy = 0; score += 5; }
				if	(SW5_enemy &&
					((curr_y >= 25 && ((curr_x <= 34 && curr_x > 28) || (curr_x < 10 && curr_x > 4)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x > 15 && curr_x < 30)) ))
					{ SW5_enemy = 0; score += 5; }
				if	(NE5_enemy &&
					(((curr_x < 70 && curr_x > 60) && curr_y <= 6) || ((curr_x < 83 && curr_x > 72) && (curr_y > 10 && curr_y < 15) )))
					{ NE5_enemy = 0; score += 5; }
				if	(SE5_enemy &&
					((curr_y >= 25 && ((curr_x < 55 && curr_x > 45) || (curr_x < 75 && curr_x > 68)))
					|| ((curr_y < 25 && curr_y > 20) && (curr_x < 73 && curr_x > 58))))
					{ SE5_enemy = 0; score += 5; }
				
			}
			//MOVE LEFT
			if ((tmpG & 0x01) == 0x01) {
				if	(NW5_enemy && SW5_enemy && ((curr_y > 11 && curr_y < 25 && curr_x > 4) ||
					((curr_y <= 11 && curr_x > 15) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68))))))
					{ curr_x -= 5; }
				else if (NW5_enemy && !SW5_enemy && ((curr_y > 11 && curr_x > 4)
					|| (curr_y <= 11 && curr_x > 15) ))
					{ curr_x -= 5; }
				else if (!NW5_enemy && SW5_enemy && ((curr_y < 25 && curr_x > 4) ||
					(curr_y >= 25 && ((curr_x > 30 && curr_x < 50) || (curr_x < 73 && curr_x > 68)))))
					{ curr_x -= 5; }
				else if (!NW5_enemy && !SW5_enemy && curr_x > 4) { curr_x -= 5; }
				else if ((curr_y >= 19 && curr_y <= 28)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE UP
			else if ((tmpG & 0x02) == 0x02) {
				if	(NW5_enemy && NE5_enemy && ((curr_y > 15) || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68 && curr_x > 11))))
					{ curr_y -= 5; }
				else if (NW5_enemy && !NE5_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x > 11))))
					{ curr_y -= 5; }
				else if (!NW5_enemy && NE5_enemy && (curr_y > 15 || ((curr_y <= 15 && curr_y > 5)
					&& (curr_x < 68))))
					{ curr_y -= 5; }
				else if (!NW5_enemy && !NE5_enemy && curr_y > 5) { curr_y -= 5; }
				else if ((curr_x >= 35 && curr_x <= 48)) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE RIGHT
			else if ((tmpG & 0x04) == 0x04) {
				if	(NE5_enemy && SE5_enemy && ((curr_y > 11 && curr_y < 25 && curr_x < 73) ||
					(curr_y <= 11 && curr_x < 63) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6 )))))
					{ curr_x += 5; }
				else if (NE5_enemy && !SE5_enemy && ((curr_y > 11 && curr_x < 73)
					|| (curr_y <= 11 && curr_x < 63) ))
					{ curr_x += 5; }
				else if (!NE5_enemy && SE5_enemy && ((curr_y < 25 && curr_x < 73) ||
					(curr_y >= 25 && ((curr_x < 49 && curr_x > 28) || (curr_x < 6)))))
					{ curr_x += 5; }

				else if (!NE5_enemy && !SE5_enemy && curr_x < 73) { curr_x += 5; }
				else if (curr_y >= 19 && curr_y <= 28) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			
			//MOVE DOWN
			else if ((tmpG & 0x08) == 0x08) {
				if	(SW5_enemy && SE5_enemy && ((curr_y < 20) || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50 && curr_x > 27) || (curr_x < 15 && curr_x > 4) || (curr_x < 80 && curr_x > 68)))))
					{ curr_y += 5; }
				else if (SW5_enemy && !SE5_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x > 27) || (curr_x < 10 && curr_x > 4)))))
					{ curr_y += 5; }
				else if (!SW5_enemy && SE5_enemy && (curr_y < 20 || ((curr_y > 20 && curr_y < 30)
					&& ((curr_x < 50) || (curr_x > 68 && curr_x < 73)))))
					{ curr_y += 5; }
				else if (!SE5_enemy && !SW5_enemy && curr_y < 32) { curr_y += 5; }
				else if (curr_x >= 35 && curr_x <= 48) {
					move_rooms = 1;
					curr_x = start_x; curr_y = start_y;
					break;
				}
			}
			nokia_draw_character(curr_x, curr_y);
			nokia_draw_enemies(NW5_enemy, NE5_enemy, SW5_enemy, SE5_enemy); 
			nokia_draw_exit(); 
			break;
			
			
		case win:
			if (!str_out) {
				nokia_lcd_clear();
				nokia_lcd_write_string(" You Escaped!", 1);
				nokia_lcd_set_cursor(0, 20);
				if (score == 100) { nokia_lcd_write_string("  Score: 100!", 1); }
				else {
					nokia_lcd_write_string("  Score: ", 1);
					nokia_lcd_set_cursor(50, 20);
					nokia_lcd_write_char((score / 10) + '0',1);
					nokia_lcd_set_cursor(57, 20);
					nokia_lcd_write_char((score % 10) + '0',1);
					
				}
				//nokia_lcd_write_string("  For now...", 1);
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
				nokia_lcd_write_string("  Resume",1);
				nokia_lcd_set_cursor(0, 30);
				nokia_lcd_write_string("  Settings",1);
				nokia_lcd_set_cursor(0, 40);
				nokia_lcd_write_string("  Exit",1);
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
			
	} // End State Actions
}
