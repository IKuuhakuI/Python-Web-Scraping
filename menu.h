/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Prototipo da class Menu
 *
*/ 

#ifndef MENU_H
#define MENU_H

class Menu {

	public:
		void showMenu ();

		/* SETTERS */
		void setSelectedOption ();

		/* GETTERS */
		int getSelectedOption ();

	private:
		int selectedOption;

};

#endif

