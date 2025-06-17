#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct _node {
    char item;
    struct _node* left;
    struct _node* right;
} t_node;

typedef struct {
    t_node* root;
} t_binary_tree;

t_binary_tree* create_tree();
t_node* create_node(char);
void pre_order(t_node*);
void in_order(t_node*);
void post_order(t_node*);
void destroy_tree_rec(t_node* node);
void destroy_tree(t_binary_tree* tree);
t_binary_tree* create_from_text(const char* text_representation);
int get_node_height(t_node* node); 
t_node* find_node(t_node* root, char item); 
void print_tree(t_node* node, int level); 

#endif