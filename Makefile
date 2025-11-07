# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:21:00 by rgohrig           #+#    #+#              #
#    Updated: 2025/11/07 15:58:04 by modiepge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- GENERAL ----------------------------------------

NAME :=			minishell

CC :=			cc #cc #clang can be used for sanitizers
DEBUG_FLAGS :=#	-g -fsanitize=address,undefined -DDEBUG_MODE=0 # debug flags
CFLAGS :=		-Wall -Werror -Wextra $(DEBUG_FLAGS)# standard flags
export CFLAGS # set also for the libft

LIBFT_DIR    = libft
LIBFT_CORE   = $(LIBFT_DIR)/libft.a
LIBFT_PRINTF = $(LIBFT_DIR)/libft_printf.a
LIBFT_GNL    = $(LIBFT_DIR)/libft_gnl.a
LIBFT_LISTS  = $(LIBFT_DIR)/libft_lists.a
LIBFT        = $(LIBFT_PRINTF) $(LIBFT_GNL) $(LIBFT_LISTS) $(LIBFT_CORE)

LIBS := $(LIBFT) -L /opt/homebrew/opt/readline/lib -lreadline

HEADERS := -I ./include -I ./libft/include -I /opt/homebrew/opt/readline/include

# ----------------------------- NORMAL -----------------------------------------

DIR_SRC :=		src
SRC :=			main.c \
				execution/built_ins/blt_unset.c \
				execution/built_ins/blt_echo.c \
				execution/built_ins/blt_noname.c \
				execution/built_ins/blt_cd.c \
				execution/built_ins/blt_exit.c \
				execution/built_ins/blt_export.c \
				execution/built_ins/blt_parsing.c \
				execution/built_ins/blt_pwd.c \
				execution/built_ins/blt_env.c \
				execution/built_ins/blt_export_helper.c \
				execution/built_ins/run_builtin.c \
				execution/error_handeling/error_return.c \
				execution/error_handeling/exit_shell.c \
				execution/envirment/init.c \
				execution/envirment/change_lines.c \
				execution/envirment/get_data.c \
				execution/runner/run_tree.c \
				execution/runner/get_cmd_path.c \
				execution/runner/pipe_helper.c \
				execution/runner/inherit_files.c \
				execution/runner/set_redirects.c \
				execution/runner/run_command.c \
				execution/signals.c \
				utils/garbage_collector/gc_split.c \
				utils/garbage_collector/gc_allocs.c \
				utils/garbage_collector/gc_string.c \
				utils/garbage_collector/gc_init.c \
				utils/garbage_collector/gc_clear.c \
				utils/garbage_collector/gc_remaning.c \
				utils/wraper/save_dir.c \
				utils/wraper/save_files.c \
				utils/wraper/save_syscals.c \
				utils/files_list/close_fds.c \
				utils/files_list/new.c \
				utils/files_list/insert.c \
				utils/files_list/extract.c \
				utils/main_utils.c \
				parsing/tokenize/list_utils.c \
				parsing/tokenize/split/split.c \
				parsing/tokenize/split/split_utils.c \
				parsing/tokenize/split/split_variables.c \
				parsing/tokenize/token_is.c \
				parsing/tokenize/token_utils.c \
				parsing/tokenize/tokenize.c \
				parsing/tree/token_advance.c \
				parsing/tree/tree_utils.c \
				parsing/tree/tree.c \
				parsing/heredoc/heredoc_in.c \
				parsing/heredoc/heredoc_open.c \
				parsing/heredoc/heredoc_write.c \
				parsing/parse.c \
				parsing/process/cleanup.c \
				parsing/process/quotes.c \
				parsing/resolve.c \
				parsing/validate/syntax.c \
				parsing/validate/syntax_error.c \
				parsing/variables/variable_expand.c \
				parsing/variables/variable_pid.c \
				parsing/wildcards/wildcard_templating.c \
				parsing/wildcards/wildcard_utils.c \
				parsing/wildcards/wildcards.c \
				animation/animation.c \
				animation/animation_utils.c \
				animation/animations_2.c \
				animation/animations.c

DIR_OBJ :=		obj
OBJ :=			$(SRC:%.c=$(DIR_OBJ)/%.o)

# ----------------------------- NORMAL -----------------------------------------

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make core printf gnl lists -C $(LIBFT_DIR) --no-print-directory > /dev/null

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c | $(DIR_OBJ)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<
	@echo 🐚 $@

# executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "\n   🐚🐚🐚 $@   ($(CFLAGS))\n"

# ----------------------------- Clean ------------------------------------------

clean:
	@rm -rf $(DIR_OBJ)
	@make -C $(LIBFT_DIR) clean --no-print-directory > /dev/null
	@echo 🧹 cleaned all objects

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory > /dev/null
	@echo 🧹🧹🧹 cleaned $(NAME)

re:
	@make fclean --no-print-directory
	@make all --no-print-directory

.PHONY: all clean fclean re reb
