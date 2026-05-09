//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA:

#include <iostream> // Biblioteca para entrada e saída de dados
#include <String> // Biblioteca para manipulação de strings

using namespace std;

// Struct de No Duplo que armazenara os dados dos produtos

struct Produto {
    int id; //id do local onde o produto esta armazenado
    string nome;
    float valor;
    int estoque;
    Produto *proximo;
    Produto *anterior;

    //id não pode passar de 50, pois o local de armazenamento tem capacidade para 50 produtos
    //id deve ser único e estar entre 1 e 50
    
};

void inicializarListaProduto(Produto* &head, Produto* &tail) {
   head = new Produto; // Nó sentinela de início
   tail = new Produto; // Nó sentinela de fim

   head->id = 0; // ID do nó sentinela de início (sempre 0, não representa um produto real)
   tail->id = 50; // ID do nó sentinela de fim

   head->proximo = tail; // Head aponta para o Tail
   tail->anterior = head; // Tail aponta para o Head

    head->anterior = nullptr; // Head não tem anterior
    tail->proximo = nullptr; // Tail não tem próximo
}


// Função para inserir um produto na lista duplamente encadeada, garantindo que o ID seja único e esteja entre 1 e 50 
// e confere se o id já existe na lista, caso exista, não insere o produto e exibe uma mensagem de erro
void inserirProduto(Produto* &head, Produto* &tail, int id, string nome, float valor, int estoque) {

    if (id < 1 || id > 50) {
        cout << "Erro: ID deve estar entre 1 e 50." << endl;
        return;
    }
    // Verificar se o ID já existe na lista
    Produto* atual = head; // Começar a verificação a partir do nó sentinela de início (id = 0)
    while (atual != tail) {
        if (atual->id == id) {
            cout << "Erro: ID já existe na lista." << endl;
            return;
        }
        atual = atual->proximo;     
    }
    // Criar um novo produto para inserir na lista de forma ordenada
    Produto* novoProduto = new Produto;
    novoProduto->id = id;
    novoProduto->nome = nome;
    novoProduto->valor = valor;
    novoProduto->estoque = estoque;
    // Inserir o novo produto na posição correta para manter a lista ordenada por ID
    Produto* atualInsercao = head->proximo; // Começar a inserção a partir do primeiro produto real (Id = 1)
    while (atualInsercao != tail && atualInsercao->id < id) {
        atualInsercao = atualInsercao->proximo; // Confere a posição correta para inserção comparando se o ID do produto atual é menor que o ID do novo produto
    }

    

    
}
int main(){
    cout << "Maquina de vendas de conveniencia" << endl;
    // Pressiona enter para acessar o menu de usuario padrao e digite 9 para acessar administrativo
    string acesso;
    char opcao;
   getline(cin, acesso);
    // Aguarda o usuário pressionar digitar para acessar o menu de opções

    // menu de opções administrativas para o usuário escolher a ação desejada
    if (acesso == "9") {
        cout << "Acesso administrativo concedido" << endl;
        cout << "Selecione a opção desejada:" << endl;
        cout << "1 - Cadastrar produto" << endl;
        cout << "2 - Listar produtos" << endl;
        cout << "3 - Sair" << endl;

        cin >> opcao; // Aguarda o usuário digitar a opção desejada

        switch (opcao) {
            case '1':
                cout << "Cadastrar produto" << endl;
                break;
            case '2':
                cout << "Listar produtos" << endl;
                break;
            case '3':
                cout << "Sair" << endl;
                break;
            default:
                cout << "Opção inválida" << endl;

        }
        return 0;
    }else{
        cout << "Bem-vindo ao menu de usuário padrão" << endl;
        cout << "Selecione a opção desejada:" << endl;
        cout << "1 - Comprar produto" << endl;
        cout << "2 - Listar produtos" << endl;
        cout << "3 - Sair" << endl;
        cin >> opcao; // Aguarda o usuário digitar a opção desejada


        //menu de opções para o usuário padrão escolher a ação desejada
        switch (opcao) {
            case '1':
                cout << "Comprar produto" << endl;
                break;
            case '2':
                cout << "Listar produtos" << endl;
                break;
            case '3':
            cout << "Sair" << endl;
                break;
            default:
                cout << "Opção inválida" << endl;
        };
    }

    return 0;
};
