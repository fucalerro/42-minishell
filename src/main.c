#include "minishell.h"

// extern char **environ;

// volatile sig_atomic_t g_signal = 1;

#ifndef UNIT_TESTS


void deal_with_multi_cmd(t_node *node)
{
	int cmd_seen = 0;
	t_node *prev_cmd;
	char **tmp;

	prev_cmd = NULL;
	while (node)
	{
		if (node->type == T_CMD)
			cmd_seen ++;
		if(cmd_seen > 1)
		{
			prev_cmd = node->previous;
			while(prev_cmd && prev_cmd->type != T_CMD)
				prev_cmd = prev_cmd->previous;
			int count = 0;
			int i = 0;
			while(node->cmd[i++])
				count++;
			i=0;
			while(prev_cmd->cmd[i++])
				count++;
			tmp = (char **) malloc(sizeof(char *) * (count + 1));
			if(!tmp)
				return;
			int ii = 0;
			i = 0;
			while(prev_cmd->cmd[i])
				tmp[ii++] = prev_cmd->cmd[i++];
			i = 0;
			while(node->cmd[i])
				tmp[ii++] = node->cmd[i++];
			tmp[ii] = NULL;
			free(prev_cmd->cmd);// we need to free that here but lest do that antoher day
			prev_cmd->cmd = tmp;
			node->previous->next = node->next;
			if (node->next)
				node->next->previous = node->previous;
			//node = node->previous;
			//need to free dropped node here
			cmd_seen = 1;
		}
		if (node->type == T_PIPE)
			cmd_seen = 0;
		node = node->next;
	}
}
void process_input_loop(char **line, char ***env_copy, t_hist **history, int *status) {
    char *prompt;
    char *tmpline;
	t_tokens **tokens;
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
			//sort_infile(&lst);
			deal_with_multi_cmd(lst);
			exe_prompt(lst, env_copy, history, status);
		}

        tmpline = builtin_pwd();
        *line = ft_strjoin(tmpline, "🌻 ");

		// free_string_array(tokens);
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
