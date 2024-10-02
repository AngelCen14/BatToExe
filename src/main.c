#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_util.h"
#include "bat_processor.h"
#include "compiler.h"

int main(int argc, char *argv[]) {
    printf("BatToExe\n");

    // Comprobar los argumentos
    int expectedArgs = 2;
    if (argc != 2+1) { // Se suma 1 por que el nombre del propio programa cuenta como argumento
        printf("Expected %d arguments: bat and exe\n", expectedArgs);
        return EXIT_FAILURE;
    }

    // Guardar referencias a los argumentos
    char *batFile = argv[1];
    char *exeFile = argv[2];

    // Leer el fichero .bat
    printf("Reading file: %s...\n", batFile);
    char *batContent = readFile(batFile);
    if (batContent == NULL) {
        perror("Error reading file");
        return EXIT_FAILURE;
    }

    // Generar codigo C a partir del .bat
    printf("Generating program...\n");
    char *generatedCode = batToC(batContent);
    free(batContent); 
    if (generatedCode == NULL) {
        perror("Error converting bat file");
        return EXIT_FAILURE;
    }

    // Compilar el codigo c
    printf("Compiling program...\n");
    int compilationResult = compileC(generatedCode, exeFile);
    free(generatedCode);

    if (compilationResult != EXIT_SUCCESS) {
        perror("Error compiling code");
        return EXIT_FAILURE;
    }

    printf("%s generated correctly\n", exeFile);
    
    return EXIT_SUCCESS;
}