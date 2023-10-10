#ifndef UNIT_H
#define UNIT_H

#include <windows.h>
#include <iostream>

class Unit
{
public:
	Unit(DWORD modBase, std::basic_string<TCHAR> dllPathStr);
	void recruit(std::string numpadNumber);

	void setMCurrentTaxesTimer(DWORD currentTaxesTimer)
	{
		mCurrentTaxesTimer = currentTaxesTimer;
	}

	DWORD getMModBase() const { return mModBase; }
	DWORD getMAutoTaxesInterval() const { return mAutoTaxesInterval; }
	DWORD getMCurrentTaxesTimer() const { return mCurrentTaxesTimer; }
	std::basic_string<TCHAR> getMDllPathStr() const { return mDllPathStr; }
private:
	DWORD mModBase;
	std::basic_string<TCHAR> mDllPathStr;
	DWORD mAutoTaxesInterval; // milliseconds
	DWORD mCurrentTaxesTimer;
};

#endif