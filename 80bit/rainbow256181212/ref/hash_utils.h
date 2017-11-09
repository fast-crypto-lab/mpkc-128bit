#ifndef _SHA256_UTILS_H_
#define _SHA256_UTILS_H_

#include <stdio.h>
#include <stdlib.h>


#ifdef  __cplusplus
extern  "C" {
#endif



int sha256_file( unsigned char * digest , FILE * fp );

int sha256_chain( unsigned char * d2 , const unsigned char * d1 );

int sha256_chain_file( unsigned char * digest , unsigned n_digest , const char * f_name );


#ifdef  __cplusplus
}
#endif



#endif

