#ifndef VBC_H
# define VBC_H

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>

typedef struct node
{
	enum
	{
		ADD,
		MULTI,
		VAL
	} type;
	int			val;
	struct node	*l;
	struct node	*r;
}				node;

#endif