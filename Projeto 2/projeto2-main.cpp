#include "projeto2.h"

int main(){

    int op = 0, criticos = 0;

    PreencherListaAdj();

    Ordenacao_Topologica();

    MateriasIniciais();
    CaminhoCritico();
    
    do{
        
        std::cout << "Selecione uma opcao:" << std::endl;
        std::cout << " 1 - Exibir lista de adjacencias" << std::endl;
        std::cout << " 2 - Exibir lista topologica" << std::endl;
        std::cout << " 3 - Exibir caminhos criticos" << std::endl;
        std::cout << " 4 - Exibir imagem do grafo" << std::endl;
        std::cout << " 5 - Exibir imagem da organizacao topologica" << std::endl;
        std::cout << " 6 - Exibir imagem dos caminhos criticos" << std::endl;
        std::cout << " 7 - Sair" << std::endl;

        std::cin >> op;

        switch(op){
            case 1:
                PrintLista();
                break;
            case 2:
                PrintListaTopologica();
                break;
            case 3:
                CaminhosDistintos();
                break;
            case 4:
                MostrarGrafo();
                break;
            case 5:
                MostrarTopologica();
                break;
            case 6:
                MostrarCaminhosCriticos();
            case 7:
                break;
            default:
                std::cout << "Opcao Invalida" << std::endl << std::endl;
                break;
        }

    }while(op!=7);

    return 0;
}