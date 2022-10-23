//===========================================================================
#include <vcl.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#pragma hdrstop

#include "main.h"
#include "log.h"
#include "vector.h"
#include "texture.h"
#include "models.h"
#include "comons.h"
#include "particles.h"
#include "terrain.h"
#include "font.h"
//#include "loader.h"
#include "camera.h"
#include "objects.h"
#include "loading.h"
#include "interface.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainFrm *MainFrm;

//===========================================================================
        float d=0.5;
        int ani=0;                                                              // счетчик кадров анимации
        bool run=false;                                                         // индикатор бега
        int fps=0,counter=0;                                                    // считает fps
        bool ModelView=true;
        bool KeyW=false,KeyA=false,KeyS=false,KeyD=false;
        CCamera Camera;
        void MoveM();
        float CamX=512,CamY=512;
//===========================================================================
        PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	 = NULL;
        PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		 = NULL;
//===========================================================================
__fastcall TMainFrm::TMainFrm(TComponent* Owner)
        : TForm(Owner)
{
        ::SetCursorPos (Screen->Width/2, Screen->Height/2);
        InitGL(Handle,0,0,Width,Height);
        Application->OnIdle = AppIdle;
        MainFrm->ClientWidth=1024;
        MainFrm->ClientHeight=768;
        randomize();
        glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)        wglGetProcAddress("glActiveTextureARB");
        glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)    wglGetProcAddress("glMultiTexCoord2fARB");
        StartLog();
        StartLoad();
        CreatePanel();
//        ReadFiles();
}
//===========================================================================
void __fastcall TMainFrm::FormResize(TObject *Sender)
{
        RezGL(0,0,Width,Height);
}
//===========================================================================
void __fastcall TMainFrm::FormDestroy(TObject *Sender)
{
        if (hGLRC) {
                wglMakeCurrent(NULL, NULL);
                wglDeleteContext(hGLRC);
                hGLRC = NULL;
        }
        if (hDC) {
                ReleaseDC(Handle, hDC);
                hDC = NULL;
        }
}
//===========================================================================
void __fastcall TMainFrm::AppIdle(TObject *Sender, bool &Done)
{

        Done = true;
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity ();
        Camera.Set();
/*                lposition[0] = 0;
                lposition[1] = 10;
                lposition[2] = 10;
                ldirection[0] = 0;
                ldirection[1] = 0;
                ldirection[2] = 0;      */
        glLightfv (GL_LIGHT0, GL_POSITION, lposition);
        glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, ldirection);



}
//===========================================================================
void __fastcall TMainFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift) {
        if (Key == VK_ESCAPE)
                Application->Terminate ();
        else
                if (Key == VK_UP)
                        Camera.ChangeAng(2);
        else
                if (Key == VK_DOWN)
                        Camera.ChangeAng(-2);

        else
                if (Key == 'A')
                        KeyA=true;
        else
                if (Key == 'D')
                        KeyD=true;
        else
                if (Key == 'W')
                        KeyW=true;
        else
                if (Key == 'S')
                        KeyS=true;
/*        else
               if (Key == 'R') {
                        if(!run) {
                                Characters[0].RunTo(7,-10);
//                                Characters[0].Command(2);
//                                Characters[0].Rx=-5;
//                                Characters[0].Ry=7;
//                                Characters[1].Command(2);
                        }
                        else {
                                Characters[0].Command(0);
//                                Characters[1].Command(0);
                        }
                        run=!run;
                }     */
        else
                if (Key == ' ') {
                        if(Cursor==crNone)
                                Cursor=crDefault;
                        else
                                Cursor=crNone;
                }
/*        else
                if (Key == 'N') {
                        ani++;
                        if(ani>34)
                                ani=0;
                }
        else
                if (Key == 'M') {
                        ani--;
                        if(ani<0)
                                ani=34;
                }
        else
                if (Key == 'O')
                        WeaponAni();  */

}
//===========================================================================
void __fastcall TMainFrm::AniTmrTimer(TObject *Sender)
{
//        MoveM();
        Camera.Currect();
}
//===========================================================================
void MoveM() {
        float dx=0,dy=0,sq=sqrt(2);
        if(KeyA && KeyW) {
                dy=1/sq;
                dx=-1/sq;
        }
        else if(KeyD && KeyW) {
                dy=-1/sq;
                dx=-1/sq;
        }
        else if(KeyA && KeyS) {
                dy=1/sq;
                dx=1/sq;
        }
        else if(KeyD && KeyS) {
                dy=-1/sq;
                dx=1/sq;
        }
        else if(KeyA)
                dy=1;
        else if(KeyD)
                dy=-1;
        else if(KeyW)
                dx=-1;
        else if(KeyS)
                dx=1;
        Camera.MoveLook(dx,-dy);
}
//===========================================================================
void __fastcall TMainFrm::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if      (Key == 'A')
                KeyA=false;
        else if (Key == 'D')
                KeyD=false;
        else if (Key == 'W')
                KeyW=false;
        else if (Key == 'S')
                KeyS=false;

}
//===========================================================================
void __fastcall TMainFrm::FormCreate(TObject *Sender)
{
//        Cursor=crNone;
}
//===========================================================================
void __fastcall TMainFrm::FrameCounterTimer(TObject *Sender)
{
        fps=counter;
        counter=0;
}
//===========================================================================

void __fastcall TMainFrm::RenderTmrTimer(TObject *Sender)
{
//===== Рисование сцены =====================================================
        counter++;                                              // нарисовали кадр, счетчик ++

//        Characters[1].Render(-1);
/*        if(run) {
                Characters[0].Turn();
                Characters[0].Run();
                }   */
        ani=Characters[0].Render(-1);
        Terrains[0].Render();

                                
//===== Интерфейс и т.п. ====================================================
        LinesPanel[0].Draw();

//        Font1.InterPri(0,1,RGBA,"FPS - %d",fps);
//        Font1.InterPri(0,1,RGBA_1,"[%2.2f] [%2.2f]",Characters[0].ang,Characters[0].Rang);
        Font1.InterPri(0,1,RGBA_1,"[%2.2f] [%2.2f]",Characters[0].x,Characters[0].y);
        Font1.InterPri(0,2,RGBA_1,"[%d]",Characters[0].runtime);
//        Font1.InterPri(0,4,RGBA,"Время бега %d кадр(ов)",Characters[0].runtime);
//        Font1.InterPri(0,5,RGBA,"№ кадра - %d",ani);
//===== Рисование законченно ================================================
        glFlush ();
        SwapBuffers(hDC);

}
//===========================================================================

void __fastcall TMainFrm::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled) {
        Camera.Distans(-1);
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled) {
        Camera.Distans(1);
}
//---------------------------------------------------------------------------


void __fastcall TMainFrm::FormMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y){
        if(Button==mbLeft) LeftClick(X,Y);
}
//---------------------------------------------------------------------------

