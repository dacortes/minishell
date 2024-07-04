################################################################################
#                               VARIABLES                                      #
################################################################################

RMV = rm -rf
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
NAME = minishell 
TOTAL_FILES = $(words $(SOURCES))

DIRECTORIES_UTILS = obj
DIRECTORI_SOURCE = src
OBJECTS = $(addprefix $(DIRECTORIES_UTILS)/, $(SOURCES:.c=.o))
DEPENDENCIES = $(addprefix $(DIRECTORIES_UTILS)/, $(SOURCES:.c=.d))
INCLUDES = $(addprefix -I, inc)
SOURCES = main.c

LIBFT = ./lib/libft/

################################################################################
#                               BOLD COLORS                                    #
################################################################################

END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CIAN = \033[36m

################################################################################
#  FONT                                                                        #
################################################################################

ligth = \033[1m
dark = \033[2m
italic = \033[3m

################################################################################
#                               MAKE RULES                                     #
################################################################################

all: libft dir progress

libft:
	@if [ ! -d "./lib/libft" ]; then \
        git clone https://github.com/tu-usuario/libft.git ./lib; \
    else \
        echo "$(YELLOW)$(ligth)[ Warnig ]$(END) libft: already exists and is not an empty directory."; \
    fi
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n✅ ==== $(BLUE)$(ligth)Project $(NAME) compiled!$(END) ==== ✅"

$(DIRECTORIES_UTILS)/%.o:$(DIRECTORI_SOURCE)/%.c
	@printf "  $(ligth)Compiling $(BLUE)$<$(END)      "
	@$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INCLUDES)
	@$(call progress,$<)

dir:
	-mkdir -p $(DIRECTORIES_UTILS)
progress: $(OBJECTS) $(NAME)

################################################################################
#                               CLEAN                                          #
################################################################################

clean:
	$(RMV) $(OBJECTS) $(DIRECTORIES_UTILS) $(NAME)
	echo "✅ ==== $(PURPLE)$(ligth)$(NAME) object files cleaned!$(END) ==== ✅"

fclean: clean
	$(RMV) $(NAME)
	echo "✅ ==== $(PURPLE)$(ligth)$(NAME) executable files and name cleaned!$(END) ==== ✅"

define progress
	@$(eval COMPILED_FILES=$(shell expr $(COMPILED_FILES) + 1))
	@bash -c 'PROG_BAR_WIDTH=50; \
	PROGRESS=$$(($(COMPILED_FILES) * $$PROG_BAR_WIDTH / $(TOTAL_FILES))); \
	EMPTY=$$(($$PROG_BAR_WIDTH - $$PROGRESS)); \
	PROGRESS=$$((PROGRESS < 0 ? 0 : PROGRESS)); \
	EMPTY=$$((EMPTY < 0 ? 0 : EMPTY)); \
	printf "\r$(ligth)[$(GREEN)"; \
	for ((i = 0; i < $$PROGRESS; i++)); do echo -n "█"; done; \
	for ((i = 0; i < $$EMPTY; i++)); do echo -n " "; done; \
	printf "$(END)$(ligth)] "; \
	printf "%d%%$(END)" $$((100 * $(COMPILED_FILES) / $(TOTAL_FILES)));'
endef

-include $(DEPENDENCIES)

re: fclean all
.PHONY: all clean progress fclean libft
COMPILED_FILES=0
.SILENT: