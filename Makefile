# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 10:21:00 by rgohrig           #+#    #+#              #
#    Updated: 2025/09/08 17:17:59 by rgohrig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----------------------------- GENERAL ----------------------------------------

NAME :=			minishell

CC :=			cc
DEBUG_FLAGS := -g -fsanitize=address,undefined# -g3 -O0 # debug flags
CFLAGS :=		-Wall -Werror -Wextra $(DEBUG_FLAGS)# standard flags
export CFLAGS # set also for the libft

LIBFT_DIR    = libft
LIBFT_CORE   = $(LIBFT_DIR)/libft.a
LIBFT_PRINTF = $(LIBFT_DIR)/libft_printf.a
LIBFT_GNL    = $(LIBFT_DIR)/libft_gnl.a
LIBFT        = $(LIBFT_PRINTF) $(LIBFT_GNL) $(LIBFT_CORE)

LIBS :=			$(LIBFT) -lreadline

HEADERS :=		-I ./include -I ./libft/include


# ----------------------------- NORMAL -----------------------------------------

DIR_SRC :=		src
SRC :=			$(shell find $(DIR_SRC) -type f -name '*.c')

DIR_OBJ :=		obj
OBJ :=			$(SRC:$(DIR_SRC)/%.c=$(DIR_OBJ)/%.o)

# ----------------------------- NORMAL -----------------------------------------

all: lazy_robin $(LIBFT) $(NAME)# temporary lazy

$(LIBFT):
	@make core printf gnl -C $(LIBFT_DIR) --no-print-directory > /dev/null

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

# ----------------------------- lazy ------------------------------------------

# temporary Rule to update the header file
lazy_robin:
	@awk '/ auto/ { exit } { print }' include/$(NAME).h > tmp-auto-header.h
	@echo '// auto' >> tmp-auto-header.h
	@awk '/^[a-zA-Z_][a-zA-Z0-9_ \*\t]*\([^\)]*\)[ \t]*$$/ { \
		last=$$0; \
		getline; \
		if ($$0 ~ /^\s*\{/) { \
			split(last, a, /[ \t]+/); \
			if (a[1] == "int") sub(/[ \t]+/, "\t\t\t", last); \
			else sub(/[ \t]+/, "\t\t", last); \
			print last ";"; \
		} \
	}' $(shell find $(DIR_SRC) -type f -name '*.c') | grep -v static >> tmp-auto-header.h
	@echo "\n#endif" >> tmp-auto-header.h
	@cmp -s tmp-auto-header.h include/$(NAME).h || mv tmp-auto-header.h include/$(NAME).h
	@rm -f tmp-auto-header.h


# ----------------------------- Clean ------------------------------------------

clean:
	@rm -f $(OBJ)
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
