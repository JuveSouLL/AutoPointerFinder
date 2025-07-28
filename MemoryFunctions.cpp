 //---------------------------------------------------------------------------
#pragma hdrstop

#include "MemoryFunctions.h"
#include "Unit1.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)


uintptr_t dwGetModuleBaseAddress(DWORD dwProcessID, const wchar_t* lpszModuleName)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);
    uintptr_t dwModuleBaseAddress = 0;

    if (hProcess != NULL)
    {
        HMODULE hModules[1024];
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
        {
            for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
            {
                wchar_t szModuleName[MAX_PATH];
                if (GetModuleFileNameEx(hProcess, hModules[i], szModuleName, sizeof(szModuleName) / sizeof(wchar_t)))
                {
                    wchar_t* pszModuleName = wcsrchr(szModuleName, L'\\');
                    if (pszModuleName)
                        pszModuleName++;

                    if (_wcsicmp(pszModuleName, lpszModuleName) == 0)
                    {
                        dwModuleBaseAddress = (uintptr_t)hModules[i];
                        break;
                    }
                }
            }
        }
        CloseHandle(hProcess);
    }
    return dwModuleBaseAddress;
}
 //---------------------------------------------------------------------------
void connect()
{
    Sleep(2000);
			char get_title[256];
			HWND client = GetForegroundWindow();
			GetWindowTextA(client, get_title, sizeof(get_title));
			HWND hwnd = FindWindowA(NULL, (get_title));
			DWORD procID;
			GetWindowThreadProcessId(hwnd, &procID);
			KO_HANDLE = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
			pidaddress=procID;
			Form1->Label4->Caption = pidaddress;
			Form1->Label3->Caption = get_title;
			Beep(500,750);
}
//---------------------------------------------------------------------------
void EtrafOkuBul()
{
    int kadir = 0;
    MessageBoxA(NULL, "Adressler Taranmaya Baþlandý.", "", MB_ICONINFORMATION);

    for (size_t i = 0; i < 9999999; i++)
    {
        UnicodeString asd1 = Form1->Edit4->Text;
        DWORD BaseAddress = dwGetModuleBaseAddress(pidaddress, asd1.c_str());

        UnicodeString editText = Form1->Edit2->Text.Trim();
        UnicodeString editText1 = Form1->Edit3->Text.Trim();

        DWORD mainadres = StrToInt(editText);
        DWORD mainadres1 = StrToInt(editText1);
        DWORD M_PlayerPtr = BaseAddress + mainadres;
        DWORD a = ReadLong(ReadLong(M_PlayerPtr + i) + 0x00) + mainadres1;

        char buffer[64];
        if (ReadProcessMemory(KO_HANDLE, (void*)a, &buffer, sizeof(buffer), 0))
        {
            UnicodeString editText = Form1->Edit1->Text;
            AnsiString ansiText = editText;

            if (strcmp(buffer, ansiText.c_str()) == 0)
            {
                char str[256] = "";
                snprintf(str, sizeof(str), "%zu", i);
                int decimalValue = StrToInt(str);
                String hexValue = IntToHex(decimalValue);

                String hex1 = Form1->Edit2->Text.Trim();
                if(hex1.UpperCase().Pos("0X") == 1)
                    hex1 = hex1.SubString(3, hex1.Length() - 2);
                if(hexValue.UpperCase().Pos("0X") == 1)
                    hexValue = hexValue.SubString(3, hexValue.Length() - 2);

                int val1 = StrToInt("0x" + hex1);
                int val2 = StrToInt("0x" + hexValue);
                int toplam = val1 + val2;

                Form1->Edit5->Text = "0x" + IntToHex(toplam);
                Form1->Edit5->Enabled = true;
                break;
            }
        }
        i++;
    }
}

// ReadLong fonksiyonu (eðer tanýmlý deðilse)
DWORD ReadLong(DWORD address)
{
    DWORD value = 0;
    ReadProcessMemory(KO_HANDLE, (LPVOID)address, &value, sizeof(DWORD), NULL);
    return value;
}
