//	Circular Queue class
////////////////////////////////////////////////////////////////////////////////

#ifndef ___QueCircular_H___
#define ___QueCircular_H___

class CQueCircular
{
protected:
	int*	m_pBuf;							// 큐의 버퍼
	int		m_iFront;						// 시작 위치
	int		m_iRear;						// 끝 위치
	int		m_iSpace;						// 남아있는 큐의 버퍼 크기
	int		m_iWidth;						// 큐의 버퍼 크기

public:
	CQueCircular();
	CQueCircular(int iWidth);
	virtual ~CQueCircular();

	int		Enqueue(int iIn);				// 데이터 추가
	int		Dequeue(int* iOut);				// 데이터 꺼냄
};

#endif

