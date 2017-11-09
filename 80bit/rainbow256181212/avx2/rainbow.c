
#include "rainbow_config.h"

#include "rainbow.h"

#include "gf16.h"

#include "blas.h"

#include "stdint.h"

#include "stdlib.h"

#include "string.h"

//#define _DEBUG_MPKC_


#ifdef _RAINBOW_256


#ifndef _DEBUG_RAINBOW_
static unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );
static void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a );
#endif



#ifndef _DEBUG_RAINBOW_
static
#endif
void rainbow_pubmap_seckey( uint8_t * z , const rainbow_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tt2[_PUB_N_BYTE] __attribute__((aligned(32))) = {0};

	gf256mat_prod_secure_avx2( tt , sk->mat_t , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_t , _PUB_N_BYTE );

	rainbow_central_map( tt2 , & sk->ckey , tt );

	gf256mat_prod_secure_avx2( z , sk->mat_s , _PUB_M_BYTE , _PUB_M , tt2 );
	gf256v_add( z , sk->vec_s , _PUB_M_BYTE );

}


#ifndef _DEBUG_RAINBOW_
static
#endif
void rainbow_genkey_debug( rainbow_key * pk , rainbow_key * sk )
{
	gf256v_rand( (uint8_t *)&sk->ckey , sizeof(rainbow_ckey) );
	memcpy( (void *)&pk->ckey , (void *)&sk->ckey , sizeof(rainbow_ckey) );

	gf256mat_rand_inv( pk->mat_s , sk->mat_s , _PUB_M );
	gf256mat_rand_inv( pk->mat_t , sk->mat_t , _PUB_N );

	gf256v_rand( pk->vec_t , _PUB_N );
	gf256mat_prod_secure_avx2( sk->vec_t , sk->mat_t , _PUB_N_BYTE , _PUB_N , pk->vec_t );

	gf256v_rand( pk->vec_s , _PUB_M );
	gf256mat_prod_secure_avx2( sk->vec_s , sk->mat_s , _PUB_M_BYTE , _PUB_M , pk->vec_s );

}



#include "mpkc.h"

static inline
void rainbow_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	rainbow_pubmap_seckey( (uint8_t *)z , (const rainbow_key *)pk_key, (const uint8_t *)w );
}


void rainbow_genkey( uint8_t * pk , rainbow_key * sk )
{

	rainbow_key _pk;
	rainbow_genkey_debug( &_pk , sk );

	mpkc_interpolate_gf256( pk , rainbow_pubmap_wrapper , (const void*) &_pk );
}




unsigned rainbow_secmap( uint8_t * w , const rainbow_key * sk , const uint8_t * z )
{
	uint8_t _z[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t y[_PUB_N_BYTE] __attribute__((aligned(32)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(32)));

	memcpy(_z,z,_PUB_M_BYTE);
	gf256mat_prod_secure_avx2(y,sk->mat_s,_PUB_M_BYTE,_PUB_M,_z);
	gf256v_add(y,sk->vec_s,_PUB_M_BYTE);

	unsigned succ = 0;
	unsigned time = 0;
	while( !succ ) {
		if( 256 == time ) break;

		gf256v_rand( x , _V1 );

		succ = rainbow_ivs_central_map( x , & sk->ckey , y );
		time ++;
	};

	gf256mat_prod_secure_avx2(w,sk->mat_t,_PUB_N_BYTE,_PUB_N,x);
	gf256v_add(w,sk->vec_t,_PUB_N_BYTE);

	// return time;
	if( 256 <= time ) return -1;
	return 0;
}





/////////////////////////////


static inline
void transpose_l1( uint8_t * r , const uint8_t * a )
{
	for(unsigned i=0;i<_O1;i++) {
		for(unsigned j=0;j<_O1;j++) {
			r[i*_O1+j] = a[j*_O1+i];
		}
	}
}

static inline
void transpose_l2( uint8_t * r , const uint8_t * a )
{
	for(unsigned i=0;i<_O2;i++) {
		for(unsigned j=0;j<_O2;j++) {
			r[i*_O2+j] = a[j*_O2+i];
		}
	}
}


static inline
void gen_l1_mat_multab( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab ) {
	for(unsigned i=0;i<_O1;i++) {
		gf256mat_prod_multab_avx2( mat + i*_O1 , k->l1_vo[i] , _O1 , _V1 , multab );
		//gf256mat_prod_secure_avx2( mat + i*_O1 , k->l1_vo[i] , _O1 , _V1 , v );
	}
	gf256v_add( mat , k->l1_o, _O1*_O1 );
}

static inline
void gen_l2_mat_multab( uint8_t * mat , const rainbow_ckey * k , const uint8_t * multab ) {
	for(unsigned i=0;i<_O2;i++) {
		gf256mat_prod_multab_avx2( mat + i*_O2 , k->l1_vo[i] , _O2 , _V2 , multab );
		//gf256mat_prod_secure_avx2( mat + i*_O2 , k->l2_vo[i] , _O2 , _V2 , v );
	}
	gf256v_add( mat , k->l2_o , _O2*_O2 );

}



static inline
void gen_l1_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	assert( _V1 < 128 );
	uint8_t multab[128*32] __attribute__((aligned(32)));
	gf256v_generate_multab_sse( multab , v , _V1 );

	gen_l1_mat_multab( mat , k , multab );
}

