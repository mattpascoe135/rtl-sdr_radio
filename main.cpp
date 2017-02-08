#include <iostream>
#include <fstream>
#include <rtl-sdr.h>
#include <cmath>


#define BYTES_TO_READ   (0xFFFF + 1)
#define CORRECTION      10
#define FREQUENCY       106.9 * 1000000
#define SAMPLE_RATE     2000000


int main(int argc, char *argv[]) {
    uint32_t deviceCount;
    rtlsdr_dev_t *device;
    unsigned char buffer[BYTES_TO_READ];
    int bytesRead, i, j;
    std::ofstream outFile;
            
    //Setup RTL-SDR
    deviceCount = rtlsdr_get_device_count();
    if(deviceCount > 0) {
        std::cout << "Device 0" << std::endl;
        std::cout << "Name: " << rtlsdr_get_device_name(0) << std::endl;
        std::cout << "(RET) rtlsdr_open = " << rtlsdr_open(&device, 0) << std::endl;
        //std::cout << "(RET) rtlsdr_set_freq_correction = " << rtlsdr_set_freq_correction(device, CORRECTION) << std::endl;
        std::cout << "(RET) rtlsdr_set_center_freq = " << rtlsdr_set_center_freq(device, FREQUENCY) << std::endl;
        std::cout << "(RET) rtlsdr_set_sample_rate = " << rtlsdr_set_sample_rate(device, SAMPLE_RATE) << std::endl;

        std::cout << "(RET) rtlsdr_reset_buffer = " << rtlsdr_reset_buffer(device) << std::endl;
        
        //Write the data out
        outFile.open("output.bin", std::ios::out);
        outFile << std::fixed;

        for(i=0; i<1; i++) {
            std::cout << "(RET) rtlsdr_read_sync = " << rtlsdr_read_sync(device, buffer, BYTES_TO_READ, &bytesRead) << std::endl;

            std::cout << "Bytes read: " << bytesRead << std::endl;


            

            int iIdx = 0;
            int qIdx = 0;
            unsigned char iData[BYTES_TO_READ / 2];
            unsigned char qData[BYTES_TO_READ / 2];

            for(j=0; j<BYTES_TO_READ; j+=2) {
                iData[iIdx++] = buffer[j];
                qData[qIdx++] = buffer[j + 1];
            }

            double phaseData[BYTES_TO_READ / 2];

            for(j=0; j<BYTES_TO_READ/2; j++) {
                phaseData[j] = atan2(iData[j], qData[j]);
            }

            for(j=1; j<BYTES_TO_READ/2 -1; j++) {
                outFile << phaseData[j] - phaseData[j-1] << std::endl;
            }
        }

        outFile.close();

        rtlsdr_close(device);

        std::cout << "Done." << std::endl;
    }    
    
    return 0;
}
