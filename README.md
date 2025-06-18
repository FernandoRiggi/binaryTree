# Trabalho Prático 05 - Árvore Binária

Este repositório contém um programa em linguagem C que implementa um Tipo Abstrato de Dados (TAD) Árvore Binária, incluindo a criação da árvore a partir de uma representação textual, travessias e outras operações.

## Integrantes do Grupo:
* Fernando Souza De Riggi
* Filipe Gioanini Braga

## Descrição do Trabalho

O objetivo deste trabalho é implementar um TAD Árvore Binária  em linguagem C. A principal funcionalidade é a capacidade de construir a árvore a partir de uma representação textual específica em parênteses, além de realizar diversas operações sobre ela.

### Operações Implementadas:
* **`create <representacao_textual>`**: Cria a árvore binária a partir de uma string no formato `(NÓ,(SUB_ARVORE_ESQUERDA),(SUB_ARVORE_DIREITA))`. Por exemplo, `(A,(B,(),()),(C,(F,(),()),()))`. A representação `()` indica uma sub-árvore vazia. O programa verifica se a expressão está mal formada, ou seja, se os parênteses estão corretamente aninhados e a estrutura é válida.
* **`pre`**: Imprime a ordem de visitação dos nós da árvore em pré-ordem (raiz, esquerda, direita).
* **`in`**: Imprime a ordem de visitação dos nós da árvore em in-ordem (esquerda, raiz, direita).
* **`post`**: Imprime a ordem de visitação dos nós da árvore em pós-ordem (esquerda, direita, raiz).
* **`height <n>`**: Imprime a altura do nó `n`. A altura de um nó folha é 0.
* **`print`**: Imprime toda a árvore em modo texto, buscando deixar clara a relação de hierarquia entre os nós.

## Requisitos de Implementação

* Todo o código foi implementado em linguagem C.
* Foi utilizado um TAD Árvore Binária (`t_binary_tree`), com arquivos `.h` para declarações e `.c` para as implementações.
* Verificação de expressões mal formadas na operação `create`.
* Um `Makefile` foi incluído para facilitar a compilação do código.

## Entrada e Saída

O programa recebe comandos via entrada padrão de forma interativa. Cada comando deve ser digitado em uma nova linha.

### Exemplo de Utilização:

**Comandos:**

```
create (A,(B,(),()),(C,(F,(),()),()))
print
pre
in
post
height A
height C
height F
height B
height Z
exit
```

**Saída Esperada (para a primeira 'create' do exemplo):**

```
Arvore criada com sucesso.
Representacao da arvore:
C
F
A
B
Pre-ordem: A B C F
In-ordem: B A F C
Post-ordem: B F C A
Altura do no 'A': 2
Altura do no 'C': 1
Altura do no 'F': 0
Altura do no 'B': 0
No 'Z' nao encontrado na arvore.
Saindo do programa.
```

**Exemplo de Expressão Mal Formada:**
Para a entrada `create (A,(B,()),(C,(F,(),()),()))` , o programa deve reportar um erro, conforme o exemplo do trabalho:

```
invalid
```

## Como Compilar e Executar

Para compilar o projeto, navegue até o diretório raiz do projeto no seu terminal e execute:

```bash
make
```

Isso criará um executável chamado binary_tree_simulator.

Para executar o programa, você pode fornecer os comandos de forma interativa:

```
./binary_tree_simulator
```
