
#ifndef _GUI_H_
#define _GUI_H_

#include "string.h"
#include "gui_config.h"

#include "blas.h"

//#define _DEBUG_MPKC


#ifdef  __cplusplus
extern  "C" {
#endif

#define KEYNAME(gf,ext,v,a) gui_##gf_##ext_##v_##a

#define BGF_SIZE GUI_BGF_SIZE
#define C_DEG    GUI_C_DEG
#define C_TERMS  GUI_C_TERMS


/// X^17 + X^16 + X^8 + X^5 + X^4 + X^2 + X + 1
struct gui_cpoly {
	uint8_t vo[_V][3*BGF_SIZE];
	uint8_t vv[_V*(_V+1)/2][BGF_SIZE];
	uint8_t c_eq[BGF_SIZE*C_TERMS];
};


typedef struct gui_cpoly cpoly_t;

struct KEYNAME(_GF,_EXT,_V,_A) {
	uint8_t mat_t[_SEC_M * _SEC_M_BYTE];
	uint8_t vec_t[_SEC_M_BYTE];
	uint8_t mat_s[_PUB_N * _PUB_N_BYTE];
	uint8_t vec_s[_PUB_N_BYTE];

	cpoly_t cpoly;
};

typedef struct KEYNAME(_GF,_EXT,_V,_A) gui_key;


static inline
void gui_fdump( FILE *fp, const gui_key * key ) {
	gf16mat_fdump(fp,key->mat_t,_SEC_M_BYTE,_SEC_M); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_t,_SEC_M_BYTE); fprintf(fp,"\n");

	gf16mat_fdump(fp,key->mat_s,_PUB_N_BYTE,_SEC_N); fprintf(fp,"\n");
	gf256v_fdump(fp,key->vec_s,_PUB_N_BYTE); fprintf(fp,"\n");

}



///////////////////////////////////


void gui_genkey( uint8_t * pk , gui_key * sk );


#define _LEN_SHA256_ 32

unsigned gui_secmap( uint8_t * w , const gui_key * sk , const uint8_t * z , const uint8_t seed[_LEN_SHA256_]);



#include "mpkc.h"

#define gui_pubmap mpkc_pub_map_gf4

#define mpkc_interpolate mpkc_interpolate_gf4


///////////////////////////////////


#define _DEBUG_GUI_

#ifdef _DEBUG_GUI_


void gui_central_map( uint8_t * r , const gui_key * key , const uint8_t * a );

unsigned gui_ivs_central_map( uint8_t * r , const gui_key * key , const uint8_t * a , const uint8_t * vinegar );


void gui_pubmap_seckey( uint8_t * z , const gui_key * sk , const uint8_t * w );

void gui_genkey_debug( gui_key * pk , gui_key * sk );


#endif /// _DEBUG_GUI_



#ifdef  __cplusplus
}
#endif


#endif
