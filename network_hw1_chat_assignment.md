# 네트워크 라이브러리 기반 채팅 프로그램 과제

## 1. 과제 개요

### 1.1 목표

- TCP 스트림 기반 데이터 처리 이해
- PacketHeader 기반 패킷 분리 구현
- 서버 중심 구조 이해 (서버가 메시지 가공)
- 네트워크 코드 라이브러리화

### 1.2 평가 기준 (100)

```
- 네트워크 동작  : 20
- 패킷 헤더      : 20
- TCP 분리 처리  : 20
- 채팅 기능      : 15
- 라이브러리 분리: 15
- 안정성         : 10
```

각 항목은 해당 기능이 정상 동작할 경우 점수가 부여된다.  
핵심 항목(패킷 헤더, TCP 분리 처리)은 미구현 시 큰 감점이 발생한다.


### 1.3 제출 규칙

- 학번_이름_네트워크채팅
- 반드시 압축 해제 후 실행 확인
- .sln 실행
- 빌드 성공 필수

---

## 2. 구현 범위

### 2.1 필수 기능

- 소켓 모델(Blocking/Non-blocking), I/O 모델(Select, EventSelect, IOCP)은 자유
- 서버 / 클라이언트 연결
- 채팅 메시지 송수신
- 사용자 이름 기반 채팅 표시
- WinAPI GUI 구성


### 2.2 동작 구조

#### 접속

- 클라이언트 이름 입력 (최대 19자)
- 클라이언트 → 서버 접속
- 서버:
  - 클라이언트 접속 시 고유 ID 생성
    - ※아이디 생성 알고리즘이 없으므로 socket 과 동일하게 유지
  - 클라이언트 정보 저장
- 서버 → 클라이언트에게 ID 전달
- 클라이언트 → 서버로 이름 전송

#### 채팅

- 클라이언트 → "hello" 메시지 전송
- 서버:
  - 메시지를 보낸 클라이언트의 이름 조회
  - "[이름] 메시지" 형태로 재구성
- 서버 → 모든 클라이언트에게 broadcast (자신 포함)

#### 주요 구현

- 클라이언트는 메시지만 전송
- 서버는 이름 + 메시지 형태로 재구성

---

## 3. 패킷 구조

### 3.1 패킷 헤더

```c
#define PACKET_MAGIC 0x50434B54 // 'PCKT'

#pragma pack(push, 1)
struct PacketHeader
{
    uint32_t magic;		// 패킷 구분자
    uint16_t size;		// 패킷 전체 길이 (헤더 포함)
    uint32_t type;		// 패킷 type (4바이트 유지)
};
#pragma pack(pop)
```

### ⚠️ 중요 주의사항

- PacketHeader.size는 반드시 헤더를 포함한 전체 패킷 크기이다
- 반드시 #pragma pack(1)을 사용해야 한다 (정렬 문제 방지)
- TCP는 데이터 경계를 보장하지 않으므로 직접 패킷을 분리해야 한다
- 잘못된 magic 값 수신 시 연결 종료 처리 가능


### 3.2 패킷 타입

```c
enum PacketType
{
    PKT_CONNECT = 1,
    PKT_CONNECT_ACK,
    PKT_CHAT           = 0x1001,
    PKT_CHAT_BROADCAST = 0x2001,
};
```

### 3.3 패킷 정의

#### 접속 요청

```c
struct PktConnect
{
    PacketHeader header;
    char name[20]; // 최대 19자 + null
};
```

#### 접속 응답

```c
struct PktConnectAck
{
    PacketHeader header;
    int id;
};
```

#### 채팅 (클라이언트 → 서버)

```c
struct PktChat
{
    PacketHeader header;
    char msg[256];
};
```

#### 채팅 (서버 → 클라이언트)

```c
struct PktChatBroadcast
{
    PacketHeader header;
    char name[20];
    char msg[256];
};
```

---

## 4. 네트워크 라이브러리

```c
// 함수의 이름은 취향에 따라 만들어도 됨
// ex)
int Net_Init();
int Net_Connect(const char* ip, int port);
int Net_Send(void* pkt);
int Net_Recv();
void Net_Close();
```

---

## 5. TCP 수신 처리 예

```c
int Net_Recv()
{
    int recvSize = recv(g_sock, buffer + remain, sizeof(buffer) - remain, 0);

    if (recvSize <= 0)
        return -1;

    remain += recvSize;

    while (remain >= sizeof(PacketHeader))
    {
        PacketHeader* header = (PacketHeader*)buffer;

        if (header->magic != PACKET_MAGIC)
            return -1;

        if (remain < header->size)
            break;

        ProcessPacket(buffer);

        memmove(buffer, buffer + header->size, remain - header->size);
        remain -= header->size;
    }

    return 0;
}
```

---

## 6. 서버 구조

```c
struct Client
{
    int    id;		// 서버에서 생성한 고유 ID. 소켓과 동일하게 유지.
    SOCKET sock;
    char name[20];
};
```

---

## 7. 클라이언트 GUI 구성

## UI 예시

![클라이언트 UI](https://raw.githubusercontent.com/3dapi/dv05_netlib/master/img_netlib/net_lib_client1.png)

---

## UI 동작

- Connect 버튼: 서버 연결 및 이름 전송
- Send 버튼: 메시지 전송
- 채팅창: 서버에서 받은 메시지 출력

---
