//
//  main.c
//  binaryFile
//
//  Created by  👻 on 8/04/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)
//==================================================
//============Structure of the student==============
//==================================================
struct Student {
    char std_Id[10];
    char name[50];
    char email_Id[50];
    char course_Id[10];
    char grade[50];
};

struct Student obj_S;//------------->object of struct
long int size = sizeof(obj_S);//---->length of struct


FILE *PTR_read, *PTR_writing;//------>file pointers for reading and writing
//==================================================
//============Add Record of the student=============
//==================================================
void createBinary(void)
{
    fseek(PTR_read, 0, SEEK_END);
    char moreStd = 'y';

    while (moreStd == 'y') {

        printf("\nEnter Student ID   : ");
        scanf("%s", obj_S.std_Id);

        printf("\nEnter Student Name : ");
        scanf("%s", obj_S.name);

        printf("\nEnter Email ID     : ");
        scanf("%s", obj_S.email_Id);

        printf("\nEnter Course ID    : ");
        scanf("%s", obj_S.course_Id);

        printf("\nEnter Std Grade    : ");
        scanf("%s", obj_S.grade);

        fwrite(&obj_S, size, 1, PTR_read);

        printf("\nWant to add another record (Y/N) : ");
        fflush(stdin);
        scanf("%c", &moreStd);
    }
}
//==================================================
//=========Delete Record of the student=============
//==================================================
void deleteRecord(void)
{
    char dummyName[50];
    printf("\nEnter student name to delete : ");
    scanf("%s", dummyName);
    PTR_writing = fopen("temp.txt", "wb");//--> taking the help of temporary file
                                           //just like we do when we swap numbers
    rewind(PTR_read);
    while (fread(&obj_S, size, 1, PTR_read) == 1)//---> deleting after matching and saving in temp file
    {
        if (strcmp(obj_S.name, dummyName) != 0)
            fwrite(&obj_S, size, 1, PTR_writing);
    }
    fclose(PTR_read);
    fclose(PTR_writing);
    remove("data.txt");
    rename("temp.txt", "data.txt");
    PTR_read = fopen("data.txt", "rb+");
    printf("\nDeletion Successfull\n");
}

//==================================================
//=========Display Record of the student============
//==================================================
void displayrecord(void)
{
    rewind(PTR_read);
    //----> rewind sets the pointer to start of the file

    printf("\nID\t\tName\t\tEmail ID\t\tCourse ID\tGrade\n", obj_S.std_Id, obj_S.name, obj_S.email_Id, obj_S.course_Id, obj_S.grade);


    while (fread(&obj_S, size, 1, PTR_read) == 1)
        printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%s",
            obj_S.std_Id, obj_S.name, obj_S.email_Id, obj_S.course_Id, obj_S.grade);
    printf("\n\n\n\t");
}

// Function to modify the record
void modifyrecord(void)
{
    char dummyName[50];
    printf("\nEnter student name to modify: ");
    scanf("%s", dummyName);
    rewind(PTR_read);
    // While File is open
    while (fread(&obj_S, size, 1, PTR_read) == 1) {
        if (strcmp(obj_S.name, dummyName) == 0) {
            printf("\nEnter new Student ID   : ");
            scanf("%s", obj_S.std_Id);

            printf("\nEnter new Student Name : ");
            scanf("%s", obj_S.name);

            printf("\nEnter new Email ID     : ");
            scanf("%s", obj_S.email_Id);

            printf("\nEnter new Course ID    : ");
            scanf("%s", obj_S.course_Id);

            printf("\nEnter new Std Grade    : ");
            scanf("%s", obj_S.grade);

            fseek(PTR_read, -size, SEEK_CUR);
            fwrite(&obj_S, size, 1, PTR_read);
            break;
        }
    }
    printf("Updation Successfull");
}

void seekSpecific(void){
    char dummyName[50];
    printf("\nEnter student name to search : ");
    scanf("%s", dummyName);
    rewind(PTR_read);
    // While File is open
    while (fread(&obj_S, size, 1, PTR_read) == 1) {
        if (strcmp(obj_S.name, dummyName) == 0) {
            printf("\nID\t\tName\t\tEmail ID\t\tCourse ID\tGrade\n", obj_S.std_Id, obj_S.name, obj_S.email_Id, obj_S.course_Id, obj_S.grade);
                printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%s",
                    obj_S.std_Id, obj_S.name, obj_S.email_Id, obj_S.course_Id, obj_S.grade);
            printf("\n\n\n\t");
            break;
        }
    }
}
void Menu(void)
{
    printf("\n\t\t\t\tM A I N   M E N U");
    printf("\n\t\t1. Create the Binary file");
    printf("\n\t\t2. Display the contents of the file");
    printf("\n\t\t3. Seek a specific record");
    printf("\n\t\t4. Update the contents of the record");
    printf("\n\t\t5. Delete a record for a specific name");
    printf("\n\t\t6. Exit");
    printf("\n\n\t\t\tPlease ENTER your choice...\n");
}

// Driver code
int main()
{

    int choice;
    // opening the file
    PTR_read = fopen("data.txt", "rb+");

    // showing error if file is
    // unable to open.
    if (PTR_read == NULL) {
        PTR_read = fopen("data.txt", "wb+");
        if (PTR_read == NULL) {
            printf("\nCannot open file...");
            exit(1);
        }
    }

    while (1) {
        Menu();

        fflush(stdin);
        scanf("%d", &choice);

        // Switch Case
        switch (choice) {
        case 1:

            // Add the records
            createBinary();
            break;

        case 2:
            // Display the records
            displayrecord();
            break;

        case 3:
                seekSpecific();
            break;

        case 4:
            //Modify the records
            modifyrecord();
            break;
        case 5:
            // Delete the records
            deleteRecord();
            break;

        case 6:
            exit(0);
            break;

        default:
            printf("\nINVALID CHOICE...\n");
        }
    }
    fclose(PTR_read);
    return 0;
}
