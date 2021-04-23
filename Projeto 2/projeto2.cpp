#include "projeto2.h"

/*declaracao das estruturas usadas no programa*/

std::vector<std::vector<std::pair<std::string,int>>> lista_adj;
std::vector<std::vector<int>> indices;
std::vector<std::vector<int>> caminhos_criticos;
std::vector<int> caminho_aux, v_possibilidades, v_materias;

std::vector<std::string> nome_materias;

std::vector<bool> visitados;
std::vector<int> list_topologica;

int existecritico = 0;    /*flag auxiliar para apresentar o png dos caminhos criticos apenas se ja existe um arquivo dot destes*/

/*!
 * @fn PreencherListaAdj
 * @brief Cria a lista de adjacencia dos vertices, cria um arquivo dot do grafo
 * @signature void PreencherListaAdj();
 **/

void PreencherListaAdj(){
    std::ifstream fin("obrigatorias.txt");

    std::ofstream teste;
    teste.open("file.dot");

    teste << "digraph obrigatorias{" << "\n";
    
    for(int i = 0; i < 32; i++){
        std::string nome;
        int n;
        std::vector<std::pair<std::string,int>> v_aux;
        std::vector<int> v_aux2;

        fin >> nome;

        nome_materias.push_back(nome);

        fin >> n;

        for(int j = 0; j < n; j++){
            
            std::pair<std::string,int> aux;
            
            char cod[8], cod1[8];
            int cred, pos, cred1;
            
            fin >> cod >> cred >> pos;

            aux.first = cod;
            aux.second = cred;

            v_aux.push_back(aux);

            v_aux2.push_back(pos);

            // ---- preencher aqruivo dot ---- //

            if(n == 1){
                teste << cod;
            }
            else{
                if(j==0){
                    cred1 = cred;
                    strcpy(cod1, cod);
                }
                else{
                    teste << cod1 << "->" << cod << "[label= \"" << cred1 <<"\"];" << std::endl;
                }
            }
            teste << "\n";
        }
        lista_adj.push_back(v_aux);
        indices.push_back(v_aux2);
    }
    
    teste << "}";
    teste.close();
}

/*!
 * @fn Busca_DFS
 * @brief Realiza uma busca em profundidade no grafo
 * @signature void Busca_DFS(int vertice);
 *
 * @param[in] vertice Inteiro que tem a posicao do vertice especifico na lista de adjacencias 
 **/
void Busca_DFS(int vertice){
    visitados[vertice] = 1;
    for(int j = 0; j < lista_adj[vertice].size(); j++){
        if(visitados[j] == 0){
            Busca_DFS(j);
        }
    }
    list_topologica.push_back(vertice);
}

/*!
 * @fn Ordenacao_Topologica
 * @brief Realiza a organizacao topologica do grafo inicializando os vetores auxiliares e chamando a funcao de busca 
 * em profundidade, cria um arquivo dot nessa configuracao
 * @signature void Ordenacao_Topologica();
 **/
void Ordenacao_Topologica(){
    visitados.assign(lista_adj.size(), 0);
    list_topologica.clear();

    for(int i=0; i<lista_adj.size(); i++){
        if(!visitados[i]){
            Busca_DFS(i);
        }
    }

    std::ofstream topologica;

    topologica.open("topologica.dot");

    topologica << "digraph {" << "\n";

    topologica <<  "    {" << "\n";

    topologica << "    rank=same" << "\n" << "    node [shape=circle]" << "\n" << "    ";

    for(int j = 0; j < list_topologica.size(); j++){
        topologica <<  lista_adj[list_topologica[j]][0].first << " ";
    }

    topologica << "\n" << "    }" << "\n";

    /*topologica << "    ordering=out" << "\n" << "    x [style=invis]" << "\n";

    topologica << "    x -> {";

    for(int j = 0; j < list_topologica.size(); j++){
        topologica << lista_adj[list_topologica[j]][0].first << " ";
    }

    topologica << "    }" << "\n";*/

    for(int j = 0; j < list_topologica.size(); j++){
        if(lista_adj[list_topologica[j]].size() > 1){ 
            for(int l = 1; l < lista_adj[list_topologica[j]].size(); l++){
                topologica << "    " << lista_adj[list_topologica[j]][0].first << " -> " << lista_adj[list_topologica[j]][l].first << "\n";
            }
        }
        /*else{
            topologica << "    " << lista_adj[list_topologica[j]][0].first << "\n";
        }*/
    }

    topologica << "\n" << "}" << "\n";

    topologica.close();

}

