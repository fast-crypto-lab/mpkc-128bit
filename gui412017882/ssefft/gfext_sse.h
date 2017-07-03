#ifndef _GF_EXT_SSE_H_
#define _GF_EXT_SSE_H_


#include "gf16.h"

#include "gf16_sse.h"

#include "tbl_gf256v_polymul.h"

#include "emmintrin.h"
#include "wmmintrin.h"


#ifdef  __cplusplus
extern  "C" {
#endif



////////////////  GF(2^384) := GF((256^3)^16)  ////////////////////////


/// GF(2^384) := GF(2^24)/  x^16 +  0x2  *x^3 + x +  0x10
static inline
void tbl_gf256ext3ext16_reduce_sse( __m128i * r , const __m128i * a )
{
	__m128i t[32*3];
	for(unsigned i=0;i<32;i++) {
		t[i*3] = a[i*3];
		t[i*3+1] = a[i*3+1];
		t[i*3+2] = a[i*3+2];
	}
	for(unsigned i=30;i>=16;i--) {
		t[(i-16)*3] ^= tbl_gf256_mul_const( 0x10 , t[i*3] );
		t[(i-16)*3+1] ^= tbl_gf256_mul_const( 0x10 , t[i*3+1] );
		t[(i-16)*3+2] ^= tbl_gf256_mul_const( 0x10 , t[i*3+2] );
		t[(i-16+1)*3] ^= t[i*3];
		t[(i-16+1)*3+1] ^= t[i*3+1];
		t[(i-16+1)*3+2] ^= t[i*3+2];
		t[(i-16+3)*3] ^= tbl_gf256_mul_const( 2 , t[i*3]);
		t[(i-16+3)*3+1] ^= tbl_gf256_mul_const( 2 , t[i*3+1]);
		t[(i-16+3)*3+2] ^= tbl_gf256_mul_const( 2 , t[i*3+2]);
	}
	for(unsigned i=0;i<16;i++) {
		r[i*3] = t[i*3];
		r[i*3+1] = t[i*3+1];
		r[i*3+2] = t[i*3+2];
	}
}

static inline
void _tbl_gf256ext3ext16_mul_sse( __m128i * c , const __m128i * a , const __m128i * b )
{
	__m128i r[32*3];
	tbl_gf256_3v_polymul_16( r , a , b );
	tbl_gf256ext3ext16_reduce_sse( c , r );
}
static inline
void tbl_gf256ext3ext16_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	__m128i _a[3*16];
	__m128i _b[3*16];
	__m128i _c[3*16];
	for(unsigned i=0;i<3*16;i++) _a[i] = _mm_load_si128( (__m128i*)(a+16*i) );
	for(unsigned i=0;i<3*16;i++) _b[i] = _mm_load_si128( (__m128i*)(b+16*i) );
	_tbl_gf256ext3ext16_mul_sse( _c , _a , _b );
	for(unsigned i=0;i<3*16;i++) _mm_store_si128( (__m128i*)(c+16*i) , _c[i] );
}

static inline
void _tbl_gf256ext3ext16_squ_sse( __m128i * c , const __m128i * a )
{
	__m128i r[32*3];
	for(unsigned i=0;i<16;i++) {
		tbl_gf256_3_squ( &r[i*3*2] , a+i*3 );
		r[3*(i*2+1)] = _mm_setzero_si128();
		r[3*(i*2+1)+1] = _mm_setzero_si128();
		r[3*(i*2+1)+2] = _mm_setzero_si128();
	}
	tbl_gf256ext3ext16_reduce_sse( c , r );
}
static inline
void tbl_gf256ext3ext16_squ_sse( uint8_t * c , const uint8_t * a )
{
	__m128i _a[3*16];
	__m128i _c[3*16];
	for(unsigned i=0;i<3*16;i++) _a[i] = _mm_load_si128( (__m128i*)(a+16*i) );
	_tbl_gf256ext3ext16_squ_sse( _c , _a );
	for(unsigned i=0;i<3*16;i++) _mm_store_si128( (__m128i*)(c+16*i) , _c[i] );
}

