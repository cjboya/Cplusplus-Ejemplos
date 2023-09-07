#include <iostream>
using namespace std;
#include <stdio.h>
#include <string.h>

struct Alumno {
	char nombre[50 + 1];
	int edad;
	int legajo;
};

struct Materia {
	int legajo;
	char codMat[5 + 1];
	char nombMat[50 + 1];
};

struct MateriaInscripto {
	char codMat[5 + 1];
};

struct NodoListaMateriasInscripto {
	MateriaInscripto info;
	NodoListaMateriasInscripto* sgte;
};

struct AlumnoMat {
	int legajo;
	char nombre[50 + 1];
	unsigned cantidadMaterias;
	NodoListaMateriasInscripto* raizListaMateriasInscripto;
};

struct NodoListaAlumnoMat {
	AlumnoMat info;
	NodoListaAlumnoMat* sgte;
};

void inicializar(NodoListaAlumnoMat*& raiz) {
	raiz = NULL;
}
void inicializar(NodoListaMateriasInscripto*& raiz) {
	raiz = NULL;
}

NodoListaAlumnoMat* insertarOrdenado(NodoListaAlumnoMat*& raiz, AlumnoMat v) {
	// no es necesario implementar
	// inserta ordenado ASC a partir del legajo del AlumnoMat
	return NULL;
}

NodoListaAlumnoMat* buscar(NodoListaAlumnoMat* raiz, int legajo) {
	// no es necesario implementar
	// busca segun el legajo del AlumnoMat
	return NULL;
}

void push(NodoListaMateriasInscripto*& raiz, MateriaInscripto info) {
	// no es necesario implementar
}

void liberar(NodoListaAlumnoMat*& raiz) {
	// no es necesario implementar
}

void liberar(NodoListaMateriasInscripto*& raiz) {
	// no es necesario implementar
}

int main() {
	NodoListaAlumnoMat* raizListaAlumnoMat;
	inicializar(raizListaAlumnoMat); // raizListaAlumnoMat = NULL;

	// cargo los alumnos en la lista

	FILE* arch = fopen("alumnos.dat", "rb+");

	Alumno regAlumno;
	fread(&regAlumno, sizeof(Alumno), 1, arch);

	while(!feof(arch)) {
		AlumnoMat info;
		info.legajo = regAlumno.legajo;
		strcpy(info.nombre, regAlumno.nombre);
		info.cantidadMaterias = 0; // inicializo en 0
		inicializar(info.raizListaMateriasInscripto); // info.raizListaMateriasInscripto = NULL;

		insertarOrdenado(raizListaAlumnoMat, info);

		fread(&regAlumno, sizeof(Alumno), 1, arch);
	}

	fclose(arch);

	// cargo la cantidad de materias para cada alumno en la lista

	FILE* archM = fopen("materias.dat", "rb+");

	Materia regMat;
	fread(&regMat, sizeof(Materia), 1, archM);

	while(!feof(archM)) {
		NodoListaAlumnoMat* ptr = buscar(raizListaAlumnoMat, regMat.legajo);
		ptr -> info.cantidadMaterias = ptr -> info.cantidadMaterias + 1;

		MateriaInscripto infoMI;
		strcpy(infoMI.codMat, regMat.codMat);
		push(ptr -> info.raizListaMateriasInscripto, infoMI);

		fread(&regMat, sizeof(Materia), 1, archM);
	}

	fclose(archM);

	// mostrar la lista armada

	NodoListaAlumnoMat* pAux = raizListaAlumnoMat;
	while(pAux != NULL) {
		cout << "Legajo: " << pAux -> info.legajo << "| Nombre: " << pAux -> info.nombre << "| Cantidad de materias: " << pAux -> info.cantidadMaterias << endl;
		cout << "Nombre Materias" << endl;

		NodoListaMateriasInscripto* pAux2 = pAux -> info.raizListaMateriasInscripto;
		while(pAux2 != NULL) {
			cout << pAux2 -> info.codMat << endl;

			pAux2 = pAux2 -> sgte;
		}

		pAux = pAux -> sgte;
	}

	// antes de terminar libero la memoria dinámica de lista que ya no necesito
	NodoListaAlumnoMat* pAux3 = raizListaAlumnoMat;
	while(pAux3 != NULL) {
		liberar(pAux3 -> info.raizListaMateriasInscripto);
		pAux3 = pAux3 -> sgte;
	}
	liberar(raizListaAlumnoMat);

	return 0;
}
