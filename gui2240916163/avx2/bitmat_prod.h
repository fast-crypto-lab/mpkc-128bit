#ifndef _BITMAT_PROD_H_
#define _BITMAT_PROD_H_

#include "stdint.h"

#include "emmintrin.h"
#include "tmmintrin.h"


#ifdef  __cplusplus
extern  "C" {
#endif





#define _ACCU_64_3_(inp_run) do {\
	for(int i=64;i>0;i--) { \
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero)); \
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16; \
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16; \
		r2 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16; \
		inp_run = _mm_srli_epi64(inp_run,1); \
	} \
} while(0)



static inline
void bitmatrix_prod_384x384_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	__m128i i0 = _mm_load_si128( (__m128i *)a );
	__m128i i1 = _mm_load_si128( (__m128i *)(a+16) );
	__m128i i2 = _mm_load_si128( (__m128i *)(a+32) );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();
	__m128i r2 = _mm_setzero_si128();

	//__m128i mask_ff00 = _mm_cmpeq_epi8(zero,zero);
	//mask_ff00 = _mm_unpacklo_epi8(zero,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_3_(inp_run);
	inp_run = i1;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i1,8);
	_ACCU_64_3_(inp_run);
	inp_run = i2;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i2,8);
	_ACCU_64_3_(inp_run);

	_mm_store_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+16) , r1 );
	_mm_storeu_si128( (__m128i*)(r+32) , r2 );
}



static inline
void bitmatrix_prod_360x360_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	__m128i i0 = _mm_load_si128( (__m128i *)a );
	__m128i i1 = _mm_load_si128( (__m128i *)(a+16) );
	__m128i i2 = _mm_srli_si128( _mm_loadu_si128( (__m128i *)(a+29) ) , 3 );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();
	__m128i r2 = _mm_setzero_si128();

	//__m128i mask_ff00 = _mm_cmpeq_epi8(zero,zero);
	//mask_ff00 = _mm_unpacklo_epi8(zero,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_3_(inp_run);
	inp_run = i1;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i1,8);
	_ACCU_64_3_(inp_run);
	inp_run = i2;
	_ACCU_64_3_(inp_run);
	inp_run = _mm_srli_si128(i2,8);
	for(int i=40;i>0;i--) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		r2 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}

	_mm_store_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+16) , r1 );
	r2 = _mm_alignr_epi8(r2,r1,13);
	_mm_storeu_si128( (__m128i*)(r+29) , r2 );
}




#define _ACCU_64_2_(inp_run) do {\
	for(int i=64;i>0;i--) { \
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero)); \
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16; \
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16; \
		inp_run = _mm_srli_epi64(inp_run,1); \
	} \
} while(0)


static inline
void bitmatrix_prod_256x256_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
#if 1
	__m128i i0 = _mm_load_si128( (__m128i *)a );
	__m128i i1 = _mm_load_si128( (__m128i *)(a+16) );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	//__m128i mask_ff00 = _mm_cmpeq_epi8(zero,zero);
	//mask_ff00 = _mm_unpacklo_epi8(zero,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_2_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_2_(inp_run);
	inp_run = i1;
	_ACCU_64_2_(inp_run);
	inp_run = _mm_srli_si128(i1,8);
	_ACCU_64_2_(inp_run);

	_mm_store_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+16) , r0 );

#else
	const uint8_t * idx = (const uint8_t *)mat;
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();
	for(unsigned i=0;i<32;i++) {
		uint8_t c = a[i];
		for(unsigned j=8;j>0;j--) {
			char m = 0-(c&1);
			c >>= 1;
			__m128i mask = _mm_set1_epi8(m);
			r0 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
			r1 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
		}
	}
	_mm_store_si128( (__m128i *) r , r0 );
	_mm_store_si128( (__m128i *)(r+16) , r1 );
#endif
}


static inline
void bitmatrix_prod_248x248_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
#if 1
	__m128i i0 = _mm_load_si128( (__m128i *)a );
	__m128i i1 = _mm_srli_si128( _mm_loadu_si128( (__m128i *)(a+15) ) , 1 );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	//__m128i mask_ff00 = _mm_cmpeq_epi8(zero,zero);
	//mask_ff00 = _mm_unpacklo_epi8(zero,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_2_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_2_(inp_run);
	inp_run = i1;
	_ACCU_64_2_(inp_run);

	inp_run = _mm_srli_si128(i1,8);
	for(int i=0;i<56;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}

	_mm_store_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+15) , _mm_alignr_epi8(r1,r0,15) );
