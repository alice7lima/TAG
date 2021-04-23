/**
 * @file: projeto2.h
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

#ifndef PROJETO2_H
#define PROJETO2_H
#include <bits/stdc++.h>

void PreencherListaAdj();

void Busca_DFS(int vertice);

void Ordenacao_Topologica();

void PrintLista();

void PrintListaTopologica();

void CaminhoMateria(int i);

int Comparacoes(std::vector<int> tres, int i);

void CaminhosDistintos();

void CaminhoCritico();

int BuscaBinaria(int n, int comeco, int fim);

void MateriasIniciais();

void PrintMaterias();

void MostrarGrafo();

void MostrarCaminhosCriticos();

void MostrarTopologica();

#endif