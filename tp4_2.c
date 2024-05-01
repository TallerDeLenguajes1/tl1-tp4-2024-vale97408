// =========EJERCICIO 2- TP4=============
#include <stdio.h>
#include <time.h> // Para nros aleatorios
#include <stdlib.h> // Para nros aleatorios
#include <string.h> // manipulacion de cadenas

//-------------------ESTRUCTURAS OTORGADAS------------------
struct Tarea{

int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100

} typedef Tarea;

// Un nodo de una lista enlazada donde cada nodo contiene una estructura Tarea
struct Nodo{
Tarea T;
struct Nodo *Siguiente;
} typedef Nodo;
//------------------------------

// ------PROTOTIPO DE FUNCIONES-------
//-----------FUNCION 1
Nodo* crearListaVacia();

//-----------FUNCION 2
Tarea cargarTarea(int id);

//-----------FUNCION 3
void agregadoDeTareas(Nodo** Lista, int *id);

//-----------FUNCION 4
void mostrarLista(Nodo* Lista);

//-----------FUNCION 5
void transNodosId(Nodo **L1, Nodo **L2); // L1 lista origen y l2 lista destino 

//-----------FUNCION 6
void buscarTareaID(Nodo* L1, Nodo* L2);

//-----------FUNCION 7
void buscarTareaPalabraClave(Nodo* L1, Nodo* L2);

//-----------FUNCION 8
void eliminarPrimerNodo(Nodo **L);


//------PROGRAMA PRINCIPAL------
int main(){
    int id = 1000; // Incremetal a usar del id  
    int opcion; // eleccion por el usuario
    srand(time(NULL)); // Semilla para el generador de numeros aleatorios

    // Creamos las dos listas solicitadas

    Nodo *listaTareasPendientes = crearListaVacia();
    Nodo *listaTareasRealizadas = crearListaVacia();

     // Menu para el usuario de la operacion a realizar
    do
    {
        printf("\n---------OPERACION A REALIZAR------------\n");
        printf("\n---1) Agregar una nueva tarea.\n");
        printf("---2) Transferir tareas de Pendientes a Realizadas. \n");
        printf("---3) Lista de Tareas Pendientes. \n");
        printf("---4) Lista de Tareas Realizadas. \n");
        printf("---5) Busqueda de  tarea por palabra clave.\n");
        printf("---6) Busqueda de tarea por id.\n");
        
        printf("---7) Salir. \n");
        printf("----- Opcion selecccionada: \n");

        scanf("%d", &opcion);

        // Segun la opcion elegida...

        switch (opcion)
        {
        case 1:
            printf("\n-----AGREGADO DE TAREAS\n");
            agregadoDeTareas(&listaTareasPendientes, &id);
            break;
        case 2:
          printf("\n-----TRANSFERENICA DE TAREAS\n");
            transNodosId(&listaTareasPendientes, &listaTareasRealizadas);
            break;
        case 3:
            printf("\n-----LISTA PENDIENTES:");
            mostrarLista(listaTareasPendientes);
            break;
        case 4:
            printf("\n-----LISTA REALIZADAS:");
            mostrarLista(listaTareasRealizadas);
             getchar();
            break;
        case 5:
         printf("\n-----BUSQUEDA DE TAREAS- PALABRA CLAVE\n");
           buscarTareaPalabraClave(listaTareasPendientes, listaTareasRealizadas);
            break;
        case 6:
          printf("\n-----BUSQUEDA DE TAREAS-  ID \n");
            buscarTareaID(listaTareasPendientes, listaTareasRealizadas);
             getchar();
            break;
        default:
            break;
        }
    } while (opcion != 7); // Itera hasta que el usuario haya seleccionado la opcion de salir 

   // Mientras la lista de pendientes no este vacia, elimina nodos y el contenido de las tareas de las listas

   // Lista Pendientes
   while(listaTareasPendientes != NULL)
   {
      free(listaTareasPendientes->T.Descripcion);
      eliminarPrimerNodo(&listaTareasPendientes);
   }

    // Lista Realizadas
   while(listaTareasRealizadas != NULL)
   {
      free(listaTareasRealizadas->T.Descripcion);
      eliminarPrimerNodo(&listaTareasRealizadas);
   }


 getchar();
 getchar();
    return 0;


}


// -------- DESARROLLO DE FUNCIONES ----------


//-----------FUNCION 1
// Devuelve un puntero nulo que indica una lista enlazada vacía
Nodo* crearListaVacia(){
    return NULL; 
}


