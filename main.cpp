//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream> // Biblioteca para entrada e saída de dados
#include <string> // Biblioteca para manipulação de strings

using namespace std;

//==============================
// PRODUTO
//==============================
// Struct de No Duplo que armazenara os dados dos produtos
struct Produto {
    int id; //id do local onde o produto esta armazenado
    string nome;
    float valor;
    int estoque;
    bool ativo; // indica se o produto esta ativo ou inativo, caso o produto seja inativo, ele não aparecerá para o cliente e não poderá ser comprado
    Produto *proximo;
    Produto *anterior;

   
    
};
//==============================
// INICIALIZAR ESTOQUE
//==============================

void inicializarEstoqueProduto(Produto* &head, Produto* &tail) {
   head = new Produto; // Nó sentinela de início
   tail = new Produto; // Nó sentinela de fim

   head->id = 0; // ID do nó sentinela de início (sempre 0, não representa um produto real)
   tail->id = 51; // ID do nó sentinela de fim

   head->proximo = tail; // Head aponta para o Tail
   tail->anterior = head; // Tail aponta para o Head

    head->anterior = nullptr; // Head não tem anterior
    tail->proximo = nullptr; // Tail não tem próximo
}

//=====================
// Cadastrar produto
//=====================
// Função para inserir um produto na lista duplamente encadeada, 
// e confere se o id já existe na lista, caso exista, não insere o produto e exibe uma mensagem de erro
void cadastrarProduto(Produto* &head, Produto* &tail, int id, string nome, float valor, int estoque, bool ativo) {

    // Verificar se o ID já existe na lista
    Produto* atual = head->proximo; // Começar a verificação a partir do primeiro produto real (id >= 1)
    while (atual != tail) {
        if (atual->id == id) {
            cout << "Erro: ID já existe no estoque." << endl;
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
    novoProduto->ativo = ativo; // Define o status do produto conforme o parâmetro recebido
    // Inserir o novo produto na posição correta para manter a lista ordenada por ID
    Produto* atualInsercao = head->proximo; // Começar a inserção a partir do primeiro produto real (Id = 1)
    
    while (atualInsercao != tail && atualInsercao->id < id) {
        atualInsercao = atualInsercao->proximo; // Confere a posição correta para inserção comparando se o ID do produto atual é menor que o ID do novo produto
    }

    novoProduto->proximo = atualInsercao;
    novoProduto->anterior = atualInsercao->anterior;

    atualInsercao->anterior->proximo = novoProduto;
    atualInsercao->anterior = novoProduto;


    
}

//====================
// Contador de produtos
//====================

//Conta quantos produtos estão dentro da maquina

int contarProdutos(Produto* head, Produto* tail) {
    int contador = 0;
    Produto* atual = head->proximo; // Começar a contagem a partir do primeiro produto real (Id = 1)
    while (atual != tail) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

//====================
// INSERIR NA MAQUINA
//====================

void inserirNaMaquina(Produto* &head, Produto* &tail, int id, string nome, float valor, int estoque, bool ativo) {
    if (contarProdutos(head, tail) >= 50) {
        cout << "Erro: Capacidade máxima de produtos atingida." << endl;
        return;
    }
    cadastrarProduto(head, tail, id, nome, valor, estoque, ativo = true); // O produto é inserido como ativo na máquina
    // A função cadastrarProduto já verifica se o ID é único e insere o produto na posição correta
    cout << "Produto cadastrado com sucesso!" << endl;
}

// =====================
// LISTAR PRODUTOS
// ======================

void listarProdutos(Produto* head, Produto* tail){
     
    Produto* atual = head->proximo; // Começar a listagem a partir do primeiro produto real (Id = 1)
    if (atual == tail) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }
    cout << "Produtos cadastrados:" << endl;
    while (atual != tail) {
        cout << "ID: " << atual->id << "| Nome: " << atual->nome << "| Valor: R$ " << atual->valor << "| Estoque: " << atual->estoque << "| Ativo: " << (atual->ativo ? "Sim" : "Não") << endl;
        
        atual = atual->proximo; // Avançar para o próximo produto na lista
    }



}


// ====================
// MENU ADMIN
// ====================

void menuAdmin(Produto* &head, Produto* &tail) {
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
                
                }
                cout << "Digite o nome do produto: ";
                cin >> nome;
            }
        }
    }





int main(){
    cout << "Maquina de vendas de conveniencia" << endl;
    // Pressiona enter para acessar o menu de usuario padrao e digite 9 para acessar administrativo
    
    return 0;
};
