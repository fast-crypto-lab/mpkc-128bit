
#ifndef _RAINBOW_H_
#define _RAINBOW_H_

#include "rainbow_config.h"

#include "blas.h"

#include "string.h"

//#define _DEBUG_MPKC_

//#define _BENCHMARK_LINEARSOLVER


#ifdef  __cplusplus
extern  "C" {
#endif

struct _rainbow_ckey {
	uint8_t l1_o[20*20];
	uint8_t l1_vo[20][28*20];
	uint8_t l1_vv[TERMS_QUAD_POLY(28)*20];

	uint8_t l2_o[20*20];
	uint8_t l2_vo[20][48*20];
	uint8_t l2_vv[TERMS_QUAD_POLY(48)*20+32];
};

typedef struct _rainbow_ckey rainbow_ckey;

struct _rainbow_key {
	uint8_t mat_t[_PUB_M * _PUB_M_BYTE];
	uint8_t vec_t[_PUB_M_BYTE];
	uint8_t mat_s[_SEC_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];

	rainbow_ckey ckey;
};

typedef struct _rainbow_key rainbow_key;


//static inline
static
unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );
//{ memcpy( r , a , _PUB_N_BYTE ); }


//static inline
static
void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );
//{ memcpy( r , a + 28 , 40 ); }





static inline
void rainbow_pubmap_seckey( uint8_t * z , const rainbow_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tt2[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	gf256mat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	rainbow_central_map( tt2 , & sk->ckey , tt );

	gf256mat_prod( z , sk->mat_t , _PUB_M_BYTE , _PUB_M , tt2 );
	gf256v_add( z , sk->vec_t , _PUB_M_BYTE );

}


//#ifdef _DEBUG_
static inline
void rainbow_genkey_debug( rainbow_key * pk , rainbow_key * sk )
{
	gf256v_rand( (uint8_t *)&sk->ckey , sizeof(rainbow_ckey) );
	memcpy( (uint8_t *)&pk->ckey , (uint8_t *)&sk->ckey , sizeof(rainbow_ckey) );

	gf256mat_rand_inv( pk->mat_t , sk->mat_t , _PUB_M );
	gf256mat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf256v_rand( pk->vec_s , _SEC_N );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _PUB_M_BYTE );

	uint8_t inp[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	rainbow_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _PUB_M_BYTE );

}
//#endif


#include "mpkc.h"

static inline
void rainbow_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	rainbow_pubmap_seckey( (uint8_t *)z , (const rainbow_key *)pk_key, (const uint8_t *)w );
}

static inline
void rainbow_genkey( uint8_t * pk , rainbow_key * sk )
{

	rainbow_key _pk;
	rainbow_genkey_debug( &_pk , sk );

	mpkc_interpolate_gf256( pk , rainbow_pubmap_wrapper , (const void*) &_pk );
}



#if 1

#include "mq_gf256.h"
#if defined(_BLAS_AVX2_)
#define rainbow_pubmap mq_gf256_n68_m40_avx2
#elif defined(_BLAS_SSE_)
#define rainbow_pubmap mq_gf256_n68_m40_ssse3
//#define rainbow_pubmap mq_gf256_n68_m40_ref
#else
#define rainbow_pubmap mq_gf256_n68_m40_ref
#endif

#else

#define rainbow_pubmap mpkc_pub_map_gf256

#endif



#define _LEN_SHA256_ 32

static inline
void rainbow_secmap( uint8_t * w , const rainbow_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
	//memcpy( sha256_digest , seed , _LEN_SHA256_ );
	RAND_seed( seed , _LEN_SHA256_ );

	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return; }


	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t y[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(32)));

	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	memset( y , 0 , _PUB_M_BYTE );
	gf256mat_prod(y,sk->mat_t,_PUB_M_BYTE,_PUB_M,_z);

	unsigned succ = 0;
	unsigned time = 0;
	while( !succ ) {
		if( 256 == time ) break;

		RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest );
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
		memcpy( x , sha256_digest , _PUB_N_BYTE - _PUB_M_BYTE );

		succ = rainbow_ivs_central_map( x , & sk->ckey , y );
		time ++;
	};

	gf256v_add(x,sk->vec_s,_PUB_N_BYTE);
	memset(w,0,_PUB_N_BYTE);
	gf256mat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//	return time;
	return;
}





