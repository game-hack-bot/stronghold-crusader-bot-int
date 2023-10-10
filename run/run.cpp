#include <iostream>
#include "init_connection.h"
#include "init_dll.h"

const wchar_t* PROCESS_NAME = L"Stronghold Crusader.exe";
DWORD processModule;
HWND windowHandle;
HANDLE processHandle;
DWORD PID;

int main()
{
	PID = getPIDByName(PROCESS_NAME);
	std::cout << PID << std::endl;

	if (PID == -1) {
		printf("Can't find process!!!");
		Sleep(1000);
		return 0;
	}

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

	processModule = getModuleBaseAddress(PID, PROCESS_NAME);

	CHAR LibraryName[MAX_PATH] = "bot-dll.dll";
	CHAR LibraryPath[MAX_PATH] = { 0 };

	GetFullPathNameA(LibraryName, MAX_PATH, LibraryPath, NULL);

	if (fileExists(LibraryPath))
		std::cout << (injectDLL(processHandle, LibraryPath) ? "Attached" : "Not attached") << std::endl;
}
