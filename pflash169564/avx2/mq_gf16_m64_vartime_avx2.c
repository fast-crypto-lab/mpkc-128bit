
#include "gf16.h"




#include <immintrin.h>




void mq_gf16_n96_m64_vartime_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t _x0[96] __attribute__((aligned(32)));
	__m128i mask16 = _mm_set1_epi8( 0xf );
	__m128i w0,w1;
	w0 = _mm_loadu_si128( (__m128i*) w );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) _x0 , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+16) , _mm_unpackhi_epi8(w0,w1) );
	w0 = _mm_loadu_si128( (__m128i*) (w+16) );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) (_x0+32) , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+48) , _mm_unpackhi_epi8(w0,w1) );
	w0 = _mm_loadu_si128( (__m128i*) (w+32) );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) (_x0+64) , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+80) , _mm_unpackhi_epi8(w0,w1) );

        __m256i mask = _mm256_load_si256( (__m256i*) __mask_low );

	__m256i r0 = _mm256_setzero_si256();
	__m256i r1 = _mm256_setzero_si256();
	for(unsigned i=0;i<96;i++) {
		unsigned b = _x0[i];
		__m256i ml = _mm256_load_si256( (__m256i*) (__gf16_mulx2 + 32*b) );

		__m256i inp = _mm256_load_si256( (__m256i*)pk_mat ); pk_mat += 32;
		r0 ^= _mm256_shuffle_epi8( ml , inp&mask );
		r1 ^= _mm256_shuffle_epi8( ml , _mm256_srli_epi16(inp,4)&mask );
	}

	for(unsigned i=0;i<96;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += 32*(i+1);
			continue;
		}
		__m256i temp0 = _mm256_setzero_si256();
		__m256i temp1 = _mm256_setzero_si256();
		__m256i ml;
		for(unsigned j=0;j<=i;j++) {
			unsigned b = _x0[j];
			ml = _mm256_load_si256( (__m256i*) (__gf16_mulx2 + 32*b) );
			__m256i inp = _mm256_load_si256( (__m256i*)pk_mat ); pk_mat += 32;

			temp0 ^= _mm256_shuffle_epi8( ml , inp&mask );
			temp1 ^= _mm256_shuffle_epi8( ml , _mm256_srli_epi16(inp,4)&mask );
		}
		r0 ^= _mm256_shuffle_epi8( ml , temp0 );
		r1 ^= _mm256_shuffle_epi8( ml , temp1 );
	}
	_mm256_storeu_si256( (__m256i*)z , r0^_mm256_slli_epi16(r1,4) );
}








void mq_gf16_n95_m64_vartime_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t _x0[96] __attribute__((aligned(32)));
	__m128i mask16 = _mm_set1_epi8( 0xf );
	__m128i w0,w1;
	w0 = _mm_loadu_si128( (__m128i*) w );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) _x0 , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+16) , _mm_unpackhi_epi8(w0,w1) );
	w0 = _mm_loadu_si128( (__m128i*) (w+16) );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) (_x0+32) , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+48) , _mm_unpackhi_epi8(w0,w1) );
	w0 = _mm_loadu_si128( (__m128i*) (w+32) );
	w1 = _mm_srli_epi16( w0 , 4 ) & mask16;
	w0 &= mask16;
	_mm_store_si128( (__m128i*) (_x0+64) , _mm_unpacklo_epi8(w0,w1) );
	_mm_store_si128( (__m128i*) (_x0+80) , _mm_unpackhi_epi8(w0,w1) );

        __m256i mask = _mm256_load_si256( (__m256i*) __mask_low );

	__m256i r0 = _mm256_setzero_si256();
	__m256i r1 = _mm256_setzero_si256();
	for(unsigned i=0;i<95;i++) {
		unsigned b = _x0[i];
		__m256i ml = _mm256_load_si256( (__m256i*) (__gf16_mulx2 + 32*b) );

		__m256i inp = _mm256_load_si256( (__m256i*)pk_mat ); pk_mat += 32;
		r0 ^= _mm256_shuffle_epi8( ml , inp&mask );
		r1 ^= _mm256_shuffle_epi8( ml , _mm256_srli_epi16(inp,4)&mask );
	}

	for(unsigned i=0;i<95;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += 32*(i+1);
			continue;
		}
		__m256i temp0 = _mm256_setzero_si256();
		__m256i temp1 = _mm256_setzero_si256();
		__m256i ml;
		for(unsigned j=0;j<=i;j++) {
			unsigned b = _x0[j];
			ml = _mm256_load_si256( (__m256i*) (__gf16_mulx2 + 32*b) );
			__m256i inp = _mm256_load_si256( (__m256i*)pk_mat ); pk_mat += 32;

			temp0 ^= _mm256_shuffle_epi8( ml , inp&mask );
			temp1 ^= _mm256_shuffle_epi8( ml , _mm256_srli_epi16(inp,4)&mask );
		}
		r0 ^= _mm256_shuffle_epi8( ml , temp0 );
		r1 ^= _mm256_shuffle_epi8( ml , temp1 );
	}
	_mm256_storeu_si256( (__m256i*)z , r0^_mm256_slli_epi16(r1,4) );
}







