
#include <stdio.h>

#include "gui_config.h"

#if 2 == _GF
#include "gui_gf2.h"
#else
#include "gui.h"
#endif

#include "quartz_sig.h"

#include "benchmark.h"


#define TEST_RUN 1000




int main()
{
	struct benchmark bm1,bm2;
	char msg[256];

	unsigned char seed[32] = {0};
	uint8_t s1[_PUB_N_BYTE*_BATCH], s2[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE],tt[_PUB_N_BYTE];
	uint8_t vinegar[_VINEGAR_BYTE*_BATCH] __attribute__((aligned(32)));
	gui_key pk,sk;
	gui_key * dpk = &pk;
	gui_key * dsk = &sk;

        printf("GUI(%d,%d,%d,%d,%d,%d)\n", _GF , _EXT , GUI_C_DEG , _V , _A , _K );
        printf("sk size: %lu\n", sizeof(gui_key) );
        printf("pk size: %d\n", _PUB_KEY_LEN );
        printf("digest size: %d\n", _PUB_M_BYTE );
        printf("signature size: %d\n\n", _SIGNATURE_BYTE );


	printf("\n\n============= genkey() test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN];
	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<50;i++) {
BENCHMARK(bm1,{
		gui_genkey(qp_pk,dsk);
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  genkey(): %s\n\n", msg );


	printf("\n\n============= central map test ==============\n");

	bm_init(&bm1);
	bm_init(&bm2);

	gf256v_rand(s1,_SEC_M_BYTE*_BATCH);
	gf256v_rand(vinegar,_VINEGAR_BYTE*_BATCH);
	gf256v_rand(s2,_PUB_N_BYTE);
	gui_ivs_central_map(s2,dsk,s1,vinegar);
	gui_central_map(tt,dpk,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _SEC_M_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	gf256v_add( tt , s1 , _SEC_M_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _SEC_M_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf256v_is_zero(tt,_SEC_M_BYTE) );

	bm_init(&bm1);
	bm_init(&bm2);
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(s1,_SEC_M_BYTE*_BATCH);
		gf256v_rand(vinegar,_VINEGAR_BYTE*_BATCH);
		gf256v_rand(s2,_PUB_N_BYTE);
BENCHMARK(bm1,{
		gui_ivs_central_map( s2 , dsk, s1 , vinegar );
});
BENCHMARK(bm2,{
		gui_central_map( tt, dpk, s2 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  iQ map(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  Q  map(): %s\n\n", msg );


	printf("\n\n============= sec/pub map test ==============\n");

	gf256v_rand(d1,_PUB_M_BYTE);
	gui_secmap( s1 , dsk , d1 , seed );
	gui_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	bm_init(&bm1);
	bm_init(&bm2);

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		gui_secmap( s1 , dsk , d1 , seed );
});
BENCHMARK(bm2,{
		gui_pubmap( d2 , qp_pk , s1 );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  secmap(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  pubmap(): %s\n\n", msg );


	printf("\n\n============= sign/verify test ==============\n");

	gf256v_rand(d1,_PUB_M_BYTE);
	uint8_t signature[_SIGNATURE_BYTE];

	bm_init(&bm1);
	bm_init(&bm2);

	unsigned rr = 1;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		rr &= quartz_sign( signature , (const uint8_t *) dsk , d1 );
});
BENCHMARK(bm2,{
		rr &= quartz_verify( qp_pk , signature , d1 );
});
	}
	printf("check: succ: %d\n", rr );
	bm_dump(msg,256,&bm1);
	printf("benchmark:  sign(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  verify(): %s\n\n", msg );


	return 0;
}

