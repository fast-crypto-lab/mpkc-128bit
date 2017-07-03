
#include <stdio.h>

#include "gui_config.h"

#if 2 == _GF
#include "gui_gf2.h"
const unsigned qterms = TERMS_QUAD_POLY_GF2(_PUB_N);
#else
#include "gui.h"
const unsigned qterms = TERMS_QUAD_POLY(_PUB_N);
#endif

#include "quartz_sig.h"

#include "mpkc.h"



#define TEST_RUN 100




void quad_poly_eval(void * r ,const void * key,const void * i ){
	gui_pubmap( (uint8_t*)r , (const uint8_t *)key , (const uint8_t *)i );
}

int main()
{


	printf("GUI(%d,%d,%d,%d,%d,%d)\n", _GF , _EXT , GUI_C_DEG , _V , _A , _K );
	printf("sk size: %lu\n", sizeof(gui_key) );
	printf("pk size: %d\n", _PUB_KEY_LEN );
	printf("digest size: %d\n", _PUB_M_BYTE );
	printf("signature size: %d\n\n", _SIGNATURE_BYTE );

/// interpolation test
	printf("\n\n============= interpolation test ==============\n");

	uint8_t poly1[qterms*_PUB_M_BYTE];
	gf256v_rand( poly1 , qterms );


	uint8_t poly2[qterms*_PUB_M_BYTE];
	mpkc_interpolate( poly2 , quad_poly_eval , poly1 );

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

	uint8_t s1[_PUB_N_BYTE*_BATCH], s2[_PUB_N_BYTE];
	uint8_t d1[_SEC_M_BYTE],d2[_SEC_M_BYTE],tt[_SEC_M_BYTE],diff[_SEC_M_BYTE];
	uint8_t vinegar[_VINEGAR_BYTE*_BATCH] __attribute__((aligned(32)));
	gui_key pk,sk;
	gui_key * dpk = &pk;
	gui_key * dsk = &sk;

	gui_genkey_debug(dpk,dsk);
	printf("debug pk/sk are generated.");

	printf("\n\n============= central map test ==============\n");

	gf256v_rand(s1,_SEC_M_BYTE);
	gf256v_rand(s1,_SEC_M_BYTE*_BATCH);
	gf256v_rand(s2,_PUB_N_BYTE);
	gf256v_rand(vinegar,_VINEGAR_BYTE*_BATCH);

	gui_ivs_central_map(s2,dsk,s1,vinegar);
	gui_central_map(tt,dpk,s2);
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
		gf256v_rand(s1,_SEC_M_BYTE*_BATCH);
		gf256v_rand(s2,_PUB_N_BYTE);
		gf256v_rand(vinegar,_VINEGAR_BYTE*_BATCH);

		unsigned succ = gui_ivs_central_map(s2,dsk,s1,vinegar);
		if( _BATCH < succ ) continue;
		accu_claim++;
		gui_central_map(tt,dpk,s2);
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

	gf256v_rand(d1,_PUB_M_BYTE);
	gui_secmap( s1 , dsk , d1 , seed );
	gui_pubmap_seckey( d2 , dpk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _SEC_M_BYTE ); printf("\n\n");

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);
		gui_secmap( s1 , dsk , d1 , seed );
		gui_pubmap_seckey( d2 , dpk , s1 );

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

	printf("\n\n============= pub/sec map test ==============\n");

	uint8_t qp_pk[_PUB_KEY_LEN];

	gui_genkey(qp_pk,dsk);

	gf256v_rand(d1,_PUB_M_BYTE);
	gui_secmap( s1 , dsk , d1 , seed );
	gui_pubmap( d2 , qp_pk , s1 );
	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , s1 , _PUB_N_BYTE ); printf("\n");
	gf256v_fdump( stdout , d2 , _PUB_M_BYTE ); printf("\n\n");

	double avg_time = 0;
	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M);
		//avg_time += gui_secmap( s1 , dsk , d1 , seed );
		gui_secmap( s1 , dsk , d1 , seed );
		gui_pubmap( d2 , qp_pk , s1 );

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
	printf("avg iQ map in sign(): %f\n\n", avg_time/TEST_RUN );


	printf("\n\n============= sign/verify test ==============\n");

	uint8_t signature[_SIGNATURE_BYTE];
	gf256v_rand(d1,_PUB_M_BYTE);

	unsigned sr = quartz_sign( signature , (const uint8_t *)dsk , d1 );
	unsigned vr = quartz_verify( qp_pk , signature , d1 );

	gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
	gf256v_fdump( stdout , signature , _SIGNATURE_BYTE ); printf("\n");
	printf("s/v: %d/%d.\n\n", sr, vr );

	for(unsigned i=0;i<TEST_RUN;i++) {
		gf256v_rand(d1,_PUB_M_BYTE);

		sr = quartz_sign( signature ,  (const uint8_t *)dsk , d1 );
		vr = quartz_verify( qp_pk , signature , d1 );


		if( ! (1 == (sr&vr)) ) {
			printf("fail:[%d]\n",i);
			gf256v_fdump( stdout , d1 , _PUB_M_BYTE ); printf("\n");
			gf256v_fdump( stdout , signature , _SIGNATURE_BYTE ); printf("\n");
			printf("s/v: %d/%d.\n", sr, vr );
			return -1;
		}
	}
	printf("sign/verify %d test success.\n\n", TEST_RUN);


	return 0;
}

