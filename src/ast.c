#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
/*

 *I personally call this the "Leaf generator" this is the fist time i am working
 with AST , this is just like an "helper file" for the parseing engine *it is
 the responsability of the Parsing engine to "fix all leaves" and stuff

 */
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
