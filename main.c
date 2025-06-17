#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binary_tree.h"

#define MAX_COMMAND_LINE_LENGTH 200

int main() {
    t_binary_tree* tree = NULL;
    char command_line[MAX_COMMAND_LINE_LENGTH];
    char command[20];
    char arg_char;

    printf("Simulador de Arvore Binaria\n");
    printf("Comandos disponiveis:\n");
    printf("  create <representacao_textual>\n");
    printf("  pre\n");
    printf("  in\n");
    printf("  post\n");
    printf("  height <n>\n");
    printf("  print\n");
    printf("  exit\n");
    printf("-----------------------------------\n");

    while (1) {
        printf("Entre com o comando: ");
        if (fgets(command_line, MAX_COMMAND_LINE_LENGTH, stdin) == NULL) {
            break;
        }

        command_line[strcspn(command_line, "\n")] = 0; 

        if (sscanf(command_line, "%19s", command) == 1) { 
            if (strcmp(command, "create") == 0) {
                const char* create_keyword_end = strstr(command_line, "create");
                if (create_keyword_end != NULL) {
                    create_keyword_end += strlen("create"); 

                    while (*create_keyword_end != '\0' && isspace(*create_keyword_end)) {
                        create_keyword_end++;
                    }

                    const char* tree_string_start = create_keyword_end;

                    if (tree_string_start != NULL && *tree_string_start == '(') {
                        if (tree != NULL) {
                            destroy_tree(tree);
                            tree = NULL;
                        }
                        tree = create_from_text(tree_string_start);
                        if (tree != NULL) {
                            printf("Arvore criada com sucesso.\n");
                        } else {
                            printf("invalid\n");
                        }
                    } else {
                        printf("Erro: Comando 'create' requer uma representacao textual da arvore valida (ex: create (A,(),())).\n");
                    }
                } else {
                    printf("Erro interno de parsing do comando 'create'.\n");
                }
            } else if (strcmp(command, "pre") == 0) {
                if (tree == NULL || tree->root == NULL) {
                    printf("Arvore vazia. Nao e possivel realizar travessia em pre-ordem.\n");
                } else {
                    printf("Pre-ordem: ");
                    pre_order(tree->root);
                    printf("\n");
                }
            } else if (strcmp(command, "in") == 0) {
                if (tree == NULL || tree->root == NULL) {
                    printf("Arvore vazia. Nao e possivel realizar travessia em in-ordem.\n");
                } else {
                    printf("In-ordem: ");
                    in_order(tree->root);
                    printf("\n");
                }
            } else if (strcmp(command, "post") == 0) {
                if (tree == NULL || tree->root == NULL) {
                    printf("Arvore vazia. Nao e possivel realizar travessia em pos-ordem.\n");
                } else {
                    printf("Pos-ordem: ");
                    post_order(tree->root);
                    printf("\n");
                }
            } else if (strcmp(command, "height") == 0) {
                int char_scanned = sscanf(command_line, "%*s %c", &arg_char);
                if (char_scanned == 1) {
                    if (tree == NULL || tree->root == NULL) {
                        printf("Arvore vazia. Nao e possivel buscar a altura do no.\n");
                    } else {
                        t_node* target_node = find_node(tree->root, arg_char);
                        if (target_node != NULL) {
                            int h = get_node_height(target_node);
                            printf("Altura do no '%c': %d\n", arg_char, h);
                        } else {
                            printf("No '%c' nao encontrado na arvore.\n", arg_char);
                        }
                    }
                } else {
                    printf("Erro: Comando 'height' requer um caractere de no (ex: height A).\n");
                }
            } else if (strcmp(command, "print") == 0) {
                if (tree == NULL || tree->root == NULL) {
                    printf("Arvore vazia. Nao ha o que imprimir.\n");
                } else {
                    printf("Representacao da arvore:\n");
                    print_tree(tree->root, 0);
                }
            } else if (strcmp(command, "exit") == 0) {
                printf("Saindo do programa.\n");
                break;
            } else {
                printf("Comando desconhecido: '%s'. Digite 'help' para ver os comandos.\n", command);
            }
        } else {
            printf("Comando invalido ou linha vazia.\n");
        }
    }

    if (tree != NULL) {
        destroy_tree(tree);
    }

    return EXIT_SUCCESS;
}