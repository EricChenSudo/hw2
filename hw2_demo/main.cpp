#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn but1(A1);         // decrease the pre_freq
DigitalIn but2(A2);         // let freq = pre_freq (confirm the freq)
DigitalIn but3(A3);         // increase the pre_freq
AnalogOut Aout(PA_4);       // set the analog output
AnalogIn Ain(A0);           // set the analog input


int pre_freq = 200; // the frequency shown on the uLCD
int freq = 200;     // the confirm frequency (the frequency of the output wave)
float ratio_Aout = 0; // to indicate the voltage I will output
float w_t = (1.0 / 200.0) / 50.0; // the time we need to wait
char step = 0; // see where I am in the period
float ADCdata[100]; // sampled data

char idx = -30;     // the index of the ADCdata array
                    // the reason why I use -30 is that I don't want to
					// sample the wave immediately.
char conf = 0;      // used to determine whether I confirmed already or not

void print_on_uLCD(void) { // print the pre_freq on the uLCD
	uLCD.color(WHITE);
	uLCD.locate(0, 0);
	uLCD.printf("pre_freq = %4D\n", pre_freq);
	uLCD.locate(0, 3);
	uLCD.printf("choose the freq\n");
	uLCD.locate(0, 4);
	uLCD.printf("from 10 to 400Hz\n");
	uLCD.filled_rectangle(100, 10, 0, 20, 0x000000);
	uLCD.filled_rectangle(pre_freq / 4, 10, 0, 20, 0x0000FF);

	
	return;
}

void print_on_uLCD_v2(void) { // print the freq on the uLCD
	uLCD.locate(0, 6);
	uLCD.printf("freq = %4D\n", freq);
	return;
}

int main(){
	int i; // loop index

	// set the mode of the button
	but1.mode(PullNone);
	but2.mode(PullNone);
	but3.mode(PullNone);

	// show the pre_freq on the uLCD
	print_on_uLCD();

    while (1) {

		// scan the button
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

		// Determine whether the magnitude of my triangle wave 
		// should become larger or smaller.
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

		// count how many time should I wait
		w_t = 1000000.0/freq/50 - 30;
		wait_us(w_t);

		// check if I need to sample the wave
		if (conf == 1) {
			if (idx >= 0) ADCdata[idx] = Ain;

			if (idx == 99) { // check if the sampling process is done
				printf("%d\r\n", freq); // output the freq to python
				// output the sampled data
				for (i = 0; i < 100; ++i){
					printf("%f\r\n", ADCdata[i]);
					ThisThread::sleep_for(10ms);
				}
				idx = -30; // reset the flag for the next sampling
				conf = 0;  // reset the flag for the next confirm
			}
			else ++idx; // move to sample next data
		}
    }
}

