#ifndef _GF_EXT_AESNI_H_
#define _GF_EXT_AESNI_H_


//#include "gf16.h"

#include "blas.h"

#include "bitmat_prod.h"

#include "emmintrin.h"
#include "wmmintrin.h"


#ifdef  __cplusplus
extern  "C" {
#endif



#define _MUL_128( c0,c2,a0,b0 ) \
do {\
  __m128i tt = _mm_clmulepi64_si128( a0,b0 , 0x01 ); \
  c0 = _mm_clmulepi64_si128( a0,b0, 0 ); \
  c2 = _mm_clmulepi64_si128( a0,b0, 0x11 ); \
  tt ^= _mm_clmulepi64_si128( a0,b0 , 0x10 ); \
  c0 ^= _mm_slli_si128( tt , 8 ); \
  c2 ^= _mm_srli_si128( tt , 8 ); \
} while(0)



#define _SQU_128( c0,c2,a0 ) \
do {\
  c0 = _mm_clmulepi64_si128( a0,a0, 0 ); \
  c2 = _mm_clmulepi64_si128( a0,a0, 0x11 ); \
} while(0)



#define _MUL_128_KARATSUBA( c0,c1,a0,b0 ) \
do {\
  c0 = _mm_clmulepi64_si128( a0,b0 , 0x00 ); \
  c1 = _mm_clmulepi64_si128( a0,b0 , 0x11 ); \
  __m128i _tt0 = a0^_mm_srli_si128(a0,8); \
  __m128i _tt1 = b0^_mm_srli_si128(b0,8); \
  _tt0 = _mm_clmulepi64_si128( _tt0, _tt1 , 0 )^c0^c1; \
  c0 ^= _mm_slli_si128( _tt0 , 8 ); \
  c1 ^= _mm_srli_si128( _tt0 , 8 ); \
} while(0)




////////////////  GF(2^384)  ////////////////////////


extern uint64_t gf256316to2384[];
extern uint64_t gf2384to256316[];

static inline
void gf256316_from_2384_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_384x384_sse( r , gf2384to256316 , a ); } ///// XXX

static inline
void gf2384_from_256316_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_384x384_sse( r , gf256316to2384 , a ); } ///// XXX

extern uint64_t gf25648to2384[];
extern uint64_t gf2384to25648[];

static inline
void gf25648_from_2384_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_384x384_sse( r , gf2384to25648 , a ); } ///// XXX

static inline
void gf2384_from_25648_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_384x384_sse( r , gf25648to2384 , a ); } ///// XXX



/// x^384 + x^8 + x^7 + x^6 + x^4 + x^3 + x^2 + x + 1   --> 0x1df
static const uint64_t _gf2ext384_reducer[2] __attribute__((aligned(16)))  = {0x1dfULL,0x0ULL};


static inline
void _gf2ext384_reduce_sse(  __m128i * p_x0 , __m128i * p_x128 , __m128i* p_x256 , __m128i x384 , __m128i x512 , __m128i x640 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext384_reducer );
	__m128i x0 = _mm_load_si128( p_x0 );
	__m128i x128 = _mm_load_si128( p_x128 );
	__m128i x256 = _mm_load_si128( p_x256 );

	__m128i tt = _mm_clmulepi64_si128( x640 , reducer , 1 );
	x256 ^= _mm_clmulepi64_si128( x640 , reducer , 0 );
	x384 ^= _mm_srli_si128( tt , 8 );
	x256 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x512 , reducer , 1 );
	x128 ^= _mm_clmulepi64_si128( x512 , reducer , 0 );
	x256 ^= _mm_srli_si128( tt , 8 );
	x128 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x384 , reducer , 1 );
	x0 ^= _mm_clmulepi64_si128( x384 , reducer , 0 );
	x128 ^= _mm_srli_si128( tt , 8 );
	x0 ^= _mm_slli_si128( tt , 8 );

	_mm_store_si128((__m128i*) p_x256 , x256 );
	_mm_store_si128((__m128i*) p_x128 , x128 );
	_mm_store_si128((__m128i*) p_x0 , x0 );
}


// ( a0 + a1 x + a2 x^2 )( b0 + b1 x + b2 x^2 )
// =  a0b0 ( 1 + x )
//  + a1b1 ( x + x^3 )
//  + a2b2 ( x^3 + x^4 )
//  + (a0+a1)(b0+b1) ( x + x^2 )
//  + (a1+a2)(b1+b2) ( x^2 + x^3 )
//  + (a0+a1+a2)(b0+b1+b2)  x^2
static inline
void gf2ext384_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b ) /// XXXX
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a1 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i a2 = _mm_load_si128( (__m128i const *)(a+32) );
	__m128i b0 = _mm_load_si128( (__m128i const *)b );
	__m128i b1 = _mm_load_si128( (__m128i const *)(b+16) );
	__m128i b2 = _mm_load_si128( (__m128i const *)(b+32) );
	__m128i a0b0_0,a0b0_1;
	_MUL_128_KARATSUBA( a0b0_0, a0b0_1 , a0,b0 );
	__m128i a1b1_0,a1b1_1;
	_MUL_128_KARATSUBA( a1b1_0, a1b1_1 , a1,b1 );
	__m128i a2b2_0,a2b2_1;
	_MUL_128_KARATSUBA( a2b2_0, a2b2_1 , a2,b2 );
	__m128i tt0,tt1;
	__m128i a0a1b0b1_0,a0a1b0b1_1;
	tt0 = a0^a1; tt1 = b0^b1;
	_MUL_128_KARATSUBA( a0a1b0b1_0, a0a1b0b1_1 , tt0,tt1 );
	tt0 = tt0^a2; tt1 = tt1^b2;
	__m128i a0a1a2b0b1b2_0,a0a1a2b0b1b2_1;
	_MUL_128_KARATSUBA( a0a1a2b0b1b2_0, a0a1a2b0b1b2_1 , tt0,tt1 );
	tt0 = a1^a2; tt1 = b1^b2;
	__m128i a1a2b1b2_0,a1a2b1b2_1;
	_MUL_128_KARATSUBA( a1a2b1b2_0, a1a2b1b2_1 , tt0,tt1 );
	__m128i c0,c1,c2,c3,c4,c5;
	c0 = a0b0_0; c1 = a0b0_1; c1 ^= a0b0_0; c2 = a0b0_1;
	c1 ^= a1b1_0; c2 ^= a1b1_1; c3 = a1b1_0; c4 = a1b1_1;
	c3 ^= a2b2_0; c4 ^= a2b2_1; c4 ^= a2b2_0; c5 = a2b2_1;
	c1 ^= a0a1b0b1_0; c2 ^= a0a1b0b1_1; c2 ^= a0a1b0b1_0; c3 ^= a0a1b0b1_1;
	c2 ^= a1a2b1b2_0; c3 ^= a1a2b1b2_1; c3 ^= a1a2b1b2_0; c4 ^= a1a2b1b2_1;
	c2 ^= a0a1a2b0b1b2_0; c3 ^= a0a1a2b0b1b2_1;

	_gf2ext384_reduce_sse( &c0 , &c1 , &c2 , c3 , c4 , c5 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c1 );
	_mm_store_si128((__m128i*) (c+32) , c2 );
}


static inline
void gf2ext384_squ_sse( uint8_t * c , const uint8_t * a ) /// XXXX
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a1 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i a2 = _mm_load_si128( (__m128i const *)(a+32) );

	__m128i c0,c1,c2,c3,c4,c5;
	_SQU_128( c0,c1, a0 );
	_SQU_128( c2,c3, a1 );
	_SQU_128( c4,c5, a2 );

	_gf2ext384_reduce_sse( &c0 , &c1 , &c2 , c3 , c4 , c5 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c1 );
	_mm_store_si128((__m128i*) (c+32) , c2 );
}

