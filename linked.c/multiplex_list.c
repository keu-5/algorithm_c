//成績表を操作するコード
#include <stdio.h>
#include <stdlib.h>

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
//出席番号と科目番号と成績を追加
void add(int x, int y, int a) {
    if (x > MAX_STUDENTS || y > MAX_SUBJECTS) {
        printf("番号が範囲外です。\n");
        return;
    }
    if (x < 0 || y < 0) {
        printf("番号が負数です。\n");
        return;
    }
    Grades *p;

    if ((p = (Grades *) malloc(sizeof(Grades))) == NULL) {
        printf("メモリ不足です。\n");
        return;
    }

    p->glink = students[x].glink;
    students[x].glink = p;

    p->klink = subjects[y].klink;
    subjects[y].klink = p;

    p->students = &students[x];
    p->subjects = &subjects[y];
    p->grade = a;

    printf("正常に追加されました。\n");
}

int get_grades(int x, int y) {
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

//BUG: 一文字にしないと無限ループに入ってしまうので注意。修正はめんどうくさいからしない
int main(void) {
    int students_num, subjects_num;
    int grade;
    int a;
    int numscanned;

    initialize();
    while (1) {
        printf("1. 成績を追加する\n");
        printf("2. 個人成績を得る\n");
        printf("3. 成績表を初期化する\n");
        printf("4. 選択科目の成績表を出力する\n");
        printf("5. 終了\n");
        printf("どうしますか?:");
        numscanned = scanf("%d", &a);
        
        switch (a) {
            case 1:
                printf("成績を追加する:\n ");
                printf("出席番号, 科目コード, 成績:");
                scanf("%d, %d, %d", &students_num, &subjects_num, &grade);
                add(students_num, subjects_num, grade);
                break;
            case 2:
                printf("個人成績を得る:\n");
                printf("出席番号, 科目:");
                scanf("%d, %d", &students_num, &subjects_num);
                grade = get_grades(students_num, subjects_num);
                printf("出席番号%d番、科目コード%dの成績は%dです。\n", students_num, subjects_num, grade);
                break;
            case 3:
                initialize();
                printf("成績表を初期化しました。");
                break;
            case 4:
                printf("選択科目の成績表を出力する:\n");
                printf("科目コード:");
                scanf("%d", &subjects_num);
                print_grades(subjects_num);
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("不正な入力です\n");
                exit(0);
                break;
        }
        puts("--------------------------------------------------------");
    }
    return 0;
}