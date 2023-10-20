//成績表を操作するコード
#include <stdio.h>

#define MAX_STUDENTS 2000
#define MAX_SUBJECTS 400

typedef struct GRADES {
    struct GRADES *glink;
    struct GRADES *klink;
    struct STUDENTS *students;
    struct SUBJECTS *subjects;
    short grade;
} Grades;

struct STUDENTS {
    struct GRADES *glink;
    char *name;
} students[MAX_STUDENTS];

struct SUBJECTS {
    struct GRADES *klink;
    char *name;
} subjects[MAX_SUBJECTS];

void initialize() {
    int i;

    for (i = 0; i < MAX_STUDENTS; i++) {
        students[i].glink = NULL;
    }
    for (i = 0; i < MAX_SUBJECTS; i++) {
        subjects[i].klink = NULL;
    }
}

void add(int x, int y, short a) {
    Grades *p;

    if ((p = (Grades *) malloc(sizeof(Grades))) == NULL) {
        error("malloc() failed");
    }

    p->glink = students[x].glink;
    students[x].glink = p;

    p->klink = subjects[y].klink;
    subjects[y].klink = p;

    p->students = &students[x];
    p->subjects = &subjects[y];
    p->grade = a;
}

void get_grades(int x, int y) {
    Grades *p;
    for (p = students[x].glink; p!= NULL; p = p->glink) {
        if (p->subjects == &subjects[y]) {
            return p->grade;
        }
    }
    return -1;
}

void print_grades(int x) {
    Grades *p;
    for (p = subjects[x].klink; p!= NULL; p = p->klink) {
        printf("%s %d\n", p->students->name, p->grade);
    }
}

int main(void) {
    return 0;
}
