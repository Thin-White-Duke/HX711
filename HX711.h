#ifndef HX711_h
#define HX711_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class HX711
{
	private:
		byte PD_SCK;	// Power Down and Serial Clock Input Pin
		byte DOUT;		// Serial Data Output Pin
		byte GAIN;		// amplification factor
		//long  OFFSET = 0;	  // obsolete: used for tare weight
		long  OFFSET_RAW = 0;
		float OFFSET = 0.f;
		float SCALE_M = 1.f;  // default gradient of the calibration function
		float SCALE_B = 0.f;  // ordinate of the calibration function

	public:
		// define clock and data pin, channel, and gain factor
		// channel selection is made by passing the appropriate gain: 128 or 64 for channel A, 32 for channel B
		// gain: 128 or 64 for channel A; channel B works with 32 gain factor only
		HX711(byte dout, byte pd_sck, byte gain = 128);

		HX711();

		virtual ~HX711();

		// Allows to set the pins and gain later than in the constructor
		void begin(byte dout, byte pd_sck, byte gain = 128);

		// check if HX711 is ready
		// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
		// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
		bool is_ready();

		// set the gain factor; takes effect only after a call to read()
		// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
		// depending on the parameter, the channel is also set to either A or B
		void set_gain(byte gain = 128);

		// waits for the chip to be ready and returns a reading
		long read();

		// returns an average reading; times = how many times to read
		long read_average(byte times = 10);

    // set the SCALE values used to convert the raw data to "human readable" data (measure units)
		void set_scale(float scale_m = 1.f, float scale_b = 0.f);

		// set tare by averaging the initial weight over times values
		void set_tare(byte times = 10);

		// // set tare OFFSETs
		void set_offset(double offset);

		// get the tare weight; times = how many times to read the tare value for averaging
		float get_tare(byte times = 10);

    // get the brutto weight; times = how many times to read the tare value for averaging
    float get_weight(byte times = 10);

    // get the current SCALE_M
    float get_scale_m();

    // get the current SCALE_B
    float get_scale_b();

		// obsolete: get the current SCALE
		float get_scale();

		// get the current OFFSET in real weight
		float get_offset();

		// get the current RAW OFFSET
		long get_offset_raw();

		// puts the chip into power down mode
		void power_down();

		// wakes up the chip after power down mode
		void power_up();
};

#endif /* HX711_h */
