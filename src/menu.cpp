//FATEC BEBEDOURO 2026 - 4° SEMESTRE BIG DATA NO AGRONEGÓCIO
//ALUNO: VICTOR DOS SANTOS QUEIROZ | RA: 2801262423001
//ALUNO: IGOR IFRAN | RA: 280126423002

#include <iostream> // Biblioteca para entrada e saída de dados
#include <string> // Biblioteca para manipulação de strings
#include <limits> // Biblioteca para limpar o buffer de entrada
#include "../include/menu.h"

using namespace std;

//====================
// LIMPAR BUFFER
//====================

//Limpa o buffer de entrada para evitar erro nas próximas leituras
void limparBufferEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//====================
// LER INTEIRO
//====================

//Lê um número inteiro e trata entrada inválida
bool lerInteiro(string mensagem, int &valor) {
    cout << mensagem;
    cin >> valor;

    if (cin.fail()) {
        cout << "Erro: Digite um numero inteiro valido." << endl;
        limparBufferEntrada();
        return false;
    }

    limparBufferEntrada();
    return true;
}

//====================
// LER FLOAT
//====================

//Lê um número decimal e trata entrada inválida
bool lerFloat(string mensagem, float &valor) {
    cout << mensagem;
    cin >> valor;

    if (cin.fail()) {
        cout << "Erro: Digite um numero valido." << endl;
        limparBufferEntrada();
        return false;
    }

    limparBufferEntrada();
    return true;
}

// ====================
// MENU USUARIO
// ====================

void menuUsuario(Slot slots[], FilaVendas &fila, Caixa &caixa) {
    char opcao;
    do {
        cout << "\n========== MENU USUARIO ==========\n";
        cout << "1 - Listar produtos disponiveis\n";
        cout << "2 - Comprar produto\n";
        cout << "3 - Voltar\n";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;
        limparBufferEntrada();

        switch (opcao) {
            case '1': {
                listarProdutosDisponiveis(slots);
                break;
            }
            case '2': {
                int local;
                int quantidade;
                float valorPago;

                listarProdutosDisponiveis(slots);

                if (!lerInteiro("Digite o local do produto: ", local)) {
                    break;
                }

                if (!lerInteiro("Digite a quantidade desejada: ", quantidade)) {
                    break;
                }

                if (!lerFloat("Digite o valor inserido na maquina: ", valorPago)) {
                    break;
                }

                realizarVenda(slots, fila, caixa, local, quantidade, valorPago);
                break;
            }
            case '3': {
                cout << "Voltando ao menu principal..." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida." << endl;
                break;
            }
        }
    } while (opcao != '3');
}

// ====================
// MENU ADMIN
// ====================

