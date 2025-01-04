#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  int id;
  char name[30];
  char surname[30];
  int birth_year;
  char group[3];
  float note[4]; // Array to store grades for 4 subjects
  float moyenne; // Average grade
  int exist; // Flag to indicate if student is active (1) or inactive (0)
} student;

void add_student();
void search_student_by_id(const char *filename, int searchid);
void modification(const char *f, const char *ftemp);
void extract_and_sort( const char *filename ,char grp[3]);
void logicaldeletion(const char *filename, int target_id);
void Physical_Deletion(const char *filename, const char *Temp_file_name);
void display_students(const char *filename);

int main()
{
    int choice;
    char filename[100] = "Listes_Etudiants.txt"; // Example filename
    char temp_filename[100] = "temp.txt"; // Temporary file for deletions
    int id;
    char group[2];

    do {
        printf("\n\t============================================================\n");
        printf("\t                   Student Management System                 \n");
        printf("\t============================================================\n\n");
        printf("\t1. Add Student\n");
        printf("\t2. Search Student by ID\n");
        printf("\t3. Modify Student Record\n");
        printf("\t4. Extract and Sort by Group\n");
        printf("\t5. Logical Deletion of a Student\n");
        printf("\t6. Physical Deletion of Students\n");
        printf("\t7. Display Students\n");
        printf("\t8. Exit\n");
        printf("\t------------------------------------------------------------\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        printf("\n\t------------------------------------------------------------\n");
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                printf("\tEnter the student ID to search: ");
                scanf("%d", &id);
                search_student_by_id(filename, id);
                break;
            case 3:
                modification("Listes_Etudiants.txt","temp.txt");
                break;
            case 4:
                printf("\tEnter the group to extract and sort (e.g., 1A): ");
                scanf("%s", group);
                extract_and_sort(filename,group);
                break;
            case 5:
                printf("\tEnter the student ID to logically delete: ");
                scanf("%d", &id);
                logicaldeletion(filename, id);
                break;
            case 6:
                Physical_Deletion(filename, temp_filename);
                break;
            case 7:
                printf("\tStudents: \n");
                display_students(filename);
                break;
            case 8:
                printf("\tExiting the system.\n");
                remove(temp_filename);
                break;
            default:
                printf("\tInvalid choice. Please try again.\n");
        }
        printf("\t------------------------------------------------------------\n");
    } while (choice != 8);

    return 0;
}

int unique_id(int id) {
    FILE *f = fopen("Listes_Etudiants.txt", "r");
    if (f == NULL) {
        return 1; // File not found, ID is unique
    }

    int existing_id;
    while (fscanf(f, "%d", &existing_id) == 1) {
        if (existing_id == id) {
            fclose(f);
            return 0; // ID is not unique
        }
        // Skip the rest of the line with `fgets`
        char line[256];
        fgets(line, sizeof(line), f);
    }

    fclose(f);
    return 1; // ID is unique
}

