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
//const int models=1, textures=2;

int TEXDET = 64;
int DETAL = 4;
BYTE Map[1024*1024];
BYTE bits[1024*1024][4];
GLuint Texture [64];
//BYTE *HeightMapB = &Map[0];
//HeightMap = &Map[0];
//---------------------------------------------------------------------------
class TMainFrm : public TForm
{
__published:	// IDE-managed Components
        TTimer *AniTmr;
   void __fastcall FormResize(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall AppIdle (TObject *Sender, bool &Done);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall AniTmrTimer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
   __fastcall TMainFrm(TComponent* Owner);
   //void ReadFiles();

};
//---------------------------------------------------------------------------
extern PACKAGE TMainFrm *MainFrm;
//---------------------------------------------------------------------------
#endif
