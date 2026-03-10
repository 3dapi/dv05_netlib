//	Circular Queue class
////////////////////////////////////////////////////////////////////////////////

#ifndef ___TqueCircular_H___
#define ___TqueCircular_H___

template<class T>
class TqueCircular
{
protected:
	T*		m_pBuf;							// 큐의 버퍼
	int		m_iFront;						// 시작 위치
	int		m_iRear;						// 끝 위치
	int		m_iSpace;						// 남아있는 큐의 버퍼 크기
	int		m_iWidth;						// 큐의 버퍼 크기

public:
	TqueCircular();
	TqueCircular(int iWidth);
	virtual ~TqueCircular();

	int		Enqueue(T* p);					// 데이터 추가
	int		Dequeue(T* p);					// 데이터 꺼냄
};




template<class T>
TqueCircular<T>::TqueCircular()
{
	m_pBuf		= nullptr;
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= 0;
	m_iWidth	= 0;
}

template<class T>
TqueCircular<T>::TqueCircular(int iWidth)
{
	m_iFront	= 0;
	m_iRear		= 0;
	m_iSpace	= iWidth;
	m_iWidth	= iWidth;

	m_pBuf	= new T[m_iWidth+1];				// End Pointer 하나 더 추가...
	memset(m_pBuf, 0, sizeof(int)*(m_iWidth+1));
}

template<class T>
TqueCircular<T>::~TqueCircular()
{
	if(m_pBuf)									// 동적으로 생성한 버퍼 해제
	{
		delete [] m_pBuf;
		m_pBuf = nullptr;
	}
}

template<class T>
int TqueCircular<T>::Enqueue(T* p)				// 큐에 데이터 추가
{
	if( 0 == m_iSpace)							// 남아 있는 공간이 없으면 채우지 못함
		return -1;								// Failed

	memcpy(&m_pBuf[m_iRear], p, sizeof(T));

	--m_iSpace;									// 빈영역 감소

	++m_iRear;
	m_iRear%= m_iWidth;							// Rear 위치 이동

	return 0;
}

template<class T>
int TqueCircular<T>::Dequeue(T* p)				// 큐에서 데이터 가져오기
{
	if(m_iSpace == m_iWidth)					// 버퍼가 비워져 있는 경우
		return -1;								// Failed

	memcpy(p, &m_pBuf[m_iFront], sizeof(T));
	
	++m_iSpace;									// 빈영역 증가

	++m_iFront;
	m_iFront%= m_iWidth;						// Front 위치 이동

	return 0;
}


#endif

