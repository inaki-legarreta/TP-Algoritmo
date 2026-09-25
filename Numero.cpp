#include "Numero.h"
/*******************************************************
* Función: inicializarNumero
* Parámetros:
*   - Numero &n   : Representa la casilla a inicializar
*   - int valor   : Número asignado al casillero (0 al 36)
*   - char color  : Carácter del color ('R', 'N' o 'V')
* Retorna:
*   - void        : No retorna valor
* Descripción:
*   Asigna el valor y el color pasados por parámetro a los
*   campos internos de la estructura Numero.
*******************************************************/
void inicializarNumero(Numero &n, int valor, char color){
	n.color=color;
	n.valor=valor;
}
	/****************************************************
	* Función: obtenerValor
	* Parámetros:
	* - Numero n : Parámetro fuente del valor a obtener
	* Retorna:
	* - int : Valor asignado en n
	* Descripción:
	* Retorna el valor asignado dentro del parametro n 
	* del tipo Numero previamente asignado.
	****************************************************/
int obtenerValor(Numero n){
	return n.valor;
}
	/****************************************************
	* Función: obtenerColor
	* Parámetros: 
	* - Numero n : Parámetro fuente del color a obtener
	* Retorna:
	* - char : caracter asignado en n
	* Descripción:
	* Retorna el caracter relacionado con el color asignado 
	* dentro del parametro n del tipo Numero previamente 
	* asignado.
	****************************************************/
char obtenerColor(Numero n){
	return n.color;
}
	/****************************************************
	* Función: obtenerParidad
	* Parámetros:
	* - Numero n : Parámetro fuente de la paridad a obtener
	* Retorna:
	* - int : entero relacionado con la paridad del numero 
	* Retorna 0, 1 o 2, si el numero es 0 retorna 0, si el 
	* numero es impar retorna 1, si es par retorna 2.
	****************************************************/
int obtenerParidad(Numero n){
	if((n.valor%2)==0) return 2;
	if(n.valor==0) return 0;
	if((n.valor%2)!=0) return 1;
}
	
