#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void mostrarMenuPrincipal() {
    //limpiarPantalla();
    printf("========================================\n");
    printf("     Sistema de Gestion Hospitalaria\n");
    printf("========================================\n");
  
    printf("1) Registrar paciente\n");
    printf("2) Asignar prioridad a paciente\n");
    printf("3) Mostrar lista de espera\n");
    printf("4) Atender al siguiente paciente\n");
    printf("5) Mostrar pacientes por prioridad\n");
    printf("6) Salir\n\n");
    
}

int main() {
    int option;
    mostrarMenuPrincipal();
    do {
        
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                printf("---INSERTE INPUT PACIENTE---\n");
                break;
            case 2:
                printf("---INSERTE INPUT PRIORIDAD---\n");
                break;

            case 3:
                printf("---INSERTE LISTA PACIENTES---\n");
                break;
            
            case 6:
                puts("Saliendo del sistema de gestion hospitalaria...\n");
                break;

            default: 
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        } 
        printf("\n");

    } while (option != 6);
    /*printf("I can't go on");*/
    printf("Keep it going\n");

    return 0;
}