#ifndef STUDENT_H
#define STUDENT_H


struct Student
{
    char name[35];
    int roll;
    int marks[3];
    int total;
    float avg;
    char grade;
};

int searchByRoll(struct Student *stu, int count, int roll);
void searchByName(struct Student *stu, int count, char *name);
void deleteRoll(struct Student *stu, int *count, int roll);
void inputMarks(struct Student *stu, int i);
void assigngrade(struct Student *stu, int i);
struct Student *resizeStudents(struct Student *stu, int *capacity);
struct Student *addStudent(struct Student *stu, int *capacity, int *count);
void viewStudent(struct Student *stu, int count);

#endif
