
#ifndef _GFEXT_POLY_GF2_H_
#define _GFEXT_POLY_GF2_H_


#include "blas.h"

#include "gfext.h"


#ifdef  __cplusplus
extern  "C" {
#endif


/// should be 28
#define _GFSIZE  (30)
#define _MAX_TERMS (32)
#define _DEG (9)
#define _TERMS (10)






static inline
void poly_eval( uint8_t *val , const uint8_t * poly , unsigned deg , const uint8_t * a )
{
	/// XXX: deg > _MAX_TERMS ???
	if( deg >= _MAX_TERMS ) { memset(val,0,_GFSIZE); return; }

	uint8_t a_deg[_MAX_TERMS*_GFSIZE] __attribute__((aligned(16))) = {0};
	memcpy( a_deg + _GFSIZE , a , _GFSIZE );
	for(unsigned i=2;i<=deg;i++) BGFMUL( a_deg + i*_GFSIZE , a_deg + (i-1)*_GFSIZE , a );

	memcpy(val,poly,_GFSIZE);
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=1;i<=deg;i++) {
		BGFMUL( temp , a_deg + i*_GFSIZE , poly + i*_GFSIZE );
		gf256v_add( val , temp , _GFSIZE );
	}
}




static inline
void poly_fdump(FILE *fp, const uint8_t *poly, unsigned deg ){
	for(unsigned i=deg+1;i!=0;i--){
		gf256v_fdump(fp,poly+(i-1)*_GFSIZE,_GFSIZE);
		fprintf(fp,"X(%d)\n",i-1);
		if(1!=i) fprintf(fp,"+");
	}
}


static inline void poly_mul( uint8_t *p3, const uint8_t *p1 , unsigned deg , const uint8_t *c )
{
	for(unsigned i=0;i<=deg;i++) BGFMUL(p3+i*_GFSIZE,p1+i*_GFSIZE,c);
}

static inline void poly_muladd( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise , const uint8_t *c )
{
	uint8_t tmp[_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=0;i<=p1deg;i++) {
		BGFMUL(tmp,p1+i*_GFSIZE,c);
		gf256v_add( p3+(i+p1raise)*_GFSIZE , tmp , _GFSIZE );
	}
}

static inline void poly_add( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise )
{
	gf256v_add( p3 + p1raise*_GFSIZE , p1 , (p1deg+1)*_GFSIZE );
}



#if 1
static inline
unsigned _get_deg1poly_gcd( uint8_t * gcd , const uint8_t * p1 , const uint8_t * p2 , unsigned deg )
{
	uint8_t buf1[_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));
	uint8_t buf2[_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));

	memcpy( buf1 , p1 , (deg+1)*_GFSIZE );
	memcpy( buf2 , p2 , (deg+1)*_GFSIZE );
	uint8_t h1[_GFSIZE] __attribute__((aligned(16)));
	uint8_t h2[_GFSIZE] __attribute__((aligned(16)));
