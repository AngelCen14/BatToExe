#include<stdio.h>
#include<stdlib.h>

#include "file_util.h"

int main(int argc, char *argv[]) {
    printf("BatToExe\n");

    // Comprobar los argumentos
    int expectedArgs = 2;
    if (argc != 2+1) { // Se suma 1 por que el nombre del propio programa cuenta como argumento
        printf("Expected %d arguments: bat and exe\n", expectedArgs);
        return 1;
    }

    // Guardar referencias a los argumentos
    char *batFile = argv[1];
    char *exeFile = argv[2];

    // Leer el fichero .bat
    char *fileContent = readFile(batFile);
    if (fileContent == NULL) {
        perror("Error reading file");
        return 1;
    }
    
    /* Escribir el contenido del .bat en el .exe 
    (Esto es temporal, se debe convertir las instrucciones del
    script a un ejecutable) */ 
    writeFile(exeFile, fileContent);

    // Liberar la memoria
    free(fileContent);
    return 0;
}