#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void moveFileToFolder(const char *filename) {
    char extension[10] = {0};
    char *dot = strrchr(filename, '.');  // Find the last dot in filename

    if (!dot || dot == filename) {
        printf("No extension found in file: %s\n", filename);
        return;
    }

    strcpy(extension, dot + 1); // Extract extension

    // Create target path: e.g., "pdf/first.pdf"
    char targetPath[100];
    snprintf(targetPath, sizeof(targetPath), "%s/%s", extension, filename);

    // Create the folder if it doesn't exist (Linux/macOS)
    char mkdirCmd[100];
    snprintf(mkdirCmd, sizeof(mkdirCmd), "mkdir  %s", extension);
    system(mkdirCmd);

    // Move the file
    if (rename(filename, targetPath) == 0) {
        printf("Moved %s to %s/\n", filename, extension);
    } else {
        perror("Error moving file");
    }
}

int main() {
    char filename[100];

    printf("Enter filename (e.g., first.pdf): ");
    scanf("%s", filename);

    moveFileToFolder(filename);

    return 0;
}
