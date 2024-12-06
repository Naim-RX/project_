#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student details
struct Student {
    int id;
    char name[50];
    float marks[5];
    float attendance;
};

void addStudent(struct Student students[], int *count);
void updateStudent(struct Student students[], int count);
void displayStudents(struct Student students[], int count);
void searchStudent(struct Student students[], int count);
void saveRecords(struct Student students[], int count);
void loadRecords(struct Student students[], int *count);

int main() {
    struct Student students[100];
    int count = 0;
    int choice;

    // Load records from file (if any)
    loadRecords(students, &count);

    while (1) {
        // Display menu
        printf("\nStudent Record System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Display All Students\n");
        printf("4. Search Student\n");
        printf("5. Save Records\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                updateStudent(students, count);
                break;
            case 3:
                displayStudents(students, count);
                break;
            case 4:
                searchStudent(students, count);
                break;
            case 5:
                saveRecords(students, count);
                break;
            case 6:
                saveRecords(students, count);
                printf("Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a student
void addStudent(struct Student students[], int *count) {
    struct Student newStudent;

    // Input student details
    printf("\nEnter Student ID: ");
    scanf("%d", &newStudent.id);
    getchar();  // To clear the buffer after entering ID

    printf("Enter Student Name: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strlen(newStudent.name)-1] = '\0';  // Remove newline character

    printf("Enter marks for 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &newStudent.marks[i]);
    }

    printf("Enter attendance percentage: ");
    scanf("%f", &newStudent.attendance);

    // Add student to the array
    students[*count] = newStudent;
    (*count)++;
    printf("Student added successfully!\n");
}

// Function to update student details
void updateStudent(struct Student students[], int count) {
    int id;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    // Search for student by ID
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Updating details for student %d - %s\n", students[i].id, students[i].name);

            printf("Enter new marks for 5 subjects:\n");
            for (int j = 0; j < 5; j++) {
                printf("Subject %d: ", j + 1);
                scanf("%f", &students[i].marks[j]);
            }

            printf("Enter new attendance percentage: ");
            scanf("%f", &students[i].attendance);
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

// Function to display all students
void displayStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    for (int i = 0; i < count; i++) {
        printf("\nStudent ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Marks: ");
        for (int j = 0; j < 5; j++) {
            printf("%.2f ", students[i].marks[j]);
        }
        printf("\nAttendance: %.2f%%\n", students[i].attendance);
    }
}

// Function to search for a student by ID or name
void searchStudent(struct Student students[], int count) {
    int choice;
    printf("\nSearch by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // To clear the buffer

    if (choice == 1) {
        int id;
        printf("Enter Student ID to search: ");
        scanf("%d", &id);

        // Search by ID
        for (int i = 0; i < count; i++) {
            if (students[i].id == id) {
                printf("\nStudent ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Marks: ");
                for (int j = 0; j < 5; j++) {
                    printf("%.2f ", students[i].marks[j]);
                }
                printf("\nAttendance: %.2f%%\n", students[i].attendance);
                return;
            }
        }
        printf("Student with ID %d not found.\n", id);
    } else if (choice == 2) {
        char name[50];
        printf("Enter Student Name to search: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';  // Remove newline character

        // Search by name
        for (int i = 0; i < count; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("\nStudent ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Marks: ");
                for (int j = 0; j < 5; j++) {
                    printf("%.2f ", students[i].marks[j]);
                }
                printf("\nAttendance: %.2f%%\n", students[i].attendance);
                return;
            }
        }
        printf("Student with name %s not found.\n", name);
    } else {
        printf("Invalid choice.\n");
    }
}

// Function to save student records to a text file
void saveRecords(struct Student students[], int count) {
    FILE *file = fopen("student_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save records.\n");
        return;
    }

    // Save each student's details in a readable format
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", students[i].id);
        fprintf(file, "%s\n", students[i].name);
        for (int j = 0; j < 5; j++) {
            fprintf(file, "%.2f ", students[i].marks[j]);
        }
        fprintf(file, "\n%.2f\n", students[i].attendance);
    }

    fclose(file);
    printf("Records saved successfully.\n");
}

// Function to load student records from a text file
void loadRecords(struct Student students[], int *count) {
    FILE *file = fopen("student_records.txt", "r");
    if (file == NULL) {
        printf("No saved records found, starting fresh.\n");
        return;
    }

    fscanf(file, "%d\n", count);

    // Load each student's details
    for (int i = 0; i < *count; i++) {
        fscanf(file, "%d\n", &students[i].id);
        fgets(students[i].name, 50, file);
        students[i].name[strlen(students[i].name)-1] = '\0';
        for (int j = 0; j < 5; j++) {
            fscanf(file, "%f", &students[i].marks[j]);
        }
        fscanf(file, "\n%f\n", &students[i].attendance);
    }
    fclose(file);
    printf("Records loaded successfully.\n");
}
