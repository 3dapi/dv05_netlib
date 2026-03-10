// 큐 응용 클래스
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include "Queue.h"
#include "QueueApp.h"

CQueueApp::CQueueApp() : m_pQueue(0) {}
CQueueApp::~CQueueApp(){}

int CQueueApp::Init(int iQueSize /* = MAX_QUEUE */)
{
	if(iQueSize<0)								// 큐의 크기가 작으면 실패
		return -1;

	m_pQueue = new CQueLinear(iQueSize);
	return 0;
}

int CQueueApp::Run()
{
	while(1)
	{
		printf("Queue 연습 -------------------------\n\n");
		printf("	Queue에 데이터를 추가하는 연습은 1 번키,\n"
				"	Queue의 데이터를 꺼내오는 언습은 2 번키,\n"
				"	Queue의 크기를 조정하려면 3 번키,\n"
				"	프로그램 종료는 Q 키 입니다.\n");

		char	sMsg[8]={0};
		InputString(sMsg, 8);
		system("cls");

		if('q' == sMsg[0] || 'Q' == sMsg[0])
		{
			printf("프로그램 종료\n");
			break;
		}
		else if('1' == sMsg[0])	// Enque 응용 모드
			EnqueuingMode();

		else if('2' == sMsg[0])	// Enque 응용 모드
			DequeuingMode();
	}

	Destroy();
	return 0;
}

void CQueueApp::Destroy()
{
	if(m_pQueue)
	{
		delete m_pQueue;
		m_pQueue = nullptr;
	}
}

void CQueueApp::EnqueuingMode()
{
	printf("Enqueuing Mode...\n");

	while(1)
	{
		printf("\n\n");
		printf("	큐에 입력할 글자를 치세요\n"
				"	이전메뉴는 Q키입니다.\n");

		char	sMsg[256]={0};
		InputString(sMsg, 256);
		system("cls");

		if('q' == sMsg[0] || 'Q' == sMsg[0])
			break;


		int iSize = strlen(sMsg);
		int iRet = m_pQueue->Enqueue(sMsg[0]);

		if(FAILED(iRet))
		{
			char*	p = sMsg;
			p += iSize - iRet;
			printf("\n\n	큐의 공간이 부족해 전부 채워지 못했습니다.\n");
			printf(		"	남은 데이터: %s\n", p);
		}
	}
}

void CQueueApp::DequeuingMode()
{
	printf("Dequeuing Mode...\n");

	while(1)
	{
		printf("\n\n	큐에서 데이터 를 꺼내오려면 Enter 키를 입력하세요\n"
					"	이전메뉴는 Q키입니다.\n");

		char	sMsg[256]={0};
		InputString(sMsg, 256);
		system("cls");

		if('q' == sMsg[0] || 'Q' == sMsg[0])
			break;


		int iVal= 0;
		int hr  = m_pQueue->Dequeue(&iVal);

		if(FAILED(hr))
		{
			printf("Queue가 비어있습니다.\n\n");
			continue;
		}

		printf("\n\n	가져온 글자: %c\n", iVal);
	}
}

void CQueueApp::InputString(char* sMsg, int iSize, FILE* fp)
{
	char sTemp[512]={0};
	char* p = sTemp;

	fgets(sTemp, 512, fp);

	for(int i=0; i<512, *p !=0; ++i, ++p)
	{
		if('\n' == *p || '\r' == *p)
		{
			*p = 0;
			break;
		}
	}

	memcpy(sMsg, sTemp, iSize);
}

