#ifndef _CRYPTP_HASH_SHA256_H_
#define _CRYPTP_HASH_SHA256_H_



#if defined(_NO_OPENSSL_)

#include "sha256.h"

static inline
void crypto_hash_sha256( unsigned char * h, const unsigned char * m,unsigned long long mlen)
{
   sha256_context ctx;
   sha256_starts( & ctx );
   sha256_update( & ctx , m , mlen );
   sha256_finish( & ctx , h );
}

#else

#include <openssl/sha.h>

static inline
void crypto_hash_sha256( unsigned char * h, const unsigned char * m,unsigned long long mlen)
{
	SHA256( m , mlen , h );
}

#endif

#endif /* _CRYPTP_HASH_SHA256_H_ */
