#ifndef _RAINBOW_CONFIG_H_
#define _RAINBOW_CONFIG_H_

/// (40,24,24) (68,36,36) (92,48,48) (84,56,56)

#ifndef _V1
#define _V1 18
#endif

#ifndef _O1
#define _O1 12
#endif

#ifndef _O2
#define _O2 12
#endif

#define _GFSIZE 256

#define STR1(x) #x
#define THE_NAME(gf,v1,o1,o2) "RAINBOW(" STR1(gf) "," STR1(v1) "," STR1(o1) "," STR1(o2) ")"

#define _S_NAME THE_NAME(_GFSIZE,_V1,_O1,_O2)


#define _V2 ((_V1)+(_O1))

//#define _RAINBOW_16
#define _RAINBOW_256

#ifdef _RAINBOW_256

#define _PUB_N  (_V1 + _O1 + _O2)
#define _PUB_M  (_O1 + _O2)
#define _SEC_N (_PUB_N)

#define _PUB_N_BYTE  _PUB_N
#define _PUB_M_BYTE  _PUB_M

#else

error

#endif



#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N+1)

#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))

#endif
