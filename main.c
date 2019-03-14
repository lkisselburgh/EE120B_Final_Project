/*
 *    Name: Lacey Kisselburgh E-mail: lkiss001@ucr.edu
 *    Lab Section: 022
 *    Custom Lab Project
 *    Project Description: This is a game where the player enters a house full of enemies and trick rooms
 *						   The game is played using a Nokia 5110 LCD screen, analog stick, and buttons
 *    I acknowledge all content contained herein, excluding template or example
 *    code, is my own original work.
 */


// ====== GLOBAL VARIABLES ======

unsigned char game_running = 0;
unsigned char str_out = 0;
unsigned char pos = 0;
unsigned char score = 0;

// ============================== 

#include <avr/io.h>
#include "io.c"
#include "pwm.h"
#include "nes_controller.h"
#include "nokia5110.c"
#include "start_menu.h"
#include "timer.h"
#include "game.h"
#include "shoot.h"

int main(void)
{   
	DDRA = 0xC0;	PORTA = 0xFF;	//PORTA is input
	DDRB = 0xFF; PORTB = 0x00; // Sets PORTB as output
	//DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long song_elapsedTime = 400;
	unsigned long menu_elapsedTime = 100;
	unsigned long game_elapsedTime = 100; 
	unsigned long shoot_elapsedTime = 50;
	const unsigned long timerPeriod = 50;
	
    TimerSet(timerPeriod);
    TimerOn();
    PWM_on();
	nokia_lcd_init();
	srand(time(NULL));
		
    while(1)
    { 	   
		if (song_elapsedTime >= 400) {
			SongTick();
			song_elapsedTime = 0;
			
		}
		if (!game_running) {
			if (menu_elapsedTime >= 100) {
				MenuTick();
				menu_elapsedTime = 0;
			}
		}
		if (game_running) {
			if (game_elapsedTime >= 100) {
				GameTick();
				game_elapsedTime = 0;
				if (!game_running) { break; }
			}
			if (shoot_elapsedTime >= 50) {
				ShootTick();
				shoot_elapsedTime = 0;
			}
		}
		//PORTB = (PORTB & 0xDF) | pwm;
		//PORTB |= pwm;
        while(!TimerFlag); 
        TimerFlag = 0;
		song_elapsedTime += timerPeriod;
		if (!game_running) { menu_elapsedTime += timerPeriod; }
		if (game_running) { 
			game_elapsedTime += timerPeriod; 
			shoot_elapsedTime += timerPeriod;
			menu_elapsedTime = 0;
		}
    }
}