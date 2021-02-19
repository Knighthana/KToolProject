#include <stdio.h>
int main(int argc, char* argv[])
{
	char baka[5] = {'b','a','k','a','\0'};
	int hentai[7] = {'h','e','t','a','i','\0'};
	printf("size of int on this machine is %lu\n", sizeof(int));
	printf("size of char on this machine is %lu\n", sizeof(char));
	printf("\'baka\' in char array, there should be \'baka\' and it is: %s\n", baka);
	printf("\'hentai\' in int array, there should be \'hentai\' but it is: %s\n", hentai);
	printf("but if \'hentai\' is compressed into an int array, it should work\n");
	hentai[0] = 1953391976;
	/* 0111,0100   0110,1110   0110,0101   0110,1000 */
	hentai[1] = 26977;
	/* 0000,0000   0000,0000   0110,1001   0110,0001 */
	printf("and it will printf a \'hentai\' like: %s\n", hentai);
	hentai[0] = 1751477876;
	/* 0110,1000   0110,0101   0110,1110   0111,0100 */
	hentai[1] = 1634271232;
	/* 0110,0001   0110,1001   0000,0000   0000,0000 */
	printf("and a more interesting thing is that, if you set it like order of H-E-N-T-A-I, it will be: %s\n", hentai);
	return 0 ;
}