void menuAdmin(Produto* &head, Produto* &tail, Slot slots[], FilaVendas &fila, PilhaAcoes &pilha, Caixa &caixa) {
    char opcao;
    do {
        cout << "\n========== MENU ADMIN ==========\n";
        cout << "1 - Cadastrar produto\n";
        cout << "2 - Ativar produto na maquina\n";
        cout << "3 - Desativar produto\n";
        cout << "4 - Alterar local de produto\n";
        cout << "5 - Repor estoque total\n";
        cout << "6 - Repor slot\n";
        cout << "7 - Listar produtos\n";
        cout << "8 - Listar produtos por valor\n";
        cout << "A - Listar produtos por estoque\n";
        cout << "B - Listar slots ativos\n";
        cout << "C - Ver locais disponiveis\n";
        cout << "D - Ver faturamento\n";
        cout << "E - Ver historico de vendas\n";
        cout << "F - Ver ultimas acoes admin\n";
        cout << "G - Cadastrar estoque teste\n";
        cout << "S - Voltar\n";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;
        limparBufferEntrada();

        switch (opcao) {
            case '1': {
                string nome;
                float valor;
                int estoqueTotal;

                cout << "Digite o nome do produto: ";
                getline(cin, nome);

                if (!lerFloat("Digite o valor do produto: ", valor)) {
                    break;
                }

                if (!lerInteiro("Digite o estoque total do produto: ", estoqueTotal)) {
                    break;
                }

                if (cadastrarProduto(head, tail, nome, valor, estoqueTotal)) {
                    cout << "Produto cadastrado com sucesso!" << endl;
                    empilharAcao(pilha, "Produto cadastrado: " + nome);
                }
                break;
            }
            case '2': {
                int id;
                int local;
                int quantidadeSlot;

                listarProdutos(head, tail);
                listarLocaisDisponiveis(slots);

                if (!lerInteiro("Digite o ID do produto: ", id)) {
                    break;
                }

                if (!lerInteiro("Digite o local na maquina: ", local)) {
                    break;
                }

                if (!lerInteiro("Digite a quantidade para carregar no local: ", quantidadeSlot)) {
                    break;
                }

                if (ativarProduto(head, tail, slots, id, local, quantidadeSlot)) {
                    empilharAcao(pilha, "Produto ativado no local " + to_string(local));
                }
                break;
            }
            case '3': {
                int local;
                int escolhaStatus;
                StatusProduto novoStatus = INATIVO;

                listarSlots(slots);

                if (!lerInteiro("Digite o local que deseja desativar: ", local)) {
                    break;
                }

                cout << "1 - Inativo\n";
                cout << "2 - Esgotado\n";
                cout << "3 - Manutencao\n";

                if (!lerInteiro("Escolha o novo status do produto: ", escolhaStatus)) {
                    break;
                }

                if (escolhaStatus == 2) {
                    novoStatus = ESGOTADO;
                } else if (escolhaStatus == 3) {
                    novoStatus = MANUTENCAO;
                }

                if (desativarProduto(head, tail, slots, local, novoStatus)) {
                    empilharAcao(pilha, "Produto desativado do local " + to_string(local));
                }
                break;
            }
            case '4': {
                int localAtual;
                int novoLocal;

                listarSlots(slots);
                listarLocaisDisponiveis(slots);

                if (!lerInteiro("Digite o local atual do produto: ", localAtual)) {
                    break;
                }

                if (!lerInteiro("Digite o novo local do produto: ", novoLocal)) {
                    break;
                }

                if (alterarLocalProduto(slots, localAtual, novoLocal)) {
                    empilharAcao(pilha, "Produto movido do local " + to_string(localAtual) + " para o local " + to_string(novoLocal));
                }
                break;
            }
            case '5': {
                int id;
                int quantidade;

                listarProdutos(head, tail);

                if (!lerInteiro("Digite o ID do produto: ", id)) {
                    break;
                }

                if (!lerInteiro("Digite a quantidade para repor no estoque total: ", quantidade)) {
                    break;
                }

                if (reporEstoqueTotal(head, tail, id, quantidade)) {
                    empilharAcao(pilha, "Estoque total reposto para produto ID " + to_string(id));
                }
                break;
            }
            case '6': {
                int local;
                int quantidade;

                listarSlots(slots);

                if (!lerInteiro("Digite o local que deseja repor: ", local)) {
                    break;
                }

                if (!lerInteiro("Digite a quantidade para carregar no slot: ", quantidade)) {
                    break;
                }

                if (reporSlot(slots, local, quantidade)) {
                    empilharAcao(pilha, "Slot reposto no local " + to_string(local));
                }
                break;
            }
            case '7': {
                listarProdutos(head, tail);
                break;
            }
            case '8': {
                listarProdutosOrdenadosPorValor(head, tail);
                break;
            }
            case 'A':
            case 'a': {
                listarProdutosOrdenadosPorEstoque(head, tail);
                break;
            }
            case 'B':
            case 'b': {
                listarSlots(slots);
                break;
            }
            case 'C':
            case 'c': {
                listarLocaisDisponiveis(slots);
                break;
            }
            case 'D':
            case 'd': {
                listarFaturamento(caixa, slots);
                break;
            }
            case 'E':
            case 'e': {
                listarHistoricoVendas(fila);
                break;
            }
            case 'F':
            case 'f': {
                listarUltimasAcoes(pilha);
                break;
            }
            case 'G':
            case 'g': {
                cadastrarEstoqueTeste(head, tail);
                empilharAcao(pilha, "Estoque de teste cadastrado");
                break;
            }
            case 'S':
            case 's': {
                cout << "Voltando ao menu principal..." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida." << endl;
                break;
            }
        }
    } while (opcao != 'S' && opcao != 's');
}
