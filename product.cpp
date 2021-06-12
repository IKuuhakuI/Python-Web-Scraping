/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Implementacao da class Product
 *
*/ 

#include <string>

#include "product.h"
#include "algorithms.h"

using namespace std;

Product::Product(string productName, string productPrice, string productUrl, string storeName) {
	name = productName;
	store = storeName;


	price = strToFloat(productPrice);

	url = productUrl;
}

string Product::getStore() {
	return store;
}

string Product::getName() {
	return name;
}

float Product::getPrice() {
	return price;
}

string Product::getURL() {
	return url;
}
