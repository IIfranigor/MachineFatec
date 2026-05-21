//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream> // Biblioteca para entrada e saída de dados
#include <string> // Biblioteca para manipulação de strings
#include "include/produto.h"
#include "include/menu.h"
#include "include/venda.h"

using namespace std;

int main(){
    Produto* head;
    Produto* tail;
    Slot slots[50];
    FilaVendas fila;
    PilhaAcoes pilha;
    Caixa caixa;
    string acesso;
    string senha;

    inicializarEstoqueProduto(head, tail);
    inicializarSlots(slots);
    inicializarFila(fila);
    inicializarPilha(pilha);
    inicializarCaixa(caixa);

    cout << "Maquina de vendas de conveniencia" << endl;
    // Pressiona enter para acessar o menu de usuario padrao e digite 9 para acessar administrativo

    do {
        cout << "\nPressione ENTER para acessar o menu usuario, digite 9 para admin ou 0 para sair: ";
        getline(cin, acesso);

        if (acesso == "") {
            menuUsuario(slots, fila, caixa);
        } else if (acesso == "9") {
            cout << "Digite a senha do administrador: ";
            getline(cin, senha);

            if (senha == "senha123") {
                menuAdmin(head, tail, slots, fila, pilha, caixa);
            } else {
                cout << "Senha incorreta." << endl;
            }
        } else if (acesso != "0") {
            cout << "Opcao invalida." << endl;
        }
    } while (acesso != "0");

    destruirFila(fila);
    destruirPilha(pilha);
    destruirLista(head, tail);

    return 0;
}
