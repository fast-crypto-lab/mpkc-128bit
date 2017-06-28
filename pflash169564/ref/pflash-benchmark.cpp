
#include <stdio.h>

#include "pflash.h"

#include "mpkc.h"

#include "benchmark.h"


#define TEST_RUN 1000




int main()
{
	struct benchmark bm1,bm2;
	char msg[256];

	unsigned char seed[32] = {0};
	uint8_t s1[_PUB_N_BYTE], s2[_PUB_N_BYTE];
	uint8_t d1[_PUB_N_BYTE],d2[_PUB_N_BYTE],tt[_PUB_N_BYTE];
	pflash_key sk;
	pflash_key * dsk = &sk;

	printf("pFLASH(16,95,64)\n" );
	printf("sk size: %lu\n", sizeof(pflash_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );

	printf("\n\n============= genkey() test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN] __attribute__((aligned(32)));
	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<15;i++) {
BENCHMARK(bm1,{
		pflash_genkey(qp_pk,dsk);
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  genkey(): %s\n\n", msg );


	printf("\n\n============= central map test ==============\n");

	bm_init(&bm1);
	bm_init(&bm2);

	gf16v_rand(s1,_SEC_N);
	pflash_ivs_central_map(s2,s1);
	pflash_central_map(tt,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _PUB_N_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _PUB_N_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_PUB_N_BYTE) );

	bm_init(&bm1);
	bm_init(&bm2);
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf16v_rand(d1,_PUB_M);
BENCHMARK(bm1,{
		pflash_ivs_central_map( s2 , s1 );
});
BENCHMARK(bm2,{
		pflash_central_map( tt, s2 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  iQ map(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  Q  map(): %s\n\n", msg );


	printf("\n\n============= sign/verify test ==============\n");

	gf16v_rand(d1,_PUB_M);
	pflash_secmap( s1 , dsk , d1 , seed );
	pflash_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf16v_rand(d1,_PUB_M);
BENCHMARK(bm1,{
		pflash_secmap( s1 , dsk , d1 , seed );
});
BENCHMARK(bm2,{
		pflash_pubmap( d2 , qp_pk , s1 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  secmap(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  pubmap(): %s\n\n", msg );

	return 0;
}

