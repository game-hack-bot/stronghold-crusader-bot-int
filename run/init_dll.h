#pragma once
BOOL fileExists(CHAR* Path)
{
	DWORD Attributes = GetFileAttributesA(Path);

	return (Attributes != INVALID_FILE_ATTRIBUTES && !(Attributes & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL injectDLL(HANDLE processHandle, CHAR* Path)
{
	HANDLE Thread;
	LPVOID RemoteMemoryAddress;
	LPVOID LoadLibraryAddress;
	BOOL ret = FALSE;
	printf("Path: %s\n", Path);
	DWORD MemorySize = strlen(Path) + 1;

	if ((RemoteMemoryAddress = VirtualAllocEx(processHandle, NULL, MemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) != NULL)
	{
		printf("RemoteMemoryAddress: %p\n", RemoteMemoryAddress);
		if (WriteProcessMemory(processHandle, RemoteMemoryAddress, Path, MemorySize, NULL))
		{
			LoadLibraryAddress = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
			printf("LoadLibraryAddress: %p\n", LoadLibraryAddress);
			if ((Thread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryAddress, RemoteMemoryAddress, 0, NULL)) != NULL)
			{
				ret = TRUE;
				CloseHandle(Thread);
			}
		}
	}
	return ret;
}