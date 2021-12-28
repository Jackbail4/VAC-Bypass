#pragma once
#include "Hooks.h"

SIZE_T __stdcall hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength){
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->State = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	return pVirtualQuery(lpAdress, 0, dwLength);
}

SIZE_T __stdcall hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength){
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->State = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	return pVirtualQueryEx(hProcess, lpAdress, 0, dwLength);
}

DWORD __stdcall hkGetProcessId(HANDLE hProcess){
	return 0;
}

BOOL __stdcall hkProcess32NextW(HANDLE hSnapShot, LPPROCESSENTRY32W lppe){
	return 0;
}

BOOL __stdcall hkModule32NextW(HANDLE hSnapShot, LPMODULEENTRY32W lppe){
	return 0;
}

BOOL __stdcall hkReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead){
	return 0;
}

BOOL __stdcall hkOpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle){
	return 0;
}

void __stdcall hkGetSystemInfo(LPSYSTEM_INFO lpSystemInfo){
	return;
}

HANDLE __stdcall hkGetCurrentProcess(){
	return INVALID_HANDLE_VALUE;
}

DWORD __stdcall hkQueryDosDeviceW(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax){
	return 0;
}

BOOL _stdcall hkGetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation){
	lpFileInformation->dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
	lpFileInformation->dwVolumeSerialNumber = 0;
	lpFileInformation->nNumberOfLinks = 0;
	return 1;
}

int __stdcall hkGetWindowTextA(HWND hwnd, LPSTR lpString, int nMaxCount){
	lpString = (LPSTR)"chrome";
	return 0;
}

BOOL __stdcall hkBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop){
	return 0;
}

FARPROC __stdcall hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName){
	return 0;
}

NTSTATUS _stdcall hkNtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded){
	return STATUS_SUCCESS;
}

bool InitHooks(){
	HMODULE kernelModule = GetModuleHandleA("kernel32.dll");
	if (kernelModule == INVALID_HANDLE_VALUE) { return false; }
	pVirtualQuery = (tVirtualQuery)DetourFunction((PBYTE)GetProcAddress(kernelModule, "VirtualQuery"), (PBYTE)hkVirtualQuery);
	pVirtualQueryEx = (tVirtualQueryEx)DetourFunction((PBYTE)GetProcAddress(kernelModule, "VirtualQueryEx"), (PBYTE)hkVirtualQueryEx);
	pGetProcessId = (tGetProcessId)DetourFunction((PBYTE)GetProcAddress(kernelModule, "GetProcessId"), (PBYTE)hkGetProcessId);
	pProcess32NextW = (tProcess32NextW)DetourFunction((PBYTE)GetProcAddress(kernelModule, "Process32NextW"), (PBYTE)hkProcess32NextW);
	pModule32NextW = (tModule32NextW)DetourFunction((PBYTE)GetProcAddress(kernelModule, "Module32NextW"), (PBYTE)hkModule32NextW);
	pReadProcessMemory = (tReadProcessMemory)DetourFunction((PBYTE)GetProcAddress(kernelModule, "ReadProcessMemory"), (PBYTE)hkReadProcessMemory);
	pOpenProcessToken = (tOpenProcessToken)DetourFunction((PBYTE)GetProcAddress(GetModuleHandleA("Advapi32.dll"), "OpenProcessToken"), (PBYTE)hkOpenProcessToken);
	pGetSystemInfo = (tGetSystemInfo)DetourFunction((PBYTE)GetProcAddress(kernelModule, "GetSystemInfo"), (PBYTE)hkGetSystemInfo);
	pGetCurrentProcess = (tGetCurrentProcess)DetourFunction((PBYTE)GetProcAddress(kernelModule, "GetCurrentProcess"), (PBYTE)hkGetCurrentProcess);
	pQueryDosDeviceW = (tQueryDosDeviceW)DetourFunction((PBYTE)GetProcAddress(kernelModule, "QueryDosDeviceW"), (PBYTE)hkQueryDosDeviceW);
	pGetFileInformationByHandle = (tGetFileInformationByHandle)DetourFunction((PBYTE)GetProcAddress(kernelModule, "GetFileInformationByHandle"), (PBYTE)hkGetFileInformationByHandle);
	pGetWindowTextA = (tGetWindowTextA)DetourFunction((PBYTE)GetProcAddress(GetModuleHandleA("User32.dll"), "GetWindowTextA"), (PBYTE)hkGetWindowTextA);
	pBitBlt = (tBitBlt)DetourFunction((PBYTE)GetProcAddress(GetModuleHandleA("Gdi32.dll"), "BitBlt"), (PBYTE)hkBitBlt);
	pGetProcAddress = (tGetProcAddress)DetourFunction((PBYTE)GetProcAddress(kernelModule, "GetProcAddress"), (PBYTE)hkGetProcAddress);
	pNtReadVirtualMemory = (tNtReadVirtualMemory)DetourFunction((PBYTE)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtReadVirtualMemory"), (PBYTE)hkNtReadVirtualMemory);
	return true;
}
