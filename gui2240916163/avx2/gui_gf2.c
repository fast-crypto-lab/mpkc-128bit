

#include "string.h"
#include "gui_config.h"

#include "blas.h"

#include "gui_gf2.h"



#ifdef _GUI_2_240_D9_V16_A16




#ifndef _DEBUG_GUI_
static inline
#endif
void gui_pubmap_seckey( uint8_t * z , const gui_key * sk , const uint8_t * w ) {

	uint8_t tt[_PUB_N_BYTE] __attribute__((aligned(16))) = {0};
	gf2mat_prod( tt , sk->mat_s , _PUB_N_BYTE , _SEC_N , w );
	gf256v_add( tt , sk->vec_s , _PUB_N_BYTE );

	uint8_t tt1[_SEC_M_BYTE] __attribute__((aligned(16))) = {0};
	gui_central_map( tt1 , sk , tt );

	uint8_t tt2[_SEC_M_BYTE] = {0};
	gf2mat_prod( tt2 , sk->mat_t , _SEC_M_BYTE , _SEC_M , tt1 );
	gf256v_add( tt2 , sk->vec_t , _SEC_M_BYTE );
	memcpy( z , tt2 , _SEC_M_BYTE ); /// here. add "minus" for simulation.
}



#ifndef _DEBUG_GUI_
static inline
#endif
void gui_genkey_debug( gui_key * pk , gui_key * sk )
{
	gf2mat_rand_inv( pk->mat_t , sk->mat_t , _SEC_M );
	gf2mat_rand_inv( pk->mat_s , sk->mat_s , _SEC_N );

	gf256v_rand( pk->vec_s , _PUB_N_BYTE );
	memcpy( sk->vec_s , pk->vec_s , _PUB_N_BYTE );

	gf256v_set_zero( pk->vec_t , _SEC_M_BYTE );

	gf256v_rand( (uint8_t *)&(pk->cpoly) , sizeof(cpoly_t) );
	memcpy( & (sk->cpoly) , & (pk->cpoly) , sizeof(cpoly_t) );

	uint8_t inp[_PUB_N_BYTE] = {0};
	gui_pubmap_seckey(sk->vec_t,pk,inp);
	memcpy( pk->vec_t , sk->vec_t , _SEC_M_BYTE );

}
//#endif


static inline
void gui_pubmap_wrapper( void * z, const void* pk_key, const void * w) {
	uint8_t tt[_SEC_M_BYTE] __attribute__((aligned(16))) ={0};
	gui_pubmap_seckey( tt , (const gui_key *)pk_key, (const uint8_t *)w );
	memcpy( (uint8_t *)z , tt , _PUB_M_BYTE );
}



void gui_genkey( uint8_t * pk , gui_key * sk )
{

	gui_key _pk;
	gui_genkey_debug( &_pk , sk );

	mpkc_interpolate( pk , gui_pubmap_wrapper , (const void*) &_pk );
}


/////////////////////////////



#define _USE_HASH_

#ifdef _USE_HASH_
#include "crypto_hash_sha256.h"
#endif


unsigned gui_secmap( uint8_t * w , const gui_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_])
{
	static uint32_t sha256_digest[_LEN_SHA256_/4];
#ifdef _USE_HASH_
	memcpy( sha256_digest , seed , _LEN_SHA256_ );
#else
	RAND_seed( seed , _LEN_SHA256_ );
#endif

	//uint8_t is_z_zero = 0;
	if( gf256v_is_zero(z,_PUB_M_BYTE) ) { memset(w,0,_PUB_N_BYTE); return 1; }

	uint8_t _z[_SEC_M_BYTE] __attribute__((aligned(16)))= {0};
	//uint8_t y[_PUB_N_BYTE] __attribute__((aligned(16)));
	uint8_t x[_PUB_N_BYTE] __attribute__((aligned(16)));
	//uint8_t _w[_PUB_N_BYTE] __attribute__((aligned(16)));

	uint8_t temp_t[_PUB_N_BYTE] __attribute__((aligned(16))) = {0};
	uint8_t temp_batch_t[(_SEC_M_BYTE)*_BATCH] __attribute__((aligned(16))) = {0};
	uint8_t vinegar[(_VINEGAR_BYTE)*_BATCH] __attribute__((aligned(16))) = {0};

	memcpy(_z,z,_PUB_M_BYTE);
	gf256v_add(_z,sk->vec_t,_PUB_M_BYTE);
	gf2mat_prod(temp_t,sk->mat_t,_SEC_M_BYTE,_PUB_M,_z);

	unsigned succ = 0;
	unsigned time = 0;
	do {
		uint8_t * temp_batch_run = temp_batch_t;
		uint8_t * vinegar_run = vinegar;
		for(unsigned i=0;i<_BATCH;i++) {
#ifdef _USE_HASH_
			crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
///			SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *)sha256_digest );
#else
			RAND_bytes( (unsigned char*) sha256_digest , _LEN_SHA256_ );
#endif
			/// minus
			memcpy( _z ,sha256_digest,_MINUS_BYTE );
			gf256v_add(_z,(sk->vec_t)+_PUB_M_BYTE,_MINUS_BYTE);
			gf2mat_prod(temp_batch_run,(sk->mat_t)+((_PUB_M)*(_SEC_M_BYTE)),_SEC_M_BYTE,_SEC_M-_PUB_M,_z);
			gf256v_add(temp_batch_run,temp_t,_SEC_M_BYTE);
			temp_batch_run += _SEC_M_BYTE;

			/// vinegar
			memcpy( vinegar_run ,sha256_digest + (_SEC_M_BYTE-_PUB_M_BYTE) , _VINEGAR_BYTE );
			vinegar_run += _VINEGAR_BYTE;
		}

		succ = gui_ivs_central_map( x , sk , temp_batch_t , vinegar );
		if( succ < _BATCH ) break;
		/// check if ivsQ sucess here
		time++;
	} while( time < 256 );
	gf256v_add( x , sk->vec_s , _PUB_N_BYTE );
	memset(w,0,_PUB_N_BYTE);
	gf2mat_prod(w,sk->mat_s,_PUB_N_BYTE,_SEC_N,x);
//	return time;
	return (time<256)?1:0;
}



