// 큐 클래스
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include "Queue.h"

CQueLinear::CQueLinear()
{
	m_pBuf	= nullptr;
	m_iRear	= 0;
	m_iWidth= 0;
}

CQueLinear::CQueLinear(int iWidth)
{
	m_iRear	= 0;
	m_iWidth= iWidth;

	m_pBuf	= new int[m_iWidth+1];				// End Pointer 하나 더 추가...
	memset(m_pBuf, 0, sizeof(int)*(m_iWidth+1));
}

CQueLinear::~CQueLinear()
{
	if(m_pBuf)									// 동적으로 생성한 버퍼 해제
	{
		delete [] m_pBuf;
		m_pBuf = nullptr;
	}
}

int CQueLinear::Enqueue(int iIn)				// 큐에 데이터 추가
{
	if( m_iRear == m_iWidth)					// 남아 있는 공간이 없으면 채우지 못함
		return -1;								// Failed

	m_pBuf[m_iRear++] = iIn;
	return 0;
}

int CQueLinear::Dequeue(int* iOut)				// 큐에서 데이터 가져오기
{
	if(0 == m_iRear)							// 버퍼가 비워져 있는 경우
		return -1;								// Failed

	*iOut = m_pBuf[0];
	
	int i=0;
	for(; i < m_iRear; ++i)
		*(m_pBuf+i) = *(m_pBuf+i+1);			// 한 단계씩 앞 자리로 이동

	*(m_pBuf+i) = 0;							// 마지막 자리 0으로 초기화
	--m_iRear;									//Rear 위치 이동

	return 0;
}

