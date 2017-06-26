
#include "mq_gf256.h"

#include "gf16.h"

#include "string.h"


void mq_gf256_n68_m40_ref( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[40] __attribute__((aligned(32))) = {0};

	/// evaluate linear terms
	for(unsigned i=0;i<68;i++) {
		for(unsigned j=0;j<40;j++) {
			r[j] ^= gf256_mul( *pk_mat , w[i] );
			pk_mat ++;
		}
	}

	uint8_t temp_r[40] __attribute__((aligned(32))) = {0};
	/// evaluate quadratic terms
	for(unsigned i=0;i<68;i++) {
		memset( temp_r , 0 , 40 );
		for(unsigned k=0;k<=i;k++) {
			for(unsigned j=0;j<40;j++) {
				temp_r[j] ^= gf256_mul( *pk_mat , w[k] );
				pk_mat ++;
			}
		}
		for(unsigned j=0;j<40;j++) r[j] ^= gf256_mul( temp_r[j] , w[i] );
	}

	for(unsigned i=0;i<40;i++) z[i] = r[i];
}





void mq_gf256_n61_m45_ref( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[45] __attribute__((aligned(32))) = {0};

	/// evaluate linear terms
	for(unsigned i=0;i<61;i++) {
		for(unsigned j=0;j<45;j++) {
			r[j] ^= gf256_mul( *pk_mat , w[i] );
			pk_mat ++;
		}
	}

	uint8_t temp_r[45] __attribute__((aligned(32))) = {0};
	/// evaluate quadratic terms
	for(unsigned i=0;i<61;i++) {
		memset( temp_r , 0 , 45 );
		for(unsigned k=0;k<=i;k++) {
			for(unsigned j=0;j<45;j++) {
				temp_r[j] ^= gf256_mul( *pk_mat , w[k] );
				pk_mat ++;
			}
		}
		for(unsigned j=0;j<45;j++) r[j] ^= gf256_mul( temp_r[j] , w[i] );
	}

	for(unsigned i=0;i<45;i++) z[i] = r[i];
}