#else
	const uint8_t * idx = (const uint8_t *)mat;
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();
	for(unsigned i=0;i<31;i++) {
		uint8_t c = a[i];
		for(unsigned j=8;j>0;j--) {
			char m = 0-(c&1);
			c >>= 1;
			__m128i mask = _mm_set1_epi8(m);
			r0 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
			r1 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
		}
	}
	_mm_store_si128( (__m128i *) r , r0 );
	_mm_store_si128( (__m128i *)(r+16) , r1 );
#endif
}


static inline
void bitmatrix_prod_240x240_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	__m128i i0 = _mm_loadu_si128( (__m128i *)a );
	__m128i i1 = _mm_srli_si128( _mm_loadu_si128( (__m128i *)(a+14) ) , 2 );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	//__m128i mask_ff00 = _mm_cmpeq_epi8(zero,zero);
	//mask_ff00 = _mm_unpacklo_epi8(zero,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_2_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_2_(inp_run);
	inp_run = i1;
	_ACCU_64_2_(inp_run);

	inp_run = _mm_srli_si128(i1,8);
	for(int i=0;i<48;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}

	_mm_storeu_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+14) ,  _mm_alignr_epi8(r1,r0,14) );
}



static inline
void bitmatrix_prod_224x224_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	__m128i i0 = _mm_loadu_si128( (__m128i *)a );
	__m128i i1 = _mm_srli_si128( _mm_loadu_si128( (__m128i *)(a+12) ) , 4 );

	__m128i zero = _mm_setzero_si128();
	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	__m128i mask_1 = _mm_set1_epi8(1);

	const uint8_t * idx = (const uint8_t *)mat;
	__m128i inp_run = i0;
	_ACCU_64_2_(inp_run);
	inp_run = _mm_srli_si128(i0,8);
	_ACCU_64_2_(inp_run);
	inp_run = i1;
	_ACCU_64_2_(inp_run);

	inp_run = _mm_srli_si128(i1,8);
	for(int i=0;i<32;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		r1 ^= (qq & _mm_load_si128( (const __m128i *)idx) ); idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}

	_mm_storeu_si128( (__m128i *) r , r0 );
	_mm_storeu_si128( (__m128i*)(r+12) , _mm_alignr_epi8(r1,r0,12) );
}


static inline
void bitmatrix_prod_128x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	const uint8_t * idx = (const uint8_t *)mat;
	__m128i r0 = _mm_setzero_si128();
	for(unsigned i=0;i<16;i++) {
		uint8_t c = a[i];
		for(unsigned j=8;j>0;j--) {
			char m = 0-(c&1);
			c >>= 1;
			__m128i mask = _mm_set1_epi8(m);
			r0 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
		}
	}
	_mm_store_si128( (__m128i *) r , r0 );
}



static inline
void bitmatrix_prod_64x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint64_t _tmp[2] __attribute__((aligned(32))) = {0};
	_tmp[0] = *(const uint64_t *)a;
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<64;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_32x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint8_t _tmp[16] __attribute__((aligned(32))) = {0};
	_tmp[0] = a[0];
	_tmp[1] = a[1];
	_tmp[2] = a[2];
	_tmp[3] = a[3];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<32;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_24x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint8_t _tmp[16] __attribute__((aligned(32))) = {0};
	_tmp[0] = a[0];
	_tmp[1] = a[1];
	_tmp[2] = a[2];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<24;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_16x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint16_t _tmp[8] __attribute__((aligned(32))) = {0};
	_tmp[0] = *(const uint16_t *)a;
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<16;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_8x128_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint8_t _tmp[16] __attribute__((aligned(32))) = {0};
	_tmp[0] = a[0];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<8;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_64x128_4R_sse( uint8_t * r , const uint64_t * mat4R , uint64_t a )
{
	__m128i r0 = _mm_setzero_si128();
	const __m128i * mat128 = (const __m128i*)mat4R;
	while( a ) {
		r0 ^= _mm_load_si128( mat128 + (a&0xf) );
		mat128 += 16;
		a >>= 4;
	}
	_mm_store_si128( (__m128i *) r , r0 );
}

