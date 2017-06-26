
#include "gf16.h"



#include "emmintrin.h"
#include "tmmintrin.h"




void mq_gf16_n96_m64_vartime_ssse3( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
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

        __m128i mask = mask16;

	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	for(unsigned i=0;i<96;i++) {
		unsigned b = _x0[i];
	        __m128i ml = _mm_load_si128( (__m128i*) (__gf16_mulx2 + 32*b) );
	        __m128i mh = _mm_slli_epi16( ml , 4 );

		__m128i inp0 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;
		__m128i inp1 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;

		r0 ^= _mm_shuffle_epi8( ml , inp0&mask );
		r0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp0,4)&mask );
		r1 ^= _mm_shuffle_epi8( ml , inp1&mask );
		r1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp1,4)&mask );
	}

	for(unsigned i=0;i<96;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += 32*(i+1);
			continue;
		}
		__m128i temp0 = _mm_setzero_si128();
		__m128i temp1 = _mm_setzero_si128();
		__m128i ml,mh;
		for(unsigned j=0;j<=i;j++) {
			unsigned b = _x0[j];
			ml = _mm_load_si128( (__m128i*) (__gf16_mulx2 + 32*b) );
			mh = _mm_slli_epi16( ml , 4 );

			__m128i inp0 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;
			__m128i inp1 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;

			temp0 ^= _mm_shuffle_epi8( ml , inp0&mask );
			temp0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp0,4)&mask );
			temp1 ^= _mm_shuffle_epi8( ml , inp1&mask );
			temp1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp1,4)&mask );
		}
		r0 ^= _mm_shuffle_epi8( ml , temp0&mask );
		r0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(temp0,4)&mask );
		r1 ^= _mm_shuffle_epi8( ml , temp1&mask );
		r1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(temp1,4)&mask );
	}
	_mm_storeu_si128( (__m128i*)z , r0 );
	_mm_storeu_si128( (__m128i*)(z+16) , r1 );
}







void mq_gf16_n95_m64_vartime_ssse3( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
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

        __m128i mask = mask16;

	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	for(unsigned i=0;i<95;i++) {
		unsigned b = _x0[i];
	        __m128i ml = _mm_load_si128( (__m128i*) (__gf16_mulx2 + 32*b) );
	        __m128i mh = _mm_slli_epi16( ml , 4 );

		__m128i inp0 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;
		__m128i inp1 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;

		r0 ^= _mm_shuffle_epi8( ml , inp0&mask );
		r0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp0,4)&mask );
		r1 ^= _mm_shuffle_epi8( ml , inp1&mask );
		r1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp1,4)&mask );
	}

	for(unsigned i=0;i<95;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += 32*(i+1);
			continue;
		}
		__m128i temp0 = _mm_setzero_si128();
		__m128i temp1 = _mm_setzero_si128();
		__m128i ml,mh;
		for(unsigned j=0;j<=i;j++) {
			unsigned b = _x0[j];
			ml = _mm_load_si128( (__m128i*) (__gf16_mulx2 + 32*b) );
			mh = _mm_slli_epi16( ml , 4 );

			__m128i inp0 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;
			__m128i inp1 = _mm_load_si128( (__m128i*)pk_mat ); pk_mat += 16;

			temp0 ^= _mm_shuffle_epi8( ml , inp0&mask );
			temp0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp0,4)&mask );
			temp1 ^= _mm_shuffle_epi8( ml , inp1&mask );
			temp1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(inp1,4)&mask );
		}
		r0 ^= _mm_shuffle_epi8( ml , temp0&mask );
		r0 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(temp0,4)&mask );
		r1 ^= _mm_shuffle_epi8( ml , temp1&mask );
		r1 ^= _mm_shuffle_epi8( mh , _mm_srli_epi16(temp1,4)&mask );
	}
	_mm_storeu_si128( (__m128i*)z , r0 );
	_mm_storeu_si128( (__m128i*)(z+16) , r1 );
}






