#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "input.h"
#include "file.h"

int main()
{
    int choice;
    struct Student *stu;
    int count = 0;
    int capacity = 3;
    stu = (struct Student *)malloc(capacity * sizeof(struct Student));
    stu = loadStudentsFromFile("students.txt", stu, &count, &capacity);

    if (stu == NULL)
    {
        printf("\nMemory allocation failed");
        exit(1);
    }
    char name[34];
    int roll, res;
    printf("\n      ----------MENU----------\n");
    while (1)
    {
        printf("\n  1 to ADD\n  2 to View\n  3 to Search by name\n  4 to to Search by roll\n  5 to Delete\n  6 for Sorting\n  7 to Exit");
        choice = safeInputInt("\n Your choice : ", 1, 9);

        switch (choice)
        {
        case 1:
            stu = addStudent(stu, &capacity, &count);
            break;

        case 2:
            viewStudent(stu, count);
            break;

        case 3:
            printf("\n Enter the name to search : ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // remove newline
            searchByName(stu, count, name);
            break;

        case 4:
            roll = safeInputInt("\n Enter the roll to search : ", 1, 500);
            res = searchByRoll(stu, count, roll);
            if (res != -1)
                printf("\nStudent Found: Name : %s , Grade : %c", stu[res].name, stu[res].grade);
            else
                printf("\nRoll not present");
            break;

        case 5:
            roll = safeInputInt("\n Enter the roll to delete : ", 1, 500);
            deleteRoll(stu, &count, roll);
            break;

        case 6:
            printf("\n  Sort by:");
            printf("\n    1.Roll\n    2.Name\n    3.Total Marks");
            int opt = safeInputInt("\n  Your choice : ", 1, 3);
            switch (opt)
            {
            case 1:
                sortByRoll(stu, count);
                break;
            case 2:
                sortByName(stu, count);
                break;
            case 3:
                sortByMarks(stu, count);
                break;
            }
            saveStudentsToFile("students.txt", stu, count);
            break;

        case 7:
            saveStudentsToFile("students.txt", stu, count);
            printf("\nData saved. Exiting program.\n");
            free(stu);
            exit(0);
            break;
        }
    }
    return 0;
}