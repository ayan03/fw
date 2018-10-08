/* CPE 357 Assignment 2 fw */
#define SIZE 100        /* Buffer size for read_long_lines */
char *read_long_lines(FILE *file);

typedef struct Node {
    char *word;         /* Point at text */
    int freq;          /* Word occurrences */
    struct Node *left;  /* Left */
    struct Node *right; /* Right */
} Node;

Node *insert_node(Node *node_ptr, Node *new_node);
Node *insert_word_tree(Node *node_ptr, char *word);
Node *create_new_node(char *word);
Node *post_order_build(Node *word_root, Node *occurrence_root);
unsigned int count_tree(Node *root);
void free_tree(Node *root);
void print_tree(Node *root);
void print_inorder(Node *root);
