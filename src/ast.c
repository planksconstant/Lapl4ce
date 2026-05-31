#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
/*

 *I personally call this the "Leaf generator" this is the fist time i am working
 with AST , this is just like an "helper file" for the parseing engine *it is
 the responsability of the Parsing engine to "fix all leaves" and stuff

 */

// calculations :>

static int factorial(int n) {
  int fact = 1;
  for (int i = 1; i <= n; i++) {
    fact = fact * i;
  }
  return fact;
}

ASTNode *create_op_node(char op, ASTNode *left, ASTNode *right) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = NODE_OP;
  node->op = op;
  node->val = 0;
  node->left = left;
  node->right = right;
  return node;
}

ASTNode *create_num_node(int val) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = NODE_NUM;
  node->op = '\0';
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

ASTNode *create_var_node(void) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = NODE_VAR;
  node->op = '\0';
  node->val = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

ASTNode *create_exp_node(void) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = NODE_EXP_BASE;
  node->op = '\0';
  node->val = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void print_ast(ASTNode *node) {
  if (node == NULL)
    return;

  if (node->type == NODE_OP)
    printf("(");

  print_ast(node->left);

  if (node->type == NODE_OP)
    printf(" %c ", node->op);
  else if (node->type == NODE_VAR)
    printf("t");
  else if (node->type == NODE_EXP_BASE)
    printf("e");
  else if (node->type == NODE_NUM)
    printf("%d", node->val);

  print_ast(node->right);

  if (node->type == NODE_OP)
    printf(")");
}

// Assisted code
void generate_laplace(ASTNode *node) {
  if (node == NULL)
    return;

  // RULE 1: Linearity Property (+ or -)
  if (node->type == NODE_OP && (node->op == '+' || node->op == '-')) {
    generate_laplace(node->left);  // Process left branch
    printf(" %c ", node->op);      // Print the operator sign
    generate_laplace(node->right); // Process right branch
    return;
  }

  // RULE 2: Exponent handling (The '^' operator node)
  if (node->type == NODE_OP && node->op == '^') {
    // Case A: Power Rule for t^n
    if (node->left->type == NODE_VAR) {
      int n = node->right->val;
      int n_fact = factorial(n);
      printf("(%d / s^%d)", n_fact, n + 1);
      return;
    }
    // Case B: Constant Exponent for e^n (like e^3)
    if (node->left->type == NODE_EXP_BASE) {
      int power = node->right->val;
      printf("(e^%d / s)", power); // e^3 is just a constant number!
      return;
    }
  }

  // RULE 3: Solo Independent Constant Leaves (like a lone number 5)
  if (node->type == NODE_NUM) {
    printf("(%d / s)", node->val);
    return;
  }

  // RULE 4: Solo Independent Variable 't' Leaf (equivalent to t^1)
  if (node->type == NODE_VAR) {
    printf("(1 / s^2)");
    return;
  }
}
