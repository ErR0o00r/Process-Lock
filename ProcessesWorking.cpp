#include "ProcessesWorking.h"

HANDLE EnumerateProcesses(std::function<HANDLE(DWORD pid)> PredProc) {
    DWORD pid_arr[1024], needed;
    HANDLE proc;
    if (EnumProcesses(pid_arr, sizeof(pid_arr), &needed)) {
        for (ptrdiff_t i = 0; i < needed / sizeof(DWORD); i++) {
            proc = PredProc(pid_arr[i]);
            if (proc != NULL) {
                return proc;
            }
        }
    }
    return NULL;
}

TCHAR* GetProcName(HANDLE proc) {
    HMODULE mod;
    DWORD needed;
    TCHAR name[MAX_PATH] = TEXT("UNKNOWN");
    if (EnumProcessModules(proc, &mod, sizeof(mod), &needed)) {
        GetModuleBaseName(proc, mod, name, sizeof(name) / sizeof(TCHAR));
    }
    return name;
}

HANDLE IsDiscordProc(DWORD pid) { 
    HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, NULL, pid);
    if (proc == NULL) {
        return NULL;
    }
    TCHAR* proc_name = GetProcName(proc);

    TCHAR discord_name[] = TEXT("Discord.exe");
    if (_tcscmp(proc_name, discord_name) == 0) {
        return proc;
    }
    return NULL;
}

