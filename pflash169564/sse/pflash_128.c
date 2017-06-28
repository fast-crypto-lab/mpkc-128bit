
#include "pflash_config.h"

#include "pflash.h"

#include "blas.h"

#include "string.h"


//#define _DEBUG_MPKC_


static inline
void pflash_fdump( FILE *fp, const pflash_key * key ) {
	gf16mat_fdump(fp,key->mat_t,_PUB_N_BYTE,_SEC_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_t,_PUB_N_BYTE); fprintf(fp,"\n");

	gf16mat_fdump(fp,key->mat_s,_PUB_N_BYTE,_SEC_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_s,_PUB_N_BYTE); fprintf(fp,"\n");
}




void pflash_pubmap_seckey( uint8_t * z , const pflash_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	gf16mat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	pflash_central_map( tt , tt );

	uint8_t tt2[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	gf16mat_prod( tt2 , sk->mat_t , _PUB_N_BYTE , _SEC_N , tt );
	gf256v_add( tt2 , sk->vec_t , _PUB_N_BYTE );
	memcpy( z , tt2 , _PUB_N_BYTE ); /// XXX:
}



void pflash_genkey_debug( pflash_key * pk , pflash_key * sk )
{
	gf16mat_rand_inv( pk->mat_t , sk->mat_t , _SEC_N );
	gf16mat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf256v_rand( pk->vec_s , _PUB_N_BYTE );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _PUB_N_BYTE );

	uint8_t inp[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	pflash_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _PUB_N_BYTE );

}




#include "mpkc.h"

static inline
void pflash_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	pflash_pubmap_seckey( _z , (const pflash_key *)pk_key, (const uint8_t *)w );
	memcpy( z , _z , _PUB_M_BYTE );
}



void pflash_genkey( uint8_t * pk , pflash_key * sk )
{

	pflash_key _pk;
	pflash_genkey_debug( &_pk , sk );

	mpkc_interpolate_gf16( pk , pflash_pubmap_wrapper , (const void*) &_pk );
}







#ifdef _PFLASH_128_



#include "gfext.h"




/// 2^(8*15) + 2^(8*31)
void pflash_central_map( uint8_t * r , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
	memcpy(r,a,_PUB_N_BYTE);
	return;
#endif
	uint8_t tmp1[48] __attribute__((aligned(32)));
	uint8_t tmp2[48] __attribute__((aligned(32)));

	uint8_t _a[48] __attribute__((aligned(32)));
	uint8_t _r[48] __attribute__((aligned(32)));
	ISO(_a,a);
//	IVSISO(r,_a);
//	return;
	BGFPOW256_15(tmp1 , _a );
	BGFPOW256_31(tmp2 , _a );
	BGFMUL(_r,tmp1,tmp2);
	IVSISO(r,_r);
}





#ifdef _BYTE_FFT_

static inline
void pflash_ivs_central_map_byteslice_16( uint8_t * r , const uint8_t * a );


static inline
uint8_t is_zero_mask( uint8_t a ){
	a |= (a>>2);
	uint8_t or_i = (a|(a>>1))&1;
	uint8_t r = -1;
	r += or_i;
	return r;
}

