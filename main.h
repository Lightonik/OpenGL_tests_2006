//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <windows.h>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glaux.h>
#include <math.h>

//---------------------------------------------------------------------------

#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1

#define GL_COMBINE_ARB						0x8570
#define GL_RGB_SCALE_ARB					0x8573

typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);

extern PFNGLMULTITEXCOORD2FARBPROC			glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB;

//---------------------------------------------------------------------------
//        BYTE Map[1024*1024];
//---------------------------------------------------------------------------
class TMainFrm : public TForm
{
__published:	// IDE-managed Components
        TTimer *AniTmr;
        TTimer *FrameCounter;
        TTimer *RenderTmr;
   void __fastcall FormResize(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall AppIdle (TObject *Sender, bool &Done);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall AniTmrTimer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FrameCounterTimer(TObject *Sender);
        void __fastcall RenderTmrTimer(TObject *Sender);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
   __fastcall TMainFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainFrm *MainFrm;
//---------------------------------------------------------------------------
#endif
