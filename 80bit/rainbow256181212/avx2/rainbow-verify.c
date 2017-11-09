
#include <stdio.h>

#include "rainbow_config.h"
#include "rainbow.h"

#include "utils.h"
#include "hash_utils.h"

int main( int argc , char ** argv )
{
	printf( "%s\n", _S_NAME );

        printf("sk size: %lu\n", sizeof(rainbow_key) );
        printf("pk size: %d\n", _PUB_KEY_LEN );
        printf("digest size: %d\n", _PUB_M_BYTE );
        printf("signature size: %d\n\n", _PUB_N_BYTE );

	if( 4 != argc ) {
                printf("Usage:\n\n\trainbow-verify pk_file_name signature_file_name message_file_name\n\n");
                return -1;
        }

	uint8_t pk[_PUB_KEY_LEN];
	unsigned char digest[_PUB_M_BYTE];
	unsigned char signature[_PUB_N_BYTE];
	unsigned char digest_ck[_PUB_M_BYTE] = {0};
	unsigned char * ptr;
	FILE * fp;
	int r;

	//fp = fopen("pk.txt", "r");
	fp = fopen( argv[1] , "r");
	if( NULL == fp ) {
		printf("fail to open public key file.\n");
		return -1;
	}
	ptr = (unsigned char *)pk;
	r = byte_fget( fp ,  ptr , _PUB_KEY_LEN );
	fclose( fp );
	if( _PUB_KEY_LEN != r ) {
		printf("fail to load key file.\n");
		return -1;
	}

	//fp = fopen("signature.txt", "r");
	fp = fopen( argv[2] , "r");
	if( NULL == fp ) {
		printf("fail to open signature file.\n");
		return -1;
	}
	ptr = (unsigned char *)signature;
	r = byte_fget( fp ,  ptr , _PUB_N_BYTE );
	fclose( fp );
	if( _PUB_N_BYTE != r ) {
		printf("fail to load signature file.\n");
		return -1;
	}

	r = sha256_chain_file( digest , _PUB_M_BYTE , argv[3] );
	if( 0 != r ){
		printf("fail to generate message hash.\n");
		return -1;
	}

	rainbow_pubmap( digest_ck , pk , signature );

	unsigned char cc = 0;
	for(unsigned i=0;i<_PUB_M_BYTE;i++) {
		cc |= (digest_ck[i]^digest[i]);
	}

	if( 0 == cc ) {
		printf("%s verification success.\n" , _S_NAME );
		return 0;
	} else {
		printf("Verification fail.\n" );
		return -1;
	}
}