static inline
void gf2ext384_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext384_squ_sse( b , b );
}
static inline
void gf2ext384_pow_256_2_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7+8*1;i++) gf2ext384_squ_sse( b , b );
}
static inline
void gf2ext384_pow_256_4_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7+8*3;i++) gf2ext384_squ_sse( b , b );
}
static inline
void gf2ext384_pow_256_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7+8*7;i++) gf2ext384_squ_sse( b , b );
}
static inline
void gf2ext384_pow_256_15_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7+8*14;i++) gf2ext384_squ_sse( b , b );
}
static inline
void gf2ext384_pow_256_31_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext384_squ_sse(b,a);
	for(unsigned i=0;i<7+8*30;i++) gf2ext384_squ_sse( b , b );
}

extern uint64_t gf2384_power_256_32[];
static inline
void gf2ext384_pow_256_32_sse( uint8_t * b , const uint8_t * a )
{
	bitmatrix_prod_384x384_sse( b , gf2384_power_256_32 , a );
}


/// 256^48 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext384_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 48;
#define W48 48
	uint8_t tmp[W48] __attribute__((aligned(16))) = {0}; gf2ext384_squ_sse(tmp,a);
	uint8_t a3[W48] __attribute__((aligned(16))); gf2ext384_mul_sse(a3,tmp,a);
	gf2ext384_squ_sse(tmp,a3);
	gf2ext384_squ_sse(tmp,tmp);
	uint8_t aF[W48] __attribute__((aligned(16))); gf2ext384_mul_sse(aF,tmp,a3);
	gf2ext384_squ_sse(tmp,aF);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	uint8_t aFF[W48] __attribute__((aligned(16))); gf2ext384_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W48;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<46;i++) {
		gf2ext384_pow_256_1_sse(tmp,tmp);
		gf2ext384_mul_sse(tmp,tmp,aFF);
	}
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_mul_sse(tmp,tmp,aF);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_mul_sse(tmp,tmp,a3);
	gf2ext384_squ_sse(tmp,tmp);
	gf2ext384_mul_sse(tmp,tmp,a);
	gf2ext384_squ_sse(b,tmp);

}




////////////////  GF(2^360)  ////////////////////////


extern uint64_t gf25640to2360[];

extern uint64_t gf2360to25640[];


static inline
void gf25640_from_2360_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_256x256_sse( r , gf2360to25640 , a ); } ///// XXX

static inline
void gf2360_from_25640_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_256x256_sse( r , gf25640to2360 , a ); } ///// XXX


/// x^360 + x^5 + x^3 + x^2 + 1   --> 0x2d
/// x^384 = x^29 + x^27 + x^26 + x^24 --> 0x2d000000
static const uint64_t _gf2ext360_reducer[2] __attribute__((aligned(16)))  = {0x2d000000ULL, 0x2dULL};
static const uint32_t _gf2ext360_mask_104bit[4] __attribute__((aligned(16)))  = {0xffffffff, 0xffffffff, 0xffffffff, 0xff};

static inline
void _gf2ext360_reduce_sse(  __m128i * p_x0 , __m128i * p_x128 , __m128i* p_x256 , __m128i x384 , __m128i x512 , __m128i x640 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext360_reducer );
	__m128i x0 = _mm_load_si128( p_x0 );
	__m128i x128 = _mm_load_si128( p_x128 );
	__m128i x256 = _mm_load_si128( p_x256 );

	__m128i tt = _mm_clmulepi64_si128( x640 , reducer , 1 );
	x256 ^= _mm_clmulepi64_si128( x640 , reducer , 0 );
	x384 ^= _mm_srli_si128( tt , 8 );
	x256 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x512 , reducer , 1 );
	x128 ^= _mm_clmulepi64_si128( x512 , reducer , 0 );
	x256 ^= _mm_srli_si128( tt , 8 );
	x128 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x384 , reducer , 1 );
	x0 ^= _mm_clmulepi64_si128( x384 , reducer , 0 );
	x128 ^= _mm_srli_si128( tt , 8 );
	x0 ^= _mm_slli_si128( tt , 8 );

	x0 ^= _mm_clmulepi64_si128( _mm_srli_si128(x256,5) , reducer , 0x11 );
	x256 &= *(__m128i*)_gf2ext360_mask_104bit;

	_mm_store_si128((__m128i*) p_x256 , x256 );
	_mm_store_si128((__m128i*) p_x128 , x128 );
	_mm_store_si128((__m128i*) p_x0 , x0 );
}


// ( a0 + a1 x + a2 x^2 )( b0 + b1 x + b2 x^2 )
// =  a0b0 ( 1 + x )
//  + a1b1 ( x + x^3 )
//  + a2b2 ( x^3 + x^4 )
//  + (a0+a1)(b0+b1) ( x + x^2 )
//  + (a1+a2)(b1+b2) ( x^2 + x^3 )
//  + (a0+a1+a2)(b0+b1+b2)  x^2
static inline
void gf2ext360_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b ) /// XXXX
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a1 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i a2 = _mm_load_si128( (__m128i const *)(a+32) );
	__m128i b0 = _mm_load_si128( (__m128i const *)b );
	__m128i b1 = _mm_load_si128( (__m128i const *)(b+16) );
	__m128i b2 = _mm_load_si128( (__m128i const *)(b+32) );
	a2 &= *(__m128i*)_gf2ext360_mask_104bit;
	b2 &= *(__m128i*)_gf2ext360_mask_104bit;
	__m128i a0b0_0,a0b0_1;
	_MUL_128_KARATSUBA( a0b0_0, a0b0_1 , a0,b0 );
	__m128i a1b1_0,a1b1_1;
	_MUL_128_KARATSUBA( a1b1_0, a1b1_1 , a1,b1 );
	__m128i a2b2_0,a2b2_1;
	_MUL_128_KARATSUBA( a2b2_0, a2b2_1 , a2,b2 );
	__m128i tt0,tt1;
	__m128i a0a1b0b1_0,a0a1b0b1_1;
	tt0 = a0^a1; tt1 = b0^b1;
	_MUL_128_KARATSUBA( a0a1b0b1_0, a0a1b0b1_1 , tt0,tt1 );
	tt0 = tt0^a2; tt1 = tt1^b2;
	__m128i a0a1a2b0b1b2_0,a0a1a2b0b1b2_1;
	_MUL_128_KARATSUBA( a0a1a2b0b1b2_0, a0a1a2b0b1b2_1 , tt0,tt1 );
	tt0 = a1^a2; tt1 = b1^b2;
	__m128i a1a2b1b2_0,a1a2b1b2_1;
	_MUL_128_KARATSUBA( a1a2b1b2_0, a1a2b1b2_1 , tt0,tt1 );
	__m128i c0,c1,c2,c3,c4,c5;
	c0 = a0b0_0; c1 = a0b0_1; c1 ^= a0b0_0; c2 = a0b0_1;
	c1 ^= a1b1_0; c2 ^= a1b1_1; c3 = a1b1_0; c4 = a1b1_1;
	c3 ^= a2b2_0; c4 ^= a2b2_1; c4 ^= a2b2_0; c5 = a2b2_1;
	c1 ^= a0a1b0b1_0; c2 ^= a0a1b0b1_1; c2 ^= a0a1b0b1_0; c3 ^= a0a1b0b1_1;
	c2 ^= a1a2b1b2_0; c3 ^= a1a2b1b2_1; c3 ^= a1a2b1b2_0; c4 ^= a1a2b1b2_1;
	c2 ^= a0a1a2b0b1b2_0; c3 ^= a0a1a2b0b1b2_1;

	_gf2ext360_reduce_sse( &c0 , &c1 , &c2 , c3 , c4 , c5 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c1 );
	_mm_store_si128((__m128i*) (c+32) , c2 );
}


