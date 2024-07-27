#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main() {
    char mainDirectory[] = "C:/Users/itssk/OneDrive/Desktop";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Create the path for the main directory and subdirectory
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);

    // Create the full file path
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Open the file in write mode
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    // Write content to the file
    fprintf(file, "This is an example file content.");

    // Close the file
    fclose(file);

    printf("File created successfully: %s\n", filePath);
    return 0;
}
