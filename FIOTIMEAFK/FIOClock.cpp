//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FIOClock.h"
#include "FIOMain.h"
#include <string>
#include "winuser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#define FIOhours FIOClockForm->FIOLabel1->Caption
#define FIOminutes FIOClockForm->FIOLabel2->Caption
#define FIOseconds FIOClockForm->FIOLabel3->Caption
TFIOClockForm *FIOClockForm;
TShape* FIOSecSmall[7];
TShape* FIOSecBig[7];
TShape* FIOMinSmall[7];
TShape* FIOMinBig[7];
TShape* FIOHourSmall[7];
TShape* FIOHourBig[7];
TShape* FIODots[4];
TColor FIOglobalColor = clBlack;
TLastInputInfo FIOinfo;
int FIOnumbers[6];
int FIOafkTime = 6;
int FIOw;
int FIOh;
int FIOclockLength;
int FIOdotsLength;
long FIOCheckInput();
long FIOdelay = 0;
bool FIOisAFK;
double FIOratioW;
double FIOratioH;
void FIOGetCurrTime();
void FIOClockUpdate();
void FIOColorShapeNum(TShape* FIOs[], int FIOnum, TColor FIOc);
void FIOColorShape(TShape* FIOs, TColor FIOc);
void FIOReverseShape();
void FIOGetDesktopResolution(int& FIOhorizontal, int& FIOvertical);
void FIOShapeResize(TShape* FIOshape[], double FIOrH, double FIOrW);
void FIOGetCurrTime()
{
	FIOhours = Time().CurrentTime().FormatString("hh");
	FIOminutes = Time().CurrentTime().FormatString("nn");
	FIOseconds = Time().CurrentTime().FormatString("ss");
	FIOnumbers[0] = StrToInt(FIOhours.t_str()[0]);
	FIOnumbers[1] = StrToInt(FIOhours.t_str()[1]);
	FIOnumbers[2] = StrToInt(FIOminutes.t_str()[0]);
	FIOnumbers[3] = StrToInt(FIOminutes.t_str()[1]);
	FIOnumbers[4] = StrToInt(FIOseconds.t_str()[0]);
	FIOnumbers[5] = StrToInt(FIOseconds.t_str()[1]);
	//FIOClockForm->FIOtime->Caption = FIOhours+FIOminutes+FIOseconds;
}
void FIOShapeResize(TShape* FIOshape[], int FIOlength, double FIOrH, double FIOrW)
{
	  for (int i = 0; i < FIOlength; i++)
	  {
		FIOshape[i]->Width = FIOshape[i]->Width * (FIOrW);
		FIOshape[i]->Height = FIOshape[i]->Height * (FIOrH);
		FIOshape[i]->Top = FIOshape[i]->Top * (FIOrH);
		FIOshape[i]->Left = FIOshape[i]->Left * (FIOrW);
	  }
}
void FIOColorShape(TShape* FIOs, TColor FIOc)
{
	FIOs->Brush->Color = FIOc;
}
long FIOCheckInput()
{
	GetLastInputInfo(&FIOinfo);
	return (GetTickCount() - FIOinfo.dwTime)/1000;;

}
void FIOColorShapeNum(TShape* FIOs[], int FIOlength, int FIOnum, TColor FIOc)
{
	switch (FIOnum)
	{
		case 0: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=6){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 1: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi==2 || FIOi== 3){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 2: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=0 && FIOi!= 3){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 3: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=0 && FIOi!= 1){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 4: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=1 && FIOi!= 4 && FIOi != 5){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 5: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=1 && FIOi!= 2){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 6: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=2){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 7: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=1 && FIOi!= 5 && FIOi!=6){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		case 8: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   FIOColorShape(FIOs[FIOi], FIOc);
			   } break;
		case 9: for (int FIOi = 0; FIOi < FIOlength; FIOi++) {
				   if(FIOi!=1){ FIOColorShape(FIOs[FIOi], FIOc); }
			   } break;
		default:
		break;
	}
}
void FIOReverseShape(TShape* FIOs)
{
	if (FIOs->Brush->Color != clWhite)
	{
		FIOs->Brush->Color = clWhite;
	}
	else
	{
		FIOs->Brush->Color = FIOglobalColor;
	}
}
void FIOGetDesktopResolution(int& FIOhorizontal, int& FIOvertical)
{
   RECT FIOdesktop;
   const HWND FIOhDesktop = GetDesktopWindow();
   GetWindowRect(FIOhDesktop, &FIOdesktop);
   FIOhorizontal = FIOdesktop.right;
   FIOvertical = FIOdesktop.bottom;
}
//---------------------------------------------------------------------------
__fastcall TFIOClockForm::TFIOClockForm(TComponent* Owner)
	: TForm(Owner)
{
	FIOw = 0;
	FIOh = 0;

	FIOGetDesktopResolution(FIOw, FIOh);

	FIOratioW = (double)FIOw / ((double)FIOClockForm->ClientWidth);
	FIOratioH = (double)FIOh / ((double)FIOClockForm->ClientHeight);

	FIOinfo.cbSize = sizeof(TLastInputInfo);

	FIOHourBig[0] = FIOShape1;
	FIOHourBig[1] = FIOShape2;
	FIOHourBig[2] = FIOShape3;
	FIOHourBig[3] = FIOShape4;
	FIOHourBig[4] = FIOShape5;
	FIOHourBig[5] = FIOShape6;
	FIOHourBig[6] = FIOShape7;

	FIOHourSmall[0] = FIOShape8;
	FIOHourSmall[1] = FIOShape9;
	FIOHourSmall[2] = FIOShape10;
	FIOHourSmall[3] = FIOShape11;
	FIOHourSmall[4] = FIOShape12;
	FIOHourSmall[5] = FIOShape13;
	FIOHourSmall[6] = FIOShape14;

	FIOMinBig[0] = FIOShape17;
	FIOMinBig[1] = FIOShape18;
	FIOMinBig[2] = FIOShape19;
	FIOMinBig[3] = FIOShape20;
	FIOMinBig[4] = FIOShape21;
	FIOMinBig[5] = FIOShape22;
	FIOMinBig[6] = FIOShape23;

	FIOMinSmall[0] = FIOShape24;
	FIOMinSmall[1] = FIOShape25;
	FIOMinSmall[2] = FIOShape26;
	FIOMinSmall[3] = FIOShape27;
	FIOMinSmall[4] = FIOShape28;
	FIOMinSmall[5] = FIOShape29;
	FIOMinSmall[6] = FIOShape30;

	FIOSecBig[0] = FIOShape33;
	FIOSecBig[1] = FIOShape34;
	FIOSecBig[2] = FIOShape35;
	FIOSecBig[3] = FIOShape36;
	FIOSecBig[4] = FIOShape37;
	FIOSecBig[5] = FIOShape38;
	FIOSecBig[6] = FIOShape39;

	FIOSecSmall[0] = FIOShape40;
	FIOSecSmall[1] = FIOShape41;
	FIOSecSmall[2] = FIOShape42;
	FIOSecSmall[3] = FIOShape43;
	FIOSecSmall[4] = FIOShape44;
	FIOSecSmall[5] = FIOShape45;
	FIOSecSmall[6] = FIOShape46;

	FIODots[0] = FIOShape15;
	FIODots[1] = FIOShape16;
	FIODots[2] = FIOShape31;
	FIODots[3] = FIOShape32;

	FIOclockLength = sizeof(FIOHourBig)/sizeof(FIOHourBig[0]);
	FIOdotsLength = sizeof(FIODots)/sizeof(FIODots[0]);

	FIOShapeResize(FIOHourBig, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIOHourSmall, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIOMinBig, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIOMinSmall, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIOSecBig, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIOSecSmall, FIOclockLength, FIOratioH, FIOratioW);
	FIOShapeResize(FIODots, FIOdotsLength, FIOratioH, FIOratioW);
	FIOClockForm->ClientHeight = FIOh;
	FIOClockForm->ClientWidth = FIOw;
	FIOClockForm->Left = 0;
	FIOClockForm->Top = 0;

	FIObackground->Width = FIOw;
	FIObackground->Height = FIOh;
	FIObackground->SendToBack();

	FIOGetCurrTime();
	FIOisAFK = false;
}
//---------------------------------------------------------------------------
void __fastcall TFIOClockForm::FIOTimeCheckTimer(TObject *Sender)
{
	FIOGetCurrTime();
	for (int FIOi = 0; FIOi < 7; FIOi++)
	{
		FIOHourBig[FIOi]->Brush->Color = clWhite;
		FIOHourSmall[FIOi]->Brush->Color = clWhite;
		FIOMinBig[FIOi]->Brush->Color = clWhite;
		FIOMinSmall[FIOi]->Brush->Color = clWhite;
		FIOSecBig[FIOi]->Brush->Color = clWhite;
		FIOSecSmall[FIOi]->Brush->Color = clWhite;
		if(FIOi < 4)
		{
			FIOReverseShape(FIODots[FIOi]);
		}
	}
	FIOColorShapeNum(FIOHourBig, FIOclockLength, FIOnumbers[0], FIOglobalColor);
	FIOColorShapeNum(FIOHourSmall, FIOclockLength, FIOnumbers[1], FIOglobalColor);
	FIOColorShapeNum(FIOMinBig, FIOclockLength, FIOnumbers[2], FIOglobalColor);
	FIOColorShapeNum(FIOMinSmall, FIOclockLength, FIOnumbers[3], FIOglobalColor);
	FIOColorShapeNum(FIOSecBig, FIOclockLength, FIOnumbers[4], FIOglobalColor);
	FIOColorShapeNum(FIOSecSmall, FIOclockLength, FIOnumbers[5], FIOglobalColor);

}
//---------------------------------------------------------------------------
void __fastcall TFIOClockForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFIOClockForm::FIOAFKCheckTimer(TObject *Sender)
{
	 FIOdelay = FIOCheckInput();

	 if (FIOdelay>FIOafkTime)
	 {
		if (FIOisAFK != true)
		{
			FIOClockForm->Show();
			FIOisAFK = true;
			FIOTransparencyOut->Enabled = true;
			FIOresult->Caption = "AFK";
		}
	 }
	 else
	 {
		 if (FIOisAFK == true)
		 {
			FIOisAFK = false;
         	FIOTransparencyIn->Enabled = true;
		 }
	 }

}
//---------------------------------------------------------------------------
void __fastcall TFIOClockForm::FormHide(TObject *Sender)
{
	FIOTimeCheck->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFIOClockForm::FormShow(TObject *Sender)
{
	FIOTimeCheck->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFIOClockForm::FIOTransparencyOutTimer(TObject *Sender)
{
	if (FIOisAFK == true)
	{
		if (FIOClockForm->AlphaBlendValue<255)
		{
			FIOClockForm->AlphaBlendValue+=5;
		}
		else
		{
			 FIOTransparencyOut->Enabled = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFIOClockForm::FIOTransparencyInTimer(TObject *Sender)
{
	if (FIOClockForm->AlphaBlendValue>0)
	{
		FIOClockForm->AlphaBlendValue-=5;
	}
	else
	{
		 FIOTransparencyIn->Enabled = false;
		 FIOClockForm->Hide();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFIOClockForm::Exit1Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFIOClockForm::FIOClockTrayRestore(TObject *Sender)
{
		FIOMainForm->Show();
		FIOClockForm->Hide();
		//ShowCursor(true);
		FIOAFKCheck->Enabled = false;
}
//---------------------------------------------------------------------------