static inline
void _tbl_gf256ext3ext16_pow_256_1_sse( __m128i * b , const __m128i * a )
{
	_tbl_gf256ext3ext16_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) _tbl_gf256ext3ext16_squ_sse( b , b );
}
static inline
void tbl_gf256ext3ext16_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext3ext16_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) tbl_gf256ext3ext16_squ_sse( b , b );
}
static inline
void tbl_gf256ext3ext16_pow_256_2_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext3ext16_squ_sse(b,a);
	for(unsigned i=0;i<7+8*1;i++) tbl_gf256ext3ext16_squ_sse( b , b );
}
static inline
void tbl_gf256ext3ext16_pow_256_4_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext3ext16_squ_sse(b,a);
	for(unsigned i=0;i<7+8*3;i++) tbl_gf256ext3ext16_squ_sse( b , b );
}
static inline
void tbl_gf256ext3ext16_pow_256_8_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext3ext16_squ_sse(b,a);
	for(unsigned i=0;i<7+8*7;i++) tbl_gf256ext3ext16_squ_sse( b , b );
}

/// 256^48 - 2 = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE
static inline
void _tbl_gf256ext3ext16_inv_sse( __m128i * b , const __m128i * a )
{
	static const unsigned W = 48;
	__m128i tmp[48] __attribute__((aligned(16))); _tbl_gf256ext3ext16_squ_sse(tmp,a);
	__m128i a3[48] __attribute__((aligned(16))); _tbl_gf256ext3ext16_mul_sse(a3,tmp,a);
	_tbl_gf256ext3ext16_squ_sse(tmp,a3);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	__m128i aF[48] __attribute__((aligned(16))); _tbl_gf256ext3ext16_mul_sse(aF,tmp,a3);
	_tbl_gf256ext3ext16_squ_sse(tmp,aF);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	__m128i aFF[48] __attribute__((aligned(16))); _tbl_gf256ext3ext16_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) tmp[i]=aFF[i];
	for(unsigned i=0;i<46;i++) {
		_tbl_gf256ext3ext16_pow_256_1_sse(tmp,tmp);
		_tbl_gf256ext3ext16_mul_sse(tmp,tmp,aFF);
	}
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_mul_sse(tmp,tmp,aF);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_mul_sse(tmp,tmp,a3);
	_tbl_gf256ext3ext16_squ_sse(tmp,tmp);
	_tbl_gf256ext3ext16_mul_sse(tmp,tmp,a);
	_tbl_gf256ext3ext16_squ_sse(b,tmp);

}
static inline
void tbl_gf256ext3ext16_inv_sse( uint8_t * c , const uint8_t * a )
{
	__m128i _a[3*16];
	__m128i _c[3*16];
	for(unsigned i=0;i<3*16;i++) _a[i] = _mm_load_si128( (__m128i*)(a+16*i) );
	_tbl_gf256ext3ext16_inv_sse( _c , _a );
	for(unsigned i=0;i<3*16;i++) _mm_store_si128( (__m128i*)(c+16*i) , _c[i] );
}







////////////////  GF(2^256) := GF(256^32)  ////////////////////////

/// GF(2^256) := GF(256)/ x^32 + 0x10*x^3 + x + 1

static inline
void tbl_gf256ext_32_reduce_sse( __m128i * r , const __m128i * a )
{
	__m128i t[64];
	for(unsigned i=0;i<63;i++) { t[i] = a[i]; }
	for(unsigned i=62;i>=32;i--) {
		t[i-32+3] ^= tbl_gf256_mul_const( 0x10 , t[i] );
		t[i-32+1] ^= t[i];
		t[i-32] ^= t[i];
	}
	for(unsigned i=0;i<32;i++) { r[i] = t[i]; }
}

static inline
void tbl_gf256ext_32_mul_sse( uint8_t * _c , const uint8_t * _a , const uint8_t * _b )
{
	__m128i a[32];
	__m128i b[32];
	__m128i c[64];
	for(unsigned i=0;i<32;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );
	for(unsigned i=0;i<32;i++) b[i] = _mm_load_si128( (__m128i*)(_b+16*i) );

	tbl_gf256v_polymul_32( c , a , b );
	tbl_gf256ext_32_reduce_sse( c , c );

	for(unsigned i=0;i<32;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_32_squ_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i a[32];
	__m128i c[64];
	for(unsigned i=0;i<32;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );

	for(unsigned i=0;i<32;i++) {
		c[i*2] = tbl_gf256_squ( a[i] );
		c[i*2+1] = _mm_setzero_si128();
	}
	tbl_gf256ext_32_reduce_sse( c , c );

	for(unsigned i=0;i<32;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_32_add_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i tmp;
	for(unsigned i=0;i<32;i++) {
		tmp = _mm_load_si128( (__m128i*)(_a+16*i) ) ^ _mm_load_si128( (__m128i*)(_c+16*i) );
		_mm_store_si128( (__m128i*)(_c+16*i) , tmp );
	}
}

static inline
void tbl_gf256ext_32_sse_extract( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<32;i++) r[i] = a[i*16+idx];
}

static inline
void tbl_gf256ext_32_sse_insert( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<32;i++) r[i*16+idx] = a[i];
}

