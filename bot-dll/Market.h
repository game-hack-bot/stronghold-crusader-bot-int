#ifndef MARKET_H
#define MARKET_H

#include <windows.h>
#include <iostream>

class Market
{
public:
	Market(DWORD modBase, std::basic_string<TCHAR> dllPathStr);
	void sell();

	void setMCurrentResourcesTimer(DWORD currentResourcesTimer)
	{
		mCurrentResourcesTimer = currentResourcesTimer;
	}

	DWORD getMModBase() const { return mModBase; }
	DWORD getMSellResourcesInterval() const { return mSellResourcesInterval; }
	DWORD getMCurrentResourcesTimer() const { return mCurrentResourcesTimer; }
	std::basic_string<TCHAR> getMDllPathStr() const { return mDllPathStr; }
private:
	DWORD mModBase;
	std::basic_string<TCHAR> mDllPathStr;
	DWORD mSellResourcesInterval; // in milliseconds
	DWORD mCurrentResourcesTimer;
};

#endif
