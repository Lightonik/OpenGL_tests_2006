#define MAX_CHARS 256
UINT FontListID = 0;
HFONT hOldFont;
int FONT_HEIGHT	= 32;
int FONT_EXTRUDE = 0.1f;
GLYPHMETRICSFLOAT g_GlyphInfo[MAX_CHARS];

//---------------------------------------------------------------------------
UINT CreateOpenGL3DFont(LPSTR strFontName, float extrude)	
{
	UINT	fontListID = 0;
	HFONT	hFont;
	fontListID = glGenLists(MAX_CHARS);
	hFont = CreateFont(             	0,
						0,
						0,
						0,
						FW_BOLD,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						strFontName);
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	wglUseFontOutlines(	hDC,
                                0,
                                MAX_CHARS - 1,
                                fontListID,
                                0,
                                0.4f,
                                WGL_FONT_POLYGONS,
                                g_GlyphInfo);
return fontListID;
}
//---------------------------------------------------------------------------
void PositionText( int x, int y )
{
	glPushAttrib( GL_TRANSFORM_BIT | GL_VIEWPORT_BIT );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	y = 768 - FONT_HEIGHT - y;
	glViewport( x - 1, y - 1, 0, 0 );
	glRasterPos4f( 0, 0, 0, 1 );
	glPopMatrix();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glPopAttrib();
}
//---------------------------------------------------------------------------
void glDraw3DText(const char *strString, ...)
{
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
	glTranslatef(0.0f - (unitLength / 2), 0.0f, 0.0f);
	glPushAttrib(GL_LIST_BIT);
	glListBase(FontListID);
	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);
	glPopAttrib();
}
//---------------------------------------------------------------------------
void DestroyFont()
{
	glDeleteLists(FontListID, MAX_CHARS);
	SelectObject(hDC, hOldFont);
}
//---------------------------------------------------------------------------
