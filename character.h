//===========================================================================
class CCharacter {
        public:
                void Set(AnsiString inifile);
        private:
                CModel *Models;
                int modNumber;
                Vector coordAbs;
                Vector *coordParts;
};
//===========================================================================
void CCharacter::Set(AnsiString inifile) {
        FILE *ini;
        if((ini = fopen(inifile.c_str(),"r"))==NULL)
                return;

}
//===========================================================================
