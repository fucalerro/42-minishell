#include "minishell.h"

// extern char **environ;

// volatile sig_atomic_t g_signal = 1;

#ifndef UNIT_TESTS



void process_input_loop(char **line, char ***env_copy, t_hist **history, int *status) {
    char *prompt;
    char *tmpline;

    while((prompt = readline(*line)))
	{
		if (prompt == NULL)
		{
			printf("exit\n");
			continue;
		}

        free(*line);
        char **tokens = tokenizer(prompt, *status); 
        t_node *lst = parser(tokens); 
        free_string_array(tokens);
        if (lst) {
            hist_append(history, prompt); 
            add_history(prompt);
            ft_write_history_file(prompt); 
        }

        sort_infile(&lst);
        exe_prompt(lst, env_copy, history, status);

        tmpline = builtin_pwd();
        *line = ft_strjoin(tmpline, "🌻 ");
        free(tmpline);
    }
}


int main(int ac, char **av, char **env)
{
	// char *prompt;
    // char *tmpline;
	char *tmpline = builtin_pwd();
	char *line;
	char **tokens;
	int status;

	// t_node *lst;
	t_hist *history;
	char **env_copy;

	status = 0;
	signal(SIGINT, sigint_handler);  // Ctrl-C
	signal(SIGQUIT, sigquit_handler);  // Ctrl-'\'

	history = NULL;

	ft_read_history(&history);

	line = ft_strjoin(tmpline, "🌻 ");
	free(tmpline);
	env_copy = copy_env(env, 0);

	process_input_loop(&line, &env_copy, &history, &status);

	// while((prompt = readline(line)))
	// {
	// 	free(line);
	// 	tokens = tokenizer(prompt, status);
	// 	lst = parser(tokens);
	// 	free_string_array(tokens);
	// 	if (lst)
	// 	{
	// 		hist_append(&history, prompt);
	// 		add_history(prompt);
	// 		ft_write_history_file(prompt);
	// 	}

	// 	sort_infile(&lst);
	// 	exe_prompt(lst, &env_copy, &history, &status);

	// 	tmpline = builtin_pwd();
	// 	line = ft_strjoin(tmpline, "🌻 ");
	// 	free(tmpline);
	// }

	printf("exit\n");
	return (0);
}
#endif
