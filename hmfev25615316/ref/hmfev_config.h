#ifndef _HMFEV_CONFIG_H_
#define _HMFEV_CONFIG_H_

//#define _HMFEV_3_2_64_
//#define _HMFEV_3_2_128_
//#define _HMFEV_3_2_72_
#define _HMFEV_3_2_120_

#if defined _HMFEV_3_2_120_
#define _PUB_N  (61)
#define _PUB_M  (45)
#define _SEC_N (61)
#define _SEC_M (45)
#define _GF (256)
#define _EXT (15)
#define _K (3)
#define _A (0)
#define _V (16)
#elif defined(_HMFEV_3_2_72_)
#define _PUB_N  (39)
#define _PUB_M  (27)
#define _SEC_N (39)
#define _SEC_M (27)
#define _GF (256)
#define _EXT (9)
#define _K (3)
#define _A (0)
#define _V (12)
#elif defined(_HMFEV_3_2_64_)
#define _PUB_N  (64)
#define _PUB_M  (40)
#define _SEC_N (64)
#define _SEC_M (48)
#define _GF (16)
#define _EXT (16)
#define _K (3)
#define _A (8)
#define _V (16)
#elif defined(_HMFEV_3_2_128_)
#define _PUB_N  (100)
#define _PUB_M  (64)
#define _SEC_N (100)
#define _SEC_M (96)
#define _GF (16)
#define _EXT (32)
#define _K (3)
#define _A (32)
#define _V (4)
#else
make some error here.
#endif


#if 256 == _GF
#define HMFEV_BGF_SIZE (_EXT)
#define _PUB_N_BYTE (_PUB_N)
#define _PUB_M_BYTE (_PUB_M)
#define _SEC_N_BYTE (_SEC_N)
#define _SEC_M_BYTE (_SEC_M)
#define _A_BYTE _A
#define _V_BYTE _V
#else
#define HMFEV_BGF_SIZE ((_EXT)/2)
#define _PUB_N_BYTE ((_PUB_N+1)/2)
#define _PUB_M_BYTE ((_PUB_M+1)/2)
#define _SEC_N_BYTE ((_SEC_N+1)/2)
#define _SEC_M_BYTE ((_SEC_M+1)/2)
#define _A_BYTE (_A/2)
#define _V_BYTE (_V/2)
#endif

#define HMFEV_TERMS_PER_CPOLY (10)


#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N)

#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))


#endif
