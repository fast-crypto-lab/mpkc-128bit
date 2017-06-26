#ifndef _RAINBOW_CONFIG_H_
#define _RAINBOW_CONFIG_H_


//#define _RAINBOW_16
#define _RAINBOW_256

#ifdef _RAINBOW_256

#define _PUB_N  (68)
#define _PUB_M  (40)
#define _SEC_N (68)

#define _PUB_N_BYTE  _PUB_N
#define _PUB_M_BYTE  _PUB_M


#elif defined _RAINBOW_16

#define _PUB_N  (96)
#define _PUB_M  (64)
#define _SEC_N (96)

#define _PUB_N_BYTE  (48)
#define _PUB_M_BYTE  (32)

#else

error

#endif


#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N)

#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))

#endif