/////////////////////////////


static inline
void transpose_20x20( uint8_t * r , const uint8_t * a )
{
	for(unsigned i=0;i<20;i++) {
		for(unsigned j=0;j<20;j++) {
			r[i*20+j] = a[j*20+i];
		}
	}
}

static inline
void gen_l1_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	for(unsigned i=0;i<20;i++) {
		gf256mat_prod( mat + i*20 , k->l1_vo[i] , 20 , 28 , v );
		gf256v_add( mat + i*20 , k->l1_o + i*20 , 20 );
	}
}

static inline
void gen_l2_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	for(unsigned i=0;i<20;i++) {
		gf256mat_prod( mat + i*20 , k->l2_vo[i] , 20 , 48 , v );
		gf256v_add( mat + i*20 , k->l2_o + i*20 , 20 );
	}
}


static inline
void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r , a+28 , 40 );
return;
#endif
	uint8_t mat1[20*20] __attribute__((aligned(32)));
	uint8_t mat2[20*20] __attribute__((aligned(32)));
	uint8_t temp[20] __attribute__((aligned(32)));

	gen_l1_mat( mat1 , k , a );
	transpose_20x20( mat2 , mat1 );
	gf256mat_prod( r , mat2 , 20 , 20 , a+28 );
	//memset(temp,0,20);
	mpkc_pub_map_gf256_n_m( temp , k->l1_vv , a , 28 , 20 );
	gf256v_add( r , temp , 20 );

	gen_l2_mat( mat1 , k , a );
	transpose_20x20( mat2 , mat1 );
	gf256mat_prod( r+20 , mat2 , 20 , 20 , a+48 );
	mpkc_pub_map_gf256_n_m( temp , k->l2_vv , a , 48 , 20 );
	gf256v_add( r+20 , temp , 20 );

}


#ifdef _BENCHMARK_LINEARSOLVER
#include "benchmark.h"
extern struct benchmark bmm;
#endif



#ifdef _BLAS_AVX2_


static inline
void mq_gf256_multab_n_m_avx2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * multab , unsigned n, unsigned m )
{
	assert(m <= 32);
	__m256i tmp;
	__m256i r = _mm256_setzero_si256();

	__m256i mask_f = _mm256_load_si256((__m256i const *) __mask_low);

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n;i++) {
		__m256i mt = _mm256_load_si256( (__m256i*)( multab + i*32) );
		__m256i ml = _mm256_permute2x128_si256(mt,mt,0x00 );
		__m256i mh = _mm256_permute2x128_si256(mt,mt,0x11 );

		__m256i inp = _mm256_loadu_si256( (__m256i*)(linear_mat) );
		r ^= _mm256_shuffle_epi8( ml , inp&mask_f );
		r ^= _mm256_shuffle_epi8( mh , _mm256_srli_epi16(inp,4)&mask_f );
		linear_mat += m;
	}
	const uint8_t * quad_mat = pk_mat + n*m;
	for(unsigned i=0;i<n;i++) {
		tmp = _mm256_setzero_si256();
		__m256i ml,mh;
		for(unsigned j=0;j<=i;j++) {
			__m256i mt = _mm256_load_si256( (__m256i*)( multab + j*32) );
			ml = _mm256_permute2x128_si256(mt,mt,0x00 );
			mh = _mm256_permute2x128_si256(mt,mt,0x11 );

			__m256i inp = _mm256_loadu_si256( (__m256i*)(quad_mat) );
			tmp ^= _mm256_shuffle_epi8( ml , inp&mask_f );
			tmp ^= _mm256_shuffle_epi8( mh , _mm256_srli_epi16(inp,4)&mask_f );
			quad_mat += m;
		}
		r ^= _mm256_shuffle_epi8( ml , tmp&mask_f );
		r ^= _mm256_shuffle_epi8( mh , _mm256_srli_epi16(tmp,4)&mask_f );
	}

	uint8_t temp[32] __attribute__((aligned(32)));
	_mm256_store_si256( (__m256i*) temp , r );
	for(unsigned i=0;i<m;i++) z[i]=temp[i];
}

