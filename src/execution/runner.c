/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:36:02 by rgohrig           #+#    #+#             */
/*   Updated: 2025/10/31 17:06:27 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <sys/file.h> // debuging only

// call ones every line to run the whole tree starting from root
pid_t	run_tree(t_expression *cmd)
{
	pid_t	pid;

	pid = -1;
	if (cmd == NULL)
		return (-1);

	gc_mode(GC_TEMPORARY);

	// flock(2, LOCK_EX);
	// msg_error("    start","");
	// debug_files(cmd->files);
	inherit_files(cmd);
	// if (cmd->first && cmd->second)
	// {
	// 	debug_files(cmd->first->files);
	// 	debug_files(cmd->second->files);
	// }
	// msg_error("    end","");
	// flock(2, LOCK_UN);




	if (cmd->type == OPERATOR_CMD)
		pid = run_cmd_switch(cmd);
	else if (cmd->type == OPERATOR_PIPE)
		pid = run_pipe(cmd);
	else if (cmd->type == OPERATOR_AND || cmd->type == OPERATOR_OR)
		pid = run_and_or(cmd);
	close_all_files(cmd);
	wait_and_set_exit_code(pid);
	return (pid);
}

pid_t run_cmd_switch(t_expression *cmd)
{
	resolve(cmd);// correct pos
	// debug_tree(data()->tree_root);
	if (is_piped_direct(cmd))
	{
		exe_command_no_return(cmd);
		return ((pid_t)-1);
	}
	else
		return (exe_command_return(cmd));
}

pid_t run_pipe(t_expression *cmd)
{
	pid_t pid_1;
	pid_t pid_2;

	file_add_front(&cmd->first->files);
	cmd->first->files->type = FD_PIPE_WRITE;
	file_add_front(&cmd->second->files);
	cmd->second->files->type = FD_PIPE_READ;
	save_pipe(&cmd->first->files->fd, &cmd->second->files->fd);

	pid_1 = save_fork();
	if (pid_1 == 0)
	{
		pid_1 = run_tree(cmd->first);// never return
		msg_exit("Programming error", "pipes 1", EXIT_GENERAL_ERROR);
	}
	save_close(&cmd->first->files->fd);
	if (is_piped_direct(cmd))
	{
		pid_2 = run_tree(cmd->second); // use me up
		msg_exit("Programming error", "pipes 2", EXIT_GENERAL_ERROR);
	}
	pid_2 = save_fork();
	if (pid_2 == 0)
	{
		pid_2 = run_tree(cmd->second);// never return
		msg_exit("Programming error", "pipes 3", EXIT_GENERAL_ERROR);
	}
	save_close(&cmd->second->files->fd);
	wait_and_set_exit_code(pid_1);
	// wait_and_set_exit_code(pid_2); wait in call function at the end
	return (pid_2);
}

pid_t run_and_or(t_expression *cmd)
{
	pid_t pid;

	pid = run_tree(cmd->first);
	// close_all_files(cmd->first);
	// wait_and_set_exit_code(pid);
	if ((data()->last_exit_code == 0 && cmd->type == OPERATOR_AND)
	 || (data()->last_exit_code != 0 && cmd->type == OPERATOR_OR))
	 {
		 pid = run_tree(cmd->second);
	 }
	// close_all_files(cmd);
	// wait_and_set_exit_code(pid);
	if (is_piped_direct(cmd))
	{
		exit_shell(data()->last_exit_code);
	}
	return (-1);
}

void wait_and_set_exit_code(pid_t pid)
{
	int status;

	status = 0;
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			data()->last_exit_code = WTERMSIG(status) + EXIT_SIGNAL_BASE;
		else if (WIFEXITED(status))
			data()->last_exit_code = WEXITSTATUS(status);
		sig_init();
	}
}


void inherit_files(t_expression *cmd)
{
	t_file *head;
	t_file **files_first_ptr;
	t_file **files_second_ptr;

	// msg_error("inherit_files", "1");
	if (cmd == NULL || cmd->first == NULL || cmd->second == NULL)
		return ;
	// msg_error("inherit_files", "2");
	files_first_ptr = &cmd->first->files;
	files_second_ptr = &cmd->second->files;
	head = file_pop_back(&cmd->files);
	while (head)
	{
		// msg_error("inherit_files", "3");
		// ft_fprintf(2, "pipe? 1=%d\n", cmd->type);
		// debug_files(cmd->files);
		// debug_files_robin(cmd->files);
		if (head->type == NOT_SET)
		{
			save_close(&head->fd);
			// msg_error("inherit_files", "file type not set");
		}
		else if (head->type == PATH_STDIN_READ
			|| head->type == FD_HEREDOC_READ
			|| head->type == FD_PIPE_READ)
		{
			file_append_front(files_first_ptr, head);
			// msg_error("inherit_files", "read");
		}
		else
		{
			if (cmd->type != OPERATOR_PIPE)
			{
				// msg_error("inherit_files", "WTF");
				file_append_front(files_first_ptr, file_dup_values(head));
				// msg_error("inherit_files", "WTF2");
			}
			file_append_front(files_second_ptr, head);
			// msg_error("inherit_files", "write");
		}
		head = file_pop_back(&cmd->files);
	}
	return ;
}


// pwd | (cat && (echo hi bob | cat -e))
// (echo 1 && echo 2) | (grep 1 && grep 2)
// echo 2 > test2.txt && (echo 1 && echo 2) | (grep 1 && grep 2 < test2.txt) && rm test2.txt

// set up debunging insied vs code with gdb and makefile