//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.CategoryButtons.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.Notification.hpp>
#include <Vcl.MPlayer.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
#include <Vcl.Samples.Gauges.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlCenterControl;
	TActionList *ActionList1;
	TAction *actHome;
	TAction *actProfile;
	TAction *actTraining;
	TAction *actStatistics;
	TAction *actSettings;
	TAction *actHelp;
	TAction *actAbout;
	TAction *actExit;
	TImageList *imlIcons;
	TAction *actMenu;
	TSplitView *SV;
	TCategoryButtons *catMenuItems;
	TSplitView *SV_Settings;
	TPanel *pnlTopControl;
	TImage *imgTopControlSystemMenu;
	TLabel *lbTopControlText;
	TPopupMenu *pmTopControlSystemMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TPanel *pnlHome;
	TPanel *pnlProfile;
	TPanel *pnlTraining;
	TPanel *pnlStatistics;
	TPanel *pnlHelp;
	TPanel *pnlAbout;
	TPanel *pnlTop_SV_Settings;
	TScrollBox *SB_SV_Settings;
	TPanel *pnlSV_SV_Settings;
	TImage *imgProfile_Settings;
	TLabel *lbSV_Settings_Account;
	TLabel *lbSV_Settings_Account_Name;
	TButton *btnSV_Settings_Password_Reset;
	TButton *btnSV_Setting_Profile_Exit;
	TActivityIndicator *ActiveInd_SV_Settings_Profile_Status;
	TImage *imgProfile_Fon;
	TLabel *lbSV_Settings_Text_01;
	TLabel *lbSV_Settings_Text_02;
	TToggleSwitch *tsSV_Settings_Status_01;
	TLabel *lbSV_Settings_Status_01;
	TLabel *lbSV_Settings_Text_03;
	TLabel *lbSV_Settings_Text_04;
	TLabel *lbSV_Settings_Status_02;
	TToggleSwitch *tsSV_Settings_Status_02;
	TImage *imgProfile_Icon;
	TPanel *pnlClasses;
	TPanel *pnlClasses_Search;
	TLabel *lbClasses_Name;
	TSearchBox *sb_Classes_Search;
	TPanel *pnlClasses_Left;
	TScrollBox *scrClasses;
	TPanel *pnlClasses_List;
	TPanel *pnlTopic_01;
	TLabel *lbSV_Settings_Text_05;
	TLabel *lbSV_Settings_Text_06;
	TLabel *lbSV_Settings_Status_03;
	TToggleSwitch *tsSV_Settings_Status_03;
	TLabel *lbSV_Settings_Text_07;
	TLabel *lbSV_Settings_Status_04;
	TToggleSwitch *tsSV_Settings_Status_04;
	TPanel *pnlTopic_02;
	TPanel *pnlTopic_03;
	TPanel *pnlTopic_04;
	TPanel *pnlTopic_05;
	TPanel *pnlTopic_06;
	TPanel *pnlTopic_07;
	TPanel *pnlTopic_08;
	TPanel *pnlTopic_09;
	TPanel *pnlTopic_10;
	TPanel *pnlTopic_11;
	TPanel *pnlTopic_12;
	TPanel *pnlTopic_13;
	TPanel *pnlTopic_14;
	TPanel *pnlTopic_15;
	TPanel *pnlTopic_16;
	TPanel *pnlTopic_17;
	TPanel *pnlTopic_18;
	TPanel *pnlTopic_19;
	TPanel *pnlTraning_Topic_Selected;
	TLabel *lbTraning_Name_Topic_Text;
	TLabel *Label1;
	TLabel *Label2;
	TListBox *lbList_Login;
	TPanel *pnlValidation;
	TLabel *Label3;
	TEdit *edValidation_Login_01;
	TEdit *edValidation_Password_01;
	TButton *btnValidation_Entrance_01;
	TActivityIndicator *actiValidation_01;
	TLabel *lbRegistration;
	TPanel *pnlReset_Password;
	TLabel *lbReset_Password;
	TEdit *edReset_Password;
	TEdit *edNew_Password_01;
	TButton *btnReset;
	TActivityIndicator *ActivityIndicator1;
	TEdit *edNew_Password_02;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TPanel *pnlTopic_20;
	TPanel *pnlTopic_21;
	TPanel *pnlTopic_22;
	TPanel *pnlTopic_23;
	TPanel *pnlTopic_24;
	TPanel *pnlTopic_25;
	TPanel *pnlTopic_26;
	TPanel *pnlTopic_27;
	TPanel *pnlTopic_28;
	TPanel *pnlTopic_29;
	TPanel *pnlTopic_30;
	TPanel *pnlTopic_31;
	TPanel *pnlTopic_32;
	TPanel *pnlTopic_33;
	TPanel *pnlTopic_34;
	TPanel *pnlTopic_35;
	TPanel *pnlTopic_36;
	TPanel *pnlTopic_Selected_01;
	TPanel *pnlTopic_Selected_02;
	TPanel *pnlTopic_Selected_04;
	TPanel *pnlTopic_Selected_03;
	TPanel *pnlTopic_Selected_08;
	TPanel *pnlTopic_Selected_07;
	TPanel *pnlTopic_Selected_06;
	TPanel *pnlTopic_Selected_05;
	TPanel *pnlTopic_Selected_13;
	TPanel *pnlTopic_Selected_14;
	TPanel *pnlTopic_Selected_15;
	TPanel *pnlTopic_Selected_16;
	TPanel *pnlTopic_Selected_09;
	TPanel *pnlTopic_Selected_10;
	TPanel *pnlTopic_Selected_11;
	TPanel *pnlTopic_Selected_12;
	TPanel *pnlTopic_Selected_30;
	TPanel *pnlTopic_Selected_28;
	TPanel *pnlTopic_Selected_27;
	TPanel *pnlTopic_Selected_26;
	TPanel *pnlTopic_Selected_25;
	TPanel *pnlTopic_Selected_32;
	TPanel *pnlTopic_Selected_31;
	TPanel *pnlTopic_Selected_29;
	TPanel *pnlTopic_Selected_21;
	TPanel *pnlTopic_Selected_22;
	TPanel *pnlTopic_Selected_23;
	TPanel *pnlTopic_Selected_24;
	TPanel *pnlTopic_Selected_20;
	TPanel *pnlTopic_Selected_19;
	TPanel *pnlTopic_Selected_18;
	TPanel *pnlTopic_Selected_17;
	TPanel *pnlTopic_Selected_36;
	TPanel *pnlTopic_Selected_33;
	TPanel *pnlTopic_Selected_35;
	TPanel *pnlTopic_Selected_34;
	TScrollBox *SB_01;
	TPanel *Pan_01;
	TImage *Imag_01;
	TPanel *P_01;
	TRichEdit *Ric_01;
	TPanel *P_02;
	TScrollBox *SB_02;
	TPanel *Pan_02;
	TImage *Imag_02;
	TPanel *P_03;
	TRichEdit *Ric_02;
	TPanel *P_04;
	TScrollBox *SB_03;
	TPanel *Pan_03;
	TImage *Imag_03;
	TPanel *P_05;
	TRichEdit *Ric_03;
	TPanel *P_06;
	TScrollBox *SB_04;
	TPanel *Pan_04;
	TImage *Imag_04;
	TPanel *P_07;
	TRichEdit *Ric_04;
	TPanel *P_08;
	TScrollBox *SB_05;
	TPanel *Pan_05;
	TImage *Imag_05;
	TPanel *P_09;
	TRichEdit *Ric_05;
	TPanel *P_10;
	TScrollBox *SB_06;
	TPanel *Pan_06;
	TImage *Imag_06;
	TPanel *P_11;
	TRichEdit *Ric_06;
	TPanel *P_12;
	TScrollBox *SB_07;
	TPanel *Pan_07;
	TImage *Imag_07;
	TPanel *P_13;
	TRichEdit *Ric_07;
	TPanel *P_14;
	TScrollBox *SB_08;
	TPanel *Pan_08;
	TImage *Imag_08;
	TPanel *P_15;
	TRichEdit *Ric_08;
	TScrollBox *SB_09;
	TPanel *Pan_09;
	TImage *Imag_09;
	TPanel *P_16;
	TRichEdit *Ric_09;
	TScrollBox *SB_10;
	TPanel *Pan_10;
	TImage *Imag_10;
	TPanel *P_17;
	TRichEdit *Ric_10;
	TPanel *P_18;
	TScrollBox *SB_11;
	TPanel *Pan_11;
	TImage *Imag_11;
	TPanel *P_19;
	TRichEdit *Ric_11;
	TPanel *P_20;
	TScrollBox *SB_12;
	TPanel *Pan_12;
	TImage *Imag_12;
	TPanel *P_21;
	TRichEdit *Ric_12;
	TPanel *P_22;
	TScrollBox *SB_13;
	TPanel *Pan_13;
	TImage *Imag_13;
	TPanel *P_23;
	TRichEdit *Ric_13;
	TPanel *P_24;
	TScrollBox *SB_14;
	TPanel *Pan_14;
	TImage *Imag_14;
	TPanel *P_25;
	TRichEdit *Ric_14;
	TPanel *P_26;
	TScrollBox *SB_15;
	TPanel *Pan_15;
	TImage *Imag_15;
	TPanel *P_27;
	TRichEdit *Ric_15;
	TPanel *P_28;
	TScrollBox *SB_16;
	TPanel *Pan_16;
	TImage *Imag_16;
	TPanel *P_29;
	TRichEdit *Ric_16;
	TPanel *P_30;
	TScrollBox *SB_17;
	TPanel *Pan_17;
	TImage *Imag_17;
	TPanel *P_31;
	TRichEdit *Ric_17;
	TScrollBox *SB_18;
	TPanel *Pan_18;
	TImage *Imag_18;
	TPanel *P_32;
	TRichEdit *Ric_18;
	TScrollBox *SB_19;
	TPanel *Pan_19;
	TImage *Imag_19;
	TPanel *P_33;
	TRichEdit *Ric_19;
	TPanel *P_65;
	TScrollBox *SB_20;
	TPanel *Pan_20;
	TImage *Imag_20;
	TPanel *P_34;
	TRichEdit *Ric_20;
	TPanel *P_35;
	TScrollBox *SB_21;
	TPanel *Pan_21;
	TImage *Imag_21;
	TPanel *P_36;
	TRichEdit *Ric_21;
	TPanel *P_37;
	TScrollBox *SB_22;
	TPanel *Pan_22;
	TImage *Imag_22;
	TPanel *P_38;
	TRichEdit *Ric_22;
	TPanel *P_39;
	TScrollBox *SB_23;
	TPanel *Pan_23;
	TImage *Imag_23;
	TPanel *P_40;
	TRichEdit *Ric_23;
	TPanel *P_41;
	TScrollBox *SB_24;
	TPanel *Pan_24;
	TImage *Imag_24;
	TPanel *P_42;
	TRichEdit *Ric_24;
	TPanel *P_43;
	TScrollBox *SB_25;
	TPanel *Pan_25;
	TImage *Imag_25;
	TPanel *P_44;
	TRichEdit *Ric_25;
	TScrollBox *SB_26;
	TPanel *Pan_26;
	TImage *Imag_26;
	TPanel *P_45;
	TRichEdit *Ric_26;
	TScrollBox *SB_27;
	TPanel *Pan_27;
	TImage *Imag_27;
	TPanel *P_46;
	TRichEdit *Ric_27;
	TPanel *P_47;
	TScrollBox *SB_28;
	TPanel *Pan_28;
	TImage *Image4;
	TPanel *P_48;
	TRichEdit *Ric_28;
	TPanel *P_49;
	TImage *Im_01;
	TImage *Img_Statistics;
	TImage *Im_02;
	TScrollBox *SB_29;
	TPanel *Pan_29;
	TImage *Imag_29;
	TPanel *P_50;
	TRichEdit *Ric_29;
	TPanel *P_51;
	TScrollBox *SB_30;
	TPanel *Pan_30;
	TImage *Imag_30;
	TPanel *P_52;
	TRichEdit *Ric_30;
	TPanel *P_53;
	TScrollBox *SB_31;
	TPanel *Pan_31;
	TImage *Imag_31;
	TPanel *P_54;
	TRichEdit *Ric_31;
	TScrollBox *SB_32;
	TScrollBox *SB_33;
	TScrollBox *SB_34;
	TScrollBox *SB_35;
	TScrollBox *SB_36;
	TPanel *Pan_32;
	TPanel *Pan_33;
	TPanel *Pan_34;
	TPanel *Pan_35;
	TPanel *Pan_36;
	TImage *Imag_32;
	TPanel *P_56;
	TRichEdit *Ric_32;
	TPanel *P_57;
	TImage *Imag_33;
	TPanel *P_58;
	TRichEdit *Ric_33;
	TPanel *P_59;
	TImage *Imag_34;
	TPanel *P_60;
	TRichEdit *Ric_34;
	TImage *Imag_35;
	TPanel *P_61;
	TRichEdit *Ric_35;
	TImage *Imag_36;
	TPanel *P_62;
	TRichEdit *Ric_36;
	TPanel *P_63;
	TImage *Im_03;
	TImage *Im_04;
	TImage *Im_05;
	TImage *Im_06;
	TImage *Im_07;
	TPanel *P_Test_01;
	TImage *Im_10;
	TImage *Im_11;
	TImage *Im_12;
	TImage *Im_13;
	TImage *Im_14;
	TImage *Im_15;
	TImage *Im_16;
	TPanel *P_Test_02;
	TImage *Im_19;
	TImage *Im_20;
	TImage *Im_21;
	TImage *Im_22;
	TImage *Im_23;
	TImage *Im_24;
	TPanel *P_Test_03;
	TImage *Im_27;
	TImage *Im_28;
	TImage *Im_29;
	TImage *Im_30;
	TImage *Im_32;
	TImage *Im_33;
	TPanel *P_Test_04;
	TImage *Im_36;
	TRadioGroup *rgpTopic_01;
	TRadioGroup *rgpTopic_02;
	TRadioGroup *rgpTopic_03;
	TRadioGroup *rgpTopic_04;
	TLabel *LblTopic_09;
	TLabel *LblTopic_12;
	TLabel *LblTopic_11;
	TRadioGroup *rgpTopic_06;
	TRadioGroup *rgpTopic_07;
	TButton *btnTest_01;
	TLabel *LblTopic_05;
	TLabel *LblTopic_06;
	TLabel *LblTopic_08;
	TLabel *LblTopic_07;
	TRadioGroup *rgpTopic_05;
	TRadioGroup *rgpTopic_18;
	TRadioGroup *rgpTopic_17;
	TRadioGroup *rgpTopic_16;
	TRadioGroup *rgpTopic_15;
	TRadioGroup *rgpTopic_14;
	TRadioGroup *rgpTopic_13;
	TButton *btnTest_02;
	TRadioGroup *RadioGroup1;
	TRadioGroup *RadioGroup2;
	TRadioGroup *RadioGroup3;
	TRadioGroup *RadioGroup4;
	TRadioGroup *RadioGroup5;
	TButton *btnTest_03;
	TRadioGroup *RadioGroup6;
	TRadioGroup *RadioGroup7;
	TRadioGroup *RadioGroup8;
	TRadioGroup *RadioGroup9;
	TLabel *Label4;
	TRadioGroup *RadioGroup10;
	TLabel *Label5;
	TRadioGroup *RadioGroup11;
	TButton *btnTest_04;
	TButton *btnDeleteYourAccount;
	TButton *btnResetDefaultCourse;
	TPanel *pnlConfirmation;
	TEdit *edtConfirmation;
	TActivityIndicator *ActivityIndicator2;
	TPanel *pnlConfirmation_2;
	TEdit *edtConfirmation_2;
	TActivityIndicator *ActivityIndicator3;
	TLabel *Label6;
	TGauge *gueProgressProgress_01;
	TPanel *pnlEvaluation;
	TPanel *pnlValue_1;
	TPanel *pnlValue_2;
	TPanel *pnlValue_3;
	TPanel *pnlValue_4;
	TPanel *pnlValue_5;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actMenuExecute(TObject *Sender);
	void __fastcall actExitExecute(TObject *Sender);
	void __fastcall actSettingsExecute(TObject *Sender);
	void __fastcall imgTopControlSystemMenuClick(TObject *Sender);
	void __fastcall actHomeExecute(TObject *Sender);
	void __fastcall actProfileExecute(TObject *Sender);
	void __fastcall actTrainingExecute(TObject *Sender);
	void __fastcall actStatisticsExecute(TObject *Sender);
	void __fastcall actHelpExecute(TObject *Sender);
	void __fastcall actAboutExecute(TObject *Sender);
	void __fastcall pnlTopControlMouseEnter(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall pnlHomeClick(TObject *Sender);
	void __fastcall pnlProfileClick(TObject *Sender);
	void __fastcall pnlTrainingClick(TObject *Sender);
	void __fastcall pnlStatisticsClick(TObject *Sender);
	void __fastcall pnlHelpClick(TObject *Sender);
	void __fastcall pnlAboutClick(TObject *Sender);
	void __fastcall SVClick(TObject *Sender);
	void __fastcall catMenuItemsClick(TObject *Sender);
	void __fastcall tsSV_Settings_Status_03Click(TObject *Sender);
	void __fastcall edValidation_Login_01KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edValidation_Password_01KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btnValidation_Entrance_01Click(TObject *Sender);
	void __fastcall lbRegistrationMouseLeave(TObject *Sender);
	void __fastcall lbRegistrationClick(TObject *Sender);
	void __fastcall lbRegistrationMouseEnter(TObject *Sender);
	void __fastcall btnSV_Setting_Profile_ExitClick(TObject *Sender);
	void __fastcall btnSV_Settings_Password_ResetClick(TObject *Sender);
	void __fastcall edReset_PasswordKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edNew_Password_01KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edNew_Password_02KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btnResetClick(TObject *Sender);
	void __fastcall pnlTopic_01MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_01MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_02MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_02MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_03MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_03MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_04MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_04MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_05MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_05MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_06MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_06MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_07MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_07MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_08MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_08MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_09MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_09MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_10MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_10MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_11MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_11MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_12MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_12MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_13MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_13MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_14MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_14MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_15MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_15MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_16MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_16MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_17MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_17MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_18MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_18MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_19MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_19MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_20MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_20MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_21MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_21MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_22MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_22MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_23MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_23MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_24MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_24MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_25MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_25MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_26MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_26MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_27MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_27MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_28MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_28MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_29MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_29MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_30MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_30MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_31MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_31MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_32MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_32MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_33MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_33MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_34MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_34MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_35MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_35MouseLeave(TObject *Sender);
	void __fastcall pnlTopic_36MouseEnter(TObject *Sender);
	void __fastcall pnlTopic_36MouseLeave(TObject *Sender);
	void __fastcall scrClassesMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall pnlTopic_01Click(TObject *Sender);
	void __fastcall scrClassesMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall pnlTopic_02Click(TObject *Sender);
	void __fastcall pnlTopic_03Click(TObject *Sender);
	void __fastcall pnlTopic_04Click(TObject *Sender);
	void __fastcall pnlTopic_05Click(TObject *Sender);
	void __fastcall pnlTopic_06Click(TObject *Sender);
	void __fastcall pnlTopic_07Click(TObject *Sender);
	void __fastcall pnlTopic_08Click(TObject *Sender);
	void __fastcall pnlTopic_09Click(TObject *Sender);
	void __fastcall pnlTopic_10Click(TObject *Sender);
	void __fastcall pnlTopic_11Click(TObject *Sender);
	void __fastcall pnlTopic_12Click(TObject *Sender);
	void __fastcall pnlTopic_13Click(TObject *Sender);
	void __fastcall pnlTopic_14Click(TObject *Sender);
	void __fastcall pnlTopic_15Click(TObject *Sender);
	void __fastcall pnlTopic_16Click(TObject *Sender);
	void __fastcall pnlTopic_17Click(TObject *Sender);
	void __fastcall pnlTopic_18Click(TObject *Sender);
	void __fastcall pnlTopic_19Click(TObject *Sender);
	void __fastcall pnlTopic_20Click(TObject *Sender);
	void __fastcall pnlTopic_21Click(TObject *Sender);
	void __fastcall pnlTopic_22Click(TObject *Sender);
	void __fastcall pnlTopic_23Click(TObject *Sender);
	void __fastcall pnlTopic_24Click(TObject *Sender);
	void __fastcall pnlTopic_25Click(TObject *Sender);
	void __fastcall pnlTopic_26Click(TObject *Sender);
	void __fastcall pnlTopic_27Click(TObject *Sender);
	void __fastcall pnlTopic_28Click(TObject *Sender);
	void __fastcall pnlTopic_29Click(TObject *Sender);
	void __fastcall pnlTopic_30Click(TObject *Sender);
	void __fastcall pnlTopic_31Click(TObject *Sender);
	void __fastcall pnlTopic_32Click(TObject *Sender);
	void __fastcall pnlTopic_33Click(TObject *Sender);
	void __fastcall pnlTopic_34Click(TObject *Sender);
	void __fastcall pnlTopic_35Click(TObject *Sender);
	void __fastcall pnlTopic_36Click(TObject *Sender);
	void __fastcall Imag_01Click(TObject *Sender);
	void __fastcall Imag_02Click(TObject *Sender);
	void __fastcall Imag_03Click(TObject *Sender);
	void __fastcall Imag_04Click(TObject *Sender);
	void __fastcall Imag_05Click(TObject *Sender);
	void __fastcall Imag_06Click(TObject *Sender);
	void __fastcall Imag_07Click(TObject *Sender);
	void __fastcall Imag_11Click(TObject *Sender);
	void __fastcall Imag_12Click(TObject *Sender);
	void __fastcall Imag_13Click(TObject *Sender);
	void __fastcall Imag_14Click(TObject *Sender);
	void __fastcall Imag_15Click(TObject *Sender);
	void __fastcall Imag_16Click(TObject *Sender);
	void __fastcall Imag_20Click(TObject *Sender);
	void __fastcall Imag_21Click(TObject *Sender);
	void __fastcall Imag_22Click(TObject *Sender);
	void __fastcall Imag_23Click(TObject *Sender);
	void __fastcall Imag_24Click(TObject *Sender);
	//???????? ?????? ?? ???????????
	void __fastcall Login_Verification(TObject *Sender);
    //?????????? ???????????? ? ini - ????
	void __fastcall WriteParams( TObject *Sender );
    //???????? ???????????? ?? ini - ?????
	void __fastcall ReadParams( TObject *Sender );
    //???????? ??????? ????? ? ???????
	void __fastcall Login_Status( TObject *Sender );
    //???????? ?????? ????????????
	void __fastcall Validation( TObject *Sender );
	//?????? ??????
	void __fastcall Change_Password( TObject *Sender );
	//??????? ??????? ??????
	void __fastcall Account_Deleting(TObject *Sender);
	//?????????? ???? ?? ?????????
    void __fastcall Course_Reset(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Imag_29Click(TObject *Sender);
	void __fastcall Imag_30Click(TObject *Sender);
	void __fastcall Imag_31Click(TObject *Sender);
	void __fastcall Imag_32Click(TObject *Sender);
	void __fastcall Imag_33Click(TObject *Sender);
	void __fastcall SB_01MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_01MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_02MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_02MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_03MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_03MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_04MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_04MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_05MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_05MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_06MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_06MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_07MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_07MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_08MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_08MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_09MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_09MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_10MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_10MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_11MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_11MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_12MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_12MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_13MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_13MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_14MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_14MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_15MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_15MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_16MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_16MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_17MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_17MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_18MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_18MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_19MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_19MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_20MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_20MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_21MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_21MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_22MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_22MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_23MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_23MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_24MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_24MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_25MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_25MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_26MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_26MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_27MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_27MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_28MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_28MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_29MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_29MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_30MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_30MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_31MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_31MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_32MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_32MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_33MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_33MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_34MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled);
	void __fastcall SB_34MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_35MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_35MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_36MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SB_36MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall btnTest_01Click(TObject *Sender);
	void __fastcall btnTest_02Click(TObject *Sender);
	void __fastcall btnTest_03Click(TObject *Sender);
	void __fastcall btnTest_04Click(TObject *Sender);
	void __fastcall edtConfirmationKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btnDeleteYourAccountClick(TObject *Sender);
	void __fastcall btnResetDefaultCourseClick(TObject *Sender);
	void __fastcall edtConfirmationChange(TObject *Sender);
	void __fastcall edtConfirmation_2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edtConfirmation_2Change(TObject *Sender);
	void __fastcall sb_Classes_SearchChange(TObject *Sender);
	void __fastcall sb_Classes_SearchKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall sb_Classes_SearchInvokeSearch(TObject *Sender);





private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
