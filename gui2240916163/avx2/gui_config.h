#ifndef _GUI_CONFIG_H_
#define _GUI_CONFIG_H_


//#define _GUI_4_112_A8_V16_D17_
//#define _GUI_4_120_A8_V8_D17_
#define _GUI_2_240_D9_V16_A16


#ifdef _GUI_4_112_A8_V16_D17_

#define _PUB_N  (128)
#define _PUB_M  (104)
#define _PUB_N_BYTE (32)
#define _PUB_M_BYTE (26)

#define _SEC_N (128)
#define _SEC_M (112)
#define _SEC_M_BYTE ((_SEC_M+3)/4)

#define _GF 4
#define _EXT (112)
#define _A (8)
#define _V (16)
#define _K (2)

#define GUI_BGF_SIZE (28)

#elif defined _GUI_4_120_A8_V8_D17_

#define _PUB_N  (128)
#define _PUB_M  (112)
#define _PUB_N_BYTE (32)
#define _PUB_M_BYTE (28)

#define _SEC_N (128)
#define _SEC_M (120)
#define _SEC_M_BYTE ((_SEC_M+3)/4)

#define _GF 4
#define _EXT (120)
#define _A (8)
#define _V (8)
#define _K (2)

#define GUI_BGF_SIZE (30)

#elif defined _GUI_2_240_D9_V16_A16

#define _PUB_N  (256)
#define _PUB_M  (224)
#define _PUB_N_BYTE (32)
#define _PUB_M_BYTE (28)

#define _SEC_N (256)
#define _SEC_M (240)
#define _SEC_M_BYTE (30)

#define _GF 2
#define _EXT (240)
#define _A (16)
#define _V (16)
#define _K (3)

#define GUI_BGF_SIZE (30)


#else
error here.
#endif


#define _BATCH 1
//#define _BATCH 16


#define _MINUS_BYTE (_SEC_M_BYTE-_PUB_M_BYTE)
#define _VINEGAR_BYTE (_PUB_N_BYTE-_SEC_M_BYTE)


#define _SIGNATURE_BYTE (_PUB_M_BYTE + (_PUB_N_BYTE-_PUB_M_BYTE)*(_K))



#define TERMS_QUAD_POLY(N) (((N)*(N+1)/2)+N)
#define TERMS_QUAD_POLY_GF2(N) (((N)*(N-1)/2)+N)


#if 2 == _GF
#define _PUB_KEY_LEN (TERMS_QUAD_POLY_GF2(_PUB_N)*(_PUB_M_BYTE))
#else
#define _PUB_KEY_LEN (TERMS_QUAD_POLY(_PUB_N)*(_PUB_M_BYTE))
#endif

#if 2 == _GF
#define GUI_C_DEG (9)
#define GUI_C_TERMS (9)
#else
#define GUI_BGF_SIZE_16 (32)
#define GUI_C_DEG (17)
#define GUI_C_TERMS (8)
#endif



#endif
