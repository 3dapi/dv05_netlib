//  Main() 함수
//

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>




#include "QueStr.h"

int main()
{
	srand( (unsigned)time( nullptr ) );
	
	std::cout<< "Ling Buffer 연습.\n\n";

	int i;
	CQueStr*	pQueue = new CQueStr(45);

	char	str[] =
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\

		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\

		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		"12345678901234567890abcdefghijabcdefghij"\
		;

	printf("         12345678901234567890abcdefghijabcdefghij\n");

	for(i=0; i<1024; ++i)
	{
		char	sBuf[128]={0};
		int		iSize = 10 + rand()%20;

		strncpy(sBuf + 1, str+i, iSize);
		iSize = strlen(sBuf+1) +1;

		sBuf[0] = iSize;
		pQueue->Enqueue(sBuf, sBuf[0]);

		memset(sBuf, 0, sizeof(sBuf));
		pQueue->Dequeue(sBuf, &iSize);

		iSize -= 1;

		printf("%3d, (%2d)%s\n", i, iSize, sBuf+1);
	}
//	pQueue->Dequeue();

	delete pQueue;

	return 0;
}
