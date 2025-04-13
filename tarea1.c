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
    int hora;
    int min;
} horario;

typedef struct {
    int ID;
    char desc[MAX];
    int prioridad;
    horario tiempo;
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
        system("cls");
    #else
        system("clear");
    #endif
}

DatosPaciente* SearchID(List* lista, int IDSearch) {
    if (lista == NULL || firstList(lista) == NULL) return NULL; //Si la lista no existe, retorna NULL
    
    DatosPaciente* patient = firstList(lista); //obtiene el primer paciente de la lista
    while (patient != NULL) { 
        //mientras el paciente no sea NULL, buscara por el ID, y pasa al siguiente si no lo es
        if (patient->ID == IDSearch) {
            return patient;
        }
        patient = nextList(lista);
    }
    //en caso de no encontrarlo, retorna NULL
    return NULL;
}

void mostrarMenuPrincipal() {
    //Muestra el menu principal del programa y sus opciones
    printf("========================================\n");
    printf("     Hospital Management System\n");
    printf("========================================\n");
  
    printf("1) Register pacient\n");
    printf("2) Assign priority to patient\n");
    printf("3) Show waiting list\n");
    printf("4) Attent next patient\n");
    printf("5) Search for Patient\n");
    printf("6) Exit\n\n");
}

void AddPacient(List* lista) {
    //define nuevo paciente
    DatosPaciente *nuevo = (DatosPaciente *)malloc(sizeof(DatosPaciente));
    if (nuevo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    } 

    printf("Insert Pacient ID:\n");

    char aux[MAX];
    scanf("%s", aux);
    /*recibe si el valor del ID en char, verifica si es un valor numerico
    si no llega a serlo, devuelve que es un valor invalido*/
    
    if (!esNumerico(aux)) {
        limpiarPantalla();
        printf("Invalid Value, returning to main menu...\n");
        free(nuevo);
        return;
    }
    //convierte el string a int para usarlo propiamente
    nuevo->ID = atoi(aux);
    getchar();

    //Lee la cadena de string para la descripcion del problema
    printf("Describe the Problem:\n");
    scanf("%[^\n]s", nuevo->desc);
    getchar();
    nuevo->prioridad = Low;

    /*Obtiene el valor de la hora actual, debido a que es un formato:
    Si la cantidad de los valores insertado es distitno a 2, lo invalida
    Si la hora es menor que 0 o mayor de 23 lo invalida
    Si los minutos son menores que 0 o mayores a 59 lo invalida
    */
    printf("Insert current time:\n");
    printf("Format must be in 24h and added as 'hh:mm'\n");
    if (scanf("%d:%d", &nuevo->tiempo.hora, &nuevo->tiempo.min) != 2 || nuevo->tiempo.hora < 0 
    || nuevo->tiempo.hora > 23 || nuevo->tiempo.min < 0 || nuevo->tiempo.min > 59) {
        printf("Invalid time format, returning to main menu...\n");
        free(nuevo);
        return;
    }

    //si todo está correcto, manda el nuevo paciente al final de la lista y limpia la pantalla
    pushBack(lista, nuevo);
    limpiarPantalla();
    printf("Pacient has been added to the list correctly.\n");
}

void eliminarPacientePorID(List* lista, int ID) {
    DatosPaciente* paciente = firstList(lista);
    DatosPaciente* anterior = NULL;
    //Obtiene el primer paciente de la lista
    //justifica el anterior de la lista como NULL de momento

    //Busca el ID del paciente por cada paciente de la lista, está ya verificado que el valor si existe
    //al encoontrarlo, lo elimina de la lista, popfront si llega a ser el primero y popCurrent si no llega a hacerlo
    //el paciente anterior ayuda a indicar si es o no el primero, ya que si no se encuentra en la primera iteracion, se justifica como el paciente actual, y continua
    while (paciente != NULL) {
        if (paciente->ID == ID) {
            if (anterior == NULL) {
                // Eliminar el primer nodo
                popFront(lista);
            } else {
                // Eliminar un nodo intermedio
                popCurrent(lista);
            }
            break;
        }
        anterior = paciente;
        paciente = nextList(lista);
    }
}