static inline
void pflash_secmap_fft( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
	//memcpy( sha256_digest , seed , _LEN_SHA256_ );
	RAND_seed( seed , _LEN_SHA256_ );

	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return; }

	uint8_t last_row_s[_SEC_N] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<_SEC_N;i++) {
		unsigned char t = gf16v_get_ele( sk->mat_s + _PUB_N_BYTE * i , _SEC_N - 1 );
		gf16v_set_ele( last_row_s , i , t );
	}
	uint8_t last_s_offset = gf16v_dot( sk->vec_s , last_row_s , _SEC_N );

	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(32)));

	uint8_t temp_t[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	uint8_t temp_t_rand[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf16mat_prod(temp_t,sk->mat_t,_PUB_N_BYTE,_PUB_M,_z);

	uint8_t temp_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32))) = {0};
	uint8_t x_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32)));

	uint8_t last_s = 1;
	unsigned time = 0;

	uint8_t temp2[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	while( 0 != last_s ) {
		if( 256 == time ) break;

		for(unsigned i=0;i<_BATCH_;i++) {
			RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest )
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
			memcpy( _z , sha256_digest , _PUB_N_BYTE-_PUB_M_BYTE );
			gf256v_add( _z , (sk->vec_t) + _PUB_M_BYTE , _PUB_N_BYTE-_PUB_M_BYTE );
			gf16mat_prod( temp_t_rand , (sk->mat_t) + (_PUB_N_BYTE*_PUB_M) , _PUB_N_BYTE , _SEC_N-_PUB_M , _z );
			gf256v_add( temp_t_rand , temp_t , _PUB_N_BYTE );
			tbl_gf256ext_48_sse_insert( temp_batch , temp_t_rand , i );
		}

		pflash_ivs_central_map_byteslice_16( x_batch , temp_batch );

		gf256v_set_zero( temp2 , 16 );
		for(unsigned i=0;i<_PUB_N_BYTE;i++) gf16v_batch_madd_sse_16( temp2 , x_batch + i*16 , last_row_s[i] );

		uint8_t idx_i = 0;
		for(unsigned i=0;i<16;i++) {
			uint8_t result_i = temp2[i]^last_s_offset;
			uint8_t mask = is_zero_mask(result_i);
			uint8_t mask_r = is_zero_mask( idx_i );
			idx_i += ((i+1)&mask)&mask_r;
		}
		if( idx_i ) {
			last_s = 0;
			unsigned i = idx_i -1;
			tbl_gf256ext_48_sse_extract( x , x_batch , i );
			gf256v_add( x , sk->vec_s , _PUB_N_BYTE );
			break;
		}
		time++;
	};

	memset(w,0,_PUB_N_BYTE);
	gf16mat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//	return time;
	return;
}



#endif


static inline
void pflash_secmap_ref( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
	//memcpy( sha256_digest , seed , _LEN_SHA256_ );
	RAND_seed( seed , _LEN_SHA256_ );

	//uint8_t is_z_zero = 0;
	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return; }

	uint8_t last_row_s[_SEC_N] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<_SEC_N;i++) {
		unsigned char t = gf16v_get_ele( sk->mat_s + _PUB_N_BYTE * i , _SEC_N - 1 );
		gf16v_set_ele( last_row_s , i , t );
	}
	uint8_t last_s_offset = gf16v_dot( sk->vec_s , last_row_s , _SEC_N );

	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(32)));

	uint8_t temp_t[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	uint8_t temp_t_rand[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf16mat_prod(temp_t,sk->mat_t,_PUB_N_BYTE,_PUB_M,_z);

	uint8_t temp_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32))) = {0};
	uint8_t x_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32)));

	uint8_t last_s = 1;
	unsigned time = 0;
	while( 0 != last_s ) {
		if( 256 == time ) break;

		for(unsigned i=0;i<_BATCH_;i++) {
			RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest )
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
			memcpy( _z , sha256_digest , _PUB_N_BYTE-_PUB_M_BYTE );
			gf256v_add( _z , (sk->vec_t) + _PUB_M_BYTE , _PUB_N_BYTE-_PUB_M_BYTE );
			gf16mat_prod( temp_t_rand , (sk->mat_t) + (_PUB_N_BYTE*_PUB_M) , _PUB_N_BYTE , _SEC_N-_PUB_M , _z );
			gf256v_add( temp_t_rand , temp_t , _PUB_N_BYTE );
			memcpy(temp_batch+(i*_PUB_N_BYTE), temp_t_rand , _PUB_N_BYTE );
		}

		pflash_ivs_central_map( x_batch , temp_batch );

		for(unsigned i=0;i<_BATCH_;i++) {
			last_s = last_s_offset ^ gf16v_dot( x_batch + i*_PUB_N_BYTE , last_row_s , _SEC_N );
			if( 0 == last_s ) {
				memcpy( x , sk->vec_s , _PUB_N_BYTE );
				gf256v_add( x , x_batch + i*_PUB_N_BYTE , _PUB_N_BYTE );
				break;
			}
			time++;
		}
	};
	memset(w,0,_PUB_N_BYTE);
	gf16mat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//	return time;
	return;
}





