/* 这个文件用于测试本机的Linux SGR情况 */

#include <stdio.h>

int main(int argc, char* argv[])
{
	int i; 
	char sgrseq[7] = {'\033', '[' ,'3', '0', 'm', '\0','\0'};
	char prtseq[6] = {'3', '0', 'm', '\n','\0', '\0'};
	for(i=0; i<8; i++){ /* 'i' can be set to 8 or 9, but dont kown what it mean */
		printf("\e[40m");
		fflush(stdout);
		sgrseq[2] = '3';
		sgrseq[3] = '0' + i;
		prtseq[0] = '3';
		prtseq[1] = '0' + i;
		printf("%s", sgrseq);
		printf("%s", prtseq);
		sgrseq[2] = '9';
		sgrseq[3] = '0' + i;
		prtseq[0] = '9';
		prtseq[1] = '0' + i;
		printf("%s", sgrseq);
		printf("%s", prtseq);
		printf("\e[97m"); /* set to noticeable frontcolor */
		fflush(stdout);
		sgrseq[2] = '4';
		sgrseq[3] = '0' + i;
		prtseq[0] = '4';
		prtseq[1] = '0' + i;
		printf("%s", sgrseq);
		printf("%s", prtseq);
	}
	/* 40 and 100 */
	printf("\e[40mthis is 40m\n");
	printf("\e[100mthis is 100m\n");
	/* 47 and 107 */
	printf("\e[30m\e[47mthis is 47m\n");
	printf("\e[30m\e[107mthis is 107m\n");
	printf("\e[0mcolor test over\n");
	/* 1 and 21 */
	printf("\e[1mthis is 1m\n");
	printf("\e[21mthis is 21m\n");
	/* 2 and 22 */
	printf("\e[0mfollowing are 2m and 22m\n");
	printf("\e[2mthis is 2m\n");
	printf("\e[22mthis is 22m\n");
	/* 3 and 23 */
	printf("\e[0mfollowing are 3m and 23m\n");
	printf("\e[3mthis is 3m\n");
	printf("\e[23mthis is 23m\n");
	/* 4 and 24 */
	printf("\e[0mfollowing are 4m and 24m\n");
	printf("\e[4mthis is 4m\n");
	printf("\e[24mthis is 24m\n");
	/* 5 and 25 */
	printf("\e[0mfollowing are 5m and 25m\n");
	printf("\e[5mthis is 5m\n");
	printf("\e[25mthis is 25m\n");
	/* 7 and 27 */
	printf("\e[7mthis is 7m\n");
	printf("\e[27mthis is 27m\n");
	/* 38 and 39 */
	printf("\e[38mthis is 38m\n");
	printf("\e[39mthis is 39m\n");
	/* set to default */
	printf("\e[0m");
	fflush(stdout);
	return 0;
}
