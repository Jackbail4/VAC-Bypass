#include "Hooks.h"

int _cdecl hkTfn1(HANDLE ProcessHandle, int a2){
	if (ProcessHandle == GetCurrentProcess())
		return pFn1(ProcessHandle, a2);
	return FALSE;
}

DWORD _stdcall hkTfn2(HANDLE TargetHandle, int a2, int a3){
	if (TargetHandle == GetCurrentProcess())
		return pFn2(TargetHandle, a2, a3);
	return FALSE;
}

bool _cdecl hkTfn3(DWORD dwProcessId, int a2, int a3){
	if (dwProcessId == GetCurrentProcessId())
		return pFn3(dwProcessId, a2, a3);
	return FALSE;
}

char _stdcall hkTfn4(){
	return FALSE;
}

char _stdcall hkTfn5(char* p_this){
	return true;
}

DWORD* _stdcall hkTfn6(DWORD* p_this){
	return p_this;
}

SIZE_T __stdcall hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	lpBuffer->Type = MEM_MAPPED;
	return pVirtualQuery(lpAdress, 0, dwLength);
}

SIZE_T __stdcall hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	lpBuffer->Type = MEM_MAPPED;
	return pVirtualQueryEx(hProcess, lpAdress, 0, dwLength);
}

BOOL __stdcall hkProcess32NextW(HANDLE hSnapShot, LPPROCESSENTRY32W lppe) {
	return 0;
}

BOOL __stdcall hkModule32NextW(HANDLE hSnapShot, LPMODULEENTRY32W lppe) {
	return 0;
}

BOOL __stdcall hkReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
	return 0;
}

bool InitVACHooks(void* DllImageBase) {
	pFn1 = (tFn1)DetourFunction((PBYTE)PatternScan(DllImageBase, "55 8B EC 83 EC ? 8D 45 F8 C7 45 F8 ? ? ? ?"), (PBYTE)hkTfn1);
	pFn2 = (tFn2)DetourFunction((PBYTE)PatternScan(DllImageBase, "55 8B EC 81 EC ? ? ? ? 53 56 57 6A ? 68 ? ? ? ?"), (PBYTE)hkTfn2);
	pFn3 = (tFn3)DetourFunction((PBYTE)PatternScan(DllImageBase, "55 8B EC 51 56 57 8B 7D 0C"), (PBYTE)hkTfn1);
	pFn4 = (tFn4)DetourFunction((PBYTE)PatternScan(DllImageBase, "55 8B EC 81 EC ? ? ? ? 56 8B 35 ? ? ? ?"), (PBYTE)hkTfn1);
	pFn5 = (tFn5)DetourFunction((PBYTE)PatternScan(DllImageBase, "56 57 8B F9 C7 07 ? ? ? ? C7 47 04 ? ? ? ?"), (PBYTE)hkTfn5);
	pFn6 = (tFn6)DetourFunction((PBYTE)PatternScan(DllImageBase, "55 8B EC 83 EC ? 56 8B F1 C7 06 ? ? ? ?"), (PBYTE)hkTfn6);

	HMODULE kernelModule = GetModuleHandleA("kernel32.dll");
	if (kernelModule == INVALID_HANDLE_VALUE) 
		return false;
	pVirtualQuery = (tVirtualQuery)DetourFunction((PBYTE)GetProcAddress(kernelModule, "VirtualQuery"), (PBYTE)hkVirtualQuery);
	pVirtualQueryEx = (tVirtualQueryEx)DetourFunction((PBYTE)GetProcAddress(kernelModule, "VirtualQueryEx"), (PBYTE)hkVirtualQueryEx);
	pProcess32NextW = (tProcess32NextW)DetourFunction((PBYTE)GetProcAddress(kernelModule, "Process32NextW"), (PBYTE)hkProcess32NextW);
	pModule32NextW = (tModule32NextW)DetourFunction((PBYTE)GetProcAddress(kernelModule, "Module32NextW"), (PBYTE)hkModule32NextW);
	pReadProcessMemory = (tReadProcessMemory)DetourFunction((PBYTE)GetProcAddress(kernelModule, "ReadProcessMemory"), (PBYTE)hkReadProcessMemory);

	return true;
}
