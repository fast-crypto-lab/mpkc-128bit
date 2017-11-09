#ifndef _BLAS_H_
#define _BLAS_H_

#include <stdint.h>
#include <stdio.h>
#include <openssl/rand.h>


#include "gf16.h"

#include "blas_config.h"


#ifdef  __cplusplus
extern  "C" {
#endif


#ifdef _BLAS_AVX2_
#include "blas_avx2.h"

#define gf4v_mul_scalar   gf4v_mul_scalar_sse
#define gf4v_madd         gf4v_madd_sse
#define gf4mat_prod       gf4mat_prod_sse

#define gf16v_mul_scalar  gf16v_mul_scalar_avx2
#define gf16v_madd        gf16v_madd_avx2
#define gf16mat_prod      gf16mat_prod_avx2
#define gf16v_dot         gf16v_dot_sse

#define gf256v_add        gf256v_add_avx2
#define gf256v_mul_scalar  gf256v_mul_scalar_sse
#define gf256v_madd        gf256v_madd_sse
#define gf256v_m0x10_add  gf256v_m0x10_add_sse
#define gf256v_m0x4_add  gf256v_m0x4_add_sse
#define gf256mat_prod      gf256mat_prod_avx2

#elif defined( _BLAS_SSE_ )
#include "blas_sse.h"

#define gf4v_mul_scalar   gf4v_mul_scalar_sse
#define gf4v_madd         gf4v_madd_sse
#define gf4mat_prod       gf4mat_prod_sse

#define gf16v_mul_scalar  gf16v_mul_scalar_sse
#define gf16v_madd        gf16v_madd_sse
#define gf16mat_prod      gf16mat_prod_sse
#define gf16v_dot         gf16v_dot_sse

#define gf256v_add        gf256v_add_sse
#define gf256v_mul_scalar  gf256v_mul_scalar_sse
#define gf256v_madd        gf256v_madd_sse
#define gf256v_m0x10_add  gf256v_m0x10_add_sse
#define gf256v_m0x4_add  gf256v_m0x4_add_sse
#define gf256mat_prod      gf256mat_prod_sse

#else

#define gf4v_mul_scalar   _gf4v_mul_scalar
#define gf4v_madd         _gf4v_madd
#define gf4mat_prod       _gf4mat_prod

#define gf16v_mul_scalar  _gf16v_mul_scalar
#define gf16v_madd        _gf16v_madd
#define gf16mat_prod      _gf16mat_prod
#define gf16v_dot         _gf16v_dot

#define gf256v_add        _gf256v_add
#define gf256v_mul_scalar  _gf256v_mul_scalar
#define gf256v_madd        _gf256v_madd
#define gf256v_m0x10_add  _gf256v_m0x10_add
#define gf256v_m0x4_add  _gf256v_m0x4_add
#define gf256mat_prod      _gf256mat_prod
#endif




extern unsigned char __zero_32[32];


static inline
void gf256v_fdump(FILE * fp, const uint8_t *v, unsigned _num_byte) {
	fprintf(fp,"[%2d][",_num_byte);
	for(unsigned i=0;i<_num_byte;i++) { fprintf(fp,"0x%02x,",v[i]); if(7==(i%8)) fprintf(fp," ");}
	fprintf(fp,"]");
}

//static inline
//void gf16v_fdump(FILE * fp, const uint8_t *v, unsigned _num_byte) { gf256v_fdump(fp,v,_num_byte); }

static inline
void _gf256v_add( uint8_t * accu_b, const uint8_t * a , unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) accu_b[i]^=a[i];
}

//static inline
//void gf16v_add( uint8_t * b, const uint8_t * a , unsigned _num_byte ) { gf256v_add(b,a,_num_byte); }

static inline
void gf256v_set_zero( uint8_t * b, unsigned _num_byte ) { gf256v_add( b , b , _num_byte ); }

//static inline
//void gf16v_set_zero( uint8_t * b, unsigned _num_byte ) { gf256v_set_zero(b,_num_byte); }

