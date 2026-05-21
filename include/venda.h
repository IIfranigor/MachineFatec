//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#ifndef VENDA_H
#define VENDA_H

#include <string> // Biblioteca para manipulação de strings
#include "produto.h"

using namespace std;

//==============================
// VENDA
//==============================
// Struct de fila que armazena uma venda realizada na maquina
struct Venda {
    int idVenda;
    string nomeProduto;
    int local;
    int quantidade;
    float valorTotal;
    float valorPago;
    float troco;
    Venda* proximo;
};

//==============================
// FILA DE VENDAS
//==============================
// Struct para controlar o início e o fim da fila de vendas
struct FilaVendas {
    Venda* inicio;
    Venda* fim;
    int totalVendas;
};

//==============================
// ACAO ADMIN
//==============================
// Struct de pilha que armazena as ações administrativas
struct AcaoAdmin {
    string descricao;
    AcaoAdmin* anterior;
};

//==============================
// PILHA DE ACOES
//==============================
// Struct para controlar o topo da pilha de ações administrativas
struct PilhaAcoes {
    AcaoAdmin* topo;
};

//==============================
// CAIXA
//==============================
// Struct para controlar o faturamento da maquina
struct Caixa {
    float faturamentoAtual;
};

void inicializarFila(FilaVendas &fila);
void enfileirarVenda(FilaVendas &fila, string nomeProduto, int local, int quantidade, float valorTotal, float valorPago, float troco);
void listarHistoricoVendas(FilaVendas fila);
void destruirFila(FilaVendas &fila);

void inicializarPilha(PilhaAcoes &pilha);
void empilharAcao(PilhaAcoes &pilha, string descricao);
void listarUltimasAcoes(PilhaAcoes pilha);
void destruirPilha(PilhaAcoes &pilha);

void inicializarCaixa(Caixa &caixa);
float calcularTroco(float valorPago, float valorTotal);
float calcularFaturamentoPrevisto(Slot slots[]);
bool realizarVenda(Slot slots[], FilaVendas &fila, Caixa &caixa, int local, int quantidade, float valorPago);
void listarFaturamento(Caixa caixa, Slot slots[]);

#endif
