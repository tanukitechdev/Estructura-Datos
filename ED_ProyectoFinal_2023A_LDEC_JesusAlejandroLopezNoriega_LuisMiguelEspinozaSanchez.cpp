// *************************************************
// Fecha: Lunes 15 de Mayo 2023                    *
// Autores: Jesus Alejandro López Noriega          *
//          Luis Miguel Espinoza Sanchez           *
// Proyecto final LDEC                             *
// Objetivo: LDEC Congreso                         *
// *************************************************


// Librerias
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include<ctime>
#include<chrono>
#include <windows.h>
using namespace std;

// TDA

struct congreso{

  // Nombre del congreso
  char nombre[30];

  // Descripcion del congreso
  char descripcion[80];

  // Nombre del Congresista
  char congresista[30];

  // Nombre del organizador del congreso
  char organizador[30];

  //Ubicacion del congreso
  char ubicacion[50];

  // Fecha de inicio del congreso
  char fechaInicio[11];

  // Fecha de finalizacion del congreso
  char fechaFin[11];

  // Duracion del congreso (En minutos)
  int duracion;

  // Lugares/Capacidad de asistentes
  int capacidadMax;

  // El congreso es virtual?
  bool esVirtual;

  // Apuntadores
  congreso * siguiente;
  congreso * anterior;
};

struct congreso * apCongreso = NULL;

// Prototipos

void menu(void);
void insertar(void);
void eliminar(void);
void busquedaCadena(void);
void ordenamiento(void);
void mayuscula(char[]);
void consultar(void);
void buscarDato(void);
void guardarArchivo(void);
void consultarArchivo(void);
void gotoxy(int, int);
bool validadorFecha(char[]);

int main() {

    // Funciones para cambiar el color del texto de la consola (Libreria Windows.h)
    HANDLE console_color;
    // Color de la consola
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);

    // P es el color.
    SetConsoleTextAttribute(console_color, 2);

    int opc;
    do{
        menu();
        cin >> opc;
        switch(opc){
        case 1:
            insertar();
            break;
        case 2:
            eliminar();
            break;
        case 3:
            consultar();
            break;
        case 4:
            buscarDato();
            break;
        case 5:
            busquedaCadena();
            break;
        case 6:
            guardarArchivo();
            break;
        case 7:
            consultarArchivo();
            break;
        case 8:
            ordenamiento();
            break;
        case 0:
            cout<<"Seleccionaste salir!"<<endl;
            break;
        default:
            cout<<"La opcion no es valida >;("<<endl;
            break;
        }
        system("pause");
    }while(opc != 0);

    return 0;
}



