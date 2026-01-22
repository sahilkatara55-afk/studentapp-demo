#include <stdio.h>
#include <string.h>

struct Student
{
    int rno;
    char name[50];
    int std;
    int marks;
    int active;
};

#define SIZE 1000

struct Student srecords[SIZE];
int total = 0, rnos = 1;

void printStudent(struct Student s)
{
    printf("\nRno: %d", s.rno);
    printf("\nName: %s", s.name);
    printf("Std: %d", s.std);
    printf("\nMarks: %d", s.marks);
    printf("\n--------------------");
}

void addStudent()
{
    struct Student s;

    if (total == SIZE)
    {
        printf("\nStudent list is full");
        return;
    }

    s.rno = rnos;

    printf("\nEnter Name: ");
    getchar();                     // clear buffer
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Std: ");
    scanf("%d", &s.std);

    printf("Enter Marks: ");
    scanf("%d", &s.marks);

    s.active = 1;
    srecords[total] = s;

    total++;
    rnos++;

    printf("\nStudent record successfully inserted...\n");
}

void displayStudents()
{
    int i;
    if (total == 0)
    {
        printf("\nStudent list is empty\n");
        return;
    }

    for (i = 0; i < total; i++)
    {
        if (srecords[i].active == 1)
        {
            printStudent(srecords[i]);
        }
    }
}

void deleteStudentbyId()
{
    int i, rno, flag = 1;

    printf("\nEnter Rno which you want to delete: ");
    scanf("%d", &rno);

    for (i = 0; i < total; i++)
    {
        if (srecords[i].rno == rno && srecords[i].active == 1)
        {
            srecords[i].active = 0;
            printf("\nStudent Rno %d deleted successfully\n", rno);
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        printf("\nStudent Rno %d not found\n", rno);
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Delete Student");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            deleteStudentbyId();
            break;
        case 4:
            return 0;
        default:
            printf("\nInvalid choice");
        }
    }
}