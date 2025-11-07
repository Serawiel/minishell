#ifndef ARGO_H
# define ARGO_H

<<<<<<< HEAD
# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct json
{
	enum
	{
=======
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct	json {
	enum {
>>>>>>> b1a44e5 (vbc)
		MAP,
		INTEGER,
		STRING
	} type;
<<<<<<< HEAD
	union
	{
		struct
		{
			struct pair	*data;
			size_t		size;
		} map;
		int				integer;
		char			*string;
	};
}						json;

typedef struct pair
{
	char				*key;
	json				value;
}						pair;
=======
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;
>>>>>>> b1a44e5 (vbc)

#endif