static inline
void gen_l2_mat( uint8_t * mat , const rainbow_ckey * k , const uint8_t * v ) {
	assert( _V2 < 128 );
	uint8_t multab[128*32] __attribute__((aligned(32)));
	gf256v_generate_multab_sse( multab , v , _V2 );

	gen_l2_mat_multab( mat , k , multab );
}



#ifndef _DEBUG_RAINBOW_
static
#endif
void rainbow_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r , a+_V1 , _PUB_M );
return;
#endif
	/// warning: asming _O2 > _O1
	uint8_t mat1[_O2*_O2] __attribute__((aligned(32)));
	uint8_t mat2[_O2*_O2] __attribute__((aligned(32)));
	uint8_t temp[_O2] __attribute__((aligned(32)));

	gen_l1_mat( mat1 , k , a );
	transpose_l1( mat2 , mat1 );
	gf256mat_prod_secure_avx2( r , mat2 , _O1 , _O1 , a+_V1 );
	//memset(temp,0,20);
	mpkc_pub_map_gf256_n_m( temp , k->l1_vv , a , _V1 , _O1 );
	gf256v_add( r , temp , _O1 );

	gen_l2_mat( mat1 , k , a );
	transpose_l2( mat2 , mat1 );
	gf256mat_prod_secure_avx2( r+_O1 , mat2 , _O2 , _O2 , a+_V2 );
	mpkc_pub_map_gf256_n_m( temp , k->l2_vv , a , _V2 , _O2 );
	gf256v_add( r+_O1 , temp , _O2 );

}


#define _O1_W (_O1+1)
#define _O2_W (_O2+1)


static inline
unsigned linear_solver_l1( uint8_t * r , const uint8_t * mat_inp , const uint8_t * cc )
{
	uint8_t mat[_O1_W*_O1] __attribute__((aligned(32)));
	for(unsigned i=0;i<_O1;i++) {
		memcpy( mat+i*_O1_W , mat_inp+i*_O1 , _O1 );
		mat[i*_O1_W + _O1] = cc[i];
	}

	unsigned rv = gf256mat_gauss_elim( mat , _O1 , _O1_W );
	gf256mat_submat( r , 1 , _O1 , mat , _O1_W , _O1 );
	return rv;
}


static inline
unsigned linear_solver_l2( uint8_t * r , const uint8_t * mat_inp , const uint8_t * cc ) {
	uint8_t mat[_O2_W*_O2] __attribute__((aligned(32)));
	for(unsigned i=0;i<_O2;i++) {
		memcpy( mat+i*_O2_W , mat_inp+i*_O2 , _O2 );
		mat[i*_O2_W + _O2] = cc[i];
	}

	unsigned rv = gf256mat_gauss_elim( mat , _O2 , _O2_W );
	gf256mat_submat( r , 1 , _O2 , mat , _O2_W , _O2 );
	return rv;

}



#ifndef _DEBUG_RAINBOW_
static
#endif
unsigned rainbow_ivs_central_map( uint8_t * r , const rainbow_ckey * k , const uint8_t * a ) {
#ifdef _DEBUG_MPKC_
memcpy( r+_V1 , a , _PUB_M );
return;
#endif
	uint8_t mat1[_O1*_O1] __attribute__((aligned(32)));
	uint8_t mat2[_O2*_O2] __attribute__((aligned(32)));
	uint8_t temp[_O2] __attribute__((aligned(32)));

	uint8_t multab[_V2*32] __attribute__((aligned(32)));
	gf256v_generate_multab_sse( multab , r , _V1 );

	mq_gf256_multab_n_m_avx2( temp , k->l1_vv , multab , _V1 , _O1 );
	gf256v_add( temp  , a , _O1 );
	gen_l1_mat_multab( mat1 , k , multab );
	unsigned r1 = linear_solver_l1( r+_V1 , mat1 , temp );

	gf256v_generate_multab_sse( multab+(_V1*32) , r+_V1 , _O1 );
	gen_l2_mat_multab( mat2 , k , multab );
	mq_gf256_multab_n_m_avx2( temp , k->l2_vv , multab , _V2 , _O2 );
	gf256v_add( temp  , a+_O1 , _O2 );
	unsigned r2 = linear_solver_l2( r+_V2 , mat2 , temp );

	return r1&r2;
}







#endif  /// _RAINBOW_256_