static inline
unsigned gf256v_is_zero( const uint8_t * a, unsigned _num_byte ) {
	unsigned char r = 0;
	for(unsigned i=0;i<_num_byte;i++) r |= a[i];
	return (0==r);
}

static inline
void _gf16v_mul_scalar( uint8_t * a, uint8_t gf16_b , unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) a[i] = gf256_mul_gf16( a[i] , gf16_b );
}

static inline
void _gf16v_madd( uint8_t * accu_c, const uint8_t * a , uint8_t gf16_b, unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) accu_c[i] ^= gf256_mul_gf16( a[i] , gf16_b );
}

static inline
void _gf256v_mul_scalar( uint8_t *a, uint8_t b, unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) a[i] = gf256_mul( a[i] , b );
}

static inline
void _gf256v_madd( uint8_t * accu_c, const uint8_t * a , uint8_t gf256_b, unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) accu_c[i] ^= gf256_mul( a[i] , gf256_b );
}

static inline
void _gf256v_m0x10_add( uint8_t * accu_c, const uint8_t * a , unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) accu_c[i] ^= gf256_mul_0x10( a[i] );
}

static inline
void _gf256v_m0x4_add( uint8_t * accu_c, const uint8_t * a , unsigned _num_byte ) {
	for(unsigned i=0;i<_num_byte;i++) accu_c[i] ^= gf256_mul_0x4( a[i] );
}

static inline
unsigned char gf16v_get_ele( const uint8_t * a , unsigned i ) {
	unsigned char r = a[i>>1];
	r = ( i&1 )? (r>>4):(r&0xf);
	return r;
}

static inline
unsigned char gf16v_set_ele( uint8_t * a , unsigned i , uint8_t v ) {
	unsigned char m = (i&1)? 0xf : 0xf0;
	a[i>>1] &= m;
	m = ( i&1 )? v<<4 : v&0xf;
	a[i>>1] |= m;
	return v;
}

static inline
void gf16v_split( uint8_t * z , const uint8_t * x , unsigned n )
{
	for(unsigned i=0;i<n;i++) z[i] = gf16v_get_ele( x , i );
}

static inline
unsigned char _gf16v_dot( const uint8_t *a , const uint8_t *b, unsigned _num_ele ){
	unsigned char r = 0;
	for(unsigned i=0;i<_num_ele;i++) {
		unsigned char _a = gf16v_get_ele(a,i);
		unsigned char _b = gf16v_get_ele(b,i);
		r ^= gf16_mul(_a,_b);
	}
	return r;
}

//static inline
//unsigned char gf256v_is_zero( const uint8_t * a , unsigned _num_byte ) {
//	unsigned char r = 0;
//	for(unsigned i=0;i<_num_byte;i++) r |= a[i];
//	return r==0;
//}

static inline
void gf16v_rand( uint8_t * a , unsigned _num_ele ) {
	if( 0 == _num_ele ) return;
	unsigned _num_byte = (_num_ele+1)/2;
	RAND_bytes( a , _num_byte );
	if( _num_ele & 1 ) a[_num_byte-1] &= 0xf;
}

static inline
void gf256v_rand( uint8_t * a , unsigned _num_byte ) {
	RAND_bytes( a , _num_byte );
}



static inline
void gf16mat_fdump(FILE * fp, const uint8_t *v, unsigned n_vec_byte , unsigned n_vec ) {
	for(unsigned i=0;i<n_vec;i++) {
		fprintf(fp,"[%d]",i);
		gf256v_fdump(fp,v,n_vec_byte);
		fprintf(fp,"\n");
		v += n_vec_byte;
	}
}

static inline
void gf256mat_fdump(FILE * fp, const uint8_t *v, unsigned n_vec_byte , unsigned n_vec ) { gf16mat_fdump(fp,v,n_vec_byte,n_vec); }


