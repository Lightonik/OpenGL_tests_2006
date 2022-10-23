#include <stdlib.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <windows.h>
#include <ExtCtrls.hpp>
#include <GL\gl.h>
#include <GL\glu.h>
#include <math.h>
#include "main.h"
//const int models=6;
//---------------------------------------------------------------------------
void __fastcall Body(float lhandx_1, float lhandy_1, float lhandz_1,
                     float lhand_2)
{
glEnable(GL_POLYGON_SMOOTH);

glBindTexture (GL_TEXTURE_2D, Texture [1]);
glCallList(1);
glTranslatef(0.32,0.105,0.33);
glBindTexture (GL_TEXTURE_2D, Texture [2]);
glPushMatrix();
if(lhandy_1<0)lhandy_1*=2;
glRotatef(lhandy_1/2,0,1,0);
glCallList(2);
//glPopMatrix();
glTranslatef(0.02,-0.04,0.12);
if(lhandy_1>0)glRotatef(lhandy_1/2,0,1,0);
glBindTexture (GL_TEXTURE_2D, Texture [5]);
glCallList(8);
glTranslatef(0.7,0,0);
glRotatef(lhand_2/2,0,0,-1);
glCallList(10);
glRotatef(lhand_2/2,0,0,-1);
//glBindTexture (GL_TEXTURE_2D, Texture [5]);
glCallList(9);
glPopMatrix();
glTranslatef(-0.66,0,0);
glBindTexture (GL_TEXTURE_2D, Texture [2]);
glCallList(3);
glTranslatef(0.34,-0.12,-1);
glBindTexture (GL_TEXTURE_2D, Texture [3]);
glCallList(4);
glBindTexture (GL_TEXTURE_2D, Texture [4]);
glCallList(5);
glCallList(6);
glCallList(7);

}
//---------------------------------------------------------------------------
void __fastcall InitModel(int model)
{
FILE *in;
int poly, ver,i,j,k;
bool tex,norm,col;
float x,y,z,nx,ny,nz,tx,ty,cr,cg,cb;
 switch (model){
  case 1: in=fopen("Data\\body.ver","r"); break;
  case 2: in=fopen("Data\\lshoulder.ver","r"); break;
  case 3: in=fopen("Data\\rshoulder.ver","r"); break;
  case 4: in=fopen("Data\\belt_1.ver","r"); break;
  case 5: in=fopen("Data\\belt_2.ver","r"); break;
  case 6: in=fopen("Data\\belt_3.ver","r"); break;
  case 7: in=fopen("Data\\belt_4.ver","r"); break;
  case 8: in=fopen("Data\\lhand_1.ver","r"); break;
  case 9: in=fopen("Data\\lhand_2.ver","r"); break;
  case 10: in=fopen("Data\\lhand_3.ver","r"); break;

 }
 fscanf(in,"%d",&poly);
 glNewList(model,GL_COMPILE);
 glColor3f(0,0.5,0);
 for(i=0;i<poly;i++){
  fscanf(in,"%d %d",&ver,&tex);
  if(tex) glEnable (GL_TEXTURE_2D);
  glBegin(GL_POLYGON);
  for(j=0;j<ver;j++){
   fscanf(in,"%f %f %f",&x,&y,&z);
   fscanf(in,"%f %f %f",&nx,&ny,&nz);
   if(tex) fscanf(in,"%f %f",&tx,&ty);
   glNormal3f(nx,ny,nz);
   if(tex) glTexCoord2f(tx,ty);
   glVertex3f(x,y,z);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
 }
 glEndList();
 fclose(in);
}

//---------------------------------------------------------------------------

