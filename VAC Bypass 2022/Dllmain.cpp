#include <Windows.h>
#include <iostream>

#include "Scanner.h"
#include "Hooks.h"

//Join my discord server https://discord.gg/dExJ9Sck7n

void MainThread(HMODULE hModule) {
	HMODULE hSteamService = GetModuleHandleA("steamservice.dll");

	if (hSteamService) {
		if (InitVACHooks((void*)hSteamService))
			MessageBoxA(0, "Patched VAC. You may start CSGO.", "VAC Bypass", MB_OK);
		else
			MessageBoxA(0, "An error occured. Please close steam", "VAC Bypass", MB_OK);
	}
	else
		MessageBoxA(0, "Could not find steamservice.dll. Please restart steam as administrator", "VAC Bypass", MB_OK);

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
	}
}