static inline
void gf2ext360_squ_sse( uint8_t * c , const uint8_t * a ) /// XXXX
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a1 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i a2 = _mm_load_si128( (__m128i const *)(a+32) );
	a2 &= *(__m128i*)_gf2ext360_mask_104bit;
	__m128i c0,c1,c2,c3,c4,c5;
	_SQU_128( c0,c1, a0 );
	_SQU_128( c2,c3, a1 );
	_SQU_128( c4,c5, a2 );

	_gf2ext360_reduce_sse( &c0 , &c1 , &c2 , c3 , c4 , c5 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c1 );
	_mm_store_si128((__m128i*) (c+32) , c2 );
}

static inline
void gf2ext360_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext360_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext360_squ_sse( b , b );
}
static inline
void gf2ext360_pow_64_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext360_squ_sse(b,a);
	for(unsigned i=0;i<5;i++) gf2ext360_squ_sse( b , b );
}

static inline
void gf2ext360_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext360_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext360_squ_sse( b , b );
}


/// 256^48 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext360_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 45;
#define W45 45
	uint8_t tmp[W45+16] __attribute__((aligned(16))) = {0}; gf2ext360_squ_sse(tmp,a);
	uint8_t a3[W45+16] __attribute__((aligned(16))); gf2ext360_mul_sse(a3,tmp,a);
	gf2ext360_squ_sse(tmp,a3);
	gf2ext360_squ_sse(tmp,tmp);
	uint8_t aF[W45+16] __attribute__((aligned(16))); gf2ext360_mul_sse(aF,tmp,a3);
	gf2ext360_squ_sse(tmp,aF);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	uint8_t aFF[W45+16] __attribute__((aligned(16))); gf2ext360_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W45;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<43;i++) {
		gf2ext360_pow_256_1_sse(tmp,tmp);
		gf2ext360_mul_sse(tmp,tmp,aFF);
	}
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_mul_sse(tmp,tmp,aF);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_mul_sse(tmp,tmp,a3);
	gf2ext360_squ_sse(tmp,tmp);
	gf2ext360_mul_sse(tmp,tmp,a);
	gf2ext360_squ_sse(b,tmp);

}





////////////////  GF(2^256)  ////////////////////////


extern uint64_t gf25632to2256[];

extern uint64_t gf2256to25632[];


static inline
void gf25632_from_2256_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_256x256_sse( r , gf2256to25632 , a ); }

static inline
void gf2256_from_25632_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_256x256_sse( r , gf25632to2256 , a ); }



/// X^256 + X^10 + X^5 + X^2 + 1
/// 0x       4      2        5
static const uint64_t _gf2ext256_reducer[2] __attribute__((aligned(16)))  = {0x425ULL,0x0ULL};


static inline
void _gf2ext256_reduce_sse( __m128i * ptr_x128 , __m128i * ptr_x0 , __m128i x256 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext256_reducer );
	__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i x128 = _mm_load_si128( ptr_x128 );
	x0 ^= _mm_clmulepi64_si128( x256 , reducer , 0 );
	__m128i x64 = _mm_clmulepi64_si128( x256 , reducer , 1 );  /// 0_32 , xx2_32 , xx1 , xx0
	x0 ^= _mm_shuffle_epi32( x64 , 0x4f ); // xx1 , xx0 , 0 , 0   ;  0x4f -->  1,0,3,3  --> xx1,xx0,0,0
	x128 ^= _mm_shuffle_epi32( x64 , 0xfe ); // 0,0,0,xx2 ; 0xfe --> 3,3,3,2
	_mm_store_si128((__m128i*) ptr_x128 , x128 );
	_mm_store_si128((__m128i*) ptr_x0 , x0 );
}

static inline
void gf2ext256_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a128 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i b0 = _mm_load_si128( (__m128i const *)b );
	__m128i b128 = _mm_load_si128( (__m128i const *)(b+16) );
	__m128i c0,c128,c256,c384;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );
	_MUL_128_KARATSUBA( c256,c384, a128,b128 );

	__m128i tt0,tt1;
	a0 ^= a128;
	b0 ^= b128;
	_MUL_128_KARATSUBA( tt0,tt1, a0,b0 );
	tt0 ^= c0 ^ c256;
	tt1 ^= c128 ^ c384;
	c128 ^= tt0;
	c256 ^= tt1;

	_gf2ext256_reduce_sse( &c256 , &c128 , c384 );
	_gf2ext256_reduce_sse( &c128 , &c0 , c256 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c128 );
}


static inline
void gf2ext256_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a128 = _mm_load_si128( (__m128i const *)(a+16) );
	__m128i c0,c128,c256,c384;
	_SQU_128( c0,c128, a0 );
	_SQU_128( c256,c384, a128 );

	_gf2ext256_reduce_sse( &c256 , &c128 , c384 );
	_gf2ext256_reduce_sse( &c128 , &c0 , c256 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_store_si128((__m128i*) (c+16) , c128 );
}

static inline
void gf2ext256_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext256_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext256_squ_sse( b , b );
}
static inline
void gf2ext256_pow_64_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext256_squ_sse(b,a);
	for(unsigned i=0;i<5;i++) gf2ext256_squ_sse( b , b );
}

static inline
void gf2ext256_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext256_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext256_squ_sse( b , b );
}


/// 256^32 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext256_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;
#define W32 32
	uint8_t tmp[W32] __attribute__((aligned(16))) = {0}; gf2ext256_squ_sse(tmp,a);
	uint8_t a3[W32] __attribute__((aligned(16))); gf2ext256_mul_sse(a3,tmp,a);
	gf2ext256_squ_sse(tmp,a3);
	gf2ext256_squ_sse(tmp,tmp);
	uint8_t aF[W32] __attribute__((aligned(16))); gf2ext256_mul_sse(aF,tmp,a3);
	gf2ext256_squ_sse(tmp,aF);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	uint8_t aFF[W32] __attribute__((aligned(16))); gf2ext256_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W32;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<30;i++) {
		gf2ext256_pow_256_1_sse(tmp,tmp);
		gf2ext256_mul_sse(tmp,tmp,aFF);
	}
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_mul_sse(tmp,tmp,aF);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_mul_sse(tmp,tmp,a3);
	gf2ext256_squ_sse(tmp,tmp);
	gf2ext256_mul_sse(tmp,tmp,a);
	gf2ext256_squ_sse(b,tmp);

}



////////////////  GF(2^248)  ////////////////////////


extern uint64_t gf25631to2248[];

extern uint64_t gf2248to25631[];


static inline
void gf25631_from_2248_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_248x248_sse( r , gf2248to25631 , a ); }

static inline
void gf2248_from_25631_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_248x248_sse( r , gf25631to2248 , a ); }


/// x^248 + x^8 + x^5 + x^4 + x^3 + x^2 + 1  --> 0x13d
/// x^256 = .... --> 0x13d00
static const uint64_t _gf2ext248_reducer[2] __attribute__((aligned(16)))  = {0x13d00ULL,0x13dULL};
static const uint32_t _gf2ext248_mask_120bit[4] __attribute__((aligned(16)))  = {0xffffffff,0xffffffff,0xffffffff,0xffffff};


