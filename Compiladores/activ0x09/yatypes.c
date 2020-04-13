#include "yatypes.h"
#define STR_LEN 32

struct t_exp
{
	enum {EXP_INTLIT, EXP_FLOATLIT, EXP_STRINGLIT, EXP_BOOLLIT, EXP_ID, EXP_OP, EXP_PRINT, EXP_ARRAY, EXP_FUNC, EXP_ASSIGN} kind;

	union
	{
		char *id;
		int intlit;
		float floatlit;
		char *stringlit;
		bool boollit;

		struct
		{
			char *op;
			t_exp arg1;
			t_exp arg2;
		} op;
		
		struct
		{
			t_args args;
		} print;

		struct
		{
			t_exp exp;
			t_exp intlit;
		} array;

		struct
		{
			t_exp id;
			t_args args;
		} func;

		struct
		{
			t_exp id;
			t_exp value;
		} assign;

		
	} u;
};

/* ................................ */


struct t_type
{
	enum {TYPE_ID, TYPE_TYPE, TYPE_ARR} kind;

	union
	{
		char *type;
		t_exp id;

		struct
		{
			t_exp size;
			t_type type;
		} arr;

	} u;
};

/* ................................ */

struct t_argdef
{
	t_exp id;
	t_type type;
};

struct t_argdefs
{
	enum {ARGDEFS_SINGLE, ARGDEFS_LIST} kind;

	struct
	{
		t_argdef argdef;
		t_argdefs argdefs;
	} u;
};

/* ................................. */

struct t_args
{
	t_exp exp;
	t_args args;
};

/* .................................. */

struct t_ids
{
	t_exp id;
	t_ids ids;
};

/* ................................. */

struct t_stm
{
	enum {STM_DECLS, STM_EXP, STM_RETURN, STM_IFELSE, STM_WHILE, STM_NEXT} kind;

	union
	{
		t_exp exp;
		t_exp rtrn;
		
		struct
		{
			t_decl decl;
		} decl;

		struct
		{
			t_exp exp;
			t_stms stms1;
			t_stms stms2;
		} ifelse;

		struct
		{
			t_exp exp;
			t_stms stms;
		} whl;
	} u;
};

struct t_stms
{
	enum {STMS_SINGLE, STMS_LIST} kind;

	struct
	{
		t_stm stm;
		t_stms stms;
	} u;
};

/* ........................................... */

struct t_decl
{
	enum {DECL_VAR, DECL_FUNC, DECL_DEFINE} kind;

	union
	{
		struct
		{
			t_ids ids;
			t_type type;
			t_exp exp;	
		} var;

		struct
		{
			t_exp id;
			t_argdefs argdefs;
			t_type type;
			t_stms stms;
		} func;

		struct
		{
			t_exp id;
			t_type type;
		} define;

	} u;

};

struct t_decls
{
	enum {DECLS_SINGLE, DECLS_LIST} kind;

	struct
	{
		t_decl decl;
		t_decls decls;
	} u;
};

/* .................................. */

char *prep_str(char *str)
{
	char *aux = malloc(sizeof(char)*64);

	int j = 0;

	for(int i = 0; i < 64; i++)
	{
		if(str[i]=='%')
		{
			aux[j]='\\';
			aux[j+1]='%';
			j+=2;
			continue;
		}
		if(str[i]=='\\')
		{
			if(str[i+1] == 'n')
			{
				i++;
				continue;
			}
		}
		if(str[i]=='\0')
		{
			aux[j] = '\0';
			break;
		} else {
			
			if(str[i] == ' ')
			{
				aux[j] = '\\';
				j++;
			}

			aux[j] = str[i];

			j++;
		}
	}

	return aux;
}


/* .................................. */

t_exp t_exp_new_id(char *id)
{
	t_exp ret = (t_exp) malloc(sizeof (*ret));

	ret -> kind = EXP_ID;
	ret -> u.id = id;

	return ret;
}

t_exp t_exp_new_intlit(int num)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind =  EXP_INTLIT;

	ret -> u.intlit = num;

	return ret;
}

t_exp t_exp_new_floatlit(float num)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind =  EXP_FLOATLIT;

	ret -> u.floatlit = num;

	return ret;
}

t_exp t_exp_new_stringlit(char *str)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_STRINGLIT;

	ret -> u.stringlit = str;

	return ret;
}

