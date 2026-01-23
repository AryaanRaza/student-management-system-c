#ifndef STUDENT_H
#define STUDENT_H

#define SUBJECTS 3

struct Student
{
    int roll;
    char name[35];
    int marks[3];
    int total;
    float avg;
    char grade;
};


void searchByName(struct Student *stu, int count, char *name);
void inputMarks(struct Student *stu, int i);
void calculateResult(struct Student *s);
struct Student *resizeStudents(struct Student *stu, int *capacity);
struct Student *addStudent(struct Student *stu, int *capacity, int *count);
void viewStudent(struct Student *stu, int count);
int safeInputInt(const char *prompt, int min, int max);
int searchByRoll(struct Student *stu, int count, int roll);
void sortByRoll(struct Student *stu, int count);
void deleteRoll(struct Student *stu, int *count, int roll);

#endif
