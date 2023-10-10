#include "pch.h"
#include "Unit.h"
#include "unit_config.h"

typedef int(__cdecl* _RecruitUnit)(int playerNumber, int unitId, int sth);
typedef int(__thiscall* _SetVariable)(DWORD* thisAddress, int a2, int a3, int a4, int a5);

_RecruitUnit RecruitUnit;
_SetVariable SetVariable;

Unit::Unit(DWORD modBase, std::basic_string<TCHAR> dllPathStr)
{
	mModBase = modBase;
	mDllPathStr = dllPathStr;

	unitConfig::load(getMDllPathStr());

	mAutoTaxesInterval = unitConfig::data["autoTaxesInterval"];
	mCurrentTaxesTimer = 0;

	RecruitUnit = (_RecruitUnit)(modBase + 0x64ef0);
	SetVariable = (_SetVariable)(modBase + 0x805d0);
}

void Unit::recruit(std::string numpadNumber)
{
	DWORD sthId = 0;
	for (int i = 0; i < 20; i++) {
		SetVariable((DWORD*)(getMModBase() + 0x151d768), (int)&sthId, 2, 1, 1);
		RecruitUnit(*(int*)(getMModBase() + 0x16275d8), unitConfig::data["recruitIdNumpad" + numpadNumber], sthId);
		Sleep(10);
	}

	printf("RECRUITED from class\n");
}