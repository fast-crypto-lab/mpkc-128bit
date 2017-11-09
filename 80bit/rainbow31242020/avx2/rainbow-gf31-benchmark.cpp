
#include <stdio.h>

#include "rainbow_config.h"

#include "rainbow.h"

#include "mpkc.h"

#include "benchmark.h"

#include "utils.h"
#include "gf31_convert.h"

#define TEST_RUN 1000

//struct benchmark bmm;


int main()
{
//	bm_init(&bmm);
	struct benchmark bm1,bm2;
	char msg[256];

	//unsigned char seed[32] = {0};
	uint8_t s1[_PUB_N_BYTE];
	uint8_t d1[_PUB_M_BYTE],d2[_PUB_M_BYTE];
	rainbow_key sk;
	rainbow_key * dsk = &sk;

	printf("%s\n", _S_NAME );
	printf("sk size: %lu\n", sizeof(rainbow_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _PUB_N_BYTE );

	printf("\n\n============= genkey() test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN] __attribute__((aligned(32)));
	bm_init(&bm1);
	bm_init(&bm2);

	uint8_t pk_output[_PUB_KEY_LEN_PACK];
	uint8_t sk_output[_GF31_PACK_SIZE(sizeof(rainbow_key))];
	unsigned n_bytes;

	for(unsigned i=0;i<15;i++) {
BENCHMARK(bm1,{
		rainbow_genkey(qp_pk,dsk);
		n_bytes = gf31_quick_pack( pk_output , qp_pk , _PUB_KEY_LEN );
		n_bytes = gf31_quick_pack( sk_output , (unsigned char *)&dsk , sizeof(rainbow_key) );
});
	}
	bm_dump(msg,256,&bm1);
	printf("benchmark:  genkey(): %s\n\n", msg );

#ifdef _DEBUG_RAINBOW_
	printf("\n\n============= central map test ==============\n");
	uint8_t s2[_PUB_N_BYTE];
	uint8_t tt[_PUB_N_BYTE];

	bm_init(&bm1);
	bm_init(&bm2);

	gf31v_rand(s1,_PUB_M_BYTE);
	rainbow_ivs_central_map(s2,&dsk->ckey,s1);
	rainbow_central_map(tt,&dsk->ckey,s2);
	printf("s1 : "); gf256v_fdump( stdout , s1 , _PUB_M_BYTE ); printf("\n");
	printf("-->: "); gf256v_fdump( stdout , s2 , _PUB_N_BYTE ); printf("\n");
	printf("<--: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	gf31v_sub( tt , s1 , _PUB_M_BYTE );
	printf("dif: "); gf256v_fdump( stdout , tt , _PUB_M_BYTE ); printf("\n");
	printf("is_zero()? %d\n", gf31v_is_zero(tt,_PUB_M_BYTE) );

	bm_init(&bm1);
	bm_init(&bm2);
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf31v_rand(d1,_PUB_M_BYTE);
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
#endif

	printf("\n\n============= sign/verify test ==============\n");

	gf31v_rand(d1,_PUB_M_BYTE);
	unsigned char digest[_GF31_PACK_SIZE(_PUB_M_BYTE)];
	unsigned char signature[_GF31_PACK_SIZE(_PUB_N_BYTE)];
	n_bytes = gf31_quick_pack( digest , d1 , _PUB_M_BYTE );

	rainbow_secmap( s1 , dsk , d1 );
	rainbow_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	bm_init(&bm1);
	bm_init(&bm2);

	unsigned r;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf31v_rand(d1,_PUB_M_BYTE);
BENCHMARK(bm1,{
		gf31_from_digest( d1 , digest , _PUB_M_BYTE );
		r = gf31_quick_unpack( (unsigned char*)dsk , sk_output , sizeof(rainbow_key) );
		rainbow_secmap( s1 , dsk , d1 );
		r = gf31_quick_pack( signature , s1 , _PUB_N_BYTE );
});
BENCHMARK(bm2,{
		r = gf31_quick_unpack( qp_pk , pk_output , _PUB_KEY_LEN );
		r = gf31_quick_unpack( s1 , signature , _PUB_N_BYTE );
		rainbow_pubmap( d2 , qp_pk , s1 );
		gf31_from_digest( d1 , digest , _PUB_M_BYTE );
		for(unsigned j=0;j<_PUB_M_BYTE;j++) n_bytes ^= (d1[j]^d2[j])+r;
});
	}
	printf("dummy: %d\n", n_bytes );
	bm_dump(msg,256,&bm1);
	printf("benchmark:  secmap(): %s\n\n", msg );
	bm_dump(msg,256,&bm2);
	printf("benchmark:  pubmap(): %s\n\n", msg );

//	bm_dump(msg,256,&bmm);
//	printf("benchmark: linear solver(): %s\n\n", msg );

	return 0;
}

