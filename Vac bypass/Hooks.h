#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <ntstatus.h>

#include "detours.h"
#pragma comment(lib, "detours.lib")

//VirtualQuery
typedef SIZE_T(WINAPI* tVirtualQuery)(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
tVirtualQuery pVirtualQuery;

SIZE_T WINAPI hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//VirtualQueryEx
typedef SIZE_T(WINAPI* tVirtualQueryEx)(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
tVirtualQueryEx pVirtualQueryEx;

SIZE_T WINAPI hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//GetProcessId
typedef DWORD(WINAPI* tGetProcessId)(HANDLE hProcess);
tGetProcessId pGetProcessId;

DWORD WINAPI hkGetProcessId(HANDLE hProcess);

//Process32NextW
typedef BOOL(WINAPI* tProcess32NextW)(HANDLE hSnapShot, LPPROCESSENTRY32W lppe);
tProcess32NextW pProcess32NextW;

BOOL WINAPI hkProcess32NextW(HANDLE hSnapShot, LPPROCESSENTRY32W lppe);

//Module32NextW

typedef BOOL(WINAPI* tModule32NextW)(HANDLE hSnapShot, LPMODULEENTRY32W lppe);
tModule32NextW pModule32NextW;

BOOL WINAPI hkModule32NextW(HANDLE hSnapShot, LPMODULEENTRY32W lppe);

//ReadProcessMemory
typedef BOOL(WINAPI* tReadProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
tReadProcessMemory pReadProcessMemory;

BOOL WINAPI hkReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);

//OpenProcessToken
typedef BOOL(WINAPI* tOpenProcessToken)(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
tOpenProcessToken pOpenProcessToken;

BOOL WINAPI hkOpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);

//GetSystemInfo
typedef void(WINAPI* tGetSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
tGetSystemInfo pGetSystemInfo;

void WINAPI hkGetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

//GetCurrentProcess
typedef HANDLE(WINAPI* tGetCurrentProcess)();
tGetCurrentProcess pGetCurrentProcess;

HANDLE WINAPI hkGetCurrentProcess();

//QueryDosDeviceW
typedef DWORD(WINAPI* tQueryDosDeviceW)(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax);
tQueryDosDeviceW pQueryDosDeviceW;

DWORD WINAPI hkQueryDosDeviceW(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax);

//GetFileInfomationByHandle
typedef BOOL(WINAPI* tGetFileInformationByHandle)(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
tGetFileInformationByHandle pGetFileInformationByHandle;

BOOL _stdcall hkGetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);

//GetWindowTextA
typedef int (WINAPI* tGetWindowTextA)(HWND hWnd, LPSTR lpString, int nMaxCount);
tGetWindowTextA pGetWindowTextA;

int WINAPI hkGetWindowTextA(HWND hwnd, LPSTR lpString, int nMaxCount);

//BitBlt
typedef BOOL (WINAPI* tBitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
tBitBlt pBitBlt;

BOOL WINAPI hkBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

//GetProcAddress
typedef FARPROC(WINAPI* tGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
tGetProcAddress pGetProcAddress;

FARPROC __stdcall hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName);

//NtReadVirtualMemory
typedef NTSTATUS (NTAPI* tNtReadVirtualMemory)(HANDLE ProcessHandle,PVOID  BaseAddress,PVOID  Buffer,ULONG NumberOfBytesToRead,PULONG NumberOfBytesReaded);
tNtReadVirtualMemory pNtReadVirtualMemory;

NTSTATUS NTAPI hkNtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded);

bool InitHooks();
