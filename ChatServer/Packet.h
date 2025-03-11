#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Define.h"
#include "ErrorCode.h"

struct RawPacketData
{
	UINT32 ClientIndex = 0;
	UINT32 DataSize = 0;
	char* pPacketData = nullptr;

	void Set(RawPacketData& vlaue)
	{
		ClientIndex = vlaue.ClientIndex;
		DataSize = vlaue.DataSize;

		pPacketData = new char[vlaue.DataSize];
		CopyMemory(pPacketData, vlaue.pPacketData, vlaue.DataSize);
	}

	void Set(UINT32 clientIndex_, UINT32 dataSize_, char* pData)
	{
		ClientIndex = clientIndex_;
		DataSize = dataSize_;

		pPacketData = new char[dataSize_];
		CopyMemory(pPacketData, pData, dataSize_);
	}

	void Release()
	{
		delete pPacketData;
	}
};


struct PacketInfo
{
	UINT32 ClientIndex = 0;
	UINT16 PacketId = 0;
	UINT16 DataSize = 0;
	char* pDataPtr = nullptr;
};


enum class  PACKET_ID : UINT16
{
	//SYSTEM
	SYS_USER_CONNECT = 11,
	SYS_USER_DISCONNECT = 12,
	SYS_END = 30,

	//Client
	REQ_LOGIN = 201,
	ANS_LOGIN = 202,

	REQ_ROOM_ENTER= 206,
	ANS_ROOM_ENTER = 207,
	NOT_ROOM_ENTER = 208,

	REQ_ROOM_LEAVE = 215,
	ANS_ROOM_LEAVE = 216,
	NOT_ROOM_LEAVE = 217,

	REQ_ROOM_CHAT = 221,
	ANS_ROOM_CHAT = 222,
	NOT_ROOM_CHAT = 223,
};


#pragma pack(push,1)
struct PACKET_HEADER
{
	UINT16 PacketLength;
	UINT16 PacketId;


};

const UINT32 REQ_PACKET_HEADER_LENGTH = sizeof(PACKET_HEADER);

//- 로그인 요청
struct REQ_LOGIN_PACKET : public PACKET_HEADER
{
	char UserID[MAX_USER_ID_LEN + 1];
};

struct ANS_LOGIN_PACKET : public PACKET_HEADER
{
	UINT16 Result;
};

//- 룸에 들어가기 요청
struct REQ_ROOM_ENTER_PACKET : public PACKET_HEADER
{
	int RoomNumber;
};

struct ANS_ROOM_ENTER_PACKET : public PACKET_HEADER
{
	UINT16 Result;
	int UserCount;
	char UserList[MAX_USER_COUNT][MAX_USER_ID_LEN+1];
};

struct NOT_ROOM_ENTER_PACKET : public PACKET_HEADER
{
	char UserID[MAX_USER_ID_LEN + 1];
};


//- 룸 나가기 요청
struct REQ_ROOM_LEAVE_PACKET : public PACKET_HEADER
{
};

struct ANS_ROOM_LEAVE_PACKET : public PACKET_HEADER
{
	UINT16 Result;
};

struct NOT_ROOM_LEAVE_PACKET : public PACKET_HEADER
{
	char UserID[MAX_USER_ID_LEN + 1];
};



// 룸 채팅
struct REQ_ROOM_CHAT_PACKET : public PACKET_HEADER
{
	char Message[MAX_CHAT_MSG_SIZE + 1] = { 0, };
};

struct ANS_ROOM_CHAT_PACKET : public PACKET_HEADER
{
	UINT16 Result;
};

struct NOT_ROOM_CHAT_PACKET : public PACKET_HEADER
{
	int UserIDLength;
	char UserID[MAX_USER_ID_LEN + 1] = { 0, };
	char Msg[MAX_CHAT_MSG_SIZE + 1] = { 0, };
};
#pragma pack(pop)

