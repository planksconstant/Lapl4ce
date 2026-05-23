#ifndef AST_H
#define AST_H

typedef enum {
  NODE_OP,
  NODE_VAR,
  NODE_EXP_BASE,
  NODE_NUM,
} ASTNodeType;

// op means operator like + - and stuff
typedef struct ASTNode {
  ASTNodeType type;
  char op;
  int val;
  struct ASTNode *left;
  struct ASTNode *right;
} ASTNode;

ASTNode *create_op_node(char op, ASTNode *left, ASTNode *right);
ASTNode *create_num_node(int val);
ASTNode *create_var_node(void);
ASTNode *create_exp_node(void);
// recursive
void print_ast(ASTNode *node);

#endif
