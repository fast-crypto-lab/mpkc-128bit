
#include <stdio.h>

#include "rainbow_config.h"
#include "rainbow.h"

#include "utils.h"
#include "prng_utils.h"
#include "gf31_convert.h"

int main( int argc , char ** argv )
{
	printf( "%s\n", _S_NAME );

        printf("sk size (gf31): %lu\n", sizeof(rainbow_key) );
        printf("pk size (gf31): %d\n", _PUB_KEY_LEN );
        printf("digest size (gf31): %d\n", _PUB_M_BYTE );
        printf("signature size (gf31): %d\n", _PUB_N_BYTE );
        printf("sk size: %lu\n", _GF31_PACK_SIZE(sizeof(rainbow_key)) );
        printf("pk size: %d\n", _GF31_PACK_SIZE(_PUB_KEY_LEN) );
        printf("digest size: %d\n", _DIGEST_BYTE );
        printf("signature size: %d\n\n", _SIGNATURE_BYTE );

	if( 3 != argc ) {
		printf("Usage:\n\n\trainbow-genkey pk_file_name sk_file_name\n\n");
		return -1;
	}

	if( 0 != prng_seed_file( "/dev/random" ) ) {
		printf("fail to load prng seed.\n");
	}

	rainbow_key sk;
	uint8_t qp_pk[_PUB_KEY_LEN];
	//unsigned char * ptr;
	FILE * fp;
	int n_bytes = 0;
	//int r = 0;

	rainbow_genkey(qp_pk,&sk);
	printf("%s key pairs generated.\n", _S_NAME );
	//if( 0 != r ) {
	//	printf("%s genkey fails.\n", _S_NAME );
	//	return -1;
	//}

	//fp = fopen("pk.txt", "w+");
	fp = fopen( argv[1] , "w+");
	if( NULL == fp ) {
		printf("fail to open public key file.\n");
		return -1;
	}
	uint8_t pk_output[_PUB_KEY_LEN_PACK];
	n_bytes = gf31_quick_pack( pk_output , qp_pk , _PUB_KEY_LEN );
	byte_fdump( fp , _S_NAME " public key" , pk_output , n_bytes );
	fclose( fp );

	//fp = fopen("sk.txt", "w+");
	fp = fopen( argv[2] , "w+");
	if( NULL == fp ) {
		printf("fail to open secret key file.\n");
		return -1;
	}
	uint8_t sk_output[_GF31_PACK_SIZE(sizeof(rainbow_key))];
	n_bytes = gf31_quick_pack( sk_output , (unsigned char *)&sk , sizeof(rainbow_key) );
	//ptr = (unsigned char *)&sk;
	//sprintf(msg,"%s secret key", name);
	byte_fdump( fp ,  _S_NAME " secret key" , sk_output , n_bytes );
	fclose( fp );

	printf("generate %s pk/sk success.\n" , _S_NAME );

	return 0;
}