///////////////////////////////////////








#include "gfext.h"



static inline
void gui_vinegar_eval( uint8_t * poly, const cpoly_t * sk , const uint8_t * _vinegar ) {
/// X^9 + X^8 + X^6 + X^5 + X^4 + X^3 + X^2 + X + 1
///struct gui_cpoly {
///	uint8_t vo[4][_V*BGF_SIZE];
///	uint8_t vv[_V*(_V-1)/2][BGF_SIZE];
///	uint8_t c_eq[BGF_SIZE*C_TERMS];
///};

	memcpy(poly,(uint8_t*)(sk->c_eq),BGF_SIZE*C_TERMS);
	//return;
	uint8_t vinegar[_V] __attribute__((aligned(16)));;
	for(unsigned i=0;i<_V;i++) vinegar[i] = gf2v_get_ele( _vinegar , i );
	uint8_t temp[BGF_SIZE] __attribute__((aligned(16)));

#if 1
	const uint8_t * ptr = sk->vo[0];
	memset(temp,0,BGF_SIZE);
	for(int j=0;j<_V;j++) { gf2v_madd_16b( temp , ptr , vinegar[j] , BGF_SIZE ); ptr += BGF_SIZE; }
	/// X
	BGFMUL( poly+BGF_SIZE , poly+BGF_SIZE , temp );

	ptr = sk->vo[1];
	memset(temp,0,BGF_SIZE);
	for(int j=0;j<_V;j++) { gf2v_madd_16b( temp , ptr , vinegar[j] , BGF_SIZE ); ptr += BGF_SIZE; }
	/// X^2
	BGFMUL( poly+BGF_SIZE*2 , poly+BGF_SIZE*2 , temp );

	ptr = sk->vo[2];
	memset(temp,0,BGF_SIZE);
	for(int j=0;j<_V;j++) { gf2v_madd_16b( temp , ptr , vinegar[j] , BGF_SIZE ); ptr += BGF_SIZE; }
	/// X^4
	BGFMUL( poly+BGF_SIZE*4 , poly+BGF_SIZE*4 , temp );

	ptr = sk->vo[3];
	memset(temp,0,BGF_SIZE);
	for(int j=0;j<_V;j++) { gf2v_madd_16b( temp , ptr , vinegar[j] , BGF_SIZE ); ptr += BGF_SIZE; }
	/// X^8
	BGFMUL( poly+BGF_SIZE*7 , poly+BGF_SIZE*7 , temp );
#endif

#if 1
	unsigned idx = 0;
	for(unsigned i=1;i<_V;i++) {
		for(unsigned j=0;j<=i;j++) {
			uint8_t vv = vinegar[i] & vinegar[j];
			gf2v_madd_16b( poly , sk->vv[idx] , vv , BGF_SIZE );
			idx++;

		}
	}
#endif
}


