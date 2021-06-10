/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Programa principal
 *
*/ 

#include <iostream>
#include <vector>
#include <string>

#include "menu.h"

using namespace std;

int main () {
	
	Menu menu;

	string product;
	char option;

	do {
		menu.showMenu();
		menu.setSelectedOption();

		option = menu.getSelectedOption();	

		switch (option) {
			case '0':
				cout << "Saindo do programa" << endl;
			break;
			
			case '1':
				cout << "________________________________________________" << endl;
				cout << "		Buscando por produto" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Informe o nome do produto que deseja pesquisar: "
				getline(product);
				
				for(size_t cont = 0; cont < sizeStore; cont ++) { 
					cout << "-------------------------------------------------"
					cout << "Loja: " /*AQUUUUUUUUUI*/
					cout << "Nome do produto: " << product << endl;
					cout << "Preço: R$: " << endl; /*AQUUUUUUUUUUUUI*/
					cout << "Link para pagina: " << endl; /*AQUIIIIIIIIIIIIIIII*/
					cout << "_________________________________________________" << endl;
				}
			break;
			
			case '2':
				cout << "________________________________________________" << endl;
				cout << "		Configurar Lojas" << endl;
				cout << "------------------------------------------------" << endl;
				
				for(size_t cont = 0;
			break;

			case '3': 
				
			break; 

			default:
				cout << "Opção invalida" << endl;		
		}
		
	} while (option != '0');

}
