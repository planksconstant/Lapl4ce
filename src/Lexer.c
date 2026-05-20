#include "Lexer.h"
#include <ctype.h>
int tokenize(const char *input, Token *token_buf, int max_token) {
  int iterator = 0;
  int token_count = 0;
  while (input[iterator] != '\0') {
    if (token_count >= max_token) {
      break;
    }
    if (input[iterator] == ' ' || input[iterator] == '\t') {
      iterator++;
      continue;
    }
    if (input[iterator] == 't') {
      token_buf[token_count].type = TOKEN_VAR_T;
      iterator++;
      token_count++;
    } else if (input[iterator] == '+') {
      token_buf[token_count].type = TOKEN_PLUS;
      iterator++;
      token_count++;

    } else if (input[iterator] == '-') {
      token_buf[token_count].type = TOKEN_MINUS;
      iterator++;
      token_count++;

    } else if (input[iterator] == '^') {
      token_buf[token_count].type = TOKEN_POWER;
      iterator++;
      token_count++;

    } else if (input[iterator] == '(') {
      token_buf[token_count].type = TOKEN_LPAREN;
      iterator++;
      token_count++;

    } else if (input[iterator] == ')') {
      token_buf[token_count].type = TOKEN_RPAREN;
      iterator++;
      token_count++;

    } else if (input[iterator] == 'e') {
      token_buf[token_count].type = TOKEN_EXP;
      iterator++;
      token_count++;
    } else if (isdigit(input[iterator])) {
      int val = 0;
      while (input[iterator] != '\0' && isdigit(input[iterator])) {
        val = (val * 10) + (input[iterator] - '0');
        iterator++;
      }
      token_buf[token_count].type = TOKEN_NUMBER;
      token_buf[token_count].value = val;
      token_count++;
    } else {
      token_buf[token_count].type = TOKEN_ERROR;
      token_count++;
      return -1;
    }
  }
  token_buf[token_count].type = TOKEN_EOF;
  token_count++;
  return token_count;
}
