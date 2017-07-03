
#include "hmfev_config.h"

#include "hmfev.h"

#include "gfext.h"

#include "mpkc.h"

#include "xl_3var.h"

#if _GF_EXT_ != HMFEV_BGF_SIZE
some macro about field size fail.
#endif



#if 256 == _GF
	#define GFmat_prod gf256mat_prod
	#define GFmat_rand_inv gf256mat_rand_inv
	#define GFv_madd gf256v_madd
#else
	#define GFmat_prod gf16_mat_prod
	#define GFmat_rand_inv gf16mat_rand_inv
	#define GFv_madd gf16v_madd
#endif



#ifndef _DEBUG_HMFEV_
static inline
#endif
void hmfev_pubmap_seckey( uint8_t * z , const hmfev_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(16))) = {0};
	GFmat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	uint8_t tt1[_SEC_M_BYTE] __attribute__((aligned(16))) = {0};
	hmfev_central_map( tt1 , sk , tt );

	uint8_t tt2[_SEC_M_BYTE] = {0};
	GFmat_prod( tt2 , sk->mat_t , _SEC_M_BYTE , _SEC_M , tt1 );
	gf256v_add( tt2 , sk->vec_t , _SEC_M_BYTE );

	memcpy( z , tt2 , _SEC_M_BYTE ); /// here. add "minus" for simulation.
}


#ifndef _DEBUG_HMFEV_
static inline
#endif
void hmfev_genkey_debug( hmfev_key * pk , hmfev_key * sk )
{
	GFmat_rand_inv( pk->mat_t , sk->mat_t , _SEC_M );
	GFmat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf256v_rand( pk->vec_s , _SEC_N_BYTE );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _SEC_M_BYTE );

	gf256v_rand( (uint8_t *)&(pk->cpoly) , sizeof(cpoly_t) );
	memcpy( & (sk->cpoly) , & (pk->cpoly) , sizeof(cpoly_t) );

	uint8_t inp[_PUB_N_BYTE] = {0};
	hmfev_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _SEC_M_BYTE );

}



#ifndef _DEBUG_HMFEV_
static inline
#endif
void hmfev_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	uint8_t tt[_SEC_M_BYTE] ={0};
	hmfev_pubmap_seckey( tt , (const hmfev_key *)pk_key, (const uint8_t *)w );
	memcpy( (uint8_t *)z , tt , _PUB_M_BYTE );
}


void hmfev_genkey( uint8_t * pk , hmfev_key * sk )
{
	hmfev_key _pk;
	hmfev_genkey_debug( &_pk , sk );

	hmfev_interpolate( pk , hmfev_pubmap_wrapper , (const void*) &_pk );
}






/////////////////////////////////




unsigned hmfev_secmap( uint8_t * w , const hmfev_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
	//memcpy( sha256_digest , seed , _LEN_SHA256_ );
	RAND_seed( seed , _LEN_SHA256_ );

	//uint8_t is_z_zero = 0;
	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return 1; }

	uint8_t _z[_SEC_M_BYTE] __attribute__((aligned(16)))= {0};
	//uint8_t y[_PUB_N_BYTE] __attribute__((aligned(16)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(16)));
	//uint8_t _w[_PUB_N_BYTE] __attribute__((aligned(16)));

	uint8_t temp_t[_PUB_N_BYTE] __attribute__((aligned(16))) = {0};

	unsigned succ = 0;
	unsigned time = 0;
	do {
		RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
///		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest );
///		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );

		/// minus
		memcpy(_z,z,_PUB_M_BYTE);
		memcpy( _z+_PUB_M_BYTE,sha256_digest,_A_BYTE );

		gf256v_add(_z,sk->vec_t,_SEC_M_BYTE);
		GFmat_prod(temp_t,sk->mat_t,_SEC_M_BYTE,_SEC_M,_z);

		/// vinegar
		memset( x , 0 , _SEC_M_BYTE );
		memcpy( x+_SEC_M_BYTE,sha256_digest + _A_BYTE,_V_BYTE );

		succ = hmfev_ivs_central_map( x , sk , temp_t );

		if( 1 == succ ) break;
		/// check if ivsQ sucess here
//		last_s = gf16v_dot( x , sk->last_row_s , _SEC_N );
		time++;
	} while( time < 256 );
	gf256v_add( x , sk->vec_s , _PUB_N_BYTE );
	memset(w,0,_PUB_N_BYTE);
	GFmat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//printf("w  : "); gf256v_fdump(stdout,w,_PUB_N_BYTE); printf("\n");
//	return time;
	return (time<256)?1:0;
}



