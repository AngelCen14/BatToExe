#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "file_util.h"

#define BUFFER_SIZE 256

char *readFile(const char *fileName) {
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL) return NULL;
    
    char *content = NULL;
    char buffer[BUFFER_SIZE];
    size_t totalLength = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t bufferLength = strlen(buffer);
        char *newContent = realloc(content, totalLength + bufferLength + 1); // +1 for null terminator
        if (newContent == NULL) {
            free(content); 
            fclose(file);
            return NULL; 
        }
        content = newContent;
        strcpy(content + totalLength, buffer); 
        totalLength += bufferLength;
    }
    fclose(file);

    return content;
}

int writeFile(const char *fileName, const char *content) {
    if (fileName == NULL || content == NULL) {
        return EXIT_FAILURE; 
    }

    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL) return EXIT_FAILURE;
    
    int result = fprintf(file, "%s", content);
    fclose(file);
    return result;
}