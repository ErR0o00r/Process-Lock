#include <iostream>
#include "ProcessesWorking.h"

int main() {
	HANDLE proc;
	while (true) {
		proc = EnumerateProcesses(IsDiscordProc);
		if (proc == NULL) {
			continue;
		}
		TerminateProcess(proc, 0);
	}
	return 0;
}