#include "Hooks.h"

void MainThread(HMODULE hModule) {
	if (InitHooks())
		MessageBoxA(0, "Success", "Vac Bypassed!", MB_OK);
	else
		MessageBoxA(0, "Error", "An error occured!", MB_OK);

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
	}
}
