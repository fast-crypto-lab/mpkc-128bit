#include "stdio.h"

int main()
{
  FILE * fp = fopen( "aa.txt" , "wb" );
  fprintf(fp,"abc");
  fclose(fp);
  return 0;
}
