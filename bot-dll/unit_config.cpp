#include "pch.h"
#include <iostream>
#include "unit_config.h"

namespace unitConfig {
	json data;

	void load(std::basic_string<TCHAR> dllPathStr)
	{
		std::ifstream f(dllPathStr + L"\\unit_config.json");
		data = json::parse(f);

		f.close();
	}
}