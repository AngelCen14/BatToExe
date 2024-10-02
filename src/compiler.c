#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "file_util.h"

int compileC(const char *cCode, const char *outputFile) {
    // Generar fichero c temporal
    char tempFile[] = "temp.c";
    if (writeFile(tempFile, cCode) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    // Calcular el tamaño del comando
    size_t commandSize = strlen("gcc ") + strlen(tempFile) + strlen(" -o ") + strlen(outputFile) + 1;
    char *command = malloc(commandSize);
    if (command == NULL) {
        remove(tempFile); // Limpiar archivo temporal si hay error
        return EXIT_FAILURE;
    }
    
    // Generar y ejecutar el comando
    sprintf(command, "gcc %s -o %s", tempFile, outputFile);
    int result = system(command);

    // Eliminar el archivo temporal y limpira la memoria
    remove(tempFile);
    free(command);
    return result;
}