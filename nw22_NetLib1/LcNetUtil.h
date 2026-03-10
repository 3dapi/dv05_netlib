// Interface for the LcNetUtil functions.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LcNetUtil_H_
#define _LcNetUtil_H_
#include <string>
#include <tuple>
#include <vector>


#define SAFE_CLOSE_HANDLE(p)	{	if(p){	CloseHandle( p );	(p) = nullptr;	}	}
#define ERROR_MESSAGE_LINE(pBuf){	printf("Error Line:%3d %s\t%s\t%s\t%s\n", __LINE__, __DATE__, __TIME__, __FILE__, (pBuf));	}


// Error Message
std::string LcNet_ErrorFormatMessage();					// Network Message Formating
std::string LcNet_ErrorFormatMessage(DWORD hr);
INT		LcNet_WSAGetError();						// Get Error


// Winsock DLL
INT		LcNet_WSAStartup();						// 윈속 라이브러리 초기화
void	LcNet_WSACleanup();						// 윈속 라이브러리 해제


// Socket
INT		LcNet_SocketErrorCheck(INT hr);											// Socket Error Checking
void	LcNet_SocketAddr(SOCKADDR_IN* pOut, char* sIp, char* sPort);			// Setting Socket Address
void	LcNet_SocketClose(SOCKET* scH);											// Socket Close
INT		LcNet_SocketTcpCreate(SOCKET* pScH, BOOL bOverLapped=FALSE);			// Create TCP Socket

INT		LcNet_SocketConnect(SOCKET scH, SOCKADDR_IN* psdH);						// Connection
INT		LcNet_SocketBind(SOCKET scH, SOCKADDR_IN* pSdH);						// Socket Binding
INT		LcNet_SocketListen(SOCKET scH);											// Socket Listen
INT		LcNet_SocketAccept(SOCKET* pscOut			// Output Socket
							, SOCKADDR_IN* psdOut	// Output Socket Address
							, SOCKET scListen		// Listen socket
							);						// Accept


INT		LcNet_SocketSelect(FD_SET* pFdRead, FD_SET* pFdWrite, TIMEVAL* timeout, FD_SET* pFdExcept=nullptr);

INT		LcNet_SocketNonBlocking(SOCKET scH, BOOL bOn=TRUE);						// Set NonBlocking
INT		LcNet_SocketNaggleOff(SOCKET scH, BOOL bOff=TRUE);						// Off nagle Algorithm
INT		LcNet_SocketDirectBuffer(SOCKET scH);									// Disable send buffering on the socket


// 쓰레드 관련 함수들
typedef unsigned (__stdcall* _PBEGIN_THREAD_EX)(void*);							// Thread용 함수포인터
typedef _PBEGIN_THREAD_EX LPBEGIN_THREAD_EX;									//

HANDLE	LcNet_ThreadCreate(LPTHREAD_START_ROUTINE pFunc,void* pParam, ULONG dFlag=0, DWORD* dId= nullptr);	// _beginthreadex()
void	LcNet_ThreadEnd();																				// _endthreadex(0)
void	LcNet_ThreadClose(HANDLE* hThread);																// Thread Close
DWORD	LcNet_ThreadResume(HANDLE* hThread);									// Thread resume
DWORD	LcNet_ThreadSuspend(HANDLE* hThread);									// Thread Suspend
DWORD	LcNet_ThreadWait(HANDLE* hThread, DWORD dMilliseconds = INFINITE);


// 이벤트
HANDLE	LcNet_EventCreate(	BOOL bManualReset=FALSE								// FALSE이면 수동으로 Reset(활성화)을 호출 해야 한다.
						,	BOOL bIntitialState=TRUE							// 초기 상태가 Signal(활성화)상태
						);

void	LcNet_EventResume(HANDLE hEvent);										// 이벤트 활성화
void	LcNet_EventSuspend(HANDLE hEvent);										// 이벤트 비활성화

INT		LcNet_EventWait(HANDLE hEvent, DWORD dWaitMillisecond=INFINITE);		// Event Wait

void	LcNet_EventClose(HANDLE* hEvent);



HANDLE	LcNet_WSAEventCreate();													// WSA Event Create
void	LcNet_WSAEventClose(HANDLE* pEvent);									// WSA Event Close

INT		LcNet_WSAEventSelect(													// WSA Event Select
								SOCKET scH
							,	HANDLE evEvt
							,	long lEvents =(FD_ACCEPT|FD_CONNECT|FD_READ|FD_WRITE|FD_CLOSE)
							 );

INT		LcNet_WSAEventWaits(INT* pArr/*In,Out*/, INT nSrc/*In*/, HANDLE* pSrc/*In*/);	// Return is Event Count.. Failse is -1
INT		LcNet_WSAEventEnum(SOCKET s, HANDLE e);									// WSA Enum Network Event




INT		LcNet_GetSystemProcessNumber();											// Number of CPU
HANDLE	LcNet_IocpPortCreate(SOCKET scH, HANDLE hIocp, void* pAddress);			// IOCP 포트 생성


std::tuple<int, std::vector<std::string> >
LcNet_LocalIpAddress();															// Get Local Ip Addresses





// Interface for the TRingBuf class.
//
////////////////////////////////////////////////////////////////////////////////

#define PCK_USE_BUF_POINTER	0
#define PCK_BUF_MAX_MSG		1024
#define PCK_BUF_MAX_QUEUE	4096
#define PCK_BUF_HEAD		2
#define PCK_BUF_KIND		4
#define PCK_BUF_TAIL		4



INT	 LcNet_PacketEncode(void* pOut						// Output Packet
					  , const void* sMsg				// Packet contents
					  , INT iSndM						// Pakcet contents length
					  , DWORD nMsg						// Send Message Kind
					  , INT iPstL=(PCK_BUF_HEAD)		// Packet Structure Length Byte =2(WORD)
					  , INT iPstM=(PCK_BUF_KIND)		// Packet Structure Message Byte = 4(INT)
					  , INT iPstT=(PCK_BUF_TAIL)		// Packet Structure Tail Byte = 4(INT)
					  );


INT	 LcNet_PacketDecode(void* sMsg						// Output Message
					  , DWORD* nMsg						// Receive Message Kind
					  , const void* pIn					// Receive Packets
					  , INT iRcvM						// Receive Packet Length
					  , INT iPstL=(PCK_BUF_HEAD)		// Packet Structure Length Byte =2(WORD)
					  , INT iPstM=(PCK_BUF_KIND)		// Packet Structure Message Byte = 4(INT)
					  , INT iPstT=(PCK_BUF_TAIL)		// Packet Structure Tail Byte = 4(INT)
					  );




#endif



