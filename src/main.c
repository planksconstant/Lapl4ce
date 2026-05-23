#include "ast.h"
#include <stdio.h>

int main() {
  // 1. Build the left branch: t^2
  ASTNode *t = create_var_node();
  ASTNode *two = create_num_node(2);
  ASTNode *left_subtree = create_op_node('^', t, two);

  // 2. Build the right branch: e^3
  ASTNode *e = create_exp_node();
  ASTNode *three = create_num_node(3);
  ASTNode *right_subtree = create_op_node('^', e, three);

  // 3. Join them at the root with '+'
  ASTNode *root = create_op_node('+', left_subtree, right_subtree);

  // 4. Print your creation!
  printf("Generated AST Structural Representation:\n");
  print_ast(root);
  printf("\n");

  return 0;
}
