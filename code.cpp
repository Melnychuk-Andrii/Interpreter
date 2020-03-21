//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "code.h"
#include "Lexer.h"
#include "Parser.h"
#include "Error_class.h"
#include "Interpreter_c.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------


//convert wchar_t[] to char[]
size_t to_narrow(const wchar_t * src, char * dest, size_t dest_len)
{
  size_t i;
  wchar_t code;
  i = 0;

  while (src[i] != '\0' && i < (dest_len - 1)){
    code = src[i];
    if (code < 128)
      dest[i] = char(code);
    else{
      dest[i] = '?';
	  if (code >= 0xD800 && code <= 0xD8FF)
        i++;
    }
    i++;
  }

  dest[i] = '\0';
  return i - 1;
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RunCode(TObject *Sender)
{
    Memo2->Text = "";
	Err errors = Err();
	char *dest = new char[1000];
	to_narrow(Memo1->Text.c_str(), dest, 1000);

	Lexer lexer = Lexer(dest, &errors);
	lexer.make_tokens();

	Memo2->Text=lexer.print_tokens().c_str();

	Parser parser = Parser(lexer.returnTokens(), lexer.returnTokenCount(), &errors);
	SNode *root = parser.parse();

	Memo2->Text = Memo2->Text + "\r\n\r\n" + printify(root);
	if (errors.happened())
	{
		Memo2->Text = Memo2->Text + errors.printify().c_str();
	}else
	{
		Interpreter inter = Interpreter(root, &errors);
        Value *result;
		result = inter.visit(root);
		if (errors.happened())
			Memo2->Text = Memo2->Text + errors.printify().c_str();
		else
			Memo2->Text = Memo2->Text + "\r\n\r\nRESULT: " + result->represent().c_str();
	}
}
//---------------------------------------------------------------------------

