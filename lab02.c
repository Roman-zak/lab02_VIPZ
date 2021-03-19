#include"Header.h"

int main()
{
    int nRate = 0;
    sStd* psElement = NULL;
    FILE* fBinInputFile = OpenFile();

    FillListFromBinFile(fBinInputFile);

    DeleteLastpsElement(psHead);

    PrintList(psHead);

    IncludeStudentToList(&psHead, InputNewStudent());

    PrintList(psHead);

    psHead = DeleteStudents(psHead);

    PrintList(psHead);

    FreeList(psHead);

    return 0;
}

// Testing examples: NEW ELEM 11.11.1999 5 4 5 4       NEW ELEM 11.05.2003 5 4 5 4        NEW ELEM 11.11.2010 5 4 5 4
