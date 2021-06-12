/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Implementacao da class Menu
 *
*/ 

#include <iostream>

#include "menu.h"

using namespace std;


/* Essa funcao eh responsavel por mostrar as opcoes do menu */
void Menu::showMenu () {
	cout << "*******************************************************" <<endl;
	cout << "Digite o numero correspondente a operacao desejada." << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "1: Buscar por produto em lojas" << endl
	     << "2: Ver lista de produtos em uma determinada loja" << endl
	     << "3: Configurar lojas" << endl
	     << "4: Comparacao de preco entre duas lojas" << endl
	     << "5: Lista de desejos" << endl
	     << "0: Sair" << endl;
	cout << "*******************************************************" << endl;
}

/* Funcao que pega entrada do usuario e valida ela */
void Menu::setSelectedOption () {
	string userInput;
		
	/* Pede a operacao do menu */
	cout << "Informe a operacao desejada: ";
	cin >> userInput;

	/* espaco em branco */
	cout << endl;

	selectedOption = userInput[0];
}

/* Retorna a opcao escolhida pelo usuario */
int Menu::getSelectedOption () {
	return selectedOption;
}

