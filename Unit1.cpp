//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ShellAPI.h"
#include "IniFiles.hpp"
#include "Unit1.h"
#include "ABOUT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//?????????? ??? ???????? ???? ???????? ?????
AnsiString DelFile = "";

//?????????? ??? ???????? ????????? ??????????? ?????
int Final_Ball = 0;

//?????????? ??? ???????? ?????????? ????? ????????????
AnsiString Temporary_Login = "";

//?????????? ??? ???????? ?????????? ?????? ????????????
AnsiString Temporary_Password = "";

//????? ??????? ??????
AnsiString Login = "";

//?????? ?? ??????? ??????
AnsiString Password = "";


//???????? Login
AnsiString User_Login = "";

//???????? ?????? ????????????
AnsiString User_Password = "";


//??????? ?????? TStringList ??? ???????????? ????? ? ??????????????
TStringList *Update = new TStringList;
TSearchRec sr;

//????? ????? ?? ?????????
void __fastcall TForm1::Course_Reset(TObject *Sender)
{
	if(Form1->edtConfirmation_2->Text == User_Password)
	{
		btnTest_01->Enabled = true;
		btnTest_02->Enabled = true;
		btnTest_03->Enabled = true;
		btnTest_04->Enabled = true;
		Final_Ball = 0;
		WriteParams(Sender);
		pnlConfirmation_2->Visible = false;
		pnlConfirmation_2->Enabled = false;
		ReadParams(Sender);
	}
}

//???????? ???????? ????????????
void __fastcall TForm1::Account_Deleting(TObject *Sender)
{
	if(Form1->edtConfirmation->Text == User_Password)
	{
		DelFile = (ExtractFilePath(Application->ExeName) + L"\\Users\\" + Login + L".ini");
		DeleteFile(DelFile);
		Login = "";
		Password = "";
		User_Login = "";
		User_Password = "";
		Login_Status(Sender);
		pnlConfirmation->Visible = false;
		pnlConfirmation->Enabled = false;
		btnDeleteYourAccount->Caption = "??????? ??????? ??????";
	}

}

//???????????? ????? ?? ????? ?????????????
void Scanning()
{
	//???????? ?????????? ?????? ? ????? ?????????????
	if(FindFirst(ExtractFilePath(Application->ExeName)+L"\\Users"+L"\\*.ini*",faAnyFile, sr)==0)
	{
		Update->Clear();
		if(CompareText(ExtractFileExt(sr.Name),".ini")==0)Update->Add(ExtractFileName(sr.Name));
		while(FindNext(sr) == 0)
		{
			if(CompareText(ExtractFileExt(sr.Name),".ini")==0)Update->Add(ExtractFileName(sr.Name));
		}
	}
	FindClose(sr);
	Form1->lbList_Login->Clear();
	for(int i = 0; i < Update->Count;i++)
	{
		Form1->lbList_Login->Items->Add(Update->Strings[i].Delete(Update->Strings[i].Length()-3,4));
	}
	Update->Clear();
}

 void __fastcall TForm1::Login_Verification(TObject *Sender)
 {
	//?????????, ??? ???????? ????? ? ?????? ?? ??????
	if((Temporary_Login != "")&&(Temporary_Password != ""))
	{
		if(Form1->lbList_Login->Count > 0)
		{
			//???? ??? - ?? ?????? ?????? 0, ????????? ????
			int Login_Verification = 0;
			for(int i = 0; i <= Form1->lbList_Login->Count-1; i++)
			{
				//???? ???? ????? ?????, ?? ?? ????????? ???????? ?????? ????????
				if(Temporary_Login == Form1->lbList_Login->Items->Strings[i])
				{
					Login_Verification = 1;
					break;

				}
			}
			if(Login_Verification == 0)
			{
				//??????? ????? ???????

				Login = Temporary_Login;
				Password = Temporary_Password;

				User_Login = Login;
				User_Password = Password;

				WriteParams(Sender);

				Temporary_Login = "";
				Temporary_Password = "";

				//????????? ????? ????????????
				Scanning();

				//????????? ?????? ????????????
				Login_Status(Sender);
			}
		}
		else if(Form1->lbList_Login->Count == 0)
		{
			//???? ??? - ?? ?????? ????? 0, ?? ??????? ????? ???????

			Login = Temporary_Login;
			Password = Temporary_Password;

			User_Login = Login;
			User_Password = Password;

			WriteParams(Sender);

			Temporary_Login = "";
			Temporary_Password = "";

			//????????? ????? ????????????
			Scanning();

			//????????? ?????? ?????
			Login_Status(Sender);
		}
	}
 }

 //?????????? ???????????? ? ini-????
void __fastcall TForm1::WriteParams(TObject *Sender)
{
	//??????? ?????? Ini ???????????? ??? ????????????.ini ??? ?????? ? ?????????????
	if((Login != "")&&(Password != ""))
	{
		//??????? ?????? Ini ???????????? ??? ????????????.ini ??? ?????? ? ?????????????
		TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+L"\\Users" + L"\\" + Login + L".ini");

		//??????? ? ???? ????? ????????????
		Ini->WriteString("User", "Login", Login);

		//??????? ? ???? ?????? ????????????
		Ini->WriteString("User", "Password", Password);

		//??????? ? ???? ????????? ?????????
		Ini->WriteInteger("Settings", "tsSV_Settings_Status_01", tsSV_Settings_Status_01->State);
		Ini->WriteInteger("Settings", "tsSV_Settings_Status_02", tsSV_Settings_Status_02->State);
		Ini->WriteInteger("Settings", "tsSV_Settings_Status_03", tsSV_Settings_Status_03->State);
		Ini->WriteInteger("Settings", "tsSV_Settings_Status_04", tsSV_Settings_Status_04->State);
		Ini->WriteInteger("Settings", "Final_Ball", Final_Ball);
		Ini->WriteBool("Settings", "btnTest_01", btnTest_01->Enabled);
		Ini->WriteBool("Settings", "btnTest_02", btnTest_02->Enabled);
		Ini->WriteBool("Settings", "btnTest_03", btnTest_03->Enabled);
		Ini->WriteBool("Settings", "btnTest_04", btnTest_04->Enabled);
		Ini->UpdateFile();
	}
}

