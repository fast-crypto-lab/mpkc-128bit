#include <stdint.h>


#include "emmintrin.h"
#include "tmmintrin.h"
#include "smmintrin.h"

#include <immintrin.h>



void mq_gf2_n256_m224_vartime_sse( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	__m128i r0 = _mm_setzero_si128();
	uint64_t r2 = 0;
	uint32_t r3 = 0;

	uint8_t ww[256];
	for(unsigned i=0;i<32;i++) {
		for(unsigned j=0;j<8;j++) {
			ww[i*8+j] = (w[i]>>j)&1;
		}
	}

	/// linear terms
	for(unsigned i=0;i<256;i++) {
		if( ww[i] ) {
			r0 ^= _mm_loadu_si128( (__m128i *) pk_mat ); pk_mat += 16;
			r2 ^= *(const uint64_t *) pk_mat; pk_mat += 8;
			r3 ^= *(const uint32_t *) pk_mat; pk_mat += 4;
		} else {
			pk_mat += 28;
		}
	}
	/// quadratic terms
	for(unsigned k=1;k<256;k++) {
		if( 0==ww[k] ) {
			pk_mat += 28*k;
			continue;
		}
		for(unsigned i=0;i<k;i++) {
			if( ww[i] ) {
				r0 ^= _mm_loadu_si128( (__m128i *) pk_mat ); pk_mat += 16;
				r2 ^= *(const uint64_t *) pk_mat; pk_mat += 8;
				r3 ^= *(const uint32_t *) pk_mat; pk_mat += 4;
			} else {
				pk_mat += 28;
			}
		}
	}
	_mm_storeu_si128( (__m128i*) z , r0 );
	*(uint64_t *)(&z[16]) = r2;
	*(uint32_t *)(&z[24]) = r3;

}