static inline
void _gf16mat_prod( uint8_t * c , const uint8_t * matA , unsigned n_A_vec_byte , unsigned n_A_width , const uint8_t * b ) {
	gf256v_set_zero(c,n_A_vec_byte);
	for(unsigned i=0;i<n_A_width;i++) {
		uint8_t bb = gf16v_get_ele( b , i );
		gf16v_madd( c , matA , bb , n_A_vec_byte );
		matA += n_A_vec_byte;
	}
}

static inline
void gf16mat_mul( uint8_t * c , const uint8_t * a , const uint8_t * b , unsigned len_vec ) {
	unsigned n_vec_byte = (len_vec+1)/2;
	for(unsigned k=0;k<len_vec;k++){
		gf256v_set_zero( c , n_vec_byte );
		const uint8_t * bk = b + n_vec_byte * k;
		for(unsigned i=0;i<len_vec;i++) {
			uint8_t bb = gf16v_get_ele( bk , i );
			gf16v_madd( c , a + n_vec_byte * i , bb , n_vec_byte  );
		}
		c += n_vec_byte;
	}
}


static inline
unsigned gf16mat_gauss_elim( uint8_t * a , uint8_t * b , unsigned W )
{
	unsigned n_vec_byte = (W+1)/2;
	for(unsigned i=0;i<W;i++) {
		uint8_t * ai = a + n_vec_byte*i;
		uint8_t * bi = b + n_vec_byte*i;
		if( 0 == gf16v_get_ele( ai , i )){
			for(unsigned j=i+1;j<W;j++) {
				uint8_t * aj = a + n_vec_byte*j;
				if( 0 == gf16v_get_ele(aj,i)) continue;
				uint8_t * bj = b + n_vec_byte*j;
				for(unsigned k=0;k<n_vec_byte;k++) {
					uint8_t tt = ai[k]; ai[k] = aj[k]; aj[k] = tt;
					tt = bi[k]; bi[k] = bj[k]; bj[k] = tt;
				}
				break;
			}
			if( 0 == gf16v_get_ele( ai , i )) return 0;
		}
		uint8_t pivot = gf16v_get_ele( ai , i );
		pivot = gf16_inv( pivot );
		gf16v_mul_scalar( ai , pivot , n_vec_byte );
		gf16v_mul_scalar( bi , pivot , n_vec_byte );
		for(unsigned j=0;j<W;j++) {
			if(i==j) continue;
			uint8_t * aj = a + n_vec_byte*j;
			uint8_t * bj = b + n_vec_byte*j;
			uint8_t e = gf16v_get_ele(aj,i);
			if( 0 == e ) continue;
			gf16v_madd( aj , ai , e , n_vec_byte );
			gf16v_madd( bj , bi , e , n_vec_byte );
		}
	}
	return 1;
}

static inline
unsigned gf16mat_rand_inv( uint8_t * a , uint8_t * b , unsigned H )
{
	unsigned n_vec_byte = (H+1)/2;
	uint8_t * aa = (uint8_t *)malloc( n_vec_byte*H );
	unsigned k;
	for(k=0;k<100;k++){
		gf256v_set_zero( b , n_vec_byte*H );
		for(unsigned i=0;i<H;i++){
			gf16v_rand( a + i*n_vec_byte, H );
			gf16v_set_ele( b + n_vec_byte * i , i , 1 );
		}
		gf256v_set_zero( aa , n_vec_byte*H );
		gf256v_add( aa , a , n_vec_byte*H );
		if( gf16mat_gauss_elim(aa,b,H) ) break;
	}
	free( aa );
	return (100!=k);
}





static inline
void gf256v_polymul( uint8_t * c, const uint8_t * a , const uint8_t * b , unsigned _num ) {
	for(unsigned i=0;i<_num*2-1;i++) c[i] = 0;
	for(unsigned i=0;i<_num;i++) _gf256v_madd( c+i , a , b[i] , _num );
}

