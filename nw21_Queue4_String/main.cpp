//  Main() 함수
//

#include <iostream>
#include <windows.h>

#include "QueStr.h"
#include "QueueApp.h"

CQueueApp	g_QueApp;

int main()
{
	std::cout<< "문자열에 대한 큐 응용프로그램.\n\n";

	// 큐 응용프로그램을 초기화 한다. 큐의 최대 크기를
	// 40바이트(한글기준 20문자)로 정함

	if(FAILED(g_QueApp.Init()))
		std::cout<<"큐 응용프로그램 초기화 실패 ==>프로그램을 종료합니다.\n\n";
	
	// 응용 프로그램을 동작
	
	return g_QueApp.Run();
}