//	printf("p1: "); poly_fdump(stdout,p1,deg); printf("\n");
//	printf("p2: "); poly_fdump(stdout,p2,deg); printf("\n");

	for(unsigned d=deg;d>=1;d--){
//printf("deg: %d\n",d);
		memcpy(h1,buf1+d*_GFSIZE,_GFSIZE);
		memcpy(h2,buf2+d*_GFSIZE,_GFSIZE);
		poly_mul(buf1,buf1,d,h2);
		poly_mul(buf2,buf2,d,h1);
		poly_add(buf1,buf2,d,0);
//printf("b1: "); poly_fdump(stdout,buf1,deg); printf("\n");
		if(1==d) break;
		memcpy(h1,buf1+(d-1)*_GFSIZE,_GFSIZE);
		memcpy(h2,buf2+d*_GFSIZE,_GFSIZE);
		poly_mul(buf1,buf1,d-1,h2);
		poly_mul(buf2,buf2,d,h1);
		poly_add(buf2,buf1,d-1,1); /// here. deal with ht of buf2 for success check.
//printf("b2: "); poly_fdump(stdout,buf2,deg); printf("\n");
	}
	memcpy(gcd,buf2,2*_GFSIZE);
	unsigned succ1 = gf256v_is_zero(buf1,2*_GFSIZE);
	unsigned succ2 = gf256v_is_zero(buf2+2*_GFSIZE,_GFSIZE);
	unsigned succ3 = (gf256v_is_zero(buf2,_GFSIZE))?0:1;
	unsigned succ4 = (gf256v_is_zero(buf2+_GFSIZE,_GFSIZE))?0:1;
	return succ1&succ2&succ3&succ4;
}
#else
static inline
unsigned _get_deg1poly_gcd( uint8_t * gcd , const uint8_t * p1 , const uint8_t * p2 , unsigned deg )
{
	uint8_t buf1[_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));
	uint8_t buf2[_GFSIZE*_MAX_TERMS] __attribute__((aligned(16)));

	memcpy( buf1 , p1 , (deg+1)*_GFSIZE );
	memcpy( buf2 , p2 , (deg+1)*_GFSIZE );
	unsigned deg1 = deg;
	while( deg1>0 && gf256v_is_zero(buf1+deg1*_GFSIZE,_GFSIZE) ) deg1--;
	unsigned deg2 = deg;
	while( deg2>0 && gf256v_is_zero(buf2+deg2*_GFSIZE,_GFSIZE) ) deg2--;
	uint8_t *ptr1 = buf1;
	uint8_t *ptr2 = buf2;
	if(deg2>deg1) {
		unsigned temp = deg1; deg1 = deg2; deg2 = temp;
		uint8_t * ptr = ptr1; ptr1 = ptr2; ptr2 = ptr;
	}
	uint8_t h1[_GFSIZE] __attribute__((aligned(16)));
	uint8_t h2[_GFSIZE] __attribute__((aligned(16)));
	while( deg2>0 ) {
		memcpy(h1,ptr1+deg1*_GFSIZE,_GFSIZE);
		memcpy(h2,ptr2+deg2*_GFSIZE,_GFSIZE);
		poly_mul(ptr1,ptr1,deg1,h2);
		poly_mul(ptr2,ptr2,deg2,h1);
		poly_add(ptr1,ptr2,deg2,deg1-deg2);
		while( deg1>0 && gf256v_is_zero(ptr1+deg1*_GFSIZE,_GFSIZE) ) deg1--;
#if 0
{
uint8_t temp[_GFSIZE];
memset(temp,0,_GFSIZE); temp[0]=0xff;
uint8_t temp2[_GFSIZE];
poly_eval(temp2,ptr1,deg1,temp);
printf("GCD:=> (%d) ",deg1); poly_fdump(stdout,ptr1,deg1);
printf(" = "); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n");
}
#endif
		if(deg2>deg1) {
			unsigned temp = deg1; deg1 = deg2; deg2 = temp;
			uint8_t * ptr = ptr1; ptr1 = ptr2; ptr2 = ptr;
		}
	}
	memcpy(gcd,ptr1,2*_GFSIZE);
	return deg1;
}
#endif


////////////////////////////////////////////////


/// X^9 + X^8 + X^6 + X^5 + X^4 + X^3 + X^2 + X + 1
static
void _poly_muladd_guicpoly( uint8_t * pp , const uint8_t * x9cpoly , const uint8_t * m )
{
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));
	unsigned i;
	i = 0; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 1; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 2; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 3; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 4; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 5; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 6; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
	i = 8; BGFMUL( temp , x9cpoly+i*_GFSIZE , m ); BGFADD( pp+i*_GFSIZE , temp );
}


static
void _X_ext_32_mod_X9cpoly( uint8_t * r , const uint8_t * ext_poly , const uint8_t * nor_x9poly )
{
	uint8_t temp[41*_GFSIZE + 16] __attribute__((aligned(16))) = {0};
	memcpy( temp + 32*_GFSIZE , ext_poly , _GFSIZE * 9 );
	for(int i=32;i>0;i--) {
		uint8_t * old_head = temp + (i+8)*_GFSIZE;
		uint8_t * new_poly = temp + (i-1)*_GFSIZE;
		//poly_muladd( new_poly , nor_x9poly , 8 , 0 , old_head );
		_poly_muladd_guicpoly( new_poly , nor_x9poly , old_head );
	}
	memcpy( r , temp , _GFSIZE*9 );
}

static
void _X_ext_23_mod_X9cpoly( uint8_t * r , const uint8_t * x9_poly , const uint8_t * nor_x9poly )
{
	uint8_t temp[41*_GFSIZE + 16] __attribute__((aligned(16))) = {0};
	memcpy( temp + 23*_GFSIZE , x9_poly , _GFSIZE * 9 );
	for(int i=23;i>0;i--) {
		uint8_t * old_head = temp + (i+8)*_GFSIZE;
		uint8_t * new_poly = temp + (i-1)*_GFSIZE;
		//poly_muladd( new_poly , nor_x9poly , 8 , 0 , old_head );
		_poly_muladd_guicpoly( new_poly , nor_x9poly , old_head );
	}
	memcpy( r , temp , _GFSIZE*9 );
}


