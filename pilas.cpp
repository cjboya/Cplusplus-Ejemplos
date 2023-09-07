#include <iostream>
using namespace std;
#include <stdio.h>

struct Alumno {
	char nombre[50 + 1];
	int edad;
	int legajo;
};

struct NodoPila {
	Alumno info;
	NodoPila* sgte;
};

void inicializar(NodoPila*& raiz) {
	raiz = NULL;
}

bool estaVacia(NodoPila* raiz) {
	return raiz == NULL;
}

void push(NodoPila*& raiz, Alumno v) {
	NodoPila* ptr = new NodoPila();
	ptr -> info = v;
	ptr -> sgte = raiz;
	raiz = ptr;
}

Alumno pop(NodoPila*& raiz) {
	NodoPila* ptr = raiz;
	Alumno info = ptr -> info;
	raiz = ptr -> sgte;
	delete ptr;
	return info;
}

int main() {

	NodoPila* raizPila;
	inicializar(raizPila); //raizPila = NULL;

	FILE* arch = fopen("alumnos.dat", "rb+");

	Alumno alumno;
	fread(&alumno, sizeof(Alumno), 1, arch);

	while(!feof(arch)) {
		push(raizPila, alumno);
		fread(&alumno, sizeof(Alumno), 1, arch);
	}

	fclose(arch);

	while(!estaVacia(raizPila)) {
		Alumno info = pop(raizPila);
		cout << info.nombre << info.edad << info.legajo << endl;
	}

	return 0;
}
