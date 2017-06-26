
#ifndef _PFLASH_H_
#define _PFLASH_H_

#include "pflash_config.h"

#include "blas.h"

#include "string.h"


#ifdef  __cplusplus
extern  "C" {
#endif

struct pflash_gf16 {
	uint8_t mat_t[_PUB_M * _PUB_M_BYTE];
	uint8_t vec_t[_PUB_M_BYTE];
	uint8_t mat_s[_SEC_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];
};

typedef struct pflash_gf16 pflash_key;


static inline
void pflash_fdump( FILE *fp, const pflash_key * key ) {
	gf16mat_fdump(fp,key->mat_t,_PUB_M_BYTE,_PUB_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_t,_PUB_M_BYTE); fprintf(fp,"\n");

	gf16mat_fdump(fp,key->mat_s,_PUB_N_BYTE,_SEC_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_s,_PUB_N_BYTE); fprintf(fp,"\n");
}



//static inline
static
void pflash_ivs_central_map( uint8_t * r , const uint8_t * a );
//{ memcpy( r , a , _PUB_N_BYTE ); }

//static
//void pflash_ivs_central_map_batch32( uint8_t * r , const uint8_t * a );




#include "gfext.h"


#ifdef _PFLASH_80_

static inline
void pflash_central_map( uint8_t * r , const uint8_t * a ) {
	uint8_t tmp1[32] __attribute__((aligned(32)));

	uint8_t _a[32] __attribute__((aligned(32)));
	uint8_t _r[32] __attribute__((aligned(32)));
	ISO(_a,a);
	BGFPOW256_8(tmp1 , _a );
	BGFMUL(_r,tmp1,_a);
	IVSISO(r,_r);
}

#endif

#ifdef _PFLASH_128_

/// 2^(8*15) + 2^(8*31)
static inline
void pflash_central_map( uint8_t * r , const uint8_t * a ) {
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

#endif



static inline
void pflash_pubmap_seckey( uint8_t * z , const pflash_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	gf16mat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	pflash_central_map( tt , tt );

	gf16mat_prod( z , sk->mat_t , _PUB_M_BYTE , _PUB_M , tt );
	gf256v_add( z , sk->vec_t , _PUB_M_BYTE );

}


//#ifdef _DEBUG_
static inline
void pflash_genkey_debug( pflash_key * pk , pflash_key * sk )
{
	gf16mat_rand_inv( pk->mat_t , sk->mat_t , _PUB_M );
	gf16mat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf16v_rand( pk->vec_s , _SEC_N );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _PUB_M_BYTE );

	uint8_t inp[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	pflash_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _PUB_M_BYTE );

}
//#endif


#include "mpkc.h"

static inline
void pflash_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	pflash_pubmap_seckey( (uint8_t *)z , (const pflash_key *)pk_key, (const uint8_t *)w );
}

static inline
void pflash_genkey( uint8_t * pk , pflash_key * sk )
{

	pflash_key _pk;
	pflash_genkey_debug( &_pk , sk );

	mpkc_interpolate_gf16( pk , pflash_pubmap_wrapper , (const void*) &_pk );
}


#if 1

#include "mq_gf16_m64_vartime.h"
#if defined(_BLAS_AVX2_)
#define pflash_pubmap mq_gf16_n95_m64_vartime_avx2
#elif defined(_BLAS_SSE_)
#define pflash_pubmap mq_gf16_n95_m64_vartime_ssse3
#else
#define pflash_pubmap mq_gf16_n95_m64_vartime
#endif

#else

#define pflash_pubmap mpkc_pub_map_gf16

#endif





/*

static
void pflash_ivs_central_map_bitslice( uint8_t * , const uint8_t * );
#include "gf-ext-bitslice.h"

#define _BIT_SLICE_

*/

#define _LEN_SHA256_ 32


