#include <utility>
#include <cstring>

#include "UserManager.h"
#include "RoomManager.h"
#include "PacketManager.h"


void PacketManager::Init(const UINT32 maxClient_)
{
	mRecvFuntionDictionary = std::unordered_map<int, PROCESS_RECV_PACKET_FUNCTION>();

	mRecvFuntionDictionary[(int)PACKET_ID::SYS_USER_CONNECT] = &PacketManager::ProcessUserConnect;
	mRecvFuntionDictionary[(int)PACKET_ID::SYS_USER_DISCONNECT] = &PacketManager::ProcessUserDisConnect;

	mRecvFuntionDictionary[(int)PACKET_ID::REQ_LOGIN] = &PacketManager::ProcessLogin;
	mRecvFuntionDictionary[(int)PACKET_ID::REQ_ROOM_ENTER] = &PacketManager::ProcessRoomEnter;
	mRecvFuntionDictionary[(int)PACKET_ID::REQ_ROOM_LEAVE] = &PacketManager::ProcessRoomLeave;
	mRecvFuntionDictionary[(int)PACKET_ID::REQ_ROOM_CHAT] = &PacketManager::ProcessChat;

	CreateCompent(maxClient_);
}

void PacketManager::CreateCompent(const UINT32 maxClient_)
{
	mUserManager = new UserManager;
	mUserManager->Init(maxClient_);

	mRoomManager = new RoomManager;
	mRoomManager->SendPacketFunc = SendPacketFunc;
	mRoomManager->Init(1, MAX_ROOM_COUNT, MAX_USER_COUNT);
}

bool PacketManager::Run()
{
	//이 부분을 패킷 처리 부분으로 이동 시킨다.
	mIsRunProcessThread = true;
	mProcessThread = std::thread([this]() { ProcessPacket(); });

	return true;
}

void PacketManager::End()
{
	mIsRunProcessThread = false;

	if (mProcessThread.joinable())
	{
		mProcessThread.join();
	}
}

void PacketManager::ReceivePacketData(const UINT32 clientIndex_, const UINT32 size_, char* pData_)
{
	auto pUser = mUserManager->GetUserByConnIdx(clientIndex_);
	pUser->SetPacketData(size_, pData_);

	EnqueuePacketData(clientIndex_);
}

