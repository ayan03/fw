#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fw.h"

/* Reads in line of arbitrary size from file stream */
char * read_long_lines(FILE *file) {
    char c;
    int count = 0;
    char * str = NULL;
    int size_count = 1;
    str = calloc(SIZE, sizeof(char));
    if (str == NULL) {
        perror("Error: ");
        return NULL;
    }
    /* Read in line character by character */
    while ((c = fgetc(file)) != '\n' && c != EOF) {
       /* If SIZE buffer isn't large enough realloc */
       if (count == (SIZE * size_count)) {
            size_count++;
            str = realloc(str, SIZE * size_count);
            if (str == NULL) {
                perror("Error: ");
                return NULL;
            }
        }
        if (isalpha(c) || c == ' ') {
            str[count] = tolower(c);
            count++;
        } 
    }
    if (count == 0) {
        free(str);
        return NULL;
    }
    str[count + 1] = '\0';
    return str;
}
int main(int argc, char *argv[]) {
    FILE *fp;
    char *reader;
    int arg_num = 10;
    int arg_len;
    int unique_words = 0;
    char *num_words = NULL;
    char *token = NULL;
    Node *word_root = NULL;
    Node *freq_root = NULL;
    
    if (argc == 1) {
        fp = stdin;
    }
    /* Takes in text file as argument and num words to be displayed*/
    else if (argc >= 3) {
       num_words = argv[1];
       for (arg_len = 0; arg_len < strlen(num_words); arg_len++) {
           if (!isdigit(num_words[arg_len])) {
               perror("Error: Input an Integer");
               return -1;
           }
       }
       arg_num = atoi(num_words);
       fp = fopen(argv[argc - 1], "r");
    }
    /* If number of words displayed is not specified */       
    else if (argc == 2) {
        fp = fopen(argv[1], "r");
    }

    /* Starts taking output from files */
    if (fp == NULL) { 
        perror("Error: ");
        return -1;
    }
    else {
        while((reader = read_long_lines(fp)) != NULL) {
            token = strtok(reader, " ");
            while (token != NULL) {
                /* Build tree sorted by word */
                word_root = insert_word_tree(word_root, token);
                token = strtok(NULL, " ");
            }
            free(reader);
        }
    /* Build binary tree sorted by frequency/word */
    freq_root = post_order_build(word_root, freq_root);
    unique_words = count_tree(freq_root); 
    printf("%d\n", unique_words);
    printf("The top %d words (out of %d) are:\n", arg_num, unique_words);
    print_tree(freq_root);
    free_tree(word_root);
    fclose(fp);
    }
    return 0;
}
