#pragma once
#include <string>

#include "Packet.h"

class User
{
	const UINT32 PACKET_DATA_BUFFER_SIZE = 8096;

public:
	enum class USER_STATE
	{
		NONE = 0,
		LOGIN = 1,
		ROOM = 2
	};


	User() = default;
	~User() = default;

	void Init(const int index)
	{
		mIndex = index;
		mPakcetDataBuffer = new char[PACKET_DATA_BUFFER_SIZE];
	}

	void Clear()
	{
		mRoomIndex = -1;
		mUserID = "";
		mCurUserState = USER_STATE::NONE;

		mPakcetDataBufferWPos = 0;
		mPakcetDataBufferRPos = 0;
	}

	int SetLogin(char* userID_)
	{
		mCurUserState = USER_STATE::LOGIN;
		mUserID = userID_;

		return 0;
	}

	void EnterRoom(int roomIndex_)
	{
		mRoomIndex = roomIndex_;
		mCurUserState = USER_STATE::ROOM;
	}

	void LeaveRoom()
	{
		mRoomIndex = 0;
		mCurUserState = USER_STATE::LOGIN;
	}

	void SetUserState(USER_STATE value_) { mCurUserState = value_; }

	int GetCurrentRoom()
	{
		return mRoomIndex;
	}

	int GetNetConnIdx()
	{
		return mIndex;
	}

	std::string GetUserId() const
	{
		return  mUserID;
	}

	USER_STATE GetUserState()
	{
		return mCurUserState;
	}

	void SetPacketData(const UINT32 dataSize_, char* pData_)
	{
		if ((mPakcetDataBufferWPos + dataSize_) >= PACKET_DATA_BUFFER_SIZE)
		{
			auto remainDataSize = mPakcetDataBufferWPos - mPakcetDataBufferRPos;

			if (remainDataSize > 0)
			{
				CopyMemory(&mPakcetDataBuffer[0], &mPakcetDataBuffer[mPakcetDataBufferRPos], remainDataSize);
				mPakcetDataBufferWPos = remainDataSize;
			}
			else
			{
				mPakcetDataBufferWPos = 0;
			}

			mPakcetDataBufferRPos = 0;
		}

		CopyMemory(&mPakcetDataBuffer[mPakcetDataBufferWPos], pData_, dataSize_);
		mPakcetDataBufferWPos += dataSize_;
	}

	PacketInfo GetPacket()
	{
		const int PACKET_SIZE_LENGTH = 2;
		const int PACKET_TYPE_LENGTH = 2;
		short packetSize = 0;

		UINT32 remainByte = mPakcetDataBufferWPos - mPakcetDataBufferRPos;

		if (remainByte < REQ_PACKET_HEADER_LENGTH)
		{
			return PacketInfo();
		}

		auto pHeader = (PACKET_HEADER*)&mPakcetDataBuffer[mPakcetDataBufferRPos];

		if (pHeader->PacketLength > remainByte)
		{
			return PacketInfo();
		}

		PacketInfo packetInfo;
		packetInfo.PacketId = pHeader->PacketId;
		packetInfo.DataSize = pHeader->PacketLength;
		packetInfo.pDataPtr = &mPakcetDataBuffer[mPakcetDataBufferRPos];

		mPakcetDataBufferRPos += pHeader->PacketLength;

		return packetInfo;
	}


private:
	int mIndex = -1;

	int mRoomIndex = -1;

	std::string mUserID;

	USER_STATE mCurUserState = USER_STATE::NONE;

	UINT32 mPakcetDataBufferWPos = 0;
	UINT32 mPakcetDataBufferRPos = 0;
	char* mPakcetDataBuffer = nullptr;
};

