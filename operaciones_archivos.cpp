#include <iostream>
using namespace std;
#include <stdio.h>

struct Persona {
	int dni;
	char nombre[30 + 1];
};

int read(FILE* f) {
	int reg;
	fread(&reg, sizeof(int), 1, f);
	return reg;
}

Persona readPersona(FILE* f) {
	Persona reg;
	fread(&reg, sizeof(Persona), 1, f);
	return reg;
}

void write(FILE* f, int v) {
	fwrite(&v, sizeof(int), 1, f);
}

void write(FILE* f, Persona v) {
	fwrite(&v, sizeof(Persona), 1, f);
}

int filePos(FILE* f) {
	long posFisicaActual = ftell(f);
	int posicionLogicaActual = posFisicaActual / sizeof(int);
	return posicionLogicaActual;
}

int filePosPersona(FILE* f) {
	long posFisicaActual = ftell(f);
	int posicionLogicaActual = posFisicaActual / sizeof(Persona);
	return posicionLogicaActual;
}

void seek(FILE* f, int n) {
	int posFisica = n * sizeof(int);
	fseek(f, posFisica, SEEK_SET);
}

void seekPersona(FILE* f, int n) {
	int posFisica = n * sizeof(Persona);
	fseek(f, posFisica, SEEK_SET);
}

int fileSize(FILE* f) {
	int posActual = filePos(f);
	fseek(f, 0, SEEK_END);
	int cantRegistros = filePos(f);
	seek(f, posActual);
	return cantRegistros;
}

// busqueda secuencial
// devuelve la posición logica del registro buscado o -1 si no lo encuentra
int buscar(FILE* f, int clave) {
	int posActual = filePos(f); // guardo la posicion actual para devolverla al mismo estado al final

	seek(f, 0); //me voy al principio para empezar buscar
	int pos = -1;
	int reg = read(f);
	while (!feof(f) && pos == -1) {
		if (reg == clave) {
			pos = filePos(f) - 1; // xq al leer la posición quedó en el proximo registro
		}
		reg = read(f);
	}

	seek(f, posActual); // recupero la posición que estaba parado antes de usar la función
	return pos;
}

int buscarPersona(FILE* f, int dni) {
	int posActual = filePos(f);

	seek(f, 0);
	int pos = -1;
	Persona reg = readPersona(f);
	while (!feof(f) && pos == -1) {
		if (reg.dni == dni) {
			pos = filePos(f) - 1;
		}
		reg = readPersona(f);
	}

	seek(f, posActual);
	return pos;
}

// devuelve la posición logica del registro buscado o -1 si no lo encuentra
int busquedaBinaria(FILE* f, int v) {
	int posActual = filePos(f); // guardo la posicion actual para devolverla al mismo estado al final

	int pos = -1;
	int ini = 0; //empieza en el registro 0
	int fin = fileSize(f) - 1;

	while(pos == -1 /* todavía no lo encontré */ && ini <= fin /* todavía no se cruzaron los índices */) {
		int medio = (ini + fin) / 2;
		seek(f, medio); //necesito pararme 1ro
		int reg = read(f); //leo inmediatamente despues
		if (reg == v) {
			pos = medio;
		} else {
			if (reg > v) {
				fin = medio - 1;
			} else {
				ini = medio + 1;
			}
		}
	}

	seek(f, posActual); // recupero la posición que estaba parado antes de usar la función
	return pos;
}

int main() {

	FILE* archivo = fopen("ejemplo.dat", "wb+");
	write(archivo, 4);
	int x = read(archivo);

	//obtengo la posicion logica actual
	int pos = filePos(archivo);

	//voy al registro de la posicion logica 8 del archivo
	seek(archivo, 8);

	int cantRegs = fileSize(archivo);

	return 0;
}
