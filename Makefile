# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/30 11:37:38 by dacortes          #+#    #+#              #
#    Updated: 2023/11/12 15:23:34 by fcespede         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               VARIABLES                                      #
################################################################################
NAME = minishell
CC = gcc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror  -g #-fsanitize=address
################################################################################
#  Bar                                                                         #
################################################################################
CURRENT_FILE = 0
PROGRESS_BAR :=
################################################################################
#                               SOURCES                                        #
################################################################################
SRC = built-ins/cd.c built-ins/echo.c built-ins/env.c built-ins/execute.c\
	built-ins/exit.c built-ins/export.c built-ins/pwd.c built-ins/unset.c\
	built-ins/utils.c\
	execute/clear.c execute/no_pipe.c execute/pipes.c execute/redirection.c\
	execute/utils.c\
	get/get_path.c get/get.c get/heredoc.c get/type_rdc.c get/utils.c\
	get/utils2.c\
	parse/analyze.c parse/copy.c parse/expand_tk.c parse/line.c parse/parse.c\
	parse/token.c parse/utils.c\
	utils.c utils2.c signal.c main.c
LIBFT = ./lib/libft/
READL = ./lib/readline/
L_SRC = ./src
L_LIB = ./lib/libft/libft.a
L_RDL = ./lib/readline/libreadline.a
L_HIT = ./lib/readline/libhistory.a 
INC		=	-I ./inc/\
			-I ./lib/libft/\
			-I ./lib/readline/
################################################################################
#                               DIRECTORIES                                    #
################################################################################
D_OBJ = $(L_SRC)/obj
OBJ = $(addprefix $(D_OBJ)/, $(SRC:.c=.o))
DEP = $(addprefix $(D_OBJ)/, $(SRC:.c=.d))
################################################################################
#                               BOLD COLORS                                    #
################################################################################
E = \033[m
R = \033[31m
G = \033[32m
Y = \033[33m
B = \033[34m
P = \033[35m
C = \033[36m
################################################################################
#  FONT                                                                        #
################################################################################
ligth = \033[1m
dark = \033[2m
italic = \033[3m
################################################################################
#                               MAKE RULES                                     #
################################################################################
#Rules
all: conf dir $(NAME)
-include $(DEP)
conf:
	@if [ ! -f $(READL)config.status ]; then\
		cd $(READL) && ./configure &> /dev/null; \
		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
	fi
dir:
	make -C $(LIBFT) --no-print-directory
	make -C $(READL) --no-print-directory &> /dev/null
	-mkdir  $(D_OBJ)
	-mkdir	$(D_OBJ)/built-ins
	-mkdir	$(D_OBJ)/execute
	-mkdir	$(D_OBJ)/get
	-mkdir  $(D_OBJ)/parse
$(D_OBJ)/%.o:$(L_SRC)/%.c Makefile
	$(CC) -MMD $(FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@ $(INC)
	$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1)))) \
	$(eval PROGRESS_BAR := $(shell awk "BEGIN { printf \"%.0f\", $(CURRENT_FILE)*100/$(TOTAL_FILES) }")) \
	printf "\r$B$(ligth)⏳Compiling libft:$E $(ligth)%-30s [$(CURRENT_FILE)/$(TOTAL_FILES)] [%-50s] %3d%%\033[K" \
	"$<..." "$(shell printf '$(G)█%.0s$(E)$(ligth)' {1..$(shell echo "$(PROGRESS_BAR)/2" | bc)})" $(PROGRESS_BAR)
	
	@if [ $(PROGRESS_BAR) = 100 ]; then \
		echo "$(B) All done$(E)"; \
	fi
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(L_LIB) $(L_RDL) $(L_HIT) -ltermcap -lreadline -o $(NAME) $(INC)
	echo "\n\n✅ ==== $(B)$(ligth)Project minishell compiled!$(E) ==== ✅"
################################################################################
#                               CLEAN                                          #
################################################################################

.PHONY: all clean fclean re
fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT) --no-print-directory
	make clean -C $(READL) --no-print-directory &> /dev/null
	echo "✅ ==== $(P)$(ligth)minishell executable files and name cleaned!$(E) ==== ✅\n"
	
clean:
	$(RM) $(D_OBJ)
	make clean -C $(LIBFT) --no-print-directory
	make -C $(READL) --no-print-directory &> /dev/null
	echo "✅ ==== $(P)$(ligth)minishell object files cleaned!$(E) ==== ✅"
re: fclean all
TOTAL_FILES := $(words $(SRC))
.SILENT:
