#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void searchDirectory(const char *directory, const char *search_term) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    int found_match = 0;

    // Open the directory
    dir = opendir(directory);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", directory, entry->d_name);

        // Check if the entry is a directory
        if (entry->d_type == DT_DIR) {
            // Skip "." and ".." directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            // Recursively search subdirectories
            searchDirectory(full_path, search_term);
        } else {
            // Check if the filename contains the search term
            if (strstr(entry->d_name, search_term) != NULL) {
                // Print directory if a match is found
                if (!found_match) {
                    printf("%s\n", directory);
                    found_match = 1;
                }
                // Print matched file
                printf("      %s\n", entry->d_name);
            }
        }
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <search_term>\n", argv[0]);
        return 1;
    }

    // Get the directory path and search term from command-line arguments
    const char *directory = argv[1];
    const char *search_term = argv[2];

    // Start the search operation
    searchDirectory(directory, search_term);

    return 0;
}