//-----------FUNCION 2
// Crea y devuelve una tarea solicitancdo descripcion y duracion de la misma
Tarea cargarTarea(int id){

    Tarea nuevaT; // Nueva tarea 

    //1)

    char *buff = (char *)malloc(sizeof(char)*100); // Asignacion dinamica de memoria de la variable auxiliar 

    nuevaT.TareaID = id; // Id para la nueva tarea


    printf("\n >>>>Descripcion de la tarea: ");
    fflush(stdin);
    gets(buff); // Almaceno en la variable auxiliar

     //2)
    nuevaT.Descripcion = (char *)malloc((strlen(buff)+1)*sizeof(char)); // Asig dinámica  para almacenar la descripcion de la tarea en la estructura


    strcpy(nuevaT.Descripcion, buff); // Copio la descripcion almacenada en mi variable auxiliar en la estructura



    do {
        printf("\n>>>>> Duracion de la tarea: \n"); 
        scanf("%d",&nuevaT.Duracion); 
    } while (nuevaT.Duracion < 10 || nuevaT.Duracion > 100 ); // Controlo que la duracion sea entre 10 y 100

   free(buff); // Libero memoria de la descripcion alamacenada en la variable auxiliar

    return nuevaT; //Nueva tarea creada

}


//-----------FUNCION 3
// Agrega tareas a una lista creando un nuevo nodo para cada tarea al inicio de la lista
void agregadoDeTareas(Nodo** Lista, int *id){
    // recibe una lista y el id de la tarea a agregar 

    int continuar;
    do
    {  //3)
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo)); // Nuevo nodo para la nueva tare 

        nuevo->Siguiente = *Lista;// Apunta al siguiente del nuevo nodo al inicio de la lista

        *Lista = nuevo; //Inclute el nuevo nodo actualizando el inicio de la lista

        nuevo->T = cargarTarea(*id);
        (*id)++; // carga la tarea en el nodo

        printf("\n>>>> Cargar otra tarea:\n");
        printf(" 0- No \n ");
        printf(" 1- Si \n ");
        printf(">>Respuesta: \n");
        scanf("%d", &continuar);

    } while (continuar != 0); // itera agregando mas tareas  hasta que ya no quiera cargar 
}

//-----------FUNCION 4
void mostrarLista(Nodo* Lista){

 // Muestra las tareas de la lista que se paso como parametro, con su id, descripcion y duracion

    if (Lista == NULL) // Si la lista esta vacia
    {
        printf("\n--------Lista vacia---------\n");
    }

    while (Lista != NULL) // Mientras no este vacia
    {
        printf("\n>>>>TAREA<<<<");
        printf("\n--ID: %d ", Lista->T.TareaID);
        printf("\n--Descripcion: %s", Lista->T.Descripcion);
        printf("\n--Duracion de la tarea: %d\n", Lista->T.Duracion);

        Lista = Lista->Siguiente; // Avanza al siguiente nodo de la lista para mostrar las demas tareas
    }

    
}



//-----------FUNCION 5
// Trnfiere donos entre dos listas enlazadas con el id de la tarea, desconectandolo de la lista l1 y conectandolo al inicio de la lista l2

void transNodosId(Nodo **L1, Nodo **L2){
    // recibe las dos listas para realizar la transferencia

    int id, respuesta;

      printf("\n----------TRANFERENCIA DE TAREAS---------\n ");
    do
    { 
        printf("--ID de la tarea a agregar a Lista de tareas realizadas: \n ");
        scanf("%d", &id);

        Nodo *actual = *L1; // Inicializa nodo como el primero de la lista 
        Nodo *anterior = NULL;

        // Buscamos el nodo (la tarea) con el id en la lista de tareas pendiente l1)hasta que se encuentra el nodo o llega al final de la lista  

        while (actual != NULL && actual ->T.TareaID != id) {  // Si no esta vacia y no hay coincidencia con el id sigue recorriendo la lista 

            anterior = actual; 
            actual = actual->Siguiente;
        }

       // Si hay coincidencia de ID- comienza la transferencia a l2
        if(actual != NULL)
        { 
            // desconecta el nodo  de la lista  l1 en donde fue encontrada la tarea

            if (anterior != NULL)
            {
                anterior->Siguiente = actual->Siguiente;   // Actualiza punteros 
            } else
            {
                *L1 = actual->Siguiente; // Actualiza el inicio de la listal1 si el nodo tranferido era el primero
            }

            // Conecta el nodo al inicio de la lista l2 en donde fue transferida la tarea ( l. realizadas) 
            actual->Siguiente = *L2; 

           // Actualiza el inicio de la lista l2 para corroborar la transferencia- lo conecta al nodo en el inicio de l2
            *L2 = actual; 

            printf("\n---Tranferencia exitosa!\n");
        } else {
            printf("\n---No existe  una tarea pendiente con el ID ingresado.---\n");
        }

        printf("\n>>>>Tranferir más tareas? \n");
        printf("0) No. \n");
        printf("1) Si. \n");
        printf("--Respuesta:  \n ");
        scanf("%d", &respuesta);

    } while (respuesta != 0); // Itera hasta que no se deban realizar mas tranferencias
    
}


//-----------FUNCION 6

