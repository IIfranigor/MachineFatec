//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream> // Biblioteca para entrada e saída de dados
#include <string> // Biblioteca para manipulação de strings
#include "../include/produto.h"

using namespace std;

//==============================
// INICIALIZAR ESTOQUE
//==============================

void inicializarEstoqueProduto(Produto* &head, Produto* &tail) {
   head = new Produto; // Nó sentinela de início
   tail = new Produto; // Nó sentinela de fim

   head->id = 0; // ID do nó sentinela de início (sempre 0, não representa um produto real)
   head->estoqueTotal = 0; // Estoque do nó sentinela de início
   head->status = INATIVO; // Status do nó sentinela de início

   tail->id = -1; // ID do nó sentinela de fim (não representa um produto real)
   tail->estoqueTotal = 0; // Estoque do nó sentinela de fim
   tail->status = INATIVO; // Status do nó sentinela de fim

   head->proximo = tail; // Head aponta para o Tail
   tail->anterior = head; // Tail aponta para o Head

    head->anterior = nullptr; // Head não tem anterior
    tail->proximo = nullptr; // Tail não tem próximo
}

//==============================
// INICIALIZAR SLOTS
//==============================

//Inicializa os 50 locais físicos da maquina
void inicializarSlots(Slot slots[]) {
    for (int i = 0; i < 50; i++) {
        slots[i].local = i + 1;
        slots[i].produto = nullptr;
        slots[i].quantidadeSlot = 0;
        slots[i].ativo = false;
    }
}

//====================
// Contador de produtos
//====================

