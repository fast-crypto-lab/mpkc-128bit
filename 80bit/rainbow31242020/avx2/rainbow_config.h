#ifndef _RAINBOW_CONFIG_H_
#define _RAINBOW_CONFIG_H_

/// (36,28,28) (64,32,48) (64,40,40)


#ifndef _V1
#define _V1 24
#endif

#ifndef _O1
#define _O1 20
#endif

#ifndef _O2
#define _O2 20
#endif


#define _GFSIZE 31

#define STR1(x) #x
#define THE_NAME(gf,v1,o1,o2) "RAINBOW(" STR1(gf) "," STR1(v1) "," STR1(o1) "," STR1(o2) ")"

#define _S_NAME THE_NAME(_GFSIZE,_V1,_O1,_O2)

#define _V2 ((_V1)+(_O1))


#define _RAINBOW_31

#ifdef _RAINBOW_31

#define _PUB_N  (_V1 + _O1 + _O2)
#define _PUB_M  (_O1 + _O2)
#define _SEC_N (_PUB_N)

#define _PUB_N_BYTE  _PUB_N
#define _PUB_M_BYTE  _PUB_M

#define _GF31_PACK_SIZE(N) (((N)/3)*2+((N)%3))

#define _DIGEST_BYTE (((_PUB_M/5)*3)+((_PUB_M%5)/2)+((_PUB_M%5)%2))

#define _SIGNATURE_BYTE _GF31_PACK_SIZE(_PUB_N)

#else

error

#endif


#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N+1)

#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))

#define _PUB_KEY_LEN_PACK _GF31_PACK_SIZE(_PUB_KEY_LEN)

#endif
