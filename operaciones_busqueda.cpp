#include <iostream>
using namespace std;
#include <string.h>


// Operaciones con arrays: busquedaBinaria, buscaEInsertaOrdenado (insertarSinRepetir), buscaYAgrega (agregarSinRepetir)


struct Persona {
	int dni;
	char nombre[25 + 1];
};

void inicializarVector(int& len) {
	len = 0;
}

void agregar(int arr[], int& len, int v) {
	arr[len] = v;
	len = len + 1;
}

int buscar(int arr[], int len, int v) {
	int pos = -1;
	int i = 0;
	while(pos == -1 && i <= len - 1) {
		if(arr[i] == v) {
			pos = i;
		}
		i = i + 1;
	}
	return pos;
}

int insertarOrdenado(int arr[], int& len, int v) {
	int i = len;
	while (i > 0 && v < arr[i - 1]) {
		arr[i] = arr[i - 1];
		i = i - 1;
	}
	arr[i] = v;
	len = len + 1;
	return i;
}

// retorna la posicion del array en el que encuentra el elemento, o -1 si no lo encuentra
int busquedaBinaria(int arr[], int len, int v, bool& enc) {
	int pos = -1;
	enc = false;
	int ini = 0;
	int fin = len - 1;

	while(!enc /* todavía no lo encontré */ && ini <= fin /* todavía no se cruzaron los índices */) {
		int medio = (ini + fin) / 2;
		if (arr[medio] == v) {
			pos = medio;
			enc = true;
		} else {
			if (arr[medio] > v) {
				fin = medio - 1;
			} else {
				ini = medio + 1;
			}
		}
	}

	return pos;
}

int busquedaBinaria(Persona arr[], int len, int dni, bool& enc) {
	int pos = -1;
	enc = false;
	int ini = 0;
	int fin = len - 1;

	while(!enc && ini <= fin) {
		int medio = (ini + fin) / 2;
		if (arr[medio].dni == dni) {
			pos = medio;
			enc = true;
		} else {
			if (arr[medio].dni > dni) {
				fin = medio - 1;
			} else {
				ini = medio + 1;
			}
		}
	}

	return pos;
}

int busquedaBinaria(Persona arr[], int len, char nombre[25 + 1], bool& enc) {
	int pos = -1;
	enc = false;
	int ini = 0;
	int fin = len - 1;

	while(!enc && ini <= fin) {
		int medio = (ini + fin) / 2;
		if (strcmp(arr[medio].nombre, nombre) == 0) {
			pos = medio;
			enc = true;
		} else {
			if (strcmp(arr[medio].nombre, nombre) > 0) {
				fin = medio - 1;
			} else {
				ini = medio + 1;
			}
		}
	}

	return pos;
}

// insertarSinRepetir
// devuelve la posición en que se encontró o se insertó el valor
int buscaEInsertaOrdenado(int arr[], int& len, int v, bool& enc) {
	int pos = busquedaBinaria(arr, len, v, enc);
	if (pos == -1) { // es lo mismo poner !enc
		pos = insertarOrdenado(arr, len, v);
	}
	return pos;
}

// agregarSinRepetir
// devuelve la posición en que se encontró o se insertó el valor
int buscaYAgrega(int arr[], int& len, int v, bool& enc) {
	int pos = buscar(arr, len, v);
	if (pos == -1) {
		agregar(arr, len, v);
		pos = len - 1; //se agregó el elemento en la última posición útil de mi array
		enc = false;
	} else {
		enc = true;
	}
	return pos;
}

int main() {

	int numeros[10];
	int lenN;
	inicializarVector(lenN);

	agregar(numeros, lenN, 1);
	agregar(numeros, lenN, 4);
	agregar(numeros, lenN, 7);
	agregar(numeros, lenN, 8);
	agregar(numeros, lenN, 10);
	agregar(numeros, lenN, 12);
	agregar(numeros, lenN, 14);

	bool enc;
	int pos = busquedaBinaria(numeros, lenN, 7, enc);
	cout << "el 7 esta en la posición " << pos << endl;

	pos = busquedaBinaria(numeros, lenN, 13, enc);
	if (pos == -1) {
		cout <<  "el 13 no está en el array" << endl;
	}

	pos = buscaEInsertaOrdenado(numeros, lenN, 8, enc);
	if (enc) {
		cout <<  "el 8 estaba en la posición " << pos << endl;
	} else {
		cout <<  "el 8 se cargó en la posición " << pos << endl;
	}

	pos = buscaEInsertaOrdenado(numeros, lenN, 20, enc);
	if (enc) {
		cout <<  "el 20 estaba en la posición " << pos << endl;
	} else {
		cout <<  "el 20 se cargó en la posición " << pos << endl;
	}

	return 0;
}
