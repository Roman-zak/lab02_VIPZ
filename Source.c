#include"Header.h"
int  g_counter = 0;
sStd* psHead = NULL;
sStd* psTail = NULL;
sStd g_sTemp;

// Create one-linked list of students, readed from .bin file
void FillListFromBinFile(FILE* fBinInputFile) {
    sStd* psElement = NULL;

    while (!feof(fBinInputFile)) {
        psElement = GetNextStudentFromFile(fBinInputFile);
        psTail = AddStudentToTail(psElement); 
    }

    fclose(fBinInputFile);
}

//--------------------------------------------------------------------------------

// Open .bin file with students list, returns pointer to opened file
FILE* OpenFile() {
    FILE* fBinInputFile = NULL;
    fBinInputFile = fopen("C:\\Users\\Roman\\out.bin", "rb");
    if (!fBinInputFile) {
        printf("Ooops!");
    }

    return fBinInputFile;
}

//--------------------------------------------------------------------------------

//Free dinamic memorry created for list elements
void FreeList(sStd* psHead) {
    sStd* psElement = psHead;

    while (psElement != NULL) {
        psHead = psHead->psNext;
        free(psElement);
        psElement = psHead;
    }
}

//--------------------------------------------------------------------------------

// Print list of students starting from psHead pointer
void PrintList(sStd* psHead) {
    sStd* psElement = NULL;
    puts("");
    psElement = psHead;

    while (psElement != NULL) {

        printf("%-15s ", psElement->Data.sSurname);
        printf("%-15s ", psElement->Data.sName);
        printf("%2d.%2d.%2d ", psElement->Data.anDate[0], psElement->Data.anDate[1], psElement->Data.anDate[2]);
        
        for (int i = 0; i < MARKS_NUMBER; i++) {
            printf("%d ", psElement->Data.anMark[i]);
        }
       
        puts("");
        psElement = psElement->psNext;
    }
    puts("");
}

//--------------------------------------------------------------------------------

// Reads new student data inputed by user from keybord, returns pointer on new student structure
sStd* InputNewStudent() {
    sStd* add_psElement = (sStd*)malloc(sizeof(sStd));
    add_psElement->psNext = NULL;

    scanf("%s", add_psElement->Data.sSurname);
    scanf("%s", add_psElement->Data.sName);
    scanf("%d.%d.%d", &add_psElement->Data.anDate[0],//
        &add_psElement->Data.anDate[1], &add_psElement->Data.anDate[2]);
    
    for (int i = 0; i < MARKS_NUMBER; i++) {
        scanf("%d", &add_psElement->Data.anMark[i]);
    }
    
    return add_psElement;
}

//--------------------------------------------------------------------------------

//Read one student data from .bin file returns readed element structure pointer
sStd* GetNextStudentFromFile(FILE* fBinInputFile) {
    sStd* psElement = NULL;
    int nDate = 0, nMark = 0;
    psElement = (sStd*)malloc(sizeof(sStd));

    fread(psElement->Data.sSurname, sizeof(g_sTemp.Data.sSurname), 1, fBinInputFile);
    fread(psElement->Data.sName, sizeof(g_sTemp.Data.sName), 1, fBinInputFile);
    fread(&nDate, sizeof(int), 1, fBinInputFile);
    psElement->Data.anDate[0] = nDate;
    fread(&nDate, sizeof(int), 1, fBinInputFile);
    psElement->Data.anDate[1] = nDate;
    fread(&nDate, sizeof(int), 1, fBinInputFile);
    psElement->Data.anDate[2] = nDate;
    for (int i = 0; i < MARKS_NUMBER; i++) {
        fread(&nMark, sizeof(int), 1, fBinInputFile);
        psElement->Data.anMark[i] = nMark;
    }

    psElement->psNext = NULL;
    return psElement;
}

//--------------------------------------------------------------------------------

// Add student structure to the tail of the list, returns pointer to tail
sStd* AddStudentToTail(sStd* psElement) {
    if (psHead == NULL) {
        psHead = psElement;
        psTail = psElement;
    } else {
        psTail->psNext = psElement;
        psTail = psElement;
    }

    g_counter++;
    return psTail;
}

