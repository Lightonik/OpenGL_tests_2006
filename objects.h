//===========================================================================
# define STAY 0
# define START 1
# define RUN 2
# define STOP 3
//==== Класс объектов и т.п. ================================================
class CObject {
        public:
                CObject();
                AnsiString name;
                int texid;
                int modid;
                int animate[7];
                int posCurr;                            // текущая позиция
                int posTo;                              // целевая позиция
                int posNext;                            // следующая позиция
                int frame;                              // кадр модели

};
//===========================================================================
CObject::CObject() {
        posCurr=0;
        posTo=0;
        frame=0;
        posNext=0;
}
//==== Класс персонажей =====================================================
class CCharacter {
        public:
                CCharacter();
                void Command(int com);
                bool Turn();
                bool turning,runing;
                bool Run();
                void RunTo(int toX, int toY);
                int time,checkT,runtime;
                AnsiString name;
                void CreateObj(int number);
                CObject *Objects;
                int objnum;
                float x,y,z;
                float Rx,Ry;
                float ang,Rang;
                int Render(int currframe);
        private:
                Vector Speed;
};
//===========================================================================
CCharacter::CCharacter() {
        turning=false;
        runing=false;
        time=0;
        checkT=0;
}
//==== Создание новых объектов ==============================================
void CCharacter::CreateObj(int number) {
        Objects = new CObject[number];
        objnum = number;
}
//==== Рисование персонажа ==================================================
int CCharacter::Render(int currframe) {
        int charframe=0;
        if(currframe!=-1)
                charframe=currframe;
        if(runing) {
                if(runtime<=11)
                        Command(STOP);
                if(Run()) {
                        runing=false;
                        Command(STAY);
                }
        }
        if(turning) {
                if(Turn()) {
//                        runing=true;
//                        Command(RUN);
                        turning=false;
                }
        }
        glTranslatef(x,y,z);
        glRotatef(ang+90,0,0,1);
        for(int i=0;i<objnum;i++) {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, Objects[i].texid);

/*                Models[Objects[i].modid].Enter(Objects[i].posCurr,
                                Objects[i].posTo,Objects[i].posNext,Objects[i].frame);
                Objects[i].posCurr=Models[Objects[i].modid].Animate();
*/
                if(Models[Objects[i].modid].anima=='f') {

//---------------------------------------------------------------------------
/*                Models[Objects[i].modid].Render(Objects[i].frame);
                Objects[i].frame++;
                if(Objects[i].frame>=Models[Objects[i].modid].Positions[Objects[i].posCurr].start
                                        +Models[Objects[i].modid].Positions[Objects[i].posCurr].frames) {
                        if(Objects[i].posCurr==Objects[i].posTo)
                                Objects[i].frame=Models[Objects[i].modid].Positions[Objects[i].posCurr].start;
                        else {
                                Models[Objects[i].modid].posSteps=-1;
                                Models[Objects[i].modid].FindNextPos(Objects[i].posCurr,0);
                                Objects[i].frame=Models[Objects[i].modid].Positions[Objects[i].posNext].start;
                                Objects[i].posCurr=Objects[i].posNext;
                        }
                } */
                Models[Objects[i].modid].posCurr=Objects[i].posCurr;
                Models[Objects[i].modid].posTo=Objects[i].posTo;
                Models[Objects[i].modid].posNext=Objects[i].posNext;
                Models[Objects[i].modid].frame=Objects[i].frame;
                charframe=Models[Objects[i].modid].Animate(currframe);
                Objects[i].posCurr=Models[Objects[i].modid].posCurr;
                Objects[i].posTo=Models[Objects[i].modid].posTo;
                Objects[i].posNext=Models[Objects[i].modid].posNext;
                Objects[i].frame=Models[Objects[i].modid].frame;
//---------------------------------------------------------------------------
                }
                else {
                        glTranslatef(Posit[charframe].x,Posit[charframe].y,Posit[charframe].z);
                        glRotatef(Posit[charframe].a,1,0,0);
                        glRotatef(Posit[charframe].b,0,1,0);
                        glRotatef(Posit[charframe].c,0,0,1);
                        Models[Objects[i].modid].Render(0);
                        glRotatef(-Posit[charframe].c,0,0,1);
                        glRotatef(-Posit[charframe].b,0,1,0);
                        glRotatef(-Posit[charframe].a,1,0,0);
                        glTranslatef(-Posit[charframe].x,-Posit[charframe].y,-Posit[charframe].z);
                }
                glDisable(GL_TEXTURE_2D);
        }
        glRotatef(-ang-90,0,0,1);
        glTranslatef(-x,-y,-z);
        return charframe;
}
//===========================================================================
void CCharacter::Command(int com) {
        for(int i=0;i<objnum;i++)
                Objects[i].posTo=com;
}
//===========================================================================
//===========================================================================
bool CCharacter::Turn() {

        float Dang=20;
        if(ang>Rang-29 && ang<Rang+29) {
                ang=Rang;
                return true;
        }
        if(ang<Rang)
                ang+=Dang;
        else
                ang-=Dang;
        return false;

        /*checkT++;
        if(Rx==x && Ry==y)
                return true;
        float RSang,dang=20; // RCang
        RSang =(180/M_PI)*asin(abs(Rx-x)/sqrt((Rx-x)*(Rx-x)+(Ry-y)*(Ry-y)));
        if(Rx-x==0) {
                if(Ry-y>0)
                        RSang=90;
                else
                        RSang=270;
                if(abs(RSang-ang)>abs(RSang-360-ang))
                        ang+=360;
                if(ang>RSang-29 && ang<RSang+29) {
                        ang=RSang;
                        return true;
                }
                if(ang<RSang) {
                        ang+=dang;
                       // checkT++;
                        return false;
                }
                if(ang>RSang) {
                        ang-=dang;
                      //  checkT++;
                        return false;
                }
        }
        if(Ry-y==0) {
                if(Rx-x>0)
                        RSang=0;
                else
                        RSang=180;
                if(abs(RSang-ang)>abs(RSang-360-ang))
                        ang+=360;
                if(ang>RSang-29 && ang<RSang+29) {
                        ang=RSang;
                        return true;
                }
                if(ang<RSang) {
                        ang+=dang;
                       // checkT++;
                        return false;
                }
                if(ang>RSang) {
                        ang-=dang;
                      //  checkT++;
                        return false;
                }
        }
        if(Rx-x>0 && Ry-y>=0) {                               // первая четверть
                if(abs(RSang-ang)>abs(RSang-360-ang))
                        ang+=360;
                if(ang>RSang-29 && ang<RSang+29) {
                        ang=RSang;
                        return true;
                }
                if(ang<RSang) {
                        ang+=dang;
                      //  checkT++;
                        return false;
                }
                if(ang>RSang) {
                        ang-=dang;
                      //  checkT++;
                        return false;
                }
        }
        if(Rx-x<=0 && Ry-y>0) {                               // вторая четверть
                if(abs(RSang+90-ang)>abs(RSang+90-360-ang))
                        ang+=360;
                if(ang>RSang+61 && ang<RSang+119) {
                        ang=RSang+90;
                        return true;
                }
                if(ang<RSang+90) {
                        ang+=dang;
                     //   checkT++;
                        return false;
                }
                if(ang>RSang+90) {
                        ang-=dang;
                     //   checkT++;
                        return false;
                }
        }
        if(Rx-x<0 && Ry-y<=0) {                               // третья четверть
                RSang=90-RSang;
                if(abs(RSang+180-ang)>abs(RSang+180-360-ang))
                        ang+=360;
                if(ang>RSang+151 && ang<RSang+209) {
                        ang=RSang+180;
                        return true;
                }
                if(ang<RSang+180) {
                        ang+=dang;
                     //   checkT++;
                        return false;
                }
                if(ang>RSang+180) {
                        ang-=dang;
                     //   checkT++;
                        return false;
                }
        }
        if(Rx-x>=0 && Ry-y<0) {                               // четвёртая четверть
                RSang=90-RSang;
                if(abs(RSang+270-ang)>abs(RSang+270-360-ang))
                        ang+=360;
                if(ang>RSang+241 && ang<RSang+299) {
                        ang=RSang+270;
                        return true;
                }
                if(ang<RSang+270) {
                        ang+=dang;
                      //  checkT++;
                        return false;
                }
                if(ang>RSang+270) {
                        ang-=dang;
                      //  checkT++;
                        return false;
                }
        }   
        return false;   */
}
//===========================================================================
bool CCharacter::Run() {
        if(Rx==x && Ry==y)
                return true;
        if(time>=runtime) {
                x=Rx;
                y=Ry;
                return true;
        }
        x+=Speed.x;
        y+=Speed.y;
        time++;
        return false;
}
//===========================================================================
void CCharacter::RunTo(int toX, int toY) {
        Rx=toX;
        Ry=toY;
        Speed.x=Rx-x;
        Speed.y=Ry-y;
        Speed.z=0;
        Speed.Normal();
        Speed.x/=3;
        Speed.y/=3;
        if(Speed.x==0 && Speed.y==0)
                return;

//        Models[Objects[0].modid].Positions[START].frames
/*        int Rtime = Models[Objects[0].modid].Positions[START].frames +
                Models[Objects[0].modid].Positions[STOP].frames +
                Models[Objects[0].modid].Positions[STAY].frames - 11;
*/      if(Speed.x!=0)
                runtime=(Rx-x)/Speed.x;
        else
                runtime=(Ry-y)/Speed.y;
//        runtime-=Rtime;
        if(runtime % Models[Objects[0].modid].Positions[RUN].frames <
                Models[Objects[0].modid].Positions[RUN].frames -
                runtime % Models[Objects[0].modid].Positions[RUN].frames)
                        runtime-=runtime % Models[Objects[0].modid].Positions[RUN].frames;
        else
                        runtime+=Models[Objects[0].modid].Positions[RUN].frames -
                                runtime % Models[Objects[0].modid].Positions[RUN].frames;

        runtime+=1;
        if(runtime==0)
                return;
        Speed.x=(Rx-x)/runtime;
        Speed.y=(Ry-y)/runtime;

        if(Rx==x && Ry>y) 
                Rang=90;
        else if(Rx==x && Ry<y)
                Rang=270;
        else if(Rx>x && Ry==y)
                Rang=0;
        else if(Rx<x && Ry==y)
                Rang=180;
        else if(Rx>x && Ry>y)
                Rang=(180/M_PI)*asin((Ry-y)/(sqrt((Ry-y)*(Ry-y)+(Rx-x)*(Rx-x))));//1
        else if(Rx>x && Ry<y)
                Rang=360+(180/M_PI)*asin((Ry-y)/(sqrt((Ry-y)*(Ry-y)+(Rx-x)*(Rx-x))));//4
        else if(Rx<x && Ry<y)
                Rang=180-(180/M_PI)*asin((Ry-y)/(sqrt((Ry-y)*(Ry-y)+(Rx-x)*(Rx-x))));//2
        else if(Rx<x && Ry>y)
                Rang=180-(180/M_PI)*asin((Ry-y)/(sqrt((Ry-y)*(Ry-y)+(Rx-x)*(Rx-x))));//3
        if(Rang-ang>180)
                ang+=360;
        else if(ang-Rang>180)
                ang-=360;
        time=0;
        turning=true;
        runing=true;
        Command(RUN);
}
//===========================================================================

