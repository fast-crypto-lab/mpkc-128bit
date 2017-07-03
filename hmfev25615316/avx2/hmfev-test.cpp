
#include <stdio.h>

#include "hmfev.h"




#define TEST_RUN 100

const unsigned qterms = TERMS_QUAD_POLY(_PUB_N);



void quad_poly_eval(void * r ,const void * key,const void * i ){
	hmfev_pub_map( (uint8_t*)r , (const uint8_t *)key , (const uint8_t *)i );
}

int main()
{

	printf("HMFEV_(%d,%d,%d,%d,%d)\n",_GF,_EXT,_K,_V,_A );
	printf("sk size: %lu\n", sizeof(hmfev_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );

/// interpolation test
	printf("\n\n============= interpolation test ==============\n");

	uint8_t poly1[qterms*_PUB_M_BYTE];
	gf256v_rand( poly1 , qterms*_PUB_M_BYTE );


	uint8_t poly2[qterms*_PUB_M_BYTE];
	hmfev_interpolate( poly2 , quad_poly_eval , poly1 );

	bool checked = true;
	for(unsigned i=0;i<qterms*_PUB_M_BYTE;i++) {
		uint8_t a = poly1[i];
		a ^= poly2[i];

		if( 0 != a ) {
			printf("[%d] %02x:%02x|%02x\n",i,poly1[i],poly2[i],a);
			checked = false;
			break;
		}
	}

	printf("interpolate check: %s\n\n", checked?"success!":"fail!") ;
	if( ! checked ) return -1;

	printf("\n\n============= GEN KEY  ==============\n");

	unsigned char seed[32] = {0};

	uint8_t s1[_PUB_N_BYTE], s2[_PUB_N_BYTE];
	uint8_t d1[_SEC_M_BYTE],d2[_SEC_M_BYTE],tt[_SEC_M_BYTE],diff[_SEC_M_BYTE];
	hmfev_key pk,sk;
	hmfev_key * dpk = &pk;
	hmfev_key * dsk = &sk;

	hmfev_genkey_debug(dpk,dsk);

	printf("\n\n============= central map test ==============\n");

	gf256v_rand(s1,_SEC_M_BYTE);
	gf256v_rand(s2,_PUB_N_BYTE);

	hmfev_ivs_central_map(s2,dsk,s1);
	hmfev_central_map(tt,dpk,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _SEC_M_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _SEC_M_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_SEC_M_BYTE) );

	unsigned accu = 0;
	unsigned accu_claim = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(s1,_SEC_M_BYTE);
		gf256v_rand(s2,_SEC_N_BYTE);

		unsigned succ = hmfev_ivs_central_map(s2,dsk,s1);
		if( 1 != succ ) continue;
		accu_claim++;
		hmfev_central_map(tt,dpk,s2);
		memcpy(diff,tt, _SEC_M_BYTE );
		gf256v_add( diff , s1 , _SEC_M_BYTE );
		if( gf256v_is_zero(diff,_SEC_M_BYTE) ) accu++;
		else {
			printf("s1 : "); gf256v_fdump( stdout , s1 , _SEC_M_BYTE ); printf("\n");
			printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
			printf("<--: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
			printf("dif: "); gf256v_fdump( stdout , diff , _SEC_M_BYTE ); printf("\n");
			printf("is_zero()? %d\n", gf256v_is_zero(diff,_SEC_M_BYTE) );
			//return -1;
		}
	}
	printf("Q/iQ map  %d/%d/%d passed.\n", accu , accu_claim , TEST_RUN );

//#ifdef _DEBUG_
	printf("\n\n============= debug pk/sk test ==============\n");

	//memset( s1 , 0 , _PUB_N_BYTE );
	//gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");
	//hmfev_pubmap_seckey(d2,dpk,s1);
	//gf256v_fdump(stdout,d2,_PUB_M_BYTE); printf("\n\n");

//	gf16v_rand(s1,_SEC_N);
//	printf("s  :"); gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");
//	memset(s2,0,_PUB_N_BYTE);
//	gf16mat_prod(s2,dsk->mat_s,_PUB_N_BYTE,_SEC_N,s1);
//	printf("-->:"); gf256v_fdump(stdout,s2,_PUB_N_BYTE); printf("\n");

//	memset(s1,0,_PUB_N_BYTE);
//	gf16mat_prod(s1,dpk->mat_s,_PUB_N_BYTE,_SEC_N,s2);
//	printf("<--:"); gf256v_fdump(stdout,s1,_PUB_N_BYTE); printf("\n");


	gf256v_rand(d1,_PUB_M_BYTE);
	hmfev_secmap( s1 , dsk , d1 , seed );
	hmfev_pubmap_seckey( d2 , dpk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _SEC_M_BYTE ); printf("\n\n");

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
		hmfev_secmap( s1 , dsk , d1 , seed );
		hmfev_pubmap_seckey( d2 , dpk , s1 );

		memcpy( tt , d2 , _PUB_M_BYTE );
		gf256v_add( tt , d1 , _PUB_M_BYTE );
		if( ! gf256v_is_zero(tt,_PUB_M_BYTE) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
			gf256v_fdump( stdout , d2 , _SEC_M_BYTE ); printf("\n\n");
			return -1;
		}
	}
	printf("debug pk/sk test success.\n");

	printf("\n\n============= sign/verify test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN];

	hmfev_genkey(qp_pk,dsk);

	gf256v_rand(d1,_PUB_M_BYTE);
	hmfev_secmap( s1 , dsk , d1 , seed );
	hmfev_pub_map( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	//double avg_time = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
		//avg_time += hmfev_secmap( s1 , dsk , d1 , seed );
		hmfev_secmap( s1 , dsk , d1 , seed );
		hmfev_pub_map( d2 , qp_pk , s1 );

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
	printf("pk/sk %d test success.\n", TEST_RUN);
	//printf("avg iQ map in sign(): %f\n\n", avg_time/TEST_RUN );

	return 0;
}

