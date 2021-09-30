#pragma once
#include <Windows.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <Psapi.h>

#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

typedef SIZE_T(_stdcall* tVirtualQuery)(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
tVirtualQuery pVirtualQuery;

typedef SIZE_T(_stdcall* tVirtualQueryEx)(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
tVirtualQueryEx pVirtualQueryEx;

typedef DWORD(_stdcall* tGetProcessId)(HANDLE hProcess);
tGetProcessId pGetProcessId;

typedef BOOL(_stdcall* tProcess32NextW)(HANDLE hSnapShot, LPPROCESSENTRY32W lppe);
tProcess32NextW pProcess32NextW;

typedef BOOL(_stdcall* tModule32NextW)(HANDLE hSnapShot, LPMODULEENTRY32W lppe);
tModule32NextW pModule32NextW;

typedef BOOL(_stdcall* tReadProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
tReadProcessMemory pReadProcessMemory;

typedef BOOL(_stdcall* tOpenProcessToken)(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
tOpenProcessToken pOpenProcessToken;

typedef void(_stdcall* tGetSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
tGetSystemInfo pGetSystemInfo;

typedef HANDLE(_stdcall* tGetCurrentProcess)();
tGetCurrentProcess pGetCurrentProcess;

typedef DWORD(_stdcall* tQueryDosDeviceW)(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax);
tQueryDosDeviceW pQueryDosDeviceW;

typedef BOOL(_stdcall* tGetFileInformationByHandle)(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
tGetFileInformationByHandle pGetFileInformationByHandle;

SIZE_T _stdcall hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	return sizeof(lpBuffer);
}

SIZE_T _stdcall hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	lpBuffer->AllocationProtect = PAGE_NOACCESS;
	lpBuffer->Protect = PAGE_NOACCESS;
	return sizeof(lpBuffer);
}

DWORD _stdcall hkGetProcessId(HANDLE hProcess) {
	return FALSE;
}

BOOL _stdcall hkProcess32NextW(HANDLE hSnapshot, LPPROCESSENTRY32W lppe){
	return FALSE;
}

BOOL _stdcall hkModule32NextW(HANDLE hSnapshot, LPMODULEENTRY32W lppe) {
	return FALSE;
}

BOOL _stdcall hkReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
	return FALSE;
}

BOOL _stdcall hkOpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle) {
	return FALSE;
}

void _stdcall hkGetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
	lpSystemInfo->dwPageSize = 1337;
	return pGetSystemInfo(lpSystemInfo);
}

HANDLE _stdcall hkGetCurrentProcess() {
	return 0;
}

DWORD _stdcall hkQueryDosDeviceW(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax) {
	return 0;
}

BOOL _stdcall hkGetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation) {
	return 0;
}