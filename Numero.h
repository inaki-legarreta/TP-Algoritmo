#ifndef NUMERO_H
#define NUMERO_H
struct Numero{
	int valor;
	char color;
};
void inicializarNumero(Numero &n,int valor, char color);
int obtenerValor(Numero n);
char obtenerColor(Numero n);
int obtenerParidad(Numero n);
	
#endif
