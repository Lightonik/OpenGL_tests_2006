#include <math.h>

const long int Max_Ver=256*256;
const long int Max_Face=256*256;
int Vertexn;
int Facen;
float Vertexs[3][Max_Ver];
int Faces[3][Max_Face];
float Textures[2][Max_Ver];
int FacesTex[3][Max_Face];
float Normals[3][Max_Ver];
//float Material[4];
//float LocMat[4][4];

void RenderHeightMap(int id);
bool LoadRawFile(AnsiString filename,int id);
void ReadStr(FILE *in, int i);
bool LoadFile(AnsiString filename,int start, int frames, float scale);
void LoadTex(FILE *in);
void FindWord(FILE *in, AnsiString word);
//void DrawModel(int id );
bool InitTex (AnsiString filename, int index);

//---------------------------------------------------------------------------
void DrawModel(int id, float scale)
{
int i;
if(scale==0)scale=1;
glNewList (id, GL_COMPILE);
for(i=0;i<Facen;i++){
 glBegin(GL_TRIANGLES);
  glNormal3f(Normals[0][Faces[0][i]-1],Normals[1][Faces[0][i]-1],Normals[2][Faces[0][i]-1]);
  glTexCoord2f(Textures[0][FacesTex[0][i]-1],Textures[1][FacesTex[0][i]-1]);
    glVertex3f(Vertexs[0][Faces[0][i]-1]/scale,Vertexs[1][Faces[0][i]-1]/scale,Vertexs[2][Faces[0][i]-1]/scale);
  glNormal3f(Normals[0][Faces[1][i]-1],Normals[1][Faces[1][i]-1],Normals[2][Faces[1][i]-1]);
  glTexCoord2f(Textures[0][FacesTex[1][i]-1],Textures[1][FacesTex[1][i]-1]);
    glVertex3f(Vertexs[0][Faces[1][i]-1]/scale,Vertexs[1][Faces[1][i]-1]/scale,Vertexs[2][Faces[1][i]-1]/scale);
  glNormal3f(Normals[0][Faces[2][i]-1],Normals[1][Faces[2][i]-1],Normals[2][Faces[2][i]-1]);
  glTexCoord2f(Textures[0][FacesTex[2][i]-1],Textures[1][FacesTex[2][i]-1]);
    glVertex3f(Vertexs[0][Faces[2][i]-1]/scale,Vertexs[1][Faces[2][i]-1]/scale,Vertexs[2][Faces[2][i]-1]/scale);

 glEnd();
}
glEndList();
}
//---------------------------------------------------------------------------
bool ReadFiles()
{
// LoadRawFile("Data\\Terrain\\001.raw",1);
 InitTex("Data\\Textures\\001.bmp",0);
 InitTex("Data\\Textures\\001d.bmp",1);
 InitTex("Data\\Textures\\metall.bmp",2);
 LoadFile("Data\\Models\\human.gms",1,1,1);
/*FILE *in;
if((in = fopen("Data\\config.txt","r"))==NULL)return false;
int i,num,frame,start;
AnsiString filename;
char c;
fscanf(in,"%d",&num);
fscanf(in,"%c",&c);
for(i=0;i<num;i++){
 do{
  if(c!='\n')filename+=c;
  fscanf(in,"%c",&c);
  }while(c!=' ');
 fscanf(in,"%d %d\n",&start,&frame);
 LoadFile(filename,start,frame);
 filename="";
 }
fscanf(in,"%d",&num);
fscanf(in,"%c",&c);
for(i=0;i<num;i++){
 do{
  if(c!='\n')filename+=c;
  fscanf(in,"%c",&c);
  }while(c!='\n' && !feof(in));
 InitTex(filename,i+1);
 filename="";
 }
fclose(in); */
return true;
}
//---------------------------------------------------------------------------
bool LoadFile(AnsiString filename,int start, int frames, float scale)
{
int i,j,num;
FILE *in;
if((in = fopen(filename.c_str(),"r"))==NULL)return false;
LoadTex(in);
for(j=0;j<frames;j++){
 ReadStr(in,5);
 fscanf(in,"%d %d\n",&Vertexn,&Facen);
 ReadStr(in,1);
 for(i=0;i<Vertexn;i++)fscanf(in,"%f %f %f\n",&Vertexs[0][i],&Vertexs[1][i],&Vertexs[2][i]);
 ReadStr(in,2);
 for(i=0;i<Facen;i++)fscanf(in,"%d %d %d\n",&Faces[0][i],&Faces[1][i],&Faces[2][i]);
 ReadStr(in,2);
 for(i=0;i<Vertexn;i++)fscanf(in,"%f %f %f\n",&Normals[0][i],&Normals[1][i],&Normals[2][i]);
 DrawModel(j+start, scale);
}
fclose(in);
return true;
}
//---------------------------------------------------------------------------
void LoadTex(FILE *in){
int i;
ReadStr(in,2);
fscanf(in,"%d %d\n",&Vertexn,&Facen);
ReadStr(in,1);
for(i=0;i<Vertexn;i++)fscanf(in,"%f %f\n",&Textures[0][i],&Textures[1][i]);
ReadStr(in,2);
for(i=0;i<Facen;i++)fscanf(in,"%d %d %d\n",&FacesTex[0][i],&FacesTex[1][i],&FacesTex[2][i]);
};
//---------------------------------------------------------------------------
bool InitTex (AnsiString filename, int index)
{
 int w,h;
 Graphics::TBitmap *bitmap;
 bitmap = new Graphics::TBitmap;
 bitmap->LoadFromFile (filename);
 w = bitmap->Width;
 h = bitmap->Height;
    for(int i = 0; i < w; i++)
    {
      for(int j = 0; j < h; j++)
        {
           bits[j+w*i][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[j][i]);
           bits[j+w*i][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[j][i]);
           bits[j+w*i][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[j][i]);
           bits[j+w*i][3]= (GLbyte)255;
       }
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenTextures(1, &Texture[index]);
    glBindTexture(GL_TEXTURE_2D, Texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, bits);
return true;
}
//-------------------------------------------------------------------------
void FindWord(FILE *in, AnsiString word){
AnsiString curr;
char c;
do{
 curr="";
 fscanf(in,"%c",&c);
 do{
  if(c!=' ' && c!='\n')curr+=c;
  fscanf(in,"%c",&c);
 }while(c!=' ' && c!='\n' && !feof(in));
}while(word!=curr && !feof(in));
}
//-------------------------------------------------------------------------
void ReadStr(FILE *in, int i){
char c;
for(int j=0;j<i;j++){
 do{
   fscanf(in,"%c",&c);
  }while(c!='\n' && !feof(in));
 }
}
//-------------------------------------------------------------------------
int HeightM(int X, int Y)
{
int x = X % 1024;
int y = Y % 1024;
return Map[x+y*1024];
}
//-------------------------------------------------------------------------
bool LoadRawFile(AnsiString filename,int id)
{
FILE *in = NULL;
if((in = fopen(filename.c_str(),"r"))==NULL)return false;
fread( Map, 1, 1024*1024, in );
fclose(in);
RenderHeightMap(id);
return true;
}

//-------------------------------------------------------------------------
void SetTextureCoord(float x, float y)
{
float u =  (float)x / (float)1024;
float v = -(float)y / (float)1024;
glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);
glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}
//-------------------------------------------------------------------------
void Normal(int X,int Y){
int i;
struct {
 float x,y,z,l,poz;
}Vector[9];
int Z;
Vector[0].x=Vector[0].y=Vector[0].z=0;

Vector[1].x=Vector[2].x=Vector[8].x=DETAL;
Vector[3].x=Vector[7].x=0;
Vector[4].x=Vector[5].x=Vector[6].x=-DETAL;

Vector[2].y=Vector[3].y=Vector[4].y=DETAL;
Vector[5].y=Vector[1].y=0;
Vector[6].y=Vector[7].y=Vector[8].y=-DETAL;

for(i=1;i<9;i++){
 Z=X+Vector[i].x+(Y+Vector[i].y)*1024;
 Vector[i].z=Map[Z];
// Vector[i].z=Map[(Vector[i].x)]+Map[X+Y*1024];
 Vector[i].l=sqrt(pow(Vector[i].x,2)+pow(Vector[i].y,2)+pow(Vector[i].z,2));
 Vector[0].x+=Vector[i].x/Vector[i].l;
 Vector[0].y+=Vector[i].y/Vector[i].l;
 Vector[0].z+=Vector[i].z/Vector[i].l;
}
glNormal3f(Vector[0].x,Vector[0].y,Vector[0].z);
}
//-------------------------------------------------------------------------
void RenderHeightMap(int id)
{
int X = 0, Y = 0;
int x, y, z;
float tx,ty;
bool bSwitchSides = false;
glNewList (id, GL_COMPILE);
glBegin( GL_TRIANGLE_STRIP );
for ( X = 0; X <= 1024; X += DETAL ){
 if(bSwitchSides){
  for ( Y = 1024; Y >= 0; Y -= DETAL ){
   x = X;
   z = HeightM(X, Y );
   y = Y;
   SetTextureCoord( (float)x, (float)y );
   Normal( (float)x, (float)y );
   glVertex3i(x, y, z);
   x = X + DETAL;
   z = HeightM(X + DETAL, Y );
   y = Y;
   SetTextureCoord( (float)x, (float)y );
   Normal( (float)x, (float)y );
   glVertex3i(x, y, z);
   }
  }
 else {
  for ( Y = 0; Y <= 1024; Y += DETAL ){
   x = X + DETAL;
   z = HeightM(X + DETAL, Y );
   y = Y;
   SetTextureCoord( (float)x, (float)y );
   Normal( (float)x, (float)y );
   glVertex3i(x, y, z);
   x = X;
   z = HeightM(X, Y );
   y = Y;
   SetTextureCoord( (float)x, (float)y );
   Normal( (float)x, (float)y );
  glVertex3i(x, y, z);
  }
 }
 bSwitchSides = !bSwitchSides;
}
glEnd();
glEndList();
}
//-------------------------------------------------------------------------
void DrawLand(int id){
   glActiveTextureARB(GL_TEXTURE0_ARB);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, Texture[0]);
   		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
		glBindTexture(GL_TEXTURE_2D, Texture[1]);
		glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glScalef((float)TEXDET, (float)TEXDET, 1);
		glMatrixMode(GL_MODELVIEW);



  glBindTexture(GL_TEXTURE_2D, Texture [1]);

  glCallList(id);

  glActiveTextureARB(GL_TEXTURE1_ARB);
  glDisable(GL_TEXTURE_2D);

  glActiveTextureARB(GL_TEXTURE0_ARB);
  glDisable(GL_TEXTURE_2D);

}
