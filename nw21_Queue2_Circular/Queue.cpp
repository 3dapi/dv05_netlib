// 큐 클래스
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include "Queue.h"

CQueCircular::CQueCircular()
{
	m_pBuf		= nullptr;
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= 0;
	m_iWidth	= 0;
}

CQueCircular::CQueCircular(int iWidth)
{
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= iWidth;
	m_iWidth	= iWidth;

	m_pBuf	= new int[m_iWidth+1];				// End Pointer 하나 더 추가...
	memset(m_pBuf, 0, sizeof(int)*(m_iWidth+1));
}

CQueCircular::~CQueCircular()
{
	if(m_pBuf)									// 동적으로 생성한 버퍼 해제
	{
		delete [] m_pBuf;
		m_pBuf = nullptr;
	}
}

int CQueCircular::Enqueue(int iIn)				// 큐에 데이터 추가
{
	if( 0 == m_iSpace)							// 남아 있는 공간이 없으면 채우지 못함
		return -1;								// Failed

	m_pBuf[m_iRear] = iIn;

	--m_iSpace;									// 빈영역 감소

	++m_iRear;
	m_iRear%= m_iWidth;							// Rear 위치 이동
	return 0;
}

int CQueCircular::Dequeue(int* iOut)			// 큐에서 데이터 가져오기
{
	if(m_iSpace == m_iWidth)					// 버퍼가 비워져 있는 경우
		return -1;								// Failed

	*iOut = m_pBuf[m_iFront];
	
	++m_iSpace;									// 빈영역 증가

	++m_iFront;
	m_iFront%= m_iWidth;						// Front 위치 이동

	return 0;
}

