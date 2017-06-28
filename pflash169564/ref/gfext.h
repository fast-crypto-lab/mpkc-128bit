#ifndef _GF_EXT_H_
#define _GF_EXT_H_


#include "gf16.h"

#include "blas.h"

#include "string.h"

#include "gfext_config.h"

#define _GF_EXT_ 48

#ifdef _USE_PCLMUL_
#include "gfext_aesni.h"

#if 8 == _GF_EXT_

#define ISO gf264_from_2568_sse
#define IVSISO gf2568_from_264_sse
#define BGFADD gf256ext_8_xor
#define BGFMUL gf2ext64_mul_sse
#define BGFMUL_256  gf256ext_8_mul
#define BGFSQU gf2ext64_squ_sse
#define BGFINV gf2ext64_inv_sse
#define BGFPOW8 gf2ext64_pow_8_sse
#define BGFPOW16 gf2ext64_pow_16_sse
#define BGFPOW32 gf2ext64_pow_32_sse

#elif 9 == _GF_EXT_

#define ISO gf272_from_2569_sse
#define IVSISO gf2569_from_272_sse
#define BGFADD gf256ext_9_xor
#define BGFMUL gf2ext72_mul_sse
#define BGFMUL_256  gf256ext_9_mul
#define BGFSQU gf2ext72_squ_sse
#define BGFINV gf2ext72_inv_sse
#define BGFPOW8 gf2ext72_pow_8_sse
#define BGFPOW16 gf2ext72_pow_16_sse
#define BGFPOW32 gf2ext72_pow_32_sse

#elif 12 == _GF_EXT_

#define ISO gf296_from_25612_sse
#define IVSISO gf25612_from_296_sse
#define BGFADD gf256ext_12_xor
#define BGFMUL gf2ext96_mul_sse
#define BGFMUL_256  gf256ext_12_mul
#define BGFSQU gf2ext96_squ_sse
#define BGFINV gf2ext96_inv_sse
#define BGFPOW8 gf2ext96_pow_8_sse
#define BGFPOW16 gf2ext96_pow_16_sse
#define BGFPOW32 gf2ext96_pow_32_sse

#elif 15 == _GF_EXT_

#define ISO gf2120_from_25615_sse
#define IVSISO gf25615_from_2120_sse
#define BGFADD gf256ext_15_xor
#define BGFMUL gf2ext120_mul_sse
#define BGFMUL_256  gf256ext_15_mul
#define BGFSQU gf2ext120_squ_sse
#define BGFINV gf2ext120_inv_sse
#define BGFPOW8 gf2ext120_pow_8_sse
#define BGFPOW16 gf2ext120_pow_16_sse
#define BGFPOW32 gf2ext120_pow_32_sse

#elif 16 == _GF_EXT_

#define ISO gf2128_from_25616_sse
#define IVSISO gf25616_from_2128_sse
#define BGFADD gf256ext_16_xor
#define BGFMUL gf2ext128_mul_sse
#define BGFMUL_256  gf256ext_16_mul
#define BGFSQU gf2ext128_squ_sse
#define BGFINV gf2ext128_inv_sse
#define BGFPOW8 gf2ext128_pow_8_sse
#define BGFPOW16 gf2ext128_pow_16_sse
#define BGFPOW32 gf2ext128_pow_32_sse

#elif 28 == _GF_EXT_

#define ISO gf2224_from_25628_sse
#define IVSISO gf25628_from_2224_sse
#define BGFADD gf256ext_28_xor
#define BGFMUL gf2ext224_mul_sse
#define BGFMUL_256  gf256ext_28_mul
#define BGFSQU gf2ext224_squ_sse
#define BGFINV gf2ext224_inv_sse
#define BGFPOW8 gf2ext224_pow_8_sse
#define BGFPOW16 gf2ext224_pow_16_sse
#define BGFPOW32 gf2ext224_pow_32_sse

#elif 30 == _GF_EXT_

#define ISO gf2240_from_25630_sse
#define IVSISO gf25630_from_2240_sse
#define BGFADD gf256ext_30_xor
#define BGFMUL gf2ext240_mul_sse
#define BGFMUL_256  gf256ext_30_mul
#define BGFSQU gf2ext240_squ_sse
#define BGFINV gf2ext240_inv_sse
#define BGFPOW8 gf2ext240_pow_8_sse
#define BGFPOW16 gf2ext240_pow_16_sse
#define BGFPOW32 gf2ext240_pow_32_sse