//???????? ???????????? ?? ini - ?????
void __fastcall TForm1::ReadParams(TObject *Sender)
{
	//??????? ?????? Ini ???????????? ??? ????????????.ini ??? ?????? ? ?????????????
	TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+L"\\Users" + L"\\" + Login + L".ini");
	//???????? ?????????
	tsSV_Settings_Status_01->State = TToggleSwitchState(Ini->ReadInteger("Settings", "tsSV_Settings_Status_01", 0));
	tsSV_Settings_Status_02->State = TToggleSwitchState(Ini->ReadInteger("Settings", "tsSV_Settings_Status_02", 0));
	tsSV_Settings_Status_03->State = TToggleSwitchState(Ini->ReadInteger("Settings", "tsSV_Settings_Status_03", 0));
	tsSV_Settings_Status_04->State = TToggleSwitchState(Ini->ReadInteger("Settings", "tsSV_Settings_Status_04", 1));
	User_Password = Ini->ReadString("User", "Password", "admin1");
	Final_Ball = Ini->ReadInteger("Settings", "Final_Ball", 0);
	btnTest_01->Enabled = Ini->ReadBool("Settings", "btnTest_01", true);
	btnTest_02->Enabled = Ini->ReadBool("Settings", "btnTest_02", true);
	btnTest_03->Enabled = Ini->ReadBool("Settings", "btnTest_03", true);
	btnTest_04->Enabled = Ini->ReadBool("Settings", "btnTest_04", true);
}

 //???????? ??????? ????? ? ???????
void __fastcall TForm1::Login_Status(TObject *Sender)
{
	if((User_Login != "")&&(User_Password != ""))
	{
		//??????? ??? ???????? ???????????? ? ???????
		lbSV_Settings_Account_Name->Caption = User_Login;
		//????????? ??????? ??????? ??????
		btnDeleteYourAccount->Enabled = true;
		//????????? ????? ?????
		btnResetDefaultCourse->Enabled = true;
		//????????? ????????? ??????
		btnSV_Settings_Password_Reset->Enabled = true;
		//?????? ???????? ?????? ???? ?? ?????
		btnSV_Setting_Profile_Exit->Caption = "?????";
		//????????? ??????????? ??????????
		ActiveInd_SV_Settings_Profile_Status->Animate = false;
		ActiveInd_SV_Settings_Profile_Status->Visible = false;
		//?????????? ?????? ???????
		imgProfile_Settings->Visible = true;
		imgProfile_Settings->BringToFront();
		//???????? ??????????? ????????? ???????? ?????????????
		tsSV_Settings_Status_01->Enabled = true;
		tsSV_Settings_Status_02->Enabled = true;
		tsSV_Settings_Status_03->Enabled = true;
		tsSV_Settings_Status_04->Enabled = true;

		//???????????? ???? ??? ????????
		pnlTopic_01->Enabled = true;
		pnlTopic_02->Enabled = true;
		pnlTopic_03->Enabled = true;
		pnlTopic_04->Enabled = true;
		pnlTopic_05->Enabled = true;
		pnlTopic_06->Enabled = true;
		pnlTopic_07->Enabled = true;
		pnlTopic_08->Enabled = true;
		pnlTopic_09->Enabled = true;
		pnlTopic_10->Enabled = true;
		pnlTopic_11->Enabled = true;
		pnlTopic_12->Enabled = true;
		pnlTopic_13->Enabled = true;
		pnlTopic_14->Enabled = true;
		pnlTopic_15->Enabled = true;
		pnlTopic_16->Enabled = true;
		pnlTopic_17->Enabled = true;
		pnlTopic_18->Enabled = true;
		pnlTopic_19->Enabled = true;
		pnlTopic_20->Enabled = true;
		pnlTopic_21->Enabled = true;
		pnlTopic_22->Enabled = true;
		pnlTopic_23->Enabled = true;
		pnlTopic_24->Enabled = true;
		pnlTopic_25->Enabled = true;
		pnlTopic_26->Enabled = true;
		pnlTopic_27->Enabled = true;
		pnlTopic_28->Enabled = true;
		pnlTopic_29->Enabled = true;
		pnlTopic_30->Enabled = true;
		pnlTopic_31->Enabled = true;
		pnlTopic_32->Enabled = true;
		pnlTopic_33->Enabled = true;
		pnlTopic_34->Enabled = true;
		pnlTopic_35->Enabled = true;
		pnlTopic_36->Enabled = true;
		//?????? ???? ???????????
		pnlValidation->Visible = false;
		pnlValidation->Enabled = false;
		Sleep(100);
		ReadParams(Sender);
	}
	else
	{
		//????????, ??? ???? ?? ????????
		lbSV_Settings_Account_Name->Caption = "???? ?? ????????";
		//????????? ??????? ??????? ??????
		btnDeleteYourAccount->Enabled = false;
		//????????? ????? ?????
		btnResetDefaultCourse->Enabled = false;
		//????????? ????????? ??????
		btnSV_Settings_Password_Reset->Enabled = false;
		//?????? ???????? ?????? ????? ?? ????
		btnSV_Setting_Profile_Exit->Caption = "?????";
		//???????? ??????????? ??????????
		ActiveInd_SV_Settings_Profile_Status->Visible = true;
		ActiveInd_SV_Settings_Profile_Status->Animate = true;
		ActiveInd_SV_Settings_Profile_Status->BringToFront();
		//????????? ?????? ???????
		imgProfile_Settings->Visible = false;
		//????????? ??????????? ????????? ???????? ?????????????
		tsSV_Settings_Status_01->Enabled = false;
		tsSV_Settings_Status_02->Enabled = false;
		tsSV_Settings_Status_03->Enabled = false;
		tsSV_Settings_Status_04->Enabled = false;
		//?????????? ???? ???????????
		pnlValidation->Visible = true;
		pnlValidation->Enabled = true;

		//????????? ???? ??? ????????
		pnlTopic_01->Enabled = false;
		pnlTopic_02->Enabled = false;
		pnlTopic_03->Enabled = false;
		pnlTopic_04->Enabled = false;
		pnlTopic_05->Enabled = false;
		pnlTopic_06->Enabled = false;
		pnlTopic_07->Enabled = false;
		pnlTopic_08->Enabled = false;
		pnlTopic_09->Enabled = false;
		pnlTopic_10->Enabled = false;
		pnlTopic_11->Enabled = false;
		pnlTopic_12->Enabled = false;
		pnlTopic_13->Enabled = false;
		pnlTopic_14->Enabled = false;
		pnlTopic_15->Enabled = false;
		pnlTopic_16->Enabled = false;
		pnlTopic_17->Enabled = false;
		pnlTopic_18->Enabled = false;
		pnlTopic_19->Enabled = false;
		pnlTopic_20->Enabled = false;
		pnlTopic_21->Enabled = false;
		pnlTopic_22->Enabled = false;
		pnlTopic_23->Enabled = false;
		pnlTopic_24->Enabled = false;
		pnlTopic_25->Enabled = false;
		pnlTopic_26->Enabled = false;
		pnlTopic_27->Enabled = false;
		pnlTopic_28->Enabled = false;
		pnlTopic_29->Enabled = false;
		pnlTopic_30->Enabled = false;
		pnlTopic_31->Enabled = false;
		pnlTopic_32->Enabled = false;
		pnlTopic_33->Enabled = false;
		pnlTopic_34->Enabled = false;
		pnlTopic_35->Enabled = false;
		pnlTopic_36->Enabled = false;
	}
}