/*!
 * @fn PrintLista
 * @brief Mostra a lista de adjacencias no terminal
 * @signature void PrintLista(); 
 **/
void PrintLista(){
    for(int i=0; i<lista_adj.size(); i++){
        for(int j=0; j<lista_adj[i].size(); j++){
            std::cout << lista_adj[i][j].first << " " << lista_adj[i][j].second << " ";
        }
        std::cout << std::endl;
    }
}

/*!
 * @fn PrintListaTopologica
 * @brief Mostra a ordem dos vertices na organizacao topologica no terminal
 * @signature void PrintListaTopologica();
 **/
void PrintListaTopologica(){
    for(int l = 0; l < list_topologica.size(); l++){
        std::cout << nome_materias[list_topologica[l]] << " - " << lista_adj[list_topologica[l]][0].first << " " << lista_adj[list_topologica[l]][0].second << std::endl;
    }
}

/*!
 * @fn CaminhoMateria
 * @brief Metodo auxiliar da CaminhosCriticos que percorre os caminhos a partir de um vertice (materia) recursivamente
 * @signature void CaminhoMateria(int i);
 * 
 * @param[in] i Inteiro que tem a posicao do vertice especifico na lista de adjacencias
 **/
void CaminhoMateria(int i){
    int mv;
    for(mv = 1; mv<lista_adj[i].size(); mv++){
        caminho_aux.push_back(indices[i][mv]);
        CaminhoMateria(indices[i][mv]);
    }
    if(mv == 1){
        int peso=0;
        for(int i=0; i<caminho_aux.size(); i++){
            peso += lista_adj[caminho_aux[i]][0].second;

        }
        caminho_aux.push_back(peso);

        caminhos_criticos.push_back(caminho_aux);
        caminho_aux.pop_back();
       

    }
    caminho_aux.pop_back();
    return;
}

/*!
 * @fn Comparacoes
 * @brief Metodo auxiliar de CaminhosDistintos que verifica se existe alguma materia no caminho atual que ja esta 
 * em um caminho critico
 * @signature Comparacoes(std::vector<int> tres, int i);
 * 
 * @param[in] tres Vetor que guarda os tres caminhos mais longos do grafo, i Inteiro que guarda a posicao do caminho a 
 * ser analisado
 **/
int Comparacoes(std::vector<int> tres, int i){

    std::vector<int>::iterator conf;

    for(int j=0; j<caminhos_criticos[i].size()-1; j++){
        
        int materia = caminhos_criticos[i][j];
        tres.pop_back();
        conf = find(tres.begin(), tres.end(), materia);
        if(conf != tres.end()){
            return 1;
        }
    }    
    return 0;    
}

/*!
 * @fn CaminhosDistintos
 * @brief Ordena todos os caminhos do grafo em ordem decrescente e seleciona os tres mais longos distintos, 
 * cria um arquivo dot e insere estes caminhos e os mostra no terminal 
 * @signature void CaminhosDistintos();
 **/
void CaminhosDistintos(){
    std::vector<std::vector<int>> tres; 
    std::vector<int>::iterator conf;
    int achou=1, achou2=1, inicio;

    sort(caminhos_criticos.begin(), caminhos_criticos.end(), [](std::vector<int> x1, std::vector<int> x2) {
        return x1.back() > x2.back();
    });

    tres.push_back(caminhos_criticos[0]);

    for(int i=1; (i<caminhos_criticos.size()) && (achou == 1); i++){

        achou = Comparacoes(tres[0], i);
        
        if(!achou){
            tres.push_back(caminhos_criticos[i]);
            inicio = i;
        }
    }
    
    for(int j=inicio; (j<caminhos_criticos.size()) && (achou2 == 1); j++){

        achou = Comparacoes(tres[0], j);
        
        if(!achou){
            achou2 = Comparacoes(tres[1], j);

            if(!achou2){
                tres.push_back(caminhos_criticos[j]);
            }
        }
    }

    // ---- Escrever no arquivo.dot ---- //

    std::ofstream criticos;
    criticos.open("criticos.dot");

    criticos << "digraph obrigatorias{" << "\n";

    for(int i=0; i<tres.size(); i++){
        for(int j=0; j<tres[i].size()-1; j++){
            if(j==0){
                criticos << lista_adj[tres[i][j]][0].first << "->"; 
            }
            else if(j<tres[i].size()-2){
                criticos << lista_adj[tres[i][j]][0].first << "\n";
                criticos << lista_adj[tres[i][j]][0].first << "->";
            }
            else{
                criticos << lista_adj[tres[i][j]][0].first << "\n" << "\n";
            }
        }
    }

    criticos << "}";
    criticos.close();
    existecritico = 1;


    // ---- Para de escrever no arquivo ---- //

    for(int i=0; i<tres.size(); i++){
        for(int j=0; j<tres[i].size()-1; j++){
            std::cout << lista_adj[tres[i][j]][0].first << " " << lista_adj[tres[i][j]][0].second << " ";
        }
        std::cout << std::endl;
        std::cout << "Peso total: " << tres[i][tres[i].size()-1] << std::endl << std::endl;
    }
}


