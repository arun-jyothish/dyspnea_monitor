#include <filters.h>
const float cutoff_freq   = 17.0;  //Cutoff frequency in Hz
const float sampling_time = 0.007; //Sampling time in seconds.
IIR::ORDER  order  = IIR::ORDER::OD4; // Order (OD1 to OD4)

// Low-pass filter
Filter f(cutoff_freq, sampling_time, order);

int i = 80;
uint64_t prev = 0;
uint64_t prev_state_ms = 0;
uint64_t currn = 0;

int menu;					// menu index
int count = 0;
int calib = 20;
float thr = 640.0;

float bpm = 88;			// test value 
float interval = 0;

float respRate ( void );
void loop() {

	currn = millis();
	int ecg_signal = analogRead(A0);
	float filteredval = f.filterIn(ecg_signal);
	Serial.println(filteredval);			// iir filtered signal
	/* delay(30); */
	int dl = 4000;					// timer delay value in ms
	bool st = filteredval > thr ;
	
	if ( st ){
		int temp = millis()  - prev_state_ms ;
		/* if ( temp < 16 &&  temp > 11 ) */
			interval = temp;
		prev_state_ms = millis() ;
	}

	if ( prev + dl < currn ){
		count++;
		prev = currn ;
	}

menu = count % 2;				// number of menu pages ( here 2 )

switch (menu){
	case 0:				// menu page 1
		if(interval){

			bpm = 1000 / interval;		//used math
			bpm += 40;
		}
		else
			bpm = 0;				// When False value read
		bpmPrint( bpm );
		break;
	case 1:				// menu page 2
		{
		bpm = 0;				// When False value read
		respRate( respRate() );
		break;
		}
}

}



float respRate ( void ){
	// function for finding respiratory rate
	float resp_rate = 102.10; 		// test value
	// add code here




	// end code here
	return  resp_rate;
}
