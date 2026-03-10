// 큐 클래스
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include "QueStr.h"

CQueStr::CQueStr()
{
	m_sBuf	= nullptr;
	m_iRear	= 0;
	m_iWidth= 0;
}

CQueStr::CQueStr(int iWidth)
{
	m_iRear	= 0;
	m_iWidth= iWidth;

	m_sBuf	= new char[m_iWidth+1];				// End Pointer 하나 더 추가...
	memset(m_sBuf, 0, sizeof(char)*(m_iWidth+1));
}

CQueStr::~CQueStr()
{
	if(m_sBuf)									// 동적으로 생성한 버퍼 해제
	{
		delete [] m_sBuf;
		m_sBuf = nullptr;
	}
}

int CQueStr::Enqueue(char* sIn,int iSize/*=1*/)	// 큐에 데이터 추가
{
	if(0== iSize)
		return 0;

	if( m_iRear == m_iWidth)					// 남아 있는 공간이 없으면 채우지 못함
		return iSize;

	int iRet =0;								// 반환 값
	int	iRemain = m_iWidth - m_iRear;			// 남은 공간 계산

	if(iSize>iRemain)							// 반환 값 설정
	{
		iRet  = iSize-iRemain;
		iSize = iRemain;
	}
	
	for(int i=0; i<iSize; ++i)
		*(m_sBuf + m_iRear++) = *(sIn+i);		// 데이터 복사, Rear 위치 이동

	return iRet;
}

int CQueStr::Dequeue(char* sOut,int iSize/*=1*/)	// 큐에서 데이터 가져오기
{
	if(0 == m_iRear)							// 버퍼가 비워져 있는 경우
		return 0;

	if(iSize>m_iRear)							// 만약 요청한 크기가 저장되어 있는 
		iSize = m_iRear;						// 크기보다 크다면 재조정

	int i=0;
	for(; i<iSize; ++i)
	{
		*(sOut+i) = *(m_sBuf + i);				// 데이터 복사
		*(m_sBuf+i) =0;							// 복사되면 큐의 내용을 0으로 초기화
	}

	if(iSize != m_iRear)						// 일부만 복사했다면 그 만큼만 이동
	{
		for(i=iSize; i < m_iRear; ++i)
			*(m_sBuf+i-iSize) = *(m_sBuf+i);	// 한 단계씩 앞 자리로 이동

		*(m_sBuf+i-iSize) = 0;					// 마지막 자리도 0으로 초기화
	}

	m_iRear -= iSize;							//Rear 위치 이동
	return iSize;								// 가져온 문장의 길이를 반환
}

void CQueStr::Clear()							// 큐의 내용을 전부 초기화
{
	m_iRear	= 0;
	memset(m_sBuf, 0, sizeof(char)*(m_iWidth+1));
}

int CQueStr::GetWidth()							// 큐의 크기 반환
{
	return m_iWidth;
}

int CQueStr::GetRemain()							// 큐에 남아 있는 공간 반환
{
	return (m_iWidth - m_iRear);
}

void CQueStr::Resize(int iSize)					// 큐의 크기 재조정
{
	char* sBuf = new char[iSize+1];				// End Pointer 하나 더 추가
	memset(sBuf, 0, sizeof(char)* (iSize+1));

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

