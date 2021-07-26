//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *EditPort;
        TButton *ButtonStart;
        TEdit *EditMessage;
        TButton *ButtonSend;
        TServerSocket *ServerSocket;
        TColorBox *ColorBox1;
        TComboBox *ComboBox1;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image1;
        TRichEdit *MemoMessages;
        TBitBtn *BitBtn1;
        TOpenDialog *OpenDialog1;
        TRadioGroup *RadioGroup1;
        TMemo *MemoConsole;
        TEdit *EditName;
        TLabel *Label2;
        TLabel *Label3;
        void __fastcall ButtonStartClick(TObject *Sender);
        void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ButtonSendClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ServerSocketAccept(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Image3Click(TObject *Sender);
        void __fastcall Image4Click(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
        void SendingMessages(AnsiString Message);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
