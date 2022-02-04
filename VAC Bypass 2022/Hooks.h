#pragma once
#include <Windows.h>
#include <fstream>
#include <string>
#include <TlHelp32.h>

#include "Scanner.h"

#include "detours.h"
#pragma comment(lib, "detours.lib")

#pragma warning (disable : 4996)

//55 8B EC 83 EC ? 8D 45 F8 C7 45 F8 ? ? ? ? int __cdecl sub_5DF50(HANDLE ProcessHandle, int a2) checks process token level
typedef int (_cdecl* tFn1)(HANDLE ProcessHandle, int a2);
inline tFn1 pFn1;

int _cdecl hkTfn1(HANDLE ProcessHandle, int a2);

//55 8B EC 81 EC ? ? ? ? 53 56 57 6A ? 68 ? ? ? ? DWORD __stdcall sub_6CDA0(HANDLE TargetHandle, int a2, int a3)
typedef DWORD(_stdcall* tFn2)(HANDLE TargetHandle, int a2, int a3);
inline tFn2 pFn2;

DWORD _stdcall hkTfn2(HANDLE TargetHandle, int a2, int a3);

//55 8B EC 51 56 57 8B 7D 0C bool __cdecl sub_58040(DWORD dwProcessId, int a2, int a3)
typedef bool(_cdecl* tFn3)(DWORD dwProcessId, int a2, int a3);
inline tFn3 pFn3;

bool _cdecl hkTfn3(DWORD dwProcessId, int a2, int a3);

//55 8B EC 81 EC ? ? ? ? 56 8B 35 ? ? ? ? char sub_58140() 
typedef char(_stdcall* tFn4)();
inline tFn4 pFn4;

char _stdcall hkTfn4();

//VirtualQuery
typedef SIZE_T(WINAPI* tVirtualQuery)(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
inline tVirtualQuery pVirtualQuery;

static SIZE_T WINAPI hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//VirtualQueryEx
typedef SIZE_T(WINAPI* tVirtualQueryEx)(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
inline tVirtualQueryEx pVirtualQueryEx;

static SIZE_T WINAPI hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//Process32NextW
typedef BOOL(WINAPI* tProcess32NextW)(HANDLE hSnapShot, LPPROCESSENTRY32W lppe);
inline tProcess32NextW pProcess32NextW;

static BOOL WINAPI hkProcess32NextW(HANDLE hSnapShot, LPPROCESSENTRY32W lppe);

//Module32NextW
typedef BOOL(WINAPI* tModule32NextW)(HANDLE hSnapShot, LPMODULEENTRY32W lppe);
inline tModule32NextW pModule32NextW;

static BOOL WINAPI hkModule32NextW(HANDLE hSnapShot, LPMODULEENTRY32W lppe);

//ReadProcessMemory
typedef BOOL(WINAPI* tReadProcessMemory)(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);
inline tReadProcessMemory pReadProcessMemory;

static BOOL WINAPI hkReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAdress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead);

bool InitVACHooks(void* DllImageBase);