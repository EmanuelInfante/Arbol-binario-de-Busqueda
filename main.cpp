/* Este programa se basa en la creacion de un arbol binario que cuenta con 5 niveles. Todos los arboles binarios son conocidos por ser bastante utiles
em la informatica, y es por ello que este cuenta con diferentes prototipos de funciones asi como las funcionas de un elemento de arbol. Ademas per-
mite al usuario ingresar los valores del arbol binario de busqueda . Cuenta con un menu con opciones como lo son el numero 1 para construir y 
verificar el arbol binario y 2 para salir del programa. A continuacion se procede con el programa*/
#include <iostream>

//Definimos si estamos en windows o linux para definir funcion d limpiar pantalla
#ifdef WIN32
    #define cls() system("cls");
#else
   #define cls() system("clear");
#endif // WIN32

using namespace std;

//Estructura del árbol
struct NodoArbol
{
    int numero;
    struct NodoArbol *nodoIzquierdo;
    struct NodoArbol *nodoDerecho;
};

//Lista para cantidad de nvl de un árbol
struct ElementosNvlArbol
{
    int nivelActual;
    int cantidadElementos;
    struct ElementosNvlArbol *siguiente;
};

//prototipos de funciones
bool menu(struct NodoArbol *&, struct ElementosNvlArbol *&);
void solicitarInsertarValoresNodos(struct NodoArbol *&, struct ElementosNvlArbol *&cantidaElementos);
void insertarNodo(struct NodoArbol *&, struct ElementosNvlArbol *&, int);
struct NodoArbol *crearNodo(int);
int cantidadNivelesArbol(struct NodoArbol *, struct ElementosNvlArbol *&, int);
//Funciones de ElementosNvlArbol
void anadirCantidadElemento(struct ElementosNvlArbol *&, int);
bool existeNivel(struct ElementosNvlArbol *, int);
void crearNivel(struct ElementosNvlArbol *&, int);
void mostrarElementosNiveles(struct ElementosNvlArbol *);
//Función para elminiar memoria dinámica de las estructuras
void eliminarMemoriaDinamicaArbol(struct NodoArbol *);
void eliminarMemoriaDinamicaCantidadElementos(struct ElementosNvlArbol *);

int main()
{
    cout << "Bienvenido al programa para realizar arboles Binarios de Busqueda" << endl << endl;

    //Creamos el puntero árbol apuntando a NULL
    struct NodoArbol *arbol;
    struct ElementosNvlArbol *cantidadElementos;

    //Llamamos al menú de forma infinita y le damos el valor de NULL
    do
    {
        arbol = NULL;
        cantidadElementos = NULL;
    }while(menu(arbol, cantidadElementos));

    return 0;
}


bool menu(struct NodoArbol *&arbol, struct ElementosNvlArbol *&cantidadElementos)
{
    /*Menú que se encarga de administrar las opciones del programa*/
    cout << endl << "1) Construir y verificar árbol binario" << endl << "2) Salir" << endl;
    cout << "Ingrese el número de la opción correspondiente: ";

    int opcion, cantidadNiveles;
    cin >> opcion;

    cin.ignore();

    cls();

    switch(opcion)
    {
    case 1:
        //Creamos el árbol y verificamos si tiene la cantidad de elementos correspondientes
        solicitarInsertarValoresNodos(arbol, cantidadElementos);
        cantidadNiveles = cantidadNivelesArbol(arbol, cantidadElementos, 0) + 1;

        if(cantidadNiveles >= 5)
        {
            //En caso de que el árbol tenga una cantidad de niveles válida, entonces:
            cout << "La cantidad de nvl que tiene el arbol es: " << cantidadNiveles << endl;
            mostrarElementosNiveles(cantidadElementos);
        }
        else
        {
            //Si la cantidad de niveles no es válida advertimos al usuario y salimos
            cls();
            cout << "El arbol introducido no es válido, ingrese uno valido (mas de 5 nvl)" << endl;
        }

        eliminarMemoriaDinamicaArbol(arbol);
        eliminarMemoriaDinamicaCantidadElementos(cantidadElementos);
        break;
    case 2:
        return false;
        break;
    default:
        cls();
        cout << "Opción no válida, intente de nuevo" << endl << endl;
        break;
    }

    return true;
}


