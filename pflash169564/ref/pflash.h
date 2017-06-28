
#ifndef _PFLASH_H_
#define _PFLASH_H_

#include "pflash_config.h"

#include "blas.h"


#ifdef  __cplusplus
extern  "C" {
#endif

struct pflash_gf16 {
	uint8_t mat_t[_SEC_N * _PUB_N_BYTE];
	uint8_t vec_t[_PUB_N_BYTE];
	uint8_t mat_s[_SEC_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];
};

typedef struct pflash_gf16 pflash_key;




void pflash_genkey( uint8_t * pk , pflash_key * sk );


#define _LEN_SHA256_ 32

void pflash_secmap( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_]);


#if 1

#include "mq_gf16_m64_vartime.h"
#if defined(_BLAS_AVX2_)
#define pflash_pubmap mq_gf16_n95_m64_vartime_avx2
#elif defined(_BLAS_SSE_)
#define pflash_pubmap mq_gf16_n95_m64_vartime_ssse3
#else
#define pflash_pubmap mq_gf16_n95_m64_vartime
#endif

#else

#include "mpkc.h"
#define pflash_pubmap mpkc_pub_map_gf16

#endif



#define _DEBUG_PFLASH_

#ifdef _DEBUG_PFLASH_

void pflash_pubmap_seckey( uint8_t * z , const pflash_key * sk , const uint8_t * w );

void pflash_genkey_debug( pflash_key * pk , pflash_key * sk );

void pflash_central_map( uint8_t * r , const uint8_t * a );

void pflash_ivs_central_map( uint8_t * _r , const uint8_t * _a );

#endif


#ifdef  __cplusplus
}
#endif


#endif
