#include <Windows.h>
#include <iostream>

#include "Scanner.h"
#include "Hooks.h"

void MainThread(HMODULE hModule) {
	HMODULE hSteamService = GetModuleHandleA("steamservice.dll");

	if (!hSteamService)
		MessageBoxA(0, "Could not find steamservice.dll - Restart steam with admin...", "VAC BYPASS", MB_OK);
	else {
		if (InitVACHooks((void*)hSteamService))
			MessageBoxA(0, "Patched VAC. You may start CSGO.", "VAC Bypass", MB_OK);
		else
			MessageBoxA(0, "An error has occured. Please close steam...", "VAC Bypass", MB_OK);
	}

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
	}
}
