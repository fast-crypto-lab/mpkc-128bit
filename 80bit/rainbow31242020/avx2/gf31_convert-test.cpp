#include "utils.h"
#include "gf31_convert.h"

#include "stdlib.h"


int main()
{
	unsigned char digest[64];
	unsigned char v1[56];

	unsigned char pstring[64];
	unsigned char v2[56];

	for(unsigned i=0;i<64;i++) digest[i] = rand()&0xff;

	byte_fdump( stdout , "digest: " , digest , 34 ); puts("");

	gf31_from_digest( v1 , digest , 56 );

	byte_fdump( stdout , "v1: " , v1 , 56 ); puts("");

	gf31_quick_pack( pstring , v1 , 56 );
	byte_fdump( stdout , "qpack: " , pstring , 20 ); puts("");

	gf31_quick_unpack( v2 , pstring , 56 );
	byte_fdump( stdout , "v2: " , v2 , 56 ); puts("");

	unsigned eq = 0;
	for(unsigned i=0;i<56;i++) {
		eq += v1[i] - v2[i];
	}

	printf("check: %d,  (0 is correct)\n", eq );
	printf("\n\n");

	return 0;
}
