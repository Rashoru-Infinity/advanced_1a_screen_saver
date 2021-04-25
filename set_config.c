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
#include <stdio.h>

static char *skip_space(char *s)
{
	char *head;

	head = s;
	while (*s == ' ' || *s == '\t')
	{
		if (*(++s) == '\0')
			return head;
	}
	return s;
}

static status_t set_map(arg_t *arg, const char *file_name)
{
	//skip space
	if (!(arg->map = read_map(skip_space((char *)file_name))))
		return FAIL;
	if (check_map(arg->map) == FAIL)
	{
		free(arg->map);
		arg->map = NULL;
		return FAIL;
	}
	return SUCCESS;
}

static pattern_t *get_ptn(t_array *ptn_list, char *name)
{
	size_t index;

	index = 0;
	while (index < ptn_list->size)
	{
		if (strcmp(((pattern_t *)(ptn_list->contents[index]))->name, name) == 0)
			return (pattern_t *)(ptn_list->contents[index]);
		++index;
	}
	return NULL;
}

static status_t set_pattern(arg_t *arg, char *name_str, char ***lines, int entry)
{
	char *name;
	pattern_t *ptn;
	char *func;
	action_list_t *action;
	action_list_t *last;

	while (*name_str && (*name_str == ' ' || *name_str == '\t'))
		++name_str;
	if (!*name_str)
		return FAIL;
	if (!(name = strdup(name_str)))
		return FAIL;
	if (!(ptn = calloc(1, sizeof(pattern_t))))
	{
		free(name);
		return FAIL;
	}
	ptn->name = name;
	if (arg->pattern_list->size == arg->pattern_list->real_size)
		array_extend(arg->pattern_list);
	if (!entry)
		arg->pattern_list->contents[arg->pattern_list->size++] = ptn;
	else
		arg->entry_point->contents[arg->pattern_list->size++] = ptn;
	(*lines)++;
	func = skip_space(**lines);
	last = NULL;
	while (strncmp(func, "exit", 5) != 0)
	{
		if (!(action = calloc(1, sizeof(action_list_t))))
			return FAIL;
		if (strncmp(func, "ahead", 6) == 0)
			action->func = ahead;
		else if (strncmp(func, "back", 5) == 0)
			action->func = back;
		else if (strncmp(func, "turnR", 6) == 0)
			action->func = turnR;
		else if (strncmp(func, "turnL", 6) == 0)
			action->func = turnL;
		else if (get_ptn(arg->pattern_list, func))
		{
			if (strncmp(func, name, strlen(name) + 1))
				memcpy(action, get_ptn(arg->pattern_list, func)->ptn, sizeof(action_list_t));
			else
			{
				if (get_ptn(arg->pattern_list, func)->ptn)
					memcpy(action, get_ptn(arg->pattern_list, func)->ptn, sizeof(action_list_t));
				else
					return FAIL;
			}
		}
		else
			return FAIL;
		if (ptn->ptn)
		{
			last = ptn->ptn;
			while (last)
			{
				if (!last->next)
				{
					last->next = action;
					break;
				}
				last = last->next;
			}
		}
		else
			ptn->ptn = action;
		++(*lines);
		func = skip_space(**lines);
	}
	++(*lines);
	return SUCCESS;
}

arg_t *set_config(char *content)
{
	char **lines;
	char **curr_line;
	char **line_words;
	char **curr_word;
	arg_t *arg;

	if (!content)
		return NULL;
	if (!(arg = calloc(1, sizeof(arg_t))))
		return NULL;
	if (!(arg->entry_point = calloc(1, sizeof(t_array))))
	{
		free(arg);
		return NULL;
	}
	if (!(arg->pattern_list = calloc(1, sizeof(t_array))))
	{
		free(arg->entry_point);
		free(arg);
		return NULL;
	}
	if (!(lines = ft_split(content, '\n')))
	{
		free(arg->entry_point);
		free(arg->pattern_list);
		free(arg);
		return NULL;
	}
	if (array_init(arg->entry_point, NULL, 10) == FAIL)
		return NULL;
	if (array_init(arg->pattern_list, NULL, 10) == FAIL)
		return NULL;
	curr_line = lines;
	while (*curr_line)
	{
		if (!(line_words = ft_split(*curr_line, ':')))
		{
			free(arg->entry_point);
			free(arg->pattern_list);
			free(arg);
			ft_split_clear(lines);
			return NULL;
		}
		curr_word = line_words;
		//set map file
		if (strncmp("map", skip_space(*curr_word), 4) == 0)
		{
			free(*(curr_word++));

			if (!*curr_word || set_map(arg, *curr_word) == FAIL)
			{
				free(arg->entry_point);
				free(arg->pattern_list);
				free(arg);
				ft_split_clear(lines);
				ft_split_clear(line_words);
				return NULL;
			}
			curr_line++;
			free(*(curr_word++));
			//check syntax error
			if (*curr_word)
			{
				free(arg->entry_point);
				free(arg->pattern_list);
				free(arg);
				ft_split_clear(lines);
				ft_split_clear(line_words);
				return NULL;
			}
		}
		//set pattern
		else if (strncmp("pattern", skip_space(*curr_word), 8) == 0)
		{
			free(*(curr_word++));
			if (set_pattern(arg, *curr_word, &curr_line, 0) == FAIL)
			{
				free(arg->entry_point);
				free(arg->pattern_list);
				free(arg);
				ft_split_clear(lines);
				ft_split_clear(line_words);
				return NULL;
			}
			free(*(curr_word++));
		}
		//set entryPoint
		else if (strncmp("entryPoint", skip_space(*curr_word), 11) == 0)
		{
			free(*(curr_word++));
			if (set_pattern(arg, *curr_word, &lines, 1) == FAIL)
			{
				free(arg->entry_point);
				free(arg->pattern_list);
				free(arg);
				ft_split_clear(lines);
				ft_split_clear(line_words);
				return NULL;
			}
			free(*(curr_word++));
		}
		else
			++curr_line;
	}
	return arg;
}
