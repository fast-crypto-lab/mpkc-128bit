
#include "rainbow_config.h"

#include "rainbow_16.h"

#include "blas.h"

#include "string.h"

#include "assert.h"


//#define _DEBUG_MPKC_

//#define _BENCHMARK_LINEARSOLVER


#ifdef _RAINBOW_16



void rainbow_pubmap_seckey( uint8_t * z , const rainbow_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tt2[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	gf16mat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	rainbow_central_map( tt2 , & sk->ckey , tt );

	gf16mat_prod( z , sk->mat_t , _PUB_M_BYTE , _PUB_M , tt2 );
	gf256v_add( z , sk->vec_t , _PUB_M_BYTE );

}


void rainbow_genkey_debug( rainbow_key * pk , rainbow_key * sk )
{
	gf256v_rand( (uint8_t *)&sk->ckey , sizeof(rainbow_ckey) );
	memcpy( (uint8_t *)&pk->ckey , (uint8_t *)&sk->ckey , sizeof(rainbow_ckey) );

	gf16mat_rand_inv( pk->mat_t , sk->mat_t , _PUB_M );
	gf16mat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf256v_rand( pk->vec_s , _PUB_N_BYTE );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _PUB_M_BYTE );

	uint8_t inp[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	rainbow_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _PUB_M_BYTE );

}



static inline
void rainbow_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	rainbow_pubmap_seckey( (uint8_t *)z , (const rainbow_key *)pk_key, (const uint8_t *)w );
}


void rainbow_genkey( uint8_t * pk , rainbow_key * sk )
{

	rainbow_key _pk;
	rainbow_genkey_debug( &_pk , sk );

	mpkc_interpolate( pk , rainbow_pubmap_wrapper , (const void*) &_pk );
}


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
	gf16mat_prod(y,sk->mat_t,_PUB_M_BYTE,_PUB_M,_z);

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
	gf16mat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//	return time;
	return;
}





/////////////////////////////


static inline
void transpose_32x32( uint8_t * r , const uint8_t * a )
{
	for(unsigned i=0;i<32;i++) {
		for(unsigned j=0;j<32;j++) {
			gf16v_set_ele( r+i*16 , j , gf16v_get_ele( a+j*16 , i ) );
			//r[i*20+j] = a[j*20+i];
		}
	}
}

static inline
void gen_l1_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	for(unsigned i=0;i<32;i++) {
		gf16mat_prod( mat + i*16 , k->l1_vo[i] , 16 , 32 , v );
		gf256v_add( mat + i*16 , k->l1_o + i*16 , 16 );
	}
}

static inline
void gen_l2_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	for(unsigned i=0;i<32;i++) {
		gf16mat_prod( mat + i*16 , k->l2_vo[i] , 16 , 64 , v );
		gf256v_add( mat + i*16 , k->l2_o + i*16 , 16 );
	}
}



static inline
void mpkc_pub_map_gf16_n_m( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w , unsigned n, unsigned m_byte )
{
	assert( n <= 64 );
	assert( m_byte <= 128 );
        uint8_t tmp[128] __attribute__((aligned(32)));
        uint8_t *r = z;
        memset(r,0,m_byte);

	gf16mat_prod( r , pk_mat , m_byte , n , w );
	pk_mat += n*m_byte;

        uint8_t _x[128] __attribute__((aligned(32)));
	gf16v_split( _x , w , n );

        for(unsigned i=0;i<n;i++) {
                memset( tmp , 0 , m_byte );
                for(unsigned j=0;j<=i;j++) {
                        gf16v_madd( tmp , pk_mat , _x[j] , m_byte );
                        pk_mat += m_byte;
                }
                gf16v_madd( r , tmp , _x[i] , m_byte );
        }
}



void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r , a+16 , 32 );
return;
#endif
	uint8_t mat1[32*16] __attribute__((aligned(32)));
	uint8_t temp[16] __attribute__((aligned(32)));

	gen_l1_mat( mat1 , k , a );

#if defined(_BLAS_AVX2_) || defined(_BLAS_SSE_)
#define _USE_GF16_DOT_
#endif
#ifdef _USE_GF16_DOT_
	for(unsigned i=0;i<32;i++) {
		uint8_t qq = gf16v_dot( mat1 + i*16 , a+16 , 32 );
		gf16v_set_ele( r , i , qq );
	}
#else
	uint8_t mat2[32*16] __attribute__((aligned(32)));
	transpose_32x32( mat2 , mat1 );
	gf16mat_prod( r , mat2 , 16 , 32 , a+16 );
#endif
	mpkc_pub_map_gf16_n_m( temp , k->l1_vv , a , 32 , 16 );
	gf256v_add( r , temp , 16 );

	gen_l2_mat( mat1 , k , a );

#ifdef _USE_GF16_DOT_
	for(unsigned i=0;i<32;i++) {
		uint8_t qq = gf16v_dot( mat1 + i*16 , a+32 , 32 );
		gf16v_set_ele( r+16 , i , qq );
	}
#else
	transpose_32x32( mat2 , mat1 );
	gf16mat_prod( r+16 , mat2 , 16 , 32 , a+32 );
#endif
	mpkc_pub_map_gf16_n_m( temp , k->l2_vv , a , 64 , 16 );
	gf256v_add( r+16 , temp , 16 );

}



#ifdef _BLAS_AVX2_

static inline
void mq_gf16_multab_n_16byte_sse( uint8_t * z , const uint8_t * pk_mat , const uint8_t * multab , unsigned n )
{
	__m128i mask_f = _mm_set1_epi8(0xf);

	__m128i r0 = _mm_setzero_si128();
	__m128i r1 = _mm_setzero_si128();

	for(unsigned i=0;i<n;i++) {
		__m128i mt = _mm_load_si128( (__m128i*)( multab + i*16 ) );

		__m128i inp = _mm_loadu_si128( (__m128i*)( pk_mat ) ); pk_mat += 16;
		r0 ^= _mm_shuffle_epi8( mt , inp&mask_f );
		r1 ^= _mm_shuffle_epi8( mt , _mm_srli_epi16(inp,4)&mask_f );
	}
	for(unsigned i=0;i<n;i++) {
		__m128i temp0 = _mm_setzero_si128();
		__m128i temp1 = _mm_setzero_si128();
		__m128i mt;
		for(unsigned j=0;j<=i;j++) {
			mt = _mm_load_si128( (__m128i*)( multab + j*16 ) );

			__m128i inp = _mm_loadu_si128( (__m128i*)( pk_mat ) ); pk_mat += 16;
			temp0 ^= _mm_shuffle_epi8( mt , inp&mask_f );
			temp1 ^= _mm_shuffle_epi8( mt , _mm_srli_epi16(inp,4)&mask_f );
		}
		r0 ^= _mm_shuffle_epi8( mt , temp0 );
		r1 ^= _mm_shuffle_epi8( mt , temp1 );
	}

	uint8_t temp[16] __attribute__((aligned(32)));
	_mm_store_si128( (__m128i*) temp , r0^_mm_slli_epi16(r1,4) );
	for(unsigned i=0;i<16;i++) z[i]=temp[i];
}


static inline
void gen_l1_mat_avx2( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab  ) {
	for(unsigned i=0;i<32;i++) {
		gf16mat_prod_multab_sse( mat + i*16 , k->l1_vo[i] , 16 , 32 , multab );
		gf256v_add_sse( mat + i*16 , k->l1_o + i*16 , 16 );
	}
}

static inline
void gen_l2_mat_avx2( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab  ) {
	for(unsigned i=0;i<32;i++) {
		gf16mat_prod_multab_sse( mat + i*16 , k->l2_vo[i] , 16 , 64 , multab );
		gf256v_add_sse( mat + i*16 , k->l2_o + i*16 , 16 );
	}
}


