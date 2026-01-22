#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "file.h"

void saveStudentsToFile(const char *filename, struct Student *stu, int count)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("\nError saving data to file.");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d|%s", stu[i].roll, stu[i].name);
        for (int j = 0; j < SUBJECTS; j++)
            fprintf(fp, "|%d", stu[i].marks[j]);

        fprintf(fp, "\n");
    }
    fclose(fp);
}

struct Student *loadStudentsFromFile(
    const char *filename,
    struct Student *stu,
    int *count,
    int *capacity)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return stu;

    while (1)
    {
        struct Student temp;
        temp.total = 0;

        if (fscanf(fp, "%d|%34[^|]", &temp.roll, temp.name) != 2)
            break;

        for (int i = 0; i < SUBJECTS; i++)
        {
            if (fscanf(fp, "|%d", &temp.marks[i]) != 1)
                goto done;
        }

        fscanf(fp, "\n");

        calculateResult(&temp);

        if (*count == *capacity)
            stu = resizeStudents(stu, capacity);

        stu[*count] = temp;
        (*count)++;
    }

done:
    fclose(fp);
    return stu;
}