//--------------------------------------------------------------------------------

// Include new readed from keybord student to the sorted list
int IncludeStudentToList(sStd** ppsHead, sStd* add_psElement) {
    sStd* psElement = NULL;

    if (!CheckForNewHead(&psHead, add_psElement)) { // if new element shouldn't become of head
        sStd* psPrevious = NULL;
        psElement = *ppsHead;
        int  j = 2; //comparing years

        while (psElement->Data.anDate[j] < add_psElement->Data.anDate[j]) { //determing where to insert new element be comparing dates
            if (psElement->psNext == NULL) {
                psElement->psNext = add_psElement;
                return 1;
            } else {
                psPrevious = psElement;
                psElement = psElement->psNext;
            }
            if (psElement->Data.anDate[j] == add_psElement->Data.anDate[j]) {
                j--; // comparind months
                while (psElement->Data.anDate[j] < add_psElement->Data.anDate[j]) {
                    if (psElement->psNext == NULL) {
                        psElement->psNext = add_psElement;
                        return 1;
                    }  else {
                        psPrevious = psElement;
                        psElement = psElement->psNext;
                    }
                }
                if (psElement->Data.anDate[j] == add_psElement->Data.anDate[j]) {
                    j--;//comparing days
                    while (psElement->Data.anDate[j] < add_psElement->Data.anDate[j]) {
                        if (psElement->psNext == NULL) {
                            psElement->psNext = add_psElement;
                            return 1;
                        }  else {
                            psPrevious = psElement;
                            psElement = psElement->psNext;
                        }
                    }
                }
            }
        }

        add_psElement->psNext = psElement;
        psPrevious->psNext = add_psElement;
    }
}

//--------------------------------------------------------------------------------

//Deletes students with marks lower than MIN_RATE from list
sStd* DeleteStudents(sStd* psHead) {
    sStd* psElement = NULL;
    double nRate = 0;
    sStd* psPrevious = NULL;
    psElement = psHead;

    while (psElement != NULL) {
        for (int j = 0; j < MARKS_NUMBER; j++) {
            nRate = nRate + (((double)psElement->Data.anMark[j]) / MARKS_NUMBER);
        }
        if (nRate >= MIN_RATE) {
            psPrevious = psElement;
            psElement = psElement->psNext;
        }  else {
            if (psElement == psHead) {
                psHead = psHead->psNext;
                free(psElement);
                psElement = psHead;
            }  else {
                psPrevious->psNext = psElement->psNext;
                free(psElement);
                psElement = psPrevious->psNext;
            }
        }
        nRate = 0;
    }

    puts("List after deleting");
    return psHead;
}

//--------------------------------------------------------------------------------

//Deleates tail element from the list 
void DeleteLastpsElement(sStd* psHead) {
    sStd* psElement = NULL;
    sStd* psNext = NULL;
    psElement = psHead;
    while (psElement->psNext != NULL) {
        psElement = psElement->psNext;
        psNext = psElement->psNext;
        if (psNext->psNext == NULL) {
            psElement->psNext = NULL;
            free(psNext->psNext);
        }
    }
}

//--------------------------------------------------------------------------------

// Check if included student must become the head of the list, returns 1 if yes, 0 if no
int CheckForNewHead(sStd** psHead, sStd* NewpsElement) {
    if ((*psHead)->Data.anDate[2] > NewpsElement->Data.anDate[2] ||//
        ((*psHead)->Data.anDate[2] == NewpsElement->Data.anDate[2] &&//
         (*psHead)->Data.anDate[1] > NewpsElement->Data.anDate[1]) || //
        ((*psHead)->Data.anDate[2] == NewpsElement->Data.anDate[2] &&//
         (*psHead)->Data.anDate[1] == NewpsElement->Data.anDate[1] &&//
         (*psHead)->Data.anDate[0] > NewpsElement->Data.anDate[0]))
    {
        NewpsElement->psNext = *psHead;
        *psHead = NewpsElement;
        return 1;
    }
    return 0;
}