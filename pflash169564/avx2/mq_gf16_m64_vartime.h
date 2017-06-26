
#ifndef _MQ_GF16_M64_VARTIME_H_
#define _MQ_GF16_M64_VARTIME_H_


#ifdef  __cplusplus
extern  "C" {
#endif


void mq_gf16_n96_m64_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf16_n96_m64_vartime_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf16_n96_m64_vartime_ssse3( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


void mq_gf16_n95_m64_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf16_n95_m64_vartime_ssse3( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf16_n95_m64_vartime_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );





#ifdef  __cplusplus
}
#endif


#endif
