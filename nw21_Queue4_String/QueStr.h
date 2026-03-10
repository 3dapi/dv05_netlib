//	큐 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef ___QueStr_H___
#define ___QueStr_H___

class CQueStr
{
protected:
	char*	m_sBuf;							// 큐의 버퍼
	int		m_iRear;						// 입력 문자열 끝 위치
	int		m_iWidth;						// 큐의 버퍼 크기

public:
	CQueStr();
	CQueStr(int iWidth);
	virtual ~CQueStr();

	int		Enqueue(char* sIn,int iSize=1);	// 데이터 추가기. 리턴 값은 추가 못한 나머지 사이즈
	int		Dequeue(char*sOut,int iSize=1);	// 데이터 가져오기. 리턴 값은 꺼내온 사이즈
	
	void	Clear();						// 큐의 내용을 지움
	int		GetWidth();						// 큐의 크기를 가져옴
	int		GetRemain();					// 큐의 남아 있는 크기를 가져옴
	void	Resize(int iSize);				// 큐의 사이즈를 다시 설정
};

#endif

