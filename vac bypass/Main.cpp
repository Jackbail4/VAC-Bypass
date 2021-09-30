#include <windows.h>
#include "Hooks.h"
#include "detours.h"
#pragma comment(lib, "detours.lib")

bool CreateHooks() {
	HMODULE hKernel = GetModuleHandle("kernel32.dll");
	HMODULE hAdvapi = GetModuleHandleA("Advapi32.dll");
	if (!hKernel || !hAdvapi) { return false; }

	pVirtualQuery = (tVirtualQuery)DetourFunction((PBYTE)GetProcAddress(hKernel, "VirtualQuery"), (PBYTE)hkVirtualQuery);
	pVirtualQueryEx = (tVirtualQueryEx)DetourFunction((PBYTE)GetProcAddress(hKernel, "VirtualQueryEx"), (PBYTE)hkVirtualQueryEx);
	pGetProcessId = (tGetProcessId)DetourFunction((PBYTE)GetProcAddress(hKernel, "GetProcessId"), (PBYTE)hkGetProcessId);
	pProcess32NextW = (tProcess32NextW)DetourFunction((PBYTE)GetProcAddress(hKernel, "Process32NextW"), (PBYTE)hkProcess32NextW);
	pModule32NextW = (tModule32NextW)DetourFunction((PBYTE)GetProcAddress(hKernel, "Module32NextW"), (PBYTE)hkModule32NextW);
	pReadProcessMemory = (tReadProcessMemory)DetourFunction((PBYTE)GetProcAddress(hKernel, "ReadProcessMemory"), (PBYTE)hkReadProcessMemory);
	pOpenProcessToken = (tOpenProcessToken)DetourFunction((PBYTE)GetProcAddress(hAdvapi, "OpenProcessToken"), (PBYTE)hkOpenProcessToken);
	pGetSystemInfo = (tGetSystemInfo)DetourFunction((PBYTE)GetProcAddress(hKernel, "GetSystemInfo"), (PBYTE)hkGetSystemInfo);
	pGetCurrentProcess = (tGetCurrentProcess)DetourFunction((PBYTE)GetProcAddress(hKernel, "GetCurrentProcess"), (PBYTE)hkGetCurrentProcess);
	pQueryDosDeviceW = (tQueryDosDeviceW)DetourFunction((PBYTE)GetProcAddress(hKernel, "QueryDosDeviceW"), (PBYTE)hkQueryDosDeviceW);
	pGetFileInformationByHandle = (tGetFileInformationByHandle)DetourFunction((PBYTE)GetProcAddress(hKernel, "GetFileInformationByHandle"), (PBYTE)hkGetFileInformationByHandle);
	
	return true;
}

void MainThread(HMODULE hModule) {
	HANDLE hToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
	AdjustTokenPrivileges(hToken, TRUE, 0, 0, 0, 0);

	if (CreateHooks()) {
		MessageBox(0, "Bypass Success", "VAC Bypass", 0);
	}
	else {
		MessageBox(0, "Bypass Failure", "VAC Bypass", 0);
	}

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPARAM lParam) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, LPTHREAD_START_ROUTINE(MainThread), hModule, 0, 0);
	}
}