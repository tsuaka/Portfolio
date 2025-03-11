#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mswsock.h>

// 매크로를 이용한 구조체 객체 생성
#define CREATE_REQ(struct_name, var_name, base_val1, base_val2) \
 	struct_name var_name = {base_val2, base_val1}

 #define CREATE_ANS(struct_name, var_name, base_val1, base_val2, base_val3, ...) \
 	struct_name var_name {base_val2, base_val1, __VA_ARGS__}
 
#define CREATE_NOT(struct_name, var_name, base_val1, base_val2) \
 	struct_name var_name {base_val2, base_val1}

const UINT32 MAX_SOCK_RECVBUF = 256;	// 소켓 버퍼의 크기
const UINT32 MAX_SOCK_SENDBUF = 4096;	// 소켓 버퍼의 크기

const int MAX_CHAT_MSG_SIZE = 256;
const int MAX_USER_ID_LEN = 32;

const int MAX_ROOM_COUNT = 4;

const UINT16 SERVER_PORT = 65535;
const UINT16 MAX_USER_COUNT = 3;		//총 접속할수 있는 클라이언트 수
const UINT32 MAX_IO_WORKER_THREAD = 4;  //쓰레드 풀에 넣을 쓰레드 수

enum class IOOperation
{
	ACCEPT,
	RECV,
	SEND
};

struct stOverlappedEx
{
	WSAOVERLAPPED m_wsaOverlapped;		//Overlapped I/O구조체
	WSABUF		m_wsaBuf;				//Overlapped I/O작업 버퍼
	IOOperation m_eOperation;			//작업 동작 종류
	UINT32 SessionIndex = 0;
};