//Menu
void menu(void){

    system("cls");

    /* Hora local (+2 Librerias y +3 funciones
     * ya que usamos Chrono para obtener el reloj del sistema y Ctime para darle un formato de fecha */

    // Funcion system_clock::now (Es para obtener el reloj del sistema en un punto especifico)
    auto fecha = std::chrono::system_clock::now();

    // Funcion to_time_t (Convierte el tiempo de finalización (end) en un formato legible de tipo time_t)
    time_t fechaActual = std::chrono::system_clock::to_time_t(fecha);

    /* Funcion Ctime (convierte el valor time_t en una cadena de caracteres que representa la fecha y hora
        local en formato legible) */
    gotoxy(34,0); cout << "Fecha Local: " << ctime(&fechaActual) << endl;

    // Logo

    cout<<"   _____ ____  _   _  _____                       _    _ _____   _____ \n"
          "  / ____/ __ \\| \\ | |/ ____|                     | |  | |  __ \\ / ____|\n"
          " | |   | |  | |  \\| | |    _   _  ___ ___  __ _  | |  | | |  | | |  __ \n"
          " | |   | |  | | . ` | |   | | | |/ __/ _ \\/ _` | | |  | | |  | | | |_ |\n"
          " | |___| |__| | |\\  | |___| |_| | (_|  __/ (_| | | |__| | |__| | |__| |\n"
          "  \\_____\\____/|_| \\_|\\_____\\__,_|\\___\\___|\\__,_|  \\____/|_____/ \\_____|\n"
          "                                                                       " <<endl;
    cout<<endl;

    cout << "Bienvenido al sistema de ConCUCEA, seleccione una opcion para continuar: " << endl;
    cout<<"~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" <<endl;
    cout<<"*  1) Dar de alta un congreso                                             *" <<endl;
    cout<<"~  2) Dar de baja un congreso                                             ~" <<endl;
    cout<<"*  3) Consultar congresos                                                 *" <<endl;
    cout<<"~  4) Buscar congreso por dato                                            ~" <<endl;
    cout<<"*  5) Buscar congreso por nombre                                          *" <<endl;
    cout<<"~  6) Guardar congresos registrados en archivo                            ~" <<endl;
    cout<<"*  7) Consultar datos del congreso en archivo                             *" <<endl;
    cout<<"~  8) Ordenar congresos                                                   ~" <<endl;
    cout<<"*  0) Salir                                                               *" <<endl;
    cout<<"~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" <<endl;
    cout<< endl;
    cout<<"Ingresa una opcion -->";

}
// Insercion de nodos
void insertar(void){
    // Declarar apuntador
    congreso * nuevo;

    // Reservar la memoria
    nuevo = new(congreso);

    // Validar el apuntador
    if (nuevo == NULL){
        cout << "No se tiene memoria suficiente para registrar un nuevo congreso" << endl;
        return;
    }

    // Solicitar y guardar los datos del nuevo congreso

    cout << "Ingrese los datos del congreso a registrar" << endl;
    cin.ignore();

    cout << "Nombre del congreso: ";
    cin.getline(nuevo -> nombre, 30, '\n');

    cout << "Descripcion del congreso: ";
    cin.getline(nuevo -> descripcion, 80, '\n');

    cout << "Nombre del congresista: ";
    cin.getline(nuevo -> congresista, 30, '\n');

    cout << "Nombre del organizador del congreso: ";
    cin.getline(nuevo -> organizador, 30, '\n');

    cout << "Lugar en que se realizara el congreso: ";
    cin.getline(nuevo -> ubicacion, 50, '\n');

    cout << "Fecha de inicio del congreso (DD/MM/AAAA): ";
    cin.getline(nuevo -> fechaInicio, 11, '\n');
    if (validadorFecha(nuevo -> fechaInicio) == 0){
        do{
            cout << "La fecha es invalida" << endl;
            cout << "Ingrese una fecha valida de inicio (DD/MM/AAAA):";
            cin.getline(nuevo -> fechaInicio, 11, '\n');
        } while (validadorFecha(nuevo -> fechaInicio) != 1);

    }

    cout << "Fecha de fin del congreso (DD/MM/AAAA): ";
    cin.getline(nuevo -> fechaFin, 11, '\n');
    if (validadorFecha(nuevo -> fechaFin) == 0){
        do{
            cout << "La fecha es invalida" << endl;
            cout << "Ingrese una fecha valida de inicio (DD/MM/AAAA):";
            cin.getline(nuevo -> fechaFin, 11, '\n');
        } while (validadorFecha(nuevo -> fechaFin) != 1);

    }

    cout << "Duracion aproximada del congreso (En minutos): ";
    cin >> nuevo -> duracion;

    // Validacion para que no exista tiempo "Negativo" en la duracion del congreso.
    if(nuevo -> duracion < 0){

        do{
            cout << "La duracion del congreso no es valida! Ingresa una duracion nuevamente" << endl;
            cout << "Duracion aproximada del congreso (En minutos): ";
            cin >> nuevo -> duracion;

        } while(nuevo -> duracion < 0);
    }

    cout << "Capacidad maxima de asistentes al congreso: ";
    cin >> nuevo -> capacidadMax;

    // Misma validacion dado que no podriamos registrar una capacidad maxima negativa
    if(nuevo -> capacidadMax < 0){
        do{
            cout << "La capacidad maxima no es valida! Ingresa una capacidad nuevamente" << endl;
            cout << "Capacidad maxima de asistentes al congreso: ";
            cin >> nuevo -> capacidadMax;

        } while(nuevo -> capacidadMax < 0);
    }

    cout << "El congreso es virtual? (1. SI o 0. NO): ";
        cin >> nuevo -> esVirtual;

    // Agregarlo a la LDEC

    // Caso A) Lista vacia
    if (apCongreso == NULL){

        nuevo -> siguiente = nuevo;
        nuevo -> anterior = nuevo;

        apCongreso = nuevo;
        cout << "Nuevo congreso registrado exitosamente" << endl;
        return;
    }

    // Caso B) 1 solo Nodo
    if (apCongreso -> siguiente == apCongreso){

        nuevo -> siguiente = apCongreso;
        nuevo -> anterior = apCongreso;

        apCongreso -> siguiente = nuevo;
        apCongreso -> anterior = nuevo;

        cout << "Nuevo congreso registrado exitosamente" << endl;
        return;
    }

    // Caso C) Mas de 1 Nodo
    nuevo -> siguiente = apCongreso -> siguiente;
    nuevo -> anterior = apCongreso;

    apCongreso -> siguiente -> anterior = nuevo;
    apCongreso -> siguiente = nuevo;

    cout << "Nuevo congreso registrado exitosamente" << endl;
    return;
}

