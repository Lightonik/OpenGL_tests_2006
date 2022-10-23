//==== Побочный класс для хранения позиций модели ==========================
class CPosition {
        public:
                int toPosition;
                int start;
                int frames;
};
//===== Класс модели ========================================================
class CModel {
        public:
                CModel();
                ~CModel();
                bool Set(AnsiString inifile);
                bool LoadFile();
                void Render(int cur_frame);
                int Animate(int currframe);
                void Command(int pos);
                void Enter(int EposCurr,int EposTo,int EposNext,int Eframe);
                CPosition *Positions;
                bool FindNextPos(int pos,int steps);
                int posSteps;
                char anima;
                int posNumber;
                int posCurr;
                int posTo;
                int posNext;
                int frame;
        private:
                void ReadStr(int i);
                void Create(int frame);
                int id;
                int frames;
                int scale;
                int Vertexn,Facen;
                AnsiString texfile;
                AnsiString filename;
//                CTexture Texture;
                Vector *TrMatrix;
                Vector *Vertexs;
                Vector *Normals;
                Face *Faces;
                Face *FacesTex;
                TexCoord *Textures;
                FILE *file;
};
//===== Обнуление позиций и фреймов =========================================
CModel::CModel() {
        posCurr=0;
        posTo=0;
        frame=0;
}
//===== Удаление модели и её текстуры =======================================
CModel::~CModel() {
      	glDeleteLists(id,frames);
//        Texture.~CTexture();
}
//===== Определяем модель ===================================================
bool CModel::Set(AnsiString inifile) {
        FILE *ini;
        AnsiString text;
        int i;
        char c;
        int fr=0;
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
        }while(c!=' ' && c!='\n');
