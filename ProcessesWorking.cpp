#include "ProcessesWorking.h"

DWORD FindProc(wchar_t* name) {
	HANDLE snapshot; 
	PROCESSENTRY32 proc_info{};
	proc_info.dwSize = sizeof(PROCESSENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (snapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}
	
	Process32First(snapshot, &proc_info);
	DWORD pid{};

	do {
		if (!wcscmp(name, proc_info.szExeFile)) {
			return proc_info.th32ProcessID;
		}
	} while (Process32Next(snapshot, &proc_info));
	
	return NULL;
}
