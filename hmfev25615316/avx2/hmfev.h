
#ifndef _HMFEV_H_
#define _HMFEV_H_

#include "hmfev_config.h"

#include "blas.h"




#ifdef  __cplusplus
extern  "C" {
#endif


#define KEYNAME(gf,ext,k,a,v) hmfev_##gf_##ext_##k_##a_##v

#define BGF_SIZE HMFEV_BGF_SIZE
#define C_TERMS  HMFEV_TERMS_PER_CPOLY


struct hmfev_cpoly {
	uint8_t vo[_K][_V*_K][BGF_SIZE];
	uint8_t vv[_K][_V*(_V+1)/2][BGF_SIZE];
	//  xx , xy , xz , x , yy , yz , y , zz , z , 1
	uint8_t c_eq[_K][BGF_SIZE * C_TERMS];
};

typedef struct hmfev_cpoly cpoly_t;

struct KEYNAME(_GF,_EXT,_K,_A,_V) {
	uint8_t mat_t[_SEC_M * _SEC_M_BYTE];
	uint8_t vec_t[_SEC_M_BYTE];
	uint8_t mat_s[_PUB_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];

	cpoly_t cpoly;
};

typedef struct KEYNAME(_GF,_EXT,_K,_A,_V) hmfev_key;


static inline
void hmfev_fdump( FILE *fp, const hmfev_key * key ) {
	gf16mat_fdump(fp,key->mat_t,_SEC_M_BYTE,_SEC_M); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_t,_SEC_M_BYTE); fprintf(fp,"\n");

	gf16mat_fdump(fp,key->mat_s,_PUB_N_BYTE,_SEC_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_s,_PUB_N_BYTE); fprintf(fp,"\n");

}


////////////////////////


#define _LEN_SHA256_ 32

void hmfev_genkey( uint8_t * pk , hmfev_key * sk );


unsigned hmfev_secmap( uint8_t * w , const hmfev_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_]);


#include "mpkc.h"

#if 256 == _GF
	#define hmfev_interpolate mpkc_interpolate_gf256
	#ifdef _BLAS_AVX2_
	#include "mq_gf256.h"
	#define hmfev_pub_map mq_gf256_n61_m45_avx2
	#else
	#define hmfev_pub_map mpkc_pub_map_gf256
	#endif
#else
	#define hmfev_pub_map mpkc_pub_map_gf16
	#define hmfev_interpolate mpkc_interpolate_gf16
#endif


////////////////////////

#define _DEBUG_HMFEV_

#ifdef _DEBUG_HMFEV_


void hmfev_central_map( uint8_t * r , const hmfev_key * key , const uint8_t * a );

unsigned hmfev_ivs_central_map( uint8_t * r , const hmfev_key * key , const uint8_t * a );


void hmfev_pubmap_seckey( uint8_t * z , const hmfev_key * sk , const uint8_t * w );

void hmfev_genkey_debug( hmfev_key * pk , hmfev_key * sk );

#endif /// _DEBUG_HMFEV_



#ifdef  __cplusplus
}
#endif



#endif