static inline
void tbl_gf256ext_32_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_32_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) tbl_gf256ext_32_squ_sse( b , b );
}

/// 256^32 - 2
static inline
void tbl_gf256ext_32_inv_sse( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 32;
	uint8_t tmp[32*16] __attribute__((aligned(16))); tbl_gf256ext_32_squ_sse(tmp,a);
	uint8_t a3[32*16] __attribute__((aligned(16))); tbl_gf256ext_32_mul_sse(a3,tmp,a);
	tbl_gf256ext_32_squ_sse(tmp,a3);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	uint8_t aF[32*16] __attribute__((aligned(16))); tbl_gf256ext_32_mul_sse(aF,tmp,a3);
	tbl_gf256ext_32_squ_sse(tmp,aF);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	uint8_t aFF[32*16] __attribute__((aligned(16))); tbl_gf256ext_32_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) for(unsigned j=0;j<16;j++) tmp[i*16+j]=aFF[i*16+j];
	for(unsigned i=0;i<30;i++) {
		tbl_gf256ext_32_pow_256_1_sse(tmp,tmp);
		tbl_gf256ext_32_mul_sse(tmp,tmp,aFF);
	}
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_mul_sse(tmp,tmp,aF);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_mul_sse(tmp,tmp,a3);
	tbl_gf256ext_32_squ_sse(tmp,tmp);
	tbl_gf256ext_32_mul_sse(tmp,tmp,a);
	tbl_gf256ext_32_squ_sse(b,tmp);
}





////////////////  GF(2^240) := GF(256^30)  ////////////////////////


/// GF(2^240) := GF(256)/ x^30 + 0x10 x^3 + x^2 + x + 1,
static inline
void tbl_gf256ext_30_reduce_sse( __m128i * r , const __m128i * a )
{
	__m128i t[60];
	for(unsigned i=0;i<59;i++) { t[i] = a[i]; }

	for(unsigned i=58;i>=30;i--) {
		t[i-30+3] ^= tbl_gf256_mul_const( 0x10 , t[i] );
		t[i-30+2] ^= t[i];
		t[i-30+1] ^= t[i];
		t[i-30] ^= t[i];
	}
	for(unsigned i=0;i<30;i++) { r[i] = t[i]; }
}

static inline
void tbl_gf256ext_30_add_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i cc;
	for(unsigned i=0;i<30;i++) {
		cc = _mm_load_si128( (__m128i*)(_a+16*i) ) ^ _mm_load_si128( (__m128i*)(_c+16*i) );
		_mm_store_si128( (__m128i*)(_c+16*i) , cc );
	}
}

static inline
void tbl_gf256ext_30_sse_extract( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<30;i++) r[i] = a[i*16+idx];
}

static inline
void tbl_gf256ext_30_sse_insert( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<30;i++) r[i*16+idx] = a[i];
}


static inline
void tbl_gf256ext_30_mul_sse( uint8_t * _c , const uint8_t * _a , const uint8_t * _b )
{
	__m128i a[32];
	__m128i b[32];
	__m128i c[64];
	for(unsigned i=0;i<30;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );
	a[30] = _mm_setzero_si128();
	a[31] = _mm_setzero_si128();
	for(unsigned i=0;i<30;i++) b[i] = _mm_load_si128( (__m128i*)(_b+16*i) );
	b[30] = _mm_setzero_si128();
	b[31] = _mm_setzero_si128();

	tbl_gf256v_polymul_32( c , a , b );
	tbl_gf256ext_30_reduce_sse( c , c );

	for(unsigned i=0;i<30;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_30_squ_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i a[32];
	__m128i c[64];
	for(unsigned i=0;i<30;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );
	a[30] = _mm_setzero_si128();
	a[31] = _mm_setzero_si128();

	for(unsigned i=0;i<30;i++) {
		c[i*2] = tbl_gf256_squ( a[i] );
		c[i*2+1] = _mm_setzero_si128();
	}
	tbl_gf256ext_30_reduce_sse( c , c );

	for(unsigned i=0;i<30;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );

}

static inline
void tbl_gf256ext_30_pow_32_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_30_squ_sse(b,a);
	for(unsigned i=0;i<4;i++) tbl_gf256ext_30_squ_sse( b , b );
}

