#include "Lexer.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

static Token *token_stream = NULL;
static int current_idx = 0;

static Token peek(void) {
  return token_stream[current_idx];
} // look-ahead  helper
static Token advance(void) {
  Token t = peek();
  if (t.type != TOKEN_EOF) {
    current_idx++;
  }
  return t;
} // func to move pointer

// lowest to highest priority
static ASTNode *parse_expression(void);
static ASTNode *parse_term(void);
static ASTNode *parse_factor(void);

static ASTNode *parse_expression(void) {
  ASTNode *left = parse_term();
  while (peek().type == TOKEN_PLUS || peek().type == TOKEN_MINUS) {
    Token op_token = advance(); // consume '+' or '-'
    char op_char = (op_token.type == TOKEN_PLUS) ? '+' : '-';

    ASTNode *right = parse_term();
    left = create_op_node(op_char, left, right);
  }
  return left;
}

static ASTNode *parse_term(void) {
  ASTNode *left = parse_factor();

  while (peek().type == TOKEN_POWER) {
    advance(); // Consume '^'
    ASTNode *right = parse_factor();
    left = create_op_node('^', left, right);
  }
  return left;
}

static ASTNode *parse_factor(void) {
  Token t = peek();

  if (t.type == TOKEN_NUMBER) {
    advance();
    return create_num_node(t.value);
  }
  if (t.type == TOKEN_VAR_T) {
    advance();
    return create_var_node();
  }
  if (t.type == TOKEN_EXP) {
    advance();
    return create_exp_node();
  }
  if (t.type == TOKEN_LPAREN) {
    advance(); // Swallow '('
    ASTNode *node =
        parse_expression(); // Restart full hierarchy inside brackets
    if (peek().type == TOKEN_RPAREN) {
      advance(); // Swallow ')'
    } else {
      printf("Parser Error: Missing closing parenthesis\n");
      exit(1);
    }
    return node;
  }

  printf("Parser Error: Unexpected token raw type encountered\n");
  exit(1);
}

ASTNode *parse(Token *tokens) {
  token_stream = tokens;
  current_idx = 0;
  return parse_expression();
}
