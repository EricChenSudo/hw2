#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn but1(A1);
DigitalIn but2(A2);
DigitalIn but3(A3);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);



// Thread t;
// EventQueue queue(32 * EVENTS_EVENT_SIZE);

int pre_freq = 400;
int freq = 400;
float ratio_Aout = 0;
float w_t = (1.0 / 700.0) / 50.0; // the time we need to wait
char step = 0; // see where I am in the period
float ADCdata[100];
char idx = -30;
char conf = 0;

void print_on_uLCD(void) {
	uLCD.locate(0, 0);
	uLCD.printf("pre_freq = %4D\n", pre_freq);
	return;
}

void print_on_uLCD_v2(void) {
	uLCD.locate(0, 3);
	uLCD.printf("freq = %4D\n", freq);
	return;
}

int main(){
	int i;
	/*uLCD.background_color(DGREY);
    uLCD.cls();
	uLCD.text_inverse(ON);
    uLCD.text_underline(ON);*/
	but1.mode(PullNone);
	but2.mode(PullNone);
	but3.mode(PullNone);
	print_on_uLCD();

    while (1) {
		if (but1 == 1) {
			pre_freq -= 10;
			print_on_uLCD();
		}

		if (but2 == 1) {
			freq = pre_freq;
			conf = 1;
			print_on_uLCD_v2();
		}

		if (but3 == 1) {
			pre_freq += 10;
			print_on_uLCD();
		}


		if (step == 50) {
			ratio_Aout = 0;
			step = 0;
		}
		else if (step < 36) {
			ratio_Aout += 0.025973;
			step++;
		}
		else {
			ratio_Aout -= 0.060606;
			step++;
		}
		
		Aout = ratio_Aout;
		w_t = 1000000.0/freq/50 - 15;
		wait_us(w_t);

		if (conf == 1) {
			if (idx >= 0) ADCdata[idx] = Ain;
			if (idx == 99) {
				printf("%d\r\n", freq);

				for (i = 0; i < 100; ++i){
					printf("%f\r\n", ADCdata[i]);
					ThisThread::sleep_for(10ms);
				}
				idx = -30;
				conf = 0;
			}
			else ++idx;
		}
    }
}