static inline
void _gf2ext248_reduce_sse( __m128i * p_x0 , __m128i * p_x128 , __m128i x256 , __m128i x384 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext248_reducer );
	__m128i x0 = _mm_load_si128( p_x0 );
	__m128i x128 = _mm_load_si128( p_x128 );

	__m128i tt = _mm_clmulepi64_si128( x384 , reducer , 1 );
	x128 ^= _mm_clmulepi64_si128( x384 , reducer , 0 );
	x256 ^= _mm_srli_si128( tt , 8 );
	x128 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x256 , reducer , 1 );
	x0 ^= _mm_clmulepi64_si128( x256 , reducer , 0 );
	x128 ^= _mm_srli_si128( tt , 8 );
	x0 ^= _mm_slli_si128( tt , 8 );

	x0 ^= _mm_clmulepi64_si128( _mm_srli_si128(x128,7) , reducer , 0x11 );
	x128 &= *(__m128i*)_gf2ext248_mask_120bit;

	_mm_store_si128( p_x128 , x128 );
	_mm_store_si128( p_x0 , x0 );
}

static inline
void gf2ext248_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+15) ) , 1 );
	__m128i b0 = _mm_load_si128( (__m128i const *)b );
	__m128i b128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(b+15) ) , 1 );
	__m128i c0,c128,c256,c384;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );
	_MUL_128_KARATSUBA( c256,c384, a128,b128 );

	__m128i tt0,tt1;
	a0 ^= a128;
	b0 ^= b128;
	_MUL_128_KARATSUBA( tt0,tt1, a0,b0 );
	tt0 ^= c0 ^ c256;
	tt1 ^= c128 ^ c384;
	c128 ^= tt0;
	c256 ^= tt1;

	_gf2ext248_reduce_sse( &c0 , &c128 , c256 , c384 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_storeu_si128((__m128i*) (c+15) , _mm_alignr_epi8(c128,c0,15) );
}


static inline
void gf2ext248_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+15) ) , 1 );
	__m128i c0,c128,c256,c384;
	_SQU_128( c0,c128, a0 );
	_SQU_128( c256,c384, a128 );

	_gf2ext248_reduce_sse( &c0 , &c128 , c256 , c384 );
	_mm_store_si128((__m128i*) c , c0 );
	_mm_storeu_si128((__m128i*) (c+15) , _mm_alignr_epi8(c128,c0,15) );
}

static inline
void gf2ext248_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext248_squ_sse( b , b );
}
static inline
void gf2ext248_pow_256_2_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7+8;i++) gf2ext248_squ_sse( b , b );
}
static inline
void gf2ext248_pow_256_4_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7+8*3;i++) gf2ext248_squ_sse( b , b );
}
static inline
void gf2ext248_pow_256_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7+8*7;i++) gf2ext248_squ_sse( b , b );
}
static inline
void gf2ext248_pow_256_15_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7+8*14;i++) gf2ext248_squ_sse( b , b );
}
static inline
void gf2ext248_pow_256_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext248_squ_sse(b,a);
	for(unsigned i=0;i<7+8*15;i++) gf2ext248_squ_sse( b , b );
}


/// 256^32 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext248_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;
	uint8_t tmp[W32] __attribute__((aligned(16))) = {0}; gf2ext248_squ_sse(tmp,a);
	uint8_t a3[W32] __attribute__((aligned(16))); gf2ext248_mul_sse(a3,tmp,a);
	gf2ext248_squ_sse(tmp,a3);
	gf2ext248_squ_sse(tmp,tmp);
	uint8_t aF[W32] __attribute__((aligned(16))); gf2ext248_mul_sse(aF,tmp,a3);
	gf2ext248_squ_sse(tmp,aF);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	uint8_t aFF[W32] __attribute__((aligned(16))); gf2ext248_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W32;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<29;i++) {
		gf2ext248_pow_256_1_sse(tmp,tmp);
		gf2ext248_mul_sse(tmp,tmp,aFF);
	}
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_mul_sse(tmp,tmp,aF);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_mul_sse(tmp,tmp,a3);
	gf2ext248_squ_sse(tmp,tmp);
	gf2ext248_mul_sse(tmp,tmp,a);
	gf2ext248_squ_sse(b,tmp);

}





////////////////  GF(2^240)  ////////////////////////


extern uint64_t gf25630to2240[];

extern uint64_t gf2240to25630[];


static inline
void gf25630_from_2240_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_240x240_sse( r , gf2240to25630 , a ); }

static inline
void gf2240_from_25630_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_240x240_sse( r , gf25630to2240 , a ); }



/// x^240 + x^8 + x^5 + x^3 + 1  --> 0x129
/// x^256 = x^24 + x^21 + x^19 + x^16 --> 0x1290000
static const uint64_t _gf2ext240_reducer[2] __attribute__((aligned(16)))  = {0x1290000ULL,0x129ULL};
static const uint32_t _gf2ext240_mask_112bit[4] __attribute__((aligned(16)))  = {0xffffffff,0xffffffff,0xffffffff,0xffff};


static inline
void _gf2ext240_reduce_sse( __m128i * p_x0 , __m128i * p_x128 , __m128i x256 , __m128i x384 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext240_reducer );
	__m128i x0 = _mm_load_si128( p_x0 );
	__m128i x128 = _mm_load_si128( p_x128 );

	__m128i tt = _mm_clmulepi64_si128( x384 , reducer , 1 );
	x128 ^= _mm_clmulepi64_si128( x384 , reducer , 0 );
	x256 ^= _mm_srli_si128( tt , 8 );
	x128 ^= _mm_slli_si128( tt , 8 );

	tt = _mm_clmulepi64_si128( x256 , reducer , 1 );
	x0 ^= _mm_clmulepi64_si128( x256 , reducer , 0 );
	x128 ^= _mm_srli_si128( tt , 8 );
	x0 ^= _mm_slli_si128( tt , 8 );

	x0 ^= _mm_clmulepi64_si128( _mm_srli_si128(x128,6) , reducer , 0x11 );
	x128 &= *(__m128i*)_gf2ext240_mask_112bit;

	_mm_store_si128( p_x128 , x128 );
	_mm_store_si128( p_x0 , x0 );
}

static inline
void gf2ext240_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_loadu_si128( (__m128i const *)a );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+14) ) , 2 );
	__m128i b0 = _mm_loadu_si128( (__m128i const *)b );
	__m128i b128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(b+14) ) , 2 );
	__m128i c0,c128,c256,c384;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );
	_MUL_128_KARATSUBA( c256,c384, a128,b128 );

	__m128i tt0,tt1;
	a0 ^= a128;
	b0 ^= b128;
	_MUL_128_KARATSUBA( tt0,tt1, a0,b0 );
	tt0 ^= c0 ^ c256;
	tt1 ^= c128 ^ c384;
	c128 ^= tt0;
	c256 ^= tt1;

	_gf2ext240_reduce_sse( &c0 , &c128 , c256 , c384 );
	_mm_storeu_si128((__m128i*) c , c0 );
	_mm_storeu_si128((__m128i*) (c+14) , _mm_alignr_epi8(c128,c0,14) );
}


static inline
void gf2ext240_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_loadu_si128( (__m128i const *)a );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+14) ) , 2 );
	__m128i c0,c128,c256,c384;
	_SQU_128( c0,c128, a0 );
	_SQU_128( c256,c384, a128 );

	_gf2ext240_reduce_sse( &c0 , &c128 , c256 , c384 );
	_mm_storeu_si128((__m128i*) c , c0 );
	_mm_storeu_si128((__m128i*) (c+14) , _mm_alignr_epi8(c128,c0,14) );
}

