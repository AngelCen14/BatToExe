#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bat_processor.h"

char *fixBat(const char* batContent) {
    // Calcular el tamaño final
    size_t finalSize = strlen(batContent);
    for (size_t i = 0; i < strlen(batContent); i++) {
        char c = batContent[i];
        if (c == '\n') finalSize += 4; // " && " = 4 caracteres
        else if (c == '"') finalSize += 2; // \" = 2 caracteres
        else if (c == '\\') finalSize += 2; // \\ = 2 caracteres
    }

    char *fixedBat = malloc(finalSize + 1);
    if (fixedBat == NULL) return NULL;

    fixedBat[0] = '\0';  // Asegurar que fixedBat este vacio

    for (size_t i = 0; i < strlen(batContent); i++) {
        char c = batContent[i];
        switch (c) {
            case '\n':
                // Reemplazar nueva linea con ' && ' para concatenar comandos en system()
                strcat(fixedBat, " && ");
                break;
            case '"':
                // Escapar las comillas dobles
                strcat(fixedBat, "\\\"");
                break;
            case '\\':
                // Escapar barras invertidas
                strcat(fixedBat, "\\\\");
                break;
            default:
                // Añadir el caracter tal cual
                size_t len = strlen(fixedBat);
                fixedBat[len] = c;       // Añadir el caracter
                fixedBat[len + 1] = '\0'; // Asegurar la terminacion de la cadena
                break;
        }
    }
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