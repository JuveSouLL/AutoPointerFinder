//---------------------------------------------------------------------------

#include <vcl.h>
#include <sstream>
#include <windows.h>
#include <psapi.h>
#include "MemoryFunctions.h"
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

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	try
	{
		if (MessageBoxA(NULL, "Oyuna Dönün", "", MB_ICONINFORMATION))
		{
			connect();
		}
        else
		{}
    }
    catch(...)
	{}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EtrafOkuBul, 0, 0, NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Position = poScreenCenter;
}
//---------------------------------------------------------------------------
