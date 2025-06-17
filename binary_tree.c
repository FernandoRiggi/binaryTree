#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binary_tree.h"

t_binary_tree* create_tree() {
    t_binary_tree* tree = malloc(sizeof(t_binary_tree));
    if (tree == NULL) {
        perror("Erro ao alocar memoria para a arvore");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

t_node* create_node(char item) {
    t_node* node = malloc(sizeof(t_node));
    if (node == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void pre_order(t_node* node) {
    if (node != NULL) {
        printf("%c ", node->item);
        pre_order(node->left);
        pre_order(node->right);
    }
}

void in_order(t_node* node) {
    if (node != NULL) {
        in_order(node->left);
        printf("%c ", node->item);
        in_order(node->right);
    }
}

void post_order(t_node* node) {
    if (node != NULL) {
        post_order(node->left);
        post_order(node->right);
        printf("%c ", node->item);
    }
}

void destroy_tree_rec(t_node *node) {
    if (node) {
        destroy_tree_rec(node->left);
        destroy_tree_rec(node->right);
        free(node);
    }
}

void destroy_tree(t_binary_tree* tree) {
    if (tree) {
        destroy_tree_rec(tree->root);
        free(tree);
    }
}

static void skip_whitespace(const char** str_ptr) {
    while (**str_ptr != '\0' && isspace(**str_ptr)) {
        (*str_ptr)++;
    }
}

static t_node* parse_tree_string_rec(const char** str_ptr) {
    skip_whitespace(str_ptr);

    if (**str_ptr != '(') {
        return NULL;
    }
    (*str_ptr)++;

    skip_whitespace(str_ptr);

    if (**str_ptr == ')') {
        (*str_ptr)++;
        return NULL;
    }

    char node_item = **str_ptr;
    (*str_ptr)++;

    t_node* new_node = create_node(node_item);
    if (new_node == NULL) {
        return NULL;
    }

    skip_whitespace(str_ptr);
    if (**str_ptr != ',') {
        destroy_tree_rec(new_node);
        return NULL;
    }
    (*str_ptr)++;

    new_node->left = parse_tree_string_rec(str_ptr);
    if (new_node->left == NULL && !(**str_ptr == ')' || **str_ptr == ',')) {
        return NULL;
    }

    skip_whitespace(str_ptr);
    if (**str_ptr != ',') {
        destroy_tree_rec(new_node);
        return NULL;
    }
    (*str_ptr)++;

    new_node->right = parse_tree_string_rec(str_ptr);
    if (new_node->right == NULL && !(**str_ptr == ')')) {
        return NULL;
    }

    skip_whitespace(str_ptr);
    if (**str_ptr != ')') {
        destroy_tree_rec(new_node);
        return NULL;
    }
    (*str_ptr)++;

    return new_node;
}

t_binary_tree* create_from_text(const char* text_representation) {
    t_binary_tree* tree = create_tree();
    if (tree == NULL) return NULL;

    const char* current_char_ptr = text_representation;

    int open_paren_count = 0;
    int close_paren_count = 0;
    for (int i = 0; text_representation[i] != '\0'; i++) {
        if (text_representation[i] == '(') open_paren_count++;
        else if (text_representation[i] == ')') close_paren_count++;
    }
    if (open_paren_count != close_paren_count) {
        fprintf(stderr, "Erro: Expressao mal formada. Parenteses desbalanceados.\n");
        destroy_tree(tree);
        return NULL;
    }

    tree->root = parse_tree_string_rec(&current_char_ptr);

    if (tree->root == NULL && !(strlen(text_representation) == 2 && text_representation[0] == '(' && text_representation[1] == ')')) {
         destroy_tree(tree);
         return NULL;
    }

    skip_whitespace(&current_char_ptr);
    if (*current_char_ptr != '\0') {
        fprintf(stderr, "Erro: Expressao mal formada. Caracteres extras apos a definicao da arvore: '%s'\n", current_char_ptr);
        destroy_tree(tree);
        return NULL;
    }

    return tree;
}

int get_node_height(t_node* node) {
    if (node == NULL) {
        return -1;
    }
    if (node->left == NULL && node->right == NULL) {
        return 0;
    }

    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

t_node* find_node(t_node* root, char item) {
    if (root == NULL) {
        return NULL;
    }
    if (root->item == item) {
        return root;
    }

    t_node* found_left = find_node(root->left, item);
    if (found_left != NULL) {
        return found_left;
    }

    return find_node(root->right, item);
}

void print_tree(t_node* node, int level) {
    if (node == NULL) {
        return;
    }

    print_tree(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("%c\n", node->item);

    print_tree(node->left, level + 1);
}