#elif 31 == _GF_EXT_

#define ISO gf2248_from_25631_sse
#define IVSISO gf25631_from_2248_sse
#define BGFADD gf256ext_31_xor
#define BGFMUL gf2ext248_mul_sse
#define BGFMUL_256  gf256ext_31_mul
#define BGFSQU gf2ext248_squ_sse
#define BGFINV gf2ext248_inv_sse
#define BGFPOW256_1 gf2ext248_pow_256_1_sse
#define BGFPOW256_2 gf2ext248_pow_256_2_sse
#define BGFPOW256_4 gf2ext248_pow_256_4_sse
#define BGFPOW256_8 gf2ext248_pow_256_8_sse
#define BGFPOW256_15 gf2ext248_pow_256_15_sse
#define BGFPOW256_16 gf2ext248_pow_256_16_sse

#elif 32 == _GF_EXT_

#define ISO gf2256_from_25632_sse
#define IVSISO gf25632_from_2256_sse
#define BGFADD gf256ext_32_xor
#define BGFMUL gf2ext256_mul_sse
#define BGFMUL_256  gf256ext_32_mul
#define BGFSQU gf2ext256_squ_sse
#define BGFINV gf2ext256_inv_sse
#define BGFPOW8 gf2ext256_pow_8_sse
#define BGFPOW16 gf2ext256_pow_16_sse
#define BGFPOW32 gf2ext256_pow_32_sse

#elif 45 == _GF_EXT_

#define ISO gf2360_from_25645_sse
#define IVSISO gf25645_from_2360_sse
#define BGFADD gf256ext_45_xor
#define BGFMUL gf2ext360_mul_sse
#define BGFMUL_256  gf256ext_45_mul
#define BGFSQU gf2ext360_squ_sse
#define BGFINV gf2ext360_inv_sse
#define BGFPOW8 gf2ext360_pow_8_sse
#define BGFPOW16 gf2ext360_pow_16_sse
#define BGFPOW32 gf2ext360_pow_32_sse


#elif 48 == _GF_EXT_

#define ISO gf2384_from_25648_sse
#define IVSISO gf25648_from_2384_sse
#define BGFADD gf256ext_48_xor
#define BGFMUL gf2ext384_mul_sse
#define BGFMUL_256  gf256ext_48_mul
#define BGFSQU gf2ext384_squ_sse
#define BGFINV gf2ext384_inv_sse
#define BGFPOW256_1 gf2ext384_pow_256_1_sse
#define BGFPOW256_2 gf2ext384_pow_256_2_sse
#define BGFPOW256_4 gf2ext384_pow_256_4_sse
#define BGFPOW256_8 gf2ext384_pow_256_8_sse
#define BGFPOW256_15 gf2ext384_pow_256_15_sse
#define BGFPOW256_31 gf2ext384_pow_256_31_sse
#define BGFPOW256_32 gf2ext384_pow_256_32_sse

#else
!!! error here

#endif

#elif defined _USE_SSE_FFT_

#include "gfext_sse.h"

#if 48 == _GF_EXT_

#define ISO identity_384
#define IVSISO identity_384
#define BGFADD gf256ext_48_xor
#define BGFMUL gf256ext_48_mul
#define BGFSQU gf256ext_48_squ
#define BGFPOW256_1 gf256ext_48_pow_256_1
#define BGFPOW256_2 gf256ext_48_pow_256_2
#define BGFPOW256_4 gf256ext_48_pow_256_4
#define BGFPOW256_8 gf256ext_48_pow_256_8
#define BGFPOW256_15 gf256ext_48_pow_256_15
#define BGFPOW256_31 gf256ext_48_pow_256_31
#define BGFPOW256_32 gf256ext_48_pow_256_32

#define TBL_BGFMUL tbl_gf256ext_48_mul_sse
#define TBL_BGFSQU tbl_gf256ext_48_squ_sse
#define TBL_BGFPOW256_1 tbl_gf256ext_48_pow_256_1_sse
#define TBL_BGFPOW256_2 tbl_gf256ext_48_pow_256_2_sse
#define TBL_BGFPOW256_4 tbl_gf256ext_48_pow_256_4_sse
#define TBL_BGFPOW256_8 tbl_gf256ext_48_pow_256_8_sse
#define TBL_BGFPOW256_15 tbl_gf256ext_48_pow_256_15_sse
#define TBL_BGFPOW256_31 tbl_gf256ext_48_pow_256_31_sse
#define TBL_BGFPOW256_32 tbl_gf256ext_48_pow_256_32_sse

