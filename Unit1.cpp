//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>      // Windows API fonksiyonlarý için
#include <psapi.h>        // Process modüllerini listelemek için
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
HANDLE KO_HANDLE;
DWORD pidaddress;
DWORD ReadLong(DWORD value){ReadProcessMemory(KO_HANDLE,(void*)value,&value,sizeof(value),0);return value;}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
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

        // Burada sadece ReadProcessMemory hatasý alýnmasý durumunda kontrol ekleniyor
        char buffer[64];
        if (ReadProcessMemory(KO_HANDLE, (void*)a, &buffer, sizeof(buffer), 0))
        {
            UnicodeString editText = Form1->Edit1->Text; // Edit kutusundan veriyi al
            AnsiString ansiText = editText;

			//Form1->ListBox1->Items->Add(buffer);
            if (strcmp(buffer, ansiText.c_str()) == 0)
            {
                char str[256] = "";
                snprintf(str, sizeof(str), "%zu", i);
                MessageBoxA(NULL, str, "", MB_ICONINFORMATION);
                break;
            }
        }

        // Hýz optimizasyonu için i'yi iki katýna çýkarmayý da deneyebilirsiniz
        i++;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    try
	{
		if (MessageBoxA(NULL, "Oyuna Dönün", "", MB_ICONINFORMATION))
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
			Label4->Caption = pidaddress;
			Label3->Caption = get_title;
			Beep(500,750);
		}
        else
        {
		   //	MessageBoxA(NULL, "Hata 0x5", "Hata", MB_ICONERROR);
			//std::exit(0);
        }
    }
    catch(...)
    {
	  //	MessageBoxA(NULL, "Hata 0x6", "Hata", MB_ICONERROR);
		//std::exit(0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EtrafOkuBul, 0, 0, NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     // Ekranýn ortasýný bulmak için ekran boyutlarýný al
    int screenWidth = Screen->Width;
    int screenHeight = Screen->Height;

    // Formun boyutunu al
    int formWidth = Width;
    int formHeight = Height;

    // Formun ekranýn ortasýnda açýlacak konumunu hesapla
    int left = (screenWidth - formWidth) / 2;
    int top = (screenHeight - formHeight) / 2;

    // Formun konumunu ayarla
    Left = left;
	Top = top;
}
//---------------------------------------------------------------------------
