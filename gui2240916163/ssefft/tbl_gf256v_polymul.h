#ifndef _TBL_GF256V_POLYMUL_H_
#define _TBL_GF256V_POLYMUL_H_

#include "emmintrin.h"

#ifdef  __cplusplus
extern  "C" {
#endif

void tbl_gf256v_polymul_16( __m128i * r , const __m128i * a , const __m128i * b );

void tbl_gf256v_polymul_32( __m128i * r , const __m128i * a , const __m128i * b );

void tbl_gf256v_polymul_48( __m128i * r , const __m128i * a , const __m128i * b );


void tbl_gf256_3v_polymul_16( __m128i * r , const __m128i * a , const __m128i * b );

void tbl_gf256_3v_polymul_4( __m128i * r , const __m128i * a , const __m128i * b );



#ifdef  __cplusplus
}
#endif

#endif
