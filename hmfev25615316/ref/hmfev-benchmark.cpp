
#include <stdio.h>

#include "hmfev.h"

#include "benchmark.h"


#define TEST_RUN 10000




int main()
{

	printf("HMFEV_(%d,%d,%d,%d,%d)\n",_GF,_EXT,_K,_V,_A );
	printf("sk size: %lu\n", sizeof(hmfev_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );

	struct benchmark bm1,bm2;
	char msg[256];

	unsigned char seed[32] = {0};
	uint8_t s1[_PUB_N_BYTE], s2[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE],tt[_PUB_N_BYTE];
	hmfev_key pk,sk;
	hmfev_key * dpk = &pk;
	hmfev_key * dsk = &sk;


	printf("\n\n============= genkey() test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN];
	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<50;i++) {
BENCHMARK(bm1,{
		hmfev_genkey(qp_pk,dsk);
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  genkey(): %s\n\n", msg );


	printf("\n\n============= central map test ==============\n");

	bm_init(&bm1);
	bm_init(&bm2);

	gf256v_rand(s1,_SEC_M_BYTE);
	gf256v_rand(s2,_SEC_N_BYTE);
	hmfev_ivs_central_map(s2,dsk,s1);
	hmfev_central_map(tt,dpk,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _SEC_M_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _SEC_M_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_SEC_M_BYTE) );

	bm_init(&bm1);
	bm_init(&bm2);
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(s1,_SEC_M_BYTE);
		gf256v_rand(s2,_SEC_N_BYTE);
BENCHMARK(bm1,{
		hmfev_ivs_central_map( s2 , dsk, s1 );
});
BENCHMARK(bm2,{
		hmfev_central_map( tt, dpk, s2 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  iQ map(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  Q  map(): %s\n\n", msg );


	printf("\n\n============= sign/verify test ==============\n");

	gf256v_rand(d1,_PUB_M_BYTE);
	hmfev_secmap( s1 , dsk , d1 , seed );
	hmfev_pub_map( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		hmfev_secmap( s1 , dsk , d1 , seed );
});
BENCHMARK(bm2,{
		hmfev_pub_map( d2 , qp_pk , s1 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  secmap(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  pubmap(): %s\n\n", msg );

	return 0;
}

