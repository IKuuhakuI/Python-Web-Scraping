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
#include "product.h"

using namespace std;

int main (int argc, char* argv[]) {

	Py_Initialize();
	
	Menu menu;

	Store amazon("Amazon");
	Store americanas("Americanas");
	Store submarino("Submarino");
	Store mercadoLivre("Mercado Livre");

	vector<Store> storesList{amazon, americanas, submarino, mercadoLivre};

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
				vector<vector<string>> productInfoFromEachStore;
				vector<vector<string>> amazonData, americanasData, submarinoData;
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

				amazonData = getData(productFinal, minPrice, maxPrice, "amazon");
				productInfoFromEachStore.push_back(amazonData[0]);				

				Product* amazonProduct = new Product (amazonData[0][0], amazonData[0][1], amazonData[0][2], amazonData[0][3]);

				//cout << (*amazonProduct).getName() << endl;

				americanasData = getData(productFinal, minPrice, maxPrice, "americanas");
				productInfoFromEachStore.push_back(americanasData[0]);				

				submarinoData = getData(productFinal, minPrice, maxPrice, "submarino");
				productInfoFromEachStore.push_back(submarinoData[0]);				

				float currentPrice;
				bool found = false;
				size_t index = 0;

				for(size_t cont = 0; cont < productInfoFromEachStore.size(); cont++) {
					
					if(storesList[cont].isSelected() == 1 && found == false) {
						currentPrice = strToFloat(productInfoFromEachStore[cont][1]);
						
						found = true;
					}
				}


				for(size_t cont = 0; cont < productInfoFromEachStore.size(); cont++) {
					float comparePrice;

					comparePrice = strToFloat (productInfoFromEachStore[cont][1]);

					if (currentPrice > comparePrice && storesList[cont].isSelected() == true /*&& found == true*/) {
						currentPrice = strToFloat(productInfoFromEachStore[cont][1]);

                                                index = cont;
					}
					
					//else
					//	currentPrice = currentPrice;	
				}
					

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
				
				cout << endl << "-------------------------------------------------" << endl;
				cout << "		Resultado da Busca" << endl;			
				cout << "-------------------------------------------------" << endl;
				cout << "Loja: " << storesList[index].name << endl;
				cout << "Nome do produto: " << productInfoFromEachStore[index][0] << endl;
				cout << "Preço: R$ "   << productInfoFromEachStore[index][1] <<endl; 
				cout << "Link para pagina: " << completeURL(productInfoFromEachStore[index]) <<endl; 
				cout << "_________________________________________________" << endl;

				cout << endl << endl;
			}
			break;
			

			case '2': {
				char option1;
				vector<vector<string>> productInfoFromEachStore, storeData;
				string product;
				float minPrice, maxPrice;
	
				cout << "________________________________________________" << endl;
				cout << "		Lista de produtos" << endl;
				cout << "------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storesList.size(); cont++) {
					cout << cont + 1 << ": " << storesList[cont].name << endl;
				}
	
				cout << "Qual loja deseja selecionar para busca? (Indique pelo numero): ";
				cin >> option1;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				
				cout << endl;

				cout << "Informe o nome do produto que deseja pesquisar: ";
				getline(cin, product);
				
				cout << endl;
                                
				cout << "Informe a faixa de preço do produto procurado" << endl;
                                cout << "Menor preço da faixa: ";
                                cin >> minPrice;
                                cout << "Maior preço da faixa: ";
                                cin >> maxPrice;
				cout << endl;			

                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				char auxiliar[product.length()];
                                char *productFinal = auxiliar;
                                strToConstCharList(product, productFinal);
				
				switch(option1) {
					case '1':
						storeData = getData(productFinal, minPrice, maxPrice, "amazon");
					break;
					case '2':
						storeData = getData(productFinal, minPrice, maxPrice, "americanas");
					break;
					case '3':
						storeData = getData(productFinal, minPrice, maxPrice, "submarino");
					break;
					case '4':
						/*storeData = getData(productFinal, minPrice, maxPrice, "mercado livre");*/
					break;
					default:
						cout << "Opção de loja indisponivel." << endl;

				}

				cout << "\n________________________________________________" << endl;
				cout << "                       LISTA" << endl;
				cout << "------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storeData.size(); cont++) {
					cout << "Nome do produto : " << storeData[cont][0] << endl;
					cout << "Preço: R$ " << storeData[cont][1] << endl;
					cout << "Link para pagina: " << completeURL(storeData[cont]) << endl;
					cout << endl;
				}

				cout << "________________________________________________" << endl;
                                
				cout << endl << endl;
			}	
			break;


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
								cout << storesList[option2 - 1].isSelected() << endl;
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
				vector<vector<string>> productInfoFromEachStore, storeData;
				float minPrice, maxPrice;
				string product;
	
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
				cout << endl;
			
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
				vector<int> stores;
				stores.push_back(store1);
				stores.push_back(store2);

				int optionDW;

				do {
					string price1, price2, product1, product2, url1, url2;						

					cout << "Indique o produto a ser buscado: ";
					getline(cin, product);
					cout << endl;				
				
					cout << "Informe a faixa de preço do produto procurado" << endl;
					cout << "Menor preço da faixa: ";
					cin >> minPrice;
					cout << "Maior preço da faixa: ";
					cin >> maxPrice;
					cout << endl;			

					char auxiliar[product.length()];
					char *productFinal = auxiliar;
					strToConstCharList(product, productFinal);

					for(int cont = 0; cont < 2; cont++) {
						switch(stores[cont]) {
							case 1:{
								storeData = getData(productFinal, minPrice, maxPrice, "amazon");
								productInfoFromEachStore.push_back(storeData[0]);
							}break;
							case 2:{
								storeData = getData(productFinal, minPrice, maxPrice, "americanas");
								productInfoFromEachStore.push_back(storeData[0]);
							}break;
							case 3:{
								storeData = getData(productFinal, minPrice, maxPrice, "submarino");
								productInfoFromEachStore.push_back(storeData[0]);
							}break;
							case 4:{
								/*storeData = getData(productFinal, minPrice, maxPrice, "mercado livre");*/
						
							}break;
							default:
								cout << "Opção de loja indisponivel." << endl;
						}
	
						if(cont == 0) {
							product1 = productInfoFromEachStore[0][0];
                                                        price1 = productInfoFromEachStore[0][1];
                                                        url1 = completeURL(productInfoFromEachStore[0]);
                                                }
                                                else {
                                                        product2 = productInfoFromEachStore[1][0];
                                                        price2 = productInfoFromEachStore[1][1];
                                                        url2 = completeURL(productInfoFromEachStore[1]);
						}
					}
							
					
					cout << "\n------------------------------------------------------" << endl;
					cout <<                         "LOJA 1" << endl;
					cout << "------------------------------------------------------" << endl;
 					cout << storesList[store1 - 1].name << endl; 
                                        cout << product1 << endl;
                                        cout << price1 << endl;
                                        cout << url1 << endl;	

					cout << endl;					

					cout << "------------------------------------------------------" << endl;
					cout <<                         "LOJA 2" << endl;
					cout << "------------------------------------------------------" << endl;
 					cout << storesList[store2 - 1].name << endl; 
                                        cout << product2 << endl;
                                        cout << price2 << endl;
                                        cout << url2 << endl;	
					
					cout << endl;

					cout << "Aperte 0 para sair e 1 para fazer outra busca." << endl;
					cin >> optionDW;						
					
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					
					productInfoFromEachStore.clear();

				} while (optionDW != 0);
				
				cout << endl << endl;

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
