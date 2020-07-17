//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TPanel *Panel1;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TBitBtn *BitBtn1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TListBox *ListBox1;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TComboBox *ComboBox1;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TBitBtn *BitBtn2;
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall ListBox1DblClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall Label7Click(TObject *Sender);
	void __fastcall Label8Click(TObject *Sender);
	void __fastcall Label9Click(TObject *Sender);
	void __fastcall Label10Click(TObject *Sender);
	void __fastcall Label11Click(TObject *Sender);
	void __fastcall Label12Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
