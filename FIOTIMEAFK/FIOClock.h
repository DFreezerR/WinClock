//---------------------------------------------------------------------------

#ifndef FIOClockH
#define FIOClockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "trayicon.h"
#include <Menus.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TFIOClockForm : public TForm
{
__published:	// IDE-managed Components
	TShape *FIOShape1;
	TShape *FIOShape2;
	TShape *FIOShape3;
	TShape *FIOShape4;
	TShape *FIOShape5;
	TShape *FIOShape6;
	TShape *FIOShape7;
	TShape *FIOShape8;
	TShape *FIOShape9;
	TShape *FIOShape10;
	TShape *FIOShape11;
	TShape *FIOShape12;
	TShape *FIOShape13;
	TShape *FIOShape14;
	TShape *FIOShape15;
	TShape *FIOShape16;
	TShape *FIOShape17;
	TShape *FIOShape18;
	TShape *FIOShape19;
	TShape *FIOShape20;
	TShape *FIOShape21;
	TShape *FIOShape22;
	TShape *FIOShape23;
	TShape *FIOShape24;
	TShape *FIOShape25;
	TShape *FIOShape26;
	TShape *FIOShape27;
	TShape *FIOShape28;
	TShape *FIOShape29;
	TShape *FIOShape30;
	TShape *FIOShape31;
	TShape *FIOShape32;
	TShape *FIOShape33;
	TShape *FIOShape34;
	TShape *FIOShape35;
	TShape *FIOShape36;
	TShape *FIOShape37;
	TShape *FIOShape38;
	TShape *FIOShape39;
	TShape *FIOShape40;
	TShape *FIOShape41;
	TShape *FIOShape42;
	TShape *FIOShape43;
	TShape *FIOShape44;
	TShape *FIOShape45;
	TShape *FIOShape46;
	TTimer *FIOTimeCheck;
	TTimer *FIOAFKCheck;
	TLabel *FIOtime;
	TLabel *FIOLabel1;
	TLabel *FIOLabel2;
	TLabel *FIOLabel3;
	TLabel *FIOy;
	TLabel *FIOx;
	TLabel *FIOresult;
	TImage *FIObackground;
	TTimer *FIOTransparencyOut;
	TTimer *FIOTransparencyIn;
	TCTrayIcon *FIOClockTray;
	TPopupMenu *FIOPopupMenu1;
	TMenuItem *Exit1;
	void __fastcall FIOTimeCheckTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FIOAFKCheckTimer(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FIOTransparencyOutTimer(TObject *Sender);
	void __fastcall FIOTransparencyInTimer(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall FIOClockTrayRestore(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFIOClockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFIOClockForm *FIOClockForm;
//---------------------------------------------------------------------------
#endif
