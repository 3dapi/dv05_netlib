//	큐 응용프로그램 클래스
////////////////////////////////////////////////////////////////////////////////

#ifndef ___QueueApp_H___
#define ___QueueApp_H___

class CQueueApp								// 큐 응용 클래스
{
private:
	enum {	MAX_QUEUE_BUF = 40,	};			// 큐의 디폴트 크기
	CQueStr*	m_pQueue;					// CQueue의 인스턴스

public:
	CQueueApp();
	virtual ~CQueueApp();

	int		Init(int iSize=MAX_QUEUE_BUF);	// 큐 초기화
	int		Run();							// 큐 응용 프로그램 가동
	void	Destroy();						// 큐 응용 프로그램 종료

private:
	void	EnqueuingMode();				// Enqueue 응용 모드
	void	DequeuingMode();				// Dequeue 응용 모드
	void	InputString(char* sMsg			// 키보드에서의 입력 값 처리
						, int iSize, FILE* fp=stdin);
};

#endif

