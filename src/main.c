#include "Lexer.h"
#include "ast.h"
#include <stdio.h>

int main() {
  char equation[1024] = "";
  printf("f(t) = ");
  if (fscanf(stdin, "%1023[^\n]", equation) != 1) {
    printf("Error in input ");
    return 1;
  }
  Token token_buffer[128];

  // Stage 1: Chop string into tokens
  int token_count = tokenize(equation, token_buffer, 128);
  if (token_count == -1) {
    printf("Lexer error detected.\n");
    return 1;
  }

  // Stage 2: Turn flat tokens into a tree map
  ASTNode *root = parse(token_buffer);

  // Stage 3: Print and verify the architecture
  printf("Input: %s\n", equation);
  printf("AST Structure:     ");
  print_ast(root);
  printf("\n");
  printf("Laplace Transform L[f(t)] :   ");
  generate_laplace(root);
  printf("\n");
  return 0;
}
