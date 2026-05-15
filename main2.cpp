//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream>
#include <string>

using namespace std;

// =====================================
// STRUCT NÓ DUPLO
// =====================================

struct NoDuplo {

    int id;
    string nome;
    float valor;
    int estoque;

    NoDuplo* anterior;
    NoDuplo* proximo;
};

// =====================================
// INICIALIZAR LISTA
// =====================================

void inicializarLista(NoDuplo*& head, NoDuplo*& tail) {

    head = new NoDuplo();
    tail = new NoDuplo();

    head->proximo = tail;
    head->anterior = nullptr;

    tail->anterior = head;
    tail->proximo = nullptr;
}

// =====================================
// INSERIR PRODUTO
// =====================================

void inserirProduto(NoDuplo*& head,
                    NoDuplo*& tail,
                    int id,
                    string nome,
                    float valor,
                    int estoque,
                    bool mostrarMensagem = true) {

    NoDuplo* atual = head->proximo;

    // VERIFICAR ID DUPLICADO

    while (atual != tail) {

        if (atual->id == id) {

            cout << "\nERRO: ID ja cadastrado.\n";
            return;
        }

        atual = atual->proximo;
    }

    // CRIAR NOVO PRODUTO

    NoDuplo* novoProduto = new NoDuplo();

    novoProduto->id = id;
    novoProduto->nome = nome;
    novoProduto->valor = valor;
    novoProduto->estoque = estoque;

    // INSERIR NO FINAL DA LISTA

    novoProduto->proximo = tail;
    novoProduto->anterior = tail->anterior;

    tail->anterior->proximo = novoProduto;
    tail->anterior = novoProduto;

    // MENSAGEM

    if (mostrarMensagem) {

        cout << "\nProduto cadastrado com sucesso!\n";
    }
}

// =====================================
// LISTAR PRODUTOS
// =====================================

void listarProdutos(NoDuplo* head, NoDuplo* tail) {

    NoDuplo* atual = head->proximo;

    if (atual == tail) {

        cout << "\nNenhum produto cadastrado.\n";
        return;
    }

    cout << "\n========== PRODUTOS ==========\n";

    while (atual != tail) {

        cout << "\nID: " << atual->id << endl;
        cout << "Nome: " << atual->nome << endl;
        cout << "Valor: R$ " << atual->valor << endl;
        cout << "Estoque: " << atual->estoque << endl;

        cout << "-----------------------------\n";

        atual = atual->proximo;
    }
}

// =====================================
// COMPRAR PRODUTO
// =====================================

void comprarProduto(NoDuplo* head,
                    NoDuplo* tail,
                    int idCompra,
                    float& totalCompra) {

    NoDuplo* atual = head->proximo;

    while (atual != tail) {

        if (atual->id == idCompra) {

            if (atual->estoque > 0) {

                atual->estoque--;

                totalCompra += atual->valor;

                cout << "\nProduto adicionado a compra!\n";
                cout << "Produto: " << atual->nome << endl;
                cout << "Valor: R$ " << atual->valor << endl;
                cout << "Total atual: R$ " << totalCompra << endl;

            } else {

                cout << "\nProduto sem estoque.\n";
            }

            return;
        }

        atual = atual->proximo;
    }

    cout << "\nProduto nao encontrado.\n";
}

// =====================================
// MENU ADMIN
// =====================================

void menuAdmin(NoDuplo*& head,
               NoDuplo*& tail) {

    char opcao;

    do {

        cout << "\n========== MENU ADMIN ==========\n";

        cout << "1 - Cadastrar produto\n";
        cout << "2 - Listar produtos\n";
        cout << "3 - Voltar\n";

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

            case '1': {

                int id;
                string nome;
                float valor;
                int estoque;

                cout << "\nDigite o ID: ";
                cin >> id;

                cin.ignore();

                cout << "Digite o nome: ";
                getline(cin, nome);

                cout << "Digite o valor: ";
                cin >> valor;

                cout << "Digite o estoque: ";
                cin >> estoque;

                inserirProduto(head,
                                tail,
                                id,
                                nome,
                                valor,
                                estoque);

                break;
            }

            case '2':

                listarProdutos(head, tail);
                break;

            case '3':

                cout << "\nRetornando ao menu principal...\n";
                break;

            default:

                cout << "\nOpcao invalida.\n";
        }

    } while (opcao != '3');
}

// =====================================
// MENU USUARIO
// =====================================

void menuUsuario(NoDuplo*& head,
                 NoDuplo*& tail) {

    string opcao;

    float totalCompra = 0;

    do {

        cout << "\n======= MAQUINA DE VENDAS =======\n";

        // MENU VISIVEL AO CLIENTE

        cout << "1 - Adicionar item a compra\n";
        cout << "2 - Finalizar compra e pagar\n";
        cout << "0 - Sair\n";

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        // =====================================
        // MENU ADMIN OCULTO
        // =====================================

        if (opcao == "9") {

            menuAdmin(head, tail);
        }

        // =====================================
        // ADICIONAR ITEM
        // =====================================

        else if (opcao == "1") {

            int idCompra;

            listarProdutos(head, tail);

            cout << "\nDigite o ID do produto: ";
            cin >> idCompra;

            comprarProduto(head,
                            tail,
                            idCompra,
                            totalCompra);
        }

        // =====================================
        // FINALIZAR PAGAMENTO
        // =====================================

        else if (opcao == "2") {

            cout << "\n======= PAGAMENTO =======\n";

            cout << "Total da compra: R$ "
                 << totalCompra << endl;

            cout << "\nPagamento realizado com sucesso!\n";
            cout << "Retire seus produtos.\n";

            // RESETAR TOTAL

            totalCompra = 0;
        }

        // =====================================
        // SAIR
        // =====================================

        else if (opcao == "0") {

            cout << "\nSistema encerrado.\n";
        }

        else {

            cout << "\nOpcao invalida.\n";
        }

    } while (opcao != "0");
}

// =====================================
// MAIN
// =====================================

int main() {

    NoDuplo* head;
    NoDuplo* tail;

    inicializarLista(head, tail);

    // PRODUTOS INICIAIS

    inserirProduto(head,
                    tail,
                    1,
                    "Coca-Cola",
                    7.50,
                    10,
                    false);

    inserirProduto(head,
                    tail,
                    2,
                    "Chocolate",
                    5.00,
                    15,
                    false);

    inserirProduto(head,
                    tail,
                    3,
                    "Fandangos",
                    6.50,
                    20,
                    false);

    // INICIAR SISTEMA

    menuUsuario(head, tail);

    return 0;
}