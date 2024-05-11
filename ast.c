/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:17:10 by elias             #+#    #+#             */
/*   Updated: 2024/05/11 17:58:49 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/* AST according to norm split in all the little parts */
typedef struct s_ast		t_ast ;
typedef enum e_ast_tag		t_ast_tag ;
typedef struct s_ast_nbr	t_ast_nbr ;
typedef struct s_ast_add	t_ast_add ;
typedef struct s_ast_mul	t_ast_mul ;
typedef union u_ast_data	t_ast_data ;

enum e_ast_tag
{
	AST_NBR,
	AST_ADD,
	AST_MUL,
};

typedef struct s_ast_nbr
{
	int	nbr;
}	t_ast_nbr;

struct s_ast_add
{
	t_ast	*left;
	t_ast	*right;
};

struct s_ast_mul
{
	t_ast	*left;
	t_ast	*right;
};

union u_ast_data
{
	t_ast_nbr	ast_nbr;
	t_ast_add	ast_add;
	t_ast_mul	ast_mul;
};

struct s_ast
{
	t_ast_tag	tag;
	t_ast_data	data;
};

/* AST Shorter and still fine by the norm */
/*
typedef struct s_ast	t_ast;

struct s_ast {
	enum {
		AST_NBR,
		AST_ADD,
		AST_MUL,
	} e_tag;
	union {
		struct s_ast_nbr
		{
			int	nbr;
		}		s_ast_nbr;
		struct s_ast_add
		{
			t_ast	*left;
			t_ast	*right;
		}			s_ast_add;
		struct s_ast_mul
		{
			t_ast	*left;
			t_ast	*right;
		}			s_ast_mul;
	} u_data;
};
*/

/* AST Best middleground I think */
/*
typedef struct s_ast	t_ast;

typedef enum e_ast_tag {
	AST_NBR,
	AST_ADD,
	AST_MUL,
}	t_ast_tag;

typedef union u_ast_data {
	struct s_ast_nbr
	{
		int	nbr;
	}		s_ast_nbr;
	struct s_ast_add
	{
		t_ast	*left;
		t_ast	*right;
	}			s_ast_add;
	struct s_ast_mul
	{
		t_ast	*left;
		t_ast	*right;
	}			s_ast_mul;
}	t_ast_data;

struct s_ast {
	t_ast_tag	tag;
	t_ast_data	data;
};
*/

/* AST structure as found online */
/*
typedef struct AST AST;

struct AST {
	enum {
		AST_NUMBER,
		AST_ADD,
		AST_MUL,
	} tag;
	union {
		struct AST_NUMBER { int number; } AST_NUMBER;
		struct AST_ADD { AST *left; AST *right; } AST_ADD;
		struct AST_MUL { AST *left; AST *right; } AST_MUL;
	} data;
};
*/

t_ast	*ast_new_node(t_ast ast)
{
	t_ast	*ret;

	ret = malloc(sizeof(t_ast));
	if (ret)
		*ret = ast;
	return (ret);
}

void	ast_print(t_ast *ptr)
{
	if (ptr->tag == AST_NBR)
	{
		printf("%d", ptr->data.ast_nbr.nbr);
		return ;
	}
	else if (ptr->tag == AST_ADD)
	{
		printf("(");
		ast_print(ptr->data.ast_add.left);
		printf(" + ");
		ast_print(ptr->data.ast_add.right);
		printf(")");
		return ;
	}
	else if (ptr->tag == AST_MUL)
	{
		printf("(");
		ast_print(ptr->data.ast_mul.left);
		printf(" * ");
		ast_print(ptr->data.ast_mul.right);
		printf(")");
		return ;
	}
	else
		printf("ERROR\n");
}

void	ast_free(t_ast *ptr)
{
	if (ptr->tag == AST_NBR)
		;
	else if (ptr->tag == AST_ADD)
	{
		ast_free(ptr->data.ast_add.left);
		ast_free(ptr->data.ast_add.right);
	}
	else if (ptr->tag == AST_MUL)
	{
		ast_free(ptr->data.ast_mul.left);
		ast_free(ptr->data.ast_mul.right);
	}
	else
		printf("ERROR\n");
	free(ptr);
}

int	main(void)
{
	t_ast	*ast_head;

	ast_head = ast_new_node((t_ast){
			AST_ADD, {.ast_add = (t_ast_add){
			ast_new_node((t_ast){
				AST_NBR, 5}),
			ast_new_node((t_ast){
				AST_NBR, 1})}}
		});
	ast_print(ast_head);
	printf("\n");
	ast_free(ast_head);

	ast_head = ast_new_node((t_ast){AST_MUL,
		{.ast_mul = (t_ast_mul){
			ast_new_node((t_ast){AST_ADD,
			{.ast_add = (t_ast_add){
				ast_new_node((t_ast){AST_NBR,
					7}),
				ast_new_node((t_ast){AST_NBR,
					5})}}}),
			ast_new_node((t_ast){
				AST_NBR,
				1}
				)}}});
	ast_print(ast_head);
	printf("\n");
	ast_free(ast_head);
	return (0);
}