static inline
void hmfev_vinegar_eval( uint8_t * poly, const cpoly_t * sk , const uint8_t * _vinegar )
{
//struct hmfev_cpoly {
//	uint8_t vo[_K][_V*_K][BGF_SIZE];
//	uint8_t vv[_K][_V*(_V+1)/2][BGF_SIZE];
//	//  xx , xy , xz , x , yy , yz , y , zz , z , 1
//	uint8_t c_eq[_K][BGF_SIZE*10];
//};
	memcpy(poly,(uint8_t*)(sk->c_eq),_K*BGF_SIZE*C_TERMS);
	//return;
	uint8_t vinegar[_V] __attribute__((aligned(16)));
#if 256 == _GF
	memcpy( vinegar , _vinegar , _V );
#else
	for(unsigned i=0;i<_V;i++) vinegar[i] = gf16v_get_ele( _vinegar , i );
#endif
	uint8_t temp[BGF_SIZE] __attribute__((aligned(16)));
	for( int i=0;i<3;i++) {
		uint8_t * pp = poly + i*C_TERMS*BGF_SIZE;
		const uint8_t * ptr = sk->vo[i][0];
		memset(temp,0,BGF_SIZE);
		for(int j=0;j<_V;j++) {
			GFv_madd( temp , ptr , vinegar[i] , BGF_SIZE);
			ptr += BGF_SIZE;
		}
		BGFMUL_256( pp+BGF_SIZE , pp+BGF_SIZE , temp );
		memset(temp,0,BGF_SIZE);
		for(int j=0;j<_V;j++) {
			GFv_madd( temp , ptr , vinegar[i] , BGF_SIZE);
			ptr += BGF_SIZE;
		}
		BGFMUL_256( pp+BGF_SIZE  , pp+3*BGF_SIZE , temp );
		memset(temp,0,BGF_SIZE);
		for(int j=0;j<_V;j++) {
			GFv_madd( temp , ptr , vinegar[i] , BGF_SIZE);
			ptr += BGF_SIZE;
		}
		BGFMUL_256( pp+BGF_SIZE  , pp+6*BGF_SIZE , temp );
	}
	uint8_t * p0 = poly;
	uint8_t * p1 = poly + C_TERMS*BGF_SIZE;
	uint8_t * p2 = poly + 2*C_TERMS*BGF_SIZE;
	uint8_t vec0[_V] __attribute__((aligned(16)));
	uint8_t vec[_V] __attribute__((aligned(16)));
	unsigned idx = 0;
	for(unsigned i=0;i<_V;i++) {
		memset( vec0 , 0 , _V );
		GFv_madd( vec0 , _vinegar , vinegar[i] , _V_BYTE );
#if 256 == _GF
		memcpy( vec , vec0 , _V );
#else
		for(unsigned j=i;j<_V;j++) vec[j] = gf16v_get_ele( vec0 , j );
#endif

		//memcpy( vec , _vinegar , _V/2 );
		//gf16v_mul_scalar( vec , vinegar[i] , _V/2 );
		for( unsigned j=i;j<_V;j++) {
			GFv_madd( p0 , sk->vv[0][idx] , vec[j] , BGF_SIZE );
			GFv_madd( p1 , sk->vv[1][idx] , vec[j] , BGF_SIZE );
			GFv_madd( p2 , sk->vv[2][idx] , vec[j] , BGF_SIZE );
			idx++;
		}
	}
}


//struct hmfev_cpoly {
//	uint8_t vo[_K][_V*_K][BGF_SIZE];
//	uint8_t vv[_K][_V*(_V+1)/2][BGF_SIZE];
//	//  xx , xy , xz , x , yy , yz , y , zz , z , 1
//	uint8_t c_eq[_K][BGF_SIZE*10];
//};
static inline
void _hmfev_cpoly_eval( uint8_t *val , const uint8_t * poly , const uint8_t * a )
{
	//const uint8_t * a0 = a;
	//const uint8_t * a1 = a+BGF_SIZE;
	//const uint8_t * a2 = a+2*BGF_SIZE;

	const uint8_t * p0 = poly;
	const uint8_t * p1 = poly + C_TERMS*BGF_SIZE;
	const uint8_t * p2 = poly + 2*C_TERMS*BGF_SIZE;

	uint8_t r0[BGF_SIZE] __attribute__((aligned(16))); memcpy( r0 , p0 , BGF_SIZE );
	uint8_t r1[BGF_SIZE] __attribute__((aligned(16))); memcpy( r1 , p1 , BGF_SIZE );
	uint8_t r2[BGF_SIZE] __attribute__((aligned(16))); memcpy( r2 , p2 , BGF_SIZE );

	poly_eval_3var_quad( (bgf_t *)r0 , (bgf_t *)p0 , (bgf_t *)a );
	poly_eval_3var_quad( (bgf_t *)r1 , (bgf_t *)p1 , (bgf_t *)a );
	poly_eval_3var_quad( (bgf_t *)r2 , (bgf_t *)p2 , (bgf_t *)a );

	memcpy( val , r0 , BGF_SIZE );
	memcpy( val + BGF_SIZE , r1 , BGF_SIZE );
	memcpy( val + 2*BGF_SIZE , r2 , BGF_SIZE );
}