void add_student() {
    char fname[30], name[30], group[3];
    int ID, year, IS = 0, inserted = 0;
    float sfsd, poo, alg, ana, avg;

    printf("Please input the data of the student:\n");
    int is_unique;
    // Input ID
    printf("ID: ");
    do {
       scanf("%d", &ID); // User inputs an ID
       is_unique = unique_id(ID); // Call unique_id only once and store the result
       if (!is_unique) {
            printf("ID already exists. Try again: ");
          }
    } while (!is_unique); // Use the stored result for the loop condition

    printf("Family name: ");
    scanf("%s", fname);

    printf("Name: ");
    scanf("%s", name);

    printf("Year of Birth: ");
    do {
        scanf("%d", &year);
        if (year < 1990 || year > 2020)
            printf("Invalid Input, please try again: ");
    } while (year < 1990 || year > 2020);

    printf("Group (e.g., 1A, 2B): ");
    do {
        scanf("%s", group);
        if (!(group[0] >= '1' && group[0] <= '3' && group[1] >= 'A' && group[1] <= 'C' && group[2] == '\0')) {
            printf("Invalid Group, try again (e.g., 1A, 2C): ");
        }
    } while (!(group[0] >= '1' && group[0] <= '3' && group[1] >= 'A' && group[1] <= 'C' && group[2] == '\0'));

    printf("\nGrades:\n");

    printf("\tSFSD: ");
    do {
        scanf("%f", &sfsd);
        if (sfsd < 0 || sfsd > 20)
            printf("Invalid Input, please try again: ");
    } while (sfsd < 0 || sfsd > 20);

    printf("\tAlgebre Lineare: ");
    do {
        scanf("%f", &alg);
        if (alg < 0 || alg > 20)
            printf("Invalid Input, please try again: ");
    } while (alg < 0 || alg > 20);

    printf("\tAnalyse: ");
    do {
        scanf("%f", &ana);
        if (ana < 0 || ana > 20)
            printf("Invalid Input, please try again: ");
    } while (ana < 0 || ana > 20);

    printf("\tPOO: ");
    do {
        scanf("%f", &poo);
        if (poo < 0 || poo > 20)
            printf("Invalid Input, please try again: ");
    } while (poo < 0 || poo > 20);

    // Calculate average
    avg = (sfsd * 4 + poo * 3 + ana * 2 + alg * 5) / 14.0;

    // Open the original file for reading and create a temp file
    FILE *f = fopen("Listes_Etudiants.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        perror("Error opening file");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    // Variables for reading existing students
    int ID1, year1, IS1;
    float sfsd1, poo1, alg1, ana1, avg1;
    char fname1[30], name1[30], group1[3], line[256];

    // Reorder and insert new student
    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "%d %s %s %d %s %f 4 %f 3 %f 2 %f 5 %f %d",
               &ID1, fname1, name1, &year1, group1, &sfsd1, &poo1, &ana1, &alg1, &avg1, &IS1);

        if (!inserted && strcmp(group, group1) < 0) {
            fprintf(temp, "%d %s %s %d %s %.2f 4 %.2f 3 %.2f 2 %.2f 5 %.2f %d\n",
                    ID, fname, name, year, group, sfsd, poo, ana, alg, avg, IS);
            inserted = 1;
        }

        fprintf(temp, "%s", line);
    }

    // Append at the end if not inserted
    if (!inserted) {
        fprintf(temp, "%d %s %s %d %s %.2f 4 %.2f 3 %.2f 2 %.2f 5 %.2f %d\n",
                ID, fname, name, year, group, sfsd, poo, ana, alg, avg, IS);
    }

    fclose(f);
    fclose(temp);

    // Replace the original file with the temp file
    if (remove("Listes_Etudiants.txt") != 0 || rename("temp.txt", "Listes_Etudiants.txt") != 0) {
        perror("Error replacing file");
        return;
    }

    printf("Student added successfully.\n");
}
void modification(const char *filename, const char *temp_filename)
 {
    char line[256];
    int fid, choice, nb, i;
    char module[20];

    printf("Enter the ID of the student you want to modify: ");
    scanf("%d", &fid);

    // Open the original file for reading
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening the file");
        return;
    }

    // Open a temporary file for writing
    FILE *ftemp = fopen(temp_filename, "w");
    if (!ftemp) {
        perror("Error creating the temporary file");
        fclose(f);
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        int id, ID, year, is_active, is_unique;
        char fname[30], name[30], group[3];
        float sfsd, poo, alg, ana, avg;

        // Parse the student record
        if (sscanf(line, "%d %s %s %d %s %f 4 %f 3 %f 2 %f 5 %f %d",
                   &id, fname, name, &year, group, &sfsd, &poo, &ana, &alg, &avg, &is_active) < 11) {
            fprintf(ftemp, "%s", line); // Copy the line if parsing fails
            continue;
        }

        if (id == fid) {
            printf("\nModification Menu:\n");
            printf("1. Modify ID\n");
            printf("2. Modify Name\n");
            printf("3. Modify Family Name\n");
            printf("4. Modify Year of Birth\n");
            printf("5. Modify Group\n");
            printf("6. Modify Status\n");
            printf("7. Modify Grades (implies recalculating average)\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    do {
                         scanf("%d", &ID);// User inputs an ID
                         if (ID == id) break;
                         is_unique = unique_id(ID);
                               if (!is_unique) {
                                  printf("ID already exists. Try again: ");
                                               }
                        } while (!is_unique );
                        ID = id;
                    break;
                case 2:
                    printf("Enter new Name: ");
                    scanf("%s", name);
                    break;
                case 3:
                    printf("Enter new Family Name: ");
                    scanf("%s", fname);
                    break;
                case 4:
                    printf("Enter new Year of Birth: ");
                    do {
                        scanf("%d", &year);
                        if (year < 1990 || year > 2020)
                            printf("Invalid Input, please try again: ");
                      } while (year < 1990 || year > 2020);

                    break;
                case 5:
                    printf("Enter new Group: ");
                    do {
                        scanf("%s", group);
                        if (!(group[0] >= '1' && group[0] <= '3' && group[1] >= 'A' && group[1] <= 'C' && group[2] == '\0')) {
                            printf("Invalid Group, try again (e.g., 1A, 2C): ");
                        }
                    } while (!(group[0] >= '1' && group[0] <= '3' && group[1] >= 'A' && group[1] <= 'C' && group[2] == '\0'));
                    break;
                case 6:
                    printf("Enter new Status (1 for active, 0 for inactive): ");
                    scanf("%d", &is_active);
                    break;
                case 7:
                    printf("Enter grades for modules:\n");
                    printf("\tSFSD: ");
                    do {
                        scanf("%f", &sfsd);
                        if (sfsd < 0 || sfsd > 20)
                            printf("Invalid Input, please try again: ");
                    } while (sfsd < 0 || sfsd > 20);

                    printf("\tPOO: ");
                    do {
                        scanf("%f", &poo);
                        if (poo < 0 || poo > 20)
                            printf("Invalid Input, please try again: ");
                    } while (poo < 0 || poo > 20);

                    printf("\tAnalyse: ");
                    do {
                        scanf("%f", &ana);
                        if (ana < 0 || ana > 20)
                            printf("Invalid Input, please try again: ");
                    } while (ana < 0 || ana > 20);

                    printf("\tAlgebra: ");
                    do {
                        scanf("%f", &alg);
                        if (alg < 0 || alg > 20)
                            printf("Invalid Input, please try again: ");
                    } while (alg < 0 || alg > 20);

                    avg = (sfsd * 4 + poo * 3 + ana * 2 + alg * 5) / 14.0;
                    break;
                default:
                    printf("Invalid choice.\n");
            }
        }

        // Write the (modified or unmodified) record to the temporary file
        fprintf(ftemp, "%d %s %s %d %s %.2f 4 %.2f 3 %.2f 2 %.2f 5 %.2f %d\n",
                id, fname, name, year, group, sfsd, poo, ana, alg, avg, is_active);
    }

    fclose(f);
    fclose(ftemp);

    // Replace the original file with the temporary file
    if (remove(filename) != 0 || rename(temp_filename, filename) != 0) {
        perror("Error replacing file");
        return;
    }

    printf("Modification completed successfully.\n");
}
void search_student_by_id(const char *filename, int searchid) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Error opening file");
    return;
  }

  student s; // Create a student struct to store read data
  char line[256];

  while (fgets(line, sizeof(line), f) != NULL) {
    if (sscanf(line, "%d %s %s %d %s %f 4 %f 3 %f 2 %f 5 %f %d",
              &s.id, s.name, s.surname, &s.birth_year, s.group,
              &s.note[0], &s.note[1], &s.note[2], &s.note[3], &s.moyenne, &s.exist) == 11) {
      if (s.id == searchid && s.exist == 0 ) {
        printf("\nStudent Found:\n");
        printf("ID: %d\n", s.id);
        printf("Name: %s %s\n", s.name, s.surname);
        printf("Birth Year: %d\n", s.birth_year);
        printf("Group: %s\n", s.group);
        printf("Grades:\n");
        printf("\tSFSD: %.2f\n", s.note[0]);
        printf("\tPOO: %.2f\n", s.note[1]);
        printf("\tAnalyse: %.2f\n", s.note[2]);
        printf("\tAlgebre Lineaire: %.2f\n", s.note[3]);
        printf("Average: %.2f\n", s.moyenne);
        fclose(f);
        return;
      }
    }
  }

  fclose(f);
  printf("\nStudent with ID '%d' not found.\n", searchid);
}

