//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#ifndef MENU_H
#define MENU_H

#include "produto.h"
#include "venda.h"

void limparBufferEntrada();
bool lerInteiro(string mensagem, int &valor);
bool lerFloat(string mensagem, float &valor);
void menuUsuario(Slot slots[], FilaVendas &fila, Caixa &caixa);
void menuAdmin(Produto* &head, Produto* &tail, Slot slots[], FilaVendas &fila, PilhaAcoes &pilha, Caixa &caixa);

#endif