// Eliminacion de nodos
void eliminar(void){

    // Declarar variables
    congreso * copia = apCongreso;
    int respuesta;

    // Validar lista vacia
    if (apCongreso == NULL){
        cout << " No se tienen pedidos registrados" << endl;
        return;
    }

    do {
        cout << "Congreso a eliminar: " << endl;
        cout << endl;
        cout << "===================================================================="<< endl;
        cout << "Nombre del congreso: " << copia -> nombre << endl;
        cout << "Descripcion del congreso: " << copia -> descripcion << endl;
        cout << "Nombre del congresista: " << copia -> congresista << endl;
        cout << "Nombre del organizador del congreso: " << copia -> organizador << endl;
        cout << "Lugar en que se realizara el congreso: " << copia -> ubicacion << endl;
        cout << "Fecha de inicio del congreso (DD/MM/AAAA): " << copia -> fechaInicio << endl;
        cout << "Fecha de fin del congreso (DD/MM/AAAA): " << copia -> fechaFin << endl;
        cout << "Duracion aproximada del congreso (En minutos): " << copia -> duracion << endl;
        cout << "Capacidad maxima de asistentes al congreso: " << copia -> capacidadMax << endl;
        cout << "El congreso es virtual? (1. SI o 0. NO): " << copia -> esVirtual << endl;
        cout << "====================================================================" << endl;

        cout << "\nEstas seguro de eliminarlo? 1. Si y 0. No: ";
        cin >> respuesta;

        if (respuesta == 1){
            // 1 Solo nodo
            if (copia -> siguiente == copia){
                delete(copia);
                apCongreso = NULL;
                cout << "La orden ha sido eliminada" << endl;
                return;
            }

            // 2 o mas nodos
            apCongreso = copia -> anterior; // Posicionarlo 1 antes de lo que quiero borrar
            apCongreso -> siguiente = copia -> siguiente;
            copia -> siguiente -> anterior = apCongreso;
            delete(copia);
            cout << "\nEl congreso ha sido eliminado correctamente!" << endl;
            return;
        }
        copia = copia -> siguiente;
    } while (copia != apCongreso);
    return;
}

// Funcion que hace mayuscula todo dentro de una cadena
void mayuscula(char cadena[]){
    int i = 0;
    while(cadena[i] != '\0'){
        cadena[i] = toupper(cadena[i]);
        i++;
    }
    return;
}