// Busca una tarea por su id en ambas listas y mostrar su informacion 
void buscarTareaID(Nodo* L1, Nodo* L2){
    int id;

    printf("\n---MOSTRAR TAREA------\n ");
    printf("---ID de la tarea a mostrar: \n ");
    scanf("%d", &id);

   // -----Busco en las listas
    //Busco en lista 1

    while (L1 != NULL && L1->T.TareaID != id)
    {  // Mientras la lista no este vacia y la  tarea NO este contenida en la lista l1
        L1 = L1->Siguiente;// Continua avanzando en la lista 
    }
    
    // Si la lista no esta vacia y si hubo coincidencia en el id de alguna tarea
    if (L1 != NULL)
    {
        printf("-Tarea encontrada en la LISTA PENDIENTES-\n");
       // datos de la tarea
        printf("\n>>>TAREA");
        printf("\n-ID: %d ", L1->T.TareaID);
        printf("\n-Descripcion: %s", L1->T.Descripcion);
        printf("\n-Duracion de la tarea: %d", L1->T.Duracion);

    } else
    {   // Busco en lista 2
        while (L2 != NULL && L2->T.TareaID != id)
        { // Mientras la lista no este vacia y la  tarea NO este contenida en la lista l2
            L2 = L2->Siguiente; // Continua avanzando en la lista 
        }

        // Si la lista no esta vacia y si hubo coincidencia en el id de alguna tarea
        if (L2 != NULL)
        { 
            printf("-Tarea encontrada en la LISTA REALIZADAS-\n");

             // datos de la tarea
            printf("\n>>>TAREA");
            printf("\n-ID: %d ", L2->T.TareaID);
            printf("\n-Descripcion: %s", L2->T.Descripcion);
            printf("\n-Duracion de la tarea: %d", L2->T.Duracion);
        } else
        { // No se encontro la tarea con el id
            printf("\n--No existe una tarea con el ID ingresado en ninguna de las dos listas.--\n");
        }
    } 
}


//-----------FUNCION 7
// Busca la tarea por una palabra clave entre las descripciones de las tareas de ambas listas

void buscarTareaPalabraClave(Nodo* L1, Nodo* L2){
    char *palabra;

    //4)
    char *buff = (char *)malloc(sizeof(char)*100); //Variable auxiliar y reserva dinámica para almacenar la palabra ingresada 

    printf("\n---MOSTRAR TAREA- PALABRA CLAVE------\n ");
    printf("----Palabra clave a buscar: \n");
    fflush(stdin);
    gets(buff);

     //5)
    palabra = (char *)malloc((strlen(buff)+1)*sizeof(char)); //Reserva dinámica con el tamaño de la palabra calculado con buff (long de la palabra)

    strcpy(palabra, buff); // copia la palabra clave de buff a palabra
    free(buff); //Libera la memoria de la variable auxiliar (4)

    // Busqueda de la palabra clave en la descripcion de las tareas de ambas  listas

    // Busco lista 1 

    // Si la lista no esta vacia y no existe la palabra ingresada en la descripcion de alguna tarea en L1
    while (L1 != NULL && strstr(L1->T.Descripcion, palabra) == NULL)
    {
        L1 = L1->Siguiente; // Avanza de nodo
    }

    //si existe la palabra ingresada en la descripcion de alguna tarea en L1
    if (L1 != NULL)
    { 
        printf("\n----La tarea encontrada en la lista Pendientes-- \n");
        printf("\n>>>TAREA");
        printf("\n-ID: %d ", L1->T.TareaID);
        printf("\n-Descripcion: %s", L1->T.Descripcion);
        printf("\n-Duracion de la tarea: %d", L1->T.Duracion);

    } else
    { // Busco lista 2

        // Si la lista no esta vacia y no existe la palabra ingresada en la descripcion de alguna tarea en L2
        while (L2 != NULL && strstr(L2->T.Descripcion, palabra) == NULL)
        {
            L2 = L2->Siguiente;// avanza nodo
        }

        //si existe la palabra ingresada en la descripcion de alguna tarea en L2
        if (L2 != NULL)
        { 
            printf("\n-----Tarea encontrada a la lista Realizadas-----\n");
            printf("\n>>>TAREA");
            printf("\n-ID: %d ", L2->T.TareaID);
            printf("\n-Descripcion: %s", L2->T.Descripcion);
            printf("\n-Duracion de la tarea: %d", L2->T.Duracion);
        } else
        { // No se encontro la tarea con la palabra clae
            printf("\n--No existe una tarea con la palabra ingresada en ninguna de las dos listas.--\n");
        }
    } 
    free(palabra); //Libero reserva de memoria de la palabra clave (5)
}


//-----------FUNCION 8
// Elimina el primer nodo de la lista si no esta vacia ara que apunte al siguiente nodo 
void eliminarPrimerNodo(Nodo **L){
    // recibe un puntero que apunta al inicio de una lista enlazada 

    if (*L != NULL) // Si la lista apuntada no esta vacia 
    { // Vemos que la lista contiene al menos un nodo la lista
        Nodo *aux = *L; //Puntero auxiliar que apunta al mismo nodo que el untero ingresado *L para conservar la referencia al primer nodo de la lista 

        *L = (*L)->Siguiente; // Modificamos el puntero ingresado para que apunte al siguiente nodo de la lista , eliminando el primer nodo de la lista

        free(aux); // Libero memoria asginada al primer nodo de la lista
        //Libero memoria del nodo eliminado ya que el puntero auxiliar aun apuntaba al primer nodo original antes de que el puntero se actualizada 
    }
}