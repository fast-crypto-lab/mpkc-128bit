
#include <stdio.h>

#include "rainbow_config.h"
#include "rainbow.h"

#include "utils.h"
#include "hash_utils.h"
#include "prng_utils.h"

int main( int argc , char ** argv )
{
	printf( "%s\n", _S_NAME );

        printf("sk size: %lu\n", sizeof(rainbow_key) );
        printf("pk size: %d\n", _PUB_KEY_LEN );
        printf("digest size: %d\n", _PUB_M_BYTE );
        printf("signature size: %d\n\n", _PUB_N_BYTE );

	if( !((3 == argc) || (4 == argc)) ) {
		printf("Usage:\n\n\trainbow-sign sk_file_name file_to_be_signed [random_seed_file]\n\n");
		return -1;
	}

	if( 0 != prng_seed_file( (4==argc)? argv[3] : "/dev/random" ) ) printf("load prng seed fail.\n");

	rainbow_key sk;
	unsigned char digest[_PUB_M_BYTE];
	unsigned char signature[_PUB_N_BYTE];
	unsigned char * ptr;
	FILE * fp;
	int r = 0;

	//fp = fopen("sk.txt", "r");
	fp = fopen( argv[1] , "r");
	if( NULL == fp ) {
		printf("fail to open secret key file.\n");
		return -1;
	}
	ptr = (unsigned char *)&sk;
	r = byte_fget( fp ,  ptr , sizeof(rainbow_key) );
	fclose( fp );
	if( sizeof(rainbow_key) != r ) {
		printf("fail to load key file.\n");
		return -1;
	}

	r = sha256_chain_file( digest , _PUB_M_BYTE , argv[2] );
	if( 0 != r ) {
		printf("fail to generate message hash.\n");
		return -1;
	}

	int ri = rainbow_secmap( signature , &sk , digest );
	if( 0 != ri ) {
		printf("%s sign() fails.\n", _S_NAME );
		return -1;
	}

	byte_fdump( stdout , _S_NAME " signature"  , signature , _PUB_N_BYTE );
	printf("\n");

#ifdef _DEBUG_PRNG_
	printf("\ndigest of singed file[%d] ", _PUB_M_BYTE );
	byte_fdump( stdout , "" , digest , _PUB_M_BYTE );
	printf("\n");

	unsigned char randomness[4096*128];
	unsigned n_rnd = prng_dump_generated( randomness , 4096*128 );
	printf("\nused randomness[%d] ", n_rnd);
	byte_fdump( stdout , "" , randomness , n_rnd );
	printf("\n");
#endif
	return 0;
}

