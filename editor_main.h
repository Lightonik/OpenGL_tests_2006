//---------------------------------------------------------------------------

#ifndef editor_mainH
#define editor_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//#include "edit_fun.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TEditFrm : public TForm
{
__published:	// IDE-managed Components
        TFileListBox *FileBox;
        TEdit *XEdit;
        TEdit *TyEdit;
        TEdit *TxEdit;
        TEdit *NzEdit;
        TEdit *NyEdit;
        TEdit *NxEdit;
        TEdit *ZEdit;
        TEdit *YEdit;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TRadioGroup *TexRad;
        TLabel *Label3;
        TCSpinEdit *PSEdit;
        TCSpinEdit *VSEdit;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FileBoxClick(TObject *Sender);
        void __fastcall PSEditChange(TObject *Sender);
        void __fastcall VSEditChange(TObject *Sender);
        void __fastcall TexRadClick(TObject *Sender);
        void __fastcall XEditChange(TObject *Sender);
        void __fastcall YEditChange(TObject *Sender);
        void __fastcall ZEditChange(TObject *Sender);
        void __fastcall NxEditChange(TObject *Sender);
        void __fastcall NyEditChange(TObject *Sender);
        void __fastcall NzEditChange(TObject *Sender);
        void __fastcall TxEditChange(TObject *Sender);
        void __fastcall TyEditChange(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void __fastcall BuildVer();
        int poly, ver[30];
        bool tex[30];
        struct {float x,y,z,nx,ny,nz,tx,ty;} vertex[90];
        //float xyz[90][8];
        __fastcall TEditFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditFrm *EditFrm;
//---------------------------------------------------------------------------
#endif
