#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int count = 0, flag = 0;
char seg[6] = { 0 };
void disp(void) {

	for (int num_seg = 0; num_seg < 6; num_seg++) {
		PORTA = 1 << num_seg;
		PORTC = seg[num_seg];
		_delay_ms(5);
	}
}

void Updatee(void) {
	seg[0]++;
	if (seg[0] == 10) {
		seg[0] = 0;
		seg[1]++;
		if (seg[1] == 6 && seg[0] == 0) {
			seg[1] = 0;
			seg[2]++;
		}

	}
	if (seg[2] == 10) {
		seg[2] = 0;
		seg[3]++;
		if (seg[3] == 6 && seg[2] == 0) {
			seg[2] = 0;
			seg[3]++;
		}

	}
	if (seg[3] == 10) {

		seg[3] = 0;
		seg[4]++;
		if (seg[4] == 6 && seg[3] == 0) {
			seg[3] = 0;
			seg[4]++;
		}

	}
	if (seg[4] == 10) {
		seg[4] = 0;
		seg[5]++;
		if (seg[5] == 10 && seg[4] == 0) {
			for (int i = 0; i < 6; i++) {
				seg[i] = 0;

			}

			TCNT1 = 0;
		}

	}

}
ISR(TIMER1_COMPA_vect) {
	SREG |= (1 << 7);
	flag = 1;
}
void Timer_1(void) {
	TIFR |= 0x01;       // clear interrupt flag
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	OCR1A = 1000;  // 1 SECOND DELAY 1000 USING 16 BIT TIMER 1 COMPARE VALUE
	TCCR1A = 0x00; // DISABLE TCCR CONTROL ON I/O PINS OF PORTA
	TCNT1 = 0;  // INITIALIZE COUNTER TO 0
	TIMSK |= (1 << OCIE1A); // COMPARE OUTPUT INTERRUPT ENABLE
}
void INT00(void) {
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);

}
ISR(INT0_vect) {
	SREG |= (1 << 7);
	for (int i = 0; i < 6; i++) {
		seg[i] = 0;
	}
	TCNT1 = 0;

}
void INT11(void) {
	MCUCR |= (1 << ISC11) | (1 << ISC10);
	GICR |= (1 << INT1);

}
ISR(INT1_vect) {
	SREG |= (1 << 7);
	TCCR1B = 0;

}

void INT22(void) {
	MCUCSR &= ~(1 << ISC2);
	GICR |= (1 << INT2);
}
ISR(INT2_vect) {
	SREG |= (1 << 7);
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

}
int main() {
	DDRC |= 0X0F;
	PORTC &= ~0X0F;
	DDRA |= 0X00;
	PORTA &= 0X00;
	SREG |= (1 << 7);
	Timer_1();
	DDRD &= ~(1 << 3);
	PORTD |= (1 << 3);
	DDRD &= ~(1 << 4);
	DDRB &= ~(1 << 3);
	PORTB |= (1 << 3);
	INT00();
	INT11();
	INT22();
	while (1) {
		disp();
		if (flag == 1) {
			flag = 0;
			Updatee();
		}
	}

	return 0;
}
