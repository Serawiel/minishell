#include "vbc.h"

node	*pars_add(char **s);

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

node	*pars_var(char **s)
{
	node	*ret;

	if (accept(s, '('))
	{
		ret = pars_add(s);
		if (!ret || !expect(s, ')'))
		{
			destroy_tree(ret);
			return (NULL);
		}
		return (ret);
	}
	if (isdigit(**s))
	{
		ret = create_node(VAL, (**s - '0'), NULL, NULL);
		if (!ret)
			return (NULL);
		(*s)++;
		return (ret);
	}
	return (NULL);
}

node	*pars_mult(char **s)
{
	node	*left;
	node	*right;

	left = pars_var(s);
	if (!left)
		return (NULL);
	while (accept(s, '*'))
	{
		right = pars_var(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		left = create_node(MULTI, 0, left, right); // ✅ Met à jour left
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
		// ✅ PAS DE RETURN ICI !
	}
	return (left); // ✅ Return APRÈS le while
}

node	*pars_add(char **s)
{
	node	*left;
	node	*right;

	left = pars_mult(s);
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		right = pars_mult(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		left = create_node(ADD, 0, left, right); // ✅ Met à jour left
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
		// ✅ PAS DE RETURN ICI ! La boucle continue
	}
	return (left); // ✅ Return APRÈS le while
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
	return (-1);
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