static inline
void gf2ext240_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext240_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext240_squ_sse( b , b );
}
static inline
void gf2ext240_pow_32_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext240_squ_sse(b,a);
	for(unsigned i=0;i<4;i++) gf2ext240_squ_sse( b , b );
}
static inline
void gf2ext240_pow_64_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext240_squ_sse(b,a);
	for(unsigned i=0;i<5;i++) gf2ext240_squ_sse( b , b );
}

static inline
void gf2ext240_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext240_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext240_squ_sse( b , b );
}


/// 256^32 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext240_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;
	uint8_t tmp[W32] __attribute__((aligned(16))) = {0}; gf2ext240_squ_sse(tmp,a);
	uint8_t a3[W32] __attribute__((aligned(16))); gf2ext240_mul_sse(a3,tmp,a);
	gf2ext240_squ_sse(tmp,a3);
	gf2ext240_squ_sse(tmp,tmp);
	uint8_t aF[W32] __attribute__((aligned(16))); gf2ext240_mul_sse(aF,tmp,a3);
	gf2ext240_squ_sse(tmp,aF);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	uint8_t aFF[W32] __attribute__((aligned(16))); gf2ext240_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W32;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<28;i++) {
		gf2ext240_pow_256_1_sse(tmp,tmp);
		gf2ext240_mul_sse(tmp,tmp,aFF);
	}
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_mul_sse(tmp,tmp,aF);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_mul_sse(tmp,tmp,a3);
	gf2ext240_squ_sse(tmp,tmp);
	gf2ext240_mul_sse(tmp,tmp,a);
	gf2ext240_squ_sse(b,tmp);

}




////////////////  GF(2^224)  ////////////////////////


extern uint64_t gf25628to2224[];

extern uint64_t gf2224to25628[];

static inline
void gf25628_from_2224_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_224x224_sse( r , gf2224to25628 , a ); }
//{memcpy(r,a,28); }

static inline
void gf2224_from_25628_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_224x224_sse( r , gf25628to2224 , a ); }
//{memcpy(r,a,28); }


/// x^224 + x^8 + x^7 + x^5 + x^4 + x^2 + 1
/// 0x       1           b             5
/// x^256 + x^40 + x^39 + x^37 + x^36 + x^34 + x^32
/// 0x       1   ,        b             5           + 32bit 0
static const uint64_t _gf2ext224_reducer[2] __attribute__((aligned(16)))  = {0x1B500000000ULL,0x1B5ULL};


static inline
void _gf2ext224_reduce_sse( __m128i * ptr_x0 , __m128i * ptr_x128 , __m128i x256 , __m128i x384 )
{
	__m128i temp;
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext224_reducer );
	__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i x128 = _mm_load_si128( ptr_x128 );
	x128 ^= _mm_clmulepi64_si128( x384 , reducer , 0 );
	x0 ^= _mm_clmulepi64_si128( x256 , reducer , 0 );
	__m128i x224 = _mm_srli_si128( x128 , 4 );  /// 0_32 , xx_32 , ??_32 , ??_32
	/// erase
	temp = _mm_shuffle_epi32( x224 , 0xbf ); // 0_32 , xx_32 , ? , ? ; 0xbf -->  2,3,3,3  --> xx_32,0,0,0
	x128 ^= temp;
	x0 ^= _mm_clmulepi64_si128( x224 , reducer , 0x11 );
	__m128i x64 = _mm_clmulepi64_si128( x256 , reducer , 1 );  /// xx_32 , xx2_32 , xx1 , xx0
	temp = _mm_castpd_si128( _mm_shuffle_pd( _mm_castsi128_pd(_mm_setzero_si128()) , _mm_castsi128_pd(x64) , 0 ) );
	x0 ^= temp;
	temp = _mm_castpd_si128( _mm_shuffle_pd( _mm_castsi128_pd(x64) , _mm_castsi128_pd(_mm_setzero_si128()) , 1 ) );
	x128 ^= temp;
	_mm_store_si128((__m128i*) ptr_x128 , x128 );
	_mm_store_si128((__m128i*) ptr_x0 , x0 );
}


static inline
void gf2ext224_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_loadu_si128( (__m128i const *)a );
	//__m128i a128 = _mm_loadu_si96( (a+16) );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+12) ) , 4 );
	__m128i b0 = _mm_loadu_si128( (__m128i const *)b );
	//__m128i b128 = _mm_loadu_si96( (b+16) );
	__m128i b128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(b+12) ) , 4 );
	__m128i c0,c128,c256,c384;

	_MUL_128_KARATSUBA( c0,c128, a0,b0 );
	_MUL_128_KARATSUBA( c256,c384, a128,b128 );
	__m128i tt0,tt1;
	a0 ^= a128;
	b0 ^= b128;
	_MUL_128_KARATSUBA( tt0,tt1, a0,b0 );
	tt0 ^= c0 ^ c256;
	tt1 ^= c128 ^ c384;
	c128 ^= tt0;
	c256 ^= tt1;

	_gf2ext224_reduce_sse( &c0 , &c128 , c256 , c384 );

	_mm_storeu_si128((__m128i*) c , c0 );
	//_mm_storeu_si96( (c+16) , c128 );
	_mm_storeu_si128((__m128i*) (c+12) , _mm_alignr_epi8(c128,c0,12) );
}


static inline
void gf2ext224_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_loadu_si128( (__m128i const *)a );
	//__m128i a128 = _mm_loadu_si96( (a+16) );
	__m128i a128 = _mm_srli_si128( _mm_loadu_si128( (__m128i const *)(a+12) ) , 4 );
	__m128i c0,c128,c256,c384;
	_SQU_128( c0,c128, a0 );
	_SQU_128( c256,c384, a128 );

	_gf2ext224_reduce_sse( &c0 , &c128 , c256 , c384 );

	_mm_storeu_si128((__m128i*) c , c0 );
	_mm_storeu_si128((__m128i*) (c+12) , _mm_alignr_epi8(c128,c0,12) );
	//_mm_storeu_si96( (c+16) , c128 );
}

static inline
void gf2ext224_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext224_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext224_squ_sse( b , b );
}
static inline
void gf2ext224_pow_32_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext224_squ_sse(b,a);
	for(unsigned i=0;i<4;i++) gf2ext224_squ_sse( b , b );
}
static inline
void gf2ext224_pow_64_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext224_squ_sse(b,a);
	for(unsigned i=0;i<5;i++) gf2ext224_squ_sse( b , b );
}

static inline
void gf2ext224_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext224_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext224_squ_sse( b , b );
}


/// 224^32 - 2 = 0xFF .... FE
static inline
void gf2ext224_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 28;
#define W28 28
	uint8_t tmp[W28] __attribute__((aligned(16))) = {0}; gf2ext224_squ_sse(tmp,a);
	uint8_t a3[W28] __attribute__((aligned(16))); gf2ext224_mul_sse(a3,tmp,a);
	gf2ext224_squ_sse(tmp,a3);
	gf2ext224_squ_sse(tmp,tmp);
	uint8_t aF[W28] __attribute__((aligned(16))); gf2ext224_mul_sse(aF,tmp,a3);
	gf2ext224_squ_sse(tmp,aF);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	uint8_t aFF[W28] __attribute__((aligned(16))); gf2ext224_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W28;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<26;i++) {
		gf2ext224_pow_256_1_sse(tmp,tmp);
		gf2ext224_mul_sse(tmp,tmp,aFF);
	}
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_mul_sse(tmp,tmp,aF);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_mul_sse(tmp,tmp,a3);
	gf2ext224_squ_sse(tmp,tmp);
	gf2ext224_mul_sse(tmp,tmp,a);
	gf2ext224_squ_sse(b,tmp);

}