/// X^9 + X^8 + X^6 + X^5 + X^4 + X^3 + X^2 + X + 1
static inline
void _gui_cpoly_eval( uint8_t *val , const uint8_t * poly , const uint8_t * a )
{
	uint8_t a2[BGF_SIZE] __attribute__((aligned(16))); BGFSQU( a2 , a );
	uint8_t a3[BGF_SIZE] __attribute__((aligned(16))); BGFMUL( a3 , a2 , a );
	uint8_t a4[BGF_SIZE] __attribute__((aligned(16))); BGFSQU( a4 , a2 );
	uint8_t a5[BGF_SIZE] __attribute__((aligned(16))); BGFMUL( a5 , a4 , a );
	uint8_t a6[BGF_SIZE] __attribute__((aligned(16))); BGFMUL( a6 , a4 , a2 );
	uint8_t a8[BGF_SIZE] __attribute__((aligned(16))); BGFSQU( a8 , a4 );
	uint8_t a9[BGF_SIZE] __attribute__((aligned(16))); BGFMUL( a9 , a8 , a );

	uint8_t temp[BGF_SIZE] __attribute__((aligned(16)));
	uint8_t r0[BGF_SIZE] __attribute__((aligned(16))); memcpy( r0 , poly , BGF_SIZE );
	BGFMUL( temp , a , poly + 1*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a2 , poly + 2*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a3 , poly + 3*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a4 , poly + 4*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a5 , poly + 5*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a6 , poly + 6*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a8 , poly + 7*BGF_SIZE ); BGFADD( r0 , temp );
	BGFMUL( temp , a9 , poly + 8*BGF_SIZE ); BGFADD( r0 , temp );

	memcpy( val , r0 , BGF_SIZE );
}





#ifndef _DEBUG_GUI_
static inline
#endif
void gui_central_map( uint8_t * y , const gui_key * sk , const uint8_t * x ) {
#ifdef _DEBUG_MPKC_
	memcpy(y,x,_SEC_M_BYTE);
	return;
#endif

	const uint8_t *v = x+BGF_SIZE;
	uint8_t poly[BGF_SIZE*C_TERMS] __attribute__((aligned(16)));
	gui_vinegar_eval( poly , & sk->cpoly , v );

	//uint8_t _x[BGF_SIZE] __attribute__((aligned(16)));
	//uint8_t _y[BGF_SIZE] __attribute__((aligned(16)));
	//memcpy( _x , x , BGF_SIZE );

	_gui_cpoly_eval( y , poly , x );
}



#if 1 == _BATCH
#include "gfext_poly_gf2.h"
#elif 16 == _BATCH
#include "b_gfext_poly_gf2.h"
#else
error
#endif




#ifndef _DEBUG_GUI_
static inline
#endif
unsigned gui_ivs_central_map( uint8_t * x , const gui_key * sk , const uint8_t * y , const uint8_t * vinegar ) {
#ifdef _DEBUG_MPKC_
	memcpy(x,y,_SEC_M_BYTE);
	return 0;
#endif

	//const uint8_t *v = x+BGF_SIZE;
	uint8_t poly[BGF_SIZE*C_TERMS*_BATCH] __attribute__((aligned(16)));
	uint8_t * _poly = poly;
	const uint8_t * _vinegar = vinegar;
	const uint8_t * _y = y;
	for(unsigned i=0;i<_BATCH;i++) {
		gui_vinegar_eval( _poly , & sk->cpoly , _vinegar ); _vinegar += _VINEGAR_BYTE;
		BGFADD( _poly , _y ); _y += BGF_SIZE;
		//for(unsigned i=0;i<C_TERMS;i++) ISO( _poly+i*BGF_SIZE , _poly+i*BGF_SIZE );
		_poly += BGF_SIZE*C_TERMS;
	}

	uint8_t batch_poly[BGF_SIZE*C_TERMS*_BATCH] __attribute__((aligned(16)));
#if 1 == _BATCH
	memcpy(batch_poly,poly, BGF_SIZE*C_TERMS*_BATCH);
#elif 16 == _BATCH
	for(unsigned i=0;i<_BATCH;i++) {
		for(unsigned j=0;j<C_TERMS;j++) {
			tbl_gf256ext_30_sse_insert( batch_poly + _BATCH*BGF_SIZE*j , poly + ( i*(C_TERMS*BGF_SIZE) + j*BGF_SIZE ) , i );
		}
	}
#else
error
#endif

	uint8_t _x[BGF_SIZE*_BATCH] __attribute__((aligned(16)));
	unsigned ret = 0;
	ret = find_unique_root( _x , batch_poly );

	/// search for correct answer
	unsigned idx = _BATCH + 1;
	uint8_t temp[BGF_SIZE] __attribute__((aligned(16)));
	uint8_t temp2[BGF_SIZE] __attribute__((aligned(16)));
	for(unsigned i=0;i<ret;i++) {
#if 1 == _BATCH
		memcpy( temp2 , _x , BGF_SIZE );
#elif 16 == _BATCH
		tbl_gf256ext_30_sse_extract( temp2 , _x ,i );
#else
error
#endif
		_gui_cpoly_eval( temp , poly+ i*BGF_SIZE*C_TERMS , temp2 );

		if( gf256v_is_zero( temp , BGF_SIZE ) ) {
			idx = i;
			break;
		}
	}
	if( idx < _BATCH ) {
		//IVSISO( x , temp2 );
		memcpy( x , temp2 , BGF_SIZE );
		memcpy( x+BGF_SIZE , vinegar+idx*_VINEGAR_BYTE , _VINEGAR_BYTE );
	}
	return idx;
}




#endif  /// _GUI_2_240_D9_V16_A16
