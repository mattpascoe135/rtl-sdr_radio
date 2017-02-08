#include "rtl.h"


#define DEBUG


/** initalise_rtlsdr
  *
  */
rtlsdr_dev_t *initalise_rtlsdr(int centerFreq, int freqCorrection, int sampleRate) {
	uint32_t deviceCount;
    rtlsdr_dev_t *device;
	int i;

	//Get the available RTL-SDR devices, procede if one is detected
	deviceCount = rtlsdr_get_device_count();
	if(deviceCount > 0) {
#ifdef DEBUG
		for(i=0; i<deviceCount; i++) {
			char manufacturer[PRODUCT_LENGTH];
			char product[PRODUCT_LENGTH];
			char serial[PRODUCT_LENGTH];

			std::cout << "Device " << i << std::endl;
			std::cout << "\tName: " << rtlsdr_get_device_name(i) << std::endl;
			rtlsdr_get_device_usb_strings(i, manufacturer, product, serial);
			std::cout << "\tManufacturer: " << manufacturer << std::endl;
			std::cout << "\tProduct: " << product << std::endl;
			std::cout << "\tSerial: " << serial << std::endl;
		}
#endif

#ifdef DEBUG
		std::cout << "Name: " << rtlsdr_get_device_name(DEFAULT_DEVICE) << std::endl;
        std::cout << "(RET) rtlsdr_open = " << rtlsdr_open(&device, DEFAULT_DEVICE) << std::endl;
        std::cout << "(RET) rtlsdr_set_center_freq = " << rtlsdr_set_center_freq(device, FREQUENCY) << std::endl;
        std::cout << "(RET) rtlsdr_set_sample_rate = " << rtlsdr_set_sample_rate(device, SAMPLE_RATE) << std::endl;
        std::cout << "(RET) rtlsdr_set_freq_correction = " << rtlsdr_set_freq_correction(device, CORRECTION) << std::endl;
        std::cout << "(RET) rtlsdr_reset_buffer = " << rtlsdr_reset_buffer(device) << std::endl;
#else
        rtlsdr_open(&device, DEFAULT_DEVICE);
        rtlsdr_set_center_freq(device, FREQUENCY);
        rtlsdr_set_center_freq(device, FREQUENCY);
        rtlsdr_set_sample_rate(device, SAMPLE_RATE);
        rtlsdr_set_freq_correction(device, CORRECTION);
#endif
	} else {
		std::cout << "No RTL-SDR devices could be located, please ensure that a RTL-SDR is connected to your computer." << std::endl;
	}

	return device;
}




/** get_phase_data
  *
  */
double *get_phase_data(unsigned char *buffer, double *processed) {
	int iIdx=0, qIdx=0, i;
    unsigned char iData[BYTES_TO_READ / 2];
    unsigned char qData[BYTES_TO_READ / 2];
    double phaseData[BYTES_TO_READ / 2];

    //Seperate I & Q values
    for(i=0; i<BYTES_TO_READ; i+=2) {
        iData[iIdx++] = buffer[i];
        qData[qIdx++] = buffer[i + 1];
    }

    //Convert I&Q values, and perform phase correction
    phaseData[0] = atan2(iData[0], qData[0]);
    for(i=1; i<BYTES_TO_READ/2; i++) {
        phaseData[i] = atan2(iData[i], qData[i]);
        processed[i-1] = phaseData[i] - phaseData[i-1];
    }

    return &processed;
}




/** fast_atan2
  *
  */
double fast_atan2(double y, double x) {
	double result=0;
	return result;
}