t_exp t_exp_new_boollit(bool boollit)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_BOOLLIT;

	ret -> u.boollit = boollit;

	return ret;
}

t_exp t_exp_new_print(t_args args)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind =  EXP_PRINT;

	ret -> u.print.args = args; 

	return ret;
}

t_exp t_exp_new_array(t_exp exp, int dim)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_ARRAY;

	ret -> u.array.exp = exp;

	ret -> u.array.intlit = t_exp_new_intlit(dim);

	return ret;
}

t_exp t_exp_new_op(char *op, t_exp arg1, t_exp arg2)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_OP;

	ret -> u.op.op = op;

	ret -> u.op.arg1 = arg1;

	ret -> u.op.arg2 = arg2;

	return ret;
}

t_exp t_exp_new_func(char *id, t_args args)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_FUNC;

	ret -> u.func.id = t_exp_new_id(id);

	ret -> u.func.args = args;

	return ret;
}

t_exp t_exp_new_assign(t_exp id, t_exp value)
{
	t_exp ret = (t_exp) malloc(sizeof(*ret));

	ret -> kind = EXP_ASSIGN;

	ret -> u.assign.id = id;

	ret -> u.assign.value = value;

	return ret;
}

void t_exp_print(t_exp exp)
{
	if(exp)
	{
		switch (exp -> kind)
		{
			case EXP_INTLIT:
				printf("[.exp [.int $%d$ ] ]\n", exp -> u.intlit);
				break;

			case EXP_FLOATLIT:
				printf("[.exp [.float $%f$ ] ]\n", exp -> u.floatlit);
				break;

			case EXP_STRINGLIT:
				exp -> u.stringlit = prep_str(exp -> u.stringlit);
				printf("[.exp [.string $\"%s\"$ ] ]\n", exp -> u.stringlit);
				break;

			case EXP_BOOLLIT:
				printf(exp -> u.boollit ? "[.exp [.bool $true$ ] ]\n" : "[.exp [.bool $false$ ] ]\n");
				break;

			case EXP_ID:
				printf("[.exp [.id $%s$ ] ]\n", exp -> u.id);
				break;

			case EXP_OP:
				exp -> u.op.op = prep_str(exp -> u.op.op);
				printf("[.exp [.op $%s$ ] ", exp -> u.op.op);
				t_exp_print(exp -> u.op.arg1);

				if (exp -> u.op.arg2)
				{
					t_exp_print(exp -> u.op.arg2);
				}

				printf(" ]\n");

				break;

			case EXP_PRINT:
				printf("[.exp [.print ");
				t_args_print(exp -> u.print.args);
				printf(" ] ]\n");
				break;

			case EXP_ARRAY:
				printf("[.exp [.array ");
				t_exp_print(exp -> u.array.exp);
				t_exp_print(exp -> u.array.intlit);
				printf(" ] ]\n");
				break;

			case EXP_FUNC:
				printf("[.exp [.function ");
				t_exp_print(exp -> u.func.id);
				t_args_print(exp -> u.func.args);
				printf(" ] ]\n");
				break;

			case EXP_ASSIGN:
				printf("[.exp [.assign ");
				t_exp_print(exp -> u.assign.id);
				t_exp_print(exp -> u.assign.value);
				printf(" ] ]\n");
				break;
		}
	}
}

/* ............................... */


t_type t_type_new(char *type)
{
	t_type ret = (t_type) malloc(sizeof(*ret));

	ret -> kind = TYPE_TYPE;

	ret -> u.type = type;

	return ret;
}

t_type t_type_new_id(char *id)
{
	t_type ret = (t_type) malloc(sizeof(*ret));

	ret -> kind = TYPE_ID;

	ret -> u.id = t_exp_new_id(id);

	return ret;
}

t_type t_type_new_array(t_type type, int dim)
{
	t_type ret = (t_type) malloc(sizeof(*ret) * dim);

	ret -> kind = TYPE_ARR;

	ret -> u.arr.type = type;

	ret -> u.arr.size = t_exp_new_intlit (dim); 

	return ret;
}