static inline
void bitmatrix_prod_128x128_4R_sse( uint8_t * r , const uint64_t * mat4R , const uint8_t *a )
{
	__m128i r0 = _mm_setzero_si128();
	const __m128i * mat128 = (const __m128i*)mat4R;
	const uint64_t * a01 = (const uint64_t *)a;
	uint64_t a0 = a01[0];
	while( a0 ) {
		r0 ^= _mm_load_si128( mat128 + (a0&0xf) );
		mat128 += 16;
		a0 >>= 4;
	}
	mat128 = (const __m128i*)mat4R;
	mat128 += 256;
	a0 = a01[1];
	while( a0 ) {
		r0 ^= _mm_load_si128( mat128 + (a0&0xf) );
		mat128 += 16;
		a0 >>= 4;
	}
	_mm_store_si128( (__m128i *) r , r0 );
}



static inline
void bitmatrix_prod_120x120_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint8_t _tmp[16] __attribute__((aligned(32))) = {0};
	for(int i=0;i<15;i++) _tmp[i]=a[i];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	//__m128i mask_ff00 = _mm_cmpeq_epi8(r0,r0);
	//mask_ff00 = _mm_unpacklo_epi8(r0,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<64;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	inp_run = _mm_srli_si128(inp,8);
	for(int i=0;i<56;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) _tmp , r0 );
	for(int i=0;i<15;i++) r[i] = _tmp[i];
}



static inline
void bitmatrix_prod_96x96_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint8_t _tmp[16] __attribute__((aligned(32)));
	for(int i=0;i<12;i++) _tmp[i]=a[i];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	//__m128i mask_ff00 = _mm_cmpeq_epi8(r0,r0);
	//mask_ff00 = _mm_unpacklo_epi8(r0,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<64;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	inp_run = _mm_srli_si128(inp,8);
	for(int i=0;i<32;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) _tmp , r0 );
	for(int i=0;i<12;i++) r[i] = _tmp[i];
}

static inline
void bitmatrix_prod_72x72_sse( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
#if 1
	uint8_t _tmp[16] __attribute__((aligned(32)));
	for(int i=0;i<9;i++) _tmp[i]=a[i];
	__m128i inp = _mm_load_si128( (__m128i *)_tmp );

	__m128i r0 = _mm_setzero_si128();
	__m128i zero = r0;
	//__m128i mask_ff00 = _mm_cmpeq_epi8(r0,r0);
	//mask_ff00 = _mm_unpacklo_epi8(r0,mask_ff00);
	//__m128i mask_1 = _mm_shuffle_epi8(_mm_srli_epi16(mask_ff00,15),zero);
	__m128i mask_1 = _mm_set1_epi8(1);

	__m128i inp_run = inp;
	const uint8_t * idx = (const uint8_t *)mat;
	for(int i=0;i<64;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	inp_run = _mm_srli_si128(inp,8);
	for(int i=0;i<8;i++) {
		__m128i qq = _mm_cmpeq_epi8(mask_1,mask_1&_mm_shuffle_epi8(inp_run,zero));
		//__m128i qq = _mm_shuffle_epi8(mask_ff00,mask_1&_mm_shuffle_epi8(inp_run,zero));
		r0 ^= (qq & _mm_load_si128( (const __m128i *)idx) );
		idx += 16;
		inp_run = _mm_srli_epi64(inp_run,1);
	}
	_mm_store_si128( (__m128i *) _tmp , r0 );
	for(int i=0;i<9;i++) r[i] = _tmp[i];
#else
	uint8_t _tmp[16] __attribute__((aligned(32)));
	const uint8_t * idx = (const uint8_t *)mat;
	__m128i r0 = _mm_setzero_si128();
	for(unsigned i=0;i<9;i++) {
		uint8_t c = a[i];
		for(unsigned j=8;j>0;j--) {
			char m = 0-(c&1);
			c >>= 1;
			__m128i mask = _mm_set1_epi8(m);
			r0 ^= (mask & _mm_load_si128( (const __m128i *)idx) );
			idx += 16;
		}
	}
	_mm_store_si128( (__m128i *) _tmp , r0 );
	for(int i=0;i<9;i++) r[i] = _tmp[i];
#endif
}


static inline
void bitmatrix_prod_64x64( uint8_t * r , const uint64_t * mat , const uint8_t * a )
{
	uint64_t r0 = 0;
	for(unsigned i=0;i<8;i++) {
		uint8_t c = a[i];
		for(unsigned j=8;j>0;j--) {
			uint64_t m = 0ULL-((uint64_t)(c&1));
			c >>= 1;
			r0 ^= (*mat)&m;
			mat += 1;
		}
	}
	((uint64_t  *)r )[0] = r0;
}




#ifdef  __cplusplus
}
#endif

#endif
