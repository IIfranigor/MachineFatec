//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream> // Biblioteca para entrada e saída de dados
#include <string> // Biblioteca para manipulação de strings
#include "../include/venda.h"

using namespace std;

//==============================
// INICIALIZAR FILA
//==============================

//Inicializa a fila de vendas
void inicializarFila(FilaVendas &fila) {
    fila.inicio = nullptr;
    fila.fim = nullptr;
    fila.totalVendas = 0;
}

//==============================
// ENFILEIRAR VENDA
//==============================

//Adiciona uma venda ao final da fila
void enfileirarVenda(FilaVendas &fila, string nomeProduto, int local, int quantidade, float valorTotal, float valorPago, float troco) {
    Venda* novaVenda = new Venda;
    novaVenda->idVenda = fila.totalVendas + 1;
    novaVenda->nomeProduto = nomeProduto;
    novaVenda->local = local;
    novaVenda->quantidade = quantidade;
    novaVenda->valorTotal = valorTotal;
    novaVenda->valorPago = valorPago;
    novaVenda->troco = troco;
    novaVenda->proximo = nullptr;

    if (fila.inicio == nullptr) {
        fila.inicio = novaVenda;
        fila.fim = novaVenda;
    } else {
        fila.fim->proximo = novaVenda;
        fila.fim = novaVenda;
    }

    fila.totalVendas++;
}

//==============================
// LISTAR HISTORICO DE VENDAS
//==============================

//Lista as vendas na ordem em que aconteceram
void listarHistoricoVendas(FilaVendas fila) {
    Venda* atual = fila.inicio;

    if (atual == nullptr) {
        cout << "Nenhuma venda registrada." << endl;
        return;
    }

    cout << "Historico de vendas:" << endl;
    while (atual != nullptr) {
        cout << "Venda: " << atual->idVenda << "| Produto: " << atual->nomeProduto << "| Local: " << atual->local << "| Quantidade: " << atual->quantidade << "| Total: R$ " << atual->valorTotal << "| Pago: R$ " << atual->valorPago << "| Troco: R$ " << atual->troco << endl;
        atual = atual->proximo;
    }
}

//==============================
// DESTRUIR FILA
//==============================

//Libera a memoria usada pela fila de vendas
void destruirFila(FilaVendas &fila) {
    Venda* atual = fila.inicio;

    while (atual != nullptr) {
        Venda* proximo = atual->proximo;
        atual->proximo = nullptr;
        delete atual;
        atual = proximo;
    }

    fila.inicio = nullptr;
    fila.fim = nullptr;
    fila.totalVendas = 0;
}

//==============================
// INICIALIZAR PILHA
//==============================

//Inicializa a pilha de acoes administrativas
void inicializarPilha(PilhaAcoes &pilha) {
    pilha.topo = nullptr;
}

//==============================
// EMPILHAR ACAO
//==============================

//Adiciona uma acao administrativa no topo da pilha
void empilharAcao(PilhaAcoes &pilha, string descricao) {
    AcaoAdmin* novaAcao = new AcaoAdmin;
    novaAcao->descricao = descricao;
    novaAcao->anterior = pilha.topo;
    pilha.topo = novaAcao;
}

//==============================
// LISTAR ULTIMAS ACOES
//==============================

//Lista as acoes administrativas da mais recente para a mais antiga
void listarUltimasAcoes(PilhaAcoes pilha) {
    AcaoAdmin* atual = pilha.topo;

    if (atual == nullptr) {
        cout << "Nenhuma acao administrativa registrada." << endl;
        return;
    }

    cout << "Ultimas acoes administrativas:" << endl;
    while (atual != nullptr) {
        cout << "- " << atual->descricao << endl;
        atual = atual->anterior;
    }
}

//==============================
// DESTRUIR PILHA
//==============================

//Libera a memoria usada pela pilha de acoes administrativas
void destruirPilha(PilhaAcoes &pilha) {
    AcaoAdmin* atual = pilha.topo;

    while (atual != nullptr) {
        AcaoAdmin* anterior = atual->anterior;
        atual->anterior = nullptr;
        delete atual;
        atual = anterior;
    }

    pilha.topo = nullptr;
}

//==============================
// INICIALIZAR CAIXA
//==============================

//Inicializa o faturamento atual da maquina
void inicializarCaixa(Caixa &caixa) {
    caixa.faturamentoAtual = 0;
}

//==============================
// CALCULAR TROCO
//==============================

//Calcula o troco da venda
float calcularTroco(float valorPago, float valorTotal) {
    return valorPago - valorTotal;
}

//==============================
// FATURAMENTO PREVISTO
//==============================

//Calcula quanto a maquina pode faturar com os produtos carregados nos slots
float calcularFaturamentoPrevisto(Slot slots[]) {
    float total = 0;

    for (int i = 0; i < 50; i++) {
        if (slots[i].ativo && slots[i].produto != nullptr) {
            total += slots[i].produto->valor * slots[i].quantidadeSlot;
        }
    }

    return total;
}

//==============================
// REALIZAR VENDA
//==============================

//Realiza uma venda simples, reduz estoque do slot, registra fila e soma faturamento
bool realizarVenda(Slot slots[], FilaVendas &fila, Caixa &caixa, int local, int quantidade, float valorPago) {
    if (local < 1 || local > 50) {
        cout << "Erro: Local deve estar entre 1 e 50." << endl;
        return false;
    }

    if (quantidade <= 0) {
        cout << "Erro: Quantidade deve ser maior que zero." << endl;
        return false;
    }

    Slot &slot = slots[local - 1];

    if (!slot.ativo || slot.produto == nullptr || slot.quantidadeSlot <= 0) {
        cout << "Erro: Produto indisponivel neste local." << endl;
        return false;
    }

    if (quantidade > slot.quantidadeSlot) {
        cout << "Erro: Quantidade solicitada maior que a quantidade disponivel no local." << endl;
        return false;
    }

    float valorTotal = slot.produto->valor * quantidade;

    if (valorPago < valorTotal) {
        cout << "Erro: Valor inserido insuficiente." << endl;
        cout << "Valor total da compra: R$ " << valorTotal << endl;
        return false;
    }

    float troco = calcularTroco(valorPago, valorTotal);

    Produto* produtoVendido = slot.produto;

    slot.quantidadeSlot -= quantidade;
    caixa.faturamentoAtual += valorTotal;

    enfileirarVenda(fila, produtoVendido->nome, local, quantidade, valorTotal, valorPago, troco);

    cout << "Compra realizada com sucesso!" << endl;
    cout << "Produto: " << produtoVendido->nome << endl;
    cout << "Valor total: R$ " << valorTotal << endl;
    cout << "Troco: R$ " << troco << endl;

    if (slot.quantidadeSlot == 0) {
        if (produtoVendido->estoqueTotal == 0) {
            produtoVendido->status = ESGOTADO;
        } else {
            produtoVendido->status = INATIVO;
        }
        slot.produto = nullptr;
        slot.ativo = false;
        cout << "Produto esgotado no local apos a venda." << endl;
    }

    return true;
}

//==============================
// LISTAR FATURAMENTO
//==============================

//Mostra o faturamento atual e o faturamento previsto da maquina
void listarFaturamento(Caixa caixa, Slot slots[]) {
    cout << "Faturamento atual: R$ " << caixa.faturamentoAtual << endl;
    cout << "Faturamento previsto: R$ " << calcularFaturamentoPrevisto(slots) << endl;
}