#elif 16 == _GF_EXT_

#define ISO identity_128
#define IVSISO identity_128
#define BGFADD gf256ext_16_xor
#define BGFMUL gf256ext_16_mul_sse
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_16_squ
#define BGFINV gf256ext_16_inv
#define BGFPOW8 gf256ext_16_pow_8
#define BGFPOW16 gf256ext_16_pow_16
#define BGFPOW32 gf256ext_16_pow_32

#elif 30 == _GF_EXT_

#define ISO identity_240
#define IVSISO identity_240
#define BGFADD gf256ext_30_xor
#define BGFMUL gf256ext_30_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_30_squ
#define BGFINV gf256ext_30_inv
#define BGFPOW32 gf256ext_30_pow_32

#define TBL_GFMUL tbl_gf256ext_30_mul_sse
#define TBL_GFINV tbl_gf256ext_30_inv_sse
#define TBL_GFPOW32 tbl_gf256ext_30_pow_32_sse
#define TBL_GFADD tbl_gf256ext_30_add_sse


#else

sse fft error here.

#endif


#else

#if 8 == _GF_EXT_

#define ISO identity_64
#define IVSISO identity_64
#define BGFADD gf256ext_8_xor
#define BGFMUL gf256ext_8_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_8_squ
#define BGFINV gf256ext_8_inv
#define BGFPOW8 gf256ext_8_pow_8
#define BGFPOW16 gf256ext_8_pow_16
#define BGFPOW32 gf256ext_8_pow_32

#elif 16 == _GF_EXT_

#define ISO identity_128
#define IVSISO identity_128
#define BGFADD gf256ext_16_xor
#define BGFMUL gf256ext_16_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_16_squ
#define BGFINV gf256ext_16_inv
#define BGFPOW8 gf256ext_16_pow_8
#define BGFPOW16 gf256ext_16_pow_16
#define BGFPOW32 gf256ext_16_pow_32

#elif 30 == _GF_EXT_

#define ISO identity_240
#define IVSISO identity_240
#define BGFADD gf256ext_30_xor
#define BGFMUL gf256ext_30_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_30_squ
#define BGFINV gf256ext_30_inv
#define BGFPOW8 gf256ext_30_pow_8
#define BGFPOW16 gf256ext_30_pow_16
#define BGFPOW32 gf256ext_30_pow_32

#elif 31 == _GF_EXT_

#define ISO identity_248
#define IVSISO identity_248
#define BGFADD gf256ext_31_xor
#define BGFMUL gf256ext_31_mul
#define BGFMUL_256  gf256ext_31_mul
#define BGFSQU gf256ext_31_squ
#define BGFINV gf256ext_31_inv
#define BGFPOW256_1 gf256ext_31_pow_256_1
#define BGFPOW256_2 gf256ext_31_pow_256_2
#define BGFPOW256_4 gf256ext_31_pow_256_4
#define BGFPOW256_8 gf256ext_31_pow_256_8
#define BGFPOW256_15 gf256ext_31_pow_256_15
#define BGFPOW256_16 gf256ext_31_pow_256_16

#elif 32 == _GF_EXT_

#define ISO identity_256
#define IVSISO identity_256
#define BGFADD gf256ext_32_xor
#define BGFMUL gf256ext_32_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_32_squ
#define BGFINV gf256ext_32_inv
#define BGFPOW8 gf256ext_32_pow_8
#define BGFPOW16 gf256ext_32_pow_16
#define BGFPOW32 gf256ext_32_pow_32

#elif 48 == _GF_EXT_

#define ISO identity_384
#define IVSISO identity_384
#define BGFADD gf256ext_3_16_xor
#define BGFMUL gf256ext_3_16_mul
#define BGFMUL_256  BGFMUL
#define BGFSQU gf256ext_3_16_squ
#define BGFPOW256_1 gf256ext_3_16_pow_256_1
#define BGFPOW256_2 gf256ext_3_16_pow_256_2
#define BGFPOW256_4 gf256ext_3_16_pow_256_4
#define BGFPOW256_8 gf256ext_3_16_pow_256_8
#define BGFPOW256_15 gf256ext_3_16_pow_256_15
#define BGFPOW256_31 gf256ext_3_16_pow_256_31
#define BGFPOW256_32 gf256ext_3_16_pow_256_32

#else
!!! error here

#endif

#endif






