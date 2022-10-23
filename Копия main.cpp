//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <stdio.h>
#pragma hdrstop

#include "main.h"
#include "comons.h"
#include "loader.h"
//#include "models.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainFrm *MainFrm;
//int ang=0;
float d=1;
int ani=1;
bool ModelView=false;
float X, Y, Z, Yaw, Pitch, Dist, DistXY;
float MapX=-512,MapY=-512,MapZ=-10;
bool KeyW=false,KeyA=false,KeyS=false,KeyD=false;

void MoveM();


   PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	 = NULL;
   PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		 = NULL;
//GLfloat lposition[] = {10, -10, 10, 1}, ldirection[] = {0, 0, 0};
//---------------------------------------------------------------------------
//HGLRC hGLRC;
//HDC   hDC;
__fastcall TMainFrm::TMainFrm(TComponent* Owner)
   : TForm(Owner)
{
   ::SetCursorPos (Screen->Width/2, Screen->Height/2);
   InitGL(Handle,0,0,Width,Height);
   Application->OnIdle = AppIdle;

  // ChangeToFullScreen();
   MainFrm->ClientWidth=1024;
   MainFrm->ClientHeight=768;

   X = 0; Y = 0; Z=0;
   Dist=10;
   Yaw = 0; Pitch = 10;

   glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
   glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");

   ReadFiles();



}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::FormResize(TObject *Sender)
{
RezGL(0,0,Width,Height);
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::FormDestroy(TObject *Sender)
{
   if (hGLRC)
   {
      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(hGLRC);
      hGLRC = NULL;
   }
   if (hDC)
   {
      ReleaseDC(Handle, hDC);
      hDC = NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::AppIdle(TObject *Sender, bool &Done)
{
   Done = true;



   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glLoadIdentity ();
   gluLookAt (X, Y, Z, 0, 0, 0, X, Y, Z+1);

   //glRotatef (Pitch, 1, 0, 0);
   //glRotatef (Yaw, 0, 0, 1);
   //glTranslatef (-X, -Y, -Z);


   lposition[0] = 0;
   lposition[1] = 10;
   lposition[2] = 10;
   ldirection[0] = 0;
   ldirection[1] = 0;
   ldirection[2] = 0;
   glLightfv (GL_LIGHT0, GL_POSITION, lposition);
   glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, ldirection);

   MoveM();


// ÐÈÑÎÂÀÍÈÅ ================================================================

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, Texture[2]);
   glCallList(1);
   glDisable(GL_TEXTURE_2D);


  //glTranslatef (MapX,MapY,MapZ);
//  DrawLand(1);
 

//===========================================================================

   glFlush ();
   SwapBuffers(hDC);
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

   if (Key == VK_ESCAPE) Application->Terminate ();
/*   else if (Key == VK_LEFT) Yaw -= 3;
   else if (Key == VK_RIGHT) Yaw += 3;
   else if (Key == VK_UP) Pitch+=3;
   else if (Key == VK_DOWN) Pitch-=3;    */

   else if (Key == 'A') KeyA=true;
   else if (Key == 'D') KeyD=true;
   else if (Key == 'W') KeyW=true;
   else if (Key == 'S') KeyS=true;
   else if (Key == 'V') ModelView=!ModelView;
   else if (Key == ' ') {if(Cursor==crNone)Cursor=crDefault;
                         else Cursor=crNone;}

/*   else if (Key == 'A') X -= 0.05;
   else if (Key == 'D') X += 0.05;
   else if (Key == 'W') Y += 0.05;
   else if (Key == 'S') Y -= 0.05;
   else if (Key == 'C') Z-=0.05;
   else if (Key == ' ') Z+=0.05;*/
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
Dist -= 5;
if(Dist<10)Dist=10;
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
Dist += 5;
if(Dist>200)Dist=200;
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::AniTmrTimer(TObject *Sender)
{
   TPoint* temp;
   temp = new TPoint;
   ::GetCursorPos (temp);
      if(Pitch>90)Pitch=90;
      if(Pitch<-90)Pitch=-90;

if(!ModelView){
   int delt=Screen->Width/2;
   float Zreal=HeightM(-MapX+X,-MapY+Y)+MapZ+4;
   while(temp->x > delt+50){
    Yaw++;
    delt+=50;
    ::SetCursorPos (temp->x-1, temp->y);
   }
   while(temp->x < delt-50){
    Yaw--;
    delt-=50;
    ::SetCursorPos (temp->x+1, temp->y);
   }

//   Yaw += (180 * (temp->x - Screen->Width/2) / Screen->Width);
//   Pitch += (180 * (temp->y - Screen->Height/2) / Screen->Height);
//   ::SetCursorPos (Screen->Width/2, Screen->Height/2);


// Z=Dist*sin(Pitch*M_PI/180.0f);

   while(Z>Zreal && Z>Dist*sin(Pitch*M_PI/180.0f)){
    Z-=0.1;
    Zreal+=0.2;
   }
   Zreal=HeightM(-MapX+X,-MapY+Y)+MapZ+4;
   DistXY=Dist*cos(Pitch*M_PI/180.0f);
   X=-DistXY*sin(Yaw*M_PI/180.0f);
   Y=-DistXY*cos(Yaw*M_PI/180.0f);
 //  if(Z<HeightM(-MapX+X,-MapY+Y)+MapZ+4)Z=HeightM(-MapX+X,-MapY+Y)+MapZ+4;
   while(Z<Zreal){
    Z+=0.1;
    Zreal-=0.2;
   }
}
else {
   Z=Dist*sin(Pitch*M_PI/180.0f);
   DistXY=Dist*cos(Pitch*M_PI/180.0f);
   X=-DistXY*sin(Yaw*M_PI/180.0f);
   Y=-DistXY*cos(Yaw*M_PI/180.0f);
   Yaw += (180 * (temp->x - Screen->Width/2) / Screen->Width);
   Pitch += (180 * (temp->y - Screen->Height/2) / Screen->Height);
   ::SetCursorPos (Screen->Width/2, Screen->Height/2);
}
}
//---------------------------------------------------------------------------
void MoveM(){

float FSIN = sin (Yaw*M_PI/180.0f);
float FCOS = cos (Yaw*M_PI/180.0f);

if (KeyA) {MapX += 0.3 * FCOS; MapY -= 0.3 * FSIN;}
if (KeyD) {MapX -= 0.3 * FCOS; MapY += 0.3 * FSIN;}
if (KeyW) {MapX -= 0.3 * FSIN; MapY -= 0.3 * FCOS;}
if (KeyS) {MapX += 0.3 * FSIN; MapY += 0.3 * FCOS;}
}
void __fastcall TMainFrm::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if      (Key == 'A') KeyA=false;
else if (Key == 'D') KeyD=false;
else if (Key == 'W') KeyW=false;
else if (Key == 'S') KeyS=false;

}
//---------------------------------------------------------------------------

