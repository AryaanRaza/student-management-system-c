#ifndef FILE_H
#define FILE_H

#include "student.h"

struct Student *loadStudentsFromFile(
    const char *filename,
    struct Student *stu,
    int *count,
    int *capacity);

void saveStudentsToFile(
    const char *filename,
    struct Student *stu,
    int count);

#endif
