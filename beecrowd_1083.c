#include <stdio.h>
#include <stdlib.h>

typedef struct No no;
struct No{
    char c;
    no *prox;
};

typedef  struct stack Stack;
struct stack{
  no *top;
};

Stack *cria_stack(){
    Stack *novo = (Stack *)malloc(sizeof(Stack));
    novo->top = NULL;
    return novo;
}

no *cria_no(char c){
    no *novo = (no *)malloc(sizeof(no));
    novo->prox = NULL;
    novo->c = c;
    return novo;
}

void push(Stack *stack, char c){
    no *novo = cria_no(c);
    if(stack->top == NULL){
        stack->top = novo;
    }
    else{
        novo->prox = stack->top;
        stack->top = novo;
    }
}

char pop(Stack *stack){
    no *aux;
    char c;

    if(stack->top == NULL){
        return 0;
    }
    else{
        c = stack->top->c;
        aux = stack->top;
        stack->top = stack->top->prox;
        free(aux);
        return c;
    }
}

void libera_pilha(Stack *stack){
    no *aux;

    if(stack == NULL)
        return;

    while(stack->top != NULL){
        aux = stack->top;
        stack->top = stack->top->prox;
        free(aux);
    }

    free(stack);
}

int operadores(char c){
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '<' || c == '>' || c == '#' || c == '=' || c == '.' || c == '|');
}

int operandos(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int precedencia(char c){
    if(c == '^')
        return 6;
    if(c == '*' || c == '/')
        return 5;
    if(c == '-' || c == '+')
        return 4;
    if(c == '>' || c == '<' || c == '=' || c == '#')
        return 3;
    if(c == '.')
        return 2;
    if(c == '|')
        return 1;
    if(c == '(' || c == ')')
        return -1;
    return 0;
}

void show(char exp[]){
    Stack *stack = cria_stack();
    char result[1001];
    int i=0, j=0;

    while(exp[i] != '\0'){
        if(precedencia(exp[i]) == 0) {
            result[j] = exp[i];
            i++;
            j++;
        } else if(exp[i] == '(') {
            push(stack, exp[i]);
            i++;
        } else if(exp[i] == ')') {
            while(stack->top != NULL && stack->top->c != '(') {
                result[j] = pop(stack);
                j++;
            }
            pop(stack);
            i++;
        } else {
            while(stack->top != NULL && precedencia(stack->top->c) >= precedencia(exp[i])) {
                result[j] = pop(stack);
                j++;
            }
            push(stack, exp[i]);
            i++;
        }
    }
    while(stack->top != NULL){
        result[j] = pop(stack);
        j++;
    }
    result[j] = '\0';
    printf("%s\n", result);
    libera_pilha(stack);

}

int check(char exp[]){
    Stack *stack = cria_stack();
    int i, erro = 0;

    for(i=0;exp[i]!='\0';i++){
        if(!operadores(exp[i]) && !operandos(exp[i]) && exp[i] != '(' && exp[i] != ')'){
            return -1;
        }
    }

    for(i=0;exp[i]!='\0';i++){
        if(exp[i] == '(')
            push(stack, exp[i]);
        else if(exp[i] == ')' && pop(stack) != '('){
            return 0;
        }
    }
    if(stack->top != NULL)
        return 0;
    libera_pilha(stack);

    for(i=0; exp[i]!='\0'; i++){
        if(operadores(exp[i]) && operadores(exp[i+1]))
            return 0;
        else if(operandos(exp[i]) && operandos(exp[i+1]))
            return 0;
        if(operadores(exp[i]) && exp[i+1] == '\0')
            return 0;

    }

    return 1;
}

int main(){
    char exp[1001], result[1001];
    int i, j, n;

    scanf("%d", &n);

    while(fscanf(stdin, "%s", exp) != EOF){
        switch(check(exp)){
            case -1:
                printf("Lexical Error!\n");
                break;
            case 0:
                printf("Syntax Error!\n");
                break;
            case 1:
                show(exp);
                break;
        } 
    }
    return 0;
}

