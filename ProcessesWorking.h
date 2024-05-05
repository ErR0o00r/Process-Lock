#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <iostream>
#include <functional>

HANDLE EnumerateProcesses(std::function<HANDLE(DWORD pid)> PredProc);

TCHAR* GetProcName(HANDLE proc);

HANDLE IsDiscordProc(DWORD pid);
