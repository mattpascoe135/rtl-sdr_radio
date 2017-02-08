/** fm.h
  * 
  *
  */
#ifndef _FM_H_
#define _FM_H_

#include "rtl.h"

//Definitions
#define RADIO_TEXT 		64
 

//Type defs.
struct rds_t{
	double alternativeFreq;		//Not really intersted in this...
	char *clockTime;
	char *programmeService;
	char *radioText;
};
typedef struct rds_t rds;

typedef enum audio_t {MONO, STEREO} Audio;


//Function definitions
void fm_thread_handler();
void *fm_mono_decoder();
void *fm_stereo_decoder();
void fm_rds_decoder();


#endif