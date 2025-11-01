#include "vbc.h"

node	*create_node(int type, int val, node *l, node *r)
{
	node	*ret;

	ret = malloc(sizeof(node));
	if (!ret)
		return (NULL);
	ret->type = type;
	ret->val = val;
	ret->l = l;
	ret->r = r;
	return (ret);
}

void	destroy_tree(node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of file\n");
}

int	accept(char **s, char c)
{
	if (**s == c)
	{
		(*s)++;
		return (1);
	}
	return (0);
}

int	expect(char **s, char c)
{
	if (accept(s, c))
		return (1);
	unexpected(**s);
	return (0);
}

node	*pars_other(char **s)
{
	node	*ret;

	if (accept(s, '('))
	{
		ret = pars_add(s);
		if (!except(s, ')'))
			return (NULL);
	}
	if (isdigit(**s))
	{
		ret = create_node(VAL, (**s - '0'), NULL, NULL);
		if (!ret)
			return (NULL);
		(*s)++;
	}
	else
	{
		unexpected(**s);
		return (NULL);
	}
	return (ret);
}

node	*pars_mult(char **s)
{
	node *ret;
	if (accept(s, '*'))
	{
		ret = create_node(MULTI)
	}
}

void	*pars_add(char **s)
{
	// noeud gauche = pars_mult();
	// si + cree un noeud a droite
}

node	*parse_expr(char *s)
{
	node	*ret;

	ret = pars_add(&s);
	if (*s)
	{
		destroy_tree(ret);
		return (NULL);
	}
	return (ret);
}

int	eval_tree(node *tree)
{
	switch (tree->type)
	{
	case ADD:
		return (eval_tree(tree->l) + eval_tree(tree->r));
	case MULTI:
		return (eval_tree(tree->l) * eval_tree(tree->r));
	case VAL:
		return (tree->val);
	}
}

int	main(int argc, char **argv)
{
	node	*tree;

	if (argc != 2)
		return (1);
	tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