////////////////  GF(2^128)  ////////////////////////


extern uint64_t gf25616to2128[];

extern uint64_t gf2128to25616[];


static inline
void gf25616_from_2128_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_128x128_sse( r , gf2128to25616 , a ); }

static inline
void gf2128_from_25616_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_128x128_sse( r , gf25616to2128 , a ); }




/// X^128 + X^7 + X^2 + X + 1
/// 0x       8       7
static const uint64_t _gf2ext128_reducer[2] __attribute__((aligned(16)))  = {0x87ULL,0x0ULL};


static inline
void _gf2ext128_reduce_sse( __m128i * ptr_x0 , __m128i x128 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext128_reducer );
	__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i x64 = _mm_clmulepi64_si128( x128 , reducer , 1 );  /// 0_32 , xx2_32 , xx1 , xx0
	x128 ^= _mm_shuffle_epi32( x64 , 0xfe ); // 0,0,0,xx2 ; 0xfe --> 3,3,3,2
	x0 ^= _mm_shuffle_epi32( x64 , 0x4f ); // xx1 , xx0 , 0 , 0   ;  0x4f -->  1,0,3,3  --> xx1,xx0,0,0
	x0 ^= _mm_clmulepi64_si128( x128 , reducer , 0 );
	_mm_store_si128((__m128i*) ptr_x0 , x0 );
}

static inline
void gf2ext128_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i b0 = _mm_load_si128( (__m128i const *)b );
	__m128i c0,c128;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );

	_gf2ext128_reduce_sse( &c0 , c128 );
	_mm_store_si128((__m128i*) c , c0 );
}


static inline
void gf2ext128_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_load_si128( (__m128i const *)a );
	__m128i c0,c128;
	_SQU_128( c0,c128, a0 );

	_gf2ext128_reduce_sse( &c0 , c128 );
	_mm_store_si128((__m128i*) c , c0 );
}

static inline
void gf2ext128_pow_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext128_squ_sse(b,a);
	for(unsigned i=0;i<2;i++) gf2ext128_squ_sse( b , b );
}
static inline
void gf2ext128_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext128_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext128_squ_sse( b , b );
}

static inline
void gf2ext128_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext128_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext128_squ_sse( b , b );
}

/// 256^16 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void gf2ext128_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 16;
#define W16 16
	uint8_t tmp[W16] __attribute__((aligned(16))) = {0}; gf2ext128_squ_sse(tmp,a);
	uint8_t a3[W16] __attribute__((aligned(16))); gf2ext128_mul_sse(a3,tmp,a);
	gf2ext128_squ_sse(tmp,a3);
	gf2ext128_squ_sse(tmp,tmp);
	uint8_t aF[W16] __attribute__((aligned(16))); gf2ext128_mul_sse(aF,tmp,a3);
	gf2ext128_squ_sse(tmp,aF);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	uint8_t aFF[W16] __attribute__((aligned(16))); gf2ext128_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W16;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<14;i++) {
		gf2ext128_pow_256_1_sse(tmp,tmp);
		gf2ext128_mul_sse(tmp,tmp,aFF);
	}
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_mul_sse(tmp,tmp,aF);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_mul_sse(tmp,tmp,a3);
	gf2ext128_squ_sse(tmp,tmp);
	gf2ext128_mul_sse(tmp,tmp,a);
	gf2ext128_squ_sse(b,tmp);

}


//////////////////////  GF(2^64) /////////////////////////////

/// X^64 + X^4 + X^3 + X + 1

extern uint64_t gf2568to264[];

extern uint64_t gf264to2568[];


static inline
void gf2568_from_264_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_64x64( r , gf264to2568 , a ); }

static inline
void gf264_from_2568_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_64x64( r , gf2568to264 , a ); }



/// X^64 + X^4 + X^3 + X + 1
/// 0x       1       b
static const uint64_t _gf2ext64_reducer[2] __attribute__((aligned(16)))  = {0x1bULL,0x0ULL};

static inline
__m128i _gf2ext64_reduce_sse( __m128i x0 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext64_reducer );
	//__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i rd0 = _mm_clmulepi64_si128( x0 , reducer , 1 );  /// 0_32 , xx2_32 , xx1 , xx0
	__m128i rd1 = _mm_clmulepi64_si128( rd0 , reducer , 1 );  /// 0_32 , xx2_32 , xx1 , xx0
	__m128i rr = _mm_move_epi64( x0^rd0^rd1 );
	//_mm_store_si128((__m128i*) ptr_x0 , x0 );
	return rr;
}

static inline
void gf2ext64_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
//	return gf256ext_8_mul(c,a,b);
	__m128i a0 = _mm_cvtsi64_si128( *(uint64_t *)a );
	__m128i b0 = _mm_cvtsi64_si128( *(uint64_t *)b );

	//tt[0] = *(const uint64_t *)a;
	//__m128i a0 = _mm_load_si128( (__m128i*)tt );
	//tt[0] = *(const uint64_t *)b;
	//__m128i b0 = _mm_load_si128( (__m128i*)tt );

	__m128i c0 = _mm_clmulepi64_si128( a0 , b0 , 0 );
	__m128i r =_gf2ext64_reduce_sse( c0 );
	//_mm_storel_epi64((__m128i*) c , r );
	uint64_t tt[2] __attribute__((aligned(16)));
	_mm_store_si128( (__m128i*)tt , r );
	*(uint64_t*)c = tt[0];
}


static inline
void gf2ext64_squ_sse( uint8_t * c , const uint8_t * a ) {
//	return gf256ext_8_squ(c,a);
	//tt[0] = *(const uint64_t *)a;
	//__m128i a0 = _mm_load_si128( (__m128i*)tt );

	__m128i a0 = _mm_cvtsi64_si128( *(uint64_t *)a );
	__m128i c0 = _mm_clmulepi64_si128( a0 , a0 , 0 );
	__m128i r = _gf2ext64_reduce_sse( c0 );
//	_mm_storel_epi64((__m128i*) c , r );
	uint64_t tt[2] __attribute__((aligned(16)));
	_mm_store_si128( (__m128i*)tt , r );
	*(uint64_t*)c = tt[0];
}


static inline
void gf2ext64_pow_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext64_squ_sse(b,a);
	for(unsigned i=0;i<2;i++) gf2ext64_squ_sse( b , b );
}

static inline
void gf2ext64_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext64_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext64_squ_sse( b , b );
}

static inline
void gf2ext64_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext64_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext64_squ_sse( b , b );
}

