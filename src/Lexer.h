

#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
  TOKEN_VAR_T,
  TOKEN_EXP,
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_POWER,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_EOF,
  TOKEN_ERROR
} TokenType;

typedef struct {
  TokenType type;
  int value;
} Token;

int tokenize(const char *input, Token *token_buf, int max_token);
const char *token_type_to_str(TokenType type);

#endif
