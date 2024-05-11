/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:17:10 by elias             #+#    #+#             */
/*   Updated: 2024/05/11 16:15:27 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* AST according to norm */
/*
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
*/

/* AST Shorter and still fine by the norm */
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
			int	number;
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

int	main(void)
{
	printf("%d %d %d\n", AST_NBR, AST_ADD, AST_MUL);
	return (0);
}
