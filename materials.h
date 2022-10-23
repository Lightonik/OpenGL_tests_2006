   GLfloat
    lposition[]  = {0, 0, 10, 1},
    ldirection[] = {0, 0, 0},
    ____white[]  = {1.0, 1.0, 1.0, 1.0},
    ____black[]  = {0.0, 0.0, 0.0, 1.0},
    Ambient[]    = {0.5, 0.5, 0.5, 1.0},
    Diffuse[]    = {0.5, 0.5, 0.5, 1},
    Specular[]   = {0.0, 0.0, 0.0, 0,},
    Shininess[]  = {50.0},
    _mainlight[] = {0.0, 0.0, 0.0, 0.0},
    _specular[]  = {0.5, 0.5, 0.5, 0,},
    _lambient[]  = {0.5, 0.5, 0.5, 1.0},
    _ldiffuse[]  = {1.0, 1.0, 1, 1.0};

void LightON(){
glEnable (GL_LIGHTING);
glLightModelfv (GL_LIGHT_MODEL_AMBIENT, _mainlight);

}
void SetMaterial(){
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);

      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
      glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Shininess);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ____black);

//   glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void Light(int id){
switch(id){
 case 0:
 glEnable (GL_LIGHT0);
 glLightfv (GL_LIGHT0, GL_POSITION, lposition);
 glLightfv (GL_LIGHT0, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT0, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT0, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT0, GL_SPECULAR, _specular);
 break;
 case 1:
 glEnable (GL_LIGHT1);
 glLightfv (GL_LIGHT1, GL_POSITION, lposition);
 glLightfv (GL_LIGHT1, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT1, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT1, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT1, GL_SPECULAR, _specular);
 break;
 case 2:
 glEnable (GL_LIGHT0);
 glLightfv (GL_LIGHT2, GL_POSITION, lposition);
 glLightfv (GL_LIGHT2, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT2, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT2, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT2, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT2, GL_SPECULAR, _specular);
 break;
 case 3:
 glEnable (GL_LIGHT0);
 glLightfv (GL_LIGHT3, GL_POSITION, lposition);
 glLightfv (GL_LIGHT3, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT3, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT3, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT3, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT3, GL_SPECULAR, _specular);
 break;
 case 4:
 glEnable (GL_LIGHT0);
 glLightfv (GL_LIGHT4, GL_POSITION, lposition);
 glLightfv (GL_LIGHT4, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT4, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT4, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT4, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT4, GL_SPECULAR, _specular);
 break;
 case 5:
 glEnable (GL_LIGHT0);
 glLightfv (GL_LIGHT5, GL_POSITION, lposition);
 glLightfv (GL_LIGHT5, GL_AMBIENT, _lambient);
 glLightfv (GL_LIGHT5, GL_DIFFUSE, _ldiffuse);
 glLightfv (GL_LIGHT5, GL_SPECULAR, ____black);
 glLightfv (GL_LIGHT5, GL_SPOT_DIRECTION, ldirection);
 glLightfv (GL_LIGHT5, GL_SPECULAR, _specular);
 break;
 }
}
void LightOFF(int id){
switch(id){
case 0:
 glDisable (GL_LIGHT0);
 break;
case 1:
 glDisable (GL_LIGHT1);
 break;
case 2:
 glDisable (GL_LIGHT2);
 break;
case 3:
 glDisable (GL_LIGHT3);
 break;
case 4:
 glDisable (GL_LIGHT4);
 break;
case 5:
 glDisable (GL_LIGHT5);
 break;
}
}
