#include "grafos.h"

int main(){
    std::vector<std::vector<int>> lista_adj;

    lista_adj = Criar_Lista_Adj();

    int op=0;

    do{         /*menu interativo*/
        
        std::cout << "Selecione uma opcao:" << std::endl;
        std::cout << " 1 - Vertices e seus respectivos graus" << std::endl;
        std::cout << " 2 - Cliques maximais" << std::endl;
        std::cout << " 3 - Coeficiente de aglomeracao de cada vertice" << std::endl;
        std::cout << " 4 - Coeficiente de aglomeracao medio" << std::endl;
        std::cout << " 5 - Sair" << std::endl;
        
        std::cin >> op;

        switch(op){
            case 1: 
                Vertices(lista_adj, lista_adj.size());
                break;
            case 2:
                Cliques_Maximiais(lista_adj.size(), lista_adj);
                break;
            case 3:
                Coeficientes_Aglomeracao(lista_adj, lista_adj.size(), op);
                break;
            case 4:
                Coeficientes_Aglomeracao(lista_adj, lista_adj.size(), op);
                break;
            case 5:
                break;
            default:
                std::cout << "Opcao Invalida" << std::endl << std::endl;
                break;
        }

    }while(op != 5);

    return 0;

}