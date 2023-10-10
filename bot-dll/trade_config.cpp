#include "pch.h"
#include <iostream>
#include "trade_config.h"

namespace tradeConfig {
	std::map<int, int> resourcesToSell = {};
	json data;

	void load(std::basic_string<TCHAR> dllPathStr)
	{
		std::ifstream f(dllPathStr + L"\\trade_config.json");
		data = json::parse(f);

		f.close();
	}

	void setResourcesToSell()
	{
		for (int resourceId : data["resourcesToSell"])
			resourcesToSell[resourceId] = data["sellTo"][std::to_string(resourceId)];
	}
}
