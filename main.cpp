#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "numero.h"

#ifdef _WIN32
#include <windows.h> // Sleep en Windows
#else
#include <unistd.h>  // sleep en Linux/Unix
#endif

#define MAX_JUGADORES 6
#define MAX_RULETA 37
#define MAX_GIROS 1200

using namespace std;

// ---------- DECLARACION DE ESTRUCTURAS ---------- 
struct Apuesta{
	int fichasJugadas;
	int tipoApuesta; // Identificador del tipo de apuesta seleccionada 1-Numero, 2-Color, 3-Par, 4-Impar
	int numeroApostado;
	char colorApostado;
};

struct Jugador {
	string nombre;
	int fichas;
	Apuesta apuestas[MAX_RULETA];
	int tlApuestas;
	int victorias;
	int derrotas;
};

// ---------- DECLARACION DE FUNCIONES ---------- 
void limpiarConsola();
void cargarInterfaz(char &opcion);
void configuracionInicial(int &cantidad_jugadores, Jugador lista_jugadores[MAX_JUGADORES]);
void registroApuestas(int cantidad_jugadores, Jugador lista_jugadores[MAX_JUGADORES]);
void inicializarRuleta(Numero ruleta[MAX_RULETA]);
Numero girarRuleta(Numero ruleta[MAX_RULETA]);

