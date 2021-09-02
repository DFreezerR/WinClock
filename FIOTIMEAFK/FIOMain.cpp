//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "FIOClock.h"
#include "FIOMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFIOMainForm *FIOMainForm;
//---------------------------------------------------------------------------
__fastcall TFIOMainForm::TFIOMainForm(TComponent* Owner)
	: TForm(Owner)
{
	
}
//---------------------------------------------------------------------------
void __fastcall TFIOMainForm::btnExitClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TFIOMainForm::btnStartClick(TObject *Sender)
{
	FIOMainForm->Hide();
	FIOClockForm->FIOAFKCheck->Enabled = true;
}

