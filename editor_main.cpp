//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include "comons.h"
#pragma hdrstop

#include "editor_main.h"
//#include "edit_fun.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TEditFrm *EditFrm;
int cur_ver=0,cur_poly=0,k;
//---------------------------------------------------------------------------
__fastcall TEditFrm::TEditFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------/*for (int i = 0; i < FileListBox1->Items->Count; i++)
//---------------------------------------------------------------------------
void __fastcall TEditFrm::BuildVer()
{
XEdit->Enabled=false;
YEdit->Enabled=false;
ZEdit->Enabled=false;
NxEdit->Enabled=false;
NyEdit->Enabled=false;
NzEdit->Enabled=false;
int i,j=0,tmp;
//PolyEdit->Text=IntToStr(cur_poly+1);
//VerEdit->Text=IntToStr(cur_ver+1);
if(tex[cur_poly])TexRad->ItemIndex=0;
else TexRad->ItemIndex=1;
for(i=0;i<cur_poly;i++)j+=ver[i];
tmp=vertex[j+cur_ver].x*100;
XEdit->Text=IntToStr(tmp);
tmp=vertex[j+cur_ver].y*100;
YEdit->Text=IntToStr(tmp);
tmp=vertex[j+cur_ver].z*100;
ZEdit->Text=IntToStr(tmp);
tmp=vertex[j+cur_ver].nx*100;
NxEdit->Text=IntToStr(tmp);
tmp=vertex[j+cur_ver].ny*100;
NyEdit->Text=IntToStr(tmp);
tmp=vertex[j+cur_ver].nz*100;
NzEdit->Text=IntToStr(tmp);
if(tex[cur_poly]){
 tmp=vertex[j+cur_ver].tx*100;
 TxEdit->Text=IntToStr(tmp);
 tmp=vertex[j+cur_ver].ty*100;
 TyEdit->Text=IntToStr(tmp);
 TxEdit->Enabled=true;
 TyEdit->Enabled=true;
 }
else {
 TxEdit->Enabled=false;
 TyEdit->Enabled=false;
 }
XEdit->Enabled=true;
YEdit->Enabled=true;
ZEdit->Enabled=true;
NxEdit->Enabled=true;
NyEdit->Enabled=true;
NzEdit->Enabled=true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TEditFrm::FormCreate(TObject *Sender)
{
FileBox->Directory = "Data\\";
InitGL(Handle,0,0,640,480);
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::FileBoxClick(TObject *Sender)
{
int i,j;
k=0;
//TexRad->Enabled=false;
bool norm,col;
int Itm=FileBox->ItemIndex;
FILE *in = fopen(FileBox->Items->Strings[Itm].c_str(),"r");
fscanf(in,"%d",&poly);
 for(i=0;i<poly;i++){
  fscanf(in,"%d %d",&ver[i],&tex[i]);
  for(j=k;j<ver[i]+k;j++){
   fscanf(in,"%f %f %f",&vertex[j].x,&vertex[j].y,&vertex[j].z);
   fscanf(in,"%f %f %f",&vertex[j].nx,&vertex[j].ny,&vertex[j].nz);
   if(tex[i]) fscanf(in,"%f %f",&vertex[j].tx,&vertex[j].ty);

  } k+=ver[i];
 }
 fclose(in);
 PSEdit->MaxValue=poly-1;
 VSEdit->MaxValue=ver[0]-1;
 PSEdit->Value=0;
 VSEdit->Value=0;
 cur_poly=0;
 cur_ver=0;
 BuildVer();
}
//---------------------------------------------------------------------------
void __fastcall TEditFrm::PSEditChange(TObject *Sender)
{
cur_poly=PSEdit->Value;
VSEdit->MaxValue=ver[cur_poly]-1;
VSEdit->Value=0;
BuildVer();
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::VSEditChange(TObject *Sender)
{
cur_ver=VSEdit->Value;
BuildVer();
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::TexRadClick(TObject *Sender)
{
if(TexRad->ItemIndex==1)tex[cur_poly]=false;
else {
 tex[cur_poly]=true;
// for(i=0;i<cur_poly;i++)j+=ver[i];
// vertex[j+cur_ver].tx=0;
// vertex[j+cur_ver].ty=0;
 }
BuildVer();
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::XEditChange(TObject *Sender)
{
if(XEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].x=StrToFloat(XEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::YEditChange(TObject *Sender)
{
if(YEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].y=StrToFloat(YEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::ZEditChange(TObject *Sender)
{
if(ZEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].z=StrToFloat(ZEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::NxEditChange(TObject *Sender)
{
if(NxEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].nx=StrToFloat(NxEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::NyEditChange(TObject *Sender)
{
if(NyEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].ny=StrToFloat(NyEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::NzEditChange(TObject *Sender)
{
if(NzEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].nz=StrToFloat(NzEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::TxEditChange(TObject *Sender)
{
if(TxEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].tx=StrToFloat(TxEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::TyEditChange(TObject *Sender)
{
if(TyEdit->Enabled){
 int i,j=0;
 for(i=0;i<cur_poly;i++)j+=ver[i];
 vertex[j+cur_ver].ty=StrToFloat(TyEdit->Text)/100;
 }
}
//---------------------------------------------------------------------------

void __fastcall TEditFrm::FormResize(TObject *Sender)
{
RezGL(0,0,640,480);        
}
//---------------------------------------------------------------------------

