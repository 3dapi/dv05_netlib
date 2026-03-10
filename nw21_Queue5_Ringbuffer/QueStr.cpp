// 큐 클래스
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include "QueStr.h"

CQueStr::CQueStr()
{
	m_sBuf		= nullptr;
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= 0;
	m_iWidth	= 0;
}

CQueStr::CQueStr(int iWidth)
{
	m_sBuf		= nullptr;
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= iWidth;
	m_iWidth	= iWidth;

	m_sBuf	= new BYTE[m_iWidth];
	memset(m_sBuf, 0, sizeof(BYTE)*m_iWidth);
}

CQueStr::~CQueStr()
{
	if(m_sBuf)									// 동적으로 생성한 버퍼 해제
	{
		delete [] m_sBuf;
		m_sBuf = nullptr;
	}
}

int CQueStr::Enqueue(void* sIn,int iSize/*=1*/)	// 큐에 데이터 추가
{
	if( 2>= m_iSpace || iSize>m_iSpace)			// 남아 있는 공간이 없거나 입력 사이즈보다 작으면
		return -1;								// 실패

	BYTE*	pIn = (BYTE*)sIn;

	for(int i=0; i<iSize; ++i)
	{
		*(m_sBuf + m_iRear) = *(pIn+i);			// 데이터 복사, Rear 위치 이동

		++m_iRear;
		m_iRear %=m_iWidth;
	}

	m_iSpace -= iSize;

	return 0;
}

int CQueStr::Dequeue(void* sOut,int* pSize/*=1*/)	// 큐에서 데이터 가져오기
{
	if(m_iSpace >= (m_iWidth-2) )				// 버퍼가 비워져 있는 경우
		return -1;

	int iSize = m_sBuf[m_iFront];				// Front의 위치는 길이

	BYTE*	pOut = (BYTE*)sOut;

	for(int i=0; i<iSize; ++i)
	{
		*(pOut+i) = *(m_sBuf + m_iFront);		// 데이터 복사
		*(m_sBuf + m_iFront) =0;				// 복사되면 큐의 내용을 0으로 초기화

		++m_iFront;
		m_iFront%=m_iWidth;						// Front위치 이동
	}

	m_iSpace += iSize;

	*pSize = iSize;								// 가져온 문장의 길이를 반환

	return 0;
}

void CQueStr::Clear()							// 큐의 내용을 전부 초기화
{
	m_iRear	= 0;
	memset(m_sBuf, 0, sizeof(BYTE)*(m_iWidth+1));
}

int CQueStr::GetWidth()							// 큐의 크기 반환
{
	return m_iWidth;
}

int CQueStr::GetRemain()						// 큐에 남아 있는 공간 반환
{
	return (m_iWidth - m_iRear);
}

void CQueStr::Resize(int iSize)					// 큐의 크기 재조정
{
	BYTE* sBuf = new BYTE[iSize];				// End Pointer 하나 더 추가
	memset(sBuf, 0, sizeof(BYTE)* (iSize));

	if(iSize<=m_iWidth)							// 생성된 버퍼가 이전보다 작을 경우
	{											// 데이터 유실될 수 있음
		for(int i=0; i<iSize; ++i)
			*(sBuf++) = *(m_sBuf++);
	}

	else										// 생성된 버퍼가 이전보다 클 경우
	{											// 데이터 유실 없음
		for(int i=0; i<m_iWidth; ++i)
			*(sBuf++) = *(m_sBuf++);
	}

	if(m_sBuf)
		delete [] m_sBuf;
	
	m_sBuf = sBuf;								// 새로운 버퍼 포인터 설정
}

