//==== �������� ���� ========================================================
void StartLog () {
        FILE *log = fopen ("log.txt","w");
        fputs(DateToStr(Date()).c_str(),log);
        fputs(" ",log);
        fputs(TimeToStr(Time()).c_str(),log);
        fputs(" ������ ����\n",log);
        fclose(log);
}
//==== ���������� ������ � ��� ==============================================
void AddToLog (AnsiString str) {
        FILE *log = fopen ("log.txt","a");
        fputs(DateToStr(Date()).c_str(),log);
        fputs(" ",log);
        fputs(TimeToStr(Time()).c_str(),log);
        fputs(" ",log);
        fputs(str.c_str(),log);
        fputs("\n",log);
        fclose(log);
}
//===========================================================================
