// Student Directory using pointers and structure

#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[100];
    int roll_number;
    float CGPA;
};

void readStudent(struct Student *s) {
    printf("Enter student name: ");
    scanf("%s", s->name); 
    
    printf("Enter roll number: ");
    scanf("%d", &s->roll_number);
    
    printf("Enter CGPA: ");
    scanf("%f", &s->CGPA);
}

void displayStudent(const struct Student *s) {
    printf("Name: %s\n", s->name);
    printf("Roll Number: %d\n", s->roll_number);
    printf("CGPA: %.2f\n", s->CGPA);
}

void sortStudents(struct Student *students, int n) {
    struct Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].roll_number > students[j + 1].roll_number) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;  
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        readStudent(&students[i]);
    }

    sortStudents(students, n);

    printf("\nStudent records after sorting by roll number:\n");
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        displayStudent(&students[i]);
    }

    free(students);

    return 0;
}

