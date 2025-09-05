# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 12:10:52 by modiepge          #+#    #+#              #
#    Updated: 2025/08/26 16:29:14 by modiepge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Sources & Objects --------------------------------------------------------

SRC_CORE = \
	src/core/ft_strnstr.c \
	src/core/ft_isdigit.c \
	src/core/ft_putstr_fd.c \
	src/core/ft_strlcpy.c \
	src/core/ft_strlen.c \
	src/core/ft_memcmp.c \
	src/core/ft_putnbr_fd.c \
	src/core/ft_strchr.c \
	src/core/ft_striteri.c \
	src/core/ft_bzero.c \
	src/core/ft_strjoin.c \
	src/core/ft_isascii.c \
	src/core/ft_memcpy.c \
	src/core/ft_isprint.c \
	src/core/ft_putendl_fd.c \
	src/core/ft_toupper.c \
	src/core/ft_split.c \
	src/core/ft_strrchr.c \
	src/core/ft_isalpha.c \
	src/core/ft_memchr.c \
	src/core/ft_putchar_fd.c \
	src/core/ft_memset.c \
	src/core/ft_substr.c \
	src/core/ft_strncmp.c \
	src/core/ft_strmapi.c \
	src/core/ft_strtrim.c \
	src/core/ft_memmove.c \
	src/core/ft_strlcat.c \
	src/core/ft_calloc.c \
	src/core/ft_strdup.c \
	src/core/ft_atoi.c \
	src/core/ft_isalnum.c \
	src/core/ft_itoa.c \
	src/core/ft_tolower.c \
	src/core/ft_free.c \
	src/core/ft_atou_base.c \
	src/core/ft_isspace.c

SRC_LISTS =	\
	src/lists/ft_lstadd_back.c \
	src/lists/ft_lstnew.c \
	src/lists/ft_lstlast.c \
	src/lists/ft_lstclear.c \
	src/lists/ft_lstiter.c \
	src/lists/ft_lstmap.c \
	src/lists/ft_lstsize.c \
	src/lists/ft_lstadd_front.c \
	src/lists/ft_lstdelone.c

SRC_PRINTF = \
	src/printf/ptf_padding.c \
	src/printf/ptf_id.c \
	src/printf/ptf_p.c \
	src/printf/ptf_utility.c \
	src/printf/ptf_b.c \
	src/printf/ptf_spec.c \
	src/printf/ptf_s.c \
	src/printf/ft_printf.c \
	src/printf/ptf_dispatch.c \
	src/printf/ptf_o.c \
	src/printf/ptf_write.c \
	src/printf/ptf_x.c \
	src/printf/ptf_r.c \
	src/printf/ptf_flags_a.c \
	src/printf/ptf_percent.c \
	src/printf/ptf_u.c \
	src/printf/ptf_flags_b.c \
	src/printf/ptf_c.c \
	src/printf/ptf_vfprintf.c

SRC_GNL = \
	src/gnl/get_next_line_utils.c \
	src/gnl/get_next_line.c

OBJ_DIR = obj
SRC_DIR = src

OBJ = $(SRC_CORE:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_LISTS = $(SRC_LISTS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_PRINTF = $(SRC_PRINTF:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_GNL = $(SRC_GNL:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = libft.a
PRINTF = libft_printf.a
LISTS = libft_lists.a
GNL = libft_gnl.a

# --- Flags --------------------------------------------------------------------

FLAGS = -Werror -Wextra -Wall

INCLUDE = -Iinclude

CC = cc

# --- Rules --------------------------------------------------------------------

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJ)
	@printf "%-30s " "$(NAME)"
	@ar -src $@ $? && \
	printf "[success]\n" || printf "[error]\n"

printf: $(PRINTF)

$(PRINTF): $(OBJ_PRINTF)
	@printf "%-30s " "$(PRINTF)"
	@ar -src $(PRINTF) $? && \
	printf "[success]\n" || printf "[error]\n"

lists: $(LISTS)

$(LISTS): $(OBJ_LISTS)
	@printf "%-30s " "$(LISTS)"
	@ar -src $(LISTS) $? && \
	printf "[success]\n" || printf "[error]\n"

gnl: $(GNL)

$(GNL): $(OBJ_GNL)
	@printf "%-30s " "$(GNL)"
	@ar -src $(GNL) $? && \
	printf "[success]\n" || printf "[error]\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "%-30s " "$(notdir $@)"
	@$(CC) $(FLAGS) -c $< $(INCLUDE) -o $@ && \
	printf "[success]\n" || printf "[error]\n"

core: all

clean:
	@rm -f $(OBJ) $(OBJ_PRINTF) $(OBJ_LISTS) $(OBJ_GNL)
	@printf "libft: objects cleaned up\n"

fclean: clean
	@rm -f $(NAME) $(PRINTF) $(LISTS) $(GNL)
	@printf "libft: archives cleaned up\n"

re: fclean all

options:
	@printf "libft: core printf lists gnl clean fclean re\n"

.PHONY: all core printf lists gnl clean fclean re