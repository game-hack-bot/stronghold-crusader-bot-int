#include "pch.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <tlhelp32.h>
#include "bonuses.h"
#include "Market.h"
#include "Unit.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

using namespace std;

DWORD modBase;
basic_string<TCHAR> dllPathStr;

BOOLEAN autoSelling = false;
BOOLEAN autoTaxes = false;

void PrintMenu()
{
	for (int n = 0; n < 5; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");
	printf("----- Created by FunDemandingProgramming -----\n");
	printf("Stronghold Crusader simple bot\n");
	printf("1. Sell Resources\n");
	printf("2. Recruit Unit assigned to Numpad 2\n");
	printf("3. Recruit Unit assigned to Numpad 3\n");
	printf("4. Set Tax level\n");
	printf("6. Auto selling: % s\n", autoSelling ? "on" : "off");
	printf("7. Auto taxes: % s\n", autoTaxes ? "on" : "off");
	printf("9. Unload DLL\n");
}

void setDllPath()
{
	TCHAR DllPath[MAX_PATH] = { 0 };
	GetModuleFileName((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
	dllPathStr = DllPath;
	dllPathStr.resize(dllPathStr.rfind('\\'));
}

DWORD WINAPI MainThread(LPVOID param) {
	modBase = (DWORD)GetModuleHandle(NULL);

	AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);

	PrintMenu();

	setDllPath();

	Market market { modBase, dllPathStr };
	Unit unit { modBase, dllPathStr };
	
	while (!GetAsyncKeyState(VK_NUMPAD9)) {
		auto start = std::chrono::high_resolution_clock::now();

		if ((GetAsyncKeyState(VK_NUMPAD1) & 1) || (market.getMCurrentResourcesTimer() > market.getMSellResourcesInterval() && autoSelling)) {
			market.sell();

			if (market.getMCurrentResourcesTimer() > market.getMSellResourcesInterval())
				market.setMCurrentResourcesTimer(0);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
			unit.recruit("2");

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
			unit.recruit("3");

		if ((GetAsyncKeyState(VK_NUMPAD4) & 1) || (unit.getMCurrentTaxesTimer() > unit.getMAutoTaxesInterval() && autoTaxes)) {
			SetNewTaxes(modBase);

			if (unit.getMCurrentTaxesTimer() > unit.getMAutoTaxesInterval())
				unit.setMCurrentTaxesTimer(0);
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			autoSelling = !autoSelling;
			PrintMenu();
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			autoTaxes = !autoTaxes;
			PrintMenu();
		}

		Sleep(10);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		market.setMCurrentResourcesTimer(market.getMCurrentResourcesTimer() + duration.count());
		unit.setMCurrentTaxesTimer(unit.getMCurrentTaxesTimer() + duration.count());
	}

	printf("DLL Unloaded\n");
	FreeConsole();
	FreeLibraryAndExitThread((HINSTANCE)param, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