void PacketManager::ProcessPacket()
{
	while (mIsRunProcessThread)
	{
		bool isIdle = true;

		if (auto packetData = DequePacketData(); packetData.PacketId > (UINT16)PACKET_ID::SYS_END)
		{
			isIdle = false;
			ProcessRecvPacket(packetData.ClientIndex, packetData.PacketId, packetData.DataSize, packetData.pDataPtr);
		}

		if (auto packetData = DequeSystemPacketData(); packetData.PacketId != 0)
		{
			isIdle = false;
			ProcessRecvPacket(packetData.ClientIndex, packetData.PacketId, packetData.DataSize, packetData.pDataPtr);
		}

		if (isIdle)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}

void PacketManager::EnqueuePacketData(const UINT32 clientIndex_)
{
	std::lock_guard<std::mutex> guard(mLock);
	mInComingPacketUserIndex.push_back(clientIndex_);
}

PacketInfo PacketManager::DequePacketData()
{
	UINT32 userIndex = 0;

	{
		std::lock_guard<std::mutex> guard(mLock);
		if (mInComingPacketUserIndex.empty())
		{
			return PacketInfo();
		}

		userIndex = mInComingPacketUserIndex.front();
		mInComingPacketUserIndex.pop_front();
	}

	auto pUser = mUserManager->GetUserByConnIdx(userIndex);
	auto packetData = pUser->GetPacket();
	packetData.ClientIndex = userIndex;
	return packetData;
}

void PacketManager::PushSystemPacket(PacketInfo packet_)
{
	std::lock_guard<std::mutex> guard(mLock);
	mSystemPacketQueue.push_back(packet_);
}

PacketInfo PacketManager::DequeSystemPacketData()
{

	std::lock_guard<std::mutex> guard(mLock);
	if (mSystemPacketQueue.empty())
	{
		return PacketInfo();
	}

	auto packetData = mSystemPacketQueue.front();
	mSystemPacketQueue.pop_front();

	return packetData;
}

void PacketManager::ProcessRecvPacket(const UINT32 clientIndex_, const UINT16 packetId_, const UINT16 packetSize_, char* pPacket_)
{
	auto iter = mRecvFuntionDictionary.find(packetId_);
	if (iter != mRecvFuntionDictionary.end())
	{
		(this->*(iter->second))(clientIndex_, packetSize_, pPacket_);
	}

}

void PacketManager::ProcessUserConnect(UINT32 clientIndex_, UINT16 packetSize_, char* pPacket_)
{
	printf("[ProcessUserConnect] clientIndex: %d\n", clientIndex_);
	auto pUser = mUserManager->GetUserByConnIdx(clientIndex_);
	pUser->Clear();
}

void PacketManager::ProcessUserDisConnect(UINT32 clientIndex_, UINT16 packetSize_, char* pPacket_)
{
	printf("[ProcessUserDisConnect] clientIndex: %d\n", clientIndex_);
	ClearConnectionInfo(clientIndex_);
}

void PacketManager::ProcessLogin(UINT32 clientIndex_, UINT16 packetSize_, char* pPacket_)
{
	auto reqPacket = reinterpret_cast<REQ_LOGIN_PACKET*>(pPacket_);

	auto pUserID = reqPacket->UserID;
	cout<<"requested user id = "<< pUserID <<endl;

	CREATE_ANS(
		ANS_LOGIN_PACKET,
		ansPacket,
		(UINT16)PACKET_ID::ANS_LOGIN,
		sizeof(ANS_LOGIN_PACKET),
		(UINT16)ERROR_CODE::NONE);

	if (mUserManager->GetCurrentUserCnt() >= mUserManager->GetMaxUserCnt())
	{
		//접속자수가 최대수를 차지해서 접속불가
		ansPacket.Result = (UINT16)ERROR_CODE::LOGIN_USER_USED_ALL_OBJ;
		SendPacketFunc(clientIndex_, sizeof(ANS_LOGIN_PACKET), (char*)&ansPacket);
		return;
	}

	//여기에서 이미 접속된 유저인지 확인하고, 접속된 유저라면 실패한다.
	if (mUserManager->FindUserIndexByID(pUserID) == -1)
	{
		mUserManager->AddUser(reqPacket->UserID, clientIndex_);

		ansPacket.Result = (UINT16)ERROR_CODE::NONE;
		SendPacketFunc(clientIndex_, sizeof(ANS_LOGIN_PACKET), (char*)&ansPacket);

	}
	else
	{
		//접속중인 유저여서 실패를 반환한다.
		ansPacket.Result = (UINT16)ERROR_CODE::LOGIN_USER_ALREADY;
		SendPacketFunc(clientIndex_, sizeof(ANS_LOGIN_PACKET), (char*)&ansPacket);
		return;
	}
}


void PacketManager::ProcessRoomEnter(UINT32 clientIndex_, UINT16 packetSize_, char* packet_)
{
	auto reqPacket = reinterpret_cast<REQ_ROOM_ENTER_PACKET*>(packet_);

	CREATE_ANS(
		ANS_ROOM_ENTER_PACKET,
		ansPacket,
		(UINT16)PACKET_ID::ANS_ROOM_ENTER,
		sizeof(ANS_ROOM_ENTER_PACKET),
		(UINT16)ERROR_CODE::NONE);

	auto reqUser = mUserManager->GetUserByConnIdx(clientIndex_);

	if (!reqUser || reqUser == nullptr)
	{
		cout <<"Not Invalid ClientIndex : " << clientIndex_ <<endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_NOT_FINDE_USER;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}

	if (reqUser->GetUserState() != User::USER_STATE::LOGIN)
	{
		cout <<"Not Invalid UserSetate :" << (int)reqUser->GetUserState() <<endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_INVALID_USER_STATUS;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}

	if (reqPacket->RoomNumber <= 0 || reqPacket->RoomNumber > MAX_ROOM_COUNT)
	{
		cout <<"Not Invalid RoomNumber : " << reqPacket->RoomNumber <<endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ROOM_INVALID_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}

	auto room = mRoomManager->GetRoomByNumber(reqPacket->RoomNumber);
	if (!room || room == nullptr)
	{
		cout <<"Not Invalid RoomNumber : " << reqPacket->RoomNumber << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ROOM_INVALID_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}

	if (room->GetCurrentUserCount() >= MAX_USER_COUNT)
	{
		cout <<"Room User Already Max. RoomNumber: "<< reqPacket->RoomNumber <<endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_FULL_USER;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}
	
	auto errorCode = room->EnterUser(reqUser);

	if (errorCode != (UINT16)ERROR_CODE::NONE)
	{
		cout<<"RoomEnter Error. ErrorCode : "<< errorCode <<" UserID : "<< reqUser->GetUserId().c_str() <<endl;
		ansPacket.Result = errorCode;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);
		return;
	}

	int i = 0;
	auto userList = room->GetUserLit();

	for (auto lit : userList)
	{
		if (!lit->GetUserId().empty())
		{
			CopyMemory(ansPacket.UserList[i++], lit->GetUserId().c_str(), lit->GetUserId().size());
			ansPacket.UserCount++;
		}
	}

	SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_ENTER_PACKET), (char*)&ansPacket);

	room->NotifyRoomEnter(clientIndex_, reqUser->GetUserId().c_str());

	return;
}

