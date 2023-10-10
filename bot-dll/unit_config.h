#pragma once
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace unitConfig {
	void load(std::basic_string<TCHAR> dllPathStr);

	extern json data;
}