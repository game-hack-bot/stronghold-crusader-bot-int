#pragma once
#include <windows.h>
#include <tlhelp32.h>

DWORD getPIDByName(std::wstring name)
{
	DWORD PID = -1;

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			std::wstring binaryPath = entry.szExeFile;
			if (binaryPath.find(name) != std::wstring::npos)
			{
				PID = entry.th32ProcessID;
				break;
			}
		}
	}

	CloseHandle(snapshot);
	return PID;
}

uintptr_t getModuleBaseAddress(DWORD procId, const wchar_t* moduleName)
{
	uintptr_t moduleBaseAddr = 0;
	HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (handleSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry;
		moduleEntry.dwSize = sizeof(moduleEntry);
		if (Module32First(handleSnap, &moduleEntry))
		{
			do
			{
				if (!_wcsicmp(moduleEntry.szModule, moduleName))
				{
					moduleBaseAddr = (uintptr_t)moduleEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(handleSnap, &moduleEntry));
		}
	}
	CloseHandle(handleSnap);
	return moduleBaseAddr;
}