//???????? ?????? ????????????
void __fastcall TForm1::Validation(TObject *Sender)
{
	if(Temporary_Login != "")
	{
		AnsiString Validation = "";
		for(int i = 0; i <= Form1->lbList_Login->Count-1; i++)
		{
			Validation = Form1->lbList_Login->Items->Strings[i];
			if(Validation == Temporary_Login)
			{
				Login = Validation;
				User_Login = Validation;
				Validation = "";
				//??????? ?????? Ini ???????????? ??? ????????????.ini ??? ?????? ? ?????????????
				TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+L"\\Users" + L"\\" + Login + L".ini");
				AnsiString Validation_Password = "";
				Validation_Password = Ini->ReadString("User", "Password", "admin1");
				if(Validation_Password == Temporary_Password)
				{
					User_Password = Validation_Password;
					Password = User_Password;
				}
				else if(Validation_Password != Temporary_Password)
				{
					edValidation_Password_01->Text = "";
					edValidation_Password_01->TextHint = "???????? ??????!";
					edValidation_Password_01->Font->Color = clRed;
					break;
				}
			}
			else if(Validation != Temporary_Login)
			{
				edValidation_Login_01->Text = "";
				edValidation_Login_01->TextHint = "???????? ?????!";
				edValidation_Login_01->Font->Color = clRed;
				break;
			}
		}

		//????????? ?????? ?????
		Login_Status(Sender);
	}
}

