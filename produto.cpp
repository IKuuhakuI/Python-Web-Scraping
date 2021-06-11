/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Implementacao da class Produto
 *
*/ 

#include "produto.h"

Produto::Produto(store, product, price, url) {
	storeName = store;
	productName = product;
	productPrice = price;
	productUURL = url;
}

string Produto::getStore() {
	return store;
}

string Produto::getName() {
	return name;
}


float Produto::getPrice() {
	return price;
}

string Produto::getURL() {
	return url;
}
