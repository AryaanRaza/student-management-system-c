/*
------------------------------------------------------------
Program : Student Progress Report System
Language: C
Concepts Used:
 - Structures
 - Dynamic Memory Allocation (malloc / realloc / free)
 - Menu-driven programming
 - Searching and deletion in arrays
 - Modular programming

Author  : Md Aryaan Raza
------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "input.h"

#define SUBJECTS 3





int searchByRoll(struct Student *stu, int count, int roll)
{
    for (int i = 0; i < count; i++)
    {
        if (stu[i].roll == roll)
            return i;
    }
    return -1;
}

void searchByName(struct Student *stu, int count, char *name)
{
    int found = 0;
    for (int i = 0; i < count; i++)
    {
        // strcmp returns 0 if strings match
        if (strcasecmp(stu[i].name, name) == 0)
        {
            printf("\nStudent Found: Roll %d, Grade %c", stu[i].roll, stu[i].grade);
            found = 1; // Mark as found
            break;     // STOP the loop immediately
        }
    }
    if (!found)
        printf("\nName not Present");
}

// takes n as pointer to update the actual n after deletion
void deleteRoll(struct Student *stu, int *count, int roll)
{
    int position = searchByRoll(stu, *count, roll);
    if (position == -1)
        printf("\nRoll number not present");

    else
    {
        for (int i = position; i < (*count) - 1; i++)
        {
            stu[i] = stu[i + 1];
        }
        (*count)--;
        printf("\nRecord deleted successfully.");
    }
}

void inputMarks(struct Student *stu, int i)
{
    for (int j = 0; j < SUBJECTS; j++)
    {
        char prompt[50];
        sprintf(prompt, "        Subject %d (0-100): ", j + 1);
        stu[i].marks[j] = safeInputInt(prompt, 0, 100);

        stu[i].total += stu[i].marks[j];
    }
}

void assigngrade(struct Student *stu, int i)
{
    /* Assign grade */
    if (stu[i].avg >= 90 && stu[i].avg <= 100)
        stu[i].grade = 'A';

    else if (stu[i].avg >= 80 && stu[i].avg < 90)
        stu[i].grade = 'B';

    else if (stu[i].avg >= 70 && stu[i].avg < 80)
        stu[i].grade = 'C';

    else if (stu[i].avg >= 60 && stu[i].avg < 70)
        stu[i].grade = 'D';

    else if (stu[i].avg >= 50 && stu[i].avg < 60)
        stu[i].grade = 'E';

    else
        stu[i].grade = 'F';
}

struct Student *resizeStudents(struct Student *stu, int *capacity)
{
    *capacity = (*capacity) * 2;
    struct Student *temp = (struct Student *)realloc(stu, (*capacity) * sizeof(struct Student));

    if (temp == NULL)
    {
        printf("\nMemory allocation failed");
        return stu; // Return the original pointer if failed
    }
    return temp; // Return the new address
}

struct Student *addStudent(struct Student *stu, int *capacity, int *count)
{

    if (*count == *capacity)
    {
        stu = resizeStudents(stu, capacity);
    }

    printf("\nEnter the details  :\n");
    int i = *count;
    stu[i].total = 0;
    printf("        Name : ");
    fgets(stu[i].name, sizeof(stu[i].name), stdin);
    stu[i].name[strcspn(stu[i].name, "\n")] = '\0'; // remove newline

    /* Read unique roll number */
    while (1)
    {
        stu[i].roll = safeInputInt("        Roll : ", 1, 500);
        // Explicitly check for -1 to ensure index 0 is recognized as "found"
        if (searchByRoll(stu, *count, stu[i].roll) != -1) // Pass value, not address
            printf("Roll already present , enter a unique roll number.\n");
        else
            break;
    }

    /* Read marks */
    printf("        Marks for--\n");
    inputMarks(stu, i);

    /* Calculate average */
    stu[i].avg = (float)stu[i].total / SUBJECTS;
    assigngrade(stu, i);

    (*count)++;
    return stu; // Return the pointer back to main
}

void viewStudent(struct Student *stu, int count)
{
    printf("\n        ----------STUDENT DETAILS----------\n");
    printf("Name\tRoll\tMaths\tPhy\tChem\tTotal\tAvgerage\tGrade\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s\t", stu[i].name);
        printf("%d\t", stu[i].roll);
        for (int j = 0; j < 3; j++)
            printf("%d\t", stu[i].marks[j]);
        printf("%d\t", stu[i].total);
        printf("%.2f\t\t", stu[i].avg);
        printf("%c\t", stu[i].grade);

        printf("\n");
    }
}