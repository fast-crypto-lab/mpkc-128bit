
#include <stdio.h>

#include "rainbow_config.h"

#include "rainbow.h"

#include "mpkc.h"



#define TEST_RUN 100

const unsigned qterms = TERMS_QUAD_POLY(_PUB_N);


void quad_poly_eval(void * r ,const void * key,const void * i ){
	rainbow_pubmap( (uint8_t*)r , (const uint8_t *)key , (const uint8_t *)i );
}

#include "benchmark.h"
//struct benchmark bmm;

int main()
{
//	bm_init( &bmm );

        printf("%s\n", _S_NAME );

        printf("sk size: %lu\n", sizeof(rainbow_key) );
        printf("pk size: %d\n", _PUB_KEY_LEN );
        printf("digest size: %d\n", _PUB_M_BYTE );
        printf("signature size: %d\n\n", _PUB_N_BYTE );

	uint8_t s1[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE];
	uint8_t tt[_PUB_N_BYTE];

	rainbow_key sk;
	rainbow_key * dsk = &sk;

#ifdef _DEBUG_RAINBOW_

	uint8_t s2[_PUB_N_BYTE];

	rainbow_key pk;
	rainbow_key * dpk = &pk;
	rainbow_genkey_debug(dpk,dsk);

	printf("\n\n============= central map test ==============\n");

	gf31v_rand(d1,_PUB_M_BYTE);
	gf31v_rand(s2,_PUB_N_BYTE-_PUB_M_BYTE);

	unsigned rr = rainbow_ivs_central_map(s2,&dsk->ckey,d1);
	rainbow_central_map(tt,&dpk->ckey,s2);
	printf("d1 : "); gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	gf31v_sub( tt , d1 , _PUB_N_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	printf("succ: %d, is_zero()? %d\n", rr , gf31v_is_zero(tt,_PUB_M_BYTE) );

	unsigned accu = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf31v_rand(d1,_PUB_M_BYTE);
		gf31v_rand(s2,_PUB_N_BYTE-_PUB_M_BYTE);

		unsigned r = rainbow_ivs_central_map(s2,&dsk->ckey,d1);
		rainbow_central_map(tt,&dpk->ckey,s2);
		gf31v_sub( tt , d1 , _PUB_M_BYTE );
		if( 1 != r ) continue;
		if( ! gf31v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail: %d, [%d]:\n", r , i );
			printf("s1 : "); gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
			printf("<--: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
			printf("dif: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
			printf("is_zero()? %d\n", gf31v_is_zero(tt,_PUB_M_BYTE) );
			return -1;
		} else accu++;

	}
	printf("Q/iQ map  %d/%d passed.\n", accu , TEST_RUN );

//#ifdef _DEBUG_
	printf("\n\n============= debug pk/sk test ==============\n");

	gf31v_rand(d1,_PUB_M_BYTE);
	rainbow_secmap( s1 , dsk , d1 );
	rainbow_pubmap_seckey( d2 , dpk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf31v_rand(d1,_PUB_M_BYTE);
		rainbow_secmap( s1 , dsk , d1 );
		rainbow_pubmap_seckey( d2 , dpk , s1 );

		memcpy( tt , d2 , _PUB_M_BYTE );
		gf31v_sub( tt , d1 , _PUB_M_BYTE );
		if( ! gf31v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");
			return -1;
		}
	}
	printf("debug pk/sk test success.\n");

#endif


	printf("\n\n============= sign/verify test ==============\n");

	uint8_t qp_pk[(qterms)*_PUB_M_BYTE];

	rainbow_genkey(qp_pk,dsk);

	gf31v_rand(d1,_PUB_M_BYTE);
	rainbow_secmap( s1 , dsk , d1 );
	rainbow_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf31v_rand(d1,_PUB_M_BYTE);
		//avg_time += rainbow_secmap( s1 , dsk , d1 , seed );
		rainbow_secmap( s1 , dsk , d1 );
		rainbow_pubmap( d2 , qp_pk , s1 );

		memcpy( tt , d2 , _PUB_M_BYTE );
		gf31v_sub( tt , d1 , _PUB_M_BYTE );
		if( ! gf31v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");
			return -1;
		}
	}
	printf("pk/sk test success.\n");

	return 0;
}

