#ifndef _PRNG_UTILS_H_
#define _PRNG_UTILS_H_

#include <stdio.h>
#include <stdlib.h>


//#define _DEBUG_PRNG_


#ifdef  __cplusplus
extern  "C" {
#endif


void prng_bytes( unsigned char * a , unsigned _num_byte );

void prng_seed( const unsigned char * a , unsigned _num_byte );


int prng_seed_file( const char * file_name );


#ifdef _DEBUG_PRNG_
unsigned prng_dump_generated( unsigned char * buffer , unsigned size_buffer );
#endif


#ifdef  __cplusplus
}
#endif



#endif

