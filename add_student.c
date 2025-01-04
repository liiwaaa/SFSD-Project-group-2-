// Function for Id check 
int unique_id(int id) {
    FILE *f = fopen("Listes_Etudiants.txt", "r");
    if (f == NULL) {
        return 1; // File not found, ID is unique
    }

    int existing_id;
    while (fscanf(f, "%d", &existing_id) == 1) { // We put our first integer of each line in the variable existing_id and we check it with the ID that the user input.
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

    // Reorder and insert new student at its corresponding location.
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
        return -1;
    }

    printf("Student added successfully.\n");
}
