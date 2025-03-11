#pragma once

#include "UserManager.h"
#include "Packet.h"
#include <iostream>

#include <functional>

using namespace std;

class Room
{
public:
	Room() = default;
	~Room() = default;

	int GetMaxUserCount() { return mMaxUserCount; }

	int GetCurrentUserCount() { return mCurrentUserCount; }

	int GetRoomNumber() { return mRoomNum; }


	void Init(const int roomNum_, const int maxUserCount_)
	{
		mRoomNum = roomNum_;
		mMaxUserCount = maxUserCount_;
	}

	UINT16 EnterUser(User* user_)
	{
		if (mCurrentUserCount >= mMaxUserCount)
		{
			return (UINT16)ERROR_CODE::ENTER_ROOM_FULL_USER;
		}

		mUserList.push_back(user_);
		++mCurrentUserCount;

		user_->EnterRoom(mRoomNum);
		return (UINT16)ERROR_CODE::NONE;
	}

	void LeaveUser(User* leaveUser_)
	{
		mUserList.remove_if([leaveUserId = leaveUser_->GetUserId()](User* pUser) {
			return leaveUserId == pUser->GetUserId(); });
	}

	void NotifyChat(int clientIndex_, const char* userID_, const char* msg_)
	{
		CREATE_NOT(
			NOT_ROOM_CHAT_PACKET,
			ntfPacket,
			(UINT16)PACKET_ID::NOT_ROOM_CHAT,
			sizeof(NOT_ROOM_CHAT_PACKET));

		ntfPacket.UserIDLength = (int)strlen(userID_);
		CopyMemory(ntfPacket.Msg, msg_, sizeof(ntfPacket.Msg));
		CopyMemory(ntfPacket.UserID, userID_, sizeof(ntfPacket.UserID));
		SendToAllUser(sizeof(ntfPacket), (char*)&ntfPacket, clientIndex_, false);
	}

	void NotifyRoomEnter(int clientIndex_, const char* userID_)
	{
 		CREATE_NOT(
 			NOT_ROOM_ENTER_PACKET,
 			ntfPacket,
 			(UINT16)PACKET_ID::NOT_ROOM_ENTER,
 			sizeof(NOT_ROOM_ENTER_PACKET));

		CopyMemory(ntfPacket.UserID, userID_, sizeof(ntfPacket.UserID));

		SendToAllUser(sizeof(ntfPacket), (char*)&ntfPacket, clientIndex_, true);
	}

	void NotifyRoomLeave(int clientIndex_, const char* userID_)
	{
		CREATE_NOT(
			NOT_ROOM_LEAVE_PACKET,
			ntfPacket,
			(UINT16)PACKET_ID::NOT_ROOM_LEAVE,
			sizeof(NOT_ROOM_LEAVE_PACKET));

		CopyMemory(&ntfPacket.UserID, userID_, sizeof(ntfPacket.UserID));

		SendToAllUser(sizeof(ntfPacket), (char*)&ntfPacket, clientIndex_, true);
	}

	list<User*> GetUserLit()
	{
		return mUserList;
	}

	function<void(UINT32, UINT32, char*)> SendPacketFunc;

private:
	void SendToAllUser(const UINT16 dataSize_, char* data_, const int passUserIndex_, bool exceptMe)
	{
		for (auto pUser : mUserList)
		{
			if (pUser == nullptr) {
				continue;
			}

			if (exceptMe && pUser->GetNetConnIdx() == passUserIndex_) {
				continue;
			}

			SendPacketFunc((UINT32)pUser->GetNetConnIdx(), (UINT32)dataSize_, data_);
		}
	}


	int mRoomNum = -1;

	std::list<User*> mUserList;

	int mMaxUserCount = 0;

	UINT16 mCurrentUserCount = 0;
};
