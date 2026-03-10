//	큐 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef ___QueStr_H___
#define ___QueStr_H___

typedef	unsigned char		BYTE;

class CQueStr
{
protected:
	BYTE*	m_sBuf;							// 큐의 버퍼
	int		m_iFront;						// Front 위치
	int		m_iRear;						// Rear 위치위치
	int		m_iSpace;						// 남아 있는 공간
	int		m_iWidth;						// 큐의 버퍼 크기

public:
	CQueStr();
	CQueStr(int iWidth);
	virtual ~CQueStr();

	int		Enqueue(void* sIn,int iSize);	// 데이터 추가기. 리턴 값은 추가 못한 나머지 사이즈
	int		Dequeue(void*sOut,int* iSize);	// 데이터 가져오기. 리턴 값은 꺼내온 사이즈
	
	void	Clear();						// 큐의 내용을 지움
	int		GetWidth();						// 큐의 크기를 가져옴
	int		GetRemain();					// 큐의 남아 있는 크기를 가져옴
	void	Resize(int iSize);				// 큐의 사이즈를 다시 설정
};

#endif

