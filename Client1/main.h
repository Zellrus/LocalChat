//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *LabelPort;
        TEdit *EditPort;
        TLabel *LabelHost;
        TEdit *EditHost;
        TButton *ButtonConnect;
        TEdit *EditMessage;
        TButton *ButtonSend;
        TClientSocket *ClientSocket;
        TLabel *Label1;
        TEdit *EditName;
        TLabel *Label2;
        TRichEdit *MemoMessages;
        TButton *ButtonClear;
        TColorBox *ColorBox1;
        TComboBox *ComboBox1;
        TImage *Image1;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TSaveDialog *SaveDialog1;
        TMemo *MemoConsole;
        TRadioGroup *RadioGroup1;
        TLabel *Label3;
        void __fastcall ButtonConnectClick(TObject *Sender);
        void __fastcall ButtonSendClick(TObject *Sender);
        void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ClientSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ButtonClearClick(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall Image3Click(TObject *Sender);
        void __fastcall Image4Click(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall ClientSocketConnecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall RadioGroup1Click(TObject *Sender);
private:	
	AnsiString Name; 	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
