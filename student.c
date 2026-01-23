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
#include <ctype.h>

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

void calculateResult(struct Student *s)
{
    s->total = 0;

    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];

    s->avg = (float)s->total / SUBJECTS;

    if (s->avg >= 90)
        s->grade = 'A';
    else if (s->avg >= 80)
        s->grade = 'B';
    else if (s->avg >= 70)
        s->grade = 'C';
    else if (s->avg >= 60)
        s->grade = 'D';
    else if (s->avg >= 50)
        s->grade = 'E';
    else
        s->grade = 'F';
}
void sortByRoll(struct Student *stu, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < count; j++)
        {
            if (stu[j].roll < stu[min].roll)
                min = j;
        }
        if (min != i)
        {
            struct Student temp = stu[i];
            stu[i] = stu[min];
            stu[min] = temp;
        }
    }
}
void sortByMarks(struct Student *stu, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < count; j++)
        {
            if (stu[j].total > stu[max].total)
                max = j;
        }
        if (max != i)
        {
            struct Student temp = stu[i];
            stu[i] = stu[max];
            stu[max] = temp;
        }
    }
}

void sortByName(struct Student *stu, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(stu[j].name, stu[min].name) < 0)
                min = j;
        }
        if (min != i)
        {
            struct Student temp = stu[i];
            stu[i] = stu[min];
            stu[min] = temp;
        }
    }
}

void normalizeName(char *name)
{
    if (name[0] > 'a' && name[0] < 'z')
        name[0] = toupper(name[0]);

    for (int i = 1; name[i] != '\0'; i++)
        name[0] = tolower(name[i]);
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
    normalizeName(stu[i].name);

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
    calculateResult(&stu[i]);

    (*count)++;
    return stu; // Return the pointer back to main
}

void viewStudent(struct Student *stu, int count)
{
    printf("\n        ----------STUDENT DETAILS----------\n");
    printf("Roll\tName\tMaths\tPhy\tChem\tTotal\tAvgerage\tGrade\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d\t", stu[i].roll);
        printf("%s\t", stu[i].name);
        for (int j = 0; j < 3; j++)
            printf("%d\t", stu[i].marks[j]);
        printf("%d\t", stu[i].total);
        printf("%.2f\t\t", stu[i].avg);
        printf("%c\t", stu[i].grade);

        printf("\n");
    }
}