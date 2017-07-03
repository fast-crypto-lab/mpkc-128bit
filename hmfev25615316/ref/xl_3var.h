
#ifndef _XL_3VAR_H_
#define _XL_3VAR_H_


#include "blas.h"

#include "gfext.h"

#include "gfext_poly.h"


#ifdef  __cplusplus
extern  "C" {
#endif


//void poly_eval( uint8_t *val , const uint8_t * poly , unsigned deg , const uint8_t * a )
//void poly_fdump(FILE *fp, const uint8_t *poly, unsigned deg ){

//static inline void poly_mul( uint8_t *p3, const uint8_t *p1 , unsigned deg , const uint8_t *c )
//static inline void poly_muladd( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise , const uint8_t *c )
//static inline void poly_add( uint8_t *p3, const uint8_t *p1 , unsigned p1deg , unsigned p1raise )

typedef
struct _bgf {
	uint8_t v[_GFSIZE];
} bgf_t;

typedef uint32_t mono_t;

static inline void _extend_mono( mono_t *m , const mono_t e ) { *m += e; }


typedef
struct _poly {
	bgf_t coefs[20];
	mono_t monos[19];
	unsigned terms;
} poly_t;

//(11) [0x10000]+[0x300]+[0x201]+[0x200]+[0x102]+[0x101]+[0x100]+[0x3]+[0x2]+[0x1]+[0x0]
static inline
void poly_eval_except_x( bgf_t * r , const bgf_t * f , const bgf_t *_yz ) {
	bgf_t z = _yz[0];
	bgf_t z2; BGFSQU( (uint8_t*)&z2 , (uint8_t*)&z  );
	bgf_t z3; BGFMUL( (uint8_t*)&z3 , (uint8_t*)&z2 , (uint8_t*)&z  );
	bgf_t y = _yz[1];
	bgf_t yz; BGFMUL( (uint8_t*)&yz , (uint8_t*)&z , (uint8_t*)&y  );
	bgf_t yz2; BGFMUL( (uint8_t*)&yz2 , (uint8_t*)&z2 , (uint8_t*)&y  );
	bgf_t y2; BGFSQU( (uint8_t*)&y2 , (uint8_t*)&y );
	bgf_t y2z; BGFMUL( (uint8_t*)&y2z , (uint8_t*)&y2 , (uint8_t*)&z );
	bgf_t y3; BGFMUL( (uint8_t*)&y3 ,(uint8_t*)&y2 , (uint8_t*)&y );

	bgf_t tmp;
	r[0] = f[10];
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&z , (uint8_t *)&f[9] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&z2 , (uint8_t *)&f[8] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&z3 , (uint8_t *)&f[7] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&y , (uint8_t *)&f[6] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&yz , (uint8_t *)&f[5] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&yz2 , (uint8_t *)&f[4] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&y2 , (uint8_t *)&f[3] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&y2z , (uint8_t *)&f[2] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
	BGFMUL( (uint8_t *)&tmp , (uint8_t*)&y3 , (uint8_t *)&f[1] ); BGFADD( (uint8_t *)r , (uint8_t *)&tmp );
}

#if 0
static inline
void poly_eval_reverse( bgf_t * r , const bgf_t * f , unsigned deg , const bgf_t *a ) {
	r[0] = f[deg];
	if(0==deg) return;
	bgf_t tmp;
	bgf_t accu_a = a[0];
	BGFMUL((uint8_t *)&tmp, (uint8_t *)&f[deg-1], (uint8_t *)&accu_a);
	BGFADD((uint8_t *)r , (uint8_t *)&tmp );
	for(unsigned i=deg-1;i>0;i--) {
		BGFMUL((uint8_t *)&accu_a,(uint8_t *)&accu_a,(uint8_t *)a);
		BGFMUL((uint8_t *)&tmp, (uint8_t *)&f[i-1], (uint8_t *)&accu_a);
		BGFADD((uint8_t *)r , (uint8_t *)&tmp );
	}
}
#endif

static inline
void poly_eval_3var_quad( bgf_t * r , const bgf_t * f , const bgf_t * _x ) {
	bgf_t vars[10];
	vars[1] = _x[0]; // z
	BGFSQU( (uint8_t *)&vars[2] , (uint8_t *)&_x[0] ); // zz
	vars[3] = _x[1]; // y
	BGFMUL( (uint8_t *)&vars[4] , (uint8_t *)&_x[1] , (uint8_t *)&_x[0] ); // yz
	BGFSQU( (uint8_t *)&vars[5] , (uint8_t *)&_x[1] ); // yy
	vars[6] = _x[2]; // x
	BGFMUL( (uint8_t *)&vars[7] , (uint8_t *)&_x[2] , (uint8_t *)&_x[0] ); // xz
	BGFMUL( (uint8_t *)&vars[8] , (uint8_t *)&_x[2] , (uint8_t *)&_x[1] ); // xy
	BGFSQU( (uint8_t *)&vars[9] , (uint8_t *)&_x[2] ); // xx

	r[0] = f[0];
	for(int i=1;i<10;i++){
		BGFMUL( (uint8_t *)vars , (uint8_t *)&vars[i] , (uint8_t *)&f[i] );
		BGFADD( (uint8_t *)r , (uint8_t *)vars );
	}
}

static inline
void poly_set_3var_quad_poly( poly_t *p , const bgf_t * f ) {
                                      //  xx  ,xy     ,xz     ,x      ,yy   , yz  , y   , zz,z  ,1
	static uint32_t mono_tab3[] = {0x20000,0x10100,0x10001,0x10000,0x200,0x101,0x100,0x2,0x1,0 };
	int j = 0;
	for( int i=0;i<10;i++ ) {
		if( gf256v_is_zero((uint8_t *)&f[9-i],_GFSIZE) ) continue;
		p->coefs[j] = f[9-i];
		p->monos[j] = mono_tab3[i];
		j++;
	}
	p->terms = j;
}

static inline
void poly_copy( poly_t *r, const poly_t *a ) {
	r->terms = a->terms;
	for(unsigned i=0;i< a->terms;i++) r->coefs[i]=a->coefs[i];
	for(unsigned i=0;i< a->terms;i++) r->monos[i]=a->monos[i];
}

static inline
void __poly_fdump(FILE *fp, const poly_t *a ) {
	fprintf(fp,"(%d) ",a->terms);
	for(unsigned i=0;i<a->terms;i++) {
		fprintf(fp,"[0x%x]",a->monos[i]);
		if(i+1<a->terms) fprintf(fp,"+");
	}
	fprintf(fp,"\n");
}

static inline
void poly_extend( poly_t *p , mono_t m ) { for(unsigned i=0;i<p->terms;i++) p->monos[i]+=m; }

static inline
void poly_reduce_head( poly_t *p, const poly_t *a ) {
	if(0==p->terms) return;
	if(0==a->terms) return;
	if(p->monos[0]!=a->monos[0]) return;

	poly_t temp;
	bgf_t mi = p->coefs[0];
	bgf_t mj = a->coefs[0];
	unsigned i=1;
	unsigned j=1;
	unsigned k=0;
	while( i<a->terms && j<p->terms ) {
		if( a->monos[i] == p->monos[j] ) {
			bgf_t ri; BGFMUL( (uint8_t *)&ri , (uint8_t *)&mi , (uint8_t *)&(a->coefs[i]) );
			bgf_t rj; BGFMUL( (uint8_t *)&rj , (uint8_t *)&mj , (uint8_t *)&(p->coefs[j]) );
			BGFADD( (uint8_t *)&rj , (uint8_t *)&ri );
			if( gf256v_is_zero( (uint8_t *)&rj , _GFSIZE ) ) { i++; j++; continue; }
			temp.monos[k] = a->monos[i];
			temp.coefs[k] = rj;
			i++; j++; k++;
		} else if( a->monos[i] > p->monos[j] ) {
			temp.monos[k] = a->monos[i];
			BGFMUL( (uint8_t *)&temp.coefs[k] , (uint8_t *)&a->coefs[i] , (uint8_t *)&mi );
			i++; k++;
		} else {
			temp.monos[k] = p->monos[j];
			BGFMUL( (uint8_t *)&temp.coefs[k] , (uint8_t *)&p->coefs[j] , (uint8_t *)&mj );
			j++; k++;
		}

	}
	while( i<a->terms ) {
		temp.monos[k] = a->monos[i];
		BGFMUL( (uint8_t *)&temp.coefs[k] , (uint8_t *)&a->coefs[i] , (uint8_t *)&mi );
		i++; k++;
	}
	while( j<p->terms ) {
		temp.monos[k] = p->monos[j];
		BGFMUL( (uint8_t *)&temp.coefs[k] , (uint8_t *)&p->coefs[j] , (uint8_t *)&mj );
		j++; k++;
	}
	temp.terms = k;
	poly_copy( p , &temp );
}

static inline
void poly_guass_elim( poly_t * ps , unsigned dim )
{
	for(unsigned i=0;i<dim;i++){
		if( 0 == ps[i].terms ) continue;
		for( unsigned j=i+1;j<dim;j++) poly_reduce_head(&ps[j],&ps[i]);
	}
}

static inline
void calc_univar( bgf_t *p, bgf_t *yz3, bgf_t *z4, bgf_t * xp, const bgf_t *f0, const bgf_t *f1, const bgf_t *f2 )
{
	static poly_t gusMat[17];
	mono_t x = 0x10000;
	mono_t y = 0x100;
	mono_t z = 0x1;

	poly_set_3var_quad_poly( &gusMat[0] , f0 ); // 200
	poly_set_3var_quad_poly( &gusMat[1] , f1 ); // 110
	poly_set_3var_quad_poly( &gusMat[2] , f2 ); // 101
	poly_guass_elim( gusMat , 3 ); // XXX: may removed
#if 0
printf("g[0]: "); __poly_fdump( stdout, &gusMat[0] );
printf("g[1]: "); __poly_fdump( stdout, &gusMat[1] );
printf("g[2]: "); __poly_fdump( stdout, &gusMat[2] );
#endif
	poly_copy( &gusMat[10] , &gusMat[2] ); // 101
	poly_copy( &gusMat[9] , &gusMat[2] );
	poly_copy( &gusMat[7] , &gusMat[2] );
	poly_copy( &gusMat[6] , &gusMat[2] );
	poly_copy( &gusMat[8] , &gusMat[1] ); // 110
	poly_copy( &gusMat[5] , &gusMat[1] );
	poly_copy( &gusMat[4] , &gusMat[1] );
	poly_copy( &gusMat[3] , &gusMat[1] );
	poly_copy( &gusMat[2] , &gusMat[0] ); // 200
	poly_copy( &gusMat[1] , &gusMat[0] );

	poly_extend( &gusMat[0] , y ); // 210
	poly_extend( &gusMat[1] , z ); // 201
	//poly_extend( &gusMat[2] , 0 ); //200
	poly_extend( &gusMat[3] , y ); // 120
	poly_extend( &gusMat[4] , z ); // 111
	//poly_extend( &gusMat[5] , 0 ); // 110
	poly_extend( &gusMat[6] , z ); // 102
	//poly_extend( &gusMat[7] , 0 ); // 101
	poly_extend( &gusMat[8] , x ); // 210->100
	poly_extend( &gusMat[9] , x ); // 201->030
	poly_extend( &gusMat[10] , y );// 111->021
	poly_guass_elim( gusMat , 11 );
#if 0
printf("g[0]: 210 "); __poly_fdump( stdout, &gusMat[0] );
printf("g[1]: 201 "); __poly_fdump( stdout, &gusMat[1] );
printf("g[2]: 200 "); __poly_fdump( stdout, &gusMat[2] );
printf("g[3]: 120"); __poly_fdump( stdout, &gusMat[3] );
printf("g[4]: 111 "); __poly_fdump( stdout, &gusMat[4] );
printf("g[5]: 110"); __poly_fdump( stdout, &gusMat[5] );
printf("g[6]: 102 "); __poly_fdump( stdout, &gusMat[6] );
printf("g[7]: 101 "); __poly_fdump( stdout, &gusMat[7] );
printf("g[8]: 100 "); __poly_fdump( stdout, &gusMat[8] );
printf("g[8]: 030"); __poly_fdump( stdout, &gusMat[9] );
__poly_fdump( stdout, &gusMat[8] );
#endif
	memcpy( xp , gusMat[8].coefs , gusMat[8].terms * _GFSIZE );

	poly_copy( &gusMat[14] , &gusMat[10] ); // 021
	poly_copy( &gusMat[12] , &gusMat[10] );
	poly_copy( &gusMat[11] , &gusMat[10] );
	poly_copy( &gusMat[10] , &gusMat[9] ); // 030
	poly_copy( &gusMat[13] , &gusMat[8] ); // 100
	poly_extend( &gusMat[9] , z ); // 031
	//poly_extend( &gusMat[10] , 0 ); // 030
	poly_extend( &gusMat[11] , z ); // 022
	//poly_extend( &gusMat[12] , 0 ); // 021
	poly_extend( &gusMat[13] , z ); // 101->020
	poly_extend( &gusMat[14] , y ); // 031->013
	poly_guass_elim( gusMat + 7 , 8 );
#if 0
printf("g[7]: 101 "); __poly_fdump( stdout, &gusMat[7] );
printf("g[8]: 100 "); __poly_fdump( stdout, &gusMat[8] );
printf("g[9]: 031 "); __poly_fdump( stdout, &gusMat[9] );
printf("g[10]: 030 "); __poly_fdump( stdout, &gusMat[10] );
printf("g[11]: 022 "); __poly_fdump( stdout, &gusMat[11] );
printf("g[12]: 021 "); __poly_fdump( stdout, &gusMat[12] );
printf("g[13]: 020 "); __poly_fdump( stdout, &gusMat[13] );
printf("g[14]: 013 "); __poly_fdump( stdout, &gusMat[14] );
#endif
	poly_copy( &gusMat[15] , &gusMat[14] ); // 013
	poly_extend( &gusMat[14] , z ); // 014
	//poly_extend( &gusMat[15] , 0 ); // 013
	poly_copy( &gusMat[16] , &gusMat[13] );
	poly_extend( &gusMat[16] , z ); // 021->012
	poly_guass_elim( gusMat + 12 , 5 );
#if 0
printf("g[12]: 021 "); __poly_fdump( stdout, &gusMat[12] );
printf("g[13]: 020 "); __poly_fdump( stdout, &gusMat[13] );
printf("g[14]: 014 "); __poly_fdump( stdout, &gusMat[14] );
printf("g[15]: 013"); __poly_fdump( stdout, &gusMat[15] );
printf("g[16]: 012 "); __poly_fdump( stdout, &gusMat[16] );
#endif
	//print_mat<T,n_v,n_t,5>(gusMat+12);
	//            0     1    2    3   4    5     6   7   8
	//gusMat[15] yz3 + yz2 + yz + y + z4 + z3 + z2 + z + 1
	//            0    1    2    3   4    5     6   7   8
	//gusMat[16] yz2 + yz + y + z5 + z4 + z3 + z2 + z + 1

	/// ([16]: z2 + z + 1) g[15] - ([15] z3 + z2 + z + 1 ) g[16]
	bgf_t *p1 = z4; for(int i=0;i<5;i++) p1[i] = gusMat[15].coefs[8-i];
	bgf_t p2[6]; for(int i=0;i<6;i++) p2[i] = gusMat[16].coefs[8-i];
	bgf_t ext1[3]; for(int i=0;i<3;i++) ext1[i] = gusMat[16].coefs[2-i];
	bgf_t *ext2 = yz3; for(int i=0;i<4;i++) ext2[i] = gusMat[15].coefs[3-i];

	memset( p , 0 , sizeof(bgf_t)*9 );
	bgf_t tmp;
	for( int j=0;j<4;j++) {
		for( int i=0;i<6;i++) {
			BGFMUL( (uint8_t *)&tmp , (uint8_t *)&ext2[j] , (uint8_t *)&p2[i] );
			BGFADD( (uint8_t *)&p[i+j] , (uint8_t *)&tmp );
		}
	}
	for( int j=0;j<3;j++) {
		for( int i=0;i<5;i++) {
			BGFMUL( (uint8_t *)&tmp , (uint8_t *)&ext1[j] , (uint8_t *)&p1[i] );
			BGFADD( (uint8_t *)&p[i+j] , (uint8_t *)&tmp );
		}
	}
}


#ifdef  __cplusplus
}
#endif


#endif





