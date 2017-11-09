
#include "hash_utils.h"

#include "openssl/sha.h"


#define _BUFFER_SIZE 4096

int sha256_file( unsigned char * digest , FILE * fp )
{
	unsigned char buffer[_BUFFER_SIZE] ={0};
	int nbyte = 0;
	SHA256_CTX sha256;
	SHA256_Init( &sha256 );
	int is_read = -1;
	while( ( nbyte = fread(buffer,1,_BUFFER_SIZE,fp) ) ) { SHA256_Update( &sha256 , buffer , nbyte ); is_read = 0; }
	SHA256_Final( digest , &sha256 );
	return is_read;
}

int sha256_chain( unsigned char * d2 , const unsigned char * d1 )
{
	SHA256_CTX sha256;
	SHA256_Init( &sha256 );
	SHA256_Update( &sha256 , d1 , 32 );
	SHA256_Final( d2 , &sha256 );
	return 0;
}

int sha256_chain_file( unsigned char * digest , unsigned n_digest , const char * f_name )
{
	unsigned char hash[32] = {0};
	FILE * fp = fopen( f_name , "rb");
        if( NULL == fp ) return -1;
	sha256_file( hash , fp );
	fclose( fp );

	if( 32 > n_digest ) {
		for(unsigned i=0;i<n_digest;i++) digest[i] = hash[i];
		return 0;
	} else {
		for(unsigned i=0;i<32;i++) digest[i] = hash[i];
	}
	n_digest -= 32;

	while( 32 <= n_digest ) {
		sha256_chain( digest+32 , digest );

		n_digest -= 32;
		digest += 32;
	}
	if( n_digest ){
		sha256_chain( hash , digest );
		for(unsigned i=0;i<n_digest;i++) digest[32+i] = hash[i];
	}

	return 0;
}
