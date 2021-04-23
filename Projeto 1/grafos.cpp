#include "grafos.h"


/*!
 * @fn Criar_Lista_Adj
 * @brief Cria a lista de adjacencia dos vertices
 * @signature std::vector<std::vector<int>> Criar_Lista_Adj();
 *
 * @return Retorna a lista de adjacencia dos vertices
 **/
std::vector<std::vector<int>> Criar_Lista_Adj(){
    std::ifstream fin("soc-dolphins.mtx");

    int I, J, N;

    while (fin.peek() == '%') fin.ignore(2048, '\n');           /*ignora os comentarios*/

    
    fin >> I >> J >> N;


    std::vector<std::vector<int>> lista_adj;

    /*preenche as listas de adjacencia*/
    for(int i=0; i<I; i++){                     
        std::vector<int> v_aux;             

        v_aux.push_back(i+1);               

        lista_adj.push_back(v_aux); 
    }
    
    for(int i=0; i<N; i++){
        int a, b;
        fin >> a >> b;
        
        lista_adj[a-1].push_back(b);

        lista_adj[b-1].push_back(a);
    }

    fin.close();

    return lista_adj;
}


/*!
 * @fn Print_Maximal
 * @brief Imprime na tela o tamanho e os vertices de todos os cliques maximais
 * @signature Print_Maximal(std::vector<int> &R);
 *
 * @param[in] R Vetor que contem o clique maximal a ser printado
 **/
void Print_Maximal(std::vector<int> &R){

    std::cout << "Tamanho do clique: " << R.size() << std::endl;
    for(int i=0; i < R.size(); i++){
        std::cout << R[i] << " ";
    }
    std::cout << std::endl << std::endl;
}


/*!
 * @fn R_uniao_V
 * @brief Adiciona em R um novo elemento
 * @signature R_uniao_V(std::vector<int> &R, int v);
 *
 * @param[in] R Vetor que contem os vertices que farao parte do clique maximal, v Vertice que tambem fara parte do clique maximal
 * @return Retorna um novo vetor que contem R e o novo vertice v
 **/
std::vector<int> R_uniao_V(std::vector<int> &R, int v){
    std::vector<int> Rnew;

    Rnew = R;
    Rnew.push_back(v);

    return Rnew;
}


/*!
 * @fn P_intersec_Vadj
 * @brief Faz a intersecao entre dois vetores
 * @signature P_intersec_Vadj(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj);
 *
 * @param[in] P Vetor que fara parte da intersecao, v Vertice que indica qual lista de adjacencia fara parte da intersecao, lista_adj Vetor das lista de adjacencia do grafo
 * @return Retorna um novo vetor que contem a intersecao de dois vetores
 **/
std::vector<int> P_intersec_Vadj(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj){

    std::vector<int> Pnew;

    for(int i=0; i < P.size(); i++){
        for(int j=1; j < lista_adj[v-1].size(); j++){
            if(P[i] == lista_adj[v-1][j]){
                Pnew.push_back(P[i]);
            }
        }
    }
    return Pnew;
}


/*!
 * @fn P_remove_V
 * @brief Remove um dos vertices do vetor
 * @signature P_remove_V(std::vector<int> &P, int v);
 *
 * @param[in] P Vetor do qual sera removido um elemento, v Vertice que sera removido do vetor
 * @return Retorna um novo vetor que nao contera o elemento v
 **/
std::vector<int> P_remove_V(std::vector<int> &P, int v){
    std::vector<int> Pnew;

    Pnew = P;

    for(int i=0; i < Pnew.size(); i++){
        if(Pnew[i] == v){
            Pnew.erase(Pnew.begin() + i);
        }
    }
    return Pnew;
}

/*!
 * @fn Bron_Kerbosch
 * @brief Faz o algoritmo Bron Kerbosch para encontrar os cliques maximais do grafo
 * @signature void Bron_Kerbosch(std::vector<int> &R, std::vector<int> &P, std::vector<int> &X, std::vector<std::vector<int>> &lista_adj);
 *
 * @param[in] R Vetor que contera os cliques maximais, P Vetor que contera os candidatos para um clique maximal, X Vetor que contera os vertices ja testados
 * lista_adj Listas de adjacencia do grafo
 */