#include "gf16_sse.h"


#ifdef _BENCHMARK_LINEARSOLVER
#include "benchmark.h"
extern struct benchmark bmm;
#endif


static inline
uint8_t if_zero_then_0xf(uint8_t p ) {
	return (p-1)>>4;
}

static inline
unsigned linear_solver_32x32_avx2( uint8_t * r , const uint8_t * mat_32x32 , const uint8_t * cc )
{
#ifdef _BENCHMARK_LINEARSOLVER
bm_start( &bmm );
#endif
	uint8_t mat[32*32] __attribute__((aligned(32)));
	for(unsigned i=0;i<32;i++) gf16v_split_sse( mat + i*32 , mat_32x32 + i*16 , 32 );

	__m256i mask_f = _mm256_load_si256((__m256i const *) __mask_low);

	uint8_t temp[32] __attribute__((aligned(32)));
	uint8_t pivots[32] __attribute__((aligned(32)));

	uint8_t rr8 = 1;
	for(unsigned i=0;i<32;i++) {
		for(unsigned j=0;j<32;j++) pivots[j] = mat[j*32+i];
			if( 0 == i ) {
				gf16v_split_sse( temp , cc , 32 );
				for(unsigned j=0;j<32;j++) mat[j*32] = temp[j];
			}
		__m256i rowi = _mm256_load_si256( (__m256i*)(mat+i*32) );
		for(unsigned j=i+1;j<32;j++) {
			temp[0] = if_zero_then_0xf( pivots[i] );
			__m256i mask_zero = _mm256_broadcastb_epi8(_mm_load_si128((__m128i*)temp));

			__m256i rowj = _mm256_load_si256( (__m256i*)(mat+j*32) );
			rowi ^= mask_zero&rowj;
			//rowi ^= predicate_zero&(*(__m256i*)(mat+j*32));
			pivots[i] ^= temp[0]&pivots[j];
		}
		uint8_t is_pi_nz = if_zero_then_0xf(pivots[i]);
		is_pi_nz = ~is_pi_nz;
		rr8 &= is_pi_nz;

		temp[0] = pivots[i];
		__m128i inv_rowi = tbl_gf16_inv( _mm_load_si128((__m128i*)temp) );
		pivots[i] = _mm_extract_epi8( inv_rowi , 0 );

		__m256i log_pivots = tbl32_gf16_log( _mm256_load_si256( (__m256i*)pivots ) );
		_mm256_store_si256( (__m256i*)pivots , log_pivots );

		temp[0] = pivots[i];
		__m256i logpi = _mm256_broadcastb_epi8( _mm_load_si128((__m128i*)temp) );
		rowi = tbl32_gf16_mul_log( rowi , logpi , mask_f );
		__m256i log_rowi = tbl32_gf16_log( rowi );
		for(unsigned j=0;j<32;j++) {
			if(i==j) {
				_mm256_store_si256( (__m256i*)(mat+j*32) , rowi );
				continue;
			}
			__m256i rowj = _mm256_load_si256( (__m256i*)(mat+j*32) );
			temp[0] = pivots[j];
			__m256i logpj = _mm256_broadcastb_epi8( _mm_load_si128((__m128i*)temp) );
			rowj ^= tbl32_gf16_mul_log_log( log_rowi , logpj , mask_f );
			_mm256_store_si256( (__m256i*)(mat+j*32) , rowj );
		}
	}

	for(unsigned i=0;i<32;i++) {
		gf16v_set_ele( r , i , mat[i*32] );
		//r[i] = gf256_mul( mat[i*32+20] , gf256_inv( mat[i*32+i] ) );
	}
#ifdef _BENCHMARK_LINEARSOLVER
bm_stop( &bmm );
#endif
	return rr8;
}



unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r+16 , a , 32 );
return 1;
#endif
	uint8_t mat1[32*16] __attribute__((aligned(32)));
	uint8_t temp[32] __attribute__((aligned(32)));

	uint8_t multab[64*16] __attribute__((aligned(32)));
	gf16v_generate_multab_sse( multab , r , 32 );

	mq_gf16_multab_n_16byte_sse( temp , k->l1_vv , multab , 32 );
	//mpkc_pub_map_gf16_n_m( temp , k->l1_vv , r , 32 , 16 );

	gf256v_add( temp  , a , 16 );
	gen_l1_mat_avx2( mat1 , k , multab );
	//gen_l1_mat( mat1 , k , r );
	unsigned r1 = linear_solver_32x32_avx2( r+16 , mat1 , temp );
	//if( 0 == r1 ) return 0;
	//unsigned r1 = linear_solver_32x32( r+16 , mat1 , temp );

	gf16v_generate_multab_sse( multab + 32*16 , r+16 , 32 );

	mq_gf16_multab_n_16byte_sse( temp , k->l2_vv , multab , 64 );
	//mpkc_pub_map_gf16_n_m( temp , k->l2_vv , r , 64 , 16 );
	gf256v_add( temp  , a+16 , 16 );
	gen_l2_mat_avx2( mat1 , k , multab );
	//gen_l2_mat( mat1 , k , r );
	unsigned r2 = linear_solver_32x32_avx2( r+32 , mat1 , temp );
	//unsigned r2 = linear_solver_32x32( r+32 , mat1 , temp );

	return r1&r2;
}


#else

static inline
unsigned linear_solver_32x32( uint8_t * r , const uint8_t * mat_32x32 , const uint8_t * cc )
{
	uint8_t mat[32*33] __attribute__((aligned(32)));
	for(unsigned i=0;i<32;i++) {
		gf16v_split( mat+i*33 , mat_32x32 + i*16 , 32 );
		mat[i*33+32] = gf16v_get_ele( cc , i );
	}

	for(unsigned i=0;i<32;i++) {
		uint8_t pivot = *(mat + i*33 + i );
		if( 0 == pivot ) {
			for(unsigned j=i+1;j<32;j++) {
				if( 0 == mat[j*33+i] ) continue;
				pivot = mat[j*33+i];
				for(unsigned k=0;k<33;k++) {
					mat[i*33+k] ^= mat[j*33+k];
					mat[j*33+k] ^= mat[i*33+k];
					mat[i*33+k] ^= mat[j*33+k];
				}
				break;
			}
		}
		if( 0 == pivot ) return 0;
		uint8_t m = gf16_inv( pivot );
		gf16v_mul_scalar( mat + i*33 , m , 33 );
		for(unsigned j= 0 ;j<32;j++) {
			if(i==j) continue;
			gf16v_madd( mat+j*33 , mat+i*33 , mat[j*33+i] , 33 );
		}
	}

	for(unsigned i=0;i<32;i++) {
		gf16v_set_ele( r ,  i , *(mat + i*33 + 32) );
	}
	return 1;
}

unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r+16 , a , 32 );
return 1;
#endif
	uint8_t mat1[32*16] __attribute__((aligned(32)));
	uint8_t temp[16] __attribute__((aligned(32)));
	mpkc_pub_map_gf16_n_m( temp , k->l1_vv , r , 32 , 16 );
	gf256v_add( temp  , a , 16 );
	gen_l1_mat( mat1 , k , r );
	unsigned r1 = linear_solver_32x32( r+16 , mat1 , temp );

	gen_l2_mat( mat1 , k , r );
	mpkc_pub_map_gf16_n_m( temp , k->l2_vv , r , 64 , 16 );
	gf256v_add( temp  , a+16 , 16 );
	unsigned r2 = linear_solver_32x32( r+32 , mat1 , temp );

	return r1&r2;
}

#endif



#endif  /// _RAINBOW_16
