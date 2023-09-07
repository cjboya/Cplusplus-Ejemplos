#include <iostream>
using namespace std;
#include <stdio.h>

struct Alumno {
	char nombre[50 + 1];
	int edad;
	int legajo;
};

struct NodoCola {
	Alumno info;
	NodoCola* sgte;
};

void inicializar(NodoCola*& p) {
	p = NULL;
}

bool estaVacia(NodoCola* p) {
	return p == NULL;
}

void encolar(NodoCola*& colaFte, NodoCola*& colaFin, Alumno v) {
	NodoCola* ptr = new NodoCola();
	ptr -> info = v;
	ptr -> sgte = NULL;
	if (estaVacia(colaFte)) { // colaFte == NULL
		colaFte = ptr;
	} else {
		colaFin -> sgte = ptr;
	}
	colaFin = ptr;
}

Alumno desencolar(NodoCola*& colaFte, NodoCola*& colaFin) {
	NodoCola* ptr = colaFte;
	Alumno info = ptr -> info;
	colaFte = ptr -> sgte;
	delete ptr;
	if (estaVacia(colaFte)) { // colaFte == NULL
		colaFin = NULL;
	}
	return info;
}

int main() {

	NodoCola* colaFte;
	NodoCola* colaFin;
	inicializar(colaFte); //colaFte = NULL;
	inicializar(colaFin);//colaFin = NULL;

	FILE* arch = fopen("alumnos.dat", "rb+");

	Alumno alumno;
	fread(&alumno, sizeof(Alumno), 1, arch);

	while(!feof(arch)) {
		encolar(colaFte, colaFin, alumno);
		fread(&alumno, sizeof(Alumno), 1, arch);
	}

	fclose(arch);

	while(!estaVacia(colaFte)) {
		Alumno info = desencolar(colaFte, colaFin);
		cout << info.nombre << info.edad << info.legajo << endl;
	}

	return 0;
}
