#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CARTAS 10000  // Limite maximo de cartas que podemos manejar

//----------------------ENTRENAMIENTO-------------------------------------------//

// Funcion para liberar memoria de las cartas
void liberarCartas(char **cartas, int num_cartas) {
    for (int i = 0; i < num_cartas; i++) {
        free(cartas[i]);
    }
}

// Funcion para dividir el contenido de archivo en cartas segun el criterio de numeros
void dividirCartas(char *contenido, char **cartas, int *num_cartas) {
    int start = 0;
    int largoContenido = strlen(contenido);
    *num_cartas = 0;

    for (int i = 0; i <= largoContenido; i++) {
        if (isdigit(contenido[i]) || contenido[i] == '\0') {
            if (i != 0) {
                int largoSegmento = i - start;
                if (largoSegmento > 0) {
                    cartas[*num_cartas] = (char *)malloc((largoSegmento + 1) * sizeof(char));
                    strncpy(cartas[*num_cartas], &contenido[start], largoSegmento);
                    cartas[*num_cartas][largoSegmento] = '\0';
                    (*num_cartas)++;
                }
            }
            start = i;
        }
    }
}

// Clasificar cartas en los diferentes tipos
void tiposCartas(char **cartas, int num_cartas, char ***cartaAmor, int *ct1, char ***cartaTermino, int *ct2, char ***cartaMejorAmigos, int *ct3, char ***cartaMeDesagradas, int *ct4, char ***cartaEstoyFeliz, int *ct5) {
    
    *ct1 = *ct2 = *ct3 = *ct4 = *ct5 = 0;

    for (int i = 0; i < num_cartas; i++) {
        
        int tipo = cartas[i][0] - '0'; // Convierte el primer carácter directamente a int

        switch (tipo) {
            case 1:
                (*cartaAmor)[(*ct1)++] = strdup(cartas[i]);
                break;
            case 2:
                (*cartaTermino)[(*ct2)++] = strdup(cartas[i]);
                break;
            case 3:
                (*cartaMejorAmigos)[(*ct3)++] = strdup(cartas[i]);
                break;
            case 4:
                (*cartaMeDesagradas)[(*ct4)++] = strdup(cartas[i]);
                break;
            case 5:
                (*cartaEstoyFeliz)[(*ct5)++] = strdup(cartas[i]);
                break;
            default:
                break;
        }
    }
}

//Banco de datos
//guardarBancos();

//ENTRENAMIENTO PRINCIPAL

void entrenamientoPrincipal(void){
    printf("\nSe esta entrenando el programa...");
    FILE *cartaMaxima = fopen("carta.txt", "r");
        if (!cartaMaxima) {
            perror("No se pudo abrir el archivo");
        }

        fseek(cartaMaxima, 0, SEEK_END);
        long cartaPrueba = ftell(cartaMaxima);
        fseek(cartaMaxima, 0, SEEK_SET);

        char *contenido = (char *)malloc((cartaPrueba + 1) * sizeof(char));
        fread(contenido, sizeof(char), cartaPrueba, cartaMaxima);
        contenido[cartaPrueba] = '\0';
        fclose(cartaMaxima);

        // Alocar memoria dinámica para las cartas
        char **cartas = (char **)calloc(MAX_CARTAS, sizeof(char *));
        int num_cartas = 0;

        // Alocar memoria para los diferentes tipos de cartas
        char **cartaAmor = (char **)calloc(MAX_CARTAS, sizeof(char *));
        char **cartaTermino = (char **)calloc(MAX_CARTAS, sizeof(char *));
        char **cartaMejorAmigos = (char **)calloc(MAX_CARTAS, sizeof(char *));
        char **cartaMeDesagradas = (char **)calloc(MAX_CARTAS, sizeof(char *));
        char **cartaEstoyFeliz = (char **)calloc(MAX_CARTAS, sizeof(char *));

        int ct1 = 0, ct2 = 0, ct3 = 0, ct4 = 0, ct5 = 0;

        //Aprendizaje
        dividirCartas(contenido, cartas, &num_cartas);
        tiposCartas(cartas, num_cartas, &cartaAmor, &ct1, &cartaTermino, &ct2, &cartaMejorAmigos, &ct3, &cartaMeDesagradas, &ct4, &cartaEstoyFeliz, &ct5);
        //guardarBancos(cartaAmor, cartaTermino, cartaMejorAmigos, cartaMeDesagradas, cartaEstoyFeliz);

    //------------------------------------Liberar memoria en cartas------------------------------------//
    // Liberar memoria de las cartas originales
        liberarCartas(cartas, num_cartas);
        free(cartas);
        free(contenido);

        // Liberar memoria de los tipos de cartas
        liberarCartas(cartaAmor, ct1);
        liberarCartas(cartaTermino, ct2);
        liberarCartas(cartaMejorAmigos, ct3);
        liberarCartas(cartaMeDesagradas, ct4);
        liberarCartas(cartaEstoyFeliz, ct5);
        free(cartaAmor);
        free(cartaTermino);
        free(cartaMejorAmigos);
        free(cartaMeDesagradas);
        free(cartaEstoyFeliz);

        printf("\nSe entreno el programa exitosamente :3 \n");
}

int main(void) {

    int repetirPrograma = 1;
    while (repetirPrograma == 1){

        int opcion = 0;
        printf("\nBienvenido al analizador de sentimientos chachipistachi :3 \n");
        printf("\n¿Ingresa la opcion que deseas hacer? \n");
        printf("\n1. Entrenar le programa (Solo seleccionalo cuando el programa se inicie por primera vez) \n");
        printf("\n2. Analizar una carta \n");
        printf("\n3. finaliza el programa \n");

        scanf("%d", &opcion);

        
            switch (opcion)
            {
            case 1:
                entrenamientoPrincipal();
                break;
            
            case 2:
                printf("Holi");
                break;

            case 3:
                repetirPrograma = 0;
                break;
            }
    }

    

    return 0;
}