#ifdef  __cplusplus
extern  "C" {
#endif



//////////////////  GF(256^9)  //////////////////////////////////


/// x^72 + x^10 + x^9 + x^3 + 1,
/// X^9 + 0x4


static inline void identity_72( uint8_t * r , const uint8_t * a ) { memcpy(r,a,9); }

static inline
void gf256ext_9_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 9 ); }


/// X^9 + 0x4
static inline
void gf256ext_9_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
#define W9 9
	static const unsigned W = 9;
	uint8_t tmp_mul[W9*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W ); /// XXX
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	gf256v_m0x4_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_9_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 9;
	uint8_t tmp_mul[W9*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	gf256v_m0x4_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}


static inline
void gf256ext_9_pow_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_9_squ(b,a);
	for(unsigned i=0;i<2;i++) gf256ext_9_squ( b , b );
}

static inline
void gf256ext_9_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_9_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_9_squ( b , b );
}

static inline
void gf256ext_9_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_9_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_9_squ( b , b );
}


/// 256^9 - 2 = 0xFFFFFFFFFFFFFFFFFE
static inline
void gf256ext_9_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 9;
	uint8_t tmp[W9] = {0};

	gf256ext_9_squ(tmp,a);
	uint8_t a3[W9]; gf256ext_9_mul(a3,tmp,a);
	gf256ext_9_squ(tmp,a3);
	gf256ext_9_squ(tmp,tmp);
	uint8_t aF[W9]; gf256ext_9_mul(aF,tmp,a3);
	gf256ext_9_squ(tmp,aF);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	uint8_t aFF[W9]; gf256ext_9_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<7;i++) {
		gf256ext_9_pow_256_1(tmp,tmp);
		gf256ext_9_mul(tmp,tmp,aFF);
	}
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_mul(tmp,tmp,aF);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_mul(tmp,tmp,a3);
	gf256ext_9_squ(tmp,tmp);
	gf256ext_9_mul(tmp,tmp,a);
	gf256ext_9_squ(b,tmp);
}





//////////////////  GF(256^15)  //////////////////////////////////


/// x^120 + x^4 + x^3 + x + 1,
/// X^15 + 0x4



static inline void identity_120( uint8_t * r , const uint8_t * a ) { memcpy(r,a,15); }

static inline
void gf256ext_15_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 15 ); }


/// X^15 + 0x4
static inline
void gf256ext_15_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
#define W15 15
	static const unsigned W = 15;
	uint8_t tmp_mul[W15*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W ); /// XXX
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	gf256v_m0x4_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_15_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 15;
	uint8_t tmp_mul[W15*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	gf256v_m0x4_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}

static inline
void gf256ext_15_pow_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_15_squ(b,a);
	for(unsigned i=0;i<2;i++) gf256ext_15_squ( b , b );
}

static inline
void gf256ext_15_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_15_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_15_squ( b , b );
}

static inline
void gf256ext_15_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_15_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_15_squ( b , b );
}

/// 256^15 - 2
static inline
void gf256ext_15_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 15;
	uint8_t tmp[W15] = {0};

	gf256ext_15_squ(tmp,a);
	uint8_t a3[W15]; gf256ext_15_mul(a3,tmp,a);
	gf256ext_15_squ(tmp,a3);
	gf256ext_15_squ(tmp,tmp);
	uint8_t aF[W15]; gf256ext_15_mul(aF,tmp,a3);
	gf256ext_15_squ(tmp,aF);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	uint8_t aFF[W15]; gf256ext_15_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<13;i++) {
		gf256ext_15_pow_256_1(tmp,tmp);
		gf256ext_15_mul(tmp,tmp,aFF);
	}
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_mul(tmp,tmp,aF);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_mul(tmp,tmp,a3);
	gf256ext_15_squ(tmp,tmp);
	gf256ext_15_mul(tmp,tmp,a);
	gf256ext_15_squ(b,tmp);
}





/////////////////////  GF(256^31)  //////////////////////////


static inline
void identity_248( uint8_t * r , const uint8_t * a ) { memcpy(r,a,31); }

static inline
void gf256ext_31_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 31 ); }

/// X^31 + X^3 + 1
static inline
void gf256ext_31_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 31;
	uint8_t tmp_mul[64] = {0};
	for(unsigned i=0;i<W;i++)
		for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_31_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 31;
	uint8_t tmp_mul[64] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}