/*!
 * @fn CaminhoCritico
 * @brief Metodo auxiliar de CaminhosDistintos que verifica se existe alguma materia no caminho atual que ja esta 
 * em um caminho critico
 * @signature void CaminhoCritico();
 **/
void CaminhoCritico(){
    for(int i=0; i<v_materias.size(); i++){
        caminho_aux.clear();
        caminho_aux.push_back(v_materias[i]);

        CaminhoMateria(v_materias[i]);
    }
}

/*!
 * @fn BuscaBinaria
 * @brief Busca recursivamente um valor em um vetor ordenado
 * @signature int BuscaBinaria(int n, int comeco, int fim)
 * 
 * @param[in] n Inteiro que se procura, comeco Inteiro com o inicio do vetor, fim Inteiro com a ultima posicao do vetor
 * @return Retorna o numero se foi possivel encontrar e -1 caso contrário
 **/
int BuscaBinaria(int n, int comeco, int fim){	
    int meio,achou=-1;
	meio=(comeco+fim)/2;
	if (comeco<=fim){   
        if (n==v_possibilidades[meio]){   
            achou=meio;
            return achou;
        }
        else{
            if(n<v_possibilidades[meio])
                BuscaBinaria(n,comeco,meio-1);
            else
                BuscaBinaria(n,meio+1,fim);
        }
    }
    else
        return achou;
} 

/*!
 * @fn MateriasIniciais
 * @brief Seleciona as materias iniciais
 * @signature void MateriasIniciais();
 **/
void MateriasIniciais(){
    for(int i=0; i<lista_adj.size(); i++){
        if(lista_adj[i].size()>1){
            for(int j=1; j<lista_adj[i].size(); j++){
                v_possibilidades.push_back(indices[i][j]);
                sort(v_possibilidades.begin(),v_possibilidades.end());
            }
        }
    }
    for(int i=0; i<lista_adj.size(); i++){
        int achou = BuscaBinaria(i, 0, v_possibilidades.size()-1);
        if(achou == -1){
            v_materias.push_back(i);
        }
    }
}


/*!
 * @fn PrintMaterias
 * @brief Mostra no terminal as materias obrigatorias
 * @signature void PrintMaterias();
 **/
void PrintMaterias(){
    for(int i=0; i<v_materias.size(); i++){
        std::cout << v_materias[i] << std::endl;
    }
}

/*!
 * @fn MostrarGrafo
 * @brief Mostra o png do grafo
 * @signature void MostrarGrafo();
 **/
void MostrarGrafo(){
    system("dot -Tpng file.dot -o grafo.png");
    system("display grafo.png");
}


/*!
 * @fn MostrarTopologica
 * @brief Mostra o png do grafo em organizacao topologica
 * @signature void MostrarTopologica();
 **/
void MostrarTopologica(){
    system("dot -Tpng topologica.dot -o topologica.png");
    system("display topologica.png");
}

/*!
 * @fn MostrarCaminhosCriticos
 * @brief Mostra o png dos caminhos criticos
 * @signature void MostrarCaminhosCriticos();
 **/
void MostrarCaminhosCriticos(){
    if(existecritico){
        system("dot -Tpng criticos.dot -o criticos.png");
        system("display criticos.png");
    }
    else{
        std::cout << "Nao foi possivel exibir a imagem dos caminhos criticos. Por favor selecione a opcao 3 do menu e tente novamente" << std::endl;
    }
}