void solicitarInsertarValoresNodos(struct NodoArbol *&arbol, struct ElementosNvlArbol *&cantidaElementos)
{
    /*Función que solitita todos los valores del arbol al usuario y lo crea*/
    cout << "INGRESAR VALORES ÁRBOL BINARIO"  <<endl << endl;
    cout << "Solo se podra construir un árbol binario de busqueda de por mínimo 5 niveles" << endl;
    cout << "Ingrese los números correspondientes al árbol binario, separados por un espacio (ejemplo:10 11 12 13 14 15): ";

    string valores;
    getline(cin, valores);

    cls();

    string valorAux = "";

    //Recorremos los valores ingresados por el usuario y creamos el arbol
    for(int i = 0; i <= int(valores.length()); i++)
    {

        //si es un espacio vacío lo ignoramos y llamamos a insertar Nodo
        if(valores[i] == ' ' || i == int(valores.length()))
        {
            insertarNodo(arbol, cantidaElementos, stoi(valorAux));
            valorAux = "";
            continue;
        }

        //Le damos los valores a el nuevo nodo, hasta que sea un espacio vacío
        valorAux += valores[i];

    }

    cout << "Valores agregados correctamente" << endl << endl;
}


//---------------------------FUNCIONES DE NODOARBOL-------------------------------//
void insertarNodo(struct NodoArbol *&raiz, struct ElementosNvlArbol *&cantidaElementos, int nuevoValor)
{
    /*Insertamos en el árbol un nuevo nodo, este nodo puede ser la raíz del arbol completo
    Esta función es recursiva, ya que puede llamar a ella multiples veces si es necesario*/
    if(raiz == NULL)
    {
        //Si el árbol no tiene agregado ningún nodo
        struct NodoArbol *nuevoNodo = crearNodo(nuevoValor);
        raiz = nuevoNodo;
    }
    else
    {
        //Si el árbol tiene algún nodo agregado

        /*Revisamos si el valor del  dato a gregar se debe ingresar en el hijo izquierdo o el hijo derecho
        Y volvemos a llamar a esta función*/
        if(raiz ->numero < nuevoValor)
        {
            insertarNodo(raiz ->nodoDerecho, cantidaElementos, nuevoValor);
        }else
        {
            insertarNodo(raiz ->nodoIzquierdo, cantidaElementos, nuevoValor);
        }
    }
}


struct NodoArbol *crearNodo(int nuevoValor)
{
    /*Creamos el nuevo nodo del arbol, los dos punteros que poseen obtienen el valor de NULL, esto
    porque no están apuntando todavia a ningun valor*/

    struct NodoArbol *nuevoNodo = new NodoArbol();

    nuevoNodo ->numero = nuevoValor;
    nuevoNodo ->nodoDerecho = NULL;
    nuevoNodo ->nodoIzquierdo = NULL;

    return nuevoNodo;
}


int cantidadNivelesArbol(struct NodoArbol *raiz, struct ElementosNvlArbol *&cantidadElementos, int nivelActual)
{
    /*Función que retorna el tamaño de un árbol, recorriendo recursivamente el mismo
    ademas modifica una lista enlazada que cntiene la cantidad de elementos por Nvl*/
    int nivelesIzq = 0, nivelesDer = 0;

    //Añadimos un contador para cada uno de los niveles, y en cada vuelta de la recursividad le sumamos a ese contador
    anadirCantidadElemento(cantidadElementos, nivelActual);

    /*Si la raíz es == NULL entonces el arbol esta vacío*/
    if(raiz == NULL)
    {
        return 0;
    }

    cout << "Se agrego el valor " << raiz ->numero << " en el nivel " << nivelActual << endl;

    //Si el arbol no tine más hijos retorna el nvl en el que se encuentra actualmente la hoja
    if(raiz ->nodoDerecho == NULL && raiz ->nodoIzquierdo == NULL)
        return nivelActual;

    //Si existen mas nvl, primero llama los niveles de la izquierda, y luego los de la derecha
    if(raiz ->nodoIzquierdo != NULL)
        nivelesIzq = cantidadNivelesArbol(raiz ->nodoIzquierdo, cantidadElementos, nivelActual + 1);

    if(raiz ->nodoDerecho != NULL)
        nivelesDer = cantidadNivelesArbol(raiz ->nodoDerecho, cantidadElementos, nivelActual + 1);

    /*Determinamos si hay mas nvl por la izquierda o por la derecha, y retornamos dicho valor para que el padre
    haga el mismo proceso*/
    if(nivelesIzq > nivelesDer)
        return nivelesIzq;
    return nivelesDer;
}


