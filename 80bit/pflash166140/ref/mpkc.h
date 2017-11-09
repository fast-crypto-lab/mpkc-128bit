
#ifndef _MPKC_H_
#define _MPKC_H_



#include "blas.h"

#include "string.h"

#include "mpkc_config.h"

#ifndef TERMS_QUAD_POLY
#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N)
#endif


#ifndef TERMS_QUAD_POLY_GF2
#define TERMS_QUAD_POLY_GF2(N) (((N)*(N-1)/2)+N)
#endif


#ifdef  __cplusplus
extern  "C" {
#endif



#define IDX_XSQ(i,n_var) (((2*(n_var)+1-i)*(i)/2)+n_var)

/// xi <= xj
#define IDX_QTERMS_REVLEX(xi,xj) ((xj)*(xj+1)/2 + (xi))


void mq_gf16_n64_m64( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );

void mq_gf16_n64_m64_const( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w );


static inline
void mpkc_pub_map_gf16( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[_PUB_M_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tmp[_PUB_M_BYTE] __attribute__((aligned(32)));

	unsigned align_m_byte = ((_PUB_M_BYTE+31)/32)*32;

	const unsigned n_var = _PUB_N;
	uint8_t x[_PUB_N] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<n_var;i++) x[i] = gf16v_get_ele(w,i);

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n_var;i++) {
		gf16v_madd( r , linear_mat , x[i] , align_m_byte );
		linear_mat += _PUB_M_BYTE;
	}

	const uint8_t * quad_mat = pk_mat + (_PUB_M_BYTE)*(_PUB_N);
	for(unsigned i=0;i<n_var;i++) {
		memset( tmp , 0 , _PUB_M_BYTE );
		for(unsigned j=0;j<=i;j++) {
			gf16v_madd( tmp , quad_mat , x[j] , align_m_byte );
			quad_mat += _PUB_M_BYTE;
		}
		gf16v_madd( r , tmp , x[i] , align_m_byte );
	}
	memcpy( z , r , _PUB_M_BYTE );
}

static inline
void mpkc_pub_map_gf256( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[_PUB_M_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tmp[_PUB_M_BYTE] __attribute__((aligned(32)));
	unsigned align_m_byte = ((_PUB_M_BYTE+31)/32)*32;

	const unsigned n_var = _PUB_N;

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n_var;i++) {
		gf256v_madd( r , linear_mat , w[i] , align_m_byte );
		linear_mat += _PUB_M_BYTE;
	}

	const uint8_t * quad_mat = pk_mat + (_PUB_M_BYTE)*(_PUB_N);
	for(unsigned i=0;i<n_var;i++) {
		memset( tmp , 0 , _PUB_M_BYTE );
		for(unsigned j=0;j<=i;j++) {
			gf256v_madd( tmp , quad_mat , w[j] , align_m_byte );
			quad_mat += _PUB_M_BYTE;
		}
		gf256v_madd( r , tmp , w[i] , align_m_byte );
	}
	memcpy( z , r , _PUB_M_BYTE );
}

static inline
void mpkc_pub_map_gf256_n_m( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w , unsigned n, unsigned m)
{
	uint8_t tmp[128] __attribute__((aligned(32)));
	uint8_t *r = z;
	memset(r,0,m);

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n;i++) {
		gf256v_madd( r , linear_mat , w[i] , m );
		linear_mat += m;
	}

	const uint8_t * quad_mat = pk_mat + n*m;
	for(unsigned i=0;i<n;i++) {
		memset( tmp , 0 , m );
		for(unsigned j=0;j<=i;j++) {
			gf256v_madd( tmp , quad_mat , w[j] , m );
			quad_mat += m;
		}
		gf256v_madd( r , tmp , w[i] , m );
	}
}


