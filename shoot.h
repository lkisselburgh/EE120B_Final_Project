
enum{shoot_start, shoot} shoot_state;
void ShootTick()
{
	unsigned char i = 0;
	//unsigned char tick = 0;
	switch(shoot_state)
	{
		case shoot_start:
			shoot_state = shoot;
			break;
		case shoot:
			shoot_state = shoot;
			break;
	}
	switch(shoot_state)
	{
		case shoot_start:
			break;
		case shoot:
			if (room == 4) {
				if (NW1_enemy) {
					nokia_lcd_set_pixel(7, 12, 1);
					//if ( i > 72 ) { }
				}
			}
			i++;
			break;
	}
}