/// 256^8 - 2 = 0xFFFFFFFFFFFFFFFE
static inline
void gf2ext64_inv_sse( uint8_t * b , const uint8_t * a )
{

//        static const unsigned W = 8;
#define W8 8

	uint8_t tmp[W8] __attribute__((aligned(16))) = {0};

        gf2ext64_squ_sse(tmp,a);
        uint8_t a3[W8] __attribute__((aligned(16))); gf2ext64_mul_sse(a3,tmp,a);
        gf2ext64_squ_sse(tmp,a3);
        gf2ext64_squ_sse(tmp,tmp);
        uint8_t aF[W8] __attribute__((aligned(16))); gf2ext64_mul_sse(aF,tmp,a3);
        gf2ext64_squ_sse(tmp,aF);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        uint8_t aFF[W8] __attribute__((aligned(16))); gf2ext64_mul_sse(aFF,tmp,aF);
        for(unsigned i=0;i<W8;i++) tmp[i]=aFF[i];
        for(unsigned i=0;i<6;i++) {
                gf2ext64_pow_256_1_sse(tmp,tmp);
                gf2ext64_mul_sse(tmp,tmp,aFF);
        }
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_mul_sse(tmp,tmp,aF);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_mul_sse(tmp,tmp,a3);
        gf2ext64_squ_sse(tmp,tmp);
        gf2ext64_mul_sse(tmp,tmp,a);
        gf2ext64_squ_sse(b,tmp);
//	gf2ext64_mul_sse(b,b,a);


#if 0
	static const unsigned W = 16;
	uint8_t tmp[W] __attribute__((aligned(16))) = {0}; gf2ext64_squ_sse(tmp,a);
	uint8_t a3[W] __attribute__((aligned(16))); gf2ext64_mul_sse(a3,tmp,a);
	gf2ext64_squ_sse(tmp,a3);
	gf2ext64_squ_sse(tmp,tmp);
	uint8_t aF[W] __attribute__((aligned(16))); gf2ext64_mul_sse(aF,tmp,a3);
	gf2ext64_squ_sse(tmp,aF);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	uint8_t aFF[W] __attribute__((aligned(16))); gf2ext64_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<8;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<6;i++) {
		gf2ext64_pow_256_1_sse(tmp,tmp);
		gf2ext64_mul_sse(tmp,tmp,aFF);
	}
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_mul_sse(tmp,tmp,aF);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_mul_sse(tmp,tmp,a3);
	gf2ext64_squ_sse(tmp,tmp);
	gf2ext64_mul_sse(tmp,tmp,a);
	gf2ext64_squ_sse(b,tmp);
//	gf2ext64_mul_sse(b,b,a);
#endif
}

















////////////////  GF(2^72)  ////////////////////////


extern uint64_t gf2569to272[];

extern uint64_t gf272to2569[];

static inline
void gf2569_from_272_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_72x72_sse( r , gf272to2569 , a ); }

static inline
void gf272_from_2569_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_72x72_sse( r , gf2569to272 , a ); }


/// x^72 + x^10 + x^9 + x^3 + 1, --> 0x609
/// x^88 --> 0x609 00 00
static const uint64_t _gf2ext72_reducer[2] __attribute__((aligned(16)))  = {0x609ULL, 0x6090000ULL};


static inline
void _gf2ext72_reduce_sse( __m128i * ptr_x0 , __m128i x128 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext72_reducer );
	__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i x88 = _mm_alignr_epi8(x128,x0,11);
	x0 ^= _mm_clmulepi64_si128( reducer , x88 , 1 );
	x88 = _mm_slli_si128( x0 , 5 ); /// erase >= x^88
	x88 = _mm_srli_si128( x88 , 14 );  /// x^72 - x^88
	x0 ^= _mm_clmulepi64_si128( x88 , reducer , 0 );
	x0 = _mm_slli_si128(x0,7);
	x0 = _mm_srli_si128(x0,7);
	_mm_store_si128((__m128i*) ptr_x0 , x0 );
}


static inline
__m128i _mm_loadu_si72( const uint8_t * a ) {
	uint64_t temp[2]  __attribute__((aligned(16))) ={0};
	temp[0] = *(uint64_t*)a;
	*(uint8_t*)&temp[1] = *(uint8_t*)(a+8);
	return _mm_load_si128( (__m128i*) temp );
}

static inline
void _mm_storeu_si72( uint8_t * d , __m128i a ) {
	union uu {
	uint8_t temp[16]  __attribute__((aligned(16)));
	uint64_t temp64[2];
	} ua;
	_mm_store_si128((__m128i *)ua.temp,a);
	*(uint64_t *)d = ua.temp64[0];
	d[8] = ua.temp[8];
}

static inline
void gf2ext72_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_loadu_si72( a );
	__m128i b0 = _mm_loadu_si72( b );
	__m128i c0,c128;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );

	_gf2ext72_reduce_sse( &c0 , c128 );
	_mm_storeu_si72( c , c0 );
}


static inline
void gf2ext72_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_loadu_si72( a );
	__m128i c0,c128;
	_SQU_128( c0,c128, a0 );

	_gf2ext72_reduce_sse( &c0 , c128 );
	_mm_storeu_si72( c , c0 );
}

static inline
void gf2ext72_pow_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext72_squ_sse(b,a);
	for(unsigned i=0;i<2;i++) gf2ext72_squ_sse( b , b );
}
static inline
void gf2ext72_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext72_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext72_squ_sse( b , b );
}
static inline
void gf2ext72_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext72_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext72_squ_sse( b , b );
}


/// 2^72 - 2 = 2^8^9 = 0xFF .... FE
static inline
void gf2ext72_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;
#define W16 16

	uint8_t tmp[W16] __attribute__((aligned(16))) = {0}; gf2ext72_squ_sse(tmp,a);
	uint8_t a3[W16] __attribute__((aligned(16))); gf2ext72_mul_sse(a3,tmp,a);
	gf2ext72_squ_sse(tmp,a3);
	gf2ext72_squ_sse(tmp,tmp);
	uint8_t aF[W16] __attribute__((aligned(16))); gf2ext72_mul_sse(aF,tmp,a3);
	gf2ext72_squ_sse(tmp,aF);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	uint8_t aFF[W16] __attribute__((aligned(16))); gf2ext72_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W16;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<7;i++) {
		gf2ext72_pow_256_1_sse(tmp,tmp);
		gf2ext72_mul_sse(tmp,tmp,aFF);
	}
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_mul_sse(tmp,tmp,aF);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_mul_sse(tmp,tmp,a3);
	gf2ext72_squ_sse(tmp,tmp);
	gf2ext72_mul_sse(tmp,tmp,a);
	gf2ext72_squ_sse(b,tmp);

}











////////////////  GF(2^120)  ////////////////////////


extern uint64_t gf25615to2120[];

extern uint64_t gf2120to25615[];

static inline
void gf25615_from_2120_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_120x120_sse( r , gf2120to25615 , a ); }

static inline
void gf2120_from_25615_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_120x120_sse( r , gf25615to2120 , a ); }


/// x^120 + x^4 + x^3 + x + 1, -->0x1b
// x^128 = x^12 + x^11 + x^9 + x^8 --> 0x1b00
static const uint64_t _gf2ext120_reducer[2] __attribute__((aligned(16)))  = {0x1BULL,0x1B00ULL};


static inline
void _gf2ext120_reduce_sse( __m128i * ptr_x0 , __m128i x128 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext120_reducer );
	__m128i x0 = _mm_load_si128( ptr_x0 );
	__m128i x64 = _mm_clmulepi64_si128( _mm_slli_si128(x128,1) , reducer , 1 );  /// 0_32 , 0_32 , xx1 , xx0
	x0 ^= _mm_slli_si128(x64,8);
	x128 = _mm_alignr_epi8(x128,x0,15);
	x0 ^= _mm_clmulepi64_si128( x128 , reducer , 0 );
	x0 = _mm_slli_si128(x0,1);
	x0 = _mm_srli_si128(x0,1);
	_mm_store_si128((__m128i*) ptr_x0 , x0 );
}




