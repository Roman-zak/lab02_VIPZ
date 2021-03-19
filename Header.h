#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define MIN_RATE 4.5
#define MARKS_NUMBER 4.0

typedef struct student_data
{
    char sSurname[20];
    char sName[15];
    int anDate[3];
    int anMark[4];
}sStdData;

typedef struct students_list
{
    sStdData Data;
    struct students_list* psNext;
}sStd;


extern int  g_counter;
extern sStd* psHead;
extern sStd* psTail;
extern sStd g_sTemp;

FILE* OpenFile();
void FillListFromBinFile(FILE* fBinInputFile);
void FreeList(sStd* psHead);
void PrintList(sStd* psHead);
sStd* InputNewStudent();
sStd* GetNextStudentFromFile(FILE* fBinInputFile);
sStd* AddStudentToTail(sStd* psElement);
int IncludeStudentToList(sStd** ppsHead, sStd* add_psElement);
sStd* DeleteStudents(sStd* psHead);
void DeleteLastpsElement(sStd* psHead);
int CheckForNewHead(sStd** psHead, sStd* NewpsElement);


#endif