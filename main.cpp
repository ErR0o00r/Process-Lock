#include <iostream>
#include <Windows.h>
#include "ProcessesWorking.h"

//TODO: переписать под winService
//#define SERVICE_NAME TEXT("ProcessLock")
//
//
//SERVICE_STATUS service_status;
//SERVICE_STATUS_HANDLE service_status_handle = NULL;
//HANDLE service_event = NULL;
//
//void ServiceReportStatus(DWORD current_state, DWORD exit_code, DWORD wait_hint) {
//	static DWORD checkpoint = 1; 
//	service_status.dwCurrentState = current_state;
//	service_status.dwWin32ExitCode = exit_code;
//	service_status.dwWaitHint = wait_hint;
//
//	if (current_state == SERVICE_START_PENDING) {
//		service_status.dwCheckPoint = 0;
//	}
//	else {
//		service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
//	}
//
//	if ((current_state == SERVICE_RUNNING) || (current_state == SERVICE_STOPPED)) {
//		service_status.dwCheckPoint = 0;
//	}
//	else {
//		service_status.dwCheckPoint = checkpoint++;
//	}
//	SetServiceStatus(service_status_handle, &service_status);
//}
//
//void WINAPI ServiceControlHandle(DWORD dw_control) {
//	switch (dw_control) {
//		case SERVICE_CONTROL_STOP: {
//			ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
//			break;
//		}
//		default:
//			break;
//	}
//}
//
//void ServiceInit() {
//	service_event = CreateEvent(NULL, TRUE, FALSE, NULL);
//	if (service_status_handle == NULL) {
//		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
//	}
//	else {
//		ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);
//	}
//
//	while (true) {
//		WaitForSingleObject(service_event, INFINITE);
//		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
//	}
//}


int main() {
	DWORD pid;
	wchar_t name[MAX_PATH] = TEXT("Discord.exe");
	HANDLE proc;

	while (true) {
		pid = FindProc(name);

		if (pid == NULL) {
			continue;
		}
		
		proc = OpenProcess(PROCESS_TERMINATE, NULL, pid);
		
		if (proc) {
			TerminateProcess(proc, 0);
		}
	}
	return 0;
}

//
//VOID WINAPI ServiceMain(DWORD argc, LPTSTR* argv) {
//	service_status_handle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceControlHandle);
//	if (service_status_handle == NULL) {
//		return;
//	}
//
//	service_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
//	service_status.dwServiceSpecificExitCode = 0;
//	ServiceReportStatus(SERVICE_START_PENDING, NO_ERROR, 3000);
//	
//	if (SetServiceStatus(service_status_handle, &service_status) == FALSE) {
//		return;
//	}
//	ServiceInit();
//}