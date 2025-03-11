#pragma once
#include <unordered_map>

#include "ErrorCode.h"
#include "User.h"

class UserManager
{
public:
	UserManager() = default;
	~UserManager() = default;

	void Init(const int maxUserCount_)
	{
		mMaxUserCnt = maxUserCount_;
		mUserObjPool = std::vector<User*>(mMaxUserCnt);

		for (auto i = 0; i < mMaxUserCnt; i++)
		{
			mUserObjPool[i] = new User();
			mUserObjPool[i]->Init(i);
		}
	}

	int GetCurrentUserCnt() { return mCurrentUserCnt; }

	int GetMaxUserCnt() { return mMaxUserCnt; }

	void IncreaseUserCnt() { mCurrentUserCnt++; }

	void DecreaseUserCnt()
	{
		if (mCurrentUserCnt > 0)
		{
			mCurrentUserCnt--;
		}
	}

	ERROR_CODE AddUser(char* userID_, int clientIndex_)
	{
		auto user_idx = clientIndex_;

		mUserObjPool[user_idx]->SetLogin(userID_);
		mUserIDDictionary.insert(std::pair< char*, int>(userID_, clientIndex_));

		return ERROR_CODE::NONE;
	}

	int FindUserIndexByID(char* userID_)
	{
		if (auto res = mUserIDDictionary.find(userID_); res != mUserIDDictionary.end())
		{
			return (*res).second;
		}

		return -1;
	}

	void DeleteUserInfo(User* user_)
	{
		mUserIDDictionary.erase(user_->GetUserId());
		user_->Clear();
	}

	User* GetUserByConnIdx(int clientIndex_)
	{
		return mUserObjPool[clientIndex_];
	}


private:
	int mMaxUserCnt = 0;
	int mCurrentUserCnt = 0;

	std::vector<User*> mUserObjPool; 
	std::unordered_map<std::string, int> mUserIDDictionary;
};
