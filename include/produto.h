//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#ifndef PRODUTO_H
#define PRODUTO_H

#include <string> // Biblioteca para manipulação de strings

using namespace std;

//==============================
// STATUS PRODUTO
//==============================
// Enum para controlar o status do produto de forma mais completa
enum StatusProduto {
    INATIVO,
    ATIVO,
    ESGOTADO,
    MANUTENCAO
};

//==============================
// PRODUTO
//==============================
// Struct de No Duplo que armazenara os dados dos produtos cadastrados
struct Produto {
    int id; //id do produto cadastrado na lista
    string nome;
    float valor;
    int estoqueTotal; // quantidade total do produto disponível para recarga
    StatusProduto status; // indica a situação atual do produto
    Produto *proximo;
    Produto *anterior;
};

//==============================
// SLOT
//==============================
// Struct que representa um local físico da maquina
struct Slot {
    int local; //local físico da maquina, de 1 até 50
    Produto* produto; //produto carregado no local
    int quantidadeSlot; //quantidade carregada no local
    bool ativo; //indica se o local está ativo para venda
};

void inicializarEstoqueProduto(Produto* &head, Produto* &tail);
void inicializarSlots(Slot slots[]);
int contarProdutosCadastrados(Produto* head, Produto* tail);
int contarProdutosAtivos(Slot slots[]);
Produto* buscarProdutoPorId(Produto* head, Produto* tail, int id);
bool nomeProdutoExiste(Produto* head, Produto* tail, string nome);
void buscarLocaisOcupados(Slot slots[], bool blacklist[]);
void listarLocaisDisponiveis(Slot slots[]);
bool cadastrarProduto(Produto* &head, Produto* &tail, string nome, float valor, int estoqueTotal);
bool ativarProduto(Produto* head, Produto* tail, Slot slots[], int id, int local, int quantidadeSlot);
bool alterarLocalProduto(Slot slots[], int localAtual, int novoLocal);
bool desativarProduto(Produto* head, Produto* tail, Slot slots[], int local, StatusProduto novoStatus);
bool reporEstoqueTotal(Produto* head, Produto* tail, int id, int quantidade);
bool reporSlot(Slot slots[], int local, int quantidade);
void listarProdutos(Produto* head, Produto* tail);
void listarSlots(Slot slots[]);
void listarProdutosDisponiveis(Slot slots[]);
void listarProdutosOrdenadosPorValor(Produto* head, Produto* tail);
void listarProdutosOrdenadosPorEstoque(Produto* head, Produto* tail);
void cadastrarEstoqueTeste(Produto* &head, Produto* &tail);
void destruirLista(Produto* &head, Produto* &tail);
string statusParaTexto(StatusProduto status);

#endif
