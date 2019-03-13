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

/*unsigned char controller = 0;

#define A_BUTTON	0x01
#define B_BUTTON	0x02
#define SELECT		0x04
#define START		0x08
#define UP			0x10
#define DOWN		0x20
#define LEFT		0x40
#define RIGHT		0x80

//pins
#define LATCH	PORTA6
#define CLOCK	PORTA7
#define DATA 	PORTA5

//button bit order 0-15 --> B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, NA, NA, NA, NA

unsigned char data = 0x00; //16 bits of controller data

//#define CLOCK		PORTA7
//#define LATCH		PORTA6
//#define DATA		PORTA5
//#define SNES_PORT	PORTA
//#define SNES_PIN	PINA
*/
// ============================== 

#include <avr/io.h>
#include "io.c"
#include "pwm.h"
#include "nes_controller.h"
#include "nokia5110.c"
#include "start_menu.h"
#include "timer.h"
#include "game.h"

int main(void)
{   
	DDRA = 0xC0;	PORTA = 0xFF;	//PORTA is input
	DDRB = 0xFF; PORTB = 0x00; // Sets PORTB as output
	//DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned long song_elapsedTime = 400;
	unsigned long menu_elapsedTime = 100;
	unsigned long game_elapsedTime = 100; 
	const unsigned long timerPeriod = 100;
	
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
			}
		}

		PORTB |= pwm;
        while(!TimerFlag); 
        TimerFlag = 0;
		song_elapsedTime += timerPeriod;
		if (!game_running) { menu_elapsedTime += timerPeriod; }
		if (game_running) { game_elapsedTime += timerPeriod; }
    }
	//return 0;
}


/*
void readController(){
	data = 0x0000;

	//pull latch to read new data
	PORTA |= (1 << LATCH);
	_delay_us(12);
	PORTA &= ~(1 << LATCH);
	_delay_us(6);

	//read bits
	for(int i = 0; i > 8; i++){
		PORTA |= (1 << CLOCK);
		_delay_us(6);
		data |= (i << (PINA & ~(DATA)));
		PORTA &= ~(1 << CLOCK);
		_delay_us(6);
	}
}
*/