
#include "gui_config.h"

#if 2 == _GF
#include "gui_gf2.h"
#else
#include "gui.h"
#endif


#include "crypto_hash_sha256.h"


unsigned quartz_sign( uint8_t * signature , const uint8_t * sec_key , const uint8_t * digest )
{
	static uint32_t sha256_digest[_LEN_SHA256_] __attribute__((aligned(32)));
	memcpy( sha256_digest , digest , _LEN_SHA256_ );
	uint8_t dd[_PUB_M_BYTE] __attribute__((aligned(32)));

	memset( signature , 0 , _PUB_M_BYTE );

	unsigned r = 1;
	for(unsigned i=0;i<_K;i++) {
//		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *) sha256_digest );
		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );

		memcpy( dd , sha256_digest , _PUB_M_BYTE );
		gf256v_add( dd , signature , _PUB_M_BYTE );
		r &= gui_secmap( signature , (const gui_key *) sec_key , dd , (const uint8_t *)sha256_digest );

		signature += (_PUB_N_BYTE-_PUB_M_BYTE);
	}
	return r;
}



unsigned quartz_verify( const uint8_t * pub_key , const uint8_t * signature , const uint8_t * digest )
{
	static uint32_t sha256_digest[_LEN_SHA256_] __attribute__((aligned(32)));
	memcpy( sha256_digest , digest , _LEN_SHA256_ );
	uint8_t dd[_K][((_PUB_M_BYTE+31)/32)*32]  __attribute__((aligned(32)));
	for(unsigned i=0;i<_K;i++) {
//		SHA256( (const uint8_t *)sha256_digest , SHA256_DIGEST_LENGTH , (uint8_t *) sha256_digest );
		crypto_hash_sha256( (uint8_t *)sha256_digest ,  (const uint8_t *)sha256_digest , _LEN_SHA256_ );
		memcpy( dd[i] , sha256_digest , _PUB_M_BYTE );
	}

	uint8_t temp_sig[_SIGNATURE_BYTE];
	uint8_t temp_pub[_PUB_M_BYTE] __attribute__((aligned(32)));
	memcpy( temp_sig , signature , _SIGNATURE_BYTE );
	for(int i=_K-1;i>=0;i--) {
		uint8_t * ss = temp_sig + (_PUB_N_BYTE-_PUB_M_BYTE)*i;
		gui_pubmap( temp_pub , pub_key , ss );
		gf256v_add( temp_pub , dd[i] , _PUB_M_BYTE );
		memcpy( ss , temp_pub , _PUB_M_BYTE );
	}
	return gf256v_is_zero( temp_sig , _PUB_M_BYTE );
}