static inline
void gf256ext_31_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_31_squ( b , b );
}
static inline
void gf256ext_31_pow_256_2( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7+8;i++) gf256ext_31_squ( b , b );
}
static inline
void gf256ext_31_pow_256_4( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7+8*3;i++) gf256ext_31_squ( b , b );
}
static inline
void gf256ext_31_pow_256_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7+8*7;i++) gf256ext_31_squ( b , b );
}
static inline
void gf256ext_31_pow_256_15( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7+8*14;i++) gf256ext_31_squ( b , b );
}
static inline
void gf256ext_31_pow_256_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_31_squ(b,a);
	for(unsigned i=0;i<7+8*15;i++) gf256ext_31_squ( b , b );
}



///////////////////  GF(256^8)  ////////////////////////////



static inline
void identity_64( uint8_t * r , const uint8_t * a ) { *(uint64_t*)r = ((uint64_t*)a)[0]; }

static inline
void gf256ext_8_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 8 ); }


/// x^8 + x^3 + x + 0x10
static inline
void gf256ext_8_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 8;
#define W8 8
	uint8_t tmp_mul[W8*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W ); /// XXX
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}
	gf256v_m0x10_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_8_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 8;
	uint8_t tmp_mul[W8*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}
	gf256v_m0x10_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}


static inline
void gf256ext_8_pow_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_8_squ(b,a);
	for(unsigned i=0;i<2;i++) gf256ext_8_squ( b , b );
}

static inline
void gf256ext_8_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_8_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_8_squ( b , b );
}

static inline
void gf256ext_8_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_8_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_8_squ( b , b );
}


/// 256^8 - 2 = 0xFFFFFFFFFFFFFFFE
static inline
void gf256ext_8_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 8;
	uint8_t tmp[W8] = {0};

	gf256ext_8_squ(tmp,a);
	uint8_t a3[W8]; gf256ext_8_mul(a3,tmp,a);
	gf256ext_8_squ(tmp,a3);
	gf256ext_8_squ(tmp,tmp);
	uint8_t aF[W8]; gf256ext_8_mul(aF,tmp,a3);
	gf256ext_8_squ(tmp,aF);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	uint8_t aFF[W8]; gf256ext_8_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<6;i++) {
		gf256ext_8_pow_256_1(tmp,tmp);
		gf256ext_8_mul(tmp,tmp,aFF);
	}
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_mul(tmp,tmp,aF);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_mul(tmp,tmp,a3);
	gf256ext_8_squ(tmp,tmp);
	gf256ext_8_mul(tmp,tmp,a);
	gf256ext_8_squ(b,tmp);

}





//////////////////////  GF(256^28)   /////////////////////////



static inline
void identity_224( uint8_t * r , const uint8_t * a ) { memcpy(r,a,28); }

static inline
void gf256ext_28_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 28 ); }


/// x^28 + x^3 + x + 0x10
static inline
void gf256ext_28_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
#ifndef W28
#define W28 28
#endif
	static const unsigned W = 28;
	uint8_t tmp_mul[W28*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W );
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}
	gf256v_m0x10_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_28_squ( uint8_t * c , const uint8_t * a )
{
	static const unsigned W = 28;
	uint8_t tmp_mul[W28*2] = {0};

	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}
	gf256v_m0x10_add( tmp_mul , tmp_mul+W , W );

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_28_pow_2_i(uint8_t *b, unsigned i, const uint8_t * a ) {
	gf256ext_28_squ(b,a);
	for(unsigned j=1;j<i;j++) gf256ext_28_squ(b,b);
}

static inline
void gf256ext_28_pow_16( uint8_t * b , const uint8_t * a ) { gf256ext_28_pow_2_i(b,4,a); }

static inline
void gf256ext_28_pow_32( uint8_t * b , const uint8_t * a ) { gf256ext_28_pow_2_i(b,5,a); }

static inline
void gf256ext_28_pow_64( uint8_t * b , const uint8_t * a ) { gf256ext_28_pow_2_i(b,6,a); }

static inline
void gf256ext_28_pow_256_1( uint8_t * b , const uint8_t * a ) { gf256ext_28_pow_2_i(b,8,a); }


