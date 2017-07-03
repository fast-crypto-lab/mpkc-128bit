
#ifndef _GFEXT_POLY_H_
#define _GFEXT_POLY_H_


#include "blas.h"

#include "gfext.h"


#ifdef  __cplusplus
extern  "C" {
#endif


#define _GFSIZE (_GF_EXT_)
#define _MAX_TERMS (32)
#define _DEG (8)
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



#if 0
static inline
unsigned _get_deg1poly_gcd( uint8_t * gcd , const uint8_t * p1 , const uint8_t * p2 , unsigned deg )
{
	uint8_t buf1[_GFSIZE*_MAX_TERMS];
	uint8_t buf2[_GFSIZE*_MAX_TERMS];

	memcpy( buf1 , p1 , (deg+1)*_GFSIZE );
	memcpy( buf2 , p2 , (deg+1)*_GFSIZE );
	uint8_t h1[_GFSIZE];
	uint8_t h2[_GFSIZE];
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



/////////////////////////  for GF(2^64)  ////////////////////////////////////////////////



static inline
void _X_ext_8_mod_X8( uint8_t * r , const uint8_t * ext_poly , const uint8_t * nor_x8poly )
{
	uint8_t temp[(8+8)*_GFSIZE] __attribute__((aligned(16))) = {0};
	memcpy( temp + 8*_GFSIZE , ext_poly , _GFSIZE*8  );
	for(unsigned i=8;i!=0;i--) {
		poly_muladd( temp , nor_x8poly , 7 , i-1 , temp + _GFSIZE*(i+7) );
	}
	memcpy( r , temp , _GFSIZE*8 );
}


static uint8_t X_8x[8][_GFSIZE*8] __attribute__((aligned(16)));
static inline
void _poly_ext8_mod_X8( uint8_t * p2 , const uint8_t * p1 )
{
	memset( p2 , 0 , _GFSIZE*8 );
	BGFPOW8( p2 , p1 ); /// constant
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=1;i<=7;i++) {
		BGFPOW8( temp , p1+i*_GFSIZE );
		poly_muladd( p2 , X_8x[i] , 7 , 0 , temp );
	}
}


static inline
void Calc_Xext264_X_mod_X8( uint8_t * Xext_X , const uint8_t * residue_of_X8 )
{
	memset( X_8x[0] , 0 , _GFSIZE*8 );
	X_8x[0][0] = 1;
	memcpy( X_8x[1] , residue_of_X8 , _GFSIZE*8 );
	for(unsigned i=2;i<8;i++) {
		_X_ext_8_mod_X8( X_8x[i] , X_8x[i-1] , residue_of_X8 );
#if 0
{
printf("X^%d : ", 16*i);
uint8_t temp[_GFSIZE] = {0}; temp[0]=0x2;
uint8_t temp2[_GFSIZE];
poly_eval(temp2,X_16x[i],7,temp);
poly_fdump(stdout,X_16x[i],7);
printf(" = "); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
}
#endif
	}

	uint8_t buf1[8*_GFSIZE];
	uint8_t buf2[8*_GFSIZE];
	_poly_ext8_mod_X8( buf1 , X_8x[2] ); ///8x2=2^4 --> 2^7
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=7;i<64;i+=3) {
		_poly_ext8_mod_X8( ptr2 , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
#if 0
{
uint8_t temp[_GFSIZE];
memset(temp,0,_GFSIZE); temp[0]=0xff;
uint8_t temp2[_GFSIZE];
poly_eval(temp2,ptr1,16,temp);
printf("X^2^256(ff): "); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n");
}
#endif
	memcpy( Xext_X , ptr1 , _GFSIZE*8 );
	Xext_X[_GFSIZE] ^= 1;
#if 0
{
uint8_t temp[_GFSIZE];
memset(temp,0,_GFSIZE); temp[0]=0xff;
uint8_t temp2[_GFSIZE];
poly_eval(temp2,Xext_X,16,temp);
printf("X^2^256+X :  "); poly_fdump(stdout,Xext_X,16); printf("\n");
printf("X^2^256+X(ff): "); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n");
}
#endif
}



/////////////////////////  for GF(2^72)  ////////////////////////////////////////////////



static inline
void Calc_Xext272_X_mod_X8( uint8_t * Xext_X , const uint8_t * residue_of_X8 )
{
	memset( X_8x[0] , 0 , _GFSIZE*8 );
	X_8x[0][0] = 1;
	memcpy( X_8x[1] , residue_of_X8 , _GFSIZE*8 );
	for(unsigned i=2;i<8;i++) {
		_X_ext_8_mod_X8( X_8x[i] , X_8x[i-1] , residue_of_X8 );
	}

	uint8_t buf1[8*_GFSIZE];
	uint8_t buf2[8*_GFSIZE];
	_poly_ext8_mod_X8( buf1 , X_8x[1] ); ///8x1=2^3 --> 2^6
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=6;i<72;i+=3) {
		_poly_ext8_mod_X8( ptr2 , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
	memcpy( Xext_X , ptr1 , _GFSIZE*8 );
	Xext_X[_GFSIZE] ^= 1;
}



/////////////////////////  for GF(2^128)  ////////////////////////////////////////////////


static inline
void _X_ext_16_mod_X8( uint8_t * r , const uint8_t * ext_poly , const uint8_t * nor_x8poly )
{
	uint8_t temp[(8+16)*_GFSIZE] __attribute__((aligned(16))) = {0};
	memcpy( temp + 16*_GFSIZE , ext_poly , _GFSIZE*8  );
	for(unsigned i=16;i!=0;i--) {
		poly_muladd( temp , nor_x8poly , 7 , i-1 , temp + _GFSIZE*(i+7) );
	}
	memcpy( r , temp , _GFSIZE*8 );
}


static uint8_t X_16x[8][_GFSIZE*8] __attribute__((aligned(16)));
static inline
void _poly_ext16_mod_X8( uint8_t * p2 , const uint8_t * p1 )
{
	memset( p2 , 0 , _GFSIZE*8 );
	BGFPOW16( p2 , p1 ); /// constant
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));
	for(unsigned i=1;i<=7;i++) {
		BGFPOW16( temp , p1+i*_GFSIZE );
		poly_muladd( p2 , X_16x[i] , 7 , 0 , temp );
	}
}


static inline
void Calc_Xext2128_X_mod_X8( uint8_t * Xext_X , const uint8_t * residue_of_X8 )
{
	memset( X_16x[0] , 0 , _GFSIZE*8 );
	X_16x[0][0] = 1;
	for(unsigned i=1;i<8;i++) {
		_X_ext_16_mod_X8( X_16x[i] , X_16x[i-1] , residue_of_X8 );
	}

	uint8_t buf1[8*_GFSIZE];
	uint8_t buf2[8*_GFSIZE];
	_poly_ext16_mod_X8( buf1 , X_16x[1] ); ///16x1=2^4 --> 2^8
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=8;i<128;i+=4) {
		_poly_ext16_mod_X8( ptr2 , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
	memcpy( Xext_X , ptr1 , _GFSIZE*8 );
	Xext_X[_GFSIZE] ^= 1;
}




/////////////////////////  for GF(2^120)  ////////////////////////////////////////////////


static inline
void Calc_Xext2120_X_mod_X8( uint8_t * Xext_X , const uint8_t * residue_of_X8 )
{
	memset( X_16x[0] , 0 , _GFSIZE*8 );
	X_16x[0][0] = 1;
	for(unsigned i=1;i<8;i++) {
		_X_ext_16_mod_X8( X_16x[i] , X_16x[i-1] , residue_of_X8 );
	}

	uint8_t buf1[8*_GFSIZE];
	uint8_t buf2[8*_GFSIZE];
	_poly_ext16_mod_X8( buf1 , X_16x[1] ); ///16x1=2^4 --> 2^8
	uint8_t * ptr1 = buf1;
	uint8_t * ptr2 = buf2;
	for(unsigned i=8;i<120;i+=4) {
		_poly_ext16_mod_X8( ptr2 , ptr1 );
		uint8_t * ptr_tmp=ptr1;
		ptr1=ptr2;
		ptr2=ptr_tmp;
	}
	memcpy( Xext_X , ptr1 , _GFSIZE*8 );
	Xext_X[_GFSIZE] ^= 1;
}


/////////////////////////  main function  ////////////////////////////////////////////////



// X^8 + ... + 1
static inline
unsigned find_unique_root( uint8_t * root , const uint8_t * poly_deg8 )
{
	uint8_t residue_poly[8*_GFSIZE] __attribute__((aligned(16))) = {0};
	uint8_t temp[_GFSIZE] __attribute__((aligned(16)));
#if 0
printf("f uni root():\n");
poly_fdump(stdout,poly_deg8,8);
memset( temp , 0 , _GFSIZE );
temp[0] = 0x2;
poly_eval( temp , poly_deg8 , 8 , temp );
printf(" eval() :  is_zero()? %d\n", gf256v_is_zero(temp,_GFSIZE) );
#endif
	/// normalize
	BGFINV( temp , poly_deg8+ 8*_GFSIZE );
	poly_muladd( residue_poly , poly_deg8 , 7 , 0 , temp );
#if 0
{
uint8_t temp1[_GFSIZE] = {0}; temp1[0] = 0x2;
uint8_t temp2[_GFSIZE];
printf("residue poly: "); poly_fdump(stdout, residue_poly , 7 );
poly_eval( temp2 , residue_poly , 7 , temp1 );
printf(" eval() : is 0 ? %d :", gf256v_is_zero(temp2,_GFSIZE)  ); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
}
#endif
	uint8_t Xext_X[8*_GFSIZE] __attribute__((aligned(16)));

#if defined(_HMFEV_3_2_64_)
	Calc_Xext264_X_mod_X8( Xext_X , residue_poly );
#elif defined(_HMFEV_3_2_72_)
	Calc_Xext272_X_mod_X8( Xext_X , residue_poly );
#elif defined(_HMFEV_3_2_128_)
	Calc_Xext2128_X_mod_X8( Xext_X , residue_poly );
#elif defined(_HMFEV_3_2_120_)
	Calc_Xext2120_X_mod_X8( Xext_X , residue_poly );
#else
	make complilation error here.
#endif

	/// residue_poly = 1X^8 + ....
	/// Xext_X = ?X^7 + .....
	poly_mul( residue_poly , residue_poly , 7 , Xext_X+7*_GFSIZE );
	poly_add( residue_poly , Xext_X , 6 , 1 );
#if 0
{
uint8_t temp1[_GFSIZE] = {0}; temp1[0] = 0x2;
uint8_t temp2[_GFSIZE];
printf("residue poly: "); poly_fdump(stdout, residue_poly , 7 );
poly_eval( temp2 , residue_poly , 7 , temp1 );
printf(" eval() : is 0 ? %d :", gf256v_is_zero(temp2,_GFSIZE)  ); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
printf("X^2^128-X poly: "); poly_fdump(stdout, Xext_X , 7 );
poly_eval( temp2 , Xext_X , 7 , temp1 );
printf(" eval() : is 0 ? %d :", gf256v_is_zero(temp2,_GFSIZE)  ); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
}
#endif
	uint8_t deg1_poly[2*_GFSIZE] __attribute__((aligned(16)));

	unsigned r = _get_deg1poly_gcd( deg1_poly , residue_poly , Xext_X , 7 );
{
//printf("gcd: ->(%d) ",r); poly_fdump(stdout, deg1_poly, 1); printf("\n = ");
//uint8_t temp1[_GFSIZE] = {0}; temp1[0] = 0xff;
//uint8_t temp2[_GFSIZE];
//poly_eval( temp2 , deg1_poly , 1 , temp1 );
//printf(" eval() : is 0 ? %d :", gf256v_is_zero(temp2,_GFSIZE)  ); gf256v_fdump(stdout,temp2,_GFSIZE); printf("\n\n");
}
	BGFINV( temp , deg1_poly + _GFSIZE );
	BGFMUL( root , temp , deg1_poly );
#if 0
{
printf("check: ");
poly_eval( temp , poly_deg17 , 17 , root );
printf("%d\n", gf256v_is_zero(temp,_GFSIZE) );
}
#endif
	return r;
}



#ifdef  __cplusplus
}
#endif


#endif





