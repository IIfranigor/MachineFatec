# Máquina de Vendas - Algoritmos Avançados

Projeto desenvolvido em C++ para simular uma máquina de vendas de conveniência. O sistema possui modo usuário e modo administrador, controle de produtos, slots físicos da máquina, estoque, vendas, troco, faturamento e histórico.

## Alunos

- Victor dos Santos Queiroz - RA: 2801262423001
- Igor Ifran - RA: 280126423002

## Funcionalidades

- Cadastro de produtos com lista duplamente encadeada.
- Controle de 50 slots físicos da máquina.
- Separação entre estoque total e quantidade carregada no slot.
- Modo usuário ativo por padrão.
- Compra de produtos com cálculo de troco.
- Redução automática do estoque do slot após venda.
- Modo administrador com senha.
- Reposição de estoque total e de slots.
- Listagem de produtos e locais disponíveis.
- Ordenação de produtos por valor e por estoque usando Selection Sort.
- Fila de vendas para histórico.
- Pilha de ações administrativas.
- Cálculo de faturamento atual e faturamento previsto.

## Estruturas Utilizadas

- `struct`
- Alocação dinâmica com `new` e `delete`
- Lista duplamente encadeada
- Fila
- Pilha
- Selection Sort

## Estrutura do Projeto

```text
.
├── main.cpp
├── include
│   ├── menu.h
│   ├── produto.h
│   └── venda.h
└── src
    ├── menu.cpp
    ├── produto.cpp
    └── venda.cpp
```

## Como Compilar no Linux Mint

Instale o compilador, se necessário:

```bash
sudo apt update
sudo apt install g++
```

Compile o projeto:

```bash
g++ -Wall -Wextra -std=c++11 main.cpp src/produto.cpp src/menu.cpp src/venda.cpp -Iinclude -o maquina_vendas
```

Execute:

```bash
./maquina_vendas
```

## Como Compilar no Windows com CL

No terminal do Visual Studio Developer Command Prompt:

```bat
cl /EHsc main.cpp src\produto.cpp src\menu.cpp src\venda.cpp /I include /Fe:maquina_vendas.exe
```

Execute:

```bat
maquina_vendas.exe
```

## Como Usar

Ao iniciar o programa, aparece o menu principal:

```text
Pressione ENTER para acessar o menu usuario, digite 9 para admin ou 0 para sair
```

### Modo Usuário

Pressione `ENTER` para acessar.

Opções principais:

- Listar produtos disponíveis.
- Comprar produto.
- Informar local do produto.
- Informar quantidade desejada.
- Informar valor inserido.
- Receber troco, se houver.

### Modo Administrador

Digite `9` no menu principal.

Senha:

```text
senha123
```

Opções principais:

- Cadastrar produto.
- Ativar produto em um slot.
- Desativar produto.
- Alterar local de produto.
- Repor estoque total.
- Repor slot.
- Listar produtos.
- Listar produtos ordenados por valor.
- Listar produtos ordenados por estoque.
- Ver faturamento.
- Ver histórico de vendas.
- Ver últimas ações administrativas.
- Cadastrar estoque de teste.

## Observações

O sistema permite cadastrar mais de 50 produtos no estoque geral, mas apenas 50 produtos podem estar ativos ao mesmo tempo na máquina, pois existem 50 slots físicos disponíveis.

Para testar rapidamente, acesse o modo administrador e use a opção de cadastrar estoque de teste. Depois ative alguns produtos em slots e volte ao modo usuário para realizar compras.
