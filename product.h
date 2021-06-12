/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2 
 * Decricao: Prototipo da class Produto
 *
*/

#pragma once

#include <string>
#include <vector>

using namespace std;

class Product {
	public:
		Product (string, string, string, string);
		
		string getName();
		string getStore();
		float getPrice();
		string getURL();

	private:
		string name, store, url;
		float price;
};
