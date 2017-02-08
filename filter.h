/** filter.h
  * 
  *
  */
#ifndef _FILTER_H_
#define _FILTER_H_

//Definitions
#define FILTER_LENGTH 		100


//Type defs.


//Function definitions
int *low_pass_filter(int *data, double frequency);
int *high_pass_filter(int *data, double frequency);
int *band_pass_filter(int *data, double lowerBand, double upperBand);


#endif