void extract_and_sort(const char *filename, char grp[3]) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Error opening the file");
        return;
    }

    if (!(grp[0] >= '1' && grp[0] <= '3' && grp[1] >= 'A' && grp[1] <= 'C' && grp[2] == '\0')) {
            printf("\tInvalid Group. \n");
            return;
        }

    student students[100]; // Array to store students from the specified group
    int count = 0;         // Count of students in the specified group
    char line[256];        // Buffer for reading lines from the file

    // Read each line of the file
    while (fgets(line, sizeof(line), f)) {
        student s; // Temporary student structure for parsing

        // Parse the student record
        if (sscanf(line, "%d %s %s %d %s %f 4 %f 3 %f 2 %f 5 %f %d",
                   &s.id, s.surname, s.name, &s.birth_year, s.group,
                   &s.note[0], &s.note[1], &s.note[2], &s.note[3], &s.moyenne, &s.exist) == 11) {


            // Check if the student belongs to the specified group and exists
            if (strcmp(s.group, grp) == 0 && s.exist == 0) {
                students[count++] = s; // Add the student to the array
            }
        }
    }

    fclose(f);

    // Sort the students by average grade in descending order
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].moyenne < students[j].moyenne) {
                student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    // Display the sorted students
    printf("\nStudents in group %s sorted by average grade:\n", grp);
    if (count == 0) {
        printf("No students found in group %s.\n", grp);
    } else {
        for (int i = 0; i < count; i++) {
            printf("Name: %s %s | ID: %d | Avg: %.2f\n",
                   students[i].name,
                   students[i].surname,
                   students[i].id,
                   students[i].moyenne);
        }
    }
}