static inline
void mpkc_interpolate_gf16( uint8_t * poly , void (*quad_poly)(void *,const void *,const void *) , const void * key )
{
	uint8_t tmp[_PUB_N_BYTE] = {0};
	uint8_t tmp_r0[_PUB_M_BYTE] = {0};
	uint8_t tmp_r1[_PUB_M_BYTE] = {0};
	uint8_t tmp_r2[_PUB_M_BYTE] = {0};
	const unsigned n_var = _PUB_N;

	for(unsigned i=0;i<n_var;i++) {
		gf256v_set_zero(tmp,_PUB_N_BYTE);
		gf16v_set_ele(tmp,i,1);
		quad_poly( tmp_r0 , key , tmp ); /// v + v^2
		memcpy( tmp_r2 , tmp_r0 , _PUB_M_BYTE );
		gf16v_mul_scalar( tmp_r0 , gf16_mul(2,2) , _PUB_M_BYTE ); /// 3v + 3v^2
		gf16v_set_ele(tmp,i,2);
		quad_poly( tmp_r1 , key , tmp ); /// 2v + 3v^2
		gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );     /// v
		gf256v_add( tmp_r2 , tmp_r0 , _PUB_M_BYTE);   /// v^2
		memcpy( poly + _PUB_M_BYTE*i , tmp_r0 , _PUB_M_BYTE );
		memcpy( poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , tmp_r2 , _PUB_M_BYTE );
	}

	for(unsigned i=0;i<n_var;i++) {
		unsigned base_idx = n_var+IDX_QTERMS_REVLEX(0,i);
		memcpy( tmp_r1 , poly + _PUB_M_BYTE*i , _PUB_M_BYTE );
		memcpy( tmp_r2 , poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , _PUB_M_BYTE );

		for(unsigned j=0;j<i;j++) {
			gf256v_set_zero(tmp,_PUB_N_BYTE);
			gf16v_set_ele(tmp,i,1);
			gf16v_set_ele(tmp,j,1);

			quad_poly( tmp_r0 , key , tmp ); /// v1 + v1^2 + v2 + v2^2 + v1v2
			gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , tmp_r2 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*j , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(j,j)) , _PUB_M_BYTE );

			memcpy( poly + _PUB_M_BYTE*(base_idx+j), tmp_r0 , _PUB_M_BYTE );
		}
	}
}



static inline
void mpkc_interpolate_gf256( uint8_t * poly , void (*quad_poly)(void *,const void *,const void *) , const void * key )
{
	uint8_t tmp[_PUB_N_BYTE] = {0};
	uint8_t tmp_r0[_PUB_M_BYTE] = {0};
	uint8_t tmp_r1[_PUB_M_BYTE] = {0};
	uint8_t tmp_r2[_PUB_M_BYTE] = {0};
	const unsigned n_var = _PUB_N;

	for(unsigned i=0;i<n_var;i++) {
		gf256v_set_zero(tmp,_PUB_N_BYTE);
		tmp[i] = 1;
		quad_poly( tmp_r0 , key , tmp ); /// v + v^2
		memcpy( tmp_r2 , tmp_r0 , _PUB_M_BYTE );
		gf256v_mul_scalar( tmp_r0 , gf16_mul(2,2) , _PUB_M_BYTE ); /// 3v + 3v^2
		tmp[i] = 2;
		quad_poly( tmp_r1 , key , tmp ); /// 2v + 3v^2
		gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );     /// v
		gf256v_add( tmp_r2 , tmp_r0 , _PUB_M_BYTE);   /// v^2
		memcpy( poly + _PUB_M_BYTE*i , tmp_r0 , _PUB_M_BYTE );
		memcpy( poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , tmp_r2 , _PUB_M_BYTE );
	}

	for(unsigned i=0;i<n_var;i++) {
		unsigned base_idx = n_var+IDX_QTERMS_REVLEX(0,i);
		memcpy( tmp_r1 , poly + _PUB_M_BYTE*i , _PUB_M_BYTE );
		memcpy( tmp_r2 , poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , _PUB_M_BYTE );

		for(unsigned j=0;j<i;j++) {
			gf256v_set_zero(tmp,_PUB_N_BYTE);
			tmp[i] = 1;
			tmp[j] = 1;

			quad_poly( tmp_r0 , key , tmp ); /// v1 + v1^2 + v2 + v2^2 + v1v2
			gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , tmp_r2 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*j , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(j,j)) , _PUB_M_BYTE );

			memcpy( poly + _PUB_M_BYTE*(base_idx+j), tmp_r0 , _PUB_M_BYTE );
		}
	}
}






/////////////////////  GF(4)  ////////////////////////////////////


static inline
void mpkc_pub_map_gf4( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[_PUB_M_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tmp[_PUB_M_BYTE] __attribute__((aligned(32)));
	const unsigned n_var = _PUB_N;
	uint8_t x[_PUB_N] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<n_var;i++) x[i] = gf4v_get_ele(w,i);

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n_var;i++) {
		gf4v_madd( r , linear_mat , x[i] , _PUB_M_BYTE );
		linear_mat += _PUB_M_BYTE;
	}

	const uint8_t * quad_mat = pk_mat + (_PUB_M_BYTE)*(_PUB_N);
	for(unsigned i=0;i<n_var;i++) {
		if( 0 == x[i] ) {
			quad_mat += _PUB_M_BYTE*(i+1);
			continue;
		}
		memset( tmp , 0 , _PUB_M_BYTE );
		for(unsigned j=0;j<=i;j++) {
			gf4v_madd( tmp , quad_mat , x[j] , _PUB_M_BYTE );
			quad_mat += _PUB_M_BYTE;
		}
		gf4v_madd( r , tmp , x[i] , _PUB_M_BYTE );
	}
	memcpy( z , r , _PUB_M_BYTE );
}


