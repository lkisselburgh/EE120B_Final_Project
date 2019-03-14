#include <avr/eeprom.h>

unsigned short pwm;

void set_PWM(double frequency) {
	//static double current_frequency; // Keeps track of the currently set frequency Will only update the registers when the frequency changes, otherwise allows music to play uninterrupted.
	
	//if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter  // prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFF; }
		// prevents OCR0A from underflowing, using prescaler 64     // 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; } // set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (628 * frequency)) - 1; }
		TCNT0 = 0; // resets counter
		//current_frequency = frequency; // Updates the current frequency
	//}
}

void PWM_on() {
	TCCR0A = (1 << COM3A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}


// C G B F#
//unsigned char piano_loop[4] = {65.41, 98.00, 123.47, 92.50};
//1a: G G E E G F# E B C# C#
unsigned char piano_1a[16] = {49.00, 49.00, 49.00, 49.00, 41.20, 41.20, 41.20, 41.20, 49.00, 46.25, 41.20, 61.74, 34.65, 34.65, 34.65, 34.65};
//1b: G G F# F# B G F# B E C B0 E
unsigned char piano_1b[16] = {49.00, 49.00, 49.00, 49.00, 46.25, 46.25, 46.25, 46.25, 61.74, 49.00, 46.25, 61.74, 41.20, 32.70, 30.87, 41.20};
//0a: G0 G0 E0 E0 G0 F#0 E0 B0 C#0 C#0
unsigned char piano_0a[16] = {24.50, 24.50, 24.50, 24.50, 20.60, 20.60, 20.60, 20.60, 24.50, 23.12, 20.60, 30.87, 17.32, 17.32, 17.32, 17.32};
//0b: G0 G0 F#0 F#0 B0 G0 F#0 B0 C1 C1 B0 E1
unsigned short piano_0b[16] = {24.50, 24.50, 24.50, 24.50, 23.12, 23.12, 23.12, 23.12, 30.87, 24.50, 23.12, 30.87, 32.70, 32.70, 30.87, 41.20};

unsigned short A1, B1, A0, B0, pl, it = 0;
unsigned char play_song = 1;

enum Song{song_start, off, play} song_state;
void SongTick ()
{
	switch(song_state)
	{ // Transitions
		case song_start:
			song_state = off;
			break;
		
		case off:
			if (eeprom_read_byte(0) == 1) { song_state = play; }
			else { song_state = off; }
			break;
		
		case play:
			if (eeprom_read_byte(0) == 0) { song_state = off; }
			else { song_state = play; }
			break;
		
		default:
			song_state = song_start;
			break;
	} //Transititions
	
	switch(song_state)
	{ 
		case song_start:
			break;
		case off:
			pl = A1 = B1 = A0 = B0 = it = 0;
			set_PWM(0);
			break;
		
		case play:
			if (it < 2) {
				if (A1 < 16) {
					set_PWM(piano_1a[A1]);
					++A1;
					PORTB = A1;
					break;
				}
				else if (B1 < 16) {
					set_PWM(piano_1b[B1]);
					++B1;
					PORTB = B1;
					break;
				}
				else {A1 = B1 = 0;}
				++it;
				break;
			}
			else if (it >= 2 && it < 4) {
				if (A0 < 16) {
					set_PWM(piano_0a[A0]);
					++A0;
					PORTB = A0;
					break;
				}
				else if (B0 < 16) {
					set_PWM(piano_0b[B0]);
					++B0;
					PORTB = B0;
					break;
				}
				else { A0 = B0 = 0; }
				++it;
				break;
			}
			else { it = 0; }
			break;
		default:
			break;
	} // State Actions
	//return song_state;
}