/** rtl.h
  * 
  *
  */
#ifndef _RTL_H_
#define _RTL_H_

//Includes
#include <rtl-sdr.h>
#include <cmath>

//Definitions
#define BYTES_TO_READ   (0xFFFF + 1)
#define CORRECTION      10
#define FREQUENCY       106.9 * 1000000
#define SAMPLE_RATE     2000000

#define DEFAULT_DEVICE  0
#define PRODUCT_LENGTH  256


//Function definitions
rtlsdr_dev_t *initalise_rtlsdr(int centerFreq, int freqCorrection, int sampleRate);
void deactive_rtlsdr(rtlsdr_dev_t *device)
void get_phase_data(unsigned char *buffer, double *processed);
double fast_atan2(double y, double x);


#endif