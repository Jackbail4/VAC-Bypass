#include <Windows.h>

extern bool InitHooks();

void MainThread(HMODULE hModule) {
	if (InitHooks()) {
		MessageBoxA(0, "Success", "Hooks Successful",MB_OK);
	}
	else {
		MessageBoxA(0, "Error", "No kernel32 module",MB_OK);
	}

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
	}
}