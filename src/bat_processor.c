#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bat_processor.h"

char *fixBat(const char* batContent) {
    char *fixedBat = malloc(strlen(batContent) * 2 + 1); 
    if (fixedBat == NULL) return NULL;

    fixedBat[0] = '\0';  // Asegurarse de que fixedBat esté vacío

    for (size_t i = 0; i < strlen(batContent); i++) {
        char c = batContent[i];

        if (c == '\n') {
            // Reemplazar nueva línea con ' && ' para concatenar comandos en system()
            strcat(fixedBat, " && ");
        } else if (c == '"') {
            // Escapar las comillas dobles
            strcat(fixedBat, "\\\"");
        } else if (c == '\\') {
            // Escapar barras invertidas
            strcat(fixedBat, "\\\\");
        } else {
            // Añadir el carácter tal cual
            size_t len = strlen(fixedBat);
            fixedBat[len] = c;       // Añadir el carácter
            fixedBat[len + 1] = '\0'; // Asegurar la terminacion de la cadena
        }
    }

    fixedBat = realloc(fixedBat, strlen(fixedBat)+1);
    return fixedBat;
}

char *batToC(const char* batContent) {
    char baseCode[] = "#include <stdlib.h>\n\nint main() {\n    system(\"%s\");\n    return 0;\n}";
    
    // Obtener el bat arreglado para la funcion system()
    char *fixedBat = fixBat(batContent);
    if (fixedBat == NULL) return NULL;

    // Formatear el bat en el codigo c
    char *code = malloc(strlen(fixedBat) + strlen(baseCode) + 1);
    if (code == NULL) return NULL;
    sprintf(code, baseCode, fixedBat);

    free(fixedBat); // Liberar memoria
    return code;
}