/*
static inline
void pflash_secmap_batch( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
	//memcpy( sha256_digest , seed , _LEN_SHA256_ );
	RAND_seed( seed , _LEN_SHA256_ );

	uint8_t is_z_zero = 0;
	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return; }

	uint8_t _z[_PUB_N_BYTE],y[_PUB_N_BYTE],x[_PUB_N_BYTE],_w[_PUB_N_BYTE];

	uint8_t temp_t[_PUB_N_BYTE] = {0};
	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf16mat_prod(temp_t,sk->mat_t,_PUB_M_BYTE,_PUB_M,_z);

	uint8_t temp_32[32*32] = {0};
#ifdef _BIT_SLICE_
	sto_t * _temp_32 = (sto_t*) temp_32;
	bit_extend(_temp_32, temp_t , _PUB_M_BYTE );
#else
	for(unsigned i=0;i<32;i++) memcpy( temp_32 + i*32 , temp_t , _PUB_M_BYTE );
#endif
	uint8_t temp_x[32*32] = {0};
	uint8_t last_s = 1;
	unsigned time = 0;
	while( 0 != last_s ) {
		if( 256 == time ) break;
#ifdef _BIT_SLICE_
		RAND_bytes( temp_32 + _PUB_M_BYTE * 32 , (_PUB_N_BYTE-_PUB_M_BYTE)*32 );
#else
for( unsigned i=0;i<32;i++) {
		RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest );
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
		memcpy(temp_32+(i*32+_PUB_M_BYTE),sha256_digest,_PUB_N_BYTE-_PUB_M_BYTE);
}
#endif
#ifdef _BIT_SLICE_
		//uint8_t temp1[32*32] = {0};
		uint8_t temp2[32*32] = {0};
		//transpose_32bytex32( temp1 , temp_32 );
		pflash_ivs_central_map_bitslice( temp2 , temp_32 );
		transpose_32x256( temp_x , temp2 );
#else
		pflash_ivs_central_map_batch32( temp_x , temp_32 );
#endif
for( unsigned i=0;i<32;i++) {
		gf256v_add( temp_x + i*32 , sk->vec_s , _PUB_N_BYTE );
		last_s = gf16v_dot( temp_x + i*32 , sk->last_row_s , _SEC_N );
		if( 0 == last_s ) {
			memcpy( x ,temp_x + i*32 , _PUB_N_BYTE );
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

*/



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
	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf16mat_prod(temp_t,sk->mat_t,_PUB_M_BYTE,_PUB_M,_z);

	uint8_t temp_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32))) = {0};
	for(unsigned j=0;j<_PUB_M_BYTE;j++){
		for(unsigned i=0;i<_BATCH_;i++) {
			temp_batch[j*_BATCH_+i] = temp_t[j];
		}
	}
	uint8_t x_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32)));

	uint8_t last_s = 1;
	unsigned time = 0;
	while( 0 != last_s ) {
		if( 256 == time ) break;

		for(unsigned i=_PUB_M_BYTE;i<_PUB_N_BYTE;i++) {
			RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest );
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
			memcpy(temp_batch+(i*_BATCH_),sha256_digest,_BATCH_);
		}

		pflash_ivs_central_map_byteslice_16( x_batch , temp_batch );

		gf256v_set_zero( temp_t , 16 );
		for(unsigned i=0;i<_PUB_N_BYTE;i++) gf16v_batch_madd_sse_16( temp_t , x_batch + i*16 , last_row_s[i] );

		uint8_t idx_i = 0;
		for(unsigned i=0;i<16;i++) {
			uint8_t result_i = temp_t[i]^last_s_offset;
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

	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(32)));

	uint8_t temp_t[_PUB_N_BYTE] __attribute__((aligned(32)))  = {0};
	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf16mat_prod(temp_t,sk->mat_t,_PUB_M_BYTE,_PUB_M,_z);

	uint8_t temp_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<_BATCH_;i++) memcpy( temp_batch + i*(_PUB_N_BYTE) , temp_t , _PUB_M_BYTE );
	uint8_t x_batch[_PUB_N_BYTE*_BATCH_] __attribute__((aligned(32)));

	uint8_t last_s = 1;
	unsigned time = 0;
	while( 0 != last_s ) {
		if( 256 == time ) break;

		for(unsigned i=0;i<_BATCH_;i++) {
			RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest )
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
			memcpy(temp_batch+((i*_PUB_N_BYTE)+_PUB_M_BYTE),sha256_digest,_PUB_N_BYTE-_PUB_M_BYTE);
		}

		pflash_ivs_central_map( x_batch , temp_batch );

		for(unsigned i=0;i<_BATCH_;i++) {
			gf256v_add( x_batch + i*_PUB_N_BYTE , sk->vec_s , _PUB_N_BYTE );
			last_s = gf16v_dot( x_batch + i*_PUB_N_BYTE , last_row_s , _SEC_N );
			if( 0 == last_s ) {  //// XXXXXXXXXX:
				memcpy( x , x_batch + i*_PUB_N_BYTE , _PUB_N_BYTE );
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




static inline
void pflash_secmap( uint8_t * w , const pflash_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
#ifdef _BYTE_FFT_
	pflash_secmap_fft( w , sk , z , seed );
#else
	pflash_secmap_ref( w , sk , z , seed );
#endif
}




/*
GCD( 256^31 - 1 , 256^8 + 1 )
Tar:
0x7F7F7F7F7F7F7F80808080808080807F7F7F7F7F7F7F7F8080808080808080

0x7F7F7F
7F7F7F7F
80808080
80808080
7F7F7F7F
7F7F7F7F
80808080
80808080


7F  : 0111,1111
80  : 1000,0000

P1: 7xsq --> 1000,0000    0x80 Done

P1-pow8 + P1 --> 8080     P11
P11-pow8x2 + P11 --> 8080,8080  P12
P12-pow8x4 + P12 --> 80808080,80808080 P13

P2: 1xsq + 1 --> 11
P3: 1xsq + 1 --> 111
P4: 1xsq + 1 --> 1111
P3x4sq + P4  -->  111,1111 0x7F Done  , P5

P5-pow8x1 + P5 --> 7F,7F    P6
P6-pow8x2 + P6 -> 7F7F,7F7F  P7
P5-pow8x2 + P6 ->   7F,7F7F  P71
P71-pow8x4 + P7 ->  7F7F7F,7F7F7F7F  P72

P5-pow8x15 -->     7F000000,00000000,00x8  P8

P72-pow8x8 + P13 -->  7f7f7f,7f7f7f7f,80808080,80808080,   P14

P14-pow8x16 + P14 + P8 :  Done

*/
#ifdef _PFLASH_80_

static inline
void pflash_ivs_central_map( uint8_t * _r , const uint8_t * _a ) {
	uint8_t P1[32] __attribute__((aligned(32))),P11[32],P12[32],P13[32],P14[32];
	uint8_t P2[32] __attribute__((aligned(32))),P3[32],P4[32],P5[32],P6[32],P7[32],P8[32],P71[32],P72[32],tmp[32];
	uint8_t a[32] __attribute__((aligned(32)));
	uint8_t r[32] __attribute__((aligned(32)));

	ISO( a , _a );
	/// P1: 7xsq --> 1000,0000    0x80 Done
	BGFSQU( tmp , a);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFSQU( tmp , tmp);
	BGFSQU( P1 , tmp);

	/// P1-pow8 + P1 --> 8080     P11
	BGFPOW256_1( tmp , P1 );
	BGFMUL( P11 , tmp , P1 );

	/// P11-pow8x2 + P11 --> 8080,8080  P12
	BGFPOW256_2( tmp , P11 );
	BGFMUL( P12 , tmp , P11 );

	/// P12-pow8x4 + P12 --> 80808080,80808080 P13
	BGFPOW256_4( tmp , P12 );
	BGFMUL( P13 , tmp , P12 );

	/// P2: 1xsq + 1 --> 11
	BGFSQU( tmp , a );
	BGFMUL( P2 , tmp , a );
	/// P3: 1xsq + 1 --> 111
	BGFSQU( tmp , P2 );
	BGFMUL( P3 , tmp , a );
	/// P4: 1xsq + 1 --> 1111
	BGFSQU( tmp , P3 );
	BGFMUL( P4 , tmp , a );

	/// P3x4sq + P4  -->  111,1111 0x7F Done  , P5
	BGFSQU( tmp , P3 );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFSQU( tmp , tmp );
	BGFMUL( P5 , tmp , P4 );

	/// P5-pow8x1 + P5 --> 7F,7F    P6
	BGFPOW256_1( tmp , P5 );
	BGFMUL( P6 , tmp , P5 );

	/// P6-pow8x2 + P6 -> 7F7F,7F7F  P7
	BGFPOW256_2( tmp , P6 );
	BGFMUL( P7 , tmp , P6 );

	/// P5-pow8x2 + P6 ->   7F,7F7F  P71
	BGFPOW256_2( tmp , P5 );
	BGFMUL( P71 , tmp , P6 );

	/// P71-pow8x4 + P7 ->  7F7F7F,7F7F7F7F  P72
	BGFPOW256_4( tmp , P71 );
	BGFMUL( P72 , tmp , P7 );

	/// P5-pow8x15 -->     7F000000,00000000,00x8  P8
	BGFPOW256_15( P8 , P5 );

	/// P72-pow8x8 + P13 -->  7f7f7f,7f7f7f7f,80808080,80808080,   P14
	BGFPOW256_8( tmp , P72 );
	BGFMUL( P14 , tmp , P13 );

	/// P14-pow8x16 + P14 + P8 :  Done
	BGFPOW256_16( tmp , P14 );
	BGFMUL( tmp , tmp , P14 );
	BGFMUL( r , tmp , P8 );

	IVSISO( _r , r );

	/// r = outA;
}

#endif


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

#ifdef _PFLASH_128_


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


static inline
void pflash_ivs_central_map( uint8_t * r , const uint8_t * _a ) {
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


/*

static inline
void pflash_ivs_central_map_batch32( uint8_t * r , const uint8_t * a ) {

	uint8_t P1[32*32],P11[32*32],P12[32*32],P13[32*32],P14[32*32];
	uint8_t P2[32*32],P3[32*32],P4[32*32],P5[32*32],P6[32*32],P7[32*32],P8[32*32],P71[32*32],P72[32*32],tmp[32*32];

	/// P1: 7xsq --> 1000,0000    0x80 Done
	gf256ext_31_squ_batch32( tmp , a);
	gf256ext_31_squ_batch32( tmp , tmp);
	gf256ext_31_squ_batch32( tmp , tmp);
	gf256ext_31_squ_batch32( tmp , tmp);
	gf256ext_31_squ_batch32( tmp , tmp);
	gf256ext_31_squ_batch32( tmp , tmp);
	gf256ext_31_squ_batch32( P1 , tmp);

	/// P1-pow8 + P1 --> 8080     P11
	gf256ext_31_pow_256_1_batch32( tmp , P1 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_1( tmp+i*32 , P1+i*32 );
	gf256ext_31_mul_batch32( P11 , tmp , P1 );

	/// P11-pow8x2 + P11 --> 8080,8080  P12
	gf256ext_31_pow_256_2_batch32( tmp , P11 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_2( tmp+i*32 , P11+i*32 );
	gf256ext_31_mul_batch32( P12 , tmp , P11 );

	/// P12-pow8x4 + P12 --> 80808080,80808080 P13
	gf256ext_31_pow_256_4_batch32( tmp , P12 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_4( tmp+i*32 , P12+i*32 );
	gf256ext_31_mul_batch32( P13 , tmp , P12 );

	/// P2: 1xsq + 1 --> 11
	gf256ext_31_squ_batch32( tmp , a );
	gf256ext_31_mul_batch32( P2 , tmp , a );
	/// P3: 1xsq + 1 --> 111
	gf256ext_31_squ_batch32( tmp , P2 );
	gf256ext_31_mul_batch32( P3 , tmp , a );
	/// P4: 1xsq + 1 --> 1111
	gf256ext_31_squ_batch32( tmp , P3 );
	gf256ext_31_mul_batch32( P4 , tmp , a );

	/// P3x4sq + P4  -->  111,1111 0x7F Done  , P5
	gf256ext_31_squ_batch32( tmp , P3 );
	gf256ext_31_squ_batch32( tmp , tmp );
	gf256ext_31_squ_batch32( tmp , tmp );
	gf256ext_31_squ_batch32( tmp , tmp );
	gf256ext_31_mul_batch32( P5 , tmp , P4 );

	/// P5-pow8x1 + P5 --> 7F,7F    P6
	gf256ext_31_pow_256_1_batch32( tmp , P5 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_1( tmp+i*32 , P5+i*32 );
	gf256ext_31_mul_batch32( P6 , tmp , P5 );

	/// P6-pow8x2 + P6 -> 7F7F,7F7F  P7
	gf256ext_31_pow_256_2_batch32( tmp , P6 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_2( tmp+i*32 , P6+i*32 );
	gf256ext_31_mul_batch32( P7 , tmp , P6 );

	/// P5-pow8x2 + P6 ->   7F,7F7F  P71
	gf256ext_31_pow_256_2_batch32( tmp , P5 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_2( tmp+i*32 , P5+i*32 );
	gf256ext_31_mul_batch32( P71 , tmp , P6 );

	/// P71-pow8x4 + P7 ->  7F7F7F,7F7F7F7F  P72
	gf256ext_31_pow_256_4_batch32( tmp , P71 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_4( tmp+i*32 , P71+i*32 );
	gf256ext_31_mul_batch32( P72 , tmp , P7 );

	/// P5-pow8x15 -->     7F000000,00000000,00x8  P8
	gf256ext_31_pow_256_15_batch32( P8 , P5 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_15( P8+i*32 , P5+i*32 );

	/// P72-pow8x8 + P13 -->  7f7f7f,7f7f7f7f,80808080,80808080,   P14
	gf256ext_31_pow_256_8_batch32( tmp , P72 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_8( tmp+i*32 , P72+i*32 );
	gf256ext_31_mul_batch32( P14 , tmp , P13 );

	/// P14-pow8x16 + P14 + P8 :  Done
	gf256ext_31_pow_256_16_batch32( tmp , P14 );
	//for(int i=0;i<32;i++) gf256ext_31_pow_256_16( tmp+i*32 , P14+i*32 );
	gf256ext_31_mul_batch32( tmp , tmp , P14 );
	gf256ext_31_mul_batch32( r , tmp , P8 );

}



static inline
void pflash_ivs_central_map_bitslice( uint8_t * r , const uint8_t * a ) {

	uint8_t P1[32*32],P11[32*32],P12[32*32],P13[32*32],P14[32*32];
	uint8_t P2[32*32],P3[32*32],P4[32*32],P5[32*32],P6[32*32],P7[32*32],P8[32*32],P71[32*32],P72[32*32],tmp[32*32];

	/// P1: 7xsq --> 1000,0000    0x80 Done
	bs_gf256_31_squ( (sto_t*)tmp , (const sto_t *)a);
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp);
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp);
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp);
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp);
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp);
	bs_gf256_31_squ( (sto_t*)P1 , (sto_t*)tmp);

	/// P1-pow8 + P1 --> 8080     P11
	bs_gf256_31_pow_256_1( (sto_t*)tmp , (sto_t*)P1 );
	bs_gf256_31_mul( (sto_t*)P11 , (sto_t*)tmp , (sto_t*)P1 );

	/// P11-pow8x2 + P11 --> 8080,8080  P12
	bs_gf256_31_pow_256_2( (sto_t*)tmp , (sto_t*)P11 );
	bs_gf256_31_mul( (sto_t*)P12 , (sto_t*)tmp , (sto_t*)P11 );

	/// P12-pow8x4 + P12 --> 80808080,80808080 P13
	bs_gf256_31_pow_256_4( (sto_t*)tmp , (sto_t*)P12 );
	bs_gf256_31_mul( (sto_t*)P13 , (sto_t*)tmp , (sto_t*)P12 );

	/// P2: 1xsq + 1 --> 11
	bs_gf256_31_squ( (sto_t*)tmp , (const sto_t*)a );
	bs_gf256_31_mul( (sto_t*)P2 , (sto_t*)tmp , (sto_t*)a );
	/// P3: 1xsq + 1 --> 111
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)P2 );
	bs_gf256_31_mul( (sto_t*)P3 , (sto_t*)tmp , (sto_t*)a );
	/// P4: 1xsq + 1 --> 1111
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)P3 );
	bs_gf256_31_mul( (sto_t*)P4 , (sto_t*)tmp , (sto_t*)a );

	/// P3x4sq + P4  -->  111,1111 0x7F Done  , P5
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)P3 );
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp );
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp );
	bs_gf256_31_squ( (sto_t*)tmp , (sto_t*)tmp );
	bs_gf256_31_mul( (sto_t*)P5 , (sto_t*)tmp , (sto_t*)P4 );

	/// P5-pow8x1 + P5 --> 7F,7F    P6
	bs_gf256_31_pow_256_1( (sto_t*)tmp , (sto_t*)P5 );
	bs_gf256_31_mul( (sto_t*)P6 , (sto_t*)tmp , (sto_t*)P5 );

	/// P6-pow8x2 + P6 -> 7F7F,7F7F  P7
	bs_gf256_31_pow_256_2( (sto_t*)tmp , (sto_t*)P6 );
	bs_gf256_31_mul( (sto_t*)P7 , (sto_t*)tmp , (sto_t*)P6 );

	/// P5-pow8x2 + P6 ->   7F,7F7F  P71
	bs_gf256_31_pow_256_2( (sto_t*)tmp , (sto_t*)P5 );
	bs_gf256_31_mul( (sto_t*)P71 , (sto_t*)tmp , (sto_t*)P6 );

	/// P71-pow8x4 + P7 ->  7F7F7F,7F7F7F7F  P72
	bs_gf256_31_pow_256_4( (sto_t*)tmp , (sto_t*)P71 );
	bs_gf256_31_mul( (sto_t*)P72 , (sto_t*)tmp , (sto_t*)P7 );

	/// P5-pow8x15 -->     7F000000,00000000,00x8  P8
	bs_gf256_31_pow_256_15( (sto_t*)P8 , (sto_t*)P5 );

	/// P72-pow8x8 + P13 -->  7f7f7f,7f7f7f7f,80808080,80808080,   P14
	bs_gf256_31_pow_256_8( (sto_t*)tmp , (sto_t*)P72 );
	bs_gf256_31_mul( (sto_t*)P14 , (sto_t*)tmp , (sto_t*)P13 );

	/// P14-pow8x16 + P14 + P8 :  Done
	bs_gf256_31_pow_256_16( (sto_t*)tmp , (sto_t*)P14 );
	bs_gf256_31_mul( (sto_t*)tmp , (sto_t*)tmp , (sto_t*)P14 );
	bs_gf256_31_mul( (sto_t*)r , (sto_t*)tmp , (sto_t*)P8 );

}

*/



#ifdef  __cplusplus
}
#endif


#endif
