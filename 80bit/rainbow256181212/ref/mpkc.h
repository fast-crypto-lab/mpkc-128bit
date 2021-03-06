
#ifndef _MPKC_H_
#define _MPKC_H_



#include "blas.h"

#include "string.h"

#include "rainbow_config.h"



#ifdef  __cplusplus
extern  "C" {
#endif



#define IDX_XSQ(i,n_var) (((2*(n_var)+1-i)*(i)/2)+n_var)

/// xi <= xj
#define IDX_QTERMS_REVLEX(xi,xj) ((xj)*(xj+1)/2 + (xi))



static inline
void mpkc_pub_map_gf256( uint8_t * z , const uint8_t * pk_mat , const uint8_t * w )
{
	uint8_t r[_PUB_M_BYTE] __attribute__((aligned(32))) = {0};
	uint8_t tmp[_PUB_M_BYTE] __attribute__((aligned(32)));
	const unsigned n_var = _PUB_N;

	const uint8_t * linear_mat = pk_mat;
	for(unsigned i=0;i<n_var;i++) {
		gf256v_madd( r , linear_mat , w[i] , _PUB_M_BYTE );
		linear_mat += _PUB_M_BYTE;
	}

	const uint8_t * quad_mat = pk_mat + (_PUB_M_BYTE)*(_PUB_N);
	for(unsigned i=0;i<n_var;i++) {
		memset( tmp , 0 , _PUB_M_BYTE );
		for(unsigned j=0;j<=i;j++) {
			gf256v_madd( tmp , quad_mat , w[j] , _PUB_M_BYTE );
			quad_mat += _PUB_M_BYTE;
		}
		gf256v_madd( r , tmp , w[i] , _PUB_M_BYTE );
	}
	gf256v_add( r , quad_mat , _PUB_M_BYTE );
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
	gf256v_add( r , quad_mat , m );
}



static inline
void mpkc_interpolate_gf256( uint8_t * poly , void (*quad_poly)(void *,const void *,const void *) , const void * key )
{
	uint8_t tmp[_PUB_N_BYTE] = {0};
	uint8_t tmp_r0[_PUB_M_BYTE] = {0};
	uint8_t tmp_r1[_PUB_M_BYTE] = {0};
	uint8_t tmp_r2[_PUB_M_BYTE] = {0};
	const unsigned n_var = _PUB_N;

	uint8_t * const_terms = poly + (TERMS_QUAD_POLY(_PUB_N)-1)*(_PUB_M_BYTE);
	gf256v_set_zero(tmp,_PUB_N_BYTE);
	quad_poly( const_terms , key , tmp );

	for(unsigned i=0;i<n_var;i++) {
		gf256v_set_zero(tmp,_PUB_N_BYTE);
		tmp[i] = 1;
		quad_poly( tmp_r0 , key , tmp ); /// v + v^2
		gf256v_add( tmp_r0 , const_terms , _PUB_M_BYTE );

		memcpy( tmp_r2 , tmp_r0 , _PUB_M_BYTE );
		gf256v_mul_scalar( tmp_r0 , gf16_mul(2,2) , _PUB_M_BYTE ); /// 3v + 3v^2
		tmp[i] = 2;
		quad_poly( tmp_r1 , key , tmp ); /// 2v + 3v^2
		gf256v_add(tmp_r1 , const_terms , _PUB_M_BYTE );

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
			gf256v_add( tmp_r0 , const_terms , _PUB_M_BYTE );

			gf256v_add( tmp_r0 , tmp_r1 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , tmp_r2 , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*j , _PUB_M_BYTE );
			gf256v_add( tmp_r0 , poly+_PUB_M_BYTE*(n_var+IDX_QTERMS_REVLEX(j,j)) , _PUB_M_BYTE );

			memcpy( poly + _PUB_M_BYTE*(base_idx+j), tmp_r0 , _PUB_M_BYTE );
		}
	}
}





#ifdef  __cplusplus
}
#endif


#endif
