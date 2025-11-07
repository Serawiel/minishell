#include "vbc.h"

node	*pars_add(char **s);
<<<<<<< HEAD
node	*pars_mult(char **s);

node	*new_node(int type, int val, node *l, node *r)
=======

node	*create_node(int type, int val, node *l, node *r)
>>>>>>> b1a44e5 (vbc)
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
		printf("Unexpected end of input\n");
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

// int	expect(char **s, char c)
// {
// 	if (accept(s, c))
// 		return (1);
// 	unexpected(**s);
// 	return (0);
// }

node	*pars_var(char **s)
{
	node	*ret;

	if (accept(s, '('))
	{
		ret = pars_add(s);
<<<<<<< HEAD
		if (!ret || !accept(s, ')'))
=======
		if (!ret || !expect(s, ')'))
>>>>>>> b1a44e5 (vbc)
		{
			destroy_tree(ret);
			return (NULL);
		}
		return (ret);
	}
	if (isdigit(**s))
	{
		ret = new_node(VAL, (**s - '0'), NULL, NULL);
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
<<<<<<< HEAD
		left = new_node(MULTI, 0, left, right);
=======
		left = create_node(MULTI, 0, left, right); // ✅ Met à jour left
>>>>>>> b1a44e5 (vbc)
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
<<<<<<< HEAD
	}
	return (left);
=======
		// ✅ PAS DE RETURN ICI !
	}
	return (left); // ✅ Return APRÈS le while
>>>>>>> b1a44e5 (vbc)
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
<<<<<<< HEAD
		left = new_node(ADD, 0, left, right);
=======
		left = create_node(ADD, 0, left, right); // ✅ Met à jour left
>>>>>>> b1a44e5 (vbc)
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
<<<<<<< HEAD
	}
	return (left);
=======
		// ✅ PAS DE RETURN ICI ! La boucle continue
	}
	return (left); // ✅ Return APRÈS le while
>>>>>>> b1a44e5 (vbc)
}

node	*parse_expr(char *s)
{
	node	*ret;

	ret = pars_add(&s);
	if (*s || !ret)
	{
		unexpected(*s);
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
	if (argc != 2)
		return (1);
	node *tree = parse_expr(argv[1]);
	if (!tree)
		return (1);
	printf("%d\n", eval_tree(tree));
	destroy_tree(tree);
}