void t_type_print(t_type type)
{
	switch (type -> kind)
	{
		case TYPE_TYPE:
			printf("[.type $%s$ ]\n", type -> u.type);
			break;

		case TYPE_ID:
			printf("[.type ");
			t_exp_print(type -> u.id);
			printf(" ]\n");
			break;

		case TYPE_ARR:
			printf("[.type ");
			t_type_print(type -> u.arr.type);
			printf("[.dim ");
			t_exp_print(type -> u.arr.size);
			printf(" ] ]\n");
			break;
	}
}

/* ............................................. */

t_ids t_ids_new(char *id, t_ids ids)
{
	t_ids ret = (t_ids) malloc(sizeof(*ret));

	ret -> id = t_exp_new_id(id);

	ret -> ids = ids;

	return ret;
}

void t_ids_print(t_ids ids)
{
	printf("[.ids ");
	t_exp_print(ids -> id);
	if (ids -> ids)
	{
		t_ids_print(ids -> ids);
	}
	printf(" ]\n");
}


/* ............................................. */

t_stm t_stm_new_return(t_exp exp)
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_RETURN;

	ret -> u.rtrn = exp;

	return ret;
}

t_stm t_stm_new_decl(t_decl decl)
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_DECLS;

	ret -> u.decl.decl = decl;

	return ret;
}

t_stm t_stm_new_exp(t_exp exp)
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_EXP;

	ret -> u.exp = exp;

	return ret;
}

t_stm t_stm_new_ifelse(t_exp exp, t_stms stms1, t_stms stms2)
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_IFELSE;

	ret -> u.ifelse.exp = exp;

	ret -> u.ifelse.stms1 = stms1;

	ret -> u.ifelse.stms2 = stms2;

	return ret;
}

t_stm t_stm_new_while(t_exp exp, t_stms stms)
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_WHILE;

	ret -> u.whl.exp = exp;

	ret -> u.whl.stms = stms;

	return ret;
}

t_stm t_stm_new_next()
{
	t_stm ret = (t_stm) malloc(sizeof(*ret));

	ret -> kind = STM_NEXT;

	return ret;
}

void t_stm_print(t_stm stm)
{
	switch (stm -> kind)
	{
		case STM_RETURN:
			printf("[.stm [.return ");
			t_exp_print(stm -> u.rtrn);
			printf(" ] ]\n");;
			break;

		case STM_DECLS:
			printf("[.stm ");
			t_decl_print(stm -> u.decl.decl);
			printf(" ]\n");
			break;

		case STM_EXP:
			printf("[.stm ");
			t_exp_print(stm -> u.exp);
			printf(" ]\n");;
			break;

		case STM_IFELSE:
			printf("[.stm [.ifelse ");
			t_exp_print(stm -> u.ifelse.exp);
			t_stms_print(stm -> u.ifelse.stms1);
			t_stms_print(stm -> u.ifelse.stms2);
			printf(" ] ]\n");
			break;

		case STM_WHILE:
			printf("[.stm [.while ");
			t_exp_print(stm -> u.whl.exp);
			t_stms_print(stm -> u.whl.stms);
			printf(" ] ]\n");
			break;

		case STM_NEXT:
			printf("[.stm .$next$ ]\n");
			break;
	}
}

t_stms t_stms_new(t_stm stm, t_stms stms)
{
	t_stms ret = (t_stms) malloc(sizeof(*ret));

	if (stms)
	{
		ret -> kind = STMS_LIST;
	}

	else
	{
		ret -> kind = STMS_SINGLE;
	}

	ret -> u.stm = stm;
	ret -> u.stms = stms;

	return ret;
}

void t_stms_print(t_stms stms)
{
	if (stms)
	{
		switch(stms -> kind)
		{
			case STMS_SINGLE:
				printf("[.stms ");
				t_stm_print(stms -> u.stm);
				printf("[.\\emph{empty} ]");
				printf(" ]\n");
				break;

			case STMS_LIST:
				printf("[.stms ");
				t_stm_print(stms -> u.stm);
				t_stms_print(stms -> u.stms);
				printf(" ]\n");
				break;
		}
	}
}

/* .................................. */


t_argdef t_argdef_new(char *id, t_type type)
{
	t_argdef ret = (t_argdef) malloc(sizeof(*ret));

	ret -> id = t_exp_new_id(id);

	ret -> type = type;

	return ret;
}

void t_argdef_print(t_argdef argdef)
{
	printf("[.argdef ");
	t_exp_print(argdef -> id);
	t_type_print(argdef -> type);
	printf(" ]\n");
}

