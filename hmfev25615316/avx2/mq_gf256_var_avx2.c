
#include "mq_gf256.h"

#include "emmintrin.h"
#include "tmmintrin.h"

#include <immintrin.h>

#include "gf16.h"

#include "string.h"



void mq_gf256_n68_m40_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	__m256i mask_0xf = _mm256_load_si256((__m256i const *) __mask_low);

	__m256i r0 = _mm256_setzero_si256();
	__m256i r1 = _mm256_setzero_si256();

	__m256i mtab_l[68];
	__m256i mtab_h[68];
	for(unsigned i=0;i<68;i++) {
		uint32_t qq = w[i];
		__m256i mul_tab_h = _mm256_load_si256((__m256i*) (__gf256_mul + 32*qq) );
		mtab_l[i] = _mm256_permute2x128_si256(mul_tab_h,mul_tab_h,0x00 );
		mtab_h[i] = _mm256_permute2x128_si256(mul_tab_h,mul_tab_h,0x11 );
	}

	/// evaluate linear terms
	__m256i mul_tab_l;
	__m256i mul_tab_h;
	for(unsigned i=0;i<68;i++) {
		mul_tab_l = mtab_l[i];
		mul_tab_h = mtab_h[i];

		__m256i key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 32;
		__m256i k_h = _mm256_srli_epi16(key,4) & mask_0xf;
		r0 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
		key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 8;
		k_h = _mm256_srli_epi16(key,4) & mask_0xf;
		r1 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
	}

	/// evaluate quadratic terms
	__m256i zero = _mm256_setzero_si256();
	for(unsigned i=0;i<68;i++) {
		__m256i t0 = zero;
		__m256i t1 = zero;
		for(unsigned j=0;j<=i;j++) {
			mul_tab_l = mtab_l[j];
			mul_tab_h = mtab_h[j];

			__m256i key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 32;
			__m256i k_h = _mm256_srli_epi16(key,4) & mask_0xf;
			t0 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
			key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 8;
			k_h = _mm256_srli_epi16(key,4) & mask_0xf;
			t1 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
		}
		__m256i t0_h = _mm256_srli_epi16( t0 , 4 )&mask_0xf;
		__m256i t1_h = _mm256_srli_epi16( t1 , 4 )&mask_0xf;
		r0 ^= _mm256_shuffle_epi8( mul_tab_l , t0&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , t0_h );
		r1 ^= _mm256_shuffle_epi8( mul_tab_l , t1&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , t1_h );
	}

	_mm256_storeu_si256((__m256i*)z , r0);
	uint8_t ttt[32] __attribute__((aligned(32)));
	_mm256_store_si256((__m256i*) ttt  , r1);
	for(unsigned i=0;i<8;i++) z[32+i] = ttt[i];
}









void mq_gf256_n61_m45_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	__m256i mask_0xf = _mm256_load_si256((__m256i const *) __mask_low);

	__m256i r0 = _mm256_setzero_si256();
	__m256i r1 = _mm256_setzero_si256();

	__m256i mtab_l[61];
	__m256i mtab_h[61];
	for(unsigned i=0;i<61;i++) {
		uint32_t qq = w[i];
		__m256i mul_tab_h = _mm256_load_si256((__m256i*) (__gf256_mul + 32*qq) );
		mtab_l[i] = _mm256_permute2x128_si256(mul_tab_h,mul_tab_h,0x00 );
		mtab_h[i] = _mm256_permute2x128_si256(mul_tab_h,mul_tab_h,0x11 );
	}

	/// evaluate linear terms
	__m256i mul_tab_l;
	__m256i mul_tab_h;
	for(unsigned i=0;i<61;i++) {
		mul_tab_l = mtab_l[i];
		mul_tab_h = mtab_h[i];

		__m256i key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 32;
		__m256i k_h = _mm256_srli_epi16(key,4) & mask_0xf;
		r0 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
		key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 13;
		k_h = _mm256_srli_epi16(key,4) & mask_0xf;
		r1 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
	}

	/// evaluate quadratic terms
	__m256i zero = _mm256_setzero_si256();
	for(unsigned i=0;i<61;i++) {
		__m256i t0 = zero;
		__m256i t1 = zero;
		for(unsigned j=0;j<=i;j++) {
			mul_tab_l = mtab_l[j];
			mul_tab_h = mtab_h[j];

			__m256i key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 32;
			__m256i k_h = _mm256_srli_epi16(key,4) & mask_0xf;
			t0 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
			key = _mm256_loadu_si256((__m256i *)pk_mat); pk_mat += 13;
			k_h = _mm256_srli_epi16(key,4) & mask_0xf;
			t1 ^= _mm256_shuffle_epi8( mul_tab_l , key&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , k_h );
		}
		__m256i t0_h = _mm256_srli_epi16( t0 , 4 )&mask_0xf;
		__m256i t1_h = _mm256_srli_epi16( t1 , 4 )&mask_0xf;
		r0 ^= _mm256_shuffle_epi8( mul_tab_l , t0&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , t0_h );
		r1 ^= _mm256_shuffle_epi8( mul_tab_l , t1&mask_0xf ) ^ _mm256_shuffle_epi8( mul_tab_h , t1_h );
	}

	_mm256_storeu_si256((__m256i*)z , r0);
	uint8_t ttt[32] __attribute__((aligned(32)));
	_mm256_store_si256((__m256i*) ttt  , r1);
	for(unsigned i=0;i<13;i++) z[32+i] = ttt[i];
}


