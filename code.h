//---------------------------------------------------------------------------

#ifndef codeH
#define codeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TImage *Image1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TBitBtn *BitBtn4;
	TMemo *Memo2;
	void __fastcall RunCode(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