static inline
__m128i _mm_loadu_si120( const uint8_t * a ) {
	uint64_t temp[2]  __attribute__((aligned(16))) ={0};
	temp[0] = *(uint64_t*)a;
	for(int i=0;i<7;i++) ((uint8_t*)&temp[1])[i] = *(uint8_t*)(a+8+i);
	return _mm_load_si128( (__m128i*) temp );
}

static inline
void _mm_storeu_si120( uint8_t * d , __m128i a ) {
	union uu {
	uint8_t temp[16]  __attribute__((aligned(16)));
	uint64_t temp64[2];
	} ua;
	_mm_store_si128((__m128i *)ua.temp,a);
	*(uint64_t *)d = ua.temp64[0];
	for(int i=0;i<7;i++) d[8+i] = ua.temp[8+i];
}

static inline
void gf2ext120_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_loadu_si120( a );
	__m128i b0 = _mm_loadu_si120( b );
	__m128i c0,c128;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );

	_gf2ext120_reduce_sse( &c0 , c128 );
	_mm_storeu_si120( c , c0 );
}



static inline
void gf2ext120_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_loadu_si120( a );
	__m128i c0,c128;
	_SQU_128( c0,c128, a0 );

	_gf2ext120_reduce_sse( &c0 , c128 );
	_mm_storeu_si120( c , c0 );
}

static inline
void gf2ext120_pow_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext120_squ_sse(b,a);
	for(unsigned i=0;i<2;i++) gf2ext120_squ_sse( b , b );
}

static inline
void gf2ext120_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext120_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext120_squ_sse( b , b );
}
static inline
void gf2ext120_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext120_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext120_squ_sse( b , b );
}


/// 2^120 - 2 = 2^8^15 = 0xFF .... FE
static inline
void gf2ext120_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;

	uint8_t tmp[W16] __attribute__((aligned(16))) = {0}; gf2ext120_squ_sse(tmp,a);
	uint8_t a3[W16] __attribute__((aligned(16))); gf2ext120_mul_sse(a3,tmp,a);
	gf2ext120_squ_sse(tmp,a3);
	gf2ext120_squ_sse(tmp,tmp);
	uint8_t aF[W16] __attribute__((aligned(16))); gf2ext120_mul_sse(aF,tmp,a3);
	gf2ext120_squ_sse(tmp,aF);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	uint8_t aFF[W16] __attribute__((aligned(16))); gf2ext120_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W16;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<13;i++) {
		gf2ext120_pow_256_1_sse(tmp,tmp);
		gf2ext120_mul_sse(tmp,tmp,aFF);
	}
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_mul_sse(tmp,tmp,aF);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_mul_sse(tmp,tmp,a3);
	gf2ext120_squ_sse(tmp,tmp);
	gf2ext120_mul_sse(tmp,tmp,a);
	gf2ext120_squ_sse(b,tmp);

}










////////////////  GF(2^96)  ////////////////////////


extern uint64_t gf25612to296[];

extern uint64_t gf296to25612[];

static inline
void gf25612_from_296_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_96x96_sse( r , gf296to25612 , a ); }

static inline
void gf296_from_25612_sse( uint8_t * r , const uint8_t * a ) { bitmatrix_prod_96x96_sse( r , gf25612to296 , a ); }


/// x^96 + x^10 + x^9 + x^6 + 1
///  x^96 + x^10 + x^9 + x^6 + 1
///  0x641
///  x^128 + x^42 + x^41 + x^38 + x^32
///  0x64100000000

static const uint64_t _gf2ext96_reducer[2] __attribute__((aligned(16)))  = {0x64100000000ULL,0x641ULL};
static const uint32_t _gf2ext96_mask[4]  __attribute__((aligned(16))) = {0xffffffff,0xffffffff,0xffffffff,0};

static inline
__m128i _gf2ext96_reduce_sse( __m128i x0 , __m128i x128 )
{
	__m128i reducer = _mm_load_si128( (__m128i const*)_gf2ext96_reducer );
	x0 ^= _mm_clmulepi64_si128( x128 , reducer , 0x00 );
	__m128i x96 = _mm_srli_si128(x0,4);
	x0 ^= _mm_clmulepi64_si128( x96 , reducer , 0x11 );
	x0 ^= _mm_load_si128((__m128i const *)_gf2ext96_mask);
	return x0;
}


#if 0
static inline
__m128i _mm_loadu_si96( const uint8_t * a ) {
	uint64_t temp[2]  __attribute__((aligned(16))) ={0};
	temp[0] = *(uint64_t*)a;
	*(uint32_t*)&temp[1] = *(uint32_t*)(a+8);
	return _mm_load_si128( (__m128i*) temp );
}

static inline
void _mm_storeu_si96( uint8_t * d , __m128i a ) {
	uint8_t temp[16]  __attribute__((aligned(16)));
	_mm_store_si128((__m128i *)temp,a);
	*(uint64_t *)d = *(uint64_t*)temp;
	*(uint32_t*)(d+8) = *(uint32_t*)(temp+8);
}
#endif

static inline
void gf2ext96_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i a0 = _mm_load_si128( (const __m128i*)a );
	__m128i b0 = _mm_load_si128( (const __m128i*)b );
	__m128i c0,c128;
	_MUL_128_KARATSUBA( c0,c128, a0,b0 );

	c0 = _gf2ext96_reduce_sse( c0 , c128 );
	_mm_store_si128( (__m128i*) c , c0 );
	//_mm_storeu_si120( c , c0 );
}



static inline
void gf2ext96_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i a0 = _mm_load_si128( (const __m128i*)a );
	__m128i c0,c128;
	_SQU_128( c0,c128, a0 );

	c0 = _gf2ext96_reduce_sse( c0 , c128 );
	_mm_store_si128( (__m128i*) c , c0 );
	//_mm_storeu_si120( c , c0 );
}

static inline
void gf2ext96_pow_8_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext96_squ_sse(b,a);
	for(unsigned i=0;i<2;i++) gf2ext96_squ_sse( b , b );
}

static inline
void gf2ext96_pow_16_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext96_squ_sse(b,a);
	for(unsigned i=0;i<3;i++) gf2ext96_squ_sse( b , b );
}

static inline
void gf2ext96_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	gf2ext96_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) gf2ext96_squ_sse( b , b );
}


/// 2^96 - 2 = 2^8^12 = 0xFF .... FE
static inline
void gf2ext96_inv_sse( uint8_t * b , const uint8_t * a )
{
//	static const unsigned W = 32;

	uint8_t tmp[W16] __attribute__((aligned(16))) = {0}; gf2ext96_squ_sse(tmp,a);
	uint8_t a3[W16] __attribute__((aligned(16))); gf2ext96_mul_sse(a3,tmp,a);
	gf2ext96_squ_sse(tmp,a3);
	gf2ext96_squ_sse(tmp,tmp);
	uint8_t aF[W16] __attribute__((aligned(16))); gf2ext96_mul_sse(aF,tmp,a3);
	gf2ext96_squ_sse(tmp,aF);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	uint8_t aFF[W16] __attribute__((aligned(16))); gf2ext96_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W16;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<10;i++) {
		gf2ext96_pow_256_1_sse(tmp,tmp);
		gf2ext96_mul_sse(tmp,tmp,aFF);
	}
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_mul_sse(tmp,tmp,aF);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_mul_sse(tmp,tmp,a3);
	gf2ext96_squ_sse(tmp,tmp);
	gf2ext96_mul_sse(tmp,tmp,a);
	gf2ext96_squ_sse(b,tmp);

}










#ifdef  __cplusplus
}
#endif



#endif