//---------------------------FUNCIONES DE ELEMENTOSNVLARBOL-------------------------------//
void anadirCantidadElemento(struct ElementosNvlArbol *&cantidadElementos, int nivelActual)
{
    /*Función que se encarga de sumar en 1 el contador e lementos de un nivel determinado, si el nivel no existe lo crea*/
    struct ElementosNvlArbol *auxCantidadElementos = cantidadElementos;

    //Revisa si el nivel actual no existe, lo crea y le añade un contador
    if(existeNivel(cantidadElementos, nivelActual) == false)
    {
        crearNivel(cantidadElementos, nivelActual);
        return;
    }

    //Recorremos la lista, y le añadims 1 al contador correspondiente
    while(auxCantidadElementos != NULL)
    {
        if(auxCantidadElementos ->nivelActual == nivelActual)
        {
            auxCantidadElementos ->cantidadElementos += 1;
            return;
        }
        auxCantidadElementos = auxCantidadElementos ->siguiente;
    }
}


bool existeNivel(struct ElementosNvlArbol *cantidadElementos, int nivelActual)
{
    /*Función que revisa si un nivel existe, y retorna true si existe, false en caso de que no*/
    while(cantidadElementos != NULL)
    {
        if(cantidadElementos ->nivelActual == nivelActual)
            return true;
        cantidadElementos = cantidadElementos ->siguiente;
    }

    return false;
}


void crearNivel(struct ElementosNvlArbol *&cantidadElementos, int nivelActual)
{
    /*Función que recibe puntero de estructura de cantidad elementos y crea un nivel y lo añade a la lista*/
    struct ElementosNvlArbol *nuevoNivel = new ElementosNvlArbol;
    nuevoNivel ->nivelActual = nivelActual;
    nuevoNivel ->cantidadElementos = 1;
    nuevoNivel ->siguiente = NULL;

    if(cantidadElementos == NULL)
    {
        cantidadElementos = nuevoNivel;
        return;
    }

    struct ElementosNvlArbol *auxCantidadElementos = cantidadElementos;

    /*Recorremos el ciclo hasta llegar al nvl nuevo, siempre sera la última posición, ya que para agregar un
    nuevo nivel es necesario que el nivel anterior exista*/
    while(auxCantidadElementos ->siguiente != NULL) { auxCantidadElementos = auxCantidadElementos ->siguiente; }

    //Agregamos el nuevo nivel a la lista
    auxCantidadElementos ->siguiente = nuevoNivel;

}


void mostrarElementosNiveles(struct ElementosNvlArbol *cantidadElementos)
{
    /*Función que imprime por pantalla la cantidad de elementos por cada nivel, esto recorriendo la
    estructra de ElementosNvlArbol*/

    cout << endl << endl << "CANTIDAD DE VALORES EN CADA NIVEL: " << endl;

    while(cantidadElementos != NULL)
    {
        cout << "Nivel " << cantidadElementos ->nivelActual << " contiene " << cantidadElementos ->cantidadElementos;
        cout << " elementos" << endl;
        cantidadElementos = cantidadElementos ->siguiente;
    }
}


void eliminarMemoriaDinamicaArbol(struct NodoArbol *arbol)
{
    /*Función que se encarga de eliminar toda la memoría dinamica que pueda existir en el arbol binario*/
    if(arbol ->nodoIzquierdo != NULL)
    {
        eliminarMemoriaDinamicaArbol(arbol ->nodoIzquierdo);
    }

    if(arbol ->nodoDerecho != NULL)
    {
        eliminarMemoriaDinamicaArbol(arbol ->nodoDerecho);
    }
    if(arbol != NULL)
        delete arbol;
}


void eliminarMemoriaDinamicaCantidadElementos(struct ElementosNvlArbol *cantidadElementos)
{
    /*Función que se encarga de eliminar toda la memoría dinámica de la lista de cantidad de elementos del árbol*/
    if(cantidadElementos ->siguiente != NULL)
    {
        eliminarMemoriaDinamicaCantidadElementos(cantidadElementos ->siguiente);
    }
    if(cantidadElementos != NULL)
        delete cantidadElementos;
}
