
#include <stdio.h>

#include "pflash.h"

#include "mpkc.h"



#define TEST_RUN 100

const unsigned qterms = TERMS_QUAD_POLY(_PUB_N);


void quad_poly_eval(void * r ,const void * key,const void * i ){
	pflash_pubmap( (uint8_t*)r , (const uint8_t *)key , (const uint8_t *)i );
}

int main()
{

	unsigned char seed[32] = {0};

	uint8_t s1[_PUB_N_BYTE], s2[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE],tt[_PUB_N_BYTE];
	pflash_key pk,sk;
	pflash_key * dpk = &pk;
	pflash_key * dsk = &sk;


	printf("pFLASH(16,95,64)\n" );
	printf("sk size: %lu\n", sizeof(pflash_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );

	pflash_genkey_debug(dpk,dsk);


	printf("\n\n============= central map test ==============\n");

	gf16v_rand(s1,_SEC_N);

	pflash_ivs_central_map(s2,s1);
	pflash_central_map(tt,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _PUB_N_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_PUB_N_BYTE) );

	unsigned accu = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf16v_rand(s1,_SEC_N);

		pflash_ivs_central_map(s2,s1);
		pflash_central_map(tt,s2);
		gf256v_add( tt , s1 , _PUB_N_BYTE );
		if( ! gf256v_is_zero(tt,_PUB_N_BYTE) ) {
			printf("s1 : "); gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
			printf("<--: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
			printf("dif: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
			printf("is_zero()? %d\n", gf256v_is_zero(tt,_PUB_N_BYTE) );
			return -1;
		} else accu++;

	}
	printf("Q/iQ map  %d/%d passed.\n", accu , TEST_RUN );


//#ifdef _DEBUG_
	printf("\n\n============= debug pk/sk test ==============\n");

	//memset( s1 , 0 , _PUB_N_BYTE );
	//gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");
	//pflash_pubmap_seckey(d2,dpk,s1);
	//gf256v_fdump(stdout,d2,_PUB_M_BYTE); printf("\n\n");

//	gf16v_rand(s1,_SEC_N);
//	printf("s  :"); gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");
//	memset(s2,0,_PUB_N_BYTE);
//	gf16mat_prod(s2,dsk->mat_s,_PUB_N_BYTE,_SEC_N,s1);
//	printf("-->:"); gf256v_fdump(stdout,s2,_PUB_N_BYTE); printf("\n");

//	memset(s1,0,_PUB_N_BYTE);
//	gf16mat_prod(s1,dpk->mat_s,_PUB_N_BYTE,_SEC_N,s2);
//	printf("<--:"); gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");



	gf16v_rand(d1,_PUB_M);
	pflash_secmap( s1 , dsk , d1 , seed );
	pflash_pubmap_seckey( d2 , dpk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf16v_rand(d1,_PUB_M);
		pflash_secmap( s1 , dsk , d1 , seed );
		pflash_pubmap_seckey( d2 , dpk , s1 );

		memcpy( tt , d2 , _PUB_M_BYTE );
		gf256v_add( tt , d1 , _PUB_M_BYTE );
		if( ! gf256v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");
			return -1;
		}
	}
	printf("debug pk/sk test success.\n");


	printf("\n\n============= sign/verify test ==============\n");

	uint8_t qp_pk[(qterms+_PUB_N)*_PUB_M_BYTE];

	pflash_genkey(qp_pk,dsk);

	gf16v_rand(d1,_PUB_M);
	pflash_secmap( s1 , dsk , d1 , seed );
	pflash_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	double avg_time = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf16v_rand(d1,_PUB_M);
		//avg_time += pflash_secmap( s1 , dsk , d1 , seed );
		pflash_secmap( s1 , dsk , d1 , seed );
		pflash_pubmap( d2 , qp_pk , s1 );

		memcpy( tt , d2 , _PUB_M_BYTE );
		gf256v_add( tt , d1 , _PUB_M_BYTE );
		if( ! gf256v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");
			return -1;
		}
	}
	printf("pk/sk test success.\n");
	printf("avg iQ map in sign(): %f\n\n", avg_time/TEST_RUN );

	return 0;
}

