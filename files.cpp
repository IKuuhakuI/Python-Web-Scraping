/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao:
 *
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "files.h"
#include "product.h"

using namespace std;

void fileWrite (string fileName, vector <Product*> productList) {
	ofstream myFile (fileName);

	for (size_t index = 0; index < productList.size(); index++) {

		myFile << (*(productList[index])).getName() << ","
		       << (*(productList[index])).getPrice() << ","
		       << (*(productList[index])).getURL() << ","
		       << (*(productList[index])).getStore() << endl;
	}

	myFile.close();
} 