// Busqueda por tipo de dato Cadena
void busquedaCadena(void){
    // Declarar variables
    congreso * copia = apCongreso;
    char nomCongresoBuscar[30], copiaNombreCongreso[30];

    // Validar
    if (copia == NULL){
        cout << "No se tienen equipos registrados" << endl;
        return;
    }

    // Solicitar el nombre del equipo a buscar
    cout << "Ingresa el nombre del congreso a buscar ";
    cin.ignore();
    cin.getline(nomCongresoBuscar, 30, '\n');
    mayuscula(nomCongresoBuscar);

    do {
        strcpy(copiaNombreCongreso, copia -> nombre);
        mayuscula(copiaNombreCongreso);

        if (strcmp(copiaNombreCongreso, nomCongresoBuscar) == 0){

            cout << "=========================================================================" << endl;
            cout << "| Nombre del congreso: " << copia -> nombre                                << endl;
            cout << "| Descripcion del congreso: " << copia -> descripcion                      << endl;
            cout << "| Nombre del congresista: " << copia -> congresista                        << endl;
            cout << "| Nombre del organizador del congreso: " << copia -> organizador           << endl;
            cout << "| Lugar en que se realizara el congreso: " << copia -> ubicacion           << endl;
            cout << "| Fecha de inicio del congreso (DD/MM/AAAA): " << copia -> fechaInicio     << endl;
            cout << "| Fecha de fin del congreso (DD/MM/AAAA): " << copia -> fechaFin           << endl;
            cout << "| Duracion aproximada del congreso (En minutos): " << copia -> duracion    << endl;
            cout << "| Capacidad maxima de asistentes al congreso: " << copia -> capacidadMax   << endl;
            cout << "| El congreso es virtual? (1. SI o 0. NO): " << copia -> esVirtual         << endl;
            cout << "=========================================================================" << endl;
            return;
        }
        copia = copia -> siguiente;
    } while (copia != apCongreso);

    cout << "\nEl congreso que busca no existe bajo ese nombre o no esta registrado" << endl;
    return;
}

// Metodo de ordenamiento metodo burbuja
void ordenamiento(void){

    // Variables para recorrer la lista
    congreso * actual = apCongreso;
    congreso * siguiente = NULL;
    bool cambio = true;

    // Verificar lista vacía o con un solo nodo
    if (apCongreso == NULL || apCongreso -> siguiente == apCongreso){
        return;
    }

    // Recorrer la lista
    while(cambio){

        cambio = false;
        actual = apCongreso;

        while(actual -> siguiente != apCongreso){
            siguiente = actual -> siguiente;

            // Comparar el campo capacidadMax de los nodos actual y siguiente
            if(actual -> capacidadMax > siguiente -> capacidadMax){

                // Intercambiar los nodos
                siguiente -> anterior = actual -> anterior;
                if (actual -> anterior != NULL){
                    actual -> anterior -> siguiente = siguiente;
                }
                actual -> siguiente = siguiente -> siguiente;
                siguiente -> siguiente -> anterior = actual;
                siguiente -> siguiente = actual;
                actual -> anterior = siguiente;
                if (apCongreso == actual){
                    apCongreso = siguiente;
                }
                cambio = true;

            } else {
                actual = actual -> siguiente;
            }
        }
    }
    cout << "Congresos ordenados por capacidad maxima, vaya a la opción CONSULTAR" << endl;
    return;
}