static inline
void gf256_3v_polymul( uint32_t * c, const uint32_t * a , const uint32_t * b , unsigned _num ) {
	for(unsigned i=0;i<_num*2-1;i++) c[i] = 0;
	for(unsigned i=0;i<_num;i++)
		for(unsigned j=0;j<_num;j++) c[i+j] ^= gf256_3_mul( a[i] , b[j] );
}


static inline
void _gf256mat_prod( uint8_t * c , const uint8_t * matA , unsigned n_A_vec_byte , unsigned n_A_width , const uint8_t * b ) {
	gf256v_set_zero(c,n_A_vec_byte);
	for(unsigned i=0;i<n_A_width;i++) {
		gf256v_madd( c , matA , b[i] , n_A_vec_byte );
		matA += n_A_vec_byte;
	}
}

static inline
void gf256mat_mul( uint8_t * c , const uint8_t * a , const uint8_t * b , unsigned len_vec ) {
	unsigned n_vec_byte = len_vec;
	for(unsigned k=0;k<len_vec;k++){
		gf256v_set_zero( c , n_vec_byte );
		const uint8_t * bk = b + n_vec_byte * k;
		for(unsigned i=0;i<len_vec;i++) {
			gf256v_madd( c , a + n_vec_byte * i , bk[i] , n_vec_byte  );
		}
		c += n_vec_byte;
	}
}


static inline
unsigned gf256mat_gauss_elim( uint8_t * a , uint8_t * b , unsigned W )
{
	unsigned n_vec_byte = W;
	for(unsigned i=0;i<W;i++) {
		uint8_t * ai = a + n_vec_byte*i;
		uint8_t * bi = b + n_vec_byte*i;
		if( 0 == ai[i] ){
			for(unsigned j=i+1;j<W;j++) {
				uint8_t * aj = a + n_vec_byte*j;
				if( 0 == aj[i] ) continue;
				uint8_t * bj = b + n_vec_byte*j;
				for(unsigned k=0;k<n_vec_byte;k++) {
					uint8_t tt = ai[k]; ai[k] = aj[k]; aj[k] = tt;
					tt = bi[k]; bi[k] = bj[k]; bj[k] = tt;
				}
				break;
			}
			if( 0 == ai[i]) return 0;
		}
		uint8_t pivot = ai[i];
		pivot = gf256_inv( pivot );
		gf256v_mul_scalar( ai , pivot , n_vec_byte );
		gf256v_mul_scalar( bi , pivot , n_vec_byte );
		for(unsigned j=0;j<W;j++) {
			if(i==j) continue;
			uint8_t * aj = a + n_vec_byte*j;
			uint8_t * bj = b + n_vec_byte*j;
			uint8_t e = aj[i];
			if( 0 == e ) continue;
			gf256v_madd( aj , ai , e , n_vec_byte );
			gf256v_madd( bj , bi , e , n_vec_byte );
		}
	}
	return 1;
}

static inline
unsigned gf256mat_rand_inv( uint8_t * a , uint8_t * b , unsigned H )
{
	unsigned n_vec_byte = H;
	uint8_t * aa = (uint8_t *)malloc( n_vec_byte*H );
	unsigned k;
	for(k=0;k<100;k++){
		gf256v_set_zero( b , n_vec_byte*H );
		for(unsigned i=0;i<H;i++){
			gf256v_rand( a + i*n_vec_byte, H );
			(b + n_vec_byte * i)[i] = 1;
		}
		gf256v_set_zero( aa , n_vec_byte*H );
		gf256v_add( aa , a , n_vec_byte*H );
		if( gf256mat_gauss_elim(aa,b,H) ) break;
	}
	free( aa );
	return (100!=k);
}



////////////////////////   GF(4)   /////////////////////////////////




static inline
uint32_t _gf4v_mul_4( uint32_t a , uint32_t b0 , uint32_t b1 ) {
	uint32_t bit0 = a&0x55555555;
	uint32_t bit1 = a&0xaaaaaaaa;
	return (((bit0<<1)^bit1^(bit1>>1))&b1) ^ (a&b0);
}

static inline
uint32_t _read_32( const uint8_t *a, unsigned i, unsigned _num_byte ) {
	union d{
	uint32_t r;
	uint8_t v[4]; } u;
	u.r = 0;
	if( i+3<_num_byte ) u.r=*(const uint32_t*)(&a[i]);
	else for(unsigned j=0;i+j<_num_byte;j++) u.v[j]=a[i+j];
	return u.r;
}
static inline
void _write_32( uint8_t *a, unsigned i, unsigned _num_byte , uint32_t _v ) {
	union d{
	uint32_t r;
	uint8_t v[4]; } u;
	u.r = _v;
	if( i+3<_num_byte ) ((uint32_t*)&a[i])[0]=_v;
	else for(unsigned j=0;i+j<_num_byte;j++) a[i+j]=u.v[j];
}

static inline
void _gf4v_mul_scalar( uint8_t * a, uint8_t gf4_b , unsigned _num_byte ) {
//	for(unsigned i=0;i<_num_byte;i++) a[i]=gf256_mul_gf16(a[i],gf4_b);
	uint32_t b0 = 0-(((uint32_t)gf4_b)&1);
	uint32_t b1 = 0-(((uint32_t)gf4_b>>1)&1);
	for(unsigned i=0;i<_num_byte;i+=4) {
		uint32_t v = _read_32(a,i,_num_byte);
		uint32_t r = _gf4v_mul_4(v,b0,b1);
		_write_32(a,i,_num_byte,r);
	}
}

static inline
void _gf4v_madd( uint8_t * accu_c, const uint8_t * a , uint8_t gf4_b, unsigned _num_byte ) {
//	for(unsigned i=0;i<_num_byte;i++) a[i]=gf256_mul_gf16(a[i],gf4_b);
	uint32_t b0 = 0-(((uint32_t)gf4_b)&1);
	uint32_t b1 = 0-(((uint32_t)gf4_b>>1)&1);
	for(unsigned i=0;i<_num_byte;i+=4) {
		uint32_t v = _read_32(a,i,_num_byte);
		uint32_t acc = _read_32(accu_c,i,_num_byte);
		acc ^= _gf4v_mul_4(v,b0,b1);
		_write_32(accu_c,i,_num_byte,acc);
	}
}


static inline
unsigned char gf4v_get_ele( const uint8_t * a , unsigned i ) {
	unsigned char r = a[i>>2];
	r = r>>(2*(i&3));
	return r&3;
}

static inline
unsigned char gf4v_set_ele( uint8_t * a , unsigned i , uint8_t v ) {
	unsigned char m = 0x3<<(2*(i&0x3));
	a[i>>2] &= (~m);
	m &= v<<(2*(i&3));
	a[i>>2] |= m;
	return v;
}


static inline
void gf4v_split( uint8_t * z , const uint8_t * x , unsigned n ){
	for(unsigned i=0;i<n;i++) z[i] = gf4v_get_ele( x , n );
}


static inline
void _gf4mat_prod( uint8_t * c , const uint8_t * matA , unsigned n_A_vec_byte , unsigned n_A_width , const uint8_t * b ) {
	gf256v_set_zero(c,n_A_vec_byte);
	for(unsigned i=0;i<n_A_width;i++) {
		uint8_t bb = gf4v_get_ele( b , i );
		gf4v_madd( c , matA , bb , n_A_vec_byte );
		matA += n_A_vec_byte;
	}
}

static inline
void gf4mat_mul( uint8_t * c , const uint8_t * a , const uint8_t * b , unsigned len_vec ) {
	unsigned n_vec_byte = (len_vec+3)/4;
	for(unsigned k=0;k<len_vec;k++){
		gf256v_set_zero( c , n_vec_byte );
		const uint8_t * bk = b + n_vec_byte * k;
		for(unsigned i=0;i<len_vec;i++) {
			uint8_t bb = gf4v_get_ele( bk , i );
			gf4v_madd( c , a + n_vec_byte * i , bb , n_vec_byte  );
		}
		c += n_vec_byte;
	}
}

