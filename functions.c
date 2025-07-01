#include "main.h"

#define MAX_TOKEN 1000

Token tokens[MAX_TOKEN];

int token_count=0;
int in_multiline_comments;

Error errors[MAX_ERRORS];
int error_count = 0;
char symbol_stack[100];
int top = -1;

const char *res_keywords_data[] = {"const", "volatile", "extern", "auto", "register", "static",
    "signed", "unsigned", "short", "long", "double", "char",
    "int", "float", "struct", "union", "enum", "void", "typedef", ""};

const char *res_keywords_non_data[] = { "goto", "return", "continue", "break", "if", "else", "for",
    "while", "do", "switch", "case", "default", "sizeof", ""};

int validate_file(char *filename)
{
    FILE *file;
    if((strstr(filename, ".c")== NULL) || (strcmp(strstr(filename,".c"),".c")!=0))
    {
        return 1;
    }
    
    file=fopen(filename,"r");
    if(file==NULL)
    {
        printf("INFO : %s is not avilable\n",filename);
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}


int is_res_keyword_data(char *word)
{
    for(int i=0;res_keywords_data[i][0] != '\0';i++)
    {
        if(strcmp(word,res_keywords_data[i])==0)
        {
            return 1;
        }
    }
    return 0;
}
int is_res_keyword_nonData(char *word)
{
    for(int i=0;res_keywords_non_data[i][0] != '\0';i++)
    {
        if(strcmp(word,res_keywords_non_data[i])==0)
        {
            return 1;
        }
    }
    return 0;
}

int is_operator(char ch)
{
    char operators[] = "+-*/%<>=!&|^";
    for (int i = 0; operators[i] != '\0'; i++)
    {
        if (ch == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_symbol(char ch)
{
    char symbols[] = "(){}[];,";
    for (int i = 0; symbols[i] != '\0'; i++)
    {
        if (ch == symbols[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_number(char *word)
{
     int dot_count = 0;
    for(int i=0;word[i];i++)  
    {
        if (word[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
                return 0; // more than one dot is invalid
        }
        if(!isdigit(word[i]))
        {
            return 0;
        }
    }
    return 1;
}
void addToken(char *type,char *word,int line_no)
{

    
    while (isspace(*word)) word++; 

    char clean_word[BUFF_SIZE];
    int i = 0;
    while (word[i] != '\0' && i < BUFF_SIZE - 1)
    {
        clean_word[i] = word[i];
        i++;
    }
    clean_word[i] = '\0';

    while (i > 0 && isspace(clean_word[i - 1])) {
        clean_word[--i] = '\0';
    }

    strcpy(tokens[token_count].word, clean_word);
    strcpy(tokens[token_count].type, type);
    tokens[token_count].lineno = line_no;
    token_count++;

}

void addError(const char *msg, int line_no) {
    if (error_count < MAX_ERRORS) {
        snprintf(errors[error_count].message, LINE_SIZE, "%s", msg);
        errors[error_count].line_no = line_no;
        error_count++;
    }
}


void push(char c) {
    if (top < 99) symbol_stack[++top] = c;
}

char pop() {
    if (top >= 0) 
    {
        return symbol_stack[top--];

    }
    return '\0';
}

char peek() {
    if (top >= 0) 
    {
        return symbol_stack[top];

    }
    return '\0';
}

void read_and_print_words(char *filename)
{
    FILE *file=fopen(filename,"r");
    char word_line[LINE_SIZE];
    int line_no = 1;
   while (fgets(word_line, sizeof(word_line), file))
    {
        printf("%s", word_line);
        tokenize(word_line, line_no);
        line_no++;
    }

    fclose(file);
}

void tokenize(char *word_line,int line_no)
{

  int k = 0;
  while (isspace(word_line[k])) k++;  

 if (word_line[k] == '#') 
 {
    char header_token[LINE_SIZE];
    strcpy(header_token, &word_line[k]);
    header_token[strcspn(header_token, "\n")] = '\0';  
    addToken("Preprocessor", header_token, line_no);
    return;
 }
    char word[50];
    int i=0,j=0;
    while(word_line[i] != '\0')
    {
        if(in_multiline_comments)    
        {
            if(word_line[i] == '*' && word_line[i+1]=='/')
            {
                in_multiline_comments=0;
                i += 2;
            }
            else
            {
                i++;
            }
            continue;
        }

        if(word_line[i] == '/' && word_line[i+1] == '/') 
        {
            break;
        }
        if(word_line[i] == '/' && word_line[i+1] == '*') 
        {
            in_multiline_comments=1;
            i += 2;
            continue;
        }

        if(isalnum(word_line[i]) || word_line[i]=='_' || word_line[i]=='.')
        {
            word[j++]=word_line[i];
        }
        else
        {
            if(j>0)
            {
                word[j]='\0';
                
                if(is_res_keyword_data(word))
                {
                    addToken("Res keyword",word,line_no);
                }
                else if(is_res_keyword_nonData(word))
                {
                    addToken("Res keyword nonData",word,line_no);
                }
                else if(is_number(word))
                {
                    addToken("Number",word,line_no);
                }
                else
                {
                    addToken("Identifier",word,line_no);

                }
                j=0;
            }

            if(is_operator(word_line[i]))
            {
                char op[2] = {word_line[i],'\0'};
                addToken("Operator",op,line_no);
            }
            else if(is_symbol(word_line[i])) 
            {
                char sym[2] = {word_line[i], '\0'};
                addToken("Symbol", sym, line_no);

                if (word_line[i] == '(' || word_line[i] == '{' || word_line[i] == '[') {
                    push(word_line[i]);
                } else if (word_line[i] == ')' || word_line[i] == '}' || word_line[i] == ']') {
                    char expected;
                    switch (word_line[i]) {
                        case ')': expected = '('; break;
                        case '}': expected = '{'; break;
                        case ']': expected = '['; break;
                    }

                    if (peek() != expected) {
                        char msg[100];
                        sprintf(msg, "Mismatched or extra '%c'", word_line[i]);
                        addError(msg, line_no);
                    } else {
                        pop();
                    }
                }
            }

        }
        i++;
    }
    if(j>0)  
    {
        word[j]='\0';
        
        if(is_res_keyword_data(word))
        {
            addToken("Res keyword",word,line_no);
        }
        else if(is_res_keyword_nonData(word))
        {
            addToken("Res keyword nonData",word,line_no);
        }
        else if(is_number(word))
        {
            addToken("Number",word,line_no);
        }
        else
        {
            addToken("Identifier",word,line_no);
        }
    }

}