static inline
void gen_l1_mat_avx2( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab  ) {
	for(unsigned i=0;i<20;i++) {
		gf256mat_prod_multab_avx2( mat + i*20 , k->l1_vo[i] , 20 , 28 , multab );
		//gf256mat_prod( mat + i*20 , k->l1_vo[i] , 20 , 28 , v );
		gf256v_add( mat + i*20 , k->l1_o + i*20 , 20 );
	}
}

static inline
void gen_l2_mat_avx2( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab  ) {
	for(unsigned i=0;i<20;i++) {
		gf256mat_prod_multab_avx2( mat + i*20 , k->l2_vo[i] , 20 , 48 , multab );
		//gf256mat_prod( mat + i*20 , k->l2_vo[i] , 20 , 48 , v );
		gf256v_add( mat + i*20 , k->l2_o + i*20 , 20 );
	}
}

#include "gf16_sse.h"

static inline
unsigned linear_solver_20x20_avx2( uint8_t * r , const uint8_t * mat_20x20 , const uint8_t * cc )
{
#ifdef _BENCHMARK_LINEARSOLVER
bm_start(&bmm);
#endif
	uint8_t mat[20*32] __attribute__((aligned(32)));
	for(unsigned i=0;i<20;i++) {
		memcpy( mat+i*32 , mat_20x20+i*20 , 20 );
		*(mat + i*32 + 20 ) = cc[i];
	}

	//uint8_t * ptr_rows[20];
	//for(unsigned i=0;i<20;i++) ptr_rows[i] = mat + i*32;

	//__m256i mask_f = _mm256_load_si256((__m256i const *) __mask_low);
	__m256i mask_0 = _mm256_setzero_si256();

	//uint8_t multab[64*16] __attribute__((aligned(32)));
	uint8_t temp[32] __attribute__((aligned(32)));

	uint8_t rr8 = 1;
	for(unsigned i=0;i<20;i++) {
		__m256i rowi = _mm256_load_si256( (__m256i*)(mat+i*32) );
#define _CONSTTIME_
#ifdef _CONSTTIME_
		_mm256_store_si256( (__m256i*)temp , _mm256_cmpeq_epi8(rowi,mask_0) );
		temp[0] = temp[i];
		__m256i predicate_zero = _mm256_broadcastb_epi8( _mm_load_si128((__m128i*)temp) );

		for(unsigned j=i+1;j<20;j++) {
			__m256i rowj = _mm256_load_si256( (__m256i*)(mat+j*32) );
			rowi ^= predicate_zero&rowj;
			//rowi ^= predicate_zero&(*(__m256i*)(mat+j*32));
		}
		_mm256_store_si256( (__m256i*)(mat+i*32) , rowi );
		uint16_t sign_i = mat[i*32+i];
		sign_i = (0-sign_i)>>8;
		rr8 &= sign_i;
#else
		uint8_t pivot = mat[i*32+i];
		if( 0 == pivot ) {
			for(unsigned j=i+1;j<20;j++) {
				if( 0 == mat[32*j+i] ) continue;
				pivot = mat[32*j+i];
				rowi ^= *(__m256i*)(mat+j*32);
				break;
			}
		}
		if( 0 == pivot ) {rr8=0; break; }
		_mm256_store_si256( (__m256i*)(mat+i*32) , rowi );
#endif
		temp[0] = mat[i*32+i];
		__m128i _pivot = _mm_load_si128( (__m128i*)temp );
		__m128i _ip = tbl_gf256_inv( _pivot );
		__m256i ip_br = _mm256_broadcastb_epi8( _ip );

		rowi = _mm256_load_si256( (__m256i*)(mat+i*32) );
		rowi = tbl32_gf256_mul( rowi , ip_br );
		_mm256_store_si256( (__m256i*)(mat+i*32) , rowi );

		for(unsigned j=0;j<20;j++) temp[j] = mat[j*32+i];
		for(unsigned j=0;j<20;j++) {
			if(i==j) continue;
			__m256i rowj = _mm256_load_si256( (__m256i*)(mat+j*32) );
#ifdef _CONSTTIME_
			temp[0] = temp[j];
			__m256i mm = _mm256_broadcastb_epi8( _mm_load_si128((__m128i*)temp) );
			rowj ^= tbl32_gf256_mul( rowi , mm );
#else
			rowj ^= tbl32_gf256_mul_const( temp[j] , rowi );
#endif
			_mm256_store_si256( (__m256i*)(mat+j*32) , rowj );
		}
	}
	for(unsigned i=0;i<20;i++) {
		r[i] = mat[i*32+20];
	}

#ifdef _BENCHMARK_LINEARSOLVER
bm_stop(&bmm);
#endif
	return rr8;
}