//Conta quantos produtos estão cadastrados na lista
int contarProdutosCadastrados(Produto* head, Produto* tail) {
    int contador = 0;
    Produto* atual = head->proximo; // Começar a contagem a partir do primeiro produto real
    while (atual != tail) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

//====================
// Contador de produtos ativos
//====================

//Conta quantos produtos estão ativos dentro da maquina
int contarProdutosAtivos(Slot slots[]) {
    int contador = 0;
    for (int i = 0; i < 50; i++) {
        if (slots[i].ativo && slots[i].produto != nullptr) {
            contador++;
        }
    }
    return contador;
}

//====================
// Buscar produto
//====================

//Busca um produto pelo id cadastrado na lista
Produto* buscarProdutoPorId(Produto* head, Produto* tail, int id) {
    Produto* atual = head->proximo; // Começar a busca a partir do primeiro produto real
    while (atual != tail) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return nullptr;
}

//====================
// Verificar nome repetido
//====================

//Verifica se já existe um produto cadastrado com o mesmo nome
bool nomeProdutoExiste(Produto* head, Produto* tail, string nome) {
    Produto* atual = head->proximo; // Começar a busca a partir do primeiro produto real
    while (atual != tail) {
        if (atual->nome == nome) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

//====================
// BUSCAR LOCAIS OCUPADOS
//====================

//Preenche uma blacklist com os locais que já estão ocupados por produtos ativos
void buscarLocaisOcupados(Slot slots[], bool blacklist[]) {
    for (int i = 1; i <= 50; i++) {
        blacklist[i] = false;
    }

    int contador = 0;
    while (contador < 50) {
        if (slots[contador].ativo && slots[contador].produto != nullptr) {
            blacklist[slots[contador].local] = true;
        }
        contador++;
    }
}

//====================
// LISTAR LOCAIS DISPONIVEIS
//====================

//Mostra quais locais de 1 a 50 ainda estão disponíveis para ativar produtos na maquina
void listarLocaisDisponiveis(Slot slots[]) {
    bool blacklist[51]; // Lista os locais bloqueados para cadastro na maquina
    bool encontrouDisponivel = false;

    buscarLocaisOcupados(slots, blacklist);

    cout << "Locais disponiveis: ";
    for (int i = 1; i <= 50; i++) {
        if (!blacklist[i]) {
            cout << i << " ";
            encontrouDisponivel = true;
        }
    }

    if (!encontrouDisponivel) {
        cout << "Nenhum local disponivel";
    }

    cout << endl;
}

//=====================
// Cadastrar produto
//=====================
// Função para inserir um produto na lista duplamente encadeada,
// permitindo cadastrar mais de 50 produtos, pois o limite de 50 vale apenas para produtos ativos na maquina
bool cadastrarProduto(Produto* &head, Produto* &tail, string nome, float valor, int estoqueTotal) {

    // Verificar se o nome informado é válido
    if (nome == "") {
        cout << "Erro: Nome do produto não pode ficar vazio." << endl;
        return false;
    }

    // Verificar se o nome já existe no cadastro
    if (nomeProdutoExiste(head, tail, nome)) {
        cout << "Erro: Já existe um produto cadastrado com esse nome." << endl;
        return false;
    }

    // Verificar se o valor informado é válido
    if (valor <= 0) {
        cout << "Erro: Valor do produto deve ser maior que zero." << endl;
        return false;
    }

    // Verificar se o estoque informado é válido
    if (estoqueTotal < 0) {
        cout << "Erro: Estoque total não pode ser negativo." << endl;
        return false;
    }

    // Criar um novo produto para inserir na lista
    Produto* novoProduto = new Produto;
    novoProduto->id = contarProdutosCadastrados(head, tail) + 1;
    novoProduto->nome = nome;
    novoProduto->valor = valor;
    novoProduto->estoqueTotal = estoqueTotal;
    novoProduto->status = INATIVO; // Produto começa inativo até ser carregado em um local da maquina

    // Inserir o novo produto antes do nó sentinela de fim
    novoProduto->proximo = tail;
    novoProduto->anterior = tail->anterior;

    tail->anterior->proximo = novoProduto;
    tail->anterior = novoProduto;

    return true;
}

//====================
// ATIVAR PRODUTO
//====================

//Ativa um produto carregando uma quantidade em um local físico da maquina
bool ativarProduto(Produto* head, Produto* tail, Slot slots[], int id, int local, int quantidadeSlot) {
    bool blacklist[51]; // Lista os locais bloqueados para cadastro na maquina

    // Verificar se o ID do produto é válido
    if (id <= 0) {
        cout << "Erro: ID do produto deve ser maior que zero." << endl;
        return false;
    }

    // Verificar se a maquina já está cheia de produtos ativos
    if (contarProdutosAtivos(slots) >= 50) {
        cout << "Erro: Capacidade máxima de produtos ativos atingida." << endl;
        return false;
    }

    // Verificar se o local está dentro do limite permitido
    if (local < 1 || local > 50) {
        cout << "Erro: Local deve estar entre 1 e 50." << endl;
        return false;
    }

    // Verificar se a quantidade carregada no slot é válida
    if (quantidadeSlot <= 0) {
        cout << "Erro: Quantidade carregada no local deve ser maior que zero." << endl;
        return false;
    }

    buscarLocaisOcupados(slots, blacklist);

    // Verificar se o local escolhido está na blacklist de locais ocupados
    if (blacklist[local]) {
        cout << "Erro: Local já está ocupado na maquina." << endl;
        listarLocaisDisponiveis(slots);
        return false;
    }

    Produto* produto = buscarProdutoPorId(head, tail, id);

    if (produto == nullptr) {
        cout << "Erro: Produto não encontrado." << endl;
        return false;
    }

    if (produto->status == ATIVO) {
        cout << "Erro: Produto já está ativo na maquina." << endl;
        return false;
    }

    if (produto->estoqueTotal <= 0) {
        cout << "Erro: Produto sem estoque total para carregar na maquina." << endl;
        produto->status = ESGOTADO;
        return false;
    }

    if (quantidadeSlot > produto->estoqueTotal) {
        cout << "Erro: Quantidade carregada não pode ser maior que o estoque total." << endl;
        return false;
    }

    slots[local - 1].produto = produto;
    slots[local - 1].quantidadeSlot = quantidadeSlot;
    slots[local - 1].ativo = true;

    produto->estoqueTotal -= quantidadeSlot;
    produto->status = ATIVO;

    cout << "Produto ativado na maquina com sucesso!" << endl;
    return true;
}

//====================
// ALTERAR LOCAL PRODUTO
//====================

//Altera o local de um produto ativo validando conflito com outros locais ocupados
bool alterarLocalProduto(Slot slots[], int localAtual, int novoLocal) {
    bool blacklist[51]; // Lista os locais bloqueados para cadastro na maquina

    if (localAtual < 1 || localAtual > 50) {
        cout << "Erro: Local atual deve estar entre 1 e 50." << endl;
        return false;
    }

    if (novoLocal < 1 || novoLocal > 50) {
        cout << "Erro: Novo local deve estar entre 1 e 50." << endl;
        return false;
    }

    Slot &slotAtual = slots[localAtual - 1];

    if (!slotAtual.ativo || slotAtual.produto == nullptr) {
        cout << "Erro: Local atual não possui produto ativo." << endl;
        return false;
    }

    if (localAtual == novoLocal) {
        cout << "Erro: Novo local deve ser diferente do local atual." << endl;
        return false;
    }

    buscarLocaisOcupados(slots, blacklist);

    if (blacklist[novoLocal]) {
        cout << "Erro: Novo local já está ocupado na maquina." << endl;
        listarLocaisDisponiveis(slots);
        return false;
    }

    slots[novoLocal - 1].produto = slotAtual.produto;
    slots[novoLocal - 1].quantidadeSlot = slotAtual.quantidadeSlot;
    slots[novoLocal - 1].ativo = true;

    slotAtual.produto = nullptr;
    slotAtual.quantidadeSlot = 0;
    slotAtual.ativo = false;

    cout << "Local do produto alterado com sucesso!" << endl;
    return true;
}

//====================
// DESATIVAR PRODUTO
//====================

//Desativa um produto e devolve a quantidade do slot ao estoque total
bool desativarProduto(Produto* head, Produto* tail, Slot slots[], int local, StatusProduto novoStatus) {
    if (local < 1 || local > 50) {
        cout << "Erro: Local deve estar entre 1 e 50." << endl;
        return false;
    }

    Slot &slot = slots[local - 1];

    if (!slot.ativo || slot.produto == nullptr) {
        cout << "Erro: Local não possui produto ativo." << endl;
        return false;
    }

    slot.produto->estoqueTotal += slot.quantidadeSlot;
    slot.produto->status = novoStatus;
    slot.produto = nullptr;
    slot.quantidadeSlot = 0;
    slot.ativo = false;

    cout << "Produto desativado com sucesso!" << endl;
    return true;
}

//====================
// REPOR ESTOQUE TOTAL
//====================

//Adiciona unidades ao estoque total do produto cadastrado
bool reporEstoqueTotal(Produto* head, Produto* tail, int id, int quantidade) {
    if (id <= 0) {
        cout << "Erro: ID do produto deve ser maior que zero." << endl;
        return false;
    }

    if (quantidade <= 0) {
        cout << "Erro: Quantidade de reposicao deve ser maior que zero." << endl;
        return false;
    }

    Produto* produto = buscarProdutoPorId(head, tail, id);

    if (produto == nullptr) {
        cout << "Erro: Produto nao encontrado." << endl;
        return false;
    }

    produto->estoqueTotal += quantidade;

    if (produto->status == ESGOTADO) {
        produto->status = INATIVO;
    }

    cout << "Estoque total reposto com sucesso!" << endl;
    return true;
}

//====================
// REPOR SLOT
//====================

//Adiciona unidades ao local ativo usando o estoque total do produto
bool reporSlot(Slot slots[], int local, int quantidade) {
    if (local < 1 || local > 50) {
        cout << "Erro: Local deve estar entre 1 e 50." << endl;
        return false;
    }

    if (quantidade <= 0) {
        cout << "Erro: Quantidade de reposicao deve ser maior que zero." << endl;
        return false;
    }

    Slot &slot = slots[local - 1];

    if (!slot.ativo || slot.produto == nullptr) {
        cout << "Erro: Local nao possui produto ativo." << endl;
        return false;
    }

    if (quantidade > slot.produto->estoqueTotal) {
        cout << "Erro: Quantidade de reposicao maior que o estoque total disponivel." << endl;
        return false;
    }

    slot.quantidadeSlot += quantidade;
    slot.produto->estoqueTotal -= quantidade;

    cout << "Slot reposto com sucesso!" << endl;
    return true;
}

// =====================
// LISTAR PRODUTOS
// ======================

void listarProdutos(Produto* head, Produto* tail){

    Produto* atual = head->proximo; // Começar a listagem a partir do primeiro produto real
    if (atual == tail) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }
    cout << "Produtos cadastrados:" << endl;
    while (atual != tail) {
        cout << "ID: " << atual->id << "| Nome: " << atual->nome << "| Valor: R$ " << atual->valor << "| Estoque total: " << atual->estoqueTotal << "| Status: " << statusParaTexto(atual->status) << endl;

        atual = atual->proximo; // Avançar para o próximo produto na lista
    }
}

// =====================
// LISTAR SLOTS
// ======================

void listarSlots(Slot slots[]){
    cout << "Slots da maquina:" << endl;

    bool encontrou = false;
    for (int i = 0; i < 50; i++) {
        if (slots[i].ativo && slots[i].produto != nullptr) {
            cout << "Local: " << slots[i].local << "| Produto: " << slots[i].produto->nome << "| Quantidade no local: " << slots[i].quantidadeSlot << endl;
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhum slot ativo." << endl;
    }
}

// =====================
// LISTAR PRODUTOS DISPONIVEIS
// ======================

//Lista os produtos disponiveis para compra no modo usuario
void listarProdutosDisponiveis(Slot slots[]){
    cout << "Produtos disponiveis para compra:" << endl;

    bool encontrou = false;
    for (int i = 0; i < 50; i++) {
        if (slots[i].ativo && slots[i].produto != nullptr && slots[i].quantidadeSlot > 0) {
            cout << "Local: " << slots[i].local << "| Produto: " << slots[i].produto->nome << "| Valor: R$ " << slots[i].produto->valor << "| Disponivel: " << slots[i].quantidadeSlot << endl;
            encontrou = true;
        }
    }

    if (!encontrou) {
        cout << "Nenhum produto disponivel para compra." << endl;
    }
}

// =====================
// LISTAR PRODUTOS ORDENADOS POR VALOR
// ======================

//Lista os produtos em ordem crescente de valor usando Selection Sort
void listarProdutosOrdenadosPorValor(Produto* head, Produto* tail) {
    int total = contarProdutosCadastrados(head, tail);

    if (total == 0) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }

    Produto** produtos = new Produto*[total];
    Produto* atual = head->proximo;
    int indice = 0;

    while (atual != tail) {
        produtos[indice] = atual;
        indice++;
        atual = atual->proximo;
    }

    for (int i = 0; i < total - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < total; j++) {
            if (produtos[j]->valor < produtos[menor]->valor) {
                menor = j;
            }
        }

        Produto* temp = produtos[i];
        produtos[i] = produtos[menor];
        produtos[menor] = temp;
    }

    cout << "Produtos ordenados por valor:" << endl;
    for (int i = 0; i < total; i++) {
        cout << "ID: " << produtos[i]->id << "| Nome: " << produtos[i]->nome << "| Valor: R$ " << produtos[i]->valor << "| Estoque total: " << produtos[i]->estoqueTotal << endl;
    }

    delete[] produtos;
}

// =====================
// LISTAR PRODUTOS ORDENADOS POR ESTOQUE
// ======================

//Lista os produtos em ordem crescente de estoque usando Selection Sort
void listarProdutosOrdenadosPorEstoque(Produto* head, Produto* tail) {
    int total = contarProdutosCadastrados(head, tail);

    if (total == 0) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }

    Produto** produtos = new Produto*[total];
    Produto* atual = head->proximo;
    int indice = 0;

    while (atual != tail) {
        produtos[indice] = atual;
        indice++;
        atual = atual->proximo;
    }

    for (int i = 0; i < total - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < total; j++) {
            if (produtos[j]->estoqueTotal < produtos[menor]->estoqueTotal) {
                menor = j;
            }
        }

        Produto* temp = produtos[i];
        produtos[i] = produtos[menor];
        produtos[menor] = temp;
    }

    cout << "Produtos ordenados por estoque total:" << endl;
    for (int i = 0; i < total; i++) {
        cout << "ID: " << produtos[i]->id << "| Nome: " << produtos[i]->nome << "| Valor: R$ " << produtos[i]->valor << "| Estoque total: " << produtos[i]->estoqueTotal << endl;
    }

    delete[] produtos;
}