static inline
void tbl_gf256ext_30_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_30_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) tbl_gf256ext_30_squ_sse( b , b );
}

/// 256^30 - 2
static inline
void tbl_gf256ext_30_inv_sse( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 30;
	uint8_t tmp[32*16] __attribute__((aligned(16))); tbl_gf256ext_30_squ_sse(tmp,a);
	uint8_t a3[32*16] __attribute__((aligned(16))); tbl_gf256ext_30_mul_sse(a3,tmp,a);
	tbl_gf256ext_30_squ_sse(tmp,a3);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	uint8_t aF[32*16] __attribute__((aligned(16))); tbl_gf256ext_30_mul_sse(aF,tmp,a3);
	tbl_gf256ext_30_squ_sse(tmp,aF);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	uint8_t aFF[32*16] __attribute__((aligned(16))); tbl_gf256ext_30_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) for(unsigned j=0;j<16;j++) tmp[i*16+j]=aFF[i*16+j];
	for(unsigned i=0;i<28;i++) {
		tbl_gf256ext_30_pow_256_1_sse(tmp,tmp);
		tbl_gf256ext_30_mul_sse(tmp,tmp,aFF);
	}
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_mul_sse(tmp,tmp,aF);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_mul_sse(tmp,tmp,a3);
	tbl_gf256ext_30_squ_sse(tmp,tmp);
	tbl_gf256ext_30_mul_sse(tmp,tmp,a);
	tbl_gf256ext_30_squ_sse(b,tmp);

}


////////////////  GF(2^128) := GF(256^16)  ////////////////////////

/// GF(2^384) := GF(256)/ x^48 + x^3 + 0x10*x^2 + 0x4*x + 1

static inline
void tbl_gf256ext_48_reduce_sse( __m128i * r , const __m128i * a )
{
	__m128i t[96];
	for(unsigned i=0;i<95;i++) { t[i] = a[i]; }
	for(unsigned i=94;i>=48;i--) {
		t[i-48+3] ^= t[i];
		t[i-48+2] ^= tbl_gf256_mul_const( 0x10 , t[i] );
		t[i-48+1] ^= tbl_gf256_mul_const( 0x4 , t[i] );
		t[i-48] ^= t[i];
	}
	for(unsigned i=0;i<48;i++) { r[i] = t[i]; }
}

static inline
void tbl_gf256ext_48_mul_sse( uint8_t * _c , const uint8_t * _a , const uint8_t * _b )
{
	__m128i c[96];
#if 0
	__m128i a[48];
	__m128i b[48];
	for(unsigned i=0;i<48;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );
	for(unsigned i=0;i<48;i++) b[i] = _mm_load_si128( (__m128i*)(_b+16*i) );
	tbl_gf256v_polymul_48( c , a , b );
#else
	tbl_gf256v_polymul_48( c , (const __m128i*)_a , (const __m128i*)_b );
#endif
	tbl_gf256ext_48_reduce_sse( c , c );

	for(unsigned i=0;i<48;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_48_squ_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i a[48];
	__m128i c[96];
	for(unsigned i=0;i<48;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );

	for(unsigned i=0;i<48;i++) {
		c[i*2] = tbl_gf256_squ( a[i] );
		c[i*2+1] = _mm_setzero_si128();
	}
	tbl_gf256ext_48_reduce_sse( c , c );

	for(unsigned i=0;i<48;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_48_add_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i tmp;
	for(unsigned i=0;i<48;i++) {
		tmp = _mm_load_si128( (__m128i*)(_a+16*i) ) ^ _mm_load_si128( (__m128i*)(_c+16*i) );
		_mm_store_si128( (__m128i*)(_c+16*i) , tmp );
	}
}

static inline
void tbl_gf256ext_48_sse_extract( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<48;i++) r[i] = a[i*16+idx];
}

static inline
void tbl_gf256ext_48_sse_insert( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<48;i++) r[i*16+idx] = a[i];
}

