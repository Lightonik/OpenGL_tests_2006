//==== Хранение бит-карты ===================================================
# define SIZE_OF_MAP 48
BYTE HMap[SIZE_OF_MAP*SIZE_OF_MAP];
int DETAL = 2;
int SCALE = 1;
int TEXDET = 4;
//==== Создание и изображение ландшафта =====================================
class CTerrain {
        public:
                CTerrain();
//                bool Set(AnsiString inifile);
                bool LoadFile(AnsiString filename);
                void Render();
                int HeightM(int X, int Y);
                int MainTex;
        private:
                void Create();
                void SetTextureCoord(float x, float y);
                void Normal(int X,int Y);
                int id;
//                AnsiString filename;
//                AnsiString maintex;
//                AnsiString mintex;
                int MinTex;
};
//===========================================================================
CTerrain::CTerrain() {
//        id=20;
        MinTex=1;
}
//==== Файлы ландшафта и текстур ============================================
/*bool CTerrain::Set(AnsiString inifile) {
        FILE *ini;
        char c;
        AnsiString text;
        if((ini = fopen(inifile.c_str(),"r"))==NULL) {
                text+="Файл ";
                text+=inifile;
                text+=" не существует";
                AddToLog(text);
                return false;
                }
        fscanf(ini,"%c",&c);
        do{
                if(c!='\n')
                        filename+=c;
                fscanf(ini,"%c",&c);
        }while(c!=' ' && c!='\n' && !feof(ini));
        fscanf(ini,"%c",&c);
        do{
                if(c!='\n')
                        maintex+=c;
                fscanf(ini,"%c",&c);
        }while(c!=' ' && c!='\n' && !feof(ini));
        fscanf(ini,"%c",&c);
        do{
                if(c!='\n')
                        mintex+=c;
                fscanf(ini,"%c",&c);
        }while(c!=' ' && c!='\n' && !feof(ini));
        fclose(ini);
        return true;
}       */
//==== Загрузка файлов ======================================================
bool CTerrain::LoadFile(AnsiString filename) {
        FILE *file;
        AnsiString text;
        if((file = fopen(filename.c_str(),"r"))==NULL) {
                text+="Файл ";
                text+=filename;
                text+=" не существует";
                AddToLog(text);
                return false;
                }
        id=glGenLists(1);
        text="Ландшафту присвоен список ";
        text+=IntToStr(id);
        AddToLog(text);
        fread(HMap,1,SIZE_OF_MAP*SIZE_OF_MAP,file);
        fclose(file);
//        MainTex.Load(maintex);
//        MinTex.Load(mintex);
        Create();
        AddToLog("Загрузка ландшафта завершена");
        return true;
}
//==== Создание поверхности =================================================
void CTerrain::Create() {
        int X = 0, Y = 0;
        int x, y, z;
        float tx,ty;
        bool bSwitchSides = false;
        glNewList (id, GL_COMPILE);
        glBegin( GL_TRIANGLE_STRIP );
        for ( X = 0; X <= SIZE_OF_MAP; X += DETAL ) {
                if(bSwitchSides){
                        for ( Y = SIZE_OF_MAP; Y >= 0; Y -= DETAL ){
                                x = X;
                                z = HeightM(X, Y );
                                y = Y;
                                SetTextureCoord( (float)x, (float)y );
//                                Normal( (float)x, (float)y );
                                glVertex3i(x/SCALE, y/SCALE, z/SCALE);
                                x = X + DETAL;
                                z = HeightM(X + DETAL, Y );
                                y = Y;
                                SetTextureCoord( (float)x, (float)y );
//                                Normal( (float)x, (float)y );
                                glVertex3i(x/SCALE, y/SCALE, z/SCALE);
                        }
                }
                else {
                        for ( Y = 0; Y <= SIZE_OF_MAP; Y += DETAL ){
                                x = X + DETAL;
                                z = HeightM(X + DETAL, Y );
                                y = Y;
                                SetTextureCoord( (float)x, (float)y );
//                                Normal( (float)x, (float)y );
                                glVertex3i(x/SCALE, y/SCALE, z/SCALE);
                                x = X;
                                z = HeightM(X, Y );
                                y = Y;
                                SetTextureCoord( (float)x, (float)y );
//                                Normal( (float)x, (float)y );
                                glVertex3i(x/SCALE, y/SCALE, z/SCALE);
                        }
                }
                bSwitchSides = !bSwitchSides;
        }
        glEnd();
        glEndList();
}
//==== Ф-я определения высоты в конкретной точке ============================
int CTerrain::HeightM(int X, int Y) {
        return HMap[X%SIZE_OF_MAP+(Y%SIZE_OF_MAP)*SIZE_OF_MAP];
}
//==== Задание тексуры ======================================================
void CTerrain::SetTextureCoord(float x, float y) {
        float u =  (float)x / (float)SIZE_OF_MAP;
        float v = -(float)y / (float)SIZE_OF_MAP;
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, u, v);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, u, v);
}
//==== Вычисление нормали ===================================================
void CTerrain::Normal(int X,int Y) {
        int i,Z;
        Vector Vec[9];
        Vec[0].x=Vec[0].y=Vec[0].z=0;
        Vec[1].x=Vec[2].x=Vec[8].x=DETAL;
        Vec[3].x=Vec[7].x=0;
        Vec[4].x=Vec[5].x=Vec[6].x=-DETAL;
        Vec[2].y=Vec[3].y=Vec[4].y=DETAL;
        Vec[5].y=Vec[1].y=0;
        Vec[6].y=Vec[7].y=Vec[8].y=-DETAL;
        for(i=1;i<9;i++){
                Vec[i].z=HeightM(X+Vec[i].x,Y+Vec[i].y);
                Vec[i].Normal();
                Vec[0].x+=Vec[i].x;
                Vec[0].y+=Vec[i].y;
                Vec[0].z+=Vec[i].z;
        }
        glNormal3f(Vec[0].x,Vec[0].y,Vec[0].z);
}
//==== Рендеринг поверхности ================================================
void CTerrain::Render() {
        glActiveTextureARB(GL_TEXTURE0_ARB);
        glEnable(GL_TEXTURE_2D);
//        MainTex.Select();
        glBindTexture(GL_TEXTURE_2D, MainTex);
        glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
//        MinTex.Select();
        glBindTexture(GL_TEXTURE_2D, MinTex);
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glScalef((float)TEXDET, (float)TEXDET, 1);
        glMatrixMode(GL_MODELVIEW);
//        MinTex.Select();
        glBindTexture(GL_TEXTURE_2D, MinTex);
//---- Ландшафт упрощён квадратиком с текстурой :-( -------------------------
        glBegin(GL_QUADS);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
        glVertex3i(-24,-24,0);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
        glVertex3i(-24,24,0);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
        glVertex3i(24,24,0);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
        glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
        glVertex3i(24,-24,0);
        glEnd();
//---------------------------------------------------------------------------
        glActiveTextureARB(GL_TEXTURE1_ARB);
        glDisable(GL_TEXTURE_2D);
        glActiveTextureARB(GL_TEXTURE0_ARB);
        glDisable(GL_TEXTURE_2D);
}
//===========================================================================
//CTerrain Land;