//Consultar lista
void consultar(void){
    //Declarar apuntador
    congreso *apCopia = apCongreso;

    //Validar lista vacia
    if(apCongreso == NULL){
        cout<<"No hay congresos registrados actualmente :c"<<endl;
        return;
    }//if - vacia

    //Mostrar todos los congresos
    system("cls");
        cout << "                      ~*~ CONGRESOS REGISTRADOS ^-^ ~*~                   " << endl;
        cout << "==========================================================================" << endl;
    do {

            cout << "==========================================================================" << endl;
            cout << "| Nombre del congreso: " << apCopia -> nombre                               << endl;
            cout << "| Descripcion del congreso: " << apCopia -> descripcion                     << endl;
            cout << "| Nombre del congresista: " << apCopia -> congresista                       << endl;
            cout << "| Nombre del organizador del congreso: " << apCopia -> organizador          << endl;
            cout << "| Lugar en que se realizara el congreso: " << apCopia -> ubicacion          << endl;
            cout << "| Fecha de inicio del congreso (DD/MM/AAAA): " << apCopia -> fechaInicio    << endl;
            cout << "| Fecha de fin del congreso (DD/MM/AAAA): " << apCopia -> fechaFin          << endl;
            cout << "| Duracion aproximada del congreso (En minutos): " << apCopia -> duracion   << endl;
            cout << "| Capacidad maxima de asistentes al congreso: " << apCopia -> capacidadMax  << endl;
            cout << "| ¿El congreso es virtual? (1. SI o 0. NO): " << apCopia -> esVirtual       << endl;
            cout << "==========================================================================" << endl;
            cout << endl;

        apCopia = apCopia -> siguiente;
    } while (apCopia != apCongreso);
}

//Buscar dato
void buscarDato(void){

    //Declarar apuntador
    congreso *apCopia = apCongreso;

    //Variables
    int opc, dato;

    //Validar lista vacia
    if(apCongreso == NULL){
        cout<<"No hay congresos registrados aun!! "<<endl;
        return;
    }//if - vacia

    //Mostrar congresos
    cout<<"Selecciona la opcion para buscar un congreso"<<endl;
    cout<<"1) Aforo maximo "<<endl;
    cout<<"2) Duracion en minutos "<<endl;
    cin >> opc;

    if(opc == 1){
    cout<<"Ingresa la capacidad maxima del congreso a buscar -->";
    cin >> dato;
    }
    else{
        cout<<"Ingresa la duracion en minutos del congreso a buscar -->";
        cin >> dato;
    }

    do{
        if(dato == apCopia->capacidadMax || dato == apCopia->duracion){
            cout << "==========================================================================" << endl;
            cout << "| Nombre del congreso: " << apCopia -> nombre                               << endl;
            cout << "| Descripcion del congreso: " << apCopia -> descripcion                     << endl;
            cout << "| Nombre del congresista: " << apCopia -> congresista                       << endl;
            cout << "| Nombre del organizador del congreso: " << apCopia -> organizador          << endl;
            cout << "| Lugar en que se realizara el congreso: " << apCopia -> ubicacion          << endl;
            cout << "| Fecha de inicio del congreso (DD/MM/AAAA): " << apCopia -> fechaInicio    << endl;
            cout << "| Fecha de fin del congreso (DD/MM/AAAA): " << apCopia -> fechaFin          << endl;
            cout << "| Duracion aproximada del congreso (En minutos): " << apCopia -> duracion   << endl;
            cout << "| Capacidad maxima de asistentes al congreso: " << apCopia -> capacidadMax  << endl;
            cout << "| ¿El congreso es virtual? (1. SI o 0. NO): " << apCopia -> esVirtual       << endl;
            cout << "==========================================================================" << endl;
            cout << endl;
        }
        apCopia = apCopia->siguiente;
    }while(apCongreso != apCopia);
    return;
}

