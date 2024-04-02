#include "minishell.h"

// extern char **environ;

// volatile sig_atomic_t g_signal = 1;

#ifndef UNIT_TESTS



void process_input_loop(char **line, char ***env_copy, t_hist **history, int *status) {
    char *prompt;
    char *tmpline;
	char **tokens;
	t_node *lst;

	int err_flag;

	err_flag = false;
    while((prompt = readline(*line)))
	{
        // free(*line);

		if (ft_strlen(prompt) == 0)
			continue;

		err_flag = false;

        tokens = tokenizer(prompt, *status);

		// print_string_tab(tokens);

		if (parsing_error(tokens))
			err_flag = true;

		if (!err_flag)
		{
			lst = parser(tokens);

			if (lst)
			{
				add_to_history(history, prompt);
				ft_write_history_file(prompt);
			}
			sort_infile(&lst);
			exe_prompt(lst, env_copy, history, status);
		}

        tmpline = builtin_pwd();
        *line = ft_strjoin(tmpline, "🌻 ");

		free_string_array(tokens);
        free(tmpline);
    }
}


int main(int ac, char **av, char **env)
{
	char 	*tmpline;
	char 	*line;
	char 	**tokens;
	int 	status;
	t_hist	*history;
	char 	**env_copy;

	tmpline = builtin_pwd();

	status = 0;
	signal(SIGINT, sigint_handler);  // Ctrl-C
	signal(SIGQUIT, sigquit_handler);  // Ctrl-'\'

	history = NULL;

	ft_read_history(&history);

	line = ft_strjoin(tmpline, "🌻 ");
	free(tmpline);
	env_copy = copy_env(env, 0);



	process_input_loop(&line, &env_copy, &history, &status);

	printf("exit\n");
	return (0);
}
#endif