/// 256^28 - 2 = 0xFFFF .... FFFE
static inline
void gf256ext_28_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 28;
	uint8_t tmp[W28] = {0};

	gf256ext_28_squ(tmp,a);
	uint8_t a3[W28]; gf256ext_28_mul(a3,tmp,a);
	gf256ext_28_squ(tmp,a3);
	gf256ext_28_squ(tmp,tmp);
	uint8_t aF[W28]; gf256ext_28_mul(aF,tmp,a3);
	gf256ext_28_squ(tmp,aF);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	uint8_t aFF[W28]; gf256ext_28_mul(aFF,tmp,aF);

	memcpy( tmp , aFF , W );
	//for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<26;i++) {
		gf256ext_28_pow_256_1(tmp,tmp);
		gf256ext_28_mul(tmp,tmp,aFF);
	}
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_mul(tmp,tmp,aF);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_mul(tmp,tmp,a3);
	gf256ext_28_squ(tmp,tmp);
	gf256ext_28_mul(tmp,tmp,a);
	gf256ext_28_squ(b,tmp);

}



//////////////////////  GF(256^30)   /////////////////////////





static inline
void identity_240( uint8_t * r , const uint8_t * a ) { memcpy(r,a,30); }

static inline
void gf256ext_30_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 30 ); }


///    x^30 + 0x10 x^3 + x^2 + x + 1,
static inline
void gf256ext_30_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 30;
#define W30 30
	uint8_t tmp_mul[W30*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W );
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+2] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_mul_0x10(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_30_squ( uint8_t * c , const uint8_t * a )
{
	static const unsigned W = 30;
	uint8_t tmp_mul[W30*2] = {0};

	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+2] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_mul_0x10(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_30_pow_2_i(uint8_t *b, unsigned i, const uint8_t * a ) {
	gf256ext_30_squ(b,a);
	for(unsigned j=1;j<i;j++) gf256ext_30_squ(b,b);
}

static inline
void gf256ext_30_pow_16( uint8_t * b , const uint8_t * a ) { gf256ext_30_pow_2_i(b,4,a); }

static inline
void gf256ext_30_pow_32( uint8_t * b , const uint8_t * a ) { gf256ext_30_pow_2_i(b,5,a); }

static inline
void gf256ext_30_pow_64( uint8_t * b , const uint8_t * a ) { gf256ext_30_pow_2_i(b,6,a); }

static inline
void gf256ext_30_pow_256_1( uint8_t * b , const uint8_t * a ) { gf256ext_30_pow_2_i(b,8,a); }


/// 256^28 - 2 = 0xFFFF .... FFFE
static inline
void gf256ext_30_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 30;
	uint8_t tmp[W30] = {0};

	gf256ext_30_squ(tmp,a);
	uint8_t a3[W30]; gf256ext_30_mul(a3,tmp,a);
	gf256ext_30_squ(tmp,a3);
	gf256ext_30_squ(tmp,tmp);
	uint8_t aF[W30]; gf256ext_30_mul(aF,tmp,a3);
	gf256ext_30_squ(tmp,aF);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	uint8_t aFF[W30]; gf256ext_30_mul(aFF,tmp,aF);

	memcpy( tmp , aFF , W );
	//for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<28;i++) {
		gf256ext_30_pow_256_1(tmp,tmp);
		gf256ext_30_mul(tmp,tmp,aFF);
	}
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_mul(tmp,tmp,aF);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_mul(tmp,tmp,a3);
	gf256ext_30_squ(tmp,tmp);
	gf256ext_30_mul(tmp,tmp,a);
	gf256ext_30_squ(b,tmp);

}





//////////////////////  GF(256^32)   /////////////////////////



static inline
void identity_256( uint8_t * r , const uint8_t * a ) { memcpy(r,a,32); }


/// x^32 + 0x10*x^3 + x + 1
static inline
void gf256ext_32_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 32;
#define W32 32
	uint8_t tmp_mul[W32*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W );
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_mul_0x10(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_32_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 32;
	uint8_t tmp_mul[W32*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_mul_0x10(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}


void gf256ext_32_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_32_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_32_squ( b , b );
}

void gf256ext_32_pow_64( uint8_t * b , const uint8_t * a )
{
	gf256ext_32_squ(b,a);
	for(unsigned i=0;i<5;i++) gf256ext_32_squ( b , b );
}


void gf256ext_32_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_32_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_32_squ( b , b );
}


/// 256^32 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf256ext_32_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 32;
	uint8_t tmp[W32] = {0};

	gf256ext_32_squ(tmp,a);
	uint8_t a3[W32]; gf256ext_32_mul(a3,tmp,a);
	gf256ext_32_squ(tmp,a3);
	gf256ext_32_squ(tmp,tmp);
	uint8_t aF[W32]; gf256ext_32_mul(aF,tmp,a3);
	gf256ext_32_squ(tmp,aF);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	uint8_t aFF[W32]; gf256ext_32_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<30;i++) {
		gf256ext_32_pow_256_1(tmp,tmp);
		gf256ext_32_mul(tmp,tmp,aFF);
	}
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_mul(tmp,tmp,aF);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_mul(tmp,tmp,a3);
	gf256ext_32_squ(tmp,tmp);
	gf256ext_32_mul(tmp,tmp,a);
	gf256ext_32_squ(b,tmp);

}




