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
#include "files.h"

using namespace std;

int main (int argc, char* argv[]) {

	Py_Initialize();
	
	Menu menu;

	Store *amazon = new Store ("amazon");
	Store *americanas = new Store ("americanas");
	Store *submarino = new Store ("submarino");

	vector<Store*> storesList{amazon, americanas, submarino};

	// Define a precisao para 2 casas decimais
	cout << fixed;
	cout << setprecision(2);

	vector<Product*> wishList;

	fileRead ("wishList.csv", wishList);

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
				// Dados extraidos
				vector<vector<string>> amazonData, americanasData, submarinoData;

				// Faixa de preco
				string strMin, strMax;
				float minPrice, maxPrice;
				string product;				

				cout << "________________________________________________" << endl;
				cout << "		Buscando por produto" << endl;
				cout << "------------------------------------------------" << endl;
				
				bool notEmpty = false;

				//Filtra erro na entrada do nome do produto
				do {
					string tempProduct;
					cout << "Informe o nome do produto que deseja pesquisar: ";
					// Pegar produto
					getline(cin, tempProduct);
						
					int index = checkEmptySpaces (tempProduct);

					if (index != -1) {
						product = tempProduct.substr (index, tempProduct.size() - index);
						notEmpty = true;
					}
				} while (notEmpty == false);

	
				cout << endl << endl;

				bool isValid;
	
				//Filtra entrada dos pre??os
				do {
					isValid = true;

					cout << "Informe a faixa de pre??o do produto procurado" << endl;
					cout << "Menor pre??o da faixa: ";
					cin >> strMin;
					cout << "Maior pre??o da faixa: ";
					cin >> strMax;
					
						try {
							minPrice = stof (strMin);
							maxPrice = stof (strMax);

							if (maxPrice <= minPrice) {
								isValid = false;
							}
						} catch (invalid_argument& e) {
							isValid = false;
						}

						if (!isValid) {
							cout << "Precos invalidos!" << endl;
						}

				} while (!isValid);

				// Limpar o buffer de entrada
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
			
				cout << endl << endl;

				// Passar o nome do produto
		  		char auxiliar[product.length()];
				char *productFinal = auxiliar;
				strToConstCharList(product, productFinal);

				vector <Product*> productList;

				string currentName, currentPrice, currentUrl, currentStore;
	
				// Verifica se as lojas estao selecionadas para busca
				if ((*amazon).isSelected() == true) {
					amazonData = getData(productFinal, minPrice, maxPrice, "amazon");

					if (amazonData.size() > 0) {
						currentName = amazonData[0][0];
						currentPrice = amazonData[0][1];
						currentUrl = amazonData[0][2];
						currentStore = amazonData[0][3];

						currentUrl = completeURL (currentStore, currentUrl);
	
						Product* amazonProduct = new Product (currentName, currentPrice, currentUrl, currentStore);
						productList.push_back(amazonProduct);
					}
				}

				if ((*americanas).isSelected() == true) {
					americanasData = getData(productFinal, minPrice, maxPrice, "americanas");

					if (americanasData.size() > 0) {
						currentName = americanasData[0][0];
						currentPrice = americanasData[0][1];
						currentUrl = americanasData[0][2];
						currentStore = americanasData[0][3];

						currentUrl = completeURL (currentStore, currentUrl);

						Product* americanasProduct = new Product (currentName, currentPrice, currentUrl, currentStore);
						productList.push_back(americanasProduct);				
					}
				}

				if ((*submarino).isSelected() == true) {
					submarinoData = getData(productFinal, minPrice, maxPrice, "submarino");
		
					if (submarinoData.size() > 0) {
						currentName = submarinoData[0][0];
						currentPrice = submarinoData[0][1];
						currentUrl = submarinoData[0][2];
						currentStore = submarinoData[0][3];

						currentUrl = completeURL (currentStore, currentUrl);

						Product* submarinoProduct = new Product (currentName, currentPrice, currentUrl, currentStore);
						productList.push_back(submarinoProduct);
					} 
				}
				
				// Filtra caso nao tenha nenhum elemento na lista	
				if (productList.size() == 0) {
					cout << "Erro: Nenhum produto encontrado" << endl;
				} else {
					float smallestPrice = (*(productList[0])).getPrice();
					size_t smallestIndex = 0;				

					for (size_t index = 1; index < productList.size(); index++) {
						if ((*(productList[index])).getPrice() < smallestPrice) {
							smallestPrice = (*(productList[index])).getPrice();
							smallestIndex = index;
						}
					}
	
					cout << endl << "-------------------------------------------------" << endl;
					cout << "		Resultado da Busca" << endl;			
					cout << "-------------------------------------------------" << endl;
					cout << "Loja: " << (*(productList[smallestIndex])).getStore() << endl;
					cout << "Nome do produto: " << (*(productList[smallestIndex])).getName() << endl;
					cout << "Pre??o: R$ "   << (*(productList[smallestIndex])).getPrice() <<endl; 
					cout << "Link para pagina: " << (*(productList[smallestIndex])).getURL() <<endl; 
					cout << "_________________________________________________" << endl;
					
					string addToWishList;
					bool isSelected = false;

					// Para adicionar produto na wishList
					do {
						cout << "Para adicionar o produto na lista de desejos, digite 1, para sair, digite 0" << endl;

						getline (cin, addToWishList);

						if (addToWishList == "1" or addToWishList == "0") {
							isSelected = true;
						} else {
							cout << "Opcao invaldia" << endl;
						}

					} while (!isSelected);
	
					if (addToWishList == "1") {
						wishList.push_back (productList[smallestIndex]);
						fileWrite ("wishList.csv", wishList);	
					}
					cout << endl << endl;
				}
			}
			break;
				
			case '2': {
					
				char chooseStore;
				vector<vector<string>> productInfoFromEachStore, storeData;
				string product;
				float minPrice, maxPrice;
				string strMin, strMax;
		
				cout << "________________________________________________" << endl;
				cout << "		Lista de produtos" << endl;
				cout << "------------------------------------------------" << endl;
					
				for(size_t cont = 0; cont < storesList.size(); cont++) {
					cout << cont + 1 << ": " << storesList[cont]->name << endl;
				}
		
				cout << "------------------------------------------------" << endl;
				cout << "Qual loja deseja selecionar para busca? (Indique pelo numero): ";
				cin >> chooseStore;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					
				cout << endl;
			
				bool notEmpty = false;

				do {
					string tempProduct;
					cout << "Informe o nome do produto que deseja pesquisar: ";
					getline(cin, tempProduct);
						
					int index = checkEmptySpaces (tempProduct);

					if (index != -1) {
						product = tempProduct.substr (index, tempProduct.size() - index);
						notEmpty = true;
					}
				} while (notEmpty == false);

				cout << endl;
                              
				bool isValid;
	
				do {
					isValid = true;

					cout << "Informe a faixa de pre??o do produto procurado" << endl;
					cout << "Menor pre??o da faixa: ";
					cin >> strMin;
					cout << "Maior pre??o da faixa: ";
					cin >> strMax;
					
						try {
							minPrice = stof (strMin);
							maxPrice = stof (strMax);

							if (maxPrice <= minPrice) {
								isValid = false;
							}
						} catch (invalid_argument& e) {
							isValid = false;
						}

						if (!isValid) {
							cout << "Precos invalidos!" << endl;
						}

						cout << endl;
						
				} while (!isValid);

                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				char auxiliar[product.length()];
                                char *productFinal = auxiliar;
                                strToConstCharList(product, productFinal);
				
				// Verfica qual loja foi escolhida
				switch(chooseStore) {
					case '1':
						storeData = getData(productFinal, minPrice, maxPrice, "amazon");
					break;
					case '2':
						storeData = getData(productFinal, minPrice, maxPrice, "americanas");
					break;
					case '3':
						storeData = getData(productFinal, minPrice, maxPrice, "submarino");
					break;
					default:
						cout << "Op????o de loja indisponivel." << endl;

				}

				vector <Product*> storeVector;

				// Adiciona os produtos no vetor
				for (size_t index = 0; index < storeData.size(); index++) {
					
					string productName = storeData[index][0];
					string productPrice = storeData[index][1];
					string storeName = storeData[index][3];

					string productUrl = completeURL (storeName, storeData[index][2]);

					Product* currentProduct = new Product (productName, productPrice, productUrl, storeName);

					storeVector.push_back (currentProduct);
				}

				cout << "\n________________________________________________" << endl;
				cout << "                       LISTA" << endl;
				cout << "------------------------------------------------" << endl;
				
				for(size_t index = 0; index < storeVector.size(); index++) {
					cout << "ID: [" << index + 1 << "]" << endl; 
					cout << "Nome do produto : " << (*storeVector[index]).getName() << endl;
					cout << "Pre??o: R$ " << (*storeVector[index]).getPrice() << endl;
					cout << "Link para pagina: " << (*storeVector[index]).getURL() << endl;
					cout << endl;
				}

				cout << "________________________________________________" << endl;
                               
				string addToWishList, selectedOption;
				bool isSelected = false;
				

				// Para adicionar produto na wishList
				do {
					cout << "Para adicionar o produto na lista de desejos, digite 1, para sair, digite 0" << endl;

					getline (cin, addToWishList);

					if (addToWishList == "1" or addToWishList == "0") {
						isSelected = true;
					} else {
						cout << "Opcao invaldia" << endl;
					}

				} while (!isSelected);
	
				if (addToWishList == "1") {
					cout << endl;
					cout << "________________________________________________" << endl;
					cout << "Indique o indice do produto para adiciona-lo na lista de desejo ou 0 para sair:" << endl;			
					cin >> selectedOption;
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					if (selectedOption != "0") {
						int addThis;

						try {		
							addThis = stoi (selectedOption);

							if((size_t)addThis <= storeVector.size() && addThis > 0) {
								wishList.push_back(storeVector[addThis - 1]);
								fileWrite ("wishList.csv", wishList);
								cout << "Produto adicionado com sucesso" << endl;

							} else {
								cout << "Entrada invalida" << endl;
							}

						} catch (invalid_argument& e){
							cout << "Entrda invalida" << endl;
						}
					}
	
				}
				
 
				cout << endl << endl;
			}	
			break;


			case '3':
				char selectedOption;

				cout << "________________________________________________" << endl;
				cout << "		Configurar Lojas" << endl;
				cout << "------------------------------------------------" << endl;
			
				// Indica as lojas disponiveis	
				for(size_t cont = 0; cont < storesList.size(); cont++) {

					if ((*(storesList[cont])).isSelected() == true) {
						cout << "[X] " << (*(storesList[cont])).name << endl;
					}
					else {
						cout << "[ ] " << (*(storesList[cont])).name << endl;
					}
				}

				cout << "------------------------------------------------" << endl;
				cout << "1: Adicionar loja" << endl;
				cout << "2: Remover loja" << endl;
				cout << "3: Voltar" << endl;
				cout << "------------------------------------------------" << endl;
				cout << "Indique a op????o selecionada: ";
				cin >> selectedOption;
				cout << "\n\n";
					
				switch (selectedOption) {
					case '1': {
						cout << "------------------------------------------------" << endl;
						cout << "Lojas n??o selecionadas" << endl;
						cout << "------------------------------------------------" << endl;
						
						bool exist = false;
						vector<int> avaiableStores;
						bool conditionStore = false;
						int selectedStore;
							
						for(size_t cont = 0; cont < storesList.size(); cont++) {
							if ((*(storesList[cont])).isSelected() == false) {
								cout << cont + 1 << ": " << (*(storesList[cont])).name << endl;
								exist = true;
								avaiableStores.push_back(cont + 1);
							}
						}
						
						if (exist == false) {
							cout << "N??o h?? lojas disponiveis. Todas as lojas j?? foram selecionadas. \n\n" << endl;
						} else {
							cout << "0: Cancelar opera????o" << endl;
							cout << "------------------------------------------------" << endl;
							cout << "Qual loja deseja adicionar? (Indique o numero correspondente): ";
							cin >> selectedStore;

							if (selectedStore != 0) {
								for(size_t cont = 0; cont < storesList.size() && conditionStore == false; cont++) {
									if (avaiableStores[cont] == selectedStore) {
										conditionStore = true;
									} else {
										conditionStore = false;
									}
								}
								
								if(conditionStore== true) {
									(*(storesList[selectedStore - 1])).changeSelection();
									cout << "\nLoja adicionada com sucesso!!\n" << endl << endl;
								} else {
									cout << "Loja selecionada n??o est?? dentre as op??oes" << endl;
								}	
								
							}	

							cout << endl << endl;
						}
					}
					break;

					case '2': {
						cout << "------------------------------------------------" << endl;
						cout << "Lojas j?? selecionadas" << endl;
						cout << "------------------------------------------------" << endl;
						
						bool exist = false;
						int selectedStore;
						vector<int> avaiableStores;
						bool conditionStore = false;
		
						for(size_t cont = 0; cont < storesList.size(); cont++) {
							if ((*(storesList[cont])).isSelected() == true) {
								cout << cont + 1 << ": " << (*(storesList[cont])).name << endl;
								exist = true;
								avaiableStores.push_back(cont + 1);
							}
						}
				
						if(exist == false)
							cout << "N??o h?? lojas disponiveis. Todas j?? foram removidas" << endl;
						else {
							cout << "0: Cancelar opera????o" << endl;
							cout << "------------------------------------------------" << endl;
							cout << "Qual loja deseja remover? (Indique o numero correspondente): ";
							cin >> selectedStore;

							if (selectedStore != 0) {
								for(size_t cont = 0; cont < storesList.size() && conditionStore == false; cont++) {
									if (avaiableStores[cont] == selectedStore) {
										conditionStore = true;
									} else {
										conditionStore = false;
									}
								}
								
								if(conditionStore== true) {
									(*(storesList[selectedStore - 1])).changeSelection();
									cout << "\nLoja adicionada com sucesso!!\n" << endl << endl;
								} else {
									cout << "Loja selecionada n??o esta dentre as op????es" << endl;
								}	

							}

							cout << endl << endl;
						}
					}
					break;

					case '3':
					break;

					default:
						cout << "Op????o invalida" << endl << endl;
				}				

			break;


			case '4': {
				int store1, store2;
				vector<int> avaiableStores;
				vector<vector<string>> storeData;
				float minPrice, maxPrice;
				string product;
	
				cout << "______________________________________________________" << endl;
				cout << "      Compara????o de pre??o entre duas lojas" << endl;
				cout << "------------------------------------------------------" << endl;
				
				for(size_t cont = 0; cont < storesList.size(); cont++) {
					cout << cont + 1 << ": " << storesList[cont]->name << endl;
					avaiableStores.push_back(cont + 1);
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
				bool conditionStore = false;
				bool conditionStore1 = false;
				int optionDW;

				for(size_t cont = 0; cont < avaiableStores.size() && conditionStore == false; cont++) {
					if (avaiableStores[cont] == store1) {
						conditionStore = true;
					} else {
						conditionStore = false;
					}
				}
								
				for(size_t cont = 0; cont < avaiableStores.size() && conditionStore1 == false; cont++) {
					if (avaiableStores[cont] == store2) {
						conditionStore1 = true;
					} else {
						conditionStore1 = false;
					}
				}
				

				if(conditionStore == true && conditionStore1 == true) {
					do {
						string product1, product2, url1, url2;						
						float price1, price2;
						string strMin, strMax;
						
						bool notEmpty = false;
			
						do {
							string tempProduct;
							cout << "Informe o nome do produto que deseja pesquisar: ";
							getline(cin, tempProduct);
							
							int index = checkEmptySpaces (tempProduct);
		
							if (index != -1) {
								product = tempProduct.substr (index, tempProduct.size() - index);
								notEmpty = true;
							}
						} while (notEmpty == false);
						

						bool isValid;
		
						do {
							isValid = true;
		
							cout << "Informe a faixa de pre??o do produto procurado" << endl;
							cout << "Menor pre??o da faixa: ";
							cin >> strMin;
							cout << "Maior pre??o da faixa: ";
							cin >> strMax;
						
								try {
									minPrice = stof (strMin);
									maxPrice = stof (strMax);

									if (maxPrice <= minPrice) {
										isValid = false;
									}
								} catch (invalid_argument& e) {
									isValid = false;
								}

								if (!isValid) {
									cout << "Precos invalidos!" << endl;
								}
		
								cout << endl;
							
						} while (!isValid);

						char auxiliar[product.length()];
						char *productFinal = auxiliar;
						strToConstCharList(product, productFinal);

						vector <Product*> productList;

						for(int cont = 0; cont < 2; cont++) {
							switch(stores[cont]) {
								case 1:{
									storeData = getData(productFinal, minPrice, maxPrice, "amazon");

									string productName = storeData[0][0];
									string productPrice = storeData[0][1];
									string storeName = storeData[0][3];

									string productUrl = completeURL (storeName, storeData[0][2]); 

									Product* newProduct = new Product (productName, productPrice, productUrl, storeName);
									productList.push_back (newProduct);
								}break;

								case 2:{
									storeData = getData(productFinal, minPrice, maxPrice, "americanas");

									string productName = storeData[0][0];
									string productPrice = storeData[0][1];
									string storeName = storeData[0][3];

									string productUrl = completeURL (storeName, storeData[0][2]); 

									Product* newProduct = new Product (productName, productPrice, productUrl, storeName);
									productList.push_back (newProduct);
								}break;

								case 3:{
									storeData = getData(productFinal, minPrice, maxPrice, "submarino");

									string productName = storeData[0][0];
									string productPrice = storeData[0][1];
									string storeName = storeData[0][3];

									string productUrl = completeURL (storeName, storeData[0][2]); 

									Product* newProduct = new Product (productName, productPrice, productUrl, storeName);
									productList.push_back (newProduct);
								}break;

								default:
									cout << "Op????o de loja indisponivel." << endl;
							}
		
							if(cont == 0) {
								product1 = (*productList[cont]).getName();
								price1 = (*productList[cont]).getPrice();
								url1 = (*productList[cont]).getURL();
							}
							else {
								product2 = (*productList[cont]).getName();
								price2 = (*productList[cont]).getPrice();
								url2 = (*productList[cont]).getURL();
							}
						}
								
						
						cout << "\n------------------------------------------------------" << endl;
						cout <<                         "LOJA 1" << endl;
						cout << "------------------------------------------------------" << endl;
						cout << storesList[store1 - 1]->name << endl; 
						cout << product1 << endl;
						cout << price1 << endl;
						cout << url1 << endl;	

						cout << endl;					

						cout << "------------------------------------------------------" << endl;
						cout <<                         "LOJA 2" << endl;
						cout << "------------------------------------------------------" << endl;
						cout << storesList[store2 - 1]->name << endl; 
						cout << product2 << endl;
						cout << price2 << endl;
						cout << url2 << endl;	
						
						cout << endl;
							
						cout << "Aperte 0 para sair, 1 para fazer outra busca e 2 para adicionar na lista de desejos." << endl;
						cin >> optionDW;						
						
						if (optionDW == 2) {
							int currentOption;
	
							cout << "Indique o numero correspondente a loja da qual deseja salvar o produto: " << endl;
							cout << "OBS: Loja 1 ou Loja 2" << endl;
							cin >> currentOption;

							if (currentOption == 1) {
								wishList.push_back(productList[0]);
								fileWrite("wishList.cvs", wishList);
								cout << "Produto adicionado com sucesso." << endl;
							} else if (currentOption == 2) {
								wishList.push_back(productList[1]);
								fileWrite("wishList.cvs", wishList);
								cout << "Produto adicionado com sucesso." << endl;
						
							} else {
								cout << "Opcao invalida" << endl;
							}
							
							break;
						}

						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						
					} while (optionDW != 0);
					

				} else {
					cout << "Loja selecionada n??o esta dentre as op????es" << endl;
				}	

				cout << endl << endl;

			}
			
			break; 


			case '5': {

				bool goBack = false;

				string selectedOption;

				do {
					cout << "______________________________________________________" << endl;
					cout << "      		Lista de Desejos" << endl;
					cout << "------------------------------------------------------" << endl;

					for (size_t index = 0; index < wishList.size(); index++) {
						cout << "[" << index + 1 << "] " << (*wishList[index]).getName() << endl;
						cout << "------------------------------------------------------" << endl;
					}

					cout << endl;

					cout << "Para remover um produto, informe o indice dele, para sair, digite 0" << endl;
					cin >> selectedOption;						
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');				

					if (selectedOption == "0") {
						goBack = true;
					} else {
						int removeThis;

						try {
							removeThis = stoi (selectedOption);
						
							if ((size_t)removeThis <= wishList.size() && removeThis > 0) {
								wishList.erase (wishList.begin() + removeThis-1);
								cout << "Produto removido!" << endl;
								fileWrite ("wishList.csv", wishList);	
							} else {
								cout << "Entrada invalida" << endl;
							}
						} catch (invalid_argument& e) {
							cout << "Entrada invalida" << endl;
						}
					}
	
					cout << endl << endl;
				} while (!goBack);
			}
			break;


			default:
				cout << "Op????o invalida\n\n" << endl;		
		}
		
	} while (option != '0');

	Py_Finalize();
	
	return 0;
}
