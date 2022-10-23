//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("game.res");
USEFORM("main.cpp", MainFrm);
USE("comons.h", File);
USE("particles.h", File);
USE("camera.h", File);
USE("vector.h", File);
USE("models.h", File);
USE("texture.h", File);
USE("terrain.h", File);
USE("console.h", File);
USE("font.h", File);
USE("materials.h", File);
USE("graphics.h", File);
USE("loading.h", File);
USE("objects.h", File);
USE("Data\weapon.ini", File);
USE("interface.h", File);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "[noname]";
                 Application->CreateForm(__classid(TMainFrm), &MainFrm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