#ifndef _DEBUG_HMFEV_
static inline
#endif
void hmfev_central_map( uint8_t * y , const hmfev_key * sk , const uint8_t * x ) {

	const uint8_t *v = x+BGF_SIZE*_K;
	uint8_t poly[BGF_SIZE*C_TERMS*_K] __attribute__((aligned(16)));
	hmfev_vinegar_eval( poly , & sk->cpoly , v );

	uint8_t _y[BGF_SIZE*_K] __attribute__((aligned(16)));
	uint8_t _x[BGF_SIZE*_K] __attribute__((aligned(16)));

	for(unsigned i=0;i<_K;i++) ISO( _x+i*BGF_SIZE , x+i*BGF_SIZE );
	for(unsigned i=0;i<C_TERMS*_K;i++) ISO( poly+i*BGF_SIZE , poly+i*BGF_SIZE );

	_hmfev_cpoly_eval( _y , poly , _x );

	for(unsigned i=0;i<_K;i++) IVSISO( y+i*BGF_SIZE , _y+i*BGF_SIZE );
}



#ifndef _DEBUG_HMFEV_
static inline
#endif
unsigned hmfev_ivs_central_map( uint8_t * x , const hmfev_key * sk , const uint8_t * y ) {
	const uint8_t *v = x+BGF_SIZE*_K;
	uint8_t poly[BGF_SIZE*C_TERMS*_K] __attribute__((aligned(16)));
	hmfev_vinegar_eval( poly , & sk->cpoly , v );
	for(unsigned i=0;i<_K;i++) gf256v_add( poly+i*C_TERMS*BGF_SIZE , y+i*BGF_SIZE , BGF_SIZE );
	for(unsigned i=0;i<C_TERMS*_K;i++) ISO( poly+i*BGF_SIZE , poly+i*BGF_SIZE );

	uint8_t * p0 = poly;
	uint8_t * p1 = poly+BGF_SIZE*C_TERMS;
	uint8_t * p2 = poly+BGF_SIZE*2*C_TERMS;

	uint8_t xyz[BGF_SIZE*3] __attribute__((aligned(16)));
	uint8_t *_x0 = xyz;
	uint8_t *_x1 = xyz+BGF_SIZE;
	uint8_t *_x2 = xyz+2*BGF_SIZE;

	unsigned ret = 1;

	uint8_t pz8[BGF_SIZE*10] __attribute__((aligned(16))) = {0};
	uint8_t pyz3[BGF_SIZE*6] __attribute__((aligned(16))) = {0};
	uint8_t pz4[BGF_SIZE*6] __attribute__((aligned(16))) = {0};
	uint8_t px[BGF_SIZE*12] __attribute__((aligned(16))) = {0};
	calc_univar( (bgf_t*)pz8 , (bgf_t*)pyz3 , (bgf_t*)pz4 , (bgf_t*)px , (bgf_t*)p0 , (bgf_t*)p1 , (bgf_t*)p2 );
	ret = find_unique_root( _x0 , pz8 );
	if( 1 == ret ) {
		poly_eval( _x1 , pz8 , 8 , _x0 );
		if( 1!=gf256v_is_zero(_x1,BGF_SIZE) ) return 0;
	} else return ret;

	poly_eval( _x1 , pyz3 , 3 , _x0 );
	poly_eval( pz8 , pz4 , 4 , _x0 );
	BGFINV( _x1 , _x1 );
	BGFMUL( _x1 , pz8 , _x1 );

	poly_eval_except_x( (bgf_t*)_x2 , (bgf_t *)px , (bgf_t *)xyz );
	BGFINV( pz8 , px );
	BGFMUL( _x2 , pz8 , _x2 );

	IVSISO( x , _x0 );
	IVSISO( x+BGF_SIZE , _x1 );
	IVSISO( x+2*BGF_SIZE , _x2 );
	return ret;
}


