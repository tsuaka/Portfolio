#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mswsock.h>

// ��ũ�θ� �̿��� ����ü ��ü ����
#define CREATE_REQ(struct_name, var_name, base_val1, base_val2) \
 	struct_name var_name = {base_val2, base_val1}

 #define CREATE_ANS(struct_name, var_name, base_val1, base_val2, base_val3, ...) \
 	struct_name var_name {base_val2, base_val1, __VA_ARGS__}
 
#define CREATE_NOT(struct_name, var_name, base_val1, base_val2) \
 	struct_name var_name {base_val2, base_val1}

const UINT32 MAX_SOCK_RECVBUF = 256;	// ���� ������ ũ��
const UINT32 MAX_SOCK_SENDBUF = 4096;	// ���� ������ ũ��

const int MAX_CHAT_MSG_SIZE = 256;
const int MAX_USER_ID_LEN = 32;

const int MAX_ROOM_COUNT = 4;

const UINT16 SERVER_PORT = 65535;
const UINT16 MAX_USER_COUNT = 3;		//�� �����Ҽ� �ִ� Ŭ���̾�Ʈ ��
const UINT32 MAX_IO_WORKER_THREAD = 4;  //������ Ǯ�� ���� ������ ��

enum class IOOperation
{
	ACCEPT,
	RECV,
	SEND
};

struct stOverlappedEx
{
	WSAOVERLAPPED m_wsaOverlapped;		//Overlapped I/O����ü
	WSABUF		m_wsaBuf;				//Overlapped I/O�۾� ����
	IOOperation m_eOperation;			//�۾� ���� ����
	UINT32 SessionIndex = 0;
};