static inline
unsigned gf4mat_gauss_elim( uint8_t * a , uint8_t * b , unsigned W )
{
	unsigned n_vec_byte = (W+3)/4;
	for(unsigned i=0;i<W;i++) {
		uint8_t * ai = a + n_vec_byte*i;
		uint8_t * bi = b + n_vec_byte*i;
		if( 0 == gf4v_get_ele( ai , i )){
			for(unsigned j=i+1;j<W;j++) {
				uint8_t * aj = a + n_vec_byte*j;
				if( 0 == gf4v_get_ele(aj,i)) continue;
				uint8_t * bj = b + n_vec_byte*j;
				for(unsigned k=0;k<n_vec_byte;k++) {
					uint8_t tt = ai[k]; ai[k] = aj[k]; aj[k] = tt;
					tt = bi[k]; bi[k] = bj[k]; bj[k] = tt;
				}
				break;
			}
			if( 0 == gf4v_get_ele( ai , i )) return 0;
		}
		uint8_t pivot = gf4v_get_ele( ai , i );
		pivot = gf4_inv( pivot );
		gf4v_mul_scalar( ai , pivot , n_vec_byte );
		gf4v_mul_scalar( bi , pivot , n_vec_byte );
		for(unsigned j=0;j<W;j++) {
			if(i==j) continue;
			uint8_t * aj = a + n_vec_byte*j;
			uint8_t * bj = b + n_vec_byte*j;
			uint8_t e = gf4v_get_ele(aj,i);
			if( 0 == e ) continue;
			gf4v_madd( aj , ai , e , n_vec_byte );
			gf4v_madd( bj , bi , e , n_vec_byte );
		}
	}
	return 1;
}

static inline
unsigned gf4mat_rand_inv( uint8_t * a , uint8_t * b , unsigned H )
{
	unsigned n_vec_byte = (H+3)/4;
	uint8_t * aa = (uint8_t *)malloc( n_vec_byte*H );
	unsigned k;
	for(k=0;k<100;k++){
		gf256v_set_zero( b , n_vec_byte*H );
		for(unsigned i=0;i<H;i++){
			gf256v_rand( a + i*n_vec_byte, n_vec_byte );
			gf4v_set_ele( b + n_vec_byte * i , i , 1 );
		}
		gf256v_set_zero( aa , n_vec_byte*H );
		gf256v_add( aa , a , n_vec_byte*H );
		if( gf4mat_gauss_elim(aa,b,H) ) break;
	}
	free( aa );
	return (100!=k);
}





///////////////////////  GF(2) ////////////////////////////////



static inline
unsigned char gf2v_get_ele( const uint8_t * a , unsigned i ) {
	unsigned char r = a[i>>3];
	r = r>>(i&7);
	return r&1;
}

static inline
unsigned char gf2v_set_ele( uint8_t * a , unsigned i , uint8_t v ) {
	unsigned char m = (1<<(i&7));
	a[i>>3] &= (~m);
	m &= v<<(i&7);
	a[i>>3] |= m;
	return v;
}


