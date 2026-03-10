//	큐 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef ___QueLinear_H___
#define ___QueLinear_H___

class CQueLinear								// 큐 클래스
{
protected:
	int*	m_pBuf;							// 큐의 버퍼
	int		m_iRear;						// 입력 문자열 끝 위치
	int		m_iWidth;						// 큐의 버퍼 크기

public:
	CQueLinear();
	CQueLinear(int iWidth);
	virtual ~CQueLinear();

	int		Enqueue(int iIn);				// 데이터 추가
	int		Dequeue(int* iOut);				// 데이터 꺼냄
};

#endif

