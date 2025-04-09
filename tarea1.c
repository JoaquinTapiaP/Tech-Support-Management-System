#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

#define MAX 255
#define High 1
#define Mid 2
#define Low 3

typedef struct {
    int ID;
    char desc[MAX];
    int prioridad;
} DatosPaciente;

int esNumerico(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0; // Cadena vacía o NULL
    }

    // Verificar si cada carácter es un dígito
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // No es numérico
        }
    }
    return 1; // Es numérico
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // En Windows
    #else
        system("clear"); // En Linux/Mac
    #endif
}

DatosPaciente* SearchID(List* lista, int IDSearch) {
    if (lista == NULL || firstList(lista) == NULL) return NULL;

    DatosPaciente* patient = firstList(lista);
    while (patient != NULL) {
        if (patient->ID == IDSearch) {
            return patient;
        }
        patient = nextList(lista);
    }
    return NULL;
}

void mostrarMenuPrincipal() {
    
    printf("========================================\n");
    printf("     Hospital Management System\n");
    printf("========================================\n");
  
    printf("1) Register pacient\n");
    printf("2) Assign priority to patient\n");
    printf("3) Show waiting list\n");
    printf("4) Attent next patient\n");
    printf("5) Show Patients by priority\n");
    printf("6) Exit\n\n");
}

void AddPacient(List* lista) {
    
    DatosPaciente *nuevo = (DatosPaciente *)malloc(sizeof(DatosPaciente));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    printf("Insert Pacient ID:\n");

    char aux[MAX];
    scanf("%s", aux);

    if (!esNumerico(aux)) {
        limpiarPantalla();
        printf("Invalid Value, returning to main menu...\n");
        return;
    }
    nuevo->ID = atoi(aux);
    getchar();

    printf("Describe the Problem:\n");
    scanf("%[^\n]s", nuevo->desc);
    nuevo->prioridad = Low;

    pushBack(lista, nuevo);
    limpiarPantalla();
    printf("Pacient has been added to the list correctly.\n");
}

void AddPriority(List* LOW, List* MID, List* HIGH) {
    int IDSearch;
    printf("Enter the patient's ID to update priority:\n");
    scanf("%d", &IDSearch);

    // Buscar en todas las listas
    DatosPaciente* paciente = SearchID(LOW, IDSearch);
    List* listaOriginal = LOW;
    
    if (paciente == NULL) {
        paciente = SearchID(MID, IDSearch);
        listaOriginal = MID;
    }
    
    if (paciente == NULL) {
        paciente = SearchID(HIGH, IDSearch);
        listaOriginal = HIGH;
    }

    if (paciente == NULL) {
        limpiarPantalla();
        printf("The ID has not been found, returning to main menu...\n");
        return;
    }

    printf("The patient with ID '%d' has been found.\n", IDSearch);
    printf("Please insert new priority (High, Mid or Low):\n");
    
    int prioridad;
    scanf("%d", &prioridad);

    // Primero eliminamos al paciente de su lista original
    DatosPaciente* current = firstList(listaOriginal);
    while (current != NULL) {
        if (current->ID == IDSearch) {
            popCurrent(listaOriginal);
            break;
        }
        current = nextList(listaOriginal);
    }

    // Luego lo insertamos en la nueva lista de prioridad
    switch (prioridad) {
        case High:
            paciente->prioridad = High;
            pushBack(HIGH, paciente);
            break;
        case Mid:
            paciente->prioridad = Mid;
            pushBack(MID, paciente);
            break;
        case Low:
            paciente->prioridad = Low;
            pushBack(LOW, paciente);
            break;
        default:
            printf("Invalid priority. Patient will remain in current list.\n");
            pushCurrent(listaOriginal, paciente); // Lo devolvemos a su lista original
            break;
    }

    limpiarPantalla();
    printf("Priority has been changed correctly.\n");
    return;
}

void ShowList(List* list) {
    if (list == NULL || firstList(list) == NULL) return;

    DatosPaciente* patient = firstList(list);
    printf("-------------------------\n");
    while (patient != NULL) {
        printf("Patient ID: %d\n", patient->ID);
        printf("Patient DESC: %s\n", patient->desc);
        printf("Patient PRIORITY: %d\n", patient->prioridad);
        printf("-------------------------\n");
        patient = nextList(list);
    }
    return;
}

int main() {
    int option;
    List* PacientesHIGH = createList();
    List* PacientesMID = createList();
    List* PacientesLOW = createList();
    
    
    do {
        mostrarMenuPrincipal();
        scanf("%d", &option);
        getchar();
        
        switch (option) {
            case 1:
                //printf("---INSERTA NUEVO PACIENTE---\n");
                AddPacient(PacientesLOW);
                break;
            case 2:
                //printf("---REEMPLAZA NUEVA PRIORIDAD---\n");
                AddPriority(PacientesLOW, PacientesMID, PacientesHIGH);
                break;
            case 3:
                //printf("---PRINT LISTA PACIENTES---\n");
                printf("Showing waiting list...\n");
                ShowList(PacientesHIGH);
                ShowList(PacientesMID);
                ShowList(PacientesLOW);
                if (option != 6) {
                    getchar();
                    limpiarPantalla();
                    }
                break;
            case 4:
                printf("---PROCESE SIGUIENTE PACIENTE---\n");
                break;
            case 5:
                printf("---PRINT MOSTRAR TODA LISTA POR PRIORIDAD---\n");
                break;
            case 6:
                puts("Closing Hospital Management System...\n");
                break;
            default:
                printf("Invalid option, please try again\n");
        }

        // Limpiar la pantalla después de cada acción y volver al menú principal
        if (option != 6) {
            getchar();
        }

    } while (option != 6);

    printf("Thank you for using HMS, see you later!\n");
    
    /*
    gcc  tarea1.c list.c -Wno-unused-result -o Tarea-1-JoaquinTapiaP 
    ./Tarea-1-JoaquinTapiaP
    */

    return 0;
}