void PacketManager::ProcessRoomLeave(UINT32 clientIndex_, UINT16 packetSize_, char* packet_)
{
	auto reqPacket = reinterpret_cast<REQ_ROOM_LEAVE_PACKET*>(packet_);

	CREATE_ANS(
		ANS_ROOM_LEAVE_PACKET,
		ansPacket,
		(UINT16)PACKET_ID::ANS_ROOM_LEAVE,
		sizeof(ANS_ROOM_LEAVE_PACKET),
		(UINT16)ERROR_CODE::NONE);

	auto reqUser = mUserManager->GetUserByConnIdx(clientIndex_);

	if (!reqUser || reqUser == nullptr)
	{
		cout << "Not Invalid ClientIndex " << clientIndex_ << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_NOT_FINDE_USER;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	if (reqUser->GetUserState() != User::USER_STATE::ROOM)
	{
		cout << "Not Invalid UserSetate. UserState " << (int)reqUser->GetUserState() << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_INVALID_USER_STATUS;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	int roomNum = reqUser->GetCurrentRoom();

	if (roomNum <= 0 || roomNum > MAX_ROOM_COUNT)
	{
		cout << "Invalid User RoomNumber. UserRoomNum : " << roomNum << " UserID : " << reqUser->GetUserId() << endl;

		ansPacket.Result = (UINT16)ERROR_CODE::LEAVE_ROOM_INVALID_ROOM_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

 	auto room = mRoomManager->GetRoomByNumber(roomNum);
	if (!room || room == nullptr)
	{
		cout << "Not Invalid RoomNumber : " << roomNum << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ROOM_INVALID_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	room->LeaveUser(reqUser);
	reqUser->LeaveRoom();

	SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);

	room->NotifyRoomLeave(clientIndex_, reqUser->GetUserId().c_str());

	return;
}

void PacketManager::ProcessChat(UINT32 clientIndex_, UINT16 packetSize_, char* packet_)
{
	auto reqPacket = reinterpret_cast<REQ_ROOM_CHAT_PACKET*>(packet_);

	CREATE_ANS(
		ANS_ROOM_CHAT_PACKET,
		ansPacket,
		(UINT16)PACKET_ID::ANS_ROOM_CHAT,
		sizeof(ANS_ROOM_CHAT_PACKET),
		(UINT16)ERROR_CODE::NONE);

	auto reqUser = mUserManager->GetUserByConnIdx(clientIndex_);

	if (!reqUser || reqUser == nullptr)
	{
		cout << "Not Invalid ClientIndex " << clientIndex_ << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_NOT_FINDE_USER;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	if (reqUser->GetUserState() != User::USER_STATE::ROOM)
	{
		cout << "Not Invalid UserSetate. UserState " << (int)reqUser->GetUserState() << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ENTER_ROOM_INVALID_USER_STATUS;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	int roomNum = reqUser->GetCurrentRoom();

	if (roomNum <= 0 || roomNum > MAX_ROOM_COUNT)
	{
		cout << "Invalid User RoomNumber. UserRoomNum : " << roomNum << " UserID : " << reqUser->GetUserId() << endl;

		ansPacket.Result = (UINT16)ERROR_CODE::LEAVE_ROOM_INVALID_ROOM_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
	}

	auto room = mRoomManager->GetRoomByNumber(reqUser->GetCurrentRoom());

	if (!room || room == nullptr)
	{
		cout << "Not Invalid RoomNumber : " << roomNum << endl;
		ansPacket.Result = (UINT16)ERROR_CODE::ROOM_INVALID_INDEX;
		SendPacketFunc(clientIndex_, sizeof(ANS_ROOM_LEAVE_PACKET), (char*)&ansPacket);
		return;
	}

	room->NotifyChat(
		clientIndex_,
		reqUser->GetUserId().c_str(),
		reqPacket->Message);

	return;
}

void PacketManager::ClearConnectionInfo(int clientIndex_)
{
	auto pReqUser = mUserManager->GetUserByConnIdx(clientIndex_);

	if (pReqUser->GetUserState() != User::USER_STATE::NONE)
	{
		mUserManager->DeleteUserInfo(pReqUser);
	}
}