// ---------- FUNCION MAIN ---------- 
int main(){
	srand(time(0));
	
	// ---------- DECLARACION DE VARIABLES ---------- 
	char opcion = '0';
	int cantidad_jugadores;
	Jugador lista_jugadores[MAX_JUGADORES];
	Numero ruleta[MAX_RULETA];
	Numero resultado;
	
	// ---------- LLAMAR FUNCIONES ---------- 
	cargarInterfaz(opcion);
	limpiarConsola();
	configuracionInicial(cantidad_jugadores, lista_jugadores);
	inicializarRuleta(ruleta); //CARGA LA RULETA 
	limpiarConsola();
	registroApuestas(cantidad_jugadores, lista_jugadores);
	resultado=girarRuleta(ruleta);
	limpiarConsola();
	cout << "\n========================================" << endl;
	cout << "SALIO EL " << obtenerValor(resultado) << " (" << obtenerColor(resultado) << ")" << endl;
	cout << "========================================\n" << endl;
	
	cout << "Presione ENTER para continuar...";
	cin.ignore();
	
	return 0;
}
	
	void limpiarConsola(){
		cout << "PROCESANDO";
		
		for (int i = 0; i < 5; i++) {
			cout << "." << flush;
			
#ifdef _WIN32
			Sleep(500);   // 500 ms en Windows
#else
			sleep(1);     // 1 segundo en Linux/Unix
#endif
		}
		
		
		for (int i = 0; i < 50; i++) {
			cout << endl;
		}
	}
		void cargarInterfaz(char &opcion){
			bool sesionActiva = false;
			
			// ---------- TITULO ---------- 
			cout << "La Ruletasca" << endl << "===========================" << endl;
			do {
				// ---------- MENU ---------- 
				cout << "1.- Iniciar nueva sesion de ruleta" << endl
					<<  "2.- Consultar estado de jugadores" << endl
					<<  "3.- Mostrar historial de giros" << endl
					<<  "4.- Mostrar estadisticas de la sesion" << endl
					<<  "5.- Ordenar sesiones segun cantidad de giros" << endl
					<<  "6.- Analizar sesiones historicas" << endl
					<<  "7.- Carga de archivo" << endl
					<<  "X.- Salir de la aplicacion" << endl;
				
				cout << "\nIngrese una opcion: ";
				cin >> opcion;
				
				if (opcion == '1'){
					sesionActiva = true;
				} else {
					cout << "ERROR: Para acceder a esta opcion debes tener una sesion activa!" << endl << endl << endl;
				}
			} while (!sesionActiva);
		}
			
			void configuracionInicial(int &cantidad_jugadores, Jugador lista_jugadores[MAX_JUGADORES]){
				bool error = false;
				// ---------- CANTIDAD DE JUGADORES ----------
				cout << "Registro de Jugadores" << endl << "===========================" << endl;
				do {
					cout << "\nCantidad de participantes (de 2 a 6): ";
					cin >> cantidad_jugadores;
					
					if (cantidad_jugadores >= 2 and cantidad_jugadores <= 6) {
						error = false;
					} else {
						cout << "ERROR: Ingrese una cantidad valida de Jugadores (entre 2 y 6)!" << endl;
						error = true;
					}
				} while (error);
				
				// ---------- LIMPIEZA DE BUFFER PARA USAR GETLINE----------
				cin.ignore();
				for (int i = 0; i<cantidad_jugadores; i++){
					// ---------- INGRESAR NOMBRE DEL JUGADOR----------
					cout << "\n-> Ingrese el nombre del jugador numero " << i+1 << ": ";
					getline(cin, lista_jugadores[i].nombre); 
					// ---------- ASIGNAR CANTIDAD DE FICHAS ----------
					lista_jugadores[i].fichas = 2000;
					lista_jugadores[i].tlApuestas = 0;
					lista_jugadores[i].victorias = 0;
					lista_jugadores[i].derrotas = 0;
					cout << lista_jugadores[i].nombre << " comienza con " << lista_jugadores[i].fichas << " fichas." << endl;
				}
				
				cout << "\nLOS " << cantidad_jugadores << " HAN SIDO REGISTRADOS CON EXITO!" << endl;
			}
				
				void registroApuestas(int cantidad_jugadores, Jugador lista_jugadores[MAX_JUGADORES]){
					bool error = false;
					
					cout << "Recioleccion de apuestas" << endl << "===========================" << endl;
					
					for (int i = 0; i < cantidad_jugadores; i++){
						
						do {
							// ---------- FICHAS QUE APUESTA EL JUGADOR NUMERO i ----------
							cout << "\n->" << lista_jugadores[i].nombre << " ingresa la cantidad de fichas a apostar (" <<  lista_jugadores[i].fichas << ") disponibles: ";
							cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].fichasJugadas;
							
							if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].fichasJugadas > lista_jugadores[i].fichas) {
								cout << "ERROR: Ingrese una cantidad valida!" << endl;
								error = true;
							} else { 
								error = false;
							}
						} while (error);
						
						// ---------- TIPO DE APUESTA DEL JUGADOR NUMERO i ---------- 
						cout << "\n-> Ingrese el tipo de apuesta: "<< endl
							<< "1 - Numero" << endl
							<< "2 - Color" << endl
							<< "3 - Par" << endl
							<< "4 - Impar" << endl << endl;
						
						/*do {    
							cout << "->";
							cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].tipoApuesta;
							
							if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].tipoApuesta >= 1 and lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].tipoApuesta <=4) {
								error = false;
							} else {
								cout << "ERROR: Ingrese una apuesta valida!" << endl;
								error = true;
							}
						} while (error);
						
						// ---------- CONFIRMAR APUESTA DEL JUGADOR i EN FUNCION DE ELECCION ---------- 
						if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].tipoApuesta == 1){
							cout << "Numero a apostar (entre 0 y " << MAX_RULETA << "): ";
							cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].numeroApostado;
						} 
						else if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].tipoApuesta == 2) {
							do{ 
								cout << "Color a apostar (r: ROJO, n: NEGRO): ";
								cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado;
								
								if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado == 'n' || lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado == 'r') {
									error = false;
								} else {
									cout << "ERROR: Ingrese una apuesta valida!" << endl;
									error = true;
								}
							} while (error);
						}*/do{
							cout << "->";
							int posicion=lista_jugadores[i].tlApuestas;
							cin >> lista_jugadores[i].apuestas[posicion].tipoApuesta;
							switch(lista_jugadores[i].apuestas[posicion].tipoApuesta){
							case 1: error=false;
								cout << "Numero a apostar (entre 0 y " << MAX_RULETA-1 << "): ";
							cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].numeroApostado;
							break;
							case 2: do{ 
								cout << "Color a apostar (r: ROJO, n: NEGRO): ";
								cin >> lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado;
								
								if (lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado == 'n' || lista_jugadores[i].apuestas[ lista_jugadores[i].tlApuestas ].colorApostado == 'r') {
									error = false;
								} else {
									cout << "ERROR: Ingrese una apuesta valida!" << endl;
									error = true;
								}
							} while (error);
							error=false;
							break;
							case 3: cout<< "Apostaste a PAR"; 
							error=false;
							break;
							case 4: cout<<"Apostaste a IMPAR";
							error=false;
							break;
							default: cout << "ERROR: Ingrese una apuesta valida!" << endl;
							error = true;
							}}while(error);
						
						// avanzar al siguiente espacio de apuestas
						lista_jugadores[i].tlApuestas++;
						
					}
					
					cout << "NO VA MAS! - Todas las apuestas han sido cargadas con exito." << endl;
					limpiarConsola();
				}
					// FUNCION PARA INICIALIZAR-CREAR LA RULETA CON SUS NUMEROS Y RESPECTIVOS COLORES
					void inicializarRuleta(Numero ruleta[MAX_RULETA]){
						inicializarNumero(ruleta[0],0,'V');
						for(int i=1;i<MAX_RULETA;i++) { 
							inicializarNumero(ruleta[i],i,'N');      //PINTO TODOS LOS NUMEROS NEGROS MENOS EL 0 (VERDE) PARA DESPUES PINTAR SOLO LOS ROJOS
						}
						int rojos[]={1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36}; //LISTA DE ROJOS 
						for(int i=0;i<18;i++) { 
							inicializarNumero(ruleta[rojos[i]],rojos[i],'R');							//PINTO SOLO LOS ROJOS 			  
						}
					}
						Numero girarRuleta(Numero ruleta[MAX_RULETA]){
							int indice= (rand() % MAX_RULETA);
							return ruleta[indice];
						}
						
						
						