static
void _generate_pow32_tables( uint8_t X_32x[][_GFSIZE*9] ,  const uint8_t * nor_cpoly )
{
	memset( X_32x[0] , 0 , _GFSIZE*9 );
	X_32x[0][0] = 1;
	_X_ext_23_mod_X9cpoly( X_32x[1] , nor_cpoly , nor_cpoly );
	for(unsigned i=2;i<9;i++) {
		_X_ext_32_mod_X9cpoly( X_32x[i] , X_32x[i-1] , nor_cpoly );
 	}
}



static
void _poly_ext32_mod_X9( uint8_t * p2 , const uint8_t X_32x[][_GFSIZE*9] , const uint8_t * p1 )
{
	memset( p2 , 0 , _GFSIZE*9 );
	BGFPOW32( p2 , p1 ); /// constant
	uint8_t temp[_GFSIZE+16] __attribute__((aligned(16)));
	for(unsigned i=1;i<=8;i++) {
		BGFPOW32( temp , p1+i*_GFSIZE );
		poly_muladd( p2 , X_32x[i] , 8 , 0 , temp );
	}
}


/// X^9 + X^8 + X^6 + X^5 + X^4 + X^3 + X^2 + X + 1
static
void Calc_Xext2_240_X_mod_cpoly( uint8_t * Xext_X , const uint8_t * nor_cpoly )
{
	uint8_t X_32x[9][_GFSIZE*9] __attribute__((aligned(16)));
	_generate_pow32_tables( X_32x , nor_cpoly );

	uint8_t buf1[10*_GFSIZE];
	uint8_t buf2[10*_GFSIZE];
	_poly_ext32_mod_X9( buf1 , X_32x , X_32x[1] ); ///32x1=2^5 --> 2^10
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=10;i<240;i+=5) {
		_poly_ext32_mod_X9( ptr2 , X_32x , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
	memcpy( Xext_X , ptr1 , _GFSIZE*9 );
	Xext_X[_GFSIZE] ^= 1;
}




/// X^9 + X^8 + X^6 + X^5 + X^4 + X^3 + X^2 + X + 1
///  8     7     6     5     4     3     2    1   0
static inline
unsigned find_unique_root( uint8_t * root , const uint8_t * gui_cpoly )
{
	uint8_t residue_poly[11*_GFSIZE] __attribute__((aligned(16))) = {0};
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));

	/// normalize
	BGFINV( temp , gui_cpoly + 8*_GFSIZE );
	BGFMUL( residue_poly , gui_cpoly , temp );
	BGFMUL( residue_poly + _GFSIZE , gui_cpoly + _GFSIZE , temp );
	BGFMUL( residue_poly + 2*_GFSIZE , gui_cpoly + 2*_GFSIZE , temp );
	BGFMUL( residue_poly + 3*_GFSIZE , gui_cpoly + 3*_GFSIZE , temp );
	BGFMUL( residue_poly + 4*_GFSIZE , gui_cpoly + 4*_GFSIZE , temp );
	BGFMUL( residue_poly + 5*_GFSIZE , gui_cpoly + 5*_GFSIZE , temp );
	BGFMUL( residue_poly + 6*_GFSIZE , gui_cpoly + 6*_GFSIZE , temp );
	BGFMUL( residue_poly + 8*_GFSIZE , gui_cpoly + 7*_GFSIZE , temp );
	//residue_poly[9*_GFSIZE] = 1;

	uint8_t Xext_X[10*_GFSIZE] __attribute__((aligned(16)));
#if 30 == _GFSIZE
	Calc_Xext2_240_X_mod_cpoly( Xext_X , residue_poly );
#else
error here.
#endif

	/// residue_poly = 1X^9 + ....
	/// Xext_X = ?X^8 + .....
	poly_mul( residue_poly , residue_poly , 9 , Xext_X+8*_GFSIZE );
	poly_add( residue_poly , Xext_X , 8 , 1 );
#if 0
{
extern uint8_t sol[];
uint8_t temp1[_GFSIZE] = {0}; temp1[0] = 0x2;
uint8_t temp2[_GFSIZE];
printf("X^2^224-X poly: "); poly_fdump(stdout, Xext_X , 16 );
poly_eval( temp2 , Xext_X , 16 , sol );
printf(" eval() : is 0 ? %d  :", gf256v_is_zero(temp2,_GFSIZE)  ); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
}
#endif

	uint8_t deg1_poly[2*_GFSIZE] __attribute__((aligned(16)));

	unsigned r = _get_deg1poly_gcd( deg1_poly , residue_poly , Xext_X , 8 );

	BGFINV( temp , deg1_poly + _GFSIZE );
	BGFMUL( root , temp , deg1_poly );

	return r;
}




#ifdef  __cplusplus
}
#endif


#endif





