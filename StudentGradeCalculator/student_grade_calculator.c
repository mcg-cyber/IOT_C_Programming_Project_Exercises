#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the grade based on the score
int calculateGrade(int score) {
    if (score >= 90) return 5;
    if (score >= 80) return 4;
    if (score >= 70) return 3;
    if (score >= 60) return 2;
    if (score >= 50) return 1;
    return 0; // Below 50
}

int main() {
    char studentName[50];
    int numSubjects, i;
    float totalScore = 0, averageGrade;

    // File handling variables
    FILE *outputFile;
    
    // Open the file in write mode
    outputFile = fopen("grade_report.txt", "w"); 

    if (outputFile == NULL){
      printf("Error opening the file!\n");
      return 1;
    }

    // Get student's name
    printf("Welcome to the Student Grade Calculator!\n");
    printf("Please enter your name: ");
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = 0; // Remove trailing newline

    // Get the number of subjects
    printf("How many subjects do you want to calculate grades for? ");
    scanf("%d", &numSubjects);
    getchar(); // Consume the newline character

    // Prepare to store subject data dynamically
    char **subjectNames = (char **)malloc(numSubjects * sizeof(char *));
    int *scores = (int *)malloc(numSubjects * sizeof(int));
    int *grades = (int *)malloc(numSubjects * sizeof(int));


    // Get subject details and store in allocated memory
    for (i = 0; i < numSubjects; i++) {
        subjectNames[i] = (char *)malloc(50 * sizeof(char)); // Allocate space for subject name
        printf("Enter subject %d name: ", i + 1);
        fgets(subjectNames[i], 50, stdin);
        subjectNames[i][strcspn(subjectNames[i], "\n")] = 0; // Remove trailing newline

        printf("Enter your score for %s (0-100): ", subjectNames[i]);
        scanf("%d", &scores[i]);
        getchar(); // Consume the newline character after scanf

        grades[i] = calculateGrade(scores[i]);
        totalScore += scores[i];
    }

    // Calculate average grade
    averageGrade = (float)totalScore / numSubjects;

    // Output to console
    printf("------------------------------------------\n");
    printf("Student: %s\n", studentName);
    printf("------------------------------------------\n");
    printf("Subject\t\tScore\tGrade\n");
    printf("------------------------------------------\n");

    // Write to the file
    fprintf(outputFile, "------------------------------------------\n");
    fprintf(outputFile, "Student: %s\n", studentName);
    fprintf(outputFile, "------------------------------------------\n");
    fprintf(outputFile, "Subject\t\tScore\tGrade\n");
    fprintf(outputFile, "------------------------------------------\n");


    for (i = 0; i < numSubjects; i++) {
         printf("%-16s%d%%\t\t%d\n", subjectNames[i], scores[i], grades[i]);
         fprintf(outputFile, "%-16s%d%%\t\t%d\n", subjectNames[i], scores[i], grades[i]);
    }

    printf("Average Grade: %.2f\n", averageGrade);
    printf("------------------------------------------\n");

    fprintf(outputFile,"Average Grade: %.2f\n", averageGrade);
    fprintf(outputFile,"------------------------------------------\n");

    fclose(outputFile);
    
     // Free dynamically allocated memory
    for (i = 0; i < numSubjects; i++) {
        free(subjectNames[i]); // free individual subject name allocations
    }
    free(subjectNames);
    free(scores);
    free(grades);

    return 0;
}