//==== Здесь хранятся все модели и ландшафты ================================
        CTerrain *Terrains;
        CObject *Objects;
        CCharacter *Characters;
//==== Движение одноручного короткого цельного оружия =======================
bool WeaponAni() {
        FILE *ini;
        int num;
        if((ini = fopen("Data\\weapon.ini","r"))==NULL) {
                AddToLog("Файл Data\\weapon.ini не существует");
                return false;
                }
        fscanf(ini,"%d",&num);
        Posit = new UniPosition[num];
        for (int i=0;i<num;i++)
                fscanf(ini,"%f %f %f %f %f %f",&Posit[i].x,&Posit[i].y,&Posit[i].z
                                                ,&Posit[i].a,&Posit[i].b,&Posit[i].c);
        return true;
}
//==== Загрузка текстур и моделей ===========================================
bool StartLoad() {
        Font1.Create();
        FILE *ini, *files;
        int number,j,k,l,obj;
        AnsiString text;
        char filename[22],c;
        WeaponAni();
        if((ini = fopen("Data\\config.ini","r"))==NULL) {
                AddToLog("Файл Data\\config.ini не существует");
                return false;
                }
        fscanf(ini,"%d\n",&number);
        for(int i=0;i<number;i++) {
                fgets(filename, 23, ini);
                fscanf(ini,"\n");
                LoadTexture(filename);
        }
        fscanf(ini,"%d\n",&number);
        Models = new CModel[number];
        for(int i=0;i<number;i++) {
                text="Загрузка модели № ";
                text+=IntToStr(i);
                text+="...";
                AddToLog(text);
                fgets(filename, 23, ini);
                fscanf(ini,"\n");
                Models[i].Set(filename);
                Models[i].LoadFile();
        }
        fscanf(ini,"%d\n",&number);
        Terrains = new CTerrain[number];
        for(int i=0;i<number;i++) {
                text="Загрузка ландшафта № ";
                text+=IntToStr(i);
                text+="...";
                AddToLog(text);
//                fgets(filename, 23, ini);
//                fscanf(ini,"\n");
//                Terrains[i].LoadFile(filename);
                Terrains[i].MainTex=i+2;
        }
        fscanf(ini,"%d\n",&number);
        Objects = new CObject[number];
        for(int i=0;i<number;i++) {
                do{
                        fscanf(ini,"%c",&c);
                        if(c!=' ')
                                Objects[i].name+=c;
                }while(c!=' ');
                fscanf(ini,"%d %d\n",&Objects[i].modid,&Objects[i].texid);
                text="Создан объект - ";
                text+=Objects[i].name;
                text+=", использующий модель № ";
                text+=Objects[i].modid;
                text+=" и текстуру № ";
                text+=Objects[i].texid;
                AddToLog(text);
        }
        if((ini = fopen("Data\\characters.ini","r"))==NULL) {
                AddToLog("Файл Data\\characters.ini не существует");
                return false;
                }
        fscanf(ini,"%d\n",&number);
        Characters = new CCharacter[number];
        for(int i=0;i<number;i++) {
                do{
                        fscanf(ini,"%c",&c);
                        if(c!=' ')
                                Characters[i].name+=c;
                }while(c!=' ');
                text="Создан персонаж - ";
                text+=Characters[i].name;
                AddToLog(text);
                fscanf(ini,"%d",&j);
                Characters[i].CreateObj(j);
                for(k=0;k<j;k++) {
                        fscanf(ini,"%d",&obj);
                        Characters[i].Objects[k]=Objects[obj];
                        for(l=0;l<7;l++)
                                fscanf(ini,"%d",&Characters[i].Objects[k].animate[l]);
                }
                fscanf(ini,"%f %f %f %f\n",&Characters[i].x,&Characters[i].y,&Characters[i].z,
                                                &Characters[i].ang);
        }
        return true;
}
//===========================================================================

