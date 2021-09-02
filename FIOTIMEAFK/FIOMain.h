//---------------------------------------------------------------------------

#ifndef FIOMainH
#define FIOMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFIOMainForm : public TForm
{
__published:	// IDE-managed Components
	TButton *btnStart;
	TButton *btnExit;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnStartClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFIOMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFIOMainForm *FIOMainForm;
//---------------------------------------------------------------------------
#endif