/*        fscanf(ini,"%c",&c);
        do{
                if(c!='\n')
                        texfile+=c;
                fscanf(ini,"%c",&c);
        }while(c!=' ' && c!='\n');
*/        fscanf(ini,"%d",&frames);
        fscanf(ini,"%d",&scale);
        TrMatrix= new Vector[frames];
        for(i=0;i<frames;i++)
                fscanf(ini,"%f %f %f",&TrMatrix[i].x,&TrMatrix[i].y,&TrMatrix[i].z);
        fscanf(ini,"\n%c",&c);
        anima=c;
        if(c=='f') {
                fscanf(ini,"%d",&posNumber);
                Positions= new CPosition[posNumber];
                for(i=0;i<posNumber;i++) {
                        fscanf(ini,"%d %d",&Positions[i].frames,&Positions[i].toPosition);
                        Positions[i].start=fr;
                        fr+=Positions[i].frames;
                }
        }
        fclose(ini);
        id=glGenLists(frames);

        text="Для модели ";
        text+=filename;
        if(frames!=1) {
                text+=" присвоены списки с ";
                text+=IntToStr(id);
                text+=" по ";
                text+=IntToStr(id+frames-1);
        }
        else {
                text+=" присвоен список ";
                text+=IntToStr(id);
        }
        AddToLog(text);
        if(c=='f')
                AddToLog("Анимация модели кадровая");
        else
                AddToLog("Анимация модели позиционная");
                
        return true;
}
//===== Иерархия движений ===================================================
bool CModel::FindNextPos(int pos,int steps) {
        if(steps>10)
                return false;
        int k=0;
        int code=Positions[pos].toPosition;
        do {
                if(code%2!=0) {
                        code--;
                        if(k==posTo) {
                                steps++;
                                if(steps<posSteps || posSteps==-1) {
                                        if(pos!=posCurr) {
                                                posNext=pos;
                                                posSteps=steps;
                                                return true;
                                        }
                                        else {
                                                posNext=k;
                                                posSteps=steps;
                                                return true;
                                        }
                                }
                                else
                                        return false;
                        }
                        else {
                                if(FindNextPos(k,steps+1)) {
                                        if(pos!=posCurr) {
                                                posNext=pos;
                                                return true;
                                        }
                                }
                        }
                }
                code/=2;
                k++;
        }while(code!=0);
        return false;
}
//===== Загрузка модели из файла ============================================
bool CModel::LoadFile() {
        int i,frame,num;
        AnsiString text;
        if((file = fopen(filename.c_str(),"r"))==NULL) {
                text+="Файл ";
                text+=filename;
                text+=" не существует";
                AddToLog(text);
                return false;
                }
        ReadStr(2);
        fscanf(file,"%d %d\n",&Vertexn,&Facen);
        Textures=new TexCoord[Vertexn];
        FacesTex=new Face[Facen];
        ReadStr(1);
        for(i=0;i<Vertexn;i++)
                fscanf(file,"%f %f\n",&Textures[i].u,&Textures[i].v);
        ReadStr(2);
        for(i=0;i<Facen;i++)
                fscanf(file,"%d %d %d\n",&FacesTex[i].p1,&FacesTex[i].p2,&FacesTex[i].p3);
        for(frame=0;frame<frames;frame++){
                ReadStr(5);
                fscanf(file,"%d %d\n",&Vertexn,&Facen);
                Vertexs=new Vector[Vertexn];
                Faces=new Face[Facen];
                Normals=new Vector[Vertexn];
                ReadStr(1);
                for(i=0;i<Vertexn;i++) {
                        fscanf(file,"%f %f %f\n",&Vertexs[i].x,&Vertexs[i].y,&Vertexs[i].z);
                        Vertexs[i].x+=TrMatrix[frame].x*scale;
                        Vertexs[i].y+=TrMatrix[frame].y*scale;
                        Vertexs[i].z+=TrMatrix[frame].z*scale;
                }
                ReadStr(2);
                for(i=0;i<Facen;i++)
                        fscanf(file,"%d %d %d\n",&Faces[i].p1,&Faces[i].p2,&Faces[i].p3);
                ReadStr(2);
                for(i=0;i<Vertexn;i++)
                        fscanf(file,"%f %f %f\n",&Normals[i].x,&Normals[i].y,&Normals[i].z);
                Create(frame);
                delete[] Vertexs;
                delete[] Faces;
                delete[] Normals;
        }
        delete[] Textures;
        delete[] FacesTex;
        delete[] TrMatrix;
//        Texture.Load(texfile);
        fclose(file);

        text="Загрузка модели завершена. Количество вершин: ";
        text+=IntToStr(Vertexn);
        text+=", количество граней: ";
        text+=IntToStr(Facen);
        AddToLog(text);

        return true;
}
//===== Чтение строки в файле ===============================================
void CModel::ReadStr(int i){
        char c;
        for(int j=0;j<i;j++){
                do{
                        fscanf(file,"%c",&c);
                }while(c!='\n' && !feof(file));
        }
}
//===== Создание модели =====================================================
void CModel::Create(int frame) {
        int i;
        int f1,f2,f3;
        int t1,t2,t3;
        if(scale==0)
                scale=1;
        glNewList (id+frame, GL_COMPILE);
        for(i=0;i<Facen;i++){
                f1=Faces[i].p1-1;
                f2=Faces[i].p2-1;
                f3=Faces[i].p3-1;
                t1=FacesTex[i].p1;
                t2=FacesTex[i].p2;
                t3=FacesTex[i].p3;
                glBegin(GL_TRIANGLES);
                        glNormal3f(Normals[f1].x,Normals[f1].y,Normals[f1].z);
                        glTexCoord2f(Textures[t1].u,1-Textures[t1].v);
                        glVertex3f(Vertexs[f1].x/scale,Vertexs[f1].y/scale,Vertexs[f1].z/scale);
                        glNormal3f(Normals[f2].x,Normals[f2].y,Normals[f2].z);
                        glTexCoord2f(Textures[t2].u,1-Textures[t2].v);
                        glVertex3f(Vertexs[f2].x/scale,Vertexs[f2].y/scale,Vertexs[f2].z/scale);
                        glNormal3f(Normals[f3].x,Normals[f3].y,Normals[f3].z);
                        glTexCoord2f(Textures[t3].u,1-Textures[t3].v);
                        glVertex3f(Vertexs[f3].x/scale,Vertexs[f3].y/scale,Vertexs[f3].z/scale);
                glEnd();
                }
        glEndList();
}
//===== Рисование модели ====================================================
void CModel::Render(int cur_frame) {
//        glEnable(GL_TEXTURE_2D);
//        Texture.Select();
        glCallList(id+cur_frame);
//        glDisable(GL_TEXTURE_2D);
}
//===== Анимация модели =====================================================
int CModel::Animate(int currframe) {
        if(currframe==-1) {
                Render(frame);
                frame++;
                if(frame>=Positions[posCurr].start+Positions[posCurr].frames) {
                        if(posCurr==posTo)
                                frame=Positions[posCurr].start;
                        else {
                                posSteps=-1;
                                FindNextPos(posCurr,0);
                                frame=Positions[posNext].start;
                                posCurr=posNext;
                        }
                }
        }
        else {
                Render(currframe);
                return currframe;
        }
        return frame;
}
//===== Входящая команда ====================================================
void CModel::Command(int pos) {
        posTo=pos;
}
//===== Передача параметров анимации ========================================
void CModel::Enter(int EposCurr,int EposTo,int EposNext,int Eframe) {
        posCurr=EposCurr;
        posTo=EposTo;
        posNext=EposNext;
        frame=Eframe;
}
//===========================================================================
CModel *Models;
UniPosition *Posit;


