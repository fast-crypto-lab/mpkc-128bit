#include "utils.h"


int main()
{
	unsigned char vv[256];

	for(int i=0;i<5;i++) vv[i] = i;
	byte_fdump( stdout , "def inp: " , vv , 5 );
	printf("\n\n");


	int ii = 0;

	ii = byte_fget( stdin , vv , 256 );

	printf("\n%d input got.\n" , ii );
	if( 0 > ii ) return -1;

	printf("input:\n");
	byte_fdump( stdout , "my inp: " , vv , ii );
	printf("\n\n");

	return 0;
}
