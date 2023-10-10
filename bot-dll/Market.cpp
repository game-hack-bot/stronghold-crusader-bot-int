#include <map>

#include "pch.h"
#include "Market.h"
#include "trade_config.h"

typedef int(__cdecl* _MarketOperate)(int actionType);

_MarketOperate MarketOperate;

Market::Market(DWORD modBase, std::basic_string<TCHAR> dllPathStr)
{
	mModBase = modBase;
	mDllPathStr = dllPathStr;

	tradeConfig::load(getMDllPathStr());
	tradeConfig::setResourcesToSell();

	mSellResourcesInterval = tradeConfig::data["sellResourcesInterval"];
	mCurrentResourcesTimer = 0;

	MarketOperate = (_MarketOperate)(modBase + 0x67040);
}

void Market::sell()
{
	DWORD resourceAmount;
	DWORD* resourceIdAddress = (DWORD*)(getMModBase() + 0xd5f814);

	for (std::map<int, int>::iterator it = tradeConfig::resourcesToSell.begin(); it != tradeConfig::resourcesToSell.end(); ++it) {
		resourceAmount = *(DWORD*)(getMModBase() + 0xd5fcc4 + (0x4 * (it->first - 2)));

		while (resourceAmount > it->second) {
			*resourceIdAddress = it->first;
			MarketOperate(1);
			Sleep(25);
			resourceAmount = *(DWORD*)(getMModBase() + 0xd5fcc4 + (0x4 * (it->first - 2)));
		}
	}

	printf("SOLD from class\n");
}