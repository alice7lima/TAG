/**
 * @file: grafos.h
 *
 * @author1: Alice da Silva de Lima
 * @Matricula: 18/0112601
 * @author2: Giovana Pinho Garcia
 * @Matricula: 18/0101374
 *
 * @disciplina: Teoria e aplicação de grafos
 * @Professor: Díbio Leandro Borges 
 *
 *Arquivo que lista todas as funcoes do programa */

#ifndef GRAFOS_H
#define GRAFOS_H

#include <fstream>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

std::vector<std::vector<int>> Criar_Lista_Adj();

void Print_Maximal(std::vector<int> &R);

std::vector<int> P_intersec_Vadj(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj);

std::vector<int> P_remove_V(std::vector<int> &P, int v);

std::vector<int> X_uniao_V(std::vector<int> &X, int v);

void Bron_Kerbosch(std::vector<int> &R, std::vector<int> &P, std::vector<int> &X, std::vector<std::vector<int>> &lista_adj);

void Cliques_Maximiais(int I, std::vector<std::vector<int>> &lista_adj);

std::vector<int> Num_Triangulos(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj);

void Coeficientes_Aglomeracao(std::vector<std::vector<int>> &lista_adj, int I, int op);

void Vertices(std::vector<std::vector<int>> &lista_adj, int I);

#endif