t_argdefs t_argdefs_new(t_argdef argdef, t_argdefs argdefs)
{
	t_argdefs ret = (t_argdefs) malloc(sizeof(*ret));

	if (argdefs)
	{
		ret -> kind = ARGDEFS_LIST;
	}

	else
	{
		ret -> kind = ARGDEFS_SINGLE;
	}

	ret -> u.argdef = argdef;
	ret -> u.argdefs = argdefs;

	return ret;
}

void t_argdefs_print(t_argdefs argdefs)
{
	if (argdefs)
	{
		switch(argdefs -> kind)
		{
			case ARGDEFS_SINGLE:
				printf("[.argdefs ");
				t_argdef_print(argdefs -> u.argdef);
				printf("[.\\emph{empty} ]");
				printf(" ]\n");
				break;

			case ARGDEFS_LIST:
				printf("[.argdefs ");
				t_argdef_print(argdefs -> u.argdef);
				t_argdefs_print(argdefs -> u.argdefs);
				printf(" ]\n");
				break;
		}
	}
}

/* ................................ */

t_args t_args_new(t_exp exp, t_args args)
{
	t_args ret = (t_args) malloc(sizeof(*ret));

	ret -> exp = exp;

	ret -> args = args;

	return ret;
}

void t_args_print(t_args args)
{
	printf("[.args ");
	t_exp_print(args -> exp);
	if (args -> args)
	{
		t_args_print(args -> args);
	} else {

		printf("[.\\emph{empty} ]");
	}
	printf(" ]\n");
}
/* .................................. */

t_decl t_decl_new_var(t_ids ids, t_type type, t_exp exp)
{
	t_decl ret = (t_decl) malloc(sizeof(*ret));

	ret -> kind = DECL_VAR;

	ret -> u.var.ids = ids;

	ret -> u.var.type = type;

	ret -> u.var.exp = exp;

	return ret;
}

t_decl t_decl_new_func(char *id, t_argdefs argdefs, t_type type, t_stms stms)
{
	t_decl ret = (t_decl) malloc(sizeof(*ret));

	ret -> kind = DECL_FUNC;

	ret -> u.func.id = t_exp_new_id(id);

	ret -> u.func.argdefs = argdefs;

	ret -> u.func.type = type;

	ret -> u.func.stms = stms;

	return ret;
}

t_decl t_decl_new_define(char *id, t_type type)/* char not t_exp*/
{
	t_decl ret = (t_decl) malloc(sizeof(*ret));

	ret -> kind = DECL_DEFINE;

	ret -> u.define.id = t_exp_new_id(id);

	ret -> u.define.type = type;

	return ret;
}

void t_decl_print(t_decl decl)
{
	switch(decl -> kind)
	{

		case DECL_VAR:
			printf("[.decl ");
			t_ids_print(decl -> u.var.ids);
			t_type_print(decl -> u.var.type);
			t_exp_print(decl -> u.var.exp);
			printf(" ]\n");
			break;

		case DECL_FUNC:
			printf("[.decl ");
			t_exp_print(decl -> u.func.id);
			t_argdefs_print(decl -> u.func.argdefs);
			t_type_print(decl -> u.func.type);
			t_stms_print(decl -> u.func.stms);
			printf(" ]\n");
			break;

		case DECL_DEFINE:
			printf("[.decl ");
			t_exp_print(decl -> u.define.id);
			t_type_print(decl -> u.define.type);
			printf(" ]\n");
			break;
	}
}

t_decls t_decls_new(t_decl decl, t_decls decls)
{
	t_decls ret = (t_decls) malloc(sizeof(*ret));

	if (decls)
	{
		ret -> kind = DECLS_LIST;
	}

	else
	{
		ret -> kind = DECLS_SINGLE;
	}

	ret -> u.decl = decl;
	ret -> u.decls = decls;

	return ret;
}

void t_decls_print(t_decls decls)
{
	if (decls)
	{
		switch(decls -> kind)
		{
			case DECLS_SINGLE:
				printf("[.decls ");
				t_decl_print(decls -> u.decl);
				printf("[.\\emph{empty} ]");
				printf(" ]\n");
				break;

			case DECLS_LIST:
				printf("[.decls ");
				t_decl_print(decls -> u.decl);
				t_decls_print(decls -> u.decls);
				printf(" ]\n");
				break;
		}
	}
}

/* .................................. */