//Guardar archivo
void guardarArchivo(void){
    //Declarar apuntador
    congreso *apCopia = apCongreso;

    //Validar lista vacia
    if(apCongreso == NULL){
        cout<<"No hay congresos registrados actualmente"<<endl;
        return;
    }//if - vacia

    ofstream apArchivo;    // 2) Crear un DESCRIPTOR de archivo

    cout << "Hola estamos creando el archivo CongresoCONCUCEA.txt" << endl;
    cout << endl;

    // 3) Crear y Abrir archivo
	apArchivo.open("CongresoCONCUCEA.txt", ios_base::out);

    // 4) Validar el descriptor del archivo
    if ( ! apArchivo ) {
          cout << "Problema al abrir archivo --> datos.txt" <<endl;
          return;
    }

     // Leer los datos del usuario, todo lo que quiero guardar

    // 5) Trabajar con el archivo
    do {
        apArchivo << "============================================================================" << endl;
        apArchivo << "| Nombre del congreso: " << apCopia -> nombre                                 << endl;
        apArchivo << "| Descripcion del congreso: " << apCopia -> descripcion                       << endl;
        apArchivo << "| Nombre del congresista: " << apCopia -> congresista                         << endl;
        apArchivo << "| Nombre del organizador del congreso: " << apCopia -> organizador            << endl;
        apArchivo << "| Lugar en que se realizara el congreso: " << apCopia -> ubicacion            << endl;
        apArchivo << "| Fecha de inicio del congreso (DD/MM/AAAA): " << apCopia -> fechaInicio      << endl;
        apArchivo << "| Fecha de fin del congreso (DD/MM/AAAA): " << apCopia -> fechaFin            << endl;
        apArchivo << "| Duracion aproximada del congreso (En minutos): " << apCopia -> duracion     << endl;
        apArchivo << "| Capacidad maxima de asistentes al congreso: " << apCopia -> capacidadMax    << endl;
        apArchivo << "| El congreso es virtual? (1. SI o 0. NO): " << apCopia -> esVirtual          << endl;
        apArchivo << "============================================================================" << endl;
        apArchivo << endl;
        apCopia = apCopia -> siguiente;
    } while (apCopia != apCongreso);

	// 6) Cerrar el archivo
    apArchivo.close();

    cout << "El archivo ha sido generado con éxito :D " << endl;

}

//Consultar archivo
void consultarArchivo(void){
    //Declarar apuntador
    congreso *apCopia = apCongreso;

    //Validar lista vacia
    if(apCongreso == NULL){
        cout<<"No hay congresos registrados actualmente"<<endl;
        return;
    }//if - vacia

	ifstream apArchivo;     // Descriptor del archivo para Lectura
	string linea;

	apArchivo.open("CongresoCONCUCEA.txt");
	if ( ! apArchivo.is_open( )  )   {
       	cout << "Problema al abrir archivo --> CongresoCONCUCEA.txt" <<endl;
     	return;
  	} // if

    while ( ! apArchivo.eof( ) )  {
   	    getline(apArchivo,linea);
   	    cout << linea << endl;
	} // while

    apArchivo.close();
}

/* Esta es una funcion para acomodar el cursor en una parte especifica de la pantalla y usa funciones de windows.h
   pero solo se contara como una funcion puesto que es sacada de internet dado que no se incluye en ninguna libreria
   como tal pero es conocida */
void gotoxy(int x,int y){
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

// Funcion para chequear que la fecha sea valida
/* Esta funcion a su vez usa varias otras funciones que no vimos en clase como:
    .length(): Para obtener el tamaño de un string dado que creo que nunca usamos string en clase
    .substr(): Basicamente para solo recuperar una parte de un string
    stoi(): Para convertir a INT los substrings que tienen la fecha
    Todo esto se podria haber solucionado trabajando en primer lugar la fecha con string...pues si pero
    lo hecho hecho esta y asi se usaban funciones nuevas Jeje.
    */
bool validadorFecha(char fechaCompleta[]){

    string fecha = fechaCompleta;

    if (fecha.length() != 10) {
        cout << "Fecha no válida. Debe tener exactamente 10 caracteres en el formato DD/MM/AAAA." << endl;
        return 0;
    }
    int dia = stoi(fecha.substr(0, 2));
    int mes = stoi(fecha.substr(3, 2));
    int anio = stoi(fecha.substr(6, 4));
    if (dia < 1 || dia > 31) {
        return 0;
    }
    if (mes < 1 || mes > 12) {
        return 0;
    }
    if (anio <= 0) {
        return 0;
    }

    return 1;
}
