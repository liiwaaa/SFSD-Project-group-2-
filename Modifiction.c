void modification(const char *filename, const char *temp_filename)
 {
    char line[256];
    int fid, choice, nb, i, exist;
    char module[20];
    exist=0;
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
            exist=1;
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
                            printf("Invalid Input, please try again, the year must be between 1990 and 2020 : ");
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
     if(exist==1) {
    printf("Modification completed successfully.\n");
     }
    else{
    printf("Id doesn't exist, modification not allowed \n");
     }
}
