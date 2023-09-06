#include <iostream>
using namespace std;

/*
	Operaciones con arrays - eliminar, ordenar, insertarOrdenadoArchivo
*/


struct Alumno {
	char nombre[50 + 1];
	int edad;
	int legajo;
};

struct NodoLista {
	Alumno info;
	NodoLista* sgte;
};

void inicializar(NodoLista*& raiz) {
	raiz = NULL;
}


// estaVacia / isEmpty
bool estaVacia(NodoLista* raiz) {
	return raiz == NULL;
}


// push / meter / insertaAdelante / insertaPrimero
void push(NodoLista*& raiz, Alumno v) {
	NodoLista* ptr = new NodoLista();
	ptr -> info = v;
	ptr -> sgte = raiz;
	raiz = ptr;
}

// pop / sacar / suprimePrimero / eliminarPrimerNodo
Alumno pop(NodoLista*& raiz) {
	NodoLista* ptr = raiz;
	Alumno info = ptr -> info;
	raiz = ptr -> sgte;
	delete ptr;
	return info;
}

// buscar / buscaNodo
// retorna la dirección de memoria del nodo encontrado, o NULL en caso de que no esté
NodoLista* buscar(NodoLista* raiz, int legajo) {
	NodoLista* pAux = raiz;
	NodoLista* pAlNodoEncontrado = NULL;

	while(pAux != NULL && pAlNodoEncontrado == NULL) { // mientras no termine la lista y no haya encontrado el dato aún
		if(pAux -> info.legajo == legajo) {
			pAlNodoEncontrado = pAux;
		}
		pAux = pAux -> sgte;
	}

	return pAlNodoEncontrado;
}

void liberar(NodoLista*& raiz) {
	while(!estaVacia(raiz)) {
		pop(raiz);
	}
}

// devuelve la dirección de memoria del nuevo nodo insertado
NodoLista* insertarOrdenado(NodoLista*& raiz, Alumno v) {
	NodoLista* ptr = new NodoLista();
	ptr -> info = v;

	NodoLista* pAct = raiz;
	NodoLista* pAnt = NULL;
	while(pAct != NULL && v.legajo > pAct -> info.legajo) {
		pAnt = pAct;
		pAct = pAct -> sgte;
	}

	ptr -> sgte = pAct;

	if (pAnt == NULL) {
		raiz = ptr; // la raiz debe apuntar al nodo nuevo ya que va adelante de todos
	} else {
		pAnt -> sgte = ptr; // el nodo queda después de un nodo existente
	}

	return ptr;
}

NodoLista* agregarAlFinal(NodoLista*& raiz, Alumno v) {
	NodoLista* ptr = new NodoLista();
	ptr -> info = v;
	ptr -> sgte = NULL; // como se que es el último nodo le pongo NULL al sgte

	NodoLista* pAct = raiz;
	NodoLista* pAnt = NULL;
	while(pAct != NULL) { // recorro siempre hasta el final
		pAnt = pAct;
		pAct = pAct -> sgte;
	}

	if (pAnt == NULL) {
		raiz = ptr; // la raiz debe apuntar al nodo nuevo ya que va adelante de todos
	} else {
		pAnt -> sgte = ptr; // el nodo queda después de un nodo existente
	}

	return ptr;
}

void eliminar(NodoLista*& raiz, int legajo) {
	NodoLista* pAct = raiz;
	NodoLista* pAnt = NULL;
	while(pAct != NULL && legajo != pAct -> info.legajo) { // avanzo mientras no lo encuentro
		pAnt = pAct;
		pAct = pAct -> sgte;
	}

	if (legajo == pAct -> info.legajo) { // si encuentro lo que busco, tengo que eliminarlo
		if (pAnt == NULL) {
			raiz = pAct -> sgte; // enlazo la raiz con el siguiente del que voy a eliminar
		} else {
			pAnt -> sgte = pAct -> sgte; // enlazo el nodo anterior con el siguiente del que voy a eliminar
		}
		delete pAct; //borro el nodo requerido
	}
}

// buscaEInsertaOrdenado / insertarSinRepetir
// devuelve el puntero al nodo de donde lo encontré o de donde lo inserté
NodoLista* buscaEInsertaOrdenado(NodoLista*& raiz, Alumno v, bool& enc) {
	NodoLista* ptr = buscar(raiz, v.legajo);

	if(ptr == NULL) {
		ptr = insertarOrdenado(raiz, v); // como no lo encontré debo insertarlo
		enc = false;
	} else {
		enc = true;
	}

	return ptr;
}

// buscaEInsertaAlPrincipio / insertarAlPrincipioSinRepetir
// devuelve el puntero al nodo de donde lo encontré o de donde lo inserté
NodoLista* buscaEInsertaAlPrincipio(NodoLista*& raiz, Alumno v, bool& enc) {
	NodoLista* ptr = buscar(raiz, v.legajo);

	if(ptr == NULL) {
		push(raiz, v); // como no lo encontré debo insertarlo
		ptr = raiz; // el push siempre iserta el elemento al principio, o sea, en la raiz
		enc = false;
	} else {
		enc = true;
	}

	return ptr;
}

void ordenar(NodoLista*& raiz) {
	NodoLista* raizAux;
	inicializar(raizAux); // raizAux = NULL

	while(!estaVacia(raiz)) {
		Alumno info = pop(raiz); // saco el nodo de la lista original
		insertarOrdenado(raizAux, info);
	}

	raiz = raizAux; // la raiz original termina apuntando a la de la nueva lista ordenada
}

int main() {
	return 0;
}
