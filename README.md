# Student Management System
This project is a Student Management System designed for academic institutions to streamline student data management. It provides functionalities such as adding, searching, editing, and logically deleting student records while ensuring data reliability and integrity.

## Table of Contents
- [I. Data Implementation](#i-data-implementation)
- [II. Functions](#ii-functions)
  - [1. Add Student](#1-add-student)
  - [2. Search Student by ID](#2-search-student-by-id)
  - [3. Modification](#3-modification)
  - [4. Logical Deletion](#4-logical-deletion)
  - [5. Extract and Sort](#5-extract-and-sort)
  - [6. Physical Deletion](#6-physical-deletion)

## I. Data Implementation
This part of code represents how to implement the student's data. We followed a sequential file implementing method and used blocks to represent the students of the same year from different groups (e.g., EX 1A, 2B). 
the output for each student was:
```
ID Family_Name Name Year_of_Birth Group Sfsd_grade Sfsd_coeff OOP_grade OOP_coeff Ana_grade Ana_coeff Alg_grade Alg_coeff Weighted_Average Existance
```
Exemple :
```
1 Ali Ahmed 2001 3A 15.5 4 12.0 3 14.0 2 16.5 5 14.2 0
```

## II. Functions
### 1. Add Student
- Validates inputs:
  - Ensures the ID is unique using the `unique_id` function.
  - Confirms the year of birth (`1990-2020`) and correct group format (e.g., `1A`).
  - Checks grades (`0-20`) and calculates the weighted average using:
    ```
    Average = (SFSD * 4 + POO * 3 + Analysis * 2 + Algebra * 5) / 14.00
    ```
- Reads the original file and compares group codes to find the correct insertion point.
- Inserts the student in order or appends to the end if applicable.
- Replaces the original file with the updated one after ensuring all data is written correctly.

#### Problems Encountred
-Inserting the student at the correct position:
For an unordered file, we could have simply opened the file in append mode to add the new student directly. However, maintaining the order required a more sophisticated approach.
 . Using fseek was attempted, but it caused unintentional changes to the data, as file I/O does not support direct insertion without overwriting.
 . Our final solution was to use a temporary file. 
 
### 2. Search Student by ID
The `search_student_by_id` function retrieves and displays detailed information about a student based on their unique ID from a data file.
#### Instructions:
1. **Prompt the user** to enter the ID of the student whose information is to be searched.
2. Open the main file `Listes_Etudiants.txt` in **read mode** and check if it is empty (no changes will be possible if it is and an error message is returned).
3. Uses a formatted string to extract and interpret structured student data.
4. Read Each Line: The `while` loop reads each line from the file using `fgets` and stores it in the line buffer until the end of the file is reached.
5. Parse and Match: `sscanf` extracts data from the line into the student structure (s) if the format matches. It checks if the parsed ID `s.id` matches the `searchid`.
6. Display Information: If a match is found, the student’s details (name, grades, etc.) are printed.
7. Returns an error message if there wasn't any match.
8. Closes the file.
#### Input
`filename` & `searchid`
#### Output
- If the student is found:
   - **Prints their detailed information to the console.**
- If the student is not found or the file cannot be opened:
   - **Displays an appropriate error message.**
### 3. Modification
This documentation explains how to implement the student information modification procedure, along with encountered problems and instructions for use.

#### Procedure Description
This function allows modifying student information as requested by the user. The modifiable details include:
- **ID**
- **First name**
- **Last name**
- **Group**
- **Grades for 4 modules** (requires recalculating the average)
- **status**

#### Instructions
1. **Prompt the user** to enter the ID of the student whose information is to be modified.
2. Open the main file `Listes_Etudiants.txt` in **read mode** and check if it is empty (no changes will be possible if it is).
3. Open the temporary file `temp.txt` in **write mode** to store the modified data. Check its existence as well.
4. Use a `while` loop to read each line from the main file and validate all the student’s fields (**condition < 11**).
5. Store the line read into the variable `line`.
6. **Compare the user-entered ID** with the ID read from the line:
   - If they match, display a menu (using a `switch-case`) with modification options (1 to 7).
   - If they don’t match, read the next line (via the `while` loop) and repeat the instructions (steps 4, 5, and 6).
7. Write the data (modified or not) into the temporary file.
8. After processing all the lines (**end of file reached**), close both files.
9. If modifications were made, rename the temporary file to the original file’s name and delete the original file.

#### Problems Encountered
1. Writing multiple variables on the same line using the `sscanf` function.
2. The file and the code must be in the same location for the code to work, or the full file path must be provided.

#### Notes
- **Validation**: Ensure the entered group is validated to confirm it exists.
- **Testing Conditions**: Address minor mistakes in test conditions.


### 4. Logical Deletion
The `logicaldeletion` function updates a student's record in a text file by marking their `exist` field as `1`, indicating the record is logically deleted while keeping the data intact.

**Process:**

1. Opens the original file for reading and creates a temporary file for writing.
2. Reads each line of the original file using a while loop.
3. Parses the line into variables (e.g., id, name, exist) with `sscanf`.
4. Checks if the id matches the target `target_id`. If it matches, updates the `exist` field to `1`.
5. Writes either the modified or original line into the temporary file.
6. Replaces the original file with the updated temporary file by deleting the original and renaming the temporary file.

**Challenge Faced:**  
Directly modifying the file caused unintended changes to the data (e.g., altering the id field). This happened due to mismatches in line lengths after modifications, leading to corruption in the file's structure. The solution was to use a temporary file for updates, ensuring the changes were applied accurately without affecting the original file's data integrity.
### 5. Extract and Sort
This function extracts all students from a specified group (e.g., "1A") from the file, sorts them by their average grade in descending order, and displays the sorted list.

#### instructions
1.Opens the file  `Listes_Etudiants.txt` containing the student data for reading.

2.Reads each line from the file.

3.Parses the line into a student structure using sscanf.

4.Checks if the student belongs to the specified group (strcmp(s.group, grp)) and is marked as active (s.exist == 0).

5.Adds matching students of the same group to an array (students[]).

6.Uses a simple nested loop to sort the students[] array in descending order based on their average grade (s.moyenne).

7.Prints the sorted list of students with their name, ID, and average grade.

#### Problems Encountered
1.If the user provides an empty or invalid group in the file, no students will be found.

2.The strcmp function is case-sensitive. If the group in the file is "1a" but the user inputs "1A", no match will occur.

### 6. Physical Deletion
This process removes students marked as logically deleted (exist != 0) by creating a temporary file that includes only active students (exist == 0). The temporary file replaces the original file.

#### Steps:
. Open Files: Read from the original file and write to a temporary file.
. Process Records:
      - Parse each student record.
      - Write active students (exist == 0) to the temporary file.
. Finalize: Close both files.
. Replace the original file with the temporary file.

#### Key Points:
- Ensures only active student records remain.

- Uses a temporary file for data safety during processing.

- The exist field determines whether a student is retained or removed.

