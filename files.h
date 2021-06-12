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

#pragma once

#include <vector>
#include <string>

#include "product.h"

using namespace std;

void fileWrite (string, vector <Product*>);
void fileRead (string, vector <Product*> &);
