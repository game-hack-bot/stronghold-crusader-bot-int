#pragma once
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace tradeConfig {
	void load(std::basic_string<TCHAR> dllPathStr);
	void setResourcesToSell();

	extern json data;
	// <resourceId, resMinAmount>
	extern std::map<int, int> resourcesToSell;
}