void AddPriority(List* LOW, List* MID, List* HIGH) {
    int IDSearch;
    printf("Enter the patient's ID to update priority:\n");
    scanf("%d", &IDSearch);
    // Obtiene el ID del paciente que se quiere cambiar

    // Buscar en la lista LOW, ya que todos se inserta ahí por defecto
    DatosPaciente* paciente = SearchID(LOW, IDSearch);

    //Si el paciente no existe, indica que no existe y vuelve al menu
    if ((paciente == NULL)) {
        limpiarPantalla();
        printf("The Value inserted is invalid, returning to main menu...\n");
        return;
    }

    //Avisa que encontró al paciente y pide que se indique la prioridad en numero
    // 1 si es alta, 2 si es media o 3 si es baja
    printf("The patient with ID '%d' has been found.\n", IDSearch);
    printf("Please insert new priority (High = 1, Mid = 2 or Low = 3):\n");

    char prioridad[MAX];
    scanf("%s", prioridad);
    /*recibe si el valor del ID en char, verifica si es un valor numerico
    si no llega a serlo, devuelve que es un valor invalido*/
    
    if (!esNumerico(prioridad)) {
        limpiarPantalla();
        printf("Invalid priority. Patient will remain in current list.\n");
        //Avisa del error y no hace nada
        return;
    }

    //transforma la prioridad en numero entero
    *prioridad = atoi(prioridad);

    // Luego lo insertamos en la nueva lista de prioridad
    limpiarPantalla();
    switch (*prioridad) {
        /*cambia la prioridad y lo tira al final de la lista correspondiente  
        Lo elimina de la lista LOW e indica que se elimino correctamente
        Si llega a ser un ID numerico no valido, lo indica y vuelve al menu principal
        Si llega a ser LOW (La misma prioridad anterior, avisa que no se cambio y termina)*/
        
        case High:
            paciente->prioridad = High;
            pushBack(HIGH, paciente);
            eliminarPacientePorID(LOW, IDSearch);
            printf("Priority has been changed correctly.\n");
            break;
        case Mid:
            paciente->prioridad = Mid;
            pushBack(MID, paciente);
            eliminarPacientePorID(LOW, IDSearch);
            printf("Priority has been changed correctly.\n");
            break;
        case Low:
            printf("Priority has been kept the same.\n");
            //no hace nada ya que ya está en la lista baja
            break;
        default:
            printf("Invalid priority. Patient will remain in current list.\n");
            //Avisa del error y no hace nada
            return;
    }
    return;
}

void showPatient(DatosPaciente *patient) {
    //Muestra todos los datos del paciente

    printf("Patient ID: %d\n", patient->ID);
    printf("Patient DESC: %s\n", patient->desc);
    printf("Patient PRIORITY: ");
    if (patient->prioridad == 1) 
        printf("HIGH\n");
    else if (patient->prioridad == 2)
        printf("MID\n");
    else 
        printf("LOW\n");
    printf("Patient TIME: %02d:%02d\n", patient->tiempo.hora, patient->tiempo.min);
    printf("-------------------------\n");
}

void ShowList(List* list) {
    if (list == NULL || firstList(list) == NULL) return; //si la lista esta vacia o no existe, termina

    //hace un paciente auxiiliar para obtener sus datos individuales y usa la funcion ShowPatient para mostrar sus datos
    DatosPaciente* patient = firstList(list);
    printf("-------------------------\n");
    //Una vez obtiene si el paciete existe, imprime todo y pasa al siguiente, se detiene una vez el paciente sea NULL
    while (patient != NULL) {
        showPatient(patient);
        patient = nextList(list);
    }
    return;
}

void ProcessPatient(List* LOW, List* MID, List* HIGH) {
    /*Marca una lista auxiliar 
    Verifica por cada lista si tiene pacientes o no, si no los tiene, procesa la siguiente
    Si la ultima fila (LOW) esta vacia, avisa que no queda nadie por procesar y te devuelve al menu prinicpal
    */
    List* prior = HIGH;
    DatosPaciente *patient = firstList(prior);
    if (patient == NULL) {
        patient = firstList(MID);
        prior = MID;
    }

    if (patient == NULL) {
        patient = firstList(LOW);
        prior = LOW;
    }
    limpiarPantalla();
    if (patient == NULL) {
        printf("There is no one left in the list, returning to main menu...\n");
        return;
    }
    
    //Procesa la lista, usa ShowPatient para mostrar todos los datos y lo elimina de su lista correspondiente
    printf("Processing next Patient on the list...\n");
    printf("-------------------------\n");
    showPatient(patient);
    popCurrent(prior);
}

