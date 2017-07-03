
#ifndef _GFEXT_POLY_H_
#define _GFEXT_POLY_H_


#include "blas.h"

#include "gfext.h"


#ifdef  __cplusplus
extern  "C" {
#endif


#define _GFSIZE  30
#define _MAX_TERMS (32)
#define _DEG (17)
#define _TERMS (18)

#if 0

#define _BATCH 1
#define B_GFMUL BGFMUL
#define B_GFADD BGFADD
#define B_GFINV BGFINV
#define B_GFPOW32 BGFPOW32

#else

#define _BATCH 16
#define B_GFMUL TBL_GFMUL
#define B_GFADD TBL_GFADD
#define B_GFINV TBL_GFINV
#define B_GFPOW32 TBL_GFPOW32

#endif

#define B_GFSIZE ((_GFSIZE)*(_BATCH))


static inline
void b_bgf_xor_1( uint8_t * bgf ) {
#if 1 == _BATCH
	bgf[0] ^= 1;
#elif 16 == _BATCH
	__m128i b = _mm_loadu_si128( (__m128i*)bgf );
	b ^= _mm_set1_epi8(1);
	_mm_storeu_si128( (__m128i*)bgf , b );
#else
error
#endif
}

static inline
void b_bgf_to_gf256v( uint8_t * gf256v , const uint8_t * bgf ) {
	for(unsigned i=0;i<_GFSIZE;i++) {
#if 1 == _BATCH
		gf256v[i] = bgf[i];
#elif 16 == _BATCH
		//gf256v[i] = tbl_gf256_get_1st_value( _mm_loadu_si128((__m128i*)(bgf+i*16)) );
		tbl_gf256ext_30_sse_extract( gf256v , bgf , 0 );
#else
here;
#endif
	}
}



static inline
void b_poly_eval( uint8_t *val , const uint8_t * poly , unsigned deg , const uint8_t * a )
{
	/// XXX: deg > _MAX_TERMS ???
	if( deg >= _MAX_TERMS ) { printf("EXCEED DEG IN POLY EVAL.\n"); memset(val,0,B_GFSIZE); return; }

	uint8_t a_deg[_MAX_TERMS*B_GFSIZE] __attribute__((aligned(16))) = {0};
	memcpy( a_deg + B_GFSIZE , a , B_GFSIZE );
	for(unsigned i=2;i<=deg;i++) B_GFMUL( a_deg + i*B_GFSIZE , a_deg + (i-1)*B_GFSIZE , a );

	uint8_t temp[B_GFSIZE] __attribute__((aligned(16)));
	uint8_t r[B_GFSIZE] __attribute__((aligned(16)));
	memcpy(r,poly,B_GFSIZE);
	for(unsigned i=1;i<=deg;i++) {
		B_GFMUL( temp , a_deg + i*B_GFSIZE , poly + i*B_GFSIZE );
		B_GFADD( r , temp );
	}
	memcpy(val,r,B_GFSIZE);
}



static inline
void b_poly_fdump(FILE *fp, const uint8_t *poly, unsigned deg ){
	uint8_t gf256v[_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=deg+1;i!=0;i--){
		b_bgf_to_gf256v( gf256v , poly+(i-1)*B_GFSIZE );
		gf256v_fdump(fp,gf256v,_GFSIZE);
		fprintf(fp,"X(%d)\n",i-1);
		if(1!=i) fprintf(fp,"+");
	}
}


static inline void b_poly_mul( uint8_t *p3, const uint8_t *p1 , unsigned deg , const uint8_t *c )
{
	for(unsigned i=0;i<=deg;i++) B_GFMUL(p3+i*B_GFSIZE,p1+i*B_GFSIZE,c);
}

static inline void b_poly_muladd( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise , const uint8_t *c )
{
	uint8_t tmp[B_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=0;i<=p1deg;i++) {
		B_GFMUL(tmp,p1+i*B_GFSIZE,c);
		B_GFADD( p3+(i+p1raise)*B_GFSIZE , tmp );
	}
}

static inline void b_poly_add( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise )
{
	for(unsigned i=0;i<=p1deg;i++) {
		B_GFADD( p3 + (i+p1raise)*B_GFSIZE, p1+ i*B_GFSIZE );
	}
	//gf256v_add( p3 + p1raise*_GFSIZE , p1 , (p1deg+1)*_GFSIZE );
}







static inline
unsigned _get_deg1poly_gcd( uint8_t * gcd , const uint8_t * p1 , const uint8_t * p2 , unsigned deg )
{
	uint8_t buf1[B_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));
	uint8_t buf2[B_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));

	memcpy( buf1 , p1 , (deg+1)*B_GFSIZE );
	memcpy( buf2 , p2 , (deg+1)*B_GFSIZE );
	uint8_t h1[B_GFSIZE] __attribute__((aligned(16)));
	uint8_t h2[B_GFSIZE] __attribute__((aligned(16)));