//=====================
// Cadastrar estoque teste
//=====================
// Função para cadastrar um estoque simples com 20 itens para teste
void cadastrarEstoqueTeste(Produto* &head, Produto* &tail) {
    string nomes[20] = {
        "Agua mineral",
        "Refrigerante lata",
        "Suco de uva",
        "Chocolate",
        "Biscoito recheado",
        "Salgadinho",
        "Barra de cereal",
        "Cafe gelado",
        "Cha gelado",
        "Amendoim",
        "Balas sortidas",
        "Goma de mascar",
        "Cookie",
        "Bolinho",
        "Achocolatado",
        "Energetico",
        "Pao de mel",
        "Torrada",
        "Castanhas",
        "Iogurte"
    };

    float valores[20] = {
        3.50, 5.00, 4.50, 6.00, 3.00,
        4.00, 2.50, 7.00, 5.50, 3.75,
        2.00, 1.50, 4.25, 3.50, 4.00,
        9.00, 3.25, 2.75, 8.50, 6.50
    };

    int estoques[20] = {
        200, 160, 120, 180, 150,
        130, 220, 90, 100, 140,
        300, 250, 110, 95, 115,
        80, 125, 135, 70, 85
    };

    for (int i = 0; i < 20; i++) {
        cadastrarProduto(head, tail, nomes[i], valores[i], estoques[i]);
    }

    cout << "Estoque de teste cadastrado com sucesso!" << endl;
}

// =====================
// DESTRUIR LISTA
// ======================

// Libera todos os nós da lista para evitar vazamento de memória
void destruirLista(Produto* &head, Produto* &tail) {
    Produto* atual = head; // Começar a destruição pelo nó sentinela de início
    while (atual != nullptr) {
        Produto* proximo = atual->proximo;
        atual->anterior = nullptr;
        atual->proximo = nullptr;
        delete atual;
        atual = proximo;
    }
    head = nullptr;
    tail = nullptr;
}

// =====================
// STATUS PARA TEXTO
// ======================

//Converte o enum de status para texto
string statusParaTexto(StatusProduto status) {
    switch (status) {
        case INATIVO:
            return "Inativo";
        case ATIVO:
            return "Ativo";
        case ESGOTADO:
            return "Esgotado";
        case MANUTENCAO:
            return "Manutencao";
        default:
            return "Desconhecido";
    }
}
