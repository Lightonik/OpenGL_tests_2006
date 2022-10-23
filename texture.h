//===== Место хранения текстуры перед чтением ===============================
BYTE bits[1024*1024][4];
//===== Класс текстуры ======================================================
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
//===== id=-1 - текстура не загруженна ======================================
CTexture::CTexture() {
        id=-1;
}   */
//===== Удаляем текстуру ====================================================
void DelTexture(int id) {
        glDeleteTextures(1, (GLuint*)&id);
        id=-1;
}
//===== Грузим текстуру из файла ============================================
bool LoadTexture(AnsiString filename) {
        int id;
        int w,h;
        Graphics::TBitmap *bitmap;
        bitmap = new Graphics::TBitmap;
        if(filename==NULL)
                return false;

        AnsiString text;
        text="Загрузка текстуры ";
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

        AddToLog("...успешно");

        return true;
}
//===== Выбираем текстуру для рисования =====================================
/*void SelectTex(int id) {
        if(id==-1)
                return;
        glBindTexture(GL_TEXTURE_2D, id);
}  */
/*
//===== Узнаём номер текстуры ===============================================
int CTexture::ReturnId() {
        return id;
} */
//===========================================================================