//	printf("p1: "); poly_fdump(stdout,p1,deg); printf("\n");
//	printf("p2: "); poly_fdump(stdout,p2,deg); printf("\n");

	for(unsigned d=deg;d>=1;d--){
//printf("deg: %d\n",d);
		memcpy(h1,buf1+d*B_GFSIZE,B_GFSIZE);
		memcpy(h2,buf2+d*B_GFSIZE,B_GFSIZE);
		b_poly_mul(buf1,buf1,d,h2);
		b_poly_mul(buf2,buf2,d,h1);
		b_poly_add(buf1,buf2,d,0);
//printf("b1: "); poly_fdump(stdout,buf1,deg); printf("\n");
		if(1==d) break;
		memcpy(h1,buf1+(d-1)*B_GFSIZE,B_GFSIZE);
		memcpy(h2,buf2+d*B_GFSIZE,B_GFSIZE);
		b_poly_mul(buf1,buf1,d-1,h2);
		b_poly_mul(buf2,buf2,d,h1);
		b_poly_add(buf2,buf1,d-1,1); /// here. deal with ht of buf2 for success check.
//printf("b2: "); poly_fdump(stdout,buf2,deg); printf("\n");
	}
	memcpy(gcd,buf2,2*B_GFSIZE);

#if 0
	unsigned succ1 = gf256v_is_zero(buf1,2*_GFSIZE);
	unsigned succ2 = gf256v_is_zero(buf2+2*_GFSIZE,_GFSIZE);
	unsigned succ3 = (gf256v_is_zero(buf2,_GFSIZE))?0:1;
	unsigned succ4 = (gf256v_is_zero(buf2+_GFSIZE,_GFSIZE))?0:1;
	return succ1&succ2&succ3&succ4;
#else
	return _BATCH;
#endif
}





////////////////////////////////////////////////


/// X^17 + X^16 + X^8 + X^5 + X^4 + X^2 + X + 1
static inline
void _poly_muladd_guicpoly( uint8_t * pp , const uint8_t * x17cpoly , const uint8_t * m )
{
	uint8_t temp[B_GFSIZE] __attribute__((aligned(16)));
	unsigned i;
	i = 0; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 1; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 2; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 4; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 5; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 8; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
	i = 16; B_GFMUL( temp , x17cpoly+i*B_GFSIZE , m ); B_GFADD( pp+i*B_GFSIZE , temp );
}

static inline
void _X_ext_32_mod_X17cpoly( uint8_t * r , const uint8_t * ext_poly , const uint8_t * nor_x17poly )
{
	const unsigned tar_deg = 32;
	const unsigned poly_len = 17;
	//uint8_t temp[(poly_len+tar_deg)*B_GFSIZE] __attribute__((aligned(16))) = {0};
	uint8_t temp[(60)*B_GFSIZE] __attribute__((aligned(16))) = {0};
	memcpy( temp + tar_deg*B_GFSIZE , ext_poly , B_GFSIZE*poly_len  );
	for(int i=(tar_deg-1);i>=0;i--) {
		uint8_t * ptr = temp + (i)*B_GFSIZE;
		_poly_muladd_guicpoly( ptr , nor_x17poly , ptr + B_GFSIZE*(poly_len) );
	}
	memcpy( r , temp , B_GFSIZE*poly_len );
}