static inline
unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r+28 , a , 40 );
return 1;
#endif
	uint8_t mat1[20*20] __attribute__((aligned(32)));
	uint8_t temp[20] __attribute__((aligned(32)));

	uint8_t multab[128*16] __attribute__((aligned(32)));
	gf256v_generate_multab_sse( multab , r , 28 );
	mq_gf256_multab_n_m_avx2( temp , k->l1_vv , multab , 28 , 20 );
	//mpkc_pub_map_gf256_n_m( temp , k->l1_vv , r , 28 , 20 );

	gf256v_add( temp  , a , 20 );
	gen_l1_mat_avx2( mat1 , k , multab );
	//gen_l1_mat( mat1 , k , r );
	unsigned r1 = linear_solver_20x20_avx2( r+28 , mat1 , temp );

	gf256v_generate_multab_sse( multab + 28*32 , r+28 , 20 );
	mq_gf256_multab_n_m_avx2( temp , k->l2_vv , multab , 48 , 20 );
	//mpkc_pub_map_gf256_n_m( temp , k->l2_vv , r , 48 , 20 );
	gf256v_add( temp  , a+20 , 20 );
	gen_l2_mat_avx2( mat1 , k , multab );
	//gen_l2_mat( mat1 , k , r );
	unsigned r2 = linear_solver_20x20_avx2( r+48 , mat1 , temp );

	return r1&r2;
}




#else


static inline
unsigned linear_solver_20x20( uint8_t * r , const uint8_t * mat_20x20 , const uint8_t * cc )
{
#ifdef _BENCHMARK_LINEARSOLVER
bm_start(&bmm);
#endif
	uint8_t mat[20*32] __attribute__((aligned(32)));
	for(unsigned i=0;i<20;i++) {
		memcpy( mat+i*32 , mat_20x20+i*20 , 20 );
		mat[i*32 + 20] = cc[i];
	}

	unsigned r8 = 1;
	for(unsigned i=0;i<20;i++) {
		uint8_t pivot = mat[ i*32 + i];

		if( 0 == pivot ) {
			for(unsigned j=i+1;j<20;j++) {
				if( 0 == mat[j*32+i] ) continue;
				pivot = mat[j*32+i];
				gf256v_add( mat + i*32 , mat + j*32 , 21 );
				gf256v_add( mat + j*32 , mat + i*32 , 21 );
				gf256v_add( mat + i*32 , mat + j*32 , 21 );
				break;
			}
		}
		if( 0 == pivot ) { r8=0; break; }
		uint8_t m = gf256_inv( pivot );
		gf256v_mul_scalar( mat + i*32 , m , 21 );
		for(unsigned j= 0 ;j<20;j++) {
			if(i==j) continue;
			gf256v_madd( mat+j*32 , mat+i*32 , mat[j*32+i] , 21 );
		}
	}
	for(unsigned i=0;i<20;i++) {
		r[i] = mat[ i*32 + 20];
	}
#ifdef _BENCHMARK_LINEARSOLVER
bm_stop(&bmm);
#endif
	return r8;
}


static inline
unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r+28 , a , 40 );
return 1;
#endif
	uint8_t mat1[20*20] __attribute__((aligned(32)));
	uint8_t temp[32] __attribute__((aligned(32)));
	mpkc_pub_map_gf256_n_m( temp , k->l1_vv , r , 28 , 20 );
	gf256v_add( temp  , a , 20 );
	gen_l1_mat( mat1 , k , r );
	unsigned r1 = linear_solver_20x20( r+28 , mat1 , temp );

	gen_l2_mat( mat1 , k , r );
	mpkc_pub_map_gf256_n_m( temp , k->l2_vv , r , 48 , 20 );
	gf256v_add( temp  , a+20 , 20 );
	unsigned r2 = linear_solver_20x20( r+48 , mat1 , temp );

	return r1&r2;
}


#endif


#ifdef  __cplusplus
}
#endif


#endif
