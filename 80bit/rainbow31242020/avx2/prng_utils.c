
#include "prng_utils.h"

#include <openssl/rand.h>

#include <stdio.h>
#include <stdlib.h>


#ifdef _DEBUG_PRNG_

#define _BUFFER_SIZE 4096*128

static unsigned n_generated = 0;
static unsigned char _generated[_BUFFER_SIZE];

static unsigned user_source = 0;
static unsigned char _source[_BUFFER_SIZE];

#endif

void prng_bytes( unsigned char * a , unsigned _num_byte )
{
#ifdef _DEBUG_PRNG_
	if( user_source ) {
		for(unsigned i=0;i < _num_byte;i++) a[i] = _source[(n_generated+i)%user_source];
	}
	else RAND_bytes( a , _num_byte );

	for(unsigned i=0;i<_num_byte;i++) {
		_generated[((n_generated+i)%((unsigned)_BUFFER_SIZE))] = a[i];
	}
	n_generated = ((n_generated+_num_byte)%((unsigned)_BUFFER_SIZE));
#else
	RAND_bytes( a , _num_byte );
#endif
}

void prng_seed( const unsigned char * a , unsigned _num_byte )
{
	RAND_seed( a , _num_byte );
}



int prng_seed_file( const char * file_name )
{

	FILE * fp = fopen( file_name , "rb" );
	if( NULL == fp ) return -1;

#ifdef _DEBUG_PRNG_
	user_source = fread( _source , 1 , _BUFFER_SIZE , fp );
#else
	unsigned char seed[32] = {0};
	unsigned r = fread( seed , 1 , 32 , fp );
	prng_seed( seed , r );
#endif
	fclose( fp );
	return 0;
}


#ifdef _DEBUG_PRNG_
unsigned prng_dump_generated( unsigned char * buffer , unsigned size_buffer )
{
	unsigned r = 0;
	for(unsigned i=0;i<n_generated;i++) {
		if( size_buffer == i ) break;
		buffer[i] = _generated[i];
		r++;
	}
	return r;
}
#endif
