
#include "gf16.h"



void mq_gf16_n96_m64_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t _x0[96] __attribute__((aligned(32)));

	for(unsigned i=0;i<48;i++) {
		_x0[i*2] = w[i]&0xf;
		_x0[i*2+1] = (w[i]&0xf0)>>4;
	}

	uint8_t r[32] __attribute__((aligned(32))) = {0};

	/// evaluate linear terms
	for(unsigned i=0;i<96;i++) {
		for(unsigned j=0;j<32;j++) {
			r[j] ^= gf256_mul_gf16( *pk_mat , _x0[i] );
			pk_mat ++;
		}
	}

	uint8_t temp_r[32] __attribute__((aligned(32))) = {0};
	/// evaluate quadratic terms
	for(unsigned i=0;i<96;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += (i+1)*32;
			continue;
		}
		for(unsigned i=0;i<32;i++) temp_r[i]^=temp_r[i];
		for(unsigned k=0;k<=i;k++) {
			for(unsigned j=0;j<32;j++) {
				temp_r[j] ^= gf256_mul_gf16( *pk_mat , _x0[k] );
				pk_mat ++;
			}
		}
		for(unsigned j=0;j<32;j++) r[j] ^= gf256_mul_gf16( temp_r[j] , _x0[i] );

	}

	for(unsigned i=0;i<32;i++) z[i] = r[i];
}







void mq_gf16_n95_m64_vartime( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t _x0[96] __attribute__((aligned(32)));

	for(unsigned i=0;i<48;i++) {
		_x0[i*2] = w[i]&0xf;
		_x0[i*2+1] = (w[i]&0xf0)>>4;
	}

	uint8_t r[32] __attribute__((aligned(32))) = {0};

	/// evaluate linear terms
	for(unsigned i=0;i<95;i++) {
		for(unsigned j=0;j<32;j++) {
			r[j] ^= gf256_mul_gf16( *pk_mat , _x0[i] );
			pk_mat ++;
		}
	}

	uint8_t temp_r[32] __attribute__((aligned(32))) = {0};
	/// evaluate quadratic terms
	for(unsigned i=0;i<95;i++) {
		if( 0 == _x0[i] ) {
			pk_mat += (i+1)*32;
			continue;
		}
		for(unsigned i=0;i<32;i++) temp_r[i]^=temp_r[i];
		for(unsigned k=0;k<=i;k++) {
			for(unsigned j=0;j<32;j++) {
				temp_r[j] ^= gf256_mul_gf16( *pk_mat , _x0[k] );
				pk_mat ++;
			}
		}
		for(unsigned j=0;j<32;j++) r[j] ^= gf256_mul_gf16( temp_r[j] , _x0[i] );

	}

	for(unsigned i=0;i<32;i++) z[i] = r[i];
}


