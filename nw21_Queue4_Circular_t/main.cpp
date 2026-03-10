//  Main() 함수
//
#include <vector>
#include <iostream>
#include <windows.h>

#include "QueCircular.h"

//int main()
//{
//
//	std::cout<< "간단한 원형큐 프로그램.\n\n";
//
//	int i,j;
//
//	TqueCircular<int>*	pQueue = new TqueCircular<int>(20);
//
//	
//	for(i=0; i<10; ++i)
//	{
//		for(j=0; j<30; ++j)
//		{
//			pQueue->Enqueue(i*30 + j);
//		}
//
//		for(j=0; j<30; ++j)
//		{
//			int iVal = 0;
//			pQueue->Dequeue(&iVal);
//
//			printf("%d\n",iVal);
//		}
//	}
//
//	delete pQueue;
//	return 0;
//}



struct NwMsg
{
	unsigned int socket;
	unsigned int nMsg;
};

int main()
{
	std::cout<< "간단한 원형큐 프로그램.\n\n";

	int i,j;

	TqueCircular<NwMsg>*	pQueue = new TqueCircular<NwMsg>(20);

	
	for(i=0; i<10; ++i)
	{
		for(j=0; j<30; ++j)
		{
			NwMsg	nwMsg;
			nwMsg.socket = i;
			nwMsg.nMsg = i*30 + j;
			pQueue->Enqueue(&nwMsg);
		}

		for(j=0; j<30; ++j)
		{
			NwMsg	nwMsg;
			pQueue->Dequeue(&nwMsg);

			printf("%d  %d\n", nwMsg.socket, nwMsg.nMsg);
		}
	}

	delete pQueue;
	return 0;
}

