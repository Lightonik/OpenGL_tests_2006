//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("editor.res");
USEFORM("editor_main.cpp", EditFrm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TEditFrm), &EditFrm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
