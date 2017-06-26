
#include <stdio.h>

#include "rainbow_config.h"

#ifdef _RAINBOW_256
#include "rainbow.h"
#else
#include "rainbow_16.h"
#endif

#include "mpkc.h"

#include "benchmark.h"


#define TEST_RUN 1000

//struct benchmark bmm;


int main()
{
//	bm_init(&bmm);
	struct benchmark bm1,bm2;
	char msg[256];

	unsigned char seed[32] = {0};
	uint8_t s1[_PUB_N_BYTE], s2[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE],tt[_PUB_N_BYTE];
	rainbow_key sk;
	rainbow_key * dsk = &sk;

#ifdef _RAINBOW_256
	printf("RAINBOW(256,28,20,20)\n" );
#else
	printf("RAINBOW(16,32,32,32)\n" );
#endif
	printf("sk size: %lu\n", sizeof(rainbow_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );


	printf("\n\n============= genkey() test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN] __attribute__((aligned(32)));
	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<15;i++) {
BENCHMARK(bm1,{
		rainbow_genkey(qp_pk,dsk);
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  genkey(): %s\n\n", msg );


	printf("\n\n============= central map test ==============\n");

	bm_init(&bm1);
	bm_init(&bm2);

	gf256v_rand(s1,_PUB_M_BYTE);
	rainbow_ivs_central_map(s2,&dsk->ckey,s1);
	rainbow_central_map(tt,&dsk->ckey,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _PUB_M_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _PUB_M_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_PUB_M_BYTE) );

	bm_init(&bm1);
	bm_init(&bm2);
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		rainbow_ivs_central_map( s2 , &dsk->ckey , d1 );
});
BENCHMARK(bm2,{
		rainbow_central_map( tt, &dsk->ckey , s2 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  iQ map(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  Q  map(): %s\n\n", msg );


	printf("\n\n============= sign/verify test ==============\n");

	gf256v_rand(d1,_PUB_M_BYTE);
	rainbow_secmap( s1 , dsk , d1 , seed );
	rainbow_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		rainbow_secmap( s1 , dsk , d1 , seed );
});
BENCHMARK(bm2,{
		rainbow_pubmap( d2 , qp_pk , s1 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  secmap(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  pubmap(): %s\n\n", msg );

//	bm_dump(msg,256,&bmm);
//	printf("benchmark: linear solver(): %s\n\n", msg );

	return 0;
}

