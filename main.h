#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>   
#include <string.h>     
#include <ctype.h>     
#include <stdlib.h> 

#define LINE_SIZE 256
#define BUFF_SIZE 100


typedef struct 
{
    char word[BUFF_SIZE];
    char type[30];
    int lineno;
} Token;

typedef struct {
    char message[LINE_SIZE];
    int line_no;
} Error;

#define MAX_ERRORS 100
extern Error errors[MAX_ERRORS];
extern int error_count;

extern Token tokens[];
extern int token_count;

char pop();

void push(char c);
char peek();


void addError(const char *msg, int line_no);

int validate_file(char *filename);

void read_and_print_words(char *filename);

void tokenize(char *word_line,int line_no);

int is_res_keyword_data(char *word);

int is_res_keyword_nonData(char *word);

int is_operator(char ch);

int is_symbol(char ch);

int is_number(char *word);

void addToken(char *type,char *word,int line_no);

void check_errors_after_tokenization();

#endif