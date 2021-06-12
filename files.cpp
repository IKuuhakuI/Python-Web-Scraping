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
#include <algorithm>

#include "files.h"
#include "product.h"

using namespace std;

void fileWrite (string fileName, vector <Product*> productList) {
	ofstream myFile (fileName);

	for (size_t index = 0; index < productList.size(); index++) {

		string name = (*(productList[index])).getName();
		replace(name.begin(), name.end(), ',', '.'); 

		myFile << name << ","
		       << (*(productList[index])).getPrice() << ","
		       << (*(productList[index])).getURL() << ","
		       << (*(productList[index])).getStore() << endl;
	}

	myFile.close();
}

void fileRead (string fileName, vector <Product*> &productList) {
	ifstream myFile (fileName);	

	string currentLine;

	while (getline(myFile, currentLine)) {
		int startName = 0;
		int endName, startPrice, endPrice;
		int startUrl, endUrl, startStore;
		int endStore = currentLine.size() - 1;

		int current = 1;
		size_t index = 0;

		while (index < currentLine.size() && current < 4) {
			if (currentLine[index] == ',') {
				if (current == 1) {
					endName = index;
					startPrice = index + 1;
				} else if (current == 2) {
					endPrice = index;
					startUrl = index + 1;
				} else if (current == 3) {
					endUrl = index;
					startStore = index + 1;
				} 

				current ++;
			}
			index++;
		}

		string name = currentLine.substr (startName, endName - startName);
		string price = currentLine.substr (startPrice, endPrice - startPrice);
		string url = currentLine.substr (startUrl, endUrl - startUrl);
		string store = currentLine.substr (startStore, endStore - startStore + 1);
		
		Product* newProduct = new Product (name, price, url, store);

		productList.push_back (newProduct);
	} 

	myFile.close();
} 
