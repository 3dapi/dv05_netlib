//  Main() 함수
//

#include <iostream>
#include <windows.h>

#include "Queue.h"

int main()
{
	std::cout<< "간단한 원형큐 프로그램.\n\n";

	int i,j;

	CQueCircular*	pQueue = new CQueCircular(20);

	
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
