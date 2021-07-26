//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
TMemoryStream *MS = new TMemoryStream ; // ������� �����
void Write(AnsiString Text);  // �-� ������ ���� � �����
int Size ; // ������ ����������� �����
bool Receive ; // �������� �� �� �� ������ ������ ����
AnsiString FileName ;  // ��� �����
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{       
}
//---------------------------------------------------------------------------
void Write(AnsiString Text)
{

if(MS->Size < Size)  // ���� �� ��� ��������� ���� � ������ ������ ������ ������� �����
{
MS->Write(Text.c_str(),Text.Length()); // ���������� � �����
FormMain->MemoConsole->Lines->Add("��������� ������..."); //
}
if(MS->Size == Size) // ���� ���� ������ � ������ ������ ������������� ������� �����
{
Receive = false ; // ������������� ����� ��������
MS->Position = 0 ;   // ��������� ����� � ������
FormMain->ClientSocket->Socket->SendText("end"); // �������� ������� ��� �� ������� ����
CreateDir("Files"); // ������� ����� ��� ����������� ������
MS->SaveToFile("Files\\"+FileName); // ��������� ���� ��� ����
MS->Clear() ; // ����������� �����
Size = 0 ;
FormMain->MemoConsole->Lines->Add("���� ������ !");

}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonConnectClick(TObject *Sender) //������ ����������� � �������
{
         if (EditPort->Text =="" || EditHost->Text =="" ||EditName->Text =="") ShowMessage("������� ��� ����!" );  //�������� �� ����������
            else{
        EditPort->Enabled = false; //��������� ���� ����� �����
        EditHost->Enabled = false; //��������� ���� ����� �����
        EditName->Enabled = false; //��������� ���� ����� ����
        ButtonConnect->Enabled = false; //��������� ������ �����������
        ClientSocket->Port = EditPort->Text.ToInt(); //������ ������� ���� ��� �����������
        ClientSocket->Host = EditHost->Text; //������ ������� ���� ��� �����������
        ClientSocket->Active = true; //�������� �������
        MemoConsole->Lines->Add("������������...");
                }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonSendClick(TObject *Sender) //������ ������� ���������
{
        ClientSocket->Socket->SendText(EditName->Text + ": " + EditMessage->Text); //�������� �� ������ ��� � ���������
        EditMessage->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket) //���������� ������ ���������
{
        if(RadioGroup1->ItemIndex == 0){
        MemoMessages->Lines->Add(Socket->ReceiveText());
        } //������� �� �������� ���������


        if(RadioGroup1->ItemIndex == 1){
AnsiString Rtext ;  // �����, ������� �������� ������
Rtext = ClientSocket->Socket->ReceiveText() ;
if(Receive == true) // ���� �� � ������ �������� �����, ��
{
Write(Rtext); // ���������� ��� � �����
}
else // ���� ��� , ��
{
MemoConsole->Lines->Add("������� ����� :" + Rtext);
if(Rtext.SubString(0,Rtext.Pos("#")-1) == "file") // ���� ��� ����, ��...
{
Rtext.Delete(1,Rtext.Pos("#")) ;    // ������� ����� file
Name = Rtext.SubString(0,Rtext.Pos("#")-1); // ���������� ��� �����
FileName = Name.SubString(Name.LastDelimiter("\\")+1,Name.Length()); ; // �������� ������ ��� ����� , �������� � c:\\test.txt , ����� test.txt
Rtext.Delete(1,Rtext.Pos("#")) ;  // ������� ��������� �����������
Size = StrToInt(Rtext.SubString(0,Rtext.Pos("#")-1)) ; // ���������� ������ �����
Rtext.Delete(1, Rtext.Pos("#")); // ������� ��������� �����������
MemoConsole->Lines->Add("������ �����: "+IntToStr(Size)+" ����"); // ������� ������ �����
MemoConsole->Lines->Add("��� �����: "+Name); // ������� ��� �����
Receive = true; // ��������� ������ � ����� ����� �����
if(Receive == true)
{
MemoConsole->Lines->Add("����� ������ ������");
}
}
}
}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action) //���������� �������� �����
{
        ClientSocket->Active = false; //��� �������� ����� ��������� �������        
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
if (ErrorCode == 10061)
{
 ErrorCode = 0; // ��� ��� �� ��������� �� ���� � ������������
 ShowMessage("��������� ������. ���������, ������ �� ��� ����!");
  EditPort->Enabled = true; //��������� ���� ����� �����
  EditHost->Enabled = true; //��������� ���� ����� �����
  EditName->Enabled = true; //��������� ���� ����� ����
  ButtonConnect->Enabled = true; //��������� ������ �����������
}
}
//---------------------------------------------------------------------------



void __fastcall TFormMain::ButtonClearClick(TObject *Sender)
{
        MemoMessages->Lines->Clear();
}
//---------------------------------------------------------------------------



void __fastcall TFormMain::Image1Click(TObject *Sender)
{
        MemoMessages->SelAttributes->Color = ColorBox1->Selected;
        MemoMessages->SelAttributes->Size = StrToInt(ComboBox1 -> Text);
}
//---------------------------------------------------------------------------



void __fastcall TFormMain::Image3Click(TObject *Sender)
{
        MemoMessages->Paragraph->Alignment = taLeftJustify;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Image4Click(TObject *Sender)
{
        MemoMessages->Paragraph->Alignment = taCenter;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Image5Click(TObject *Sender)
{
        MemoMessages->Paragraph->Alignment = taRightJustify;
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::ClientSocketConnecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
        MemoMessages->Lines->Add("�� ������������!");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RadioGroup1Click(TObject *Sender)
{
        if(RadioGroup1->ItemIndex == 1){ //���� ������ ����

              ButtonSend->Visible = false;
           }else{                            //���� ���������
                ButtonSend->Visible = true;
           
           }
}
//---------------------------------------------------------------------------


