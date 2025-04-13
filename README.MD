### Hospital Management System (HMS)


## Descripción
Este programa permite a los usuarios gestionar los pacientes de un hospital.
Los usuarios pueden registrar nuevos pacientes, reasignar prioridades, ver la lista de espera, procesar el siguiente paciente y buscar y mostrar la informacion de un paciente.
Esta herramiente esta hecha con el proposito de ayudar con el orden y organizacion de los pacientes, asegurando que aquellos en situaciones peligrosas sean los primeros en ser atendidos.


## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el** archivo `.zip` en una carpeta de tu elección.
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. **Compila el código**
    - Abre el archivo principal `tarea1.c`.
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal Git Bash, compila el programa con el siguiente comando: 
    ```
    gcc  tarea1.c list.c -Wno-unused-result -o Tarea-1-JoaquinTapiaP 
    ```
4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
    ```
    ./Tarea-1-JoaquinTapiaP
    ```

### Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con su ID, descripcion, hora y una prioridad inicial en orden de llegada.
- Modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad (de alta a baja).
- Buscar un paciente según su ID.

### Problemas conocidos:

- Una vez la prioridad de un paciente en la lista de prioridad baja es cambiada, no se puede cambiar al estar en otra lista de prioridad

### A mejorar:

- Permitir la edición de la descripcion de los pacientes.
- Permitir el cambio de prioridades cuando no se encuentran en prioridad baja.


## Ejemplo de uso

**Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando un nuevo paciente que acaba de llegar al hospital.

```
Opción seleccionada: 1) Registrar paciente
Ingrese el ID del paciente: 6
Ingrese la descripcion del problema del paciente: Equince de muñeca
Ingrese hora de llegada: 12:34
```

El sistema registra a un paciente con una ID, con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más adelante.

**Paso 2: Reasignar Prioridad a un Paciente**

Tras una evaluación inicial, el médico determina que el estado del paciente requiere atención prioritaria.

```
Opción seleccionada: 2) Asignar nueva prioridad a paciente
Ingrese el ID del paciente: 6
Seleccione el nuevo nivel de prioridad (Alto = 1, Medio = 2, Bajo = 3): 1
```

El sistema cambiara la prioridad del paciente a alto, y lo movera a la lista de alta prioridad.

**Paso 3: Mostrar la lista de espera**
El usuario desea ver la lista de pacientes del dia.

```
Opción Seleccionada: 3) Mostrar lista de espera
```

Mostrara la lista de espera, desde el primer paciente en la lista de pruioriad alta, hasta el ultimo paciente en la lista de prioridad baja.

**Paso 4: Mostrar la lista de espera**
El primer paciente es llamado para ser atendido.

```
Opción Seleccionada: 4) Procesar siguiente paciente
```
El sistema muestra la informacion del paciente, y lo elimina de la lista de espera.

**Paso 5: Buscar por un paciente**
El usuario desea buscar la informacion de un paciente en especifico
```
Opción Seleccionada: 5) Buscar un paciente
Ingrese el ID del paciente: 6
```

El sistema muestra la informacion del paciente.

**Paso 6: Buscar por un paciente**
Al final del dia, el usuario desea terminar el programa y vaciar toda la lista de espera
```
Opción Seleccionada: 6) Abandonar programa
```
El programa se termina y elimina la informacion restante.