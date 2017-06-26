
#ifndef _MQ_GF256_H_
#define _MQ_GF256_H_

#include <stdint.h>

#ifdef  __cplusplus
extern  "C" {
#endif


void mq_gf256_n64_m64_multab( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


void mq_gf256_n64_m64( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );




void mq_gf256_n61_m45_ref( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf256_n61_m45_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


void mq_gf256_n68_m40_ref( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf256_n68_m40_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );





#ifdef  __cplusplus
}
#endif


#endif
