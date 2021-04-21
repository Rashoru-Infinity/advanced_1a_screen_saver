/* ************************************************************************** */
/*                                                                            */
/*   set_config.c                                                             */
/*                                                                            */
/*   By: al19136 <al19136@shibaura-it.ac.jp>                                  */
/*                                                                            */
/*   Created: 2021/04/21 14:47:07 by al19136                                  */
/*   Updated: 2021/04/21 14:47:07 by al19136                                  */
/*                                                                            */
/* ************************************************************************** */

#include <scr.h>
#include <world.h>
#include <string.h>
#include <stdlib.h>

static status_e set_map(arg_t *arg, const char *file_name)
{
	//skip space
	while (*file_name == ' ')
		++file_name;
	if (!(arg->map = read_map(file_name)))
		return FAIL;
	if (check_map(arg->map) == FAIL)
	{
		free(arg->map);
		arg->map = NULL;
		return FAIL;
	}
	return SUCCESS;
}

static status_e set_pattern(arg_t *arg, char *name, char ***lines)
{
	pattern_t *pattern;
	pattern_t *curr_ptn;
	action_list_t *action;
	char *line;

	while (*name && *name == ' ')
		++name;
	if (!(pattern = calloc(sizeof(pattern_t))))
		return FAIL;
	if (!(pattern->name = strdup(name)))
	{
		free(pattern)
		return FAIL;
	}
	(*lines)++;
	while (*lines)
	{
		line = **lines;
		while (*line || *line == ' ' || *line == '\t')
			++line;
		if (strncmp(line, "ahead", 6) == 0)
		{
			if (!(action = calloc(action_list_t)))
			{
				free(pattern);
				return FAIL;
			}
			action->func = ahead;
		}
		else if (strncmp(line, "back", 5) == 0)
		{
			if ((!action = calloc(action_list_t)))
			{
				free(pattern);
				return FAIL;
			}
			action->func = back;
		}
		else if (strncmp(line, "turnR", 6) == 0)
		{
			if ((!action = calloc(action_list_t)))
			{
				free(pattern);
				return FAIL;
			}
			action->func = turnR;
		}
		else if (strncmp(line, "turnL", 6) == 0)
		{
			if ((!action = calloc(action_list_t)))
			{
				free(pattern);
				return FAIL;
			}
			action->func = turnL;
		}
		else
		{
			curr_ptn = arg->pattern_list;
			if (copy_pattern() == FAIL)
			
		}
	}
}

arg_t *set_config(char *content)
{
	char **lines;
	char **curr_line;
	char **line_words;
	arg_t *arg;
	char *curr_word;

	if (!content)
		return NULL;
	if (!(arg = calloc(sizeof(arg_t))))
		return NULL;
	if (!(lines = ft_split(content, '\n')))
		return NULL;
	curr_line = lines;
	while (*curr_line)
	{
		if (!(line_words = ft_split(*curr_line, ':')))
			exit(1);
		curr_word = *line_words;
		//set map file
		if (strncmp("map", *curr_word, 4) == 0)
		{
			free(curr_word++);
			if (set_map(arg, curr_word) == FAIL)
			{
				split_clear(lines);
				split_clear(line_words);
				return NULL;
			}
			curr_line++;
			free(curr_word++);
			//check syntax error
			if (curr_word)
			{
				split_clear(lines);
				split_clear(line_words);
				return NULL;
			}
		}
		//set pattern
		else if (strncmp("pattern", *curr_word, 8) == 0)
		{
			free(curr_word++);
			if (set_pattern() == FAIL)
			{
				split_clear(lines);
				split_clear(line_words);
				return NULL;
			}	
		}
		//set entryPoint
		else if (strncmp("entryPoint", curr_word, 11) == 0)
		{
		}
		++curr_line;
	}
	return arg;
}