static uint8_t X_32x[17][B_GFSIZE*17] __attribute__((aligned(16)));
static inline
void _poly_ext32_mod_X17( uint8_t * p2 , const uint8_t * p1 )
{
	memset( p2 , 0 , B_GFSIZE*17 );
	B_GFPOW32( p2 , p1 ); /// constant
	uint8_t temp[B_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=1;i<=16;i++) {
		B_GFPOW32( temp , p1+i*B_GFSIZE );
		b_poly_muladd( p2 , X_32x[i] , 16 , 0 , temp );
	}
}





/// X^17 + X^16 + X^8 + X^5 + X^4 + X^2 + X + 1
static inline
void Calc_Xext2_240_X_mod_cpoly( uint8_t * Xext_X , const uint8_t * nor_cpoly )
{
	memset( X_32x[0] , 0 , B_GFSIZE*17 );

	b_bgf_xor_1( X_32x[0] );
	//X_32x[0][0] = 1;
	for(unsigned i=1;i<17;i++) {
		_X_ext_32_mod_X17cpoly( X_32x[i] , X_32x[i-1] , nor_cpoly );
	}

	uint8_t buf1[17*B_GFSIZE] __attribute__((aligned(16)));
	uint8_t buf2[17*B_GFSIZE] __attribute__((aligned(16)));
	_poly_ext32_mod_X17( buf1 , X_32x[1] ); ///32x1=2^5 --> 2^10
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=10;i<240;i+=5) {
		_poly_ext32_mod_X17( ptr2 , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
	memcpy( Xext_X , ptr1 , B_GFSIZE*17 );
#if 1
	b_bgf_xor_1( Xext_X + B_GFSIZE );
	//Xext_X[_GFSIZE] ^= 1;
#endif
}





/// X^17 + X^16 + X^8 + X^5 + X^4 + X^2 + X + 1
///  7       6     5     4     3     2    1   0
static inline
unsigned find_unique_root( uint8_t * root , const uint8_t * gui_cpoly )
{
	uint8_t residue_poly[18*B_GFSIZE] __attribute__((aligned(16))) = {0};
	uint8_t temp[B_GFSIZE] __attribute__((aligned(16)));

	/// normalize
	B_GFINV( temp , gui_cpoly + 7*B_GFSIZE );
	B_GFMUL( residue_poly , gui_cpoly , temp );
	B_GFMUL( residue_poly + B_GFSIZE , gui_cpoly + B_GFSIZE , temp );
	B_GFMUL( residue_poly + 2*B_GFSIZE , gui_cpoly + 2*B_GFSIZE , temp );
	B_GFMUL( residue_poly + 4*B_GFSIZE , gui_cpoly + 3*B_GFSIZE , temp );
	B_GFMUL( residue_poly + 5*B_GFSIZE , gui_cpoly + 4*B_GFSIZE , temp );
	B_GFMUL( residue_poly + 8*B_GFSIZE , gui_cpoly + 5*B_GFSIZE , temp );
	B_GFMUL( residue_poly + 16*B_GFSIZE , gui_cpoly + 6*B_GFSIZE , temp );

	uint8_t Xext_X[18*B_GFSIZE] __attribute__((aligned(16)));

#if 30 == _GFSIZE
	Calc_Xext2_240_X_mod_cpoly( Xext_X , residue_poly );
#else
error here
#endif

	/// residue_poly = 1X^17 + ....
	/// Xext_X = ?X^16 + .....
	b_poly_mul( residue_poly , residue_poly , 16 , Xext_X+16*B_GFSIZE );
	b_poly_add( residue_poly , Xext_X , 15 , 1 );

	uint8_t deg1_poly[2*B_GFSIZE] __attribute__((aligned(16)));

	unsigned r = _get_deg1poly_gcd( deg1_poly , residue_poly , Xext_X , 16 );

	B_GFINV( temp , deg1_poly + B_GFSIZE );
	B_GFMUL( root , temp , deg1_poly );

	return r;
}




#define poly_add b_poly_add
#define poly_muladd b_poly_muladd
#define poly_mul b_poly_mul
#define poly_fdump b_poly_fdump
#define poly_eval b_poly_eval

#if 1

#undef poly_add
#undef poly_muladd
#undef poly_mul
#undef poly_fdump
#undef poly_eval

#endif


#ifdef  __cplusplus
}
#endif


#endif