//////////////////////  GF(256^48) := GF(256^3^16)   /////////////////////////



static inline
void identity_384( uint8_t * r , const uint8_t * a ) { memcpy(r,a,48); }


/// x^16 + 0x2 *x^3 + x + 0x10
static inline
void gf256ext_3_16_mul( uint8_t * c , const uint8_t * _a , const uint8_t * _b )
{
#define W16 16
	static const unsigned W = 16;
	uint32_t tmp_mul[W16*2] = {0};
	uint32_t a[W16] = {0};
	uint32_t b[W16] = {0};

	for(unsigned i=0;i<W;i++) a[i] = ((uint32_t)_a[i*3+0])|(((uint32_t)_a[i*3+1])<<8)|(((uint32_t)_a[i*3+2])<<16);
	for(unsigned i=0;i<W;i++) b[i] = ((uint32_t)_b[i*3+0])|(((uint32_t)_b[i*3+1])<<8)|(((uint32_t)_b[i*3+2])<<16);


	for(unsigned i=0;i<W;i++) {
		for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_3_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= gf256_3_mul_0x10( tmp_mul[i]);
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_3_mul_0x2(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) {
		c[i*3+0] = tmp_mul[i]&0xff;
		c[i*3+1] = (tmp_mul[i]>>8)&0xff;
		c[i*3+2] = (tmp_mul[i]>>16)&0xff;
	}
}

static inline
void gf256ext_3_16_squ( uint8_t * c , const uint8_t * _a )
{
	static const unsigned W = 16;
	uint32_t tmp_mul[W16*2] = {0};
	uint32_t a[W16] = {0};
	for(unsigned i=0;i<W;i++) a[i] = ((uint32_t)_a[i*3+0])|(((uint32_t)_a[i*3+1])<<8)|(((uint32_t)_a[i*3+2])<<16);

	for(unsigned i=0;i<W;i++) tmp_mul[i*2] = gf256_3_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= gf256_3_mul_0x10( tmp_mul[i]);
		tmp_mul[i-W+1] ^= tmp_mul[i];
		tmp_mul[i-W+3] ^= gf256_3_mul_0x2(tmp_mul[i]);
	}

	for(unsigned i=0;i<W;i++) {
		c[i*3+0] = tmp_mul[i]&0xff;
		c[i*3+1] = (tmp_mul[i]>>8)&0xff;
		c[i*3+2] = (tmp_mul[i]>>16)&0xff;
	}
}

void gf256ext_3_16_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_2( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*1;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_4( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*3;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*7;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_15( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*14;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_31( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*30;i++) gf256ext_3_16_squ( b , b );
}
void gf256ext_3_16_pow_256_32( uint8_t * b , const uint8_t * a )
{
	gf256ext_3_16_squ(b,a);
	for(unsigned i=0;i<7+8*31;i++) gf256ext_3_16_squ( b , b );
}





//////////////////////  GF(256^48)   /////////////////////////


static inline
void gf256ext_48_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 48 ); }

/// x^48 + x^3 + 0x10*x^2 + 0x4*x + 1
static inline
void gf256ext_48_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
#ifndef W48
#define W48 48
#endif
	static const unsigned W = 48;
	uint8_t tmp_mul[W48*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W );
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= gf256_mul_0x4(tmp_mul[i]);
		tmp_mul[i-W+2] ^= gf256_mul_0x10(tmp_mul[i]);
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}

	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_48_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 48;
	uint8_t tmp_mul[W48*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= tmp_mul[i];
		tmp_mul[i-W+1] ^= gf256_mul_0x4(tmp_mul[i]);
		tmp_mul[i-W+2] ^= gf256_mul_0x10(tmp_mul[i]);
		tmp_mul[i-W+3] ^= tmp_mul[i];
	}

	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}


void gf256ext_48_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_48_squ( b , b );
}

void gf256ext_48_pow_64( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<5;i++) gf256ext_48_squ( b , b );
}


