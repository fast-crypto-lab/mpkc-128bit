
#ifndef _QUARTZ_SIG_H_
#define _QUARTZ_SIG_H_

#include "gui_config.h"

#if 2 == _GF
#include "gui_gf2.h"
#else
#include "gui.h"
#endif


#ifdef  __cplusplus
extern  "C" {
#endif


unsigned quartz_sign( uint8_t * signature , const uint8_t * sec_key , const uint8_t * digest );

unsigned quartz_verify( const uint8_t * pub_key , const uint8_t * signature , const uint8_t * digest );


#ifdef  __cplusplus
}
#endif


#endif
