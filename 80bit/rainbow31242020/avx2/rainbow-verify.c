
#include <stdio.h>

#include "rainbow_config.h"
#include "rainbow.h"

#include "utils.h"
#include "hash_utils.h"
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

	if( 4 != argc ) {
                printf("Usage:\n\n\trainbow-verify pk_file_name signature_file_name file_name_to_be_signed\n\n");
                return -1;
        }

	uint8_t pk[_PUB_KEY_LEN];
	uint8_t pk_input[_PUB_KEY_LEN_PACK];
	unsigned char hash[64];
	unsigned char digest[_PUB_M_BYTE];
	unsigned char signature[_PUB_N_BYTE];
	unsigned char signature_pack[_SIGNATURE_BYTE];
	unsigned char digest_ck[_PUB_M_BYTE] = {0};
	FILE * fp;
	int r;

	//fp = fopen("pk.txt", "r");
	fp = fopen( argv[1] , "r");
	if( NULL == fp ) {
		printf("fail to open public key file.\n");
		return -1;
	}
	r = byte_fget( fp ,  pk_input , _PUB_KEY_LEN_PACK );
	fclose( fp );
	if( _PUB_KEY_LEN_PACK != r ) {
		printf("fail to load key file.\n");
		return -1;
	}
	r = gf31_quick_unpack( pk , pk_input , _PUB_KEY_LEN );
	if( 0 != gf31_sanity_check( pk , _PUB_KEY_LEN ) ) {
		printf("key format fails.\n");
		return -1;
	}

	//fp = fopen("signature.txt", "r");
	fp = fopen( argv[2] , "r");
	if( NULL == fp ) {
		printf("fail to open signature file.\n");
		return -1;
	}
	//ptr = (unsigned char *)signature_pack;
	r = byte_fget( fp ,  signature_pack , _SIGNATURE_BYTE );
	fclose( fp );
	if( _SIGNATURE_BYTE != r ) {
		printf("fail to load signature file.\n");
		return -1;
	}
	gf31_quick_unpack( signature , signature_pack , _PUB_N_BYTE );
	if( 0 != gf31_sanity_check( signature , _PUB_N_BYTE ) ) {
		printf("Signature format fails.\n");
		return -1;
	}

	rainbow_pubmap( digest_ck , pk , signature );

	r = sha256_chain_file( hash , 64 , argv[3] );
	if( 0 != r ) {
		printf("fail to generate message hash.\n");
		return -1;
	}
	gf31_from_digest( digest , hash , _PUB_M_BYTE );

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

