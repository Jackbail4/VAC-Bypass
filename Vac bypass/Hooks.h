#include <Windows.h>
#include <TlHelp32.h>
#include <string>

#include "detours.h"
#pragma comment(lib, "detours.lib")

//VirtualQuery
typedef SIZE_T(WINAPI* tVirtualQuery)(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
inline tVirtualQuery pVirtualQuery;

static SIZE_T WINAPI hkVirtualQuery(LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//VirtualQueryEx
typedef SIZE_T(WINAPI* tVirtualQueryEx)(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
inline tVirtualQueryEx pVirtualQueryEx;

static SIZE_T WINAPI hkVirtualQueryEx(HANDLE hProcess, LPCVOID lpAdress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

//GetProcessId
typedef DWORD(WINAPI* tGetProcessId)(HANDLE hProcess);
inline tGetProcessId pGetProcessId;

static DWORD WINAPI hkGetProcessId(HANDLE hProcess);

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

//OpenProcessToken
typedef BOOL(WINAPI* tOpenProcessToken)(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);
inline tOpenProcessToken pOpenProcessToken;

static BOOL WINAPI hkOpenProcessToken(HANDLE ProcessHandle, DWORD DesiredAccess, PHANDLE TokenHandle);

//GetSystemInfo
typedef void(WINAPI* tGetSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
inline tGetSystemInfo pGetSystemInfo;

static void WINAPI hkGetSystemInfo(LPSYSTEM_INFO lpSystemInfo);

//GetCurrentProcess
typedef HANDLE(WINAPI* tGetCurrentProcess)();
inline tGetCurrentProcess pGetCurrentProcess;

static HANDLE WINAPI hkGetCurrentProcess();

//QueryDosDeviceW
typedef DWORD(WINAPI* tQueryDosDeviceW)(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax);
inline tQueryDosDeviceW pQueryDosDeviceW;

static DWORD WINAPI hkQueryDosDeviceW(LPCWSTR lpDeviceName, LPWSTR lpTargetPath, DWORD ucchMax);

//GetFileInfomationByHandle
typedef BOOL(WINAPI* tGetFileInformationByHandle)(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);
inline tGetFileInformationByHandle pGetFileInformationByHandle;

static BOOL _stdcall hkGetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpFileInformation);

//GetWindowTextA
typedef int (WINAPI* tGetWindowTextA)(HWND hWnd, LPSTR lpString, int nMaxCount);
inline tGetWindowTextA pGetWindowTextA;

static int WINAPI hkGetWindowTextA(HWND hwnd, LPSTR lpString, int nMaxCount);

//BitBlt
typedef BOOL (WINAPI* tBitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);
inline tBitBlt pBitBlt;

static BOOL WINAPI hkBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

//GetProcAddress
typedef FARPROC(WINAPI* tGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
inline tGetProcAddress pGetProcAddress;

static FARPROC __stdcall hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName);

bool InitHooks(void);
