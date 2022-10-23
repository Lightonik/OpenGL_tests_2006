//===== ����� �������� �������� ����� ������� ===============================
BYTE bits[1024*1024][4];
//===== ����� �������� ======================================================
/*class CTexture {
        public:
                CTexture();
                ~CTexture();
//                bool Load(AnsiString filename);
                void Select();
                int ReturnId();
        private:
                int id;
};
//===== id=-1 - �������� �� ���������� ======================================
CTexture::CTexture() {
        id=-1;
}   */
//===== ������� �������� ====================================================
void DelTexture(int id) {
        glDeleteTextures(1, (GLuint*)&id);
        id=-1;
}
//===== ������ �������� �� ����� ============================================
bool LoadTexture(AnsiString filename) {
        int id;
        int w,h;
        Graphics::TBitmap *bitmap;
        bitmap = new Graphics::TBitmap;
        if(filename==NULL)
                return false;

        AnsiString text;
        text="�������� �������� ";
        text+=filename;
        text+="...";
        AddToLog(text);

        bitmap->LoadFromFile (filename);
        w = bitmap->Width;
        h = bitmap->Height;
        for(int i = 0; i < w; i++) {
                for(int j = 0; j < h; j++) {
                        bits[j+w*i][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[j][i]);
                        bits[j+w*i][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[j][i]);
                        bits[j+w*i][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[j][i]);
                        bits[j+w*i][3]= (GLbyte)255;
                }
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glGenTextures(1, (GLuint*)&id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, bits);

        AddToLog("...�������");

        return true;
}
//===== �������� �������� ��� ��������� =====================================
/*void SelectTex(int id) {
        if(id==-1)
                return;
        glBindTexture(GL_TEXTURE_2D, id);
}  */
/*
//===== ����� ����� �������� ===============================================
int CTexture::ReturnId() {
        return id;
} */
//===========================================================================
