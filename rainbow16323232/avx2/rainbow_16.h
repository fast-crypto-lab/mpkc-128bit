
#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include "rainbow_config.h"

#include "blas.h"

//#define _DEBUG_MPKC_


#ifdef  __cplusplus
extern  "C" {
#endif



struct _rainbow_ckey {
	uint8_t l1_o[32*16];
	uint8_t l1_vo[32][32*16];
	uint8_t l1_vv[TERMS_QUAD_POLY(32)*16];

	uint8_t l2_o[32*16];
	uint8_t l2_vo[32][64*16];
	uint8_t l2_vv[TERMS_QUAD_POLY(64)*16];
};

typedef struct _rainbow_ckey rainbow_ckey;

struct _rainbow_key {
	uint8_t mat_t[_PUB_M * _PUB_M_BYTE];
	uint8_t vec_t[_PUB_M_BYTE];
	uint8_t mat_s[_SEC_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];

	rainbow_ckey ckey;
};

typedef struct _rainbow_key rainbow_key;




void rainbow_genkey( uint8_t * pk , rainbow_key * sk );


#include "mpkc.h"

#define mpkc_interpolate mpkc_interpolate_gf16

#if 1

#include "mq_gf16_m64_vartime.h"
#if defined(_BLAS_AVX2_)
#define rainbow_pubmap mq_gf16_n96_m64_vartime_avx2
#elif defined(_BLAS_SSE_)
#define rainbow_pubmap mq_gf16_n96_m64_vartime_sse
#else
#define rainbow_pubmap mq_gf16_n96_m64_vartime
#endif

#else

#define rainbow_pubmap mpkc_pub_map_gf16

#endif


#define _LEN_SHA256_ 32

void rainbow_secmap( uint8_t * w , const rainbow_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_]);



#define _DEBUG_RAINBOW_

#ifdef _DEBUG_RAINBOW_


unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );

void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );

void rainbow_pubmap_seckey( uint8_t * z , const rainbow_key * sk , const uint8_t * w );

void rainbow_genkey_debug( rainbow_key * pk , rainbow_key * sk );

#endif



#ifdef  __cplusplus
}
#endif


#endif