//?????? ??????
void __fastcall TForm1::Change_Password(TObject *Sender)
{
	if(Form1->edReset_Password->Text == User_Password)
	{
		if(Form1->edNew_Password_01->Text == Form1->edNew_Password_02->Text)
		{
			User_Password = Form1->edNew_Password_02->Text;
			Password = Form1->edNew_Password_02->Text;

			pnlReset_Password->Visible = false;

			btnSV_Settings_Password_Reset->Caption = "???????? ??????";
			WriteParams(Sender);
		}
	}
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	//????????? ?????????? ??? ?????? ??????
	Form1->Width = Screen->Width;
	Form1->Height = Screen->Height;

	if((Form1->Width >= 1600)&&(Form1->Height >= 900))
	{
		Form1->Width = 1600;
		Form1->Height = 900;
	}
	else
	{
		/*if(mrOk == MessageDlg("????????! ????????? ?? ???????????? ??????? ?????? ???? ??????????? 1600 x 900. ?????????? ????? ???????", mtInformation,TMsgDlgButtons() <<mbOK, 0))
		{
			Application->Terminate();
		}*/
		Form1->Width = 1600;
        Form1->Height = Screen->Height;
	}
	//????????? ??????? ???? ? ?????????? ?????
	SV->Close();
	//????????? ???? ???????? ? ??????? ?????
	SV_Settings->Close();
	//????????? ????????? ???? ? ??????? ?????
	pnlTopControl->Height = 1;
	//??????? ?????? Home ?? ??????? ?????
	pnlHome->BringToFront();
	pnlHome->Enabled = true;
	pnlHome->Visible = true;
	//????????? ???? ????? ? ???????? ?????
	pnlValidation->Visible = true;
	//????????? ????? ?????????????
	Scanning();
	//????????? ?????? ????? ? ???????
	Login_Status(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::actMenuExecute(TObject *Sender)
{
	//?????????? ?????????? ???????? ????
	SV->BringToFront();
	if(SV->Opened)
	{
		SV->Close();
	}
	else
	{
		SV->Open();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actExitExecute(TObject *Sender)
{
	//????????? ????????? ??????????
	if(tsSV_Settings_Status_04->State == tssOn)
	{
		//????????? ????????? ??????? ??????
		WriteParams(Sender);
	}
	//?????????? ?????? ?????????
	Sleep(100);
	Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actSettingsExecute(TObject *Sender)
{
	//?????????? ?????????? ???? ????????
	SV_Settings->BringToFront();
	if(SV_Settings->Opened)
	{
		SV_Settings->Close();
	}
	else
	{
		SV_Settings->Open();
	}
	if((SV->Opened)&&(tsSV_Settings_Status_02->State == tssOn))
	{
		//????????? ??????? ???? ???? ?????? ????? ? ??????????
		SV->Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imgTopControlSystemMenuClick(TObject *Sender)
{
	//????? ?????????? ???????
	pmTopControlSystemMenu->Popup(0,30);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actHomeExecute(TObject *Sender)
{
	//?????? ??? ?????? ????? Home
	pnlProfile->Enabled = false;
	pnlProfile->Visible = false;
	pnlTraining->Enabled = false;
	pnlTraining->Visible = false;
	pnlStatistics->Enabled = false;
	pnlStatistics->Visible = false;
	pnlHelp->Enabled = false;
	pnlHelp->Visible = false;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//??????? ?????? Home
	pnlHome->BringToFront();
	pnlHome->Enabled = true;
	pnlHome->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actProfileExecute(TObject *Sender)
{   //?????? ??? ?????? ????? Profile
	pnlHome->Enabled = false;
	pnlHome->Visible = false;
	pnlTraining->Enabled = false;
	pnlTraining->Visible = false;
	pnlStatistics->Enabled = false;
	pnlStatistics->Visible = false;
	pnlHelp->Enabled = false;
	pnlHelp->Visible = false;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//??????? ?????? Profile
	pnlProfile->BringToFront();
	pnlProfile->Enabled = true;
	pnlProfile->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actTrainingExecute(TObject *Sender)
{   //?????? ??? ?????? ????? Training
	pnlHome->Enabled = false;
	pnlHome->Visible = false;
	pnlProfile->Enabled = false;
	pnlProfile->Visible = false;
	pnlStatistics->Enabled = false;
	pnlStatistics->Visible = false;
	pnlHelp->Enabled = false;
	pnlHelp->Visible = false;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//??????? ?????? Training
	pnlTraining->BringToFront();
	pnlTraining->Enabled = true;
	pnlTraining->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actStatisticsExecute(TObject *Sender)
{
	//?????? ??? ?????? ????? Statistics
	pnlHome->Enabled = false;
	pnlHome->Visible = false;
	pnlProfile->Enabled = false;
	pnlProfile->Visible = false;
	pnlTraining->Enabled = false;
	pnlTraining->Visible = false;
	pnlHelp->Enabled = false;
	pnlHelp->Visible = false;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//??????? ?????? Statistics
	pnlStatistics->BringToFront();
	pnlStatistics->Enabled = true;
	pnlStatistics->Visible = true;

	//?????????? ???????? ??????????? ?????
	gueProgressProgress_01->Progress = 0;
	for(int X = 0; X < Final_Ball; X++)
	{
		Sleep(10);
		gueProgressProgress_01->Progress += 1;
	}

	if((Final_Ball > 0)&&(Final_Ball < 40))
	{
		pnlValue_1->Color = (TColor)RGB(161, 70, 0);
		pnlValue_1->Caption = "???? ??????: 1";
		pnlValue_2->Color = clBlack;
		pnlValue_3->Color = clBlack;
		pnlValue_4->Color = clBlack;
		pnlValue_5->Color = clBlack;
	}
	if((Final_Ball >= 40)&&(Final_Ball < 60))
	{
		pnlValue_1->Color = (TColor)RGB(161, 70, 0);
		pnlValue_1->Caption = "";
		pnlValue_2->Color = (TColor)RGB(161, 0, 0);
		pnlValue_2->Caption = "???? ??????: 2";
		pnlValue_3->Color = clBlack;
		pnlValue_4->Color = clBlack;
		pnlValue_5->Color = clBlack;
	}
	if((Final_Ball >= 60)&&(Final_Ball < 80))
	{
		pnlValue_1->Color = (TColor)RGB(161, 70, 0);
		pnlValue_1->Caption = "";
		pnlValue_2->Color = (TColor)RGB(161, 0, 0);
		pnlValue_2->Caption = "";
		pnlValue_3->Color = (TColor)RGB(235, 76, 2);
		pnlValue_3->Caption = "???? ??????: 3";
		pnlValue_4->Color = clBlack;
		pnlValue_5->Color = clBlack;
	}
	if((Final_Ball >= 80)&&(Final_Ball < 100))
	{
		pnlValue_1->Color = (TColor)RGB(161, 70, 0);
		pnlValue_1->Caption = "";
		pnlValue_2->Color = (TColor)RGB(161, 0, 0);
		pnlValue_2->Caption = "";
		pnlValue_3->Color = (TColor)RGB(235, 76, 2);
		pnlValue_3->Caption = "";
		pnlValue_4->Color = (TColor)RGB(235, 173, 2);
		pnlValue_4->Caption = "???? ??????: 4";
		pnlValue_5->Color = clBlack;
	}
	if(Final_Ball == 100)
	{
		pnlValue_1->Color = (TColor)RGB(161, 70, 0);
		pnlValue_1->Caption = "";
		pnlValue_2->Color = (TColor)RGB(161, 0, 0);
		pnlValue_2->Caption = "";
		pnlValue_3->Color = (TColor)RGB(235, 76, 2);
		pnlValue_3->Caption = "";
		pnlValue_4->Color = (TColor)RGB(235, 173, 2);
		pnlValue_4->Caption = "";
		pnlValue_5->Color = (TColor)RGB(2, 235, 22);
		pnlValue_5->Caption = "???? ??????: 5";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actHelpExecute(TObject *Sender)
{
	//?????? ??? ?????? ????? Help
	pnlHome->Enabled = true;
	pnlHome->Visible = true;
	pnlProfile->Enabled = true;
	pnlProfile->Visible = true;
	pnlTraining->Enabled = true;
	pnlTraining->Visible = true;
	pnlStatistics->Enabled = true;
	pnlStatistics->Visible = true;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//??????? ?????? Help
	//pnlHelp->BringToFront();
	//pnlHelp->Enabled = true;
	//pnlHelp->Visible = true;

	//????????? ???????? ??????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Help\\??????????? ????????????.pdf").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actAboutExecute(TObject *Sender)
{
	//?????? ??? ?????? ????? About
	pnlHome->Enabled = true	;
	pnlHome->Visible = true;
	pnlProfile->Enabled = true;
	pnlProfile->Visible = true;
	pnlTraining->Enabled = true;
	pnlTraining->Visible = true;
	pnlStatistics->Enabled = true;
	pnlStatistics->Visible = true;
	pnlHelp->Enabled = true;
	pnlHelp->Visible = true;
	//??????? ?????? About
	//pnlAbout->BringToFront();
	//pnlAbout->Enabled = true;
	//pnlAbout->Visible = true;
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopControlMouseEnter(TObject *Sender)
{
	//????????? ????????? ?????? TopControl
	pnlTopControl->BringToFront();
	if(pnlTopControl->Height == 1)
	{
		//????????? ????????? ??????
		for(int Value_1 = 1; Value_1 <= 30; Value_1++)
		{
			pnlTopControl->Height = Value_1;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
	//?????? ??? ?????? ????? Help
	pnlHome->Enabled = false;
	pnlHome->Visible = false;
	pnlProfile->Enabled = false;
	pnlProfile->Visible = false;
	pnlTraining->Enabled = false;
	pnlTraining->Visible = false;
	pnlStatistics->Enabled = false;
	pnlStatistics->Visible = false;
	pnlAbout->Enabled = false;
	pnlAbout->Visible = false;
	//???????? ?????? Help
	pnlHelp->BringToFront();
	pnlHelp->Enabled = true;
	pnlHelp->Visible = true;
	//????????? ????????? ??????
	pnlTopControl->Height = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	//????????? ????????? ??????
	pnlTopControl->Height = 1;
	//???????? ???? ???????? SV_Settings
	SV_Settings->BringToFront();
	SV_Settings->Open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlHomeClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::pnlProfileClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTrainingClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlStatisticsClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlHelpClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlAboutClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SVClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
	//????????? ???? ????????
	SV_Settings->BringToFront();
	SV_Settings->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::catMenuItemsClick(TObject *Sender)
{
	//????????? ????????? ????
	pnlTopControl->Height = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tsSV_Settings_Status_03Click(TObject *Sender)
{
	if(tsSV_Settings_Status_03->State == tssOn)
	{
		//????????? ?????????? ? ??????? ?????
		Form1->Width = 1000;
		Form1->Height = 700;
		Form1->BorderStyle = bsSingle;
	}
	else
	{
		//????????? ?????????? ? ????????????? ?????
		Form1->Position = poDesktopCenter;
		Form1->Width = Screen->Width;
		Form1->Height = Screen->Height;
		Form1->BorderStyle = bsNone;
		Form1->WindowState = wsMaximized;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edValidation_Login_01KeyPress(TObject *Sender, System::WideChar &Key)
{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edValidation_Password_01KeyPress(TObject *Sender, System::WideChar &Key)
{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnValidation_Entrance_01Click(TObject *Sender)
{
	//???? ? ???????

	//?????????? ?? ???????? ?????
	Temporary_Login = edValidation_Login_01->Text;

	 //?????????? ?? ???????? ??????
	Temporary_Password = edValidation_Password_01->Text;

	//????????? ???????????? ??????
	Validation(Sender);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbRegistrationMouseLeave(TObject *Sender)
{
	//????????????? ?????????
	lbRegistration->Font->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbRegistrationClick(TObject *Sender)
{
	//??????????? ? ???????

	//?????????? ?? ???????? ?????
	Temporary_Login = edValidation_Login_01->Text;

	//?????????? ?? ???????? ??????
	Temporary_Password = edValidation_Password_01->Text;

	//????????? ?? ???????????, ? ???? ????????, ?? ???????
	Login_Verification(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbRegistrationMouseEnter(TObject *Sender)
{
	//????????????? ?????????
	lbRegistration->Font->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnSV_Setting_Profile_ExitClick(TObject *Sender)
{
	if(btnSV_Setting_Profile_Exit->Caption == "?????")
	{
		//??????? ?? ??????? ??????

		//??????? ?????
		User_Login = "";
		User_Password = "";
		Login_Status(Sender);
        pnlProfile->BringToFront();
		pnlProfile->Enabled = true;
		pnlProfile->Visible = true;
	}
	else if(btnSV_Setting_Profile_Exit->Caption == "?????")
	{
		//?????? ??? ?????? ????? Profile
		pnlHome->Enabled = false;
		pnlHome->Visible = false;
		pnlTraining->Enabled = false;
		pnlTraining->Visible = false;
		pnlStatistics->Enabled = false;
		pnlStatistics->Visible = false;
		pnlHelp->Enabled = false;
		pnlHelp->Visible = false;
		pnlAbout->Enabled = false;
		pnlAbout->Visible = false;
		//??????? ?????? Profile
		pnlProfile->BringToFront();
		pnlProfile->Enabled = true;
		pnlProfile->Visible = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnSV_Settings_Password_ResetClick(TObject *Sender)
{
	if(pnlReset_Password->Visible == true)
	{
        pnlProfile->BringToFront();
		pnlProfile->Enabled = true;
		pnlProfile->Visible = true;

		btnSV_Settings_Password_Reset->Caption = "???????? ??????";
		pnlReset_Password->Visible = false;
	}
	else if(pnlReset_Password->Visible == false)
	{
		btnSV_Settings_Password_Reset->Caption = "????????";
		pnlReset_Password->Visible = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edReset_PasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edNew_Password_01KeyPress(TObject *Sender, System::WideChar &Key)
{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edNew_Password_02KeyPress(TObject *Sender, System::WideChar &Key)
{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnResetClick(TObject *Sender)
{
	//????????? ?????? ??????? ??????

	//?????? ?????? ??????? ??????
	Change_Password(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pnlTopic_01MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_01->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_01MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_01->Color = clMenu;
	if(pnlTopic_Selected_01->Visible == true)
	{
		pnlTopic_01->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_02MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_02->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_02MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_02->Color = clMenu;
	if(pnlTopic_Selected_02->Visible == true)
	{
		pnlTopic_02->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_03MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_03->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_03MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_03->Color = clMenu;
	if(pnlTopic_Selected_03->Visible == true)
	{
		pnlTopic_03->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_04MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_04->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_04MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_04->Color = clMenu;
	if(pnlTopic_Selected_04->Visible == true)
	{
		pnlTopic_04->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_05MouseEnter(TObject *Sender)
{
	 //????????????? ????
	pnlTopic_05->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_05MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_05->Color = clMenu;
	if(pnlTopic_Selected_05->Visible == true)
	{
		pnlTopic_05->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_06MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_06->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_06MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_06->Color = clMenu;
	if(pnlTopic_Selected_06->Visible == true)
	{
		pnlTopic_06->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_07MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_07->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_07MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_07->Color = clMenu;
	if(pnlTopic_Selected_07->Visible == true)
	{
		pnlTopic_07->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_08MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_08->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_08MouseLeave(TObject *Sender)
{
	 //????????????? ????
	pnlTopic_08->Color = clMenu;
	if(pnlTopic_Selected_08->Visible == true)
	{
		pnlTopic_08->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_09MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_09->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_09MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_09->Color = clMenu;
	if(pnlTopic_Selected_09->Visible == true)
	{
		pnlTopic_09->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_10MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_10->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_10MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_10->Color = clMenu;
	if(pnlTopic_Selected_10->Visible == true)
	{
		pnlTopic_10->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_11MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_11->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_11MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_11->Color = clMenu;
	if(pnlTopic_Selected_11->Visible == true)
	{
		pnlTopic_11->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_12MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_12->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_12MouseLeave(TObject *Sender)
{
	 //????????????? ????
	pnlTopic_12->Color = clMenu;
	if(pnlTopic_Selected_12->Visible == true)
	{
		pnlTopic_12->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_13MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_13->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_13MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_13->Color = clMenu;
	if(pnlTopic_Selected_13->Visible == true)
	{
		pnlTopic_13->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_14MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_14->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_14MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_14->Color = clMenu;
	if(pnlTopic_Selected_14->Visible == true)
	{
		pnlTopic_14->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_15MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_15->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_15MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_15->Color = clMenu;
	if(pnlTopic_Selected_15->Visible == true)
	{
		pnlTopic_15->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_16MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_16->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_16MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_16->Color = clMenu;
	if(pnlTopic_Selected_16->Visible == true)
	{
		pnlTopic_16->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_17MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_17->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_17MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_17->Color = clMenu;
	if(pnlTopic_Selected_17->Visible == true)
	{
		pnlTopic_17->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_18MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_18->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_18MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_18->Color = clMenu;
	if(pnlTopic_Selected_18->Visible == true)
	{
		pnlTopic_18->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_19MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_19->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_19MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_19->Color = clMenu;
	if(pnlTopic_Selected_19->Visible == true)
	{
		pnlTopic_19->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_20MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_20->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_20MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_20->Color = clMenu;
	if(pnlTopic_Selected_20->Visible == true)
	{
		pnlTopic_20->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_21MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_21->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_21MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_21->Color = clMenu;
	if(pnlTopic_Selected_21->Visible == true)
	{
		pnlTopic_21->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_22MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_22->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_22MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_22->Color = clMenu;
	if(pnlTopic_Selected_22->Visible == true)
	{
		pnlTopic_22->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_23MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_23->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_23MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_23->Color = clMenu;
	if(pnlTopic_Selected_23->Visible == true)
	{
		pnlTopic_23->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_24MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_24->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_24MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_24->Color = clMenu;
	if(pnlTopic_Selected_24->Visible == true)
	{
		pnlTopic_24->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_25MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_25->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_25MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_25->Color = clMenu;
	if(pnlTopic_Selected_25->Visible == true)
	{
		pnlTopic_25->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_26MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_26->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_26MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_26->Color = clMenu;
	if(pnlTopic_Selected_26->Visible == true)
	{
		pnlTopic_26->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_27MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_27->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_27MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_27->Color = clMenu;
	if(pnlTopic_Selected_27->Visible == true)
	{
		pnlTopic_27->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_28MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_28->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_28MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_28->Color = clMenu;
	if(pnlTopic_Selected_28->Visible == true)
	{
		pnlTopic_28->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_29MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_29->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_29MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_29->Color = clMenu;
	if(pnlTopic_Selected_29->Visible == true)
	{
		pnlTopic_29->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_30MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_30->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_30MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_30->Color = clMenu;
	if(pnlTopic_Selected_30->Visible == true)
	{
		pnlTopic_30->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_31MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_31->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_31MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_31->Color = clMenu;
	if(pnlTopic_Selected_31->Visible == true)
	{
		pnlTopic_31->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_32MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_32->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_32MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_32->Color = clMenu;
	if(pnlTopic_Selected_32->Visible == true)
	{
		pnlTopic_32->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_33MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_33->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_33MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_33->Color = clMenu;
	if(pnlTopic_Selected_33->Visible == true)
	{
		pnlTopic_33->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_34MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_34->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_34MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_34->Color = clMenu;
	if(pnlTopic_Selected_34->Visible == true)
	{
		pnlTopic_34->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_35MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_35->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_35MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_35->Color = clMenu;
	if(pnlTopic_Selected_35->Visible == true)
	{
		pnlTopic_35->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_36MouseEnter(TObject *Sender)
{
	//????????????? ????
	pnlTopic_36->Color = clGradientInactiveCaption;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_36MouseLeave(TObject *Sender)
{
	//????????????? ????
	pnlTopic_36->Color = clMenu;
	if(pnlTopic_Selected_36->Visible == true)
	{
		pnlTopic_36->Color = clGradientInactiveCaption;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::scrClassesMouseWheelDown(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	//??????? ???????? ????? ?????
	scrClasses->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::scrClassesMouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	//??????? ???????? ????? ?????
	scrClasses->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_01Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_01->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_1.rtf");
	//???? ?????????? ??????
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = true;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_01->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pnlTopic_02Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_02->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_2.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = true;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_02->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_03Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_03->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_3.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = true;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_03->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_04Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_04->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_4.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = true;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_04->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_05Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_05->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_5.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = true;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_05->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_06Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_06->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_6.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = true;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_06->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_07Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_07->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_7.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = true;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_07->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_08Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_08->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_8.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = true;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_08->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_09Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_09->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_9.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = true;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_09->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_10Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_10->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????1_???????_10.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = true;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_10->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_11Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_11->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_1.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = true;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_11->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_12Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_12->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_2.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = true;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_12->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_13Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
    Ric_13->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_3.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = true;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_13->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_14Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_14->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_4.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = true;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_14->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_15Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_15->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_5.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = true;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_15->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_16Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_16->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_6.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = true;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_16->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_17Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_17->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_7.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = true;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_17->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_18Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_18->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_8.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = true;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_18->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_19Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
    Ric_19->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????2_???????_9.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = true;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_19->BringToFront();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::pnlTopic_20Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_20->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_1.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = true;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_20->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_21Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_21->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_2.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = true;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_21->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_22Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_22->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_3.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = true;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_22->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_23Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_23->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_4.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = true;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_23->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_24Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_24->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_4.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = true;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_24->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_25Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_25->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_6.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = true;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_25->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_26Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_26->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_7.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = true;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_26->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_27Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_27->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????3_???????_8.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = true;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_27->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_28Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_28->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_1.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = true;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_28->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_29Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_29->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_2.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = true;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_29->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_30Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_30->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_3.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = true;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_30->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_31Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_31->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_4.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = true;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_31->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_32Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_32->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_5.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	pnlTopic_36->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = true;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_32->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_33Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_33->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_5.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = true;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_33->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_34Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_34->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_7.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_35->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = true;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_34->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_35Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
	Ric_35->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_8.rtf");
	//???? ?????????? ??????
	pnlTopic_01->Color = clMenu;
	pnlTopic_02->Color = clMenu;
	pnlTopic_03->Color = clMenu;
	pnlTopic_04->Color = clMenu;
	pnlTopic_05->Color = clMenu;
	pnlTopic_06->Color = clMenu;
	pnlTopic_07->Color = clMenu;
	pnlTopic_08->Color = clMenu;
	pnlTopic_09->Color = clMenu;
	pnlTopic_10->Color = clMenu;
	pnlTopic_11->Color = clMenu;
	pnlTopic_12->Color = clMenu;
	pnlTopic_13->Color = clMenu;
	pnlTopic_14->Color = clMenu;
	pnlTopic_15->Color = clMenu;
	pnlTopic_16->Color = clMenu;
	pnlTopic_17->Color = clMenu;
	pnlTopic_18->Color = clMenu;
	pnlTopic_19->Color = clMenu;
	pnlTopic_20->Color = clMenu;
	pnlTopic_21->Color = clMenu;
	pnlTopic_22->Color = clMenu;
	pnlTopic_23->Color = clMenu;
	pnlTopic_24->Color = clMenu;
	pnlTopic_25->Color = clMenu;
	pnlTopic_26->Color = clMenu;
	pnlTopic_27->Color = clMenu;
	pnlTopic_28->Color = clMenu;
	pnlTopic_29->Color = clMenu;
	pnlTopic_30->Color = clMenu;
	pnlTopic_31->Color = clMenu;
	pnlTopic_32->Color = clMenu;
	pnlTopic_33->Color = clMenu;
	pnlTopic_34->Color = clMenu;
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = true;
	pnlTopic_Selected_36->Visible = false;
	//???? ?????? ???????
	pnlTopic_Selected_35->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pnlTopic_36Click(TObject *Sender)
{
	//???????? ?????? ??? ??????? ???????
    Ric_36->Lines->LoadFromFile(ExtractFilePath(Application->ExeName)+L"\\Library"+L"\\?????4_???????_9.rtf");
	//???? ????????? ???????
	pnlTopic_Selected_01->Visible = false;
	pnlTopic_Selected_02->Visible = false;
	pnlTopic_Selected_03->Visible = false;
	pnlTopic_Selected_04->Visible = false;
	pnlTopic_Selected_05->Visible = false;
	pnlTopic_Selected_06->Visible = false;
	pnlTopic_Selected_07->Visible = false;
	pnlTopic_Selected_08->Visible = false;
	pnlTopic_Selected_09->Visible = false;
	pnlTopic_Selected_10->Visible = false;
	pnlTopic_Selected_11->Visible = false;
	pnlTopic_Selected_12->Visible = false;
	pnlTopic_Selected_13->Visible = false;
	pnlTopic_Selected_14->Visible = false;
	pnlTopic_Selected_15->Visible = false;
	pnlTopic_Selected_16->Visible = false;
	pnlTopic_Selected_17->Visible = false;
	pnlTopic_Selected_18->Visible = false;
	pnlTopic_Selected_19->Visible = false;
	pnlTopic_Selected_20->Visible = false;
	pnlTopic_Selected_21->Visible = false;
	pnlTopic_Selected_22->Visible = false;
	pnlTopic_Selected_23->Visible = false;
	pnlTopic_Selected_24->Visible = false;
	pnlTopic_Selected_25->Visible = false;
	pnlTopic_Selected_26->Visible = false;
	pnlTopic_Selected_27->Visible = false;
	pnlTopic_Selected_28->Visible = false;
	pnlTopic_Selected_29->Visible = false;
	pnlTopic_Selected_30->Visible = false;
	pnlTopic_Selected_31->Visible = false;
	pnlTopic_Selected_32->Visible = false;
	pnlTopic_Selected_33->Visible = false;
	pnlTopic_Selected_34->Visible = false;
	pnlTopic_Selected_35->Visible = false;
	pnlTopic_Selected_36->Visible = true;
	//???? ?????? ???????
	pnlTopic_Selected_36->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_01Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\??? ????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_02Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\??? ????? ??????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_03Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\??????? ? ?????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_04Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\?????????????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_05Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\??????????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_06Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\?????? ?????????????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_07Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_1\\?????????????? ?????? ? ????? ?????? ? ???????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_11Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\??????????? ?????? ????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_12Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\???????? ??? ???????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_13Click(TObject *Sender)
{
	 //????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\?????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_14Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\??????????? ???????? ?????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_15Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\??????????????? ? ???????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Imag_16Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_2\\??????? (???????????).mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_20Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_3\\???????????? ? ???????????????? ?????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_21Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_3\\????????????????? ?????????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_22Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_3\\???? ?????? ????????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_23Click(TObject *Sender)
 {
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_3\\??????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_24Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_3\\??????????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\????????? ? ????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_29Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\????? ? ???????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_30Click(TObject *Sender)
{
	//????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\????????????? ??????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_31Click(TObject *Sender)
{
    //????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\??????? ????????????, ??????????, ????????? ?????????????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_32Click(TObject *Sender)
{
    //????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\??????? ? ????????????? ????? ?? ?????????? ? ???????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Imag_33Click(TObject *Sender)
{
    //????????? ????????? ?????
	ShellExecute(Handle,
	L"open", (ExtractFilePath(Application->ExeName) + L"Video\\Chapters\\Chapter_4\\??????? ???????? ? ????????????? ????? ?? ?????????? ? ???????.mp4").w_str(),
	NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_01MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
	SB_01->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_01MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	SB_01->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_02MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	SB_02->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_02MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
    SB_02->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_03MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_03->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_03MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_03->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_04MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_04->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_04MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_04->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_05MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_05->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_05MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
	SB_05->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_06MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	SB_06->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_06MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
    SB_06->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_07MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_07->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_07MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_07->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_08MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_08->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_08MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_08->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_09MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_09->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_09MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_09->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_10MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_10->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_10MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_10->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_11MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_11->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_11MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_11->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_12MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_12->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_12MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_12->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_13MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_13->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_13MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_13->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_14MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_14->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_14MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_14->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_15MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_15->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_15MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_15->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_16MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_16->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_16MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_16->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_17MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_17->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_17MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_17->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_18MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_18->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_18MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_18->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_19MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_19->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_19MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_19->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_20MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_20->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_20MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_20->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_21MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_21->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_21MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_21->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_22MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_22->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_22MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_22->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_23MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_23->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_23MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_23->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_24MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_24->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_24MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_24->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_25MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_25->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_25MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_25->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_26MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_26->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_26MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_26->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_27MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_27->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_27MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_27->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_28MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_28->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_28MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_28->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_29MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_29->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_29MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_29->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_30MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_30->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_30MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_30->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_31MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_31->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_31MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_31->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_32MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_32->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_32MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_32->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_33MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_33->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_33MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_33->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_34MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled)
{
    SB_34->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_34MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_34->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_35MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled)
{
    SB_35->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_35MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
    SB_35->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_36MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	SB_36->VertScrollBar->Position++;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SB_36MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled)
{
	SB_36->VertScrollBar->Position--;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTest_01Click(TObject *Sender)
{
	//???????? ????????? ????????????

	int Test_Rezult_1 = 0;
	int Test_Ball_1 = 0;
	double Test_1 = 0;

	if(rgpTopic_01->ItemIndex == 2)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_02->ItemIndex == 0)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_03->ItemIndex == 0)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_04->ItemIndex == 2)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_05->ItemIndex == 0)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_06->ItemIndex == 0)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}
	if(rgpTopic_07->ItemIndex == 0)
	{
		Test_1 = Test_1 + 3.58;
		Test_Ball_1++;
	}

	if(Test_Ball_1 >= 4)
	{
		btnTest_01->Enabled = false;
		btnTest_01->Caption = "??????? ???????, ?? ??????!";
		Test_Rezult_1 = Test_Rezult_1 + Test_1;
        Final_Ball = Final_Ball + Test_Rezult_1;
	}
	else if(Test_Ball_1 < 4)
	{
		btnTest_01->Caption = "???? ?? ?????, ?? ?? ?????? ??????????? ???!";
		Sleep(2000);
		btnTest_01->Caption = "?????????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTest_02Click(TObject *Sender)
{
	//???????? ????????? ????????????

	int Test_Rezult_2 = 0;
	int Test_Ball_2 = 0;
	double Test_2 = 0;

	if(rgpTopic_13->ItemIndex == 0)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}
	if(rgpTopic_14->ItemIndex == 1)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}
	if(rgpTopic_15->ItemIndex == 1)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}
	if(rgpTopic_16->ItemIndex == 0)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}
	if(rgpTopic_17->ItemIndex == 2)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}
	if(rgpTopic_18->ItemIndex == 1)
	{
		Test_2 = Test_2 + 4.17;
		Test_Ball_2++;
	}


	if(Test_Ball_2 >= 4)
	{
		btnTest_02->Enabled = false;
		btnTest_02->Caption = "??????? ???????, ?? ??????!";
		Test_Rezult_2 = Test_Rezult_2 + Test_2;
		Final_Ball = Final_Ball + Test_Rezult_2;
	}
	else if(Test_Ball_2 < 4)
	{
		btnTest_02->Caption = "???? ?? ?????, ?? ?? ?????? ??????????? ???!";
		Sleep(2000);
		btnTest_02->Caption = "?????????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTest_03Click(TObject *Sender)
{
	//???????? ????????? ????????????

	int Test_Rezult_3 = 0;
	int Test_Ball_3 = 0;
	double Test_3 = 0;

	if(RadioGroup1->ItemIndex == 1)
	{
		Test_3 = Test_3 + 5;
		Test_Ball_3++;
	}
	if(RadioGroup2->ItemIndex == 1)
	{
		Test_3 = Test_3 + 5;
		Test_Ball_3++;
	}
	if(RadioGroup3->ItemIndex == 1)
	{
		Test_3 = Test_3 + 5;
		Test_Ball_3++;
	}
	if(RadioGroup4->ItemIndex == 2)
	{
		Test_3 = Test_3 + 5;
		Test_Ball_3++;
	}
	if(RadioGroup5->ItemIndex == 3)
	{
		Test_3 = Test_3 + 5;
		Test_Ball_3++;
	}

	if(Test_Ball_3 >= 3)
	{
		btnTest_03->Enabled = false;
		btnTest_03->Caption = "??????? ???????, ?? ??????!";
		Test_Rezult_3 = Test_Rezult_3 + Test_3;
		Final_Ball = Final_Ball + Test_Rezult_3;
	}
	else if(Test_Ball_3 < 3)
	{
		btnTest_03->Caption = "???? ?? ?????, ?? ?? ?????? ??????????? ???!";
		Sleep(2000);
		btnTest_03->Caption = "?????????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnTest_04Click(TObject *Sender)
{
	//???????? ????????? ????????????

	int Test_Rezult_4 = 0;
	int Test_Ball_4 = 0;
	double Test_4 = 0;

	if(RadioGroup6->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}
	if(RadioGroup7->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}
	if(RadioGroup8->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}
	if(RadioGroup9->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}
	if(RadioGroup10->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}
	if(RadioGroup11->ItemIndex == 1)
	{
		Test_4 = Test_4 + 4.17;
		Test_Ball_4++;
	}


	if(Test_Ball_4 >= 4)
	{
		btnTest_04->Enabled = false;
		btnTest_04->Caption = "??????? ???????, ?? ??????!";
		Test_Rezult_4 = Test_Rezult_4 + Test_4;
		Final_Ball  = Final_Ball + Test_Rezult_4;
	}
	else if(Test_Ball_4 < 4)
	{
		btnTest_04->Caption = "???? ?? ?????, ?? ?? ?????? ??????????? ???!";
		Sleep(2000);
		btnTest_04->Caption = "?????????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtConfirmationKeyPress(TObject *Sender, System::WideChar &Key)

{
	//????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDeleteYourAccountClick(TObject *Sender)
{
	if(btnDeleteYourAccount->Caption == "??????? ??????? ??????")
	{
		pnlProfile->BringToFront();
		pnlProfile->Enabled = true;
		pnlProfile->Visible = true;

		pnlConfirmation->Enabled = true;
		pnlConfirmation->BringToFront();
		pnlConfirmation->Visible = true;
		btnDeleteYourAccount->Caption = "???????? ????????";
	}
	else if(btnDeleteYourAccount->Caption == "???????? ????????")
	{
		pnlConfirmation->Enabled = false;
		pnlConfirmation->Visible = false;
		btnDeleteYourAccount->Caption = "??????? ??????? ??????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnResetDefaultCourseClick(TObject *Sender)
{
	if(btnResetDefaultCourse->Caption == "???????? ???? ?? ?????????")
	{
        pnlProfile->BringToFront();
		pnlProfile->Enabled = true;
		pnlProfile->Visible = true;

		pnlConfirmation_2->Enabled = true;
		pnlConfirmation_2->BringToFront();
		pnlConfirmation_2->Visible = true;

		btnResetDefaultCourse->Caption = "???????? ????? ?????";

	}
	else if(btnResetDefaultCourse->Caption == "???????? ????? ?????")
	{
		pnlConfirmation_2->Enabled = false;
		pnlConfirmation_2->Visible = false;

		btnResetDefaultCourse->Caption = "????? ????? ?? ?????????";
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtConfirmationChange(TObject *Sender)
{
	if(edtConfirmation->Text != "")
	{
		Account_Deleting(Sender);
		Scanning();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtConfirmation_2KeyPress(TObject *Sender, System::WideChar &Key)

{
    //????????? ?????????? ???????
	if((Key >= 'A')&&(Key <= 'Z'))
	return;
	if((Key >= 'a')&&(Key <= 'z'))
	return;
	if((Key >= '0')&&(Key <= '9'))
	return;
	if(Key == VK_BACK)
	return;
	Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtConfirmation_2Change(TObject *Sender)
{
	if(edtConfirmation_2->Text != "")
	{
		Course_Reset(Sender);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::sb_Classes_SearchChange(TObject *Sender)
{
   //????? ???????????? ??? ??? ????????
	UnicodeString Text = sb_Classes_Search->Text;

	for(int i=1;i<=36;i++)
	{
		TComponent *?????????;
		if(i<10)?????????=FindComponent("pnlTopic_0"+IntToStr(i)); //???? ????????? ? ?????? ??? ??????
		else ?????????=FindComponent("pnlTopic_"+IntToStr(i)); //???? ????????? ? ?????? ??? ??????
		if(?????????!=NULL) //???? ????????? ? ????? ?????? ?????? ?? ?????
		{
			if(Text != "")
			{
				int ???????=AnsiPos(Text,((TPanel*)?????????)->Caption);
				if(???????>0)((TPanel*)?????????)->Visible=true;
				else ((TPanel*)?????????)->Visible=false;
			}
			else
			{
				((TPanel*)?????????)->Visible=true;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sb_Classes_SearchKeyPress(TObject *Sender, System::WideChar &Key)

{
   //????????? ??? ??????? ????? ??????????
	UnicodeString Text = "??????Ũ???????????????????????????????????????????????????????????";
	int j = 0;
	for(int i = 1; i < Text.Length(); i++)
	{
		if(AnsiUpperCase(Key) == Text[i])
		{
			j = 1;
			return;
		}
		if(Key == VK_BACK)
		{
			j = 1;
			return;
		}
		if(Key == VK_SPACE)
		{
			j = 1;
			return;
		}
	}
	if(j == 0)
	Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sb_Classes_SearchInvokeSearch(TObject *Sender)
{
	//????? ???????????? ??? ??? ????????
	UnicodeString Text = sb_Classes_Search->Text;

	for(int i=1;i<=36;i++)
	{
		TComponent *?????????;
		if(i<10)?????????=FindComponent("pnlTopic_0"+IntToStr(i)); //???? ????????? ? ?????? ??? ??????
		else ?????????=FindComponent("pnlTopic_"+IntToStr(i)); //???? ????????? ? ?????? ??? ??????
		if(?????????!=NULL) //???? ????????? ? ????? ?????? ?????? ?? ?????
		{
			if(Text != "")
			{
				int ???????=AnsiPos(Text,((TPanel*)?????????)->Caption);
				if(???????>0)((TPanel*)?????????)->Visible=true;
				else ((TPanel*)?????????)->Visible=false;
			}
			else
			{
				((TPanel*)?????????)->Visible=true;
			}
		}
	}
}
//---------------------------------------------------------------------------