static inline
void mpkc_interpolate_gf4( uint8_t * poly , void (*quad_poly)(void *,const void *,const void *) , const void * key )
{
	uint8_t tmp[_PUB_N_BYTE] = {0};
	uint8_t tmp_r0[_PUB_M_BYTE] = {0};
	uint8_t tmp_r1[_PUB_M_BYTE] = {0};
	uint8_t tmp_r2[_PUB_M_BYTE] = {0};
	const unsigned n_var = _PUB_N;

	for(unsigned i=0;i<n_var;i++) {
		gf256v_set_zero(tmp,_PUB_N_BYTE);
		gf4v_set_ele(tmp,i,1);
		quad_poly( tmp_r0 , key , tmp ); /// v + v^2
		memcpy( tmp_r2 , tmp_r0 , _PUB_M_BYTE );
		gf4v_mul_scalar( tmp_r0 , gf4_mul(2,2) , _PUB_M_BYTE ); /// 3v + 3v^2
		gf4v_set_ele(tmp,i,2);
		quad_poly( tmp_r1 , key , tmp ); /// 2v + 3v^2
		gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );     /// v
		gf256v_add( tmp_r2 , tmp_r0 , _PUB_M_BYTE);   /// v^2
		memcpy( poly + _PUB_M_BYTE*i , tmp_r0 , _PUB_M_BYTE );
		memcpy( poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , tmp_r2 , _PUB_M_BYTE );
	}

	for(unsigned i=0;i<n_var;i++) {
		unsigned base_idx = n_var+IDX_QTERMS_REVLEX(0,i);
		memcpy( tmp_r1 , poly + _PUB_M_BYTE*i , _PUB_M_BYTE );
		memcpy( tmp_r2 , poly + _PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(i,i)) , _PUB_M_BYTE );

		for(unsigned j=0;j<i;j++) {
			gf256v_set_zero(tmp,_PUB_N_BYTE);
			gf4v_set_ele(tmp,i,1);
			gf4v_set_ele(tmp,j,1);

			quad_poly( tmp_r0 , key , tmp ); /// v1 + v1^2 + v2 + v2^2 + v1v2
			gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , tmp_r2 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*j , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(j,j)) , _PUB_M_BYTE );

			memcpy( poly + _PUB_M_BYTE*(base_idx+j), tmp_r0 , _PUB_M_BYTE );
		}
	}
}





/////////////////////  GF(2)  ////////////////////////////////////


static inline
void mpkc_pub_map_gf2( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[_PUB_M_BYTE] __attribute__((aligned(32))) = {0};

	const unsigned n_var = _PUB_N;
	uint8_t x[_PUB_N] __attribute__((aligned(32))) = {0};
	for(unsigned i=0;i<n_var;i++) x[i] = gf2v_get_ele(w,i);

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n_var;i++) {
		if( x[i] ) gf256v_add( r , linear_mat , _PUB_M_BYTE );
		linear_mat += _PUB_M_BYTE;
	}

	const uint8_t * quad_mat = pk_mat + (_PUB_M_BYTE)*(_PUB_N);
	for(unsigned i=1;i<n_var;i++) {
		if( 0 == x[i] ) {
			quad_mat += _PUB_M_BYTE*i;
			continue;
		}
		for(unsigned j=0;j<i;j++) {
			if( x[j] ) gf256v_add( r , quad_mat , _PUB_M_BYTE );
			quad_mat += _PUB_M_BYTE;
		}
	}
	memcpy( z , r , _PUB_M_BYTE );
}


static inline
void mpkc_interpolate_gf2( uint8_t * poly , void (*quad_poly)(void *,const void *,const void *) , const void * key )
{
	uint8_t tmp[_PUB_N_BYTE] = {0};
	const unsigned n_var = _PUB_N;

	for(unsigned i=0;i<n_var;i++) {
		gf256v_set_zero(tmp,_PUB_N_BYTE);
		gf2v_set_ele(tmp,i,1);
		quad_poly( poly + (_PUB_M_BYTE * i) , key , tmp ); /// v
	}

	uint8_t * q_poly = poly + _PUB_M_BYTE*n_var;
	for(unsigned i=1;i<n_var;i++) {
		for(unsigned j=0;j<i;j++) {
			gf256v_set_zero(tmp,_PUB_N_BYTE);
			gf2v_set_ele(tmp,i,1);
			gf2v_set_ele(tmp,j,1);
			quad_poly( q_poly  , key , tmp ); /// v1*v2
			gf256v_add( q_poly , poly + (i*_PUB_M_BYTE) , _PUB_M_BYTE );
			gf256v_add( q_poly , poly + (j*_PUB_M_BYTE) , _PUB_M_BYTE );
			q_poly += _PUB_M_BYTE;
		}
	}
}




#ifdef  __cplusplus
}
#endif


#endif
