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

#include <Python.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <typeinfo>

#include "menu.h"
#include "store.h"
#include "scraping.h"
#include "algorithms.h"


using namespace std;

int main (int argc, char* argv[]) {
	Py_Initialize();
	
	Menu menu;

	Store amazon("Amazon");
	Store submarino("Subamarino");

	vector<Store> storesList{amazon, submarino}; 	
	vector<vector<string>> productInfoFromEachStore;

	char option;

	do {
		menu.showMenu();
		menu.setSelectedOption();

		option = menu.getSelectedOption();	
		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch (option) {

			case '0':
				cout << "Saindo do programa..." << endl;
			break;
		
	
			case '1':{
				vector<vector<string>> amazonData, submarinoData;
				float minPrice, maxPrice;
				string product;				

				cout << "________________________________________________" << endl;
				cout << "		Buscando por produto" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Informe o nome do produto que deseja pesquisar: ";
				getline(cin, product);
				
				cout << endl << endl;

				cout << "Informe a faixa de preço do produto procurado" << endl;
				cout << "Menor preço da faixa: ";
				cin >> minPrice;
				cout << "Maior preço da faixa: ";
				cin >> maxPrice;

				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
			
				cout << endl << endl;

				char auxiliar[product.length()];
				char *productFinal = auxiliar;
				strToConstCharList(product, productFinal);

				amazonData = getAmazonData(productFinal, minPrice, maxPrice);
				productInfoFromEachStore.push_back(amazonData[0]);				

				submarinoData = getAmazonData(productFinal, minPrice, maxPrice);
				productInfoFromEachStore.push_back(amazonData[1]);				

				float currentPrice = strToFloat(productInfoFromEachStore[0][1]);
				size_t index = 0;
				for (size_t cont = 0; cont < productInfoFromEachStore.size(); cont++) {
					
					if(currentPrice < strToFloat(productInfoFromEachStore[cont][1])) 
						currentPrice = currentPrice;
						
					else {
						currentPrice = strToFloat(productInfoFromEachStore[cont][1]);
						index = cont;
					}
				}

				/*cout << currentPrice << " INDEX ->" << index << endl;*/

				/*for(size_t cont = 0; cont < amazonData.size(); cont++) {
					cout << amazonData[cont][0] << endl;
					cout << amazonData[cont][1] << endl;
					cout << amazonData[cont][2] << endl;
					cout << amazonData[cont][3] << endl << endl;
				}*/

				/*for(size_t cont = 0; cont < productInfoFromEachStore.size(); cont++) {
					cout << productInfoFromEachStore[cont][0] << endl;
					cout << productInfoFromEachStore[cont][1] << endl;
					cout << productInfoFromEachStore[cont][2] << endl;
					cout << productInfoFromEachStore[cont][3] << endl;
				}*/
				
				/*cout << "Caso deseje, adicione uma palavra-chave para auxiliar na busca" << endl;
				cout << "(Opcional, caso não seja necessario, aperte enter)" << endl;
				cout << "Palavra-chave: ";
				getline(cin, keyWord);
				cout << endl;
				*/
				
				cout << endl << "-------------------------------------------------" << endl;
				cout << "		Resultado da Busca" << endl;			
				cout << "-------------------------------------------------" << endl;
				cout << "Loja: " << storesList[index].name << endl;
				cout << "Nome do produto: " << productInfoFromEachStore[index][0] << endl;
				cout << "Preço: R$: "   << productInfoFromEachStore[index][1] <<endl; 
				cout << "Link para pagina: " << completeURL(productInfoFromEachStore[index]) <<endl; 
				cout << "_________________________________________________" << endl;

				cout << endl << endl;
			}
			break;
			

		/*	case '2': {
				cout << "________________________________________________" << endl;
				cout << "		Lista de produtos" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Qual loja deseja selecionar para busca?: ";
				getline(cin, product);

				cout << "Informe o nome do produto que deseja pesquisar: ";
				getline(cin, product);
				
				cout << endl << endl;
                                
				cout << "Informe a faixa de preço do produto procurado" << endl;
                                cout << "Menor preço da faixa: ";
                                cin >> minPrice;
                                cout << "Maior preço da faixa: ";
                                cin >> maxPrice;

                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
                                cout << endl << endl;
			
			break;
*/

			case '3':
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


			case '4':{
				int store1, store2;
				float minPrice, maxPrice;
				string product;
	
				cout << "______________________________________________________" << endl;
				cout << "      Comparação de preço entre duas lojas" << endl;
				cout << "------------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storesList.size(); cont++) {
					cout << cont + 1 << ": " << storesList[cont].name << endl;
				}
				cout << "------------------------------------------------------" << endl;
				
				cout << "Indique o produto a ser buscado: ";
				getline(cin, product);
				cout << endl;			
	
				cout << "Informe a faixa de preço do produto procurado" << endl;
				cout << "Menor preço da faixa: ";
				cin >> minPrice;
				cout << "Maior preço da faixa: ";
				cin >> maxPrice;
				cout << endl;			
	
				cout << "Selecione a primeira loja (Indique o numero correspondente): ";
				cin >> store1;
				cout << "Selecione a segunda loja (Indique o numero correspondente): ";
				cin >> store2;
				cout << endl;

				char auxiliar[product.length()];
                                char *productFinal = auxiliar;
                                strToConstCharList(product, productFinal);
                           /*   amazonData = getAmazonData(productFinal, minPrice, maxPrice);
                                productInfoFromEachStore.push_back(amazonData[0]);

                                submarinoData = getAmazonData(productFinal, minPrice, maxPrice);
                                productInfoFromEachStore.push_back(amazonData[1]);
*/
				cout << setw(20) << storesList[store1 - 1].name << setw(30) << storesList[store2 - 1].name << endl;
				cout << setw(20) << store1 << setw(30) << store1 << endl;
				cout << setw(20) << store1/*PRECO1*/ << setw(30) << store1/*PRECO2*/ << endl;
				cout << setw(20) << store1/*URL1*/  << setw(30) << store1/*URL2*/ << endl;
			}
			break; 


			case '5': {

			}
			break;


			default:
				cout << "Opção invalida\n\n" << endl;		
		}
		
	} while (option != '0');

	Py_Finalize();
	
	return 0;
}