void gf256ext_48_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_2( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*1;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_4( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*3;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_8( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*7;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_15( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*14;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_31( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*30;i++) gf256ext_48_squ( b , b );
}
void gf256ext_48_pow_256_32( uint8_t * b , const uint8_t * a )
{
	gf256ext_48_squ(b,a);
	for(unsigned i=0;i<7+8*31;i++) gf256ext_48_squ( b , b );
}





/// 256^32 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf256ext_48_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 48;
	uint8_t tmp[W48] = {0};

	gf256ext_48_squ(tmp,a);
	uint8_t a3[W48]; gf256ext_48_mul(a3,tmp,a);
	gf256ext_48_squ(tmp,a3);
	gf256ext_48_squ(tmp,tmp);
	uint8_t aF[W48]; gf256ext_48_mul(aF,tmp,a3);
	gf256ext_48_squ(tmp,aF);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	uint8_t aFF[W48]; gf256ext_48_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<46;i++) {
		gf256ext_48_pow_256_1(tmp,tmp);
		gf256ext_48_mul(tmp,tmp,aFF);
	}
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_mul(tmp,tmp,aF);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_mul(tmp,tmp,a3);
	gf256ext_48_squ(tmp,tmp);
	gf256ext_48_mul(tmp,tmp,a);
	gf256ext_48_squ(b,tmp);

}



//////////////////////  GF(256^16)   /////////////////////////




static inline
void identity_128( uint8_t * r , const uint8_t * a ) { memcpy(r,a,16); }

static inline
void gf256ext_16_xor( uint8_t * b , const uint8_t * a ) { gf256v_add( b , a , 16 ); }

/// x^16 + x^5 + x^3 + 0x10
static inline
void gf256ext_16_mul( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 16;
	uint8_t tmp_mul[W16*2] = {0};
	for(unsigned i=0;i<W;i++) {
		gf256v_madd( tmp_mul+i , a , b[i] , W );
		//for( unsigned j=0;j<W;j++) tmp_mul[i+j] ^= gf256_mul( a[i] , b[j] );
	}

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= gf256_mul_0x10(tmp_mul[i]);
		tmp_mul[i-W+3] ^= tmp_mul[i];
		tmp_mul[i-W+5] ^= tmp_mul[i];
	}
	for(unsigned i=0;i<W;i++) c[i] = tmp_mul[i];
}

static inline
void gf256ext_16_squ( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 16;
	uint8_t tmp_mul[W16*2] = {0};
	for(unsigned i=0;i<W;i++) tmp_mul[i<<1] = gf256_squ( a[i] );

	for(unsigned i = (W-1)*2;i>=W;i--) {
		tmp_mul[i-W+0] ^= gf256_mul_0x10(tmp_mul[i]);
		tmp_mul[i-W+3] ^= tmp_mul[i];
		tmp_mul[i-W+5] ^= tmp_mul[i];
	}
	for(unsigned i=0;i<W;i++) b[i] = tmp_mul[i];
}


void gf256ext_16_pow_16( uint8_t * b , const uint8_t * a )
{
	gf256ext_16_squ(b,a);
	for(unsigned i=0;i<3;i++) gf256ext_16_squ( b , b );
}

void gf256ext_16_pow_64( uint8_t * b , const uint8_t * a )
{
	gf256ext_16_squ(b,a);
	for(unsigned i=0;i<5;i++) gf256ext_16_squ( b , b );
}


void gf256ext_16_pow_256_1( uint8_t * b , const uint8_t * a )
{
	gf256ext_16_squ(b,a);
	for(unsigned i=0;i<7;i++) gf256ext_16_squ( b , b );
}


/// 256^16 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf256ext_16_inv( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 32;
	uint8_t tmp[W32] = {0};

	gf256ext_16_squ(tmp,a);
	uint8_t a3[W32]; gf256ext_16_mul(a3,tmp,a);
	gf256ext_16_squ(tmp,a3);
	gf256ext_16_squ(tmp,tmp);
	uint8_t aF[W32]; gf256ext_16_mul(aF,tmp,a3);
	gf256ext_16_squ(tmp,aF);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	uint8_t aFF[W32]; gf256ext_16_mul(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<14;i++) {
		gf256ext_16_pow_256_1(tmp,tmp);
		gf256ext_16_mul(tmp,tmp,aFF);
	}
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_mul(tmp,tmp,aF);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_mul(tmp,tmp,a3);
	gf256ext_16_squ(tmp,tmp);
	gf256ext_16_mul(tmp,tmp,a);
	gf256ext_16_squ(b,tmp);
}



#ifdef  __cplusplus
}
#endif




#endif
