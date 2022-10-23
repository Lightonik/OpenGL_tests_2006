class CFont {
        public:
                ~CFont();
                void Create();
                void Print(const char *strString, ...);
                void InterPri(float x, float y, Color RGBA, const char *strString, ...);
        private:
                char *text;
                int base;
                GLYPHMETRICSFLOAT g_GlyphInfo[256];
                HFONT hOldFont;
};
//---------------------------------------------------------------------------
CFont::~CFont() {
        glDeleteLists(base, 256);
        SelectObject(hDC, hOldFont);
}
//---------------------------------------------------------------------------
void CFont::Create() {
	HFONT	hFont;
	base = glGenLists(256);
	hFont = CreateFont(             	0,
						0,
						0,
						0,
						FW_NORMAL,
						false,
						false,
						false,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						"CyrillicGoth");
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	wglUseFontOutlines(	hDC,
                                0,
                                256,
                                base,
                                0,
                                0.1f,
                                WGL_FONT_POLYGONS,
                                g_GlyphInfo);
}
//---------------------------------------------------------------------------
void CFont::Print(const char *strString, ...) {
	char strText[256];
	va_list argumentPtr;
	float unitLength=0.0f;
	if (strString == NULL)
                return;
	va_start(argumentPtr, strString);
	vsprintf(strText, strString, argumentPtr);
	va_end(argumentPtr);
	for (int i=0; i < (int)strlen(strText); i++) {
		unitLength += g_GlyphInfo[strText[i]].gmfCellIncX;
	}
//	glTranslatef(0.0f - (unitLength / 2), 0.0f, 0.0f);
	glPushAttrib(GL_LIST_BIT);
	glListBase(base);
        glDisable (GL_LIGHTING);
	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);
        glEnable (GL_LIGHTING);
	glPopAttrib();
}
//---------------------------------------------------------------------------
void CFont::InterPri(float x, float y, Color RGBA, const char *strString, ...) {
	char strText[256];
	va_list argumentPtr;
//	float unitLength=0.0f;
	if (strString == NULL)
                return;
	va_start(argumentPtr, strString);
	vsprintf(strText, strString, argumentPtr);
	va_end(argumentPtr);
/*	for (int i=0; i < (int)strlen(strText); i++) {
		unitLength += g_GlyphInfo[strText[i]].gmfCellIncX;
	}  */
        OrthoMode(0,0,40,40);
        glTranslatef(x,y,0);
        glRotatef(180,1,0,0);
//	glTranslatef(0.0f - (unitLength / 2), 0.0f, 0.0f);
	glPushAttrib(GL_LIST_BIT);
	glListBase(base);
        glDisable (GL_LIGHTING);
        glColor4f(RGBA.red ,RGBA.green, RGBA.blue, RGBA.alfa);
	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);
        glColor4f(1.0f,1.0f,1.0f,1.0f);
        glEnable (GL_LIGHTING);
	glPopAttrib();
        PerspectiveMode();
}
//---------------------------------------------------------------------------
CFont Font1;