static inline
void tbl_gf256ext_48_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_48_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) tbl_gf256ext_48_squ_sse( b , b );
}
static inline
void tbl_gf256ext_48_pow_256_2_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_48_squ_sse(b,a);
	for(unsigned i=0;i<7+8;i++) tbl_gf256ext_48_squ_sse( b , b );
}
static inline
void tbl_gf256ext_48_pow_256_4_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_48_squ_sse(b,a);
	for(unsigned i=0;i<7+8*3;i++) tbl_gf256ext_48_squ_sse( b , b );
}
static inline
void tbl_gf256ext_48_pow_256_8_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_48_squ_sse(b,a);
	for(unsigned i=0;i<7+8*7;i++) tbl_gf256ext_48_squ_sse( b , b );
}
static inline
void tbl_gf256ext_48_pow_256_32_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_48_squ_sse(b,a);
	for(unsigned i=0;i<7+8*31;i++) tbl_gf256ext_48_squ_sse( b , b );
}

/// 256^48 - 2
static inline
void tbl_gf256ext_48_inv_sse( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 48;
	uint8_t tmp[48*16] __attribute__((aligned(16))); tbl_gf256ext_48_squ_sse(tmp,a);
	uint8_t a3[48*16] __attribute__((aligned(16))); tbl_gf256ext_48_mul_sse(a3,tmp,a);
	tbl_gf256ext_48_squ_sse(tmp,a3);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	uint8_t aF[48*16] __attribute__((aligned(16))); tbl_gf256ext_48_mul_sse(aF,tmp,a3);
	tbl_gf256ext_48_squ_sse(tmp,aF);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	uint8_t aFF[48*16] __attribute__((aligned(16))); tbl_gf256ext_48_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) for(unsigned j=0;j<16;j++) tmp[i*16+j]=aFF[i*16+j];
	for(unsigned i=0;i<46;i++) {
		tbl_gf256ext_48_pow_256_1_sse(tmp,tmp);
		tbl_gf256ext_48_mul_sse(tmp,tmp,aFF);
	}
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_mul_sse(tmp,tmp,aF);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_mul_sse(tmp,tmp,a3);
	tbl_gf256ext_48_squ_sse(tmp,tmp);
	tbl_gf256ext_48_mul_sse(tmp,tmp,a);
	tbl_gf256ext_48_squ_sse(b,tmp);
}



////////////////  GF(2^128) := GF(256^16)  ////////////////////////


/// GF(2^128) := GF(256)/ x^16 + x^5 + x^3 + 0x10

static inline
void tbl_gf256ext_16_reduce_sse( __m128i * r , const __m128i * a )
{
	__m128i t[32];
	for(unsigned i=0;i<31;i++) { t[i] = a[i]; }
	for(unsigned i=30;i>=16;i--) {
		t[i-16+5] ^= t[i];
		t[i-16+3] ^= t[i];
		t[i-16] ^= tbl_gf256_mul_const( 0x10 , t[i] );
	}
	for(unsigned i=0;i<32;i++) { r[i] = t[i]; }
}

static inline
void tbl_gf256ext_16_mul_sse( uint8_t * _c , const uint8_t * _a , const uint8_t * _b )
{
	__m128i a[16];
	__m128i b[16];
	__m128i c[32];
	for(unsigned i=0;i<16;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );
	for(unsigned i=0;i<16;i++) b[i] = _mm_load_si128( (__m128i*)(_b+16*i) );

	tbl_gf256v_polymul_16( c , a , b );
	tbl_gf256ext_16_reduce_sse( c , c );

	for(unsigned i=0;i<16;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_16_squ_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i a[16];
	__m128i c[32];
	for(unsigned i=0;i<16;i++) a[i] = _mm_load_si128( (__m128i*)(_a+16*i) );

	for(unsigned i=0;i<16;i++) {
		c[i*2] = tbl_gf256_squ( a[i] );
		c[i*2+1] = _mm_setzero_si128();
	}
	tbl_gf256ext_16_reduce_sse( c , c );

	for(unsigned i=0;i<16;i++) _mm_store_si128( (__m128i*)(_c+16*i) , c[i] );
}

static inline
void tbl_gf256ext_16_add_sse( uint8_t * _c , const uint8_t * _a )
{
	__m128i tmp;
	for(unsigned i=0;i<16;i++) {
		tmp = _mm_load_si128( (__m128i*)(_a+16*i) ) ^ _mm_load_si128( (__m128i*)(_c+16*i) );
		_mm_store_si128( (__m128i*)(_c+16*i) , tmp );
	}
}

static inline
void tbl_gf256ext_16_sse_extract( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<16;i++) r[i] = a[i*16+idx];
}

