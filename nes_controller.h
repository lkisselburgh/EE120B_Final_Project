/*
unsigned char NESData = 0x20;       // this is the pin that the Data connection is connected to
unsigned char NESLatch = 0x40;         // this is the pin that the Latch (otherwise known as strobe) connection is connected to
unsigned char NESClock = 0x80;         // this is the pin that the Clock connection is connected to
unsigned char NESButtonData;         // This is where we will store the received data that comes from the NES Control Pad

void GetNESControllerData(){            // this is where it all happens as far as grabbing the NES control pad data
	//digitalWrite(NESLatch, HIGH);       // we need to send a clock pulse to the latch (strobe connection)...
	//digitalWrite(NESLatch, LOW);        // this will cause the status of all eight buttons to get saved within the 4021 chip in the NES control pad.
	PORTA |= (1<<NESLatch);
	PORTA &= ~(1<<NESLatch);
	
	for(int x=0; x<=7; x++){         // Now we need to transmit the eight bits of data serially from the NES control pad to the Arduino
		//bitWrite(NESButtonData,x,digitalRead(NESData)); // one by one, we will read from the NESData line and store each bit in the NESButtonData variable.
		//writes value of digitalRead(NESData) to bit x of NESButtonData
		NESButtonData |= (x << (PINA & ~(NESData)));
		//digitalWrite(NESClock, HIGH);                   // once each bit is saved, we send a clock pulse to the NES clock connection...
		//digitalWrite(NESClock, LOW);                    // this will now shift all bits in the 4021 chip in the NES control pad, so we can read the next bit.
		PORTA |= (1<<NESClock);
		PORTA &= ~(1<<NESClock);
	}
}
*/
/*
#include <avr/io.h>

//pins
#define LATCH	PORTA6
#define CLOCK	PORTA7
#define DATA 	PORTA5

//button bit order 0-15 --> B, Y, SELECT, START, UP, DOWN, LEFT, RIGHT, A, X, L, R, NA, NA, NA, NA

uint16_t data = 0x0000; //16 bits of controller data

int main(void) {
	DDRA = 0xC0;
	PORTA &= ~(1 << LATCH) & ~(1 << CLOCK); //sets latch and clock low
}

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
}*/