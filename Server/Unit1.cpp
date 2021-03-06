//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TMemoryStream *MS = new TMemoryStream ;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}

void TForm1::SendingMessages(AnsiString Message) //??????? ???????? ?????????
{
 //if(RadioGroup1->ItemIndex == 0){
 MemoMessages->Lines->Add(Message); //????? ????????? ?? ?????
  for(int i = 0; i<ServerSocket->Socket->ActiveConnections; i++) //???? ?????????? ???? ????????????
  {
    ServerSocket->Socket->Connections[i]->SendText(Message); //???????? ?????????
  }
//}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonStartClick(TObject *Sender)
{           if (EditPort->Text =="") ShowMessage("??????? ????!" );  //???????? ?? ??????????
            else{
        EditPort->Enabled = false; //?????????? ???? ????? ?????
        ButtonStart->Enabled = false; //?????????? ?????? ???????
        ServerSocket->Port = EditPort->Text.ToInt(); //???????? ??????? ????
        ServerSocket->Active = true; //???, ?????????
        MemoMessages->Lines->Add("?????? ??????? ??????!");
                }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
         if(RadioGroup1->ItemIndex == 0){
         Label3->Caption=Socket->RemoteAddress;
         SendingMessages(Socket->ReceiveText());  //?????? ????????? ? ?????????
         }
         if(RadioGroup1->ItemIndex == 1)
         {


         for(int i = 0; i<ServerSocket->Socket->ActiveConnections; i++) //???? ?????????? ???? ????????????
  {
    if(ServerSocket->Socket->Connections[i]->ReceiveText()=="end")
    {
	MemoConsole->Lines->Add("?????? ?????? ????"); // ?????????? ? ???
	MS->Clear() ;                            // ??????? ?????
}
  }


         //if(ServerSocket->Socket->Connections[0]->ReceiveText()=="end") // ???? ?????? ??????? ??????? \"end\"

}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSendClick(TObject *Sender)
{
        SendingMessages(EditName->Text + ": " + EditMessage->Text);
        EditMessage->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        ServerSocket->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket)
{
        MemoMessages->Lines->Add("? ??? ????????????");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)
{
MemoMessages->Paragraph->Alignment = taLeftJustify;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{
MemoMessages->Paragraph->Alignment = taCenter;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5Click(TObject *Sender)
{
MemoMessages->Paragraph->Alignment = taRightJustify;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
        MemoMessages->SelAttributes->Color = ColorBox1->Selected;
        MemoMessages->SelAttributes->Size = StrToInt(ComboBox1 -> Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
void *P;
int Size ;
if(OpenDialog1->Execute())
{
MS->LoadFromFile(OpenDialog1->FileName);
MemoConsole->Lines->Add("????????? ????????? ???? ? ?????...");
}
SendingMessages("file#"+OpenDialog1->FileName+"#"+IntToStr(MS->Size)+'#');
MemoConsole->Lines->Add("??????? ???. ? ?????");
MS->Position = 0 ;
P = MS->Memory ;
    for(int i = 0; i<ServerSocket->Socket->ActiveConnections; i++) //???? ?????????? ???? ????????????
  {
Size = ServerSocket->Socket->Connections[i]->SendBuf(P,MS->Size);
}
MemoConsole->Lines->Add("??????????: " + IntToStr(Size)+" ?? "+ IntToStr(MS->Size));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
           if(RadioGroup1->ItemIndex == 1){ //???? ?????? ????
              BitBtn1->Visible = true;
              ButtonSend->Visible = false;
           }else{                            //???? ?????????
                ButtonSend->Visible = true;
                BitBtn1->Visible = false;
           }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   Label2->Caption="?????? ? ????: " + IntToStr(ServerSocket->Socket->ActiveConnections);
   Label3->Caption=Socket->RemoteAddress;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Label2->Caption="?????? ? ????: " + IntToStr(ServerSocket->Socket->ActiveConnections);

}
//---------------------------------------------------------------------------

