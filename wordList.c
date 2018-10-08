#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"

Node *create_new_node(char *word) {
    Node *n_ptr;
    n_ptr = calloc(1, sizeof(Node));
    if (n_ptr == NULL) {
        perror("Error: ");
    }
    n_ptr->word = strdup(word);
    n_ptr->left = NULL;
    n_ptr->right = NULL;
    n_ptr->freq = 1;
    return n_ptr;
    }

/* Word tree sorted lexicographically */
Node *insert_word_tree(Node *node_ptr, char *word) {
    if (node_ptr == NULL) {
        node_ptr = create_new_node(word);
    }
    /* Word is the same as node_word */
    else if (strcmp(node_ptr->word, word) == 0) {
        node_ptr->freq++;
    }
    /* Word is greater than node_word, go right*/
    else if (strcmp(node_ptr->word, word) < 0) {
        node_ptr->right = insert_word_tree(node_ptr->right, word);
    }
    /* Word is less than node_word, go left */
    else {
        node_ptr->left = insert_word_tree(node_ptr->left, word);
    }
    return node_ptr;
}

/* Occurrence tree sorted by frequency */
Node *insert_node(Node *node_ptr, Node *new_node) {
    int cmp_num;
    /* Empty tree root node */
    if (node_ptr == NULL) {
        node_ptr = new_node;
    }
    /* If new node same freq compare strings */
    else if (node_ptr->freq == new_node->freq) {
        /* str 1 > str 2 go left */
        if ((cmp_num = strcmp(node_ptr->word, new_node->word)) > 0) {
            node_ptr->left = insert_node(node_ptr->left, new_node);
        }
        /* str 1 < str 2 go right */
        else if (cmp_num < 0) {
            node_ptr->right = insert_node(node_ptr->right, new_node);
        }
    }
    /* If new node freq less go left */
    else if (node_ptr->freq > new_node->freq) {
        node_ptr->left = insert_node(node_ptr->left, new_node);
    }
    /* If new node freq greater go right */
    else {
        node_ptr->right = insert_node(node_ptr->right, new_node);
    }
    return node_ptr;
}

/* Builds occurrence tree from word tree */
Node *post_order_build(Node *word_root, Node *occurrence_root) {
    if(word_root != NULL) {
        post_order_build(word_root->left, occurrence_root);
        post_order_build(word_root->right, occurrence_root);
        occurrence_root = insert_node(occurrence_root, word_root);
    }
    return occurrence_root;
}

/* Free the tree when all is done and increment unique characters */
void free_tree(Node *root) {
    if(root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root->word);
        free(root);
    }
}

/* For checking purposes */
void print_tree(Node *root) {
    if(root != NULL) {
        print_tree(root->right);
        print_tree(root->left);
        printf("         %d %s\n", root->freq, root->word);
    }
}

/* Returns the unique number of nodes in tree */
unsigned int count_tree(Node *root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return 1 + count_tree(root->left) + count_tree(root->right);
    }
}

/* Prints inorder traversal */
void print_inorder(Node *root) {
    if (root != NULL) {
        print_inorder(root->right);
        printf(" %d %s\n", root->freq, root->word);
        print_inorder(root->left);
    }
}
     
