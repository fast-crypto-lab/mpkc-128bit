
#include <stdio.h>

#include "rainbow_config.h"
#include "rainbow.h"

#include "utils.h"
#include "prng_utils.h"

int main( int argc , char ** argv )
{
	printf( "%s\n", _S_NAME );

        printf("sk size: %lu\n", sizeof(rainbow_key) );
        printf("pk size: %d\n", _PUB_KEY_LEN );
        printf("digest size: %d\n", _PUB_M_BYTE );
        printf("signature size: %d\n\n", _PUB_N_BYTE );

	if( 3 != argc ) {
		printf("Usage:\n\n\trainbow-genkey pk_file_name sk_file_name\n\n");
		return -1;
	}

	if( 0 != prng_seed_file( "/dev/random" ) ) printf("load prng seed fail.\n");

	rainbow_key sk;
	uint8_t qp_pk[_PUB_KEY_LEN];
	unsigned char * ptr;
	FILE * fp;
	//int r = 0;

	rainbow_genkey(qp_pk,&sk);
#if 0
	if( 0 != r ) {
		printf("%s genkey fails.\n", _S_NAME );
		return -1;
	}
#endif

	//fp = fopen("pk.txt", "w+");
	fp = fopen( argv[1] , "w+");
	if( NULL == fp ) {
		printf("fail to open public key file.\n");
		return -1;
	}
	ptr = qp_pk;
	byte_fdump( fp , _S_NAME " public key" , ptr , _PUB_KEY_LEN );
	fclose( fp );

	//fp = fopen("sk.txt", "w+");
	fp = fopen( argv[2] , "w+");
	if( NULL == fp ) {
		printf("fail to open secret key file.\n");
		return -1;
	}
	ptr = (unsigned char *)&sk;
	//sprintf(msg,"%s secret key", name);
	byte_fdump( fp ,  _S_NAME " secret key" , ptr , sizeof(rainbow_key) );
	fclose( fp );

	printf("generate %s pk/sk success.\n" , _S_NAME );

	return 0;
}