void Bron_Kerbosch(std::vector<int> &R, std::vector<int> &P, std::vector<int> &X, std::vector<std::vector<int>> &lista_adj){
    std::vector<int> Rnew, Pnew, Xnew;

    if(P.empty() && X.empty()){   /*confere se ja foi encontrado um clique maximal*/
        Print_Maximal(R);
    }

    while(!P.empty()){
        for(int i=0; i < P.size(); i++){

            int v = P[i];

            Rnew = R_uniao_V(R, v);
            Pnew = P_intersec_Vadj(P, v, lista_adj);
            Xnew = P_intersec_Vadj(X, v, lista_adj);

            Bron_Kerbosch(Rnew, Pnew, Xnew, lista_adj);
            

            P = P_remove_V(P, v);
            X = R_uniao_V(X, v);

        }
    }
    return;

}


/*!
 * @fn Cliques_Maximais
 * @brief Inicializa asos vetores que serao usados na funcao Bron Kerbosch
 * @signature void Cliques_Maximiais(int I, std::vector<std::vector<int>> &lista_adj);
 *
 * @param[in] I Numero de vertices, lista_adj Listas de adjacencia do grafo
 */
void Cliques_Maximiais(int I, std::vector<std::vector<int>> &lista_adj){
    std::vector<int> R, P, X; 

    for(int i=0; i<I; i++){   /* adiciona em P todos os vertices do grafo*/
        P.push_back(i+1);
    }
    
    Bron_Kerbosch(R, P, X, lista_adj);

}

/*!
 * @fn Num_Triangulos
 * @brief Verifica os vértices adjacentes comuns entre dois vértices
 * @signature std::vector<int> Num_Triangulos(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj);
 *
 * @param[in] P Lista de adjacencia do vertice cujos vizinhos estao sendo analisados, v Vertice vizinho, lista_adj Listas de adjacencia de cada vertice do grafo 
 */
std::vector<int> Num_Triangulos(std::vector<int> &P, int v, std::vector<std::vector<int>> &lista_adj){

    std::vector<int> Pnew;

    for(int i=1; i < P.size(); i++){
        for(int j=1; j < lista_adj[v-1].size(); j++){
            if(P[i] == lista_adj[v-1][j] && P[i] > v){
                Pnew.push_back(P[i]);
            }
        }
    }
    return Pnew;
}

/*!
 * @fn Coeficientes_Aglomeracao
 * @brief Calcula o coeficiente de aglomeracao de cada vertice
 * @signature void Coeficientes_Aglomeracao(std::vector<std::vector<int>> &lista_adj, int I, int op);
 *
 * @param[in] lista_adj Listas de adjacencia de cada vertice do grafo, I Numero de vertices do grafo, op Opcao do menu
 */

void Coeficientes_Aglomeracao(std::vector<std::vector<int>> &lista_adj, int I, int op){
    double coef_medio = 0;


    for(int i = 0; i < I; i++){
    double vizinhos = (lista_adj[i].size()) - 1;
    double coef = 0, triangulos = 0;

        for(int j = 1; j < lista_adj[i].size(); j++){

            if(vizinhos > 1){                       
                std::vector<int> num_triangulos;
                int aux = lista_adj[i][j];

                num_triangulos = Num_Triangulos(lista_adj[i], aux, lista_adj); 

                triangulos += num_triangulos.size(); /* conta o numero de triangulos*/

                coef = (2*triangulos)/(vizinhos*(vizinhos-1));  /*2t / 2n(n-1)*/
                
            }
            else{
                coef = 0;
            }
        }
        if(op == 3){
            std::cout << "coeficiente de aglomeração de " << i + 1 << " " << coef << std::endl;
        }
        coef_medio += coef; 
    }    

    
    if(op == 4){
        coef_medio = (coef_medio / I);   /* 1/N * somatorio(coef)*/
        
        std::cout << std::endl << "coeficiente medio: " << coef_medio << std::endl;
    }

    std::cout <<  std::endl;
}

/*!
 * @fn Vertices
 * @brief Mostra todos os vertices do grafo e seus respectivos graus
 * @signature void Vertices(std::vector<std::vector<int>> &lista_adj, int I);
 *
 * @param[in] lista_adj Listas de adjacencia de cada vertice do grafo, I Numero de vertices do grafo
 */
void Vertices(std::vector<std::vector<int>> &lista_adj, int I){

    for(int i=0; i<I; i++){
        int grau, aux;
        
        grau = (lista_adj[i].size()) - 1;

        std::cout <<  "vertice: " << lista_adj[i][0] << " ";

        std::cout << "grau do vertice: " << grau <<std::endl;

    }
    std::cout <<  std::endl;
}
