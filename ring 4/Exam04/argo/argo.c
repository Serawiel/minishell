#include "argo.h"

int	peek(FILE *stream)
{
	int	c;

	c = getc(stream);
	ungetc(c, stream);
	return (c);
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return (1);
	}
	return (0);
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return (1);
	unexpected(stream);
	return (0);
}

void	free_json(json j)
{
	switch (j.type)
	{
	case MAP:
		for (size_t i = 0; i < j.map.size; i++)
		{
			free(j.map.data[i].key);
			free_json(j.map.data[i].value);
		}
		free(j.map.data);
		break ;
	case STRING:
		free(j.string);
		break ;
	default:
		break ;
	}
}

int	pars_integer(json *file, FILE *stream)
{
	if (!fscanf(stream, "%d", &file->integer))
	{
		unexpected(stream);
		return (-1);
	}
	file->type = INTEGER;
	return (1);
}

int	pars_string(json *file, FILE *stream)
{
	char	*buffer;
	int		i;
	char	c;
	char	*new_buffer;

	buffer = NULL;
	i = 0;
	if (!expect(stream, '"'))
		return (-1);
	while (1)
	{
		c = getc(stream);
		if (c == EOF)
		{
			free(buffer);
			unexpected(stream);
			return (-1);
		}
		if (c == '\\')
		{
			c = getc(stream);
			{
				if (c == EOF || (c != '"' && c != '\\'))
				{
					free(buffer);
					unexpected(stream);
					return (-1);
				}
				new_buffer = realloc(buffer, i + 1);
				if (!new_buffer)
				{
					free(buffer);
					return (-1);
				}
				buffer = new_buffer;
				buffer[i] = c;
				i++;
				continue ;
			}
		}
		if (c == '"')
			break ;
		new_buffer = realloc(buffer, i + 1);
		if (!new_buffer)
		{
			free(buffer);
			return (-1);
		}
		buffer = new_buffer;
		buffer[i] = c;
		i++;
	}
	new_buffer = realloc(buffer, i + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (-1);
	}
	buffer = new_buffer;
	buffer[i] = '\0';
	file->type = STRING;
	file->string = new_buffer;
	return (1);
}

int	pars_map(json *file, FILE *stream)
{
	char	c;
	json *key;
	json *value;

	if (!expect(stream, '{'))
		return (-1);
	file->type = MAP;
	file->map.size = 0;
	file->map.data = NULL;
	// MAP vide
	if (accept(stream, '}'))
		return (1);
	while (1)
	{
		c = getc(stream);
		if (c == EOF)
			return (-1);
		if (!pars_string(key, stream))
			return (-1);
		if (!argo(value, stream))
			return (-1);
		file->map.data = realloc(file->map.data, (file->map.size + 1)
				* sizeof(pair));
		file->map.data[file->map.size].key = key.string;
		file->map.data[file->map.size].value = value;
		file->map.size++;
	}
}

int	argo(json *file, FILE *stream)
{
	char	c;

	c = getc(stream);
	if (c == EOF)
	{
		unexpected(stream);
		return (-1);
	}
	ungetc(c, stream);
	if (isdigit(c) || c == '-')
		return (pars_integer(file, stream));
	if (expect(stream, '"'))
	{
		ungetc(c, stream);
		return (pars_string(file, stream));
	}
	if (expect(stream, "{"))
	{
		ungetc(c, stream);
		return (pars_map(file, stream));
	}
	return (-1);
}

void	serialize(json j)
{
	switch (j.type)
	{
	case INTEGER:
		printf("%d", j.integer);
		break ;
	case STRING:
		putchar('"');
		for (int i = 0; j.string[i]; i++)
		{
			if (j.string[i] == '\\' || j.string[i] == '"')
				putchar('\\');
			putchar(j.string[i]);
		}
		putchar('"');
		break ;
	case MAP:
		putchar('{');
		for (size_t i = 0; i < j.map.size; i++)
		{
			if (i != 0)
				putchar(',');
			serialize((json){.type = STRING, .string = j.map.data[i].key});
			putchar(':');
			serialize(j.map.data[i].value);
		}
		putchar('}');
		break ;
	}
}

int	main(int argc, char **argv)
{
	char	*filename;
	FILE	*stream;
	json	file;

	if (argc != 2)
		return (1);
	filename = argv[1];
	stream = fopen(filename, "r");
	if (argo(&file, stream) != 1)
	{
		free_json(file);
		return (1);
	}
	serialize(file);
	printf("\n");
}
