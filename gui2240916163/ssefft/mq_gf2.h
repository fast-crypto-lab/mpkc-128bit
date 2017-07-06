
#ifndef _MQ_GF2_H_
#define _MQ_GF2_H_

#include <stdint.h>

#ifndef TERMS_QUAD_POLY
#define TERMS_QUAD_POLY(N) (((N)*(N-1)/2)+N)
#endif

#ifdef  __cplusplus
extern  "C" {
#endif

void mq_gf2_n256_m256( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf2_n256_m256_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


void mq_gf2_n256_m224_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf2_n256_m224_vartime_sse( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


#ifdef  __cplusplus
}
#endif


#endif
