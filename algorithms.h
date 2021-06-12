/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * EEL670 - Linguagens de Programacao - Turma 2020/2
 * Prof. Miguel Elias M. Campista
 * Autor: Luiz Carlos Aguiar Carrion & Maria Eduarda de Souza Mafra
 * Trabalho Final - Etapa 2
 * Decricao: Prototipo de funcoes extras
 *
*/ 

#pragma once

#include <string>
#include <vector>

using namespace std;


string completeURL (string, string);

void strToConstCharList (string, char*&);

float strToFloat (string);

vector<string> constCharToVectorStr (const char*);

int checkEmptySpaces (string);
