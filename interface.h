Color RGBA_1,RGBA_2;
int panelnum=1;
//CScreenLine *Events;
//int lines=0;
//===========================================================================
bool CursorIn(int left,int top,int right,int bottom) {
        TPoint* cursor;
        int x,y;
        cursor = new TPoint;
        ::GetCursorPos (cursor);
        x=cursor->x;
        y=cursor->y;
        top--;
        bottom--;
        left++;
        right++;
        left*=Screen->Width/40;
        top*=Screen->Height/40;
        right*=Screen->Width/40;
        bottom*=Screen->Height/40;
        if(x>left && x<right && y>top && y<bottom)
                return true;
        return false;
}
//===========================================================================
class CScreenLine {
        public:
                AnsiString text;
                Color TColor;
                Color HighLight;
                int eventcode;
        private:
};
//===========================================================================
class CLinesPanel {
        public:
                void Create(AnsiString panelname, Color nameCol, int maxlines, int X, int Y);
                void CreateLine(AnsiString text,Color TColor,
                     Color HighLight,int eventcode);
                void Draw();
                int max;
                int x,y;
                CScreenLine *Lines;
        private:
                AnsiString name;
                int numlines;
                Color nameC;
}*LinesPanel;
//===========================================================================
void CLinesPanel::Create(AnsiString panelname, Color nameCol, int maxlines, int X, int Y) {
        name=panelname;
        max=maxlines;
        nameC=nameCol;
        x=X;
        y=Y;
        numlines=0;
        Lines= new CScreenLine[max];
}
//===========================================================================
void CLinesPanel::CreateLine(AnsiString text,Color TColor,
                                Color HighLight,int eventcode) {
//        numlines++;
        if(numlines>max)
                return;
        Lines[numlines].text=text;
        Lines[numlines].TColor=TColor;
        Lines[numlines].HighLight=HighLight;
        Lines[numlines].eventcode=eventcode;
        numlines++;
}
//===========================================================================
void CLinesPanel::Draw() {
        Font1.InterPri(x,y,nameC,name.c_str());
        for(int i=0;i<numlines;i++) {
                if(CursorIn(x,y+i+1,x+10,y+i+2))
                        Font1.InterPri(x,y+i+1,Lines[i].HighLight,Lines[i].text.c_str());
                else
                        Font1.InterPri(x,y+i+1,Lines[i].TColor,Lines[i].text.c_str());
        }
}
//===========================================================================
void CreatePanel() {
        RGBA_1.red=1.0f;
        RGBA_1.green=1.0f;
        RGBA_1.blue=1.0f;
        RGBA_2.red=1.0f;
        RGBA_2.green=0.0f;
        RGBA_2.blue=0.0f;
        LinesPanel= new CLinesPanel[panelnum];
        LinesPanel[0].Create("   Движения", RGBA_1, 7, 30, 1);
        LinesPanel[0].CreateLine("Бежать в точку (0)(0)", RGBA_1, RGBA_2, 0);
        LinesPanel[0].CreateLine("Бежать в точку (1)(0)", RGBA_1, RGBA_2, 1);
        LinesPanel[0].CreateLine("Бежать в точку (2)(0)", RGBA_1, RGBA_2, 2);
        LinesPanel[0].CreateLine("Бежать в точку (4)(0)", RGBA_1, RGBA_2, 3);
        LinesPanel[0].CreateLine("Бежать в точку (5)(0)", RGBA_1, RGBA_2, 4);
        LinesPanel[0].CreateLine("Бежать в точку (10)(0)", RGBA_1, RGBA_2, 5);
        LinesPanel[0].CreateLine("Бежать в произвольную (.)", RGBA_1, RGBA_2, 6);
}
//===========================================================================
void Event(int eventcode) {
        switch (eventcode) {
                case 0:
                        Characters[0].RunTo(0,0);
                        break;
                case 1:
                        Characters[0].RunTo(1,0);
                        break;
                case 2:
                        Characters[0].RunTo(2,0);
                        break;
                case 3:
                        Characters[0].RunTo(4,0);
                        break;
                case 4:
                        Characters[0].RunTo(5,0);
                        break;
                case 5:
                        Characters[0].RunTo(10,0);
                        break;
                case 6:
                        Characters[0].RunTo(random(20)-10,random(20)-10);
                        break;
        }
}
//===========================================================================
void LeftClick(int x, int y) {
        for(int i=0;i<panelnum;i++) {
                for(int j=0;j<LinesPanel[i].max;j++) {
                        if(CursorIn(LinesPanel[i].x,LinesPanel[i].y+j+1,
                                        LinesPanel[i].x+10,LinesPanel[i].y+j+2)) {
                                Event(LinesPanel[i].Lines[j].eventcode);
                                return;
                        }
                }
        }
}
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================



