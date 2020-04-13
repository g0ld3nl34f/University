#ifndef YATYPE_H_
#define YATYPE_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

typedef struct t_exp *t_exp;
typedef struct t_type *t_type;
typedef struct t_argdef *t_argdef;
typedef struct t_argdefs *t_argdefs;
typedef struct t_args *t_args;
typedef struct t_ids *t_ids;
typedef struct t_stm *t_stm;
typedef struct t_stms *t_stms;
typedef struct t_decl *t_decl;
typedef struct t_decls *t_decls;

/*******************************************************/

t_exp t_exp_new_id(char *id);
t_exp t_exp_new_intlit(int num);
t_exp t_exp_new_floatlit(float num);
t_exp t_exp_new_stringlit(char *str);
t_exp t_exp_new_boollit(bool boollit);
t_exp t_exp_new_print(t_args args);
t_exp t_exp_new_array(t_exp exp, int dim);
t_exp t_exp_new_op(char *op, t_exp arg1, t_exp arg2);
t_exp t_exp_new_func(char *id, t_args args);
t_exp t_exp_new_assign(t_exp id, t_exp value);
t_type t_type_new(char *type);
t_type t_type_new_id(char *id);
t_type t_type_new_array(t_type type, int dim);
t_argdef t_argdef_new(char *id, t_type type);
t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs);
t_args t_args_new(t_exp exp, t_args args);
t_ids t_ids_new(char *id, t_ids ids);
t_stm t_stm_new_return(t_exp exp);
t_stm t_stm_new_decl(t_decl decl);
t_stm t_stm_new_exp(t_exp exp);
t_stm t_stm_new_ifelse(t_exp exp, t_stms stms1, t_stms stms2);
t_stm t_stm_new_while(t_exp exp, t_stms stms);
t_stm t_stm_new_next();
t_stms t_stms_new(t_stm stm, t_stms stms);
t_decl t_decl_new_var(t_ids ids, t_type type, t_exp exp);
t_decl t_decl_new_func(char *id, t_argdefs argdefs, t_type type, t_stms stms);
t_decl t_decl_new_define(char *id, t_type type);
t_decls t_decls_new(t_decl decl, t_decls decls);

/*******************************************************/

void t_exp_print(t_exp exp);
void t_type_print(t_type type);
void t_argdef_print(t_argdef argdef);
void t_argdefs_print(t_argdefs argdefs);
void t_args_print(t_args args);
void t_args_print(t_args args);
void t_ids_print(t_ids ids);
void t_stm_print(t_stm stm);
void t_stms_print(t_stms stms);
void t_decl_print(t_decl decl);
void t_decls_print(t_decls decls);

#endif