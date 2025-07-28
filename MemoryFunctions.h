//---------------------------------------------------------------------------
#ifndef MemoryFunctionsH
#define MemoryFunctionsH
//---------------------------------------------------------------------------
#include <windows.h>
#include <psapi.h>
#include <System.hpp>
extern HANDLE KO_HANDLE;
extern DWORD pidaddress;
uintptr_t dwGetModuleBaseAddress(DWORD dwProcessID, const wchar_t* lpszModuleName);
void EtrafOkuBul();
void connect();
DWORD ReadLong(DWORD address);

#endif
