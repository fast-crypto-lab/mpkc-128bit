#ifndef _PFLASH_CONFIG_H_
#define _PFLASH_CONFIG_H_


//#define _PFLASH_80_
#define _PFLASH_128_


#ifdef _PFLASH_80_

#define _PUB_N  (61)
#define _PUB_M  (40)
#define _SEC_N (62)

#elif defined _PFLASH_128_

#define _PUB_N  (95)
#define _PUB_M  (64)
#define _SEC_N (96)

#else

#endif

//#define _BYTE_FFT_

#ifdef _BYTE_FFT_
#define _BATCH_ (16)
#else
#define _BATCH_ (1)
#endif

#define _PUB_N_BYTE ((_PUB_N+1)/2)
#define _PUB_M_BYTE ((_PUB_M+1)/2)


#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N)

#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))

#endif