#if 0
static inline
void gf2v_madd( uint8_t * c, const uint8_t * a , uint8_t b, unsigned _num_byte ) {
	if( 0 != (_num_byte & 3) ) {
		printf("error\n");
		exit(-1);
	}
	uint32_t vv = ((uint32_t)0)-b;
	for(unsigned j=0;j<_num_byte;j+=4)
		((uint32_t*)(c+j))[0] ^= (vv)&((uint32_t*)(a+j))[0];
}
#else
static inline
void gf2v_madd_64b( uint8_t * c, const uint8_t * a , uint8_t b, unsigned _num_byte ) {
	uint64_t vv = ((uint64_t)0)-b;
	for(unsigned j=0;j<_num_byte;j+=8)
		((uint64_t*)(c+j))[0] ^= (vv)&((uint64_t*)(a+j))[0];
}
static inline
void gf2v_madd_32b( uint8_t * c, const uint8_t * a , uint8_t b, unsigned _num_byte ) {
	uint32_t vv = ((uint32_t)0)-b;
	for(unsigned j=0;j<_num_byte;j+=4)
		((uint32_t*)(c+j))[0] ^= (vv)&((uint32_t*)(a+j))[0];
}
static inline
void gf2v_madd_16b( uint8_t * c, const uint8_t * a , uint8_t b, unsigned _num_byte ) {
	uint16_t vv = ((uint16_t)0)-b;
	for(unsigned j=0;j<_num_byte;j+=2)
		((uint16_t*)(c+j))[0] ^= (vv)&((uint16_t*)(a+j))[0];
}
static inline
void gf2v_madd( uint8_t * c, const uint8_t * a , uint8_t b, unsigned _num_byte ) {
	uint8_t vv = ((uint8_t)0)-b;
	for(unsigned j=0;j<_num_byte;j++) c[j] ^= a[j] & vv;
}
#endif

static inline
void gf2mat_prod( uint8_t * c , const uint8_t * matA , unsigned n_A_vec_byte , unsigned n_A_width , const uint8_t * b ) {
	gf256v_set_zero(c,n_A_vec_byte);
	for(unsigned i=0;i<n_A_width;i++) {
		gf2v_madd( c , matA , gf2v_get_ele(b,i) , n_A_vec_byte );
		matA += n_A_vec_byte;
	}
}


static inline
unsigned gf2mat_gauss_elim( uint8_t * a , uint8_t * b , unsigned W )
{
	unsigned n_vec_byte = (W+7)/8;
	for(unsigned i=0;i<W;i++) {
		uint8_t * ai = a + n_vec_byte*i;
		uint8_t * bi = b + n_vec_byte*i;
		if( 0 == gf2v_get_ele( ai , i )){
			for(unsigned j=i+1;j<W;j++) {
				uint8_t * aj = a + n_vec_byte*j;
				if( 0 == gf2v_get_ele(aj,i)) continue;
				uint8_t * bj = b + n_vec_byte*j;
				for(unsigned k=0;k<n_vec_byte;k++) {
					uint8_t tt = ai[k]; ai[k] = aj[k]; aj[k] = tt;
					tt = bi[k]; bi[k] = bj[k]; bj[k] = tt;
				}
				break;
			}
			if( 0 == gf2v_get_ele( ai , i )) return 0;
		}
		for(unsigned j=0;j<W;j++) {
			if(i==j) continue;
			uint8_t * aj = a + n_vec_byte*j;
			uint8_t * bj = b + n_vec_byte*j;

			uint8_t e = gf2v_get_ele(aj,i);
			if( 0 == e ) continue;
			gf256v_add( aj , ai , n_vec_byte );
			gf256v_add( bj , bi , n_vec_byte );
		}
	}
	return 1;
}

static inline
unsigned gf2mat_rand_inv( uint8_t * a , uint8_t * b , unsigned H )
{
	unsigned n_vec_byte = (H+7)/8;
	uint8_t * aa = (uint8_t *)malloc( n_vec_byte*H );
	unsigned k;
	for(k=0;k<100;k++){
		gf256v_set_zero( b , n_vec_byte*H );
		for(unsigned i=0;i<H;i++){
			gf256v_rand( a + i*n_vec_byte, n_vec_byte );
			gf2v_set_ele( b + n_vec_byte * i , i , 1 );
		}
		gf256v_set_zero( aa , n_vec_byte*H );
		gf256v_add( aa , a , n_vec_byte*H );
		if( gf2mat_gauss_elim(aa,b,H) ) break;
	}
	free( aa );
	return (100!=k);
}






#ifdef  __cplusplus
}
#endif



#endif