void logicaldeletion(const char *filename, int target_id) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    student buf;
    char line[256];
    int coeff[4];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int read_count = sscanf(line, "%d %s %s %d %s %f %d %f %d %f %d %f %d %f %d",
                                &buf.id, buf.name, buf.surname, &buf.birth_year, buf.group,
                                &buf.note[0], &coeff[0], &buf.note[1], &coeff[1],
                                &buf.note[2], &coeff[2], &buf.note[3], &coeff[3],
                                &buf.moyenne, &buf.exist);

        if (read_count == 15 && buf.id == target_id) {
            buf.exist = 1; // Mark as logically deleted
            found = 1;
        }

        fprintf(temp, "%d %s %s %d %s %.1f %d %.1f %d %.1f %d %.1f %d %.1f %d\n",
                buf.id, buf.name, buf.surname, buf.birth_year, buf.group,
                buf.note[0], coeff[0], buf.note[1], coeff[1],
                buf.note[2], coeff[2], buf.note[3], coeff[3],
                buf.moyenne, buf.exist);
    }

    fclose(file);
    fclose(temp);

    // Replace the original file with the temporary file
    remove(filename);
    rename("tempfile.txt", filename);

    if (found) {
        printf("Student with ID %d has been logically deleted.\n", target_id);
    } else {
        printf("Student with ID %d not found.\n", target_id);
    }
}

void Physical_Deletion( const char *filename, const char *Temp_file_name) {
    // Use fopen_read to open the original file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    // Open the temporary file for writing
    FILE *Temp_File =fopen(Temp_file_name,"w");
    if (file == NULL) {
        return;
    }

    student buf;
    char line[256];
    int line_number = 1, coef1, coef2, coef4, coef3;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse the line using sscanf
       int read_count = sscanf(line, "%d %s %s %d %s %f %d %f %d %f %d %f %d %f %d",
                                &buf.id, buf.name, buf.surname, &buf.birth_year, buf.group,
                                &buf.note[0], &coef1,
                                &buf.note[1], &coef2,
                                &buf.note[2], &coef3,
                                &buf.note[3], &coef4,
                                &buf.moyenne, &buf.exist);

        // Check if the correct number of fields was parsed
        if (read_count != 15) {
            fprintf(stderr, "Error reading student data on line %d: . Expected 15 items, got %d\n", line_number, line, read_count);
            line_number++;
            continue;
        }

        // Write to temporary file only if the student exists
        if (buf.exist == 0) {
            fprintf(Temp_File, "%d %s %s %d %2s %.1f %d %.1f %d %.1f %d %.1f %d %.2f %d\n",
                    buf.id, buf.name, buf.surname, buf.birth_year, buf.group,
                                buf.note[0], coef1,
                                buf.note[1], coef2,
                                buf.note[2], coef3,
                                buf.note[3], coef4,
                                buf.moyenne, buf.exist);
        }
        line_number++;
    }

    fclose(file);
    fclose(Temp_File);

    // These lines to replace the original file with the temporary file
    remove(filename);
    rename(Temp_file_name, filename);
    printf("\nStudents deleted successfully.\n");
}

void display_students(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
    perror("Error opening file");
    return;
    }

  student s;
  char line[256];

  while (fgets(line, sizeof(line), f) != NULL) {
    if (sscanf(line, "%d %s %s %d %s %f 4 %f 3 %f 2 %f 5 %f %d",
              &s.id, s.name, s.surname, &s.birth_year, s.group,
              &s.note[0], &s.note[1], &s.note[2], &s.note[3], &s.moyenne, &s.exist) == 11) {
        printf("ID: %d | Name: %s %s | Birth Year: %d | Group: %s | Average: %.2f | Active : %d\n", s.id, s.name, s.surname, s.birth_year,  s.group, s.moyenne, s.exist);
      }
    }
}
