/** fm.c
 *
 *
 * 
 *
 */

#include "fm.h"

#define RDS_DECODE

void fm_thread_handler() {
	//Determine which decoder to thread
	
}


/** fm_mono_decoder
  *
  */
void *fm_mono_decoder(rtlsdr_dev_t *device) {
	unsigned char buffer[BYTES_TO_READ];
	double processedData[BYTES_TO_READ/2];
	int bytesRead;

	//While the rtlsdr device can be read from, read from it
	while(!(rtlsdr_read_sync(device, buffer, BYTES_TO_READ, &bytesRead))) {
		get_phase_data(buffer, processedData);
		//LPF
		//send data to the speakers

#ifdef RDS_DECODE
		//thread rds decode with the provided data
#endif
	}
	return NULL;
}






/** fm_stereo_decoder
  *
  */
void *fm_stereo_decoder(rtlsdr_dev_t *device) {
	unsigned char buffer[BYTES_TO_READ];
	double processedData[BYTES_TO_READ/2];
	int bytesRead;

	//While the rtlsdr device can be read from, read from it
	while(!(rtlsdr_read_sync(device, buffer, BYTES_TO_READ, &bytesRead))) {
		get_phase_data(buffer, processedData);
		//BPF
		//send data to the speakers

#ifdef RDS_DECODE
		//thread rds decode with the provided data
#endif
	}
	return NULL;
}







/** fm_rds_decoder()
  *
  */
void fm_rds_decoder() {
}