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
#include <iomanip>

#include "menu.h"
#include "store.h"

using namespace std;

int main () {
	
	Menu menu;

	Store amazon("Amazon");

	vector<Store> storesList{amazon}; 	

	string product;
	char option;

	do {
		menu.showMenu();
		menu.setSelectedOption();

		option = menu.getSelectedOption();	

		switch (option) {
			case '0':
				cout << "Saindo do programa..." << endl;
			break;
			
			case '1':
				cout << "________________________________________________" << endl;
				cout << "		Buscando por produto" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Informe o nome do produto que deseja pesquisar: ";
				getline(cin, product);
				
				for(size_t cont = 0; cont < storesList.size(); cont ++) { 
					cout << "-------------------------------------------------" << endl;
					cout << "Loja: " << storesList[cont].name << endl;
					cout << "Nome do produto: " << product << endl;
					cout << "Preço: R$: " << endl; /*AQUUUUUUUUUUUUI*/
					cout << "Link para pagina: " << endl; /*AQUIIIIIIIIIIIIIIII*/
					cout << "_________________________________________________" << endl;
				}
			break;
			
			case '2':
				char option1;

				cout << "________________________________________________" << endl;
				cout << "		Configurar Lojas" << endl;
				cout << "------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storesList.size(); cont++) {

					if (storesList[cont].isSelected() == true) {
						cout << "[X] " << storesList[cont].name << endl;
					}
					else {
						cout << "[ ] " << storesList[cont].name << endl;
					}
				}

				cout << "------------------------------------------------" << endl;
				cout << "1: Adicionar loja" << endl;
				cout << "2: Remover loja" << endl;
				cout << "3: Voltar" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Indique a opção selecionada: ";
				cin >> option1;
				cout << "\n\n";
					
				switch(option1) {
					case '1': {
						cout << "------------------------------------------------" << endl;
						cout << "Lojas não selecionadas" << endl;
						cout << "------------------------------------------------" << endl;
						
						bool exist = false;
						int option2;
							
						for(size_t cont = 0; cont < storesList.size(); cont++) {
							if (storesList[cont].isSelected() == false) {
								cout << cont + 1 << ": " << storesList[cont].name << endl;
								exist = true;
							}
						}
						
						if(exist == false) {
							cout << "Não há lojas disponiveis. Todas as lojas já foram selecionadas. \n\n" << endl;
						}
						else {
							cout << "0: Cancelar operação" << endl;
							cout << "------------------------------------------------" << endl;
							cout << "Qual loja deseja adicionar? (Indique o numero correspondente): ";
							cin >> option2;

							if(option2 != 0) {
								storesList[option2 - 1].changeSelection();
								cout << "\nLoja adicionada com sucesso!!\n" << endl << endl;
							}
							else
								cout << endl << endl;
						}
					}
					break;

					case '2': {
						cout << "------------------------------------------------" << endl;
						cout << "Lojas já selecionadas" << endl;
						cout << "------------------------------------------------" << endl;
						
						bool exist = false;
						int option2;
							
						for(size_t cont = 0; cont < storesList.size(); cont++) {
							if (storesList[cont].isSelected() == true) {
								cout << cont + 1 << ": " << storesList[cont].name << endl;
								exist = true;
							}
						}
				
						if(exist == false)
							cout << "Não há lojas disponiveis. Todas já foram removidas" << endl;
						else {
							cout << "0: Cancelar operação" << endl;
							cout << "------------------------------------------------" << endl;
							cout << "Qual loja deseja remover? (Indique o numero correspondente): ";
							cin >> option2;

							if(option2 != 0) {
								storesList[option2 - 1].changeSelection();
								cout << "\nLoja removida com sucesso!!\n" << endl << endl;
							}
							else
								cout << endl << endl;
						}
					}
					break;

					case '3':
					break;

					default:
						cout << "Opção invalida" << endl << endl;
				}				

			break;

			case '3':
				int store1, store2;

				cout << "______________________________________________________" << endl;
				cout << "      Comparação de preço entre duas lojas" << endl;
				cout << "------------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storesList.size(); cont++) {
					cout << cont + 1 << ": " << storesList[cont].name << endl;
				}
				cout << "------------------------------------------------------" << endl;
				
				cout << "Selecione a primeira loja (Indique o numero correspondente): ";
				cin >> store1;
				cout << "Selecione a segunda loja (Indique o numero correspondente): ";
				cin >> store2;

				cout << setw(20) << storesList[store1 - 1].name << setw(30) << storesList[store2 - 1].name << endl;



			break; 

			default:
				cout << "Opção invalida" << endl;		
		}
		
	} while (option != '0');

}