void SearchPatient(List* LOW, List* MID, List* HIGH) {
    /*Una vez toda prioridad cambiada y/o procesada, pasa por todas las listas y busca con la funcion SearchID
    Si es que el paciente esta en la lista, si no esta en ninguna, indica que no existe*/
    List* prior = HIGH;
    int IDReq;
    printf("Insert the ID you are searching for\n");
    scanf("%d", &IDReq);
    

    DatosPaciente *patient = SearchID(prior, IDReq);
    if (patient == NULL) {
        patient = firstList(MID);
        prior = MID;
    }
    patient = SearchID(prior, IDReq);
    if (patient == NULL) {
        patient = firstList(LOW);
        prior = LOW;
    }
    patient = SearchID(prior, IDReq);
    limpiarPantalla();
    if (patient == NULL) {
        printf("The Patient with id %d does not exist, returning to main menu...\n", IDReq);
        return;
    }

    //Si encuentra el paciente, usa la funcion ShowPatient para mostrar sus datos
    printf("-------------------------\n");
    showPatient(patient);
}

int main() {
    //Crea la variante option para procesar la opcion que se quiere utilizar
    int option;

    //Crea 3 listas, una para cada prioridad, alta, media y baja
    List* PacientesHIGH = createList();
    List* PacientesMID = createList();
    List* PacientesLOW = createList();
    
    do {
        //obtiene el valor de la opcion y muestra el menu principal
        mostrarMenuPrincipal();
        scanf("%d", &option);
        getchar();
        
        switch (option) {
            case 1:
                //ejecuta la funcion para añadir un paciente
                //printf("---INSERTA NUEVO PACIENTE---\n");
                AddPacient(PacientesLOW);
                break;
            case 2:
                //ejecuta la funcion para cambiar la prioridad de un paciente
                //printf("---REEMPLAZA NUEVA PRIORIDAD---\n");
                AddPriority(PacientesLOW, PacientesMID, PacientesHIGH);
                break;
            case 3:
                //ejecuta la funcion showList para mostrar todos los pacientes de las 3 listas
                //printf("---PRINT LISTA PACIENTES---\n");
                printf("Showing waiting list...\n");
                printf("\nHigh Priority:\n");
                ShowList(PacientesHIGH);
                printf("\nMid Priority:\n");
                ShowList(PacientesMID);
                printf("\nLow Priority:\n");
                ShowList(PacientesLOW);
                if (option != 6) {
                    getchar();
                    limpiarPantalla();
                    }
                break;
            case 4:
                //ejecuta la funcion para procesar el siguiente paciente segun su prioridad y momento inscrito
                //printf("---PROCESE SIGUIENTE PACIENTE---\n");
                ProcessPatient(PacientesLOW, PacientesMID, PacientesHIGH);
                break;
            case 5:
                //ejecuta la funcion de buscar el paciente en las listas
                //printf("---PRINT MOSTRAR TODA LISTA POR PRIORIDAD---\n");
                SearchPatient(PacientesLOW, PacientesMID, PacientesHIGH);
                break;
            case 6:
                //termina el programa
                printf("Closing Hospital Management System...\n");
                break;
            default:
                printf("Invalid option, please try again\n");
        }

        // Después de cada acción volver al menú principal
        if (option != 6) {
            getchar();
        }

    } while (option != 6);

    printf("Thank you for using HMS, see you later!\n");
    free(PacientesHIGH);
    free(PacientesMID);
    free(PacientesLOW);

    /*
    gcc  tarea1.c list.c -Wno-unused-result -o Tarea-1-JoaquinTapiaP 
    ./Tarea-1-JoaquinTapiaP
    */

    return 0;
}