static inline
void tbl_gf256ext_16_sse_insert( uint8_t * r , const uint8_t * a , uint8_t idx )
{
	for(unsigned i=0;i<16;i++) r[i*16+idx] = a[i];
}

static inline
void tbl_gf256ext_16_pow_256_1_sse( uint8_t * b , const uint8_t * a )
{
	tbl_gf256ext_16_squ_sse(b,a);
	for(unsigned i=0;i<7;i++) tbl_gf256ext_16_squ_sse( b , b );
}

/// 256^32 - 2
static inline
void tbl_gf256ext_16_inv_sse( uint8_t * b , const uint8_t * a )
{
	static const unsigned W = 16;
	uint8_t tmp[16*16] __attribute__((aligned(16))); tbl_gf256ext_16_squ_sse(tmp,a);
	uint8_t a3[16*16] __attribute__((aligned(16))); tbl_gf256ext_16_mul_sse(a3,tmp,a);
	tbl_gf256ext_16_squ_sse(tmp,a3);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	uint8_t aF[16*16] __attribute__((aligned(16))); tbl_gf256ext_16_mul_sse(aF,tmp,a3);
	tbl_gf256ext_16_squ_sse(tmp,aF);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	uint8_t aFF[16*16] __attribute__((aligned(16))); tbl_gf256ext_16_mul_sse(aFF,tmp,aF);

	for(unsigned i=0;i<W;i++) for(unsigned j=0;j<16;j++) tmp[i*16+j]=aFF[i*16+j];
	for(unsigned i=0;i<14;i++) {
		tbl_gf256ext_16_pow_256_1_sse(tmp,tmp);
		tbl_gf256ext_16_mul_sse(tmp,tmp,aFF);
	}
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_mul_sse(tmp,tmp,aF);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_mul_sse(tmp,tmp,a3);
	tbl_gf256ext_16_squ_sse(tmp,tmp);
	tbl_gf256ext_16_mul_sse(tmp,tmp,a);
	tbl_gf256ext_16_squ_sse(b,tmp);
}






#if 1


////////////////////// GF(2^128) := GF(256^16)   schoolbook for comparison only /////////////////////////////////


#define _ACCU_(i) do { \
		xl_broadcast = _mm_set1_epi8( xl[i] ); \
		xh_broadcast = _mm_set1_epi8( xh[i] ); \
		xlh_broadcast = _mm_set1_epi8( xlh[i] ); \
		__m128i kl = lb0l; \
		__m128i kh = lb0h; \
		__m128i klh = lb0lh; \
		kl = _mm_add_epi8(kl,xl_broadcast); \
		kh = _mm_add_epi8(kh,xh_broadcast); \
		klh = _mm_add_epi8(klh,xlh_broadcast); \
		kl = _mm_shuffle_epi8( gf16_exp , _mm_sub_epi8(kl,mf&_mm_cmpgt_epi8(kl,mf)) ); \
		kh = _mm_shuffle_epi8( gf16_exp , _mm_sub_epi8(kh,mf&_mm_cmpgt_epi8(kh,mf)) ); \
		klh = _mm_shuffle_epi8( gf16_exp , _mm_sub_epi8(klh,mf&_mm_cmpgt_epi8(klh,mf)) ); \
		__m128i rl = kl ^ _mm_shuffle_epi8( mul_8 , kh ); \
		__m128i rh = klh ^ kl; \
		rl = rl ^ _mm_slli_epi16( rh , 4 ); \
		__m128i zero = _mm_setzero_si128(); \
		c0 ^= _mm_alignr_epi8( rl , zero , 16-i ); \
		c1 ^= _mm_alignr_epi8( zero , rl , 16-i ); \
        } while(0)


/// x^2 + x + 0x8
static inline
__m128i mul_0x10( __m128i mul_8 , __m128i mf , __m128i c )
{
	__m128i cl = c&mf;
	__m128i ch = _mm_srli_epi16(c,4)&mf;
	__m128i rl = _mm_shuffle_epi8( mul_8 , ch );
	__m128i rh = cl^ch;
	return rl^_mm_slli_epi16( rh , 4 );
}

/// x^16 + x^5 + x^3 + 0x10
static inline
void gf256ext_16_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{

	__m128i gf16_log = _mm_load_si128((__m128i const *) __gf16_log);
	__m128i gf16_exp = _mm_load_si128((__m128i const *) __gf16_exp);
	__m128i mf = _mm_load_si128((__m128i const *) __mask_low);
	__m128i mul_8 = _mm_load_si128((__m128i const *) (__gf16_mulx2 + 8*32) );

	__m128i a0 = _mm_loadu_si128 ((__m128i const *) a );
	__m128i b0 = _mm_loadu_si128 ((__m128i const *) (b) );

	uint8_t xl[32] __attribute__((aligned(32)));
	uint8_t xh[32] __attribute__((aligned(32)));
	uint8_t xlh[32] __attribute__((aligned(32)));

	__m128i _l = a0&mf;
	__m128i _h = _mm_srli_epi16(a0,4)&mf;
	_mm_store_si128( (__m128i*) xl , _mm_shuffle_epi8(gf16_log , _l ) );
	_mm_store_si128( (__m128i*) xh , _mm_shuffle_epi8(gf16_log , _h ) );
	_mm_store_si128( (__m128i*) xlh , _mm_shuffle_epi8(gf16_log , _l^_h ) );

	__m128i lb0l;
	__m128i lb0h;
	__m128i lb0lh;

	_l = b0&mf;
	_h = _mm_srli_epi16(b0,4)&mf;
	lb0l = _mm_shuffle_epi8(gf16_log , _l );
	lb0h = _mm_shuffle_epi8(gf16_log , _h );
	lb0lh = _mm_shuffle_epi8(gf16_log , _l^_h );

        __m128i xl_broadcast;
        __m128i xh_broadcast;
        __m128i xlh_broadcast;

	__m128i c0 = _mm_setzero_si128();
	__m128i c1 = _mm_setzero_si128();

	_ACCU_(0);
	_ACCU_(1);
	_ACCU_(2);
	_ACCU_(3);
	_ACCU_(4);
	_ACCU_(5);
	_ACCU_(6);
	_ACCU_(7);
	_ACCU_(8);
	_ACCU_(9);
	_ACCU_(10);
	_ACCU_(11);
	_ACCU_(12);
	_ACCU_(13);
	_ACCU_(14);
	_ACCU_(15);


	__m128i c1_h = c1;
	c1_h = _mm_srli_si128( c1_h , 8 );
	c1_h = _mm_slli_si128( c1_h , 8 );

	c1 = _mm_slli_si128( c1 , 8 );
	c1 = _mm_srli_si128( c1 , 8 );

	/// x^16 + x^5 + x^3 + 0x10
	{
	__m128i zero = _mm_setzero_si128();
	c0 ^= mul_0x10( mul_8 , mf , c1_h );
	c0 ^= _mm_alignr_epi8( c1_h , zero , 16-3 );
	c1 ^= _mm_alignr_epi8( zero , c1_h , 16-3 );
	c0 ^= _mm_alignr_epi8( c1_h , zero , 16-5 );
	c1 ^= _mm_alignr_epi8( zero , c1_h , 16-5 );
	}
	{
	__m128i zero = _mm_setzero_si128();
	c0 ^= mul_0x10( mul_8 , mf , c1 );
	c0 ^= _mm_alignr_epi8( c1 , zero , 16-3 );
	c0 ^= _mm_alignr_epi8( c1 , zero , 16-5 );
	}


	_mm_storeu_si128( (__m128i*) c , c0 );

}


#endif


//////////////////////////////////////////////////////////////////////


#if 0
/// x^32 + 0x10*x^3 + x + 1
static inline
void gf256ext_32_mul_sse( uint8_t * c , const uint8_t * a , const uint8_t * b )
{
	static const unsigned W = 32;
	uint8_t tmp_mul[32*2] = {0};
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
#endif



#ifdef  __cplusplus
}
#endif



#endif


