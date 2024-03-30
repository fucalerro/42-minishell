#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
	char *line = builtin_pwd();
	char *prompt;
	char **tokens;

	t_node *lst;
	t_hist *history;
	char **env_copy;

	signal(SIGINT, sigint_handler);  // Ctrl-C
	signal(SIGQUIT, sigquit_handler);  // Ctrl-\

	history = NULL;

	ft_read_history(&history);
	line = ft_strjoin(line, "🌻 ");

	env_copy = copy_env(env, 0);

	while((prompt = readline(line)))
	{
		tokens = tokenizer(prompt);
		lst = parser(tokens);

		if (lst)
		{
			hist_append(&history, prompt);
			add_history(prompt);
			ft_write_history_file(prompt);
		}
		// print_list(lst);

		sort_infile(&lst);
		exe_prompt(lst, &env_copy, &history);
		line = builtin_pwd();
		line = ft_strjoin(line, "🌻 ");
	}

	return (0);
}
#endif
