//==== Класс управления камерой =============================================
class CCamera {
        public:
                CCamera();
                void Set();
                void Distans(int delt);
                void Currect();
                void MoveLook(float dx, float dy);
                bool PointIn(Vector &point);
                void ChangeAng(float da);
        private:
                Vector position;
                Vector lookat;
                Vector angel;
                float distans;
                float min, max;
                float fovY,fovX;
                float aspect;
};
//==== Начальные координаты =================================================
CCamera::CCamera() {
        distans=20;
        angel.x=45;
        angel.z=0;
        lookat.x=0;
        lookat.y=0;
        lookat.z=0;
        min=0.1;
        max=4000;
        fovY=90;
        aspect=4/3;
        fovX=2*atan(max*tan(fovY/2)*aspect/max);
}
//==== Приближение/удаление =================================================
void CCamera::Distans(int delt) {
        distans+=delt;
        if(distans<2)
                distans=2;
        if(distans>50)
                distans=50;
}
//==== Задать положение =====================================================
void CCamera::Set() {
        gluLookAt(position.x, position.y, position.z,
                lookat.x, lookat.y, lookat.z,
                0, 0, 1);
}
//==== Определить положение =================================================
void CCamera::Currect() {
        TPoint* cursor;
        cursor = new TPoint;
        ::GetCursorPos (cursor);
//        int center=Screen->Width/2;
//        int centerY=Screen->Height/2;
        position.x=lookat.x+distans*cos(angel.x*M_PI/180)*sin(angel.z*M_PI/180);
        position.y=lookat.y+distans*cos(angel.x*M_PI/180)*cos(angel.z*M_PI/180);
        position.z=lookat.z+distans*sin(angel.x*M_PI/180);
        int ScrMin=0;
        int ScrMax=Screen->Width;

        while(cursor->x > ScrMax-5){
                angel.z++;
                ScrMax+=1;
//                ::SetCursorPos (cursor->x-1, cursor->y);
        }
        while(cursor->x < ScrMin+5) {
                angel.z--;
                ScrMin-=1;
//                ::SetCursorPos (cursor->x+1, cursor->y);
        }


/*        int center=Screen->Width/2;
//      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        float Zreal=Land.HeightM(position.x, position.y)+3, Zlook;

        while(cursor->x > center+50){
                angel.z++;
                center+=50;
                ::SetCursorPos (cursor->x-1, cursor->y);
        }
        while(cursor->x < center-50) {
                angel.z--;
                center-=50;
                ::SetCursorPos (cursor->x+1, cursor->y);
        }
//      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        lookat.z=Land.HeightM(lookat.x, lookat.y)+3;
        Zlook=lookat.z+distans*sin(angel.x*M_PI/180);
        position.x=lookat.x+distans*cos(angel.x*M_PI/180)*sin(angel.z*M_PI/180);
        position.y=lookat.y+distans*cos(angel.x*M_PI/180)*cos(angel.z*M_PI/180);
        while(position.z < Zreal){
                position.z+=0.1;
                Zreal-=0.2;
        }
//      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        Zreal=Land.HeightM(position.x, position.y)+3;
        while(position.z > Zreal
                && position.z >Zlook) {
                        position.z-=0.1;
                        Zreal+=0.2;
        }
//      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        Zreal=Land.HeightM(position.x, position.y)+3;
        while(position.z > Zreal
                && position.z <Zlook) {
                        position.z+=0.1;
                        Zreal+=0.2;
        }  */
}
//==== Изменить точку наблюдения ============================================
void CCamera::MoveLook(float dx, float dy) {
        lookat.x+=dx*sin (angel.z*M_PI/180)-dy*cos (angel.z*M_PI/180);
        lookat.y+=dx*cos (angel.z*M_PI/180)+dy*sin (angel.z*M_PI/180);
}
//==== Изменить угол наклона ================================================
void CCamera::ChangeAng(float da) {
        angel.x+=da;
        if(angel.x<5)
                angel.x=5;
        else
                if(angel.x>89)
                        angel.x=89;
}
//==== Определение в обзоре ли объект =======================================
bool CCamera::PointIn(Vector &point) {
   /*     Vector direction, pointTmp = point, angel;
        direction.x=lookat.x-position.x;
        direction.y=lookat.y-position.y;
        direction.z=lookat.z-position.z;
        pointTmp.x-=position.x;
        pointTmp.y-=position.y;
        pointTmp.z-=position.z;
        pointTmp.Normal();
        direction.Normal();
        angel.y=asin(pointTmp.z)*180/M_PI;
        angel.y-=asin(direction.z)*180/M_PI;
        angel.x=asin(pointTmp.y)*180/M_PI;
        angel.x-=asin(direction.y)*180/M_PI;
        if(abs(angel.y)>fovY/2 || abs(angel.x)>fovX/2)
                return false;
        else    */
                return true;
}
//===========================================================================