void pflash_secmap( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
#ifdef _BYTE_FFT_
	pflash_secmap_fft( w , sk , z , seed );
#else
	pflash_secmap_ref( w , sk , z , seed );
#endif
}






/*
XGCD( 2^384 - 1 , 2^(8*15) + 2^(8*31) ):Hex;
0x1 -0x80000000000000000000000000000001 0x800000000000000000000000000000007FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF80

(1)
80
000000
000000
000000
000000
000000
7F
FFFFFF
FFFFFF
FFFFFF
FFFFFF
FFFFFF
80

(2)
80000000
00000000
00000000
00000000
7FFFFFFF
FFFFFFFF
FFFFFFFF
FFFFFFFF
80

*/



#ifdef _BYTE_FFT_

static inline
void pflash_ivs_central_map_byteslice_16( uint8_t * r , const uint8_t * a ) {
	uint8_t tmp[48*16] __attribute__((aligned(32)));
	uint8_t p1[48*16] __attribute__((aligned(32)));

	TBL_BGFSQU( tmp , a);
	TBL_BGFMUL( p1 , tmp , a ); // 3
	TBL_BGFSQU( tmp , p1);
	TBL_BGFSQU( tmp , tmp);
	TBL_BGFMUL( p1 , tmp , p1 ); // f
	TBL_BGFSQU( tmp , p1);
	TBL_BGFSQU( tmp , tmp);
	TBL_BGFSQU( tmp , tmp);
	TBL_BGFSQU( tmp , tmp);
	TBL_BGFMUL( p1 , tmp, p1 ); // ff

	TBL_BGFPOW256_1( tmp , p1 );
	TBL_BGFMUL( p1 , tmp , p1 ); // ffx2
	TBL_BGFPOW256_2( tmp , p1 );
	TBL_BGFMUL( p1 , tmp , p1 ); // ffx4
	TBL_BGFPOW256_4( tmp , p1 );
	TBL_BGFMUL( p1 , tmp , p1 ); // ffx8
	TBL_BGFPOW256_8( tmp , p1 );
	TBL_BGFMUL( p1 , tmp , p1 ); // ffx16

	TBL_BGFPOW256_32( tmp , a ); // 1,00x32
	TBL_BGFMUL( p1 , tmp , p1 ); // 1,00x16,ffx16

	TBL_BGFSQU( tmp , p1 );
	TBL_BGFSQU( tmp , tmp );
	TBL_BGFSQU( tmp , tmp );
	TBL_BGFSQU( tmp , tmp );
	TBL_BGFSQU( tmp , tmp );
	TBL_BGFSQU( tmp , tmp );
	TBL_BGFSQU( r , tmp );
}
#endif


void pflash_ivs_central_map( uint8_t * r , const uint8_t * _a ) {
#ifdef _DEBUG_MPKC_
	memcpy(r,_a,_PUB_N_BYTE);
	return;
#endif
	uint8_t a[48] __attribute__((aligned(32)));
	uint8_t tmp[48] __attribute__((aligned(32)));
	uint8_t p1[48] __attribute__((aligned(32)));

	ISO( a , _a );
//	IVSISO(r,a);
//	return;

	BGFSQU( tmp , a);
	BGFMUL( p1 , tmp , a ); // 3
	BGFSQU( tmp , p1);
	BGFSQU( tmp , tmp);
	BGFMUL( p1 , tmp , p1 ); // f
	BGFSQU( tmp , p1);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFMUL( p1 , tmp, p1 ); // ff

	BGFPOW256_1( tmp , p1 );
	BGFMUL( p1 , tmp , p1 ); // ffx2
	BGFPOW256_2( tmp , p1 );
	BGFMUL( p1 , tmp , p1 ); // ffx4
	BGFPOW256_4( tmp , p1 );
	BGFMUL( p1 , tmp , p1 ); // ffx8
	BGFPOW256_8( tmp , p1 );
	BGFMUL( p1 , tmp , p1 ); // ffx16

	BGFPOW256_32( tmp , a ); // 1,00x32
	BGFMUL( p1 , tmp , p1 ); // 1,00x16,ffx16

	BGFSQU( tmp , p1 );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );

	IVSISO( r , tmp );
}




#endif
