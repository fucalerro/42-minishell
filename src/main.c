#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
	char *tmpline = builtin_pwd();
	char *line;
	char *prompt;
	char **tokens;

	t_node *lst;
	t_hist *history;
	char **env_copy;

	signal(SIGINT, sigint_handler);  // Ctrl-C
	signal(SIGQUIT, sigquit_handler);  // Ctrl-'\'

	history = NULL;

	ft_read_history(&history);


	line = ft_strjoin(tmpline, "🌻 ");
	free(tmpline);
	env_copy = copy_env(env, 0);

	
	while((prompt = readline(line)))
	{

		if (prompt == NULL)
		{	
			printf("exit\n");
			free(line);
			break;
		}

		free(line);
		tokens = tokenizer(prompt);
		lst = parser(tokens);
		free_string_array(tokens);
		if (lst)
		{
			hist_append(&history, prompt);
			add_history(prompt);
			ft_write_history_file(prompt);
		}


		sort_infile(&lst);
		exe_prompt(lst, &env_copy, &history);
		tmpline = builtin_pwd();
		line = ft_strjoin(tmpline, "🌻 ");
		free(tmpline);
		
	}
	printf("exit\n");
	return (0);
}
#endif
