/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Decricao: Implementacao das funcoes relacionadas a struct Store
*/ 

#include "store.h"

Store::Store(string storeName, bool status) {
	name =  storeName;
	selected = status;
}

bool Store::isSelected() {
	return selected;
}

void Store::changeSelection() {
	if(selected == true) {
		selected = false;
	}

	else {
		